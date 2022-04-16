#include <array>
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
span<pair> bar(arena::t& arena, i64 n, i64 x, i64 y) {
  return arena.make_span<pair>(n, x, y);
}

int main(int argc, char ** argv) {
  (void) argc;
  (void) argv;

  if (argc != 2) {
    fprintf(stderr, "Usage: fae [path]\n");

    return 1;
  }
  
  char const * filename = argv[1];
  char const * source = io::read(filename);

  (void) source;

  arena::t arena;

  auto p = foo(arena, -3, -4);
  auto q = bar(arena, 3, -13, -14);

  // array<i64, n> * q = arena.make<array<i64, n>>();

  (void) p;
  (void) q;

  // auto q = arena.make<arena::t>();
  // (void) q;

  printf("Hello, world!\n");
  p->print();
  for (pair x : q) x.print();

  return 0;
}
