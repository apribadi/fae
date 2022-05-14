namespace arena {
  // TODO: take parent allocator as a parameter

  // 2MB
  constexpr size_t CHUNK_ALIGNMENT = 1 << 21;
  constexpr size_t CHUNK_INCREMENT = 1 << 21;
}

class Arena {
  private:
    size_t capacity;
    size_t mark;
    void * chunk;
    vector<void *> full_chunks;

    // PRECONDITIONS:
    // - `size` is positive
    // - `size` is a multiple of `align`
    // - `align` is a power of 2

    void * Allocate(size_t size, size_t align) {
      if (size > mark) [[unlikely]] return AllocateSlow(size, align);
      mark = (mark - size) & ~ (align - 1);
      return static_cast<char *>(chunk) + mark;
    }

    void * AllocateSlow(size_t size, size_t align) {
      size_t new_capacity = capacity + arena::CHUNK_INCREMENT;
      void * old_chunk = chunk;
      void * new_chunk = ::operator new(new_capacity, (align_val_t) (arena::CHUNK_ALIGNMENT));

      capacity = new_capacity;
      mark = new_capacity;
      chunk = new_chunk;
      if (old_chunk) full_chunks.push_back(old_chunk); 

      return Allocate(size, align);
    }

  public:
    Arena() :
      capacity(0),
      mark(0),
      chunk(nullptr),
      full_chunks()
    {
    }

    ~Arena() {
      if (chunk) ::operator delete(chunk); 
      for (void * p : full_chunks) ::operator delete(p);
    }

    Arena(Arena const &) = delete;
    Arena(Arena &&) = delete;
    Arena & operator=(Arena const &) = delete;
    Arena & operator=(Arena &&) = delete;

    template<class T, class ... A>
    T * MakeArray(size_t n, A && ... a) {
      static_assert(is_trivially_destructible<T>());
      static_assert(alignof(T) <= arena::CHUNK_ALIGNMENT);
      static_assert(popcount(alignof(T)) == 1);
      static_assert(sizeof(T) > 0);
      static_assert(sizeof(T) % alignof(T) == 0);

      if (n == 0) return nullptr;

      T * p = static_cast<T *>(Allocate(n * sizeof(T), alignof(T)));
      for (size_t i = 0; i < n; ++ i) new (p + i) T(forward<A>(a) ...);

      return p;
    }

    template<class T, class ... A>
    T * Make(A && ... a) {
      return MakeArray<T, A ...>(1, forward<A>(a) ...);
    }

    template<class T, class ... A>
    span<T> MakeSpan(size_t n, A && ... a) {
      return span<T>(MakeArray<T, A ...>(n, forward<A>(a) ...), n);
    }

    void Clear() {
      // If we have any allocated chunks, then we reset and retain the most
      // recently allocated chunk but deallocate the other chunks.

      mark = capacity;
      for (void * p : full_chunks) ::operator delete(p);
      full_chunks.clear();
    }
};
