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

__attribute__ ((noinline))
i64 * foo(arena::t& arena) {
  return arena.make<i64>(13);
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

  i64 * p = foo(arena);

  (void) p;

  // auto q = arena.make<arena::t>();
  // (void) q;

  printf("Hello, world!\n");
  printf("value: %d\n", (int) * p);

  return 0;
}
