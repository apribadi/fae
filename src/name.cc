enum class Name : u64;

namespace name {
  // 64-bit hash
  //
  // The hash is invariant under null-padding. That is, we treat every string
  // as if it were an infinitely long string terminated by repeated null bytes.
  //
  // The hash is injective on 8-byte strings.

  constexpr u64 ReadPeelableLoop(char const * a, size_t n) {
    // For a constant `n` this code gets unrolled by clang into an appropriate
    // set of simple loads.
    u64 x = 0;
    for (size_t i = 0; i < n; ++ i)
      x |= ((u64)(u8) a[i]) << (i * 8);
    return x;
  }

  constexpr u64 Read8b(char const * a) {
    return ReadPeelableLoop(a, 8);
  }

  constexpr u64 Read1bTo8b(char const * a, size_t n) {
    switch (n) {
      case 1: return ReadPeelableLoop(a, 1);
      case 2: return ReadPeelableLoop(a, 2);
      case 3: return ReadPeelableLoop(a, 3);
      case 4: return ReadPeelableLoop(a, 4);
      case 5: return ReadPeelableLoop(a, 5);
      case 6: return ReadPeelableLoop(a, 6);
      case 7: return ReadPeelableLoop(a, 7);
      case 8: return ReadPeelableLoop(a, 8);
    }

    __builtin_unreachable();
  }

  // TODO: optimize this value
  constexpr u64 MULT = 0x3C79AC492BA7B653ull;

  constexpr u64 Mix1(u64 x) {
    x ^= rotl(x, 21) ^ rotr(x, 21);
    x *= MULT;
    return x;
  }

  constexpr u64 Mix2(u64 x) {
    x ^= x >> 7;
    x ^= x << 9;
    return x;
  }

  constexpr u64 Mix3(u64 x) {
    x = __builtin_bswap64(x);
    x *= MULT;
    return x;
  }

  constexpr Name Make(char const * a, char const * b) {
    if (a == b)
      return (Name) (0);

    size_t n = ((b - a - 1) & 7) + 1;

    b -= n;

    u64 x = Mix1(Read1bTo8b(b, n));

    while (a != b) {
      b -= 8;
      x = Mix2(x);
      x += Mix1(Read8b(b));
    }

    x = Mix3(x);

    return (Name) (x);
  }

  constexpr Name Make(string_view s) {
    char const * a = &s[0];
    char const * b = a + s.size();
    return Make(a, b);
  }
}
