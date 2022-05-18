namespace fae::lexer {

using Token = token::Token;

class Lexer {
public:
  explicit Lexer(span<char>);
  Token next();

private:
  char const * start;
  char const * stop;
  char const * current;
};

namespace internal {
  enum class Kind : u8 {
    DIGIT,
    DOT,
    HASH,
    ILLEGAL,
    LETTER,
    LINEBREAK,
    NIL,
    OPERATOR,
    PUNCTUATION,
    QUOTE,
    SPACE,
    UNDERSCORE,
  };

  namespace kind {
    using enum Kind;

    constexpr size_t NUM_VALUES = 12;

    constexpr array<Kind, 256> TABLE = {
      NIL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      LINEBREAK,   // line feed
      ILLEGAL,
      ILLEGAL,
      LINEBREAK,   // carriage return
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      SPACE,       // ' '
      OPERATOR,    // !
      QUOTE,       // "
      HASH,        // #
      OPERATOR,    // $
      OPERATOR,    // %
      OPERATOR,    // &
      ILLEGAL,     // '
      PUNCTUATION, // (
      PUNCTUATION, // )
      OPERATOR,    // *
      OPERATOR,    // +
      PUNCTUATION, // ,
      OPERATOR,    // -
      DOT,         // .
      OPERATOR,    // /
      DIGIT,       // 0
      DIGIT,       // 1
      DIGIT,       // 2
      DIGIT,       // 3
      DIGIT,       // 4
      DIGIT,       // 5
      DIGIT,       // 6
      DIGIT,       // 7
      DIGIT,       // 8
      DIGIT,       // 9
      PUNCTUATION, // :
      PUNCTUATION, // ;
      OPERATOR,    // <
      OPERATOR,    // =
      OPERATOR,    // >
      OPERATOR,    // ?
      OPERATOR,    // @
      LETTER,      // A
      LETTER,      // B
      LETTER,      // C
      LETTER,      // D
      LETTER,      // E
      LETTER,      // F
      LETTER,      // G
      LETTER,      // H
      LETTER,      // I
      LETTER,      // J
      LETTER,      // K
      LETTER,      // L
      LETTER,      // M
      LETTER,      // N
      LETTER,      // O
      LETTER,      // P
      LETTER,      // Q
      LETTER,      // R
      LETTER,      // S
      LETTER,      // T
      LETTER,      // U
      LETTER,      // V
      LETTER,      // W
      LETTER,      // X
      LETTER,      // Y
      LETTER,      // Z
      PUNCTUATION, // [
      ILLEGAL,     // backslash
      PUNCTUATION, // ]
      OPERATOR,    // ^
      UNDERSCORE,  // _
      ILLEGAL,     // `
      LETTER,      // a
      LETTER,      // b
      LETTER,      // c
      LETTER,      // d
      LETTER,      // e
      LETTER,      // f
      LETTER,      // g
      LETTER,      // h
      LETTER,      // i
      LETTER,      // j
      LETTER,      // k
      LETTER,      // l
      LETTER,      // m
      LETTER,      // n
      LETTER,      // o
      LETTER,      // p
      LETTER,      // q
      LETTER,      // r
      LETTER,      // s
      LETTER,      // t
      LETTER,      // u
      LETTER,      // v
      LETTER,      // w
      LETTER,      // x
      LETTER,      // y
      LETTER,      // z
      PUNCTUATION, // {
      OPERATOR,    // |
      PUNCTUATION, // }
      OPERATOR,    // ~
      ILLEGAL,     // 127
      ILLEGAL,     // 128
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,    // 255
    };
  }

  enum class State {
    RESTART,
    START,
    COMMENT,
    DOT,
    IDENTIFIER,
    NUMBER,
    OPERATOR,
    STRING,
    STOP_DOT,
    STOP_IDENTIFIER,
    STOP_ILLEGAL_CHARACTER,
    STOP_ILLEGAL_TOKEN,
    STOP_NIL,
    STOP_NUMBER,
    STOP_OPERATOR,
    STOP_PUNCTUATION,
    STOP_PUNCTUATION_NOSPACE,
    STOP_STRING,
  };

  namespace state {
    using enum State;

    constexpr size_t NUM_VALUES_NONTERMINAL = 8;
    constexpr size_t NUM_VALUES_TERMINAL = 10;
    constexpr size_t NUM_VALUES = NUM_VALUES_NONTERMINAL + NUM_VALUES_TERMINAL;

    constexpr array<State, kind::NUM_VALUES> TABLE_RESTART = {
      NUMBER,
      DOT,
      COMMENT,
      STOP_ILLEGAL_CHARACTER,
      IDENTIFIER,
      RESTART,
      STOP_NIL,
      OPERATOR,
      STOP_PUNCTUATION,
      STRING,
      RESTART,
      IDENTIFIER,
    };

    constexpr array<State, kind::NUM_VALUES> TABLE_START = {
      NUMBER,
      DOT,
      COMMENT,
      STOP_ILLEGAL_CHARACTER,
      IDENTIFIER,
      RESTART,
      STOP_NIL,
      OPERATOR,
      STOP_PUNCTUATION_NOSPACE,
      STRING,
      RESTART,
      IDENTIFIER,
    };

    constexpr array<State, kind::NUM_VALUES> TABLE_COMMENT = {
      COMMENT,
      COMMENT,
      COMMENT,
      COMMENT,
      COMMENT,
      RESTART,
      STOP_NIL,
      COMMENT,
      COMMENT,
      COMMENT,
      COMMENT,
      COMMENT,
    };

    constexpr array<State, kind::NUM_VALUES> TABLE_DOT = {
      STOP_DOT,
      DOT,
      STOP_DOT,
      STOP_DOT,
      STOP_DOT,
      STOP_DOT,
      STOP_DOT,
      STOP_DOT,
      STOP_DOT,
      STOP_DOT,
      STOP_DOT,
      STOP_DOT,
    };

    constexpr array<State, kind::NUM_VALUES> TABLE_IDENTIFIER = {
      IDENTIFIER,
      STOP_IDENTIFIER,
      STOP_IDENTIFIER,
      STOP_IDENTIFIER,
      IDENTIFIER,
      STOP_IDENTIFIER,
      STOP_IDENTIFIER,
      STOP_IDENTIFIER,
      STOP_IDENTIFIER,
      STOP_IDENTIFIER,
      STOP_IDENTIFIER,
      IDENTIFIER,
    };

    constexpr array<State, kind::NUM_VALUES> TABLE_NUMBER = {
      NUMBER,
      NUMBER,
      STOP_NUMBER,
      STOP_NUMBER,
      STOP_NUMBER,
      STOP_NUMBER,
      STOP_NUMBER,
      STOP_NUMBER,
      STOP_NUMBER,
      STOP_NUMBER,
      STOP_NUMBER,
      STOP_NUMBER,
    };

    constexpr array<State, kind::NUM_VALUES> TABLE_OPERATOR = {
      STOP_OPERATOR,
      STOP_OPERATOR,
      STOP_OPERATOR,
      STOP_OPERATOR,
      STOP_OPERATOR,
      STOP_OPERATOR,
      STOP_OPERATOR,
      OPERATOR,
      STOP_OPERATOR,
      STOP_OPERATOR,
      STOP_OPERATOR,
      STOP_OPERATOR,
    };

    constexpr array<State, kind::NUM_VALUES> TABLE_STRING = {
      STRING,
      STRING,
      STRING,
      STRING,
      STRING,
      STRING,
      STOP_ILLEGAL_TOKEN,
      STRING,
      STRING,
      STOP_STRING,
      STRING,
      STRING,
    };

    constexpr array<array<State, kind::NUM_VALUES>, NUM_VALUES_NONTERMINAL> TABLE = {
      TABLE_RESTART,
      TABLE_START,
      TABLE_COMMENT,
      TABLE_DOT,
      TABLE_IDENTIFIER,
      TABLE_NUMBER,
      TABLE_OPERATOR,
      TABLE_STRING,
    };
  }

  struct Table {
    array<Kind, 256> classify;
    array<array<State, kind::NUM_VALUES>, state::NUM_VALUES_NONTERMINAL> transition;
    array<Token(*)(Table const &, char const *, char const *, char const *, State), state::NUM_VALUES> jump;
  };

  Token next__start(Table const & table, char const * a, char const * b) {
    State s = table.transition[(u8) State::START][(u8) table.classify[(u8) (* a)]];
    return table.jump[(u8) s](table, a, a, b, s);
  }

  Token next__continue(Table const & table, char const * a, char const * b, char const * c, State s) {
    a = s == State::RESTART ? b + 1 : a;
    b = b + 1;
    s = table.transition[(u8) s][(u8) table.classify[(u8) (* b)]];
    [[clang::musttail]] return table.jump[(u8) s](table, a, b, c, s);
  }

  Token next__stop_dot(Table const &, char const * a, char const * b, char const *, State) {
    if (b - a == 1)
      return Token::make(Token::Tag::DOT, a, b);

    return Token::make(Token::Tag::ILLEGAL, a, b);
  }

  Token next__stop_identifier(Table const &, char const * a, char const * b, char const *, State) {
    switch (b - a) {
    case 2:
      if (!bcmp(a, "if", 2)) return Token::make(Token::Tag::IF, a, b);
      if (!bcmp(a, "or", 2)) return Token::make(Token::Tag::OR, a, b);
      break;
    case 3:
      if (!bcmp(a, "and", 3)) return Token::make(Token::Tag::AND, a, b);
      if (!bcmp(a, "end", 3)) return Token::make(Token::Tag::END, a, b);
      if (!bcmp(a, "for", 3)) return Token::make(Token::Tag::FOR, a, b);
      if (!bcmp(a, "fun", 3)) return Token::make(Token::Tag::FUN, a, b);
      if (!bcmp(a, "let", 3)) return Token::make(Token::Tag::LET, a, b);
      break;
    case 4:
      if (!bcmp(a, "else", 4)) return Token::make(Token::Tag::ELSE, a, b);
      if (!bcmp(a, "elif", 4)) return Token::make(Token::Tag::ELIF, a, b);
      if (!bcmp(a, "loop", 4)) return Token::make(Token::Tag::LOOP, a, b);
      break;
    case 5:
      if (!bcmp(a, "break", 5)) return Token::make(Token::Tag::BREAK, a, b);
      if (!bcmp(a, "while", 5)) return Token::make(Token::Tag::WHILE, a, b);
      break;
    case 6:
      if (!bcmp(a, "return", 5)) return Token::make(Token::Tag::RETURN, a, b);
      break;
    }

    return Token::make(Token::Tag::IDENTIFIER, a, b);
  }

  Token next__stop_illegal_character(Table const &, char const * a, char const * b, char const *, State) {
    return Token::make(Token::Tag::ILLEGAL, a, b + 1);
  }

  Token next__stop_illegal_token(Table const &, char const * a, char const * b, char const *, State) {
    return Token::make(Token::Tag::ILLEGAL, a, b);
  }

  Token next__stop_nil(Table const &, char const *, char const * b, char const * c, State) {
    if (b != c)
      return Token::make(Token::Tag::ILLEGAL, b, b + 1);

    return Token::make(Token::Tag::STOP, b, b);
  }

  Token next__stop_number(Table const &, char const * a, char const * b, char const *, State) {
    return Token::make(Token::Tag::NUMBER, a, b);
  }

  Token next__stop_operator(Table const &, char const * a, char const * b, char const *, State) {
    if (b - a == 1) {
      switch (* a) {
        case '=': return Token::make(Token::Tag::ASSIGN, a, b);
        case '<': return Token::make(Token::Tag::LT, a, b);
        case '>': return Token::make(Token::Tag::GT, a, b);
        case '+': return Token::make(Token::Tag::PLUS, a, b);
        case '-': return Token::make(Token::Tag::MINUS, a, b);
        case '*': return Token::make(Token::Tag::STAR, a, b);
        case '/': return Token::make(Token::Tag::SLASH, a, b);
        case '&': return Token::make(Token::Tag::AMPERSAND, a, b);
        case '@': return Token::make(Token::Tag::AT, a, b);
        case '!': return Token::make(Token::Tag::BANG, a, b);
        case '^': return Token::make(Token::Tag::CARET, a, b);
        case '$': return Token::make(Token::Tag::DOLLAR, a, b);
        case '%': return Token::make(Token::Tag::PERCENT, a, b);
        case '|': return Token::make(Token::Tag::PIPE, a, b);
        case '?': return Token::make(Token::Tag::QUERY, a, b);
        case '~': return Token::make(Token::Tag::TILDE, a, b);
      }
    }
    else if (b - a == 2) {
      if (!bcmp(a, "==", 2)) return Token::make(Token::Tag::EQ, a, b);
      if (!bcmp(a, "!=", 2)) return Token::make(Token::Tag::NE, a, b);
      if (!bcmp(a, "<=", 2)) return Token::make(Token::Tag::LE, a, b);
      if (!bcmp(a, ">=", 2)) return Token::make(Token::Tag::GE, a, b);
    }

    return Token::make(Token::Tag::ILLEGAL, a, b);
  }

  Token next__stop_string(Table const &, char const * a, char const * b, char const *, State) {
    return Token::make(Token::Tag::STRING, a, b + 1);
  }

  Token next__stop_punctuation(Table const &, char const * a, char const * b, char const *, State) {
    switch (* a) {
      case ':': return Token::make(Token::Tag::COLON, a, b + 1);
      case ',': return Token::make(Token::Tag::COMMA, a, b + 1);
      case ';': return Token::make(Token::Tag::SEMICOLON, a, b + 1);
      case '(': return Token::make(Token::Tag::LPAREN, a, b + 1);
      case '[': return Token::make(Token::Tag::LBRACKET, a, b + 1);
      case '{': return Token::make(Token::Tag::LBRACE, a, b + 1);
      case ')': return Token::make(Token::Tag::RPAREN, a, b + 1);
      case ']': return Token::make(Token::Tag::RBRACKET, a, b + 1);
      case '}': return Token::make(Token::Tag::RBRACE, a, b + 1);
    }

    return Token::make(Token::Tag::ILLEGAL, a, b + 1);
  }

  Token next__stop_punctuation_no_space(Table const &, char const * a, char const * b, char const *, State) {
    switch (* a) {
      case ':': return Token::make(Token::Tag::COLON, a, b + 1);
      case ',': return Token::make(Token::Tag::COMMA, a, b + 1);
      case ';': return Token::make(Token::Tag::SEMICOLON, a, b + 1);
      case '(': return Token::make(Token::Tag::LPAREN_NOSPACE, a, b + 1);
      case '[': return Token::make(Token::Tag::LBRACKET_NOSPACE, a, b + 1);
      case '{': return Token::make(Token::Tag::LBRACE, a, b + 1);
      case ')': return Token::make(Token::Tag::RPAREN, a, b + 1);
      case ']': return Token::make(Token::Tag::RBRACKET, a, b + 1);
      case '}': return Token::make(Token::Tag::RBRACE, a, b + 1);
    }

    return Token::make(Token::Tag::ILLEGAL, a, b + 1);
  }

  constexpr Table global_table = {
    kind::TABLE,
    state::TABLE,
    {
      next__continue,
      NULL,
      next__continue,
      next__continue,
      next__continue,
      next__continue,
      next__continue,
      next__continue,
      next__stop_dot,
      next__stop_identifier,
      next__stop_illegal_character,
      next__stop_illegal_token,
      next__stop_nil,
      next__stop_number,
      next__stop_operator,
      next__stop_punctuation,
      next__stop_punctuation_no_space,
      next__stop_string,
    }
  };
}

Lexer::Lexer(span<char> source) {
  size_t n = source.size();

  assert(n >= 1);
  assert(source[n - 1] == '\0');

  start = &source[0];
  stop = &source[n - 1];
  current = start;
}

Token Lexer::next() {
  Token token = internal::next__start(internal::global_table, current, stop);
  current = token.stop;
  return token;
}

}
