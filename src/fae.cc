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
#include <type_traits>
#include <vector>

#include "prelude.cc"
#include "arena.cc"
#include "io.cc"
#include "name.cc"
#include "token.cc"
#include "lexer.cc"
#include "ast.cc"
#include "parser.cc"

using Arena = fae::arena::Arena;
using Lexer = fae::lexer::Lexer;
using Token = fae::token::Token;

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: fae [path]\n");

    return 1;
  }

  Arena arena;
  span<char> source = fae::io::read(arena, argv[1]);
  Lexer lexer(source);

  for (;;) {
    Token tok = lexer.next();
    Token::print(tok);

    if (tok.tag == Token::Tag::STOP) break;
  }

  return 0;
}
