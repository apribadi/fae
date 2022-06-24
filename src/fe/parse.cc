namespace fae::fe::parse {

using Arena = fae::mm::Arena;
using Token = fae::ir::Token;

class Parser {
public:
  explicit Parser(Arena &, span<char>);

// private:
  Arena * arena;
  Token token;
  char * start;
  char * stop;
  char * cursor;
};

Parser::Parser(Arena & arena, span<char> source) :
  arena(& arena),
  token(Token(Token::Tag::ILLEGAL, nullptr, nullptr))
{
  size_t n = source.size();

  assert(n >= 1);
  assert(source[n - 1] == '\0');

  start = &source[0];
  stop = &source[n - 1];
  token = fae::fe::lex::next(start, stop);
  cursor = token.stop;
}

}
