namespace arena {
  constexpr size_t CHUNK_ALIGNMENT = 1 << 21;
  constexpr size_t CHUNK_CAPACITY_INCREMENT = 1 << 21;

  class t {
    private:
      size_t capacity;
      size_t mark;
      void * chunk;
      vector<void *> full_chunks;

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

      void * allocate(size_t size, size_t align) {
        if (size > mark) [[unlikely]] return allocate_slow(size, align);
        mark = (mark - size) & ~ (align - 1);
        return static_cast<byte *>(chunk) + mark;
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

      template<class T, class... A>
      T * make(A&&... a) {
        static_assert(is_trivially_destructible<T>());
        static_assert(alignof(T) <= CHUNK_ALIGNMENT);
        return new (allocate(sizeof(T), alignof(T))) T(forward<A>(a)...);
      }

      void clear() {
        for (void * p : full_chunks) ::operator delete(p);
        full_chunks.clear();

        // We leave the current chunk, if it is allocated.
        mark = capacity;
      }
  };
}
