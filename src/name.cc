namespace name {
  enum class t : u64;

  // 64-bit hash
  //
  // The hash is invariant under null-padding. That is, we treat every string
  // as if it were an infinitely long string terminated by repeated null bytes.
  //
  // The hash is injective on 8-byte strings.

  constexpr u64 read_le_loop(char const * a, size_t n) {
    // For a constant `n` this code gets unrolled by clang into an appropriate
    // set of simple loads.
    u64 x = 0;
    for (size_t i = 0; i < n; ++ i)
      x |= static_cast<u64>(static_cast<u8>(a[i])) << (i * 8);
    return x;
  }

  constexpr u64 read_le_8b(char const * a) {
    return read_le_loop(a, 8);
  }

  constexpr u64 read_le_1b_to_8b(char const * a, size_t n) {
    switch (n) {
      case 1: return read_le_loop(a, 1);
      case 2: return read_le_loop(a, 2);
      case 3: return read_le_loop(a, 3);
      case 4: return read_le_loop(a, 4);
      case 5: return read_le_loop(a, 5);
      case 6: return read_le_loop(a, 6);
      case 7: return read_le_loop(a, 7);
      case 8: return read_le_loop(a, 8);
    }

    __builtin_unreachable();
  }

  // TODO: optimize this value
  constexpr u64 MULT = 0x3C79AC492BA7B653ull;

  constexpr u64 mix1(u64 x) {
    x ^= rotl(x, 21) ^ rotr(x, 21);
    x *= MULT;
    return x;
  }

  constexpr u64 mix2(u64 x) {
    x ^= x >> 7;
    x ^= x << 9;
    return x;
  }

  constexpr u64 mix3(u64 x) {
    x = __builtin_bswap64(x);
    x *= MULT;
    return x;
  }

  constexpr t hash(char const * a, char const * b) {
    if (a == b)
      return static_cast<t>(0);

    size_t n = ((b - a - 1) & 7) + 1;

    b -= n;

    u64 x = mix1(read_le_1b_to_8b(b, n));

    while (a != b) {
      b -= 8;
      x = mix2(x);
      x += mix1(read_le_8b(b));
    }

    x = mix3(x);

    return static_cast<t>(x);
  }

  constexpr t hash(string_view s) {
    char const * a = &s[0];
    char const * b = a + s.size();
    return hash(a, b);
  }

  namespace map {
  }
}
