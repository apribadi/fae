namespace arena {
  // TODO: take allocator as a parameter
  // TODO: allocate array
  // TODO: allocate span

  // 2MB
  constexpr size_t CHUNK_ALIGNMENT = 1 << 21;
  constexpr size_t CHUNK_CAPACITY_INCREMENT = 1 << 21;

  class t {
    private:
      size_t capacity;
      size_t mark;
      void * chunk;
      vector<void *> full_chunks;

      // PRECONDITIONS:
      // - `size` is positive
      // - `size` is a multiple of `align`
      // - `align` is a power of 2

      void * allocate(size_t size, size_t align) {
        if (size > mark) [[unlikely]] return allocate_slow(size, align);
        mark = (mark - size) & ~ (align - 1);
        return static_cast<byte *>(chunk) + mark;
      }

      void * allocate_slow(size_t size, size_t align) {
        size_t new_capacity = capacity + CHUNK_CAPACITY_INCREMENT;
        void * new_chunk = ::operator new(new_capacity, static_cast<align_val_t>(CHUNK_ALIGNMENT));
        void * old_chunk = chunk;

        capacity = new_capacity;
        mark = new_capacity;
        chunk = new_chunk;
        if (old_chunk) full_chunks.push_back(old_chunk); 

        return allocate(size, align);
      }

    public:
      t() :
        capacity(0),
        mark(0),
        chunk(nullptr),
        full_chunks()
      {
      }

      ~t() {
        if (chunk) ::operator delete(chunk); 
        for (void * p : full_chunks) ::operator delete(p);
      }

      t(const t&) = delete;
      t(t&&) = delete;
      t& operator=(const t&) = delete;
      t& operator=(t&&) = delete;

      template<class T, class ...A>
      T * make_array(size_t n, A&& ...a) {
        static_assert(is_trivially_destructible<T>());

        if (n == 0) return nullptr;

        T * p = static_cast<T *>(allocate(n * sizeof(T), alignof(T)));
        for (size_t i = 0; i < n; ++ i) new (&p[i]) T(forward<A>(a)...);

        return p;
      }

      template<class T, class ...A>
      T * make(A&&... a) {
        return make_array<T, A...>(1, a...);
      }

      template<class T, class ...A>
      span<T> make_span(size_t n, A&& ...a) {
        return span<T>(make_array<T, A...>(n, a...), n);
      }

      void clear() {
        // If we have any allocated chunks, we reset the most recently
        // allocated chunk and deallocate the other chunks.

        mark = capacity;
        for (void * p : full_chunks) ::operator delete(p);
        full_chunks.clear();
      }
  };
}
