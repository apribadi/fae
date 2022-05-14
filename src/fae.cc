#include <array>
#include <bit>
#include <cassert>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <span>
#include <stdexcept>
#include <string_view>
#include <vector>

#include "prelude.cc"
#include "arena.cc"
#include "io.cc"
#include "name.cc"
#include "token.cc"
#include "lexer.cc"
#include "syn.cc"
#include "parser.cc"

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: fae [path]\n");

    return 1;
  }

  arena::t arena;
  span<char> source = io::read(arena, argv[1]);
  Lexer lexer(source);

  for (;;) {
    Token tok = lexer.next();
    token::print(tok);

    if (tok.tag == token::Tag::STOP) break;
  }

  return 0;
}
