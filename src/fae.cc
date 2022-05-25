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
#include "data.token.cc"
#include "data.name.cc"
#include "data.ast.cc"
#include "io.cc"
#include "lex.cc"
#include "parse.cc"

using Arena = fae::arena::Arena;
using Token = fae::data::token::Token;

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: fae [path]\n");

    return 1;
  }

  Arena arena;
  span<char> source = fae::io::read(arena, argv[1]);

  size_t n = source.size();
  assert(n >= 1);
  assert(source[n - 1] == '\0');

  char const * start = &source[0];
  char const * stop = &source[n - 1];

  for (;;) {
    Token tok = fae::lex::next(start, stop);
    start = tok.stop;
    tok.print();

    if (tok.tag == Token::Tag::STOP) break;
  }

  return 0;
}
