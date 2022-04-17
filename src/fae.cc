#include <array>
#include <bit>
#include <cassert>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <stdexcept>
#include <span>
#include <vector>

#include "prelude.cc"
#include "arena.cc"
#include "io.cc"
#include "token.cc"
#include "lexer.cc"

class pair {
public:
  i64 x;
  i64 y;

  pair(i64 a, i64 b) : x(a), y(b) {}
  void print() { printf("x = %d, y = %d\n", (int) x, (int) y); }
};

__attribute__ ((noinline))
pair * foo(arena::t& arena, i64 x, i64 y) {
  return arena.make<pair>(x, y);
}

__attribute__ ((noinline))
span<pair> bar(arena::t& arena, i64 x, i64 y, size_t n) {
  return arena.make_span<pair>(n, x, y);
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: fae [path]\n");

    return 1;
  }

  arena::t arena;
  
  char const * filename = argv[1];
  char const * source = io::read(arena, filename);

  (void) source;

  auto p = foo(arena, -3, -4);
  auto q = bar(arena, -13, -14, 3);

  (void) p;
  (void) q;

  printf("Hello, world!\n");
  p->print();
  for (pair x : q) x.print();

  return 0;
}
