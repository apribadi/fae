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

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: fae [path]\n");

    return 1;
  }

  arena::t arena;
  span<char> source = io::read(arena, argv[1]);
  lexer::t lexer(source);

  for (;;) {
    token::t token = lexer.next();
    token::print(token);

    if (token.tag == token::tag::STOP) break;
  }

  return 0;
}
