namespace fae::mm::arena::internal {
  constexpr size_t CHUNK_ALIGNMENT = 1 << 21; // 2MB
  constexpr size_t CHUNK_INCREMENT = 1 << 21;
}

namespace fae::mm {

class Arena {
public:
  explicit Arena();
  ~Arena();

  Arena(Arena const &) = delete;
  Arena(Arena &&) = delete;
  Arena & operator=(Arena const &) = delete;
  Arena & operator=(Arena &&) = delete;

  template<class T, class ... A> T * make(A && ... a);
  template<class T, class ... A> T * make_array(size_t n, A && ... a);
  template<class T, class ... A> span<T> make_span(size_t n, A && ... a);
  template<class T, class U, class ... A> T * make_flex(size_t n, A && ... a);

  void clear();

private:
  size_t capacity;
  size_t mark;
  void * chunk;
  vector<void *> full_chunks;

  void * allocate(size_t, size_t);
  void * allocate_slow(size_t, size_t);
};

Arena::Arena() :
  capacity(0),
  mark(0),
  chunk(nullptr),
  full_chunks() {
}

Arena::~Arena() {
  if (chunk) ::operator delete(chunk); 
  for (void * p : full_chunks) ::operator delete(p);
}

void * Arena::allocate(size_t size, size_t align) {
  if (size > mark) [[unlikely]] return allocate_slow(size, align);
  mark = (mark - size) & ~ (align - 1);
  return static_cast<char *>(chunk) + mark;
}

void * Arena::allocate_slow(size_t size, size_t align) {
  size_t new_capacity = capacity + arena::internal::CHUNK_INCREMENT;
  void * old_chunk = chunk;
  void * new_chunk = ::operator new(new_capacity, (align_val_t) (arena::internal::CHUNK_ALIGNMENT));

  capacity = new_capacity;
  mark = new_capacity;
  chunk = new_chunk;
  if (old_chunk) full_chunks.push_back(old_chunk); 

  return allocate(size, align);
}

template<class T, class ... A>
T * Arena::make(A && ... a) {
  static_assert(is_trivially_destructible<T>());
  static_assert(alignof(T) <= arena::internal::CHUNK_ALIGNMENT);

  return new (allocate(sizeof(T), alignof(T))) T(forward<A>(a) ...);
}

template<class T, class ... A>
T * Arena::make_array(size_t n, A && ... a) {
  static_assert(is_trivially_destructible<T>());
  static_assert(alignof(T) <= arena::internal::CHUNK_ALIGNMENT);

  if (n == 0) return nullptr;

  T * p = static_cast<T *>(allocate(n * sizeof(T), alignof(T)));
  for (size_t i = 0; i < n; ++ i) new (p + i) T(forward<A>(a) ...);

  return p;
}

template<class T, class ... A>
span<T> Arena::make_span(size_t n, A && ... a) {
  return span<T>(make_array<T, A ...>(n, forward<A>(a) ...), n);
}

template<class T, class U, class ... A>
T * Arena::make_flex(size_t n, A && ... a) {
  static_assert(is_trivially_destructible<T>());
  static_assert(alignof(T) <= arena::internal::CHUNK_ALIGNMENT);

  static_assert(is_trivially_default_constructible<U>());
  static_assert(is_trivially_destructible<U>());
  static_assert(alignof(U) <= alignof(T));

  return new (allocate(sizeof(T) + n * sizeof(U), alignof(T))) T(forward<A>(a) ...);
}

void Arena::clear() {
  // If we have any allocated chunks, then we reset and retain the most
  // recently allocated chunk but deallocate the other chunks.

  mark = capacity;
  for (void * p : full_chunks) ::operator delete(p);
  full_chunks.clear();
}

}
