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

using i32 = int32_t;
using i64 = int64_t;
using u8 = uint8_t;
using u32 = uint32_t;
using u64 = uint64_t;

using std::align_val_t;
using std::array;
using std::byte;
using std::forward;
using std::is_trivially_default_constructible;
using std::is_trivially_destructible;
using std::move;
using std::popcount;
using std::rotl;
using std::rotr;
using std::runtime_error;
using std::span;
using std::string_view;
using std::to_array;
using std::vector;

#include "mm/arena.cc"
#include "io/file.cc"
#include "ir/token.cc"
#include "ir/name.cc"
#include "ir/ast.cc"
#include "fe/lex.cc"
#include "fe/parse.cc"

using Arena = fae::mm::Arena;
using Token = fae::ir::Token;

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: fae [path]\n");

    return 1;
  }

  Arena arena;
  span<char> source = fae::io::file::read(arena, argv[1]);

  size_t n = source.size();
  assert(n >= 1);
  assert(source[n - 1] == '\0');

  char const * start = &source[0];
  char const * stop = &source[n - 1];

  for (;;) {
    Token tok = fae::fe::lex::next(start, stop);
    start = tok.stop;
    fae::ir::token::print(tok);

    if (tok.tag == Token::Tag::STOP) break;
  }

  return 0;
}
