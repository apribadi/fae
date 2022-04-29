namespace name {
  enum class t : u64;

  // compiles to a simple unaligned load
  u64 read_le_u64(char const * a) {
    u64 w = 0;
    for (size_t i = 0; i < 8; ++ i)
      w |= static_cast<u64>(static_cast<u8>(a[i])) << (i * 8);
    return w;
  }

  u64 read_le_u64_tail(char const * a, size_t n) {
    // TODO: optimize
    u64 w = 0;
    for (size_t i = 0; i < n; ++ i)
      w |= static_cast<u64>(static_cast<u8>(a[i])) << (i * 8);
    return w;
  }

  constexpr u64 MULT = 11400714819323198485ull;

  // invariant under null-padding
  t hash(char const * a, char const * b) {
    if (a == b)
      return static_cast<t>(0);

    size_t n = ((b - a - 1) & 7) + 1;

    b -= n;

    u64 u = read_le_u64_tail(b, n) * MULT;

    while (a != b) {
      u ^= (u >> 13); 
      u ^= (u << 7); 
      u ^= (u >> 17); 
      b -= 8;
      u |= read_le_u64(b) * MULT;
    }

    u = __builtin_bswap64(u);
    u *= MULT;
    u ^= (u >> 32);

    return static_cast<t>(u);
  }
}
