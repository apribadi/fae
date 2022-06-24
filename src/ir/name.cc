namespace fae::ir::name::internal {

  // 64-bit hash
  //
  // The hash is invariant under null-padding. That is, we treat every string
  // as if it were an infinitely long string terminated by repeated null bytes.
  //
  // The hash is injective on 8-byte strings.

  constexpr u64 read_peelable_loop(char * a, size_t n) {
    // For a constant `n` this code gets unrolled by clang into an appropriate
    // set of simple loads.
    u64 x = 0;
    for (size_t i = 0; i < n; ++ i)
      x |= ((u64)(u8) a[i]) << (i * 8);
    return x;
  }

  constexpr u64 read_8b(char * a) {
    return read_peelable_loop(a, 8);
  }

  constexpr u64 read_1b_to_8b(char * a, size_t n) {
    switch (n) {
      case 1: return read_peelable_loop(a, 1);
      case 2: return read_peelable_loop(a, 2);
      case 3: return read_peelable_loop(a, 3);
      case 4: return read_peelable_loop(a, 4);
      case 5: return read_peelable_loop(a, 5);
      case 6: return read_peelable_loop(a, 6);
      case 7: return read_peelable_loop(a, 7);
      case 8: return read_peelable_loop(a, 8);
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

  constexpr u64 hash(char * a, char * b) {
    if (a == b)
      return 0;

    size_t n = ((b - a - 1) & 7) + 1;

    b -= n;

    u64 x = mix1(read_1b_to_8b(b, n));

    while (a != b) {
      b -= 8;
      x = mix2(x);
      x += mix1(read_8b(b));
    }

    x = mix3(x);

    return x;
  }
}

namespace fae::ir {
  class Name {
  public:
    constexpr explicit Name(char *, char *);

    constexpr u64 hashcode();

  private:
    u64 value;

    constexpr explicit Name(u64);
  };

  constexpr Name::Name(u64 x) : value(x) { };

  constexpr Name::Name(char * a, char * b) : Name(name::internal::hash(a, b)) { };

  constexpr u64 Name::hashcode() {
    return value;
  }

  constexpr bool operator==(Name a, Name b) {
    return a.hashcode() == b.hashcode();;
  }
}
