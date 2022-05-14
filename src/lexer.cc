namespace lexer {
  enum class CharClass : u8 {
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
}

namespace lexer::char_class {
  using enum lexer::CharClass;

  constexpr size_t NUM_VALUES = 12;

  constexpr array<CharClass, 256> TABLE = {
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

namespace lexer {
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
}

namespace lexer::state {
  using enum lexer::State;

  constexpr size_t NUM_VALUES_NONTERMINAL = 8;
  constexpr size_t NUM_VALUES_TERMINAL = 10;
  constexpr size_t NUM_VALUES = NUM_VALUES_NONTERMINAL + NUM_VALUES_TERMINAL;

  constexpr array<State, lexer::char_class::NUM_VALUES> TABLE_RESTART = {
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

  constexpr array<State, lexer::char_class::NUM_VALUES> TABLE_START = {
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

  constexpr array<State, lexer::char_class::NUM_VALUES> TABLE_COMMENT = {
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

  constexpr array<State, lexer::char_class::NUM_VALUES> TABLE_DOT = {
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

  constexpr array<State, lexer::char_class::NUM_VALUES> TABLE_IDENTIFIER = {
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

  constexpr array<State, lexer::char_class::NUM_VALUES> TABLE_NUMBER = {
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

  constexpr array<State, lexer::char_class::NUM_VALUES> TABLE_OPERATOR = {
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

  constexpr array<State, lexer::char_class::NUM_VALUES> TABLE_STRING = {
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

  constexpr array<array<State, lexer::char_class::NUM_VALUES>, NUM_VALUES_NONTERMINAL> TABLE = {
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

namespace lexer {
  struct Table {
    array<CharClass, 256> classify;
    array<array<State, lexer::char_class::NUM_VALUES>, lexer::state::NUM_VALUES_NONTERMINAL> transition;
    array<Token(*)(Table const &, char const *, char const *, char const *, State), lexer::state::NUM_VALUES> jump;
  };

  Token Next__Start(Table const & table, char const * a, char const * b) {
    State s = table.transition[(u8) State::START][(u8) table.classify[(u8) (* a)]];
    return table.jump[(u8) s](table, a, a, b, s);
  }

  Token Next__Continue(Table const & table, char const * a, char const * b, char const * c, State s) {
    a = s == State::RESTART ? b + 1 : a;
    b = b + 1;
    s = table.transition[(u8) s][(u8) table.classify[(u8) (* b)]];
    [[clang::musttail]] return table.jump[(u8) s](table, a, b, c, s);
  }

  Token Next__StopDot(Table const &, char const * a, char const * b, char const *, State) {
    if (b - a == 1)
      return token::Make(token::Tag::DOT, a, b);

    return token::Make(token::Tag::ILLEGAL, a, b);
  }

  Token Next__StopIdentifier(Table const &, char const * a, char const * b, char const *, State) {
    switch (b - a) {
    case 2:
      if (!bcmp(a, "if", 2)) return token::Make(token::Tag::IF, a, b);
      if (!bcmp(a, "or", 2)) return token::Make(token::Tag::OR, a, b);
      break;
    case 3:
      if (!bcmp(a, "and", 3)) return token::Make(token::Tag::AND, a, b);
      if (!bcmp(a, "end", 3)) return token::Make(token::Tag::END, a, b);
      if (!bcmp(a, "for", 3)) return token::Make(token::Tag::FOR, a, b);
      if (!bcmp(a, "fun", 3)) return token::Make(token::Tag::FUN, a, b);
      if (!bcmp(a, "let", 3)) return token::Make(token::Tag::LET, a, b);
      break;
    case 4:
      if (!bcmp(a, "else", 4)) return token::Make(token::Tag::ELSE, a, b);
      if (!bcmp(a, "elif", 4)) return token::Make(token::Tag::ELIF, a, b);
      if (!bcmp(a, "loop", 4)) return token::Make(token::Tag::LOOP, a, b);
      break;
    case 5:
      if (!bcmp(a, "break", 5)) return token::Make(token::Tag::BREAK, a, b);
      if (!bcmp(a, "while", 5)) return token::Make(token::Tag::WHILE, a, b);
      break;
    case 6:
      if (!bcmp(a, "return", 5)) return token::Make(token::Tag::RETURN, a, b);
      break;
    }

    return token::Make(token::Tag::IDENTIFIER, a, b);
  }

  Token Next__StopIllegalCharacter(Table const &, char const * a, char const * b, char const *, State) {
    return token::Make(token::Tag::ILLEGAL, a, b + 1);
  }

  Token Next__StopIllegalToken(Table const &, char const * a, char const * b, char const *, State) {
    return token::Make(token::Tag::ILLEGAL, a, b);
  }

  Token Next__StopNil(Table const &, char const *, char const * b, char const * c, State) {
    if (b != c)
      return token::Make(token::Tag::ILLEGAL, b, b + 1);

    return token::Make(token::Tag::STOP, b, b);
  }

  Token Next__StopNumber(Table const &, char const * a, char const * b, char const *, State) {
    return token::Make(token::Tag::NUMBER, a, b);
  }

  Token Next__StopOperator(Table const &, char const * a, char const * b, char const *, State) {
    if (b - a == 1) {
      switch (* a) {
        case '=': return token::Make(token::Tag::ASSIGN, a, b);
        case '<': return token::Make(token::Tag::LT, a, b);
        case '>': return token::Make(token::Tag::GT, a, b);
        case '+': return token::Make(token::Tag::PLUS, a, b);
        case '-': return token::Make(token::Tag::MINUS, a, b);
        case '*': return token::Make(token::Tag::STAR, a, b);
        case '/': return token::Make(token::Tag::SLASH, a, b);
        case '&': return token::Make(token::Tag::AMPERSAND, a, b);
        case '@': return token::Make(token::Tag::AT, a, b);
        case '!': return token::Make(token::Tag::BANG, a, b);
        case '^': return token::Make(token::Tag::CARET, a, b);
        case '$': return token::Make(token::Tag::DOLLAR, a, b);
        case '%': return token::Make(token::Tag::PERCENT, a, b);
        case '|': return token::Make(token::Tag::PIPE, a, b);
        case '?': return token::Make(token::Tag::QUERY, a, b);
        case '~': return token::Make(token::Tag::TILDE, a, b);
      }
    }
    else if (b - a == 2) {
      if (!bcmp(a, "==", 2)) return token::Make(token::Tag::EQ, a, b);
      if (!bcmp(a, "!=", 2)) return token::Make(token::Tag::NE, a, b);
      if (!bcmp(a, "<=", 2)) return token::Make(token::Tag::LE, a, b);
      if (!bcmp(a, ">=", 2)) return token::Make(token::Tag::GE, a, b);
    }

    return token::Make(token::Tag::ILLEGAL, a, b);
  }

  Token Next__StopString(Table const &, char const * a, char const * b, char const *, State) {
    return token::Make(token::Tag::STRING, a, b + 1);
  }

  Token Next__StopPunctuation(Table const &, char const * a, char const * b, char const *, State) {
    switch (* a) {
      case ':': return token::Make(token::Tag::COLON, a, b + 1);
      case ',': return token::Make(token::Tag::COMMA, a, b + 1);
      case ';': return token::Make(token::Tag::SEMICOLON, a, b + 1);
      case '(': return token::Make(token::Tag::LPAREN, a, b + 1);
      case '[': return token::Make(token::Tag::LBRACKET, a, b + 1);
      case '{': return token::Make(token::Tag::LBRACE, a, b + 1);
      case ')': return token::Make(token::Tag::RPAREN, a, b + 1);
      case ']': return token::Make(token::Tag::RBRACKET, a, b + 1);
      case '}': return token::Make(token::Tag::RBRACE, a, b + 1);
    }

    return token::Make(token::Tag::ILLEGAL, a, b + 1);
  }

  Token Next__StopPunctuationNoSpace(Table const &, char const * a, char const * b, char const *, State) {
    switch (* a) {
      case ':': return token::Make(token::Tag::COLON, a, b + 1);
      case ',': return token::Make(token::Tag::COMMA, a, b + 1);
      case ';': return token::Make(token::Tag::SEMICOLON, a, b + 1);
      case '(': return token::Make(token::Tag::LPAREN_NOSPACE, a, b + 1);
      case '[': return token::Make(token::Tag::LBRACKET_NOSPACE, a, b + 1);
      case '{': return token::Make(token::Tag::LBRACE, a, b + 1);
      case ')': return token::Make(token::Tag::RPAREN, a, b + 1);
      case ']': return token::Make(token::Tag::RBRACKET, a, b + 1);
      case '}': return token::Make(token::Tag::RBRACE, a, b + 1);
    }

    return token::Make(token::Tag::ILLEGAL, a, b + 1);
  }
}

namespace lexer::table {
  constexpr lexer::Table global = {
    lexer::char_class::TABLE,
    lexer::state::TABLE,
    {
      Next__Continue,
      NULL,
      Next__Continue,
      Next__Continue,
      Next__Continue,
      Next__Continue,
      Next__Continue,
      Next__Continue,
      Next__StopDot,
      Next__StopIdentifier,
      Next__StopIllegalCharacter,
      Next__StopIllegalToken,
      Next__StopNil,
      Next__StopNumber,
      Next__StopOperator,
      Next__StopPunctuation,
      Next__StopPunctuationNoSpace,
      Next__StopString,
    }
  };
}

class Lexer {
private:
  char const * start;
  char const * stop;
  char const * current;

public:
  Lexer(span<char> source) {
    size_t n = source.size();

    assert(n >= 1);
    assert(source[n - 1] == '\0');

    start = &source[0];
    stop = &source[n - 1];
    current = start;
  }

  Token Next() {
    Token token = lexer::Next__Start(lexer::table::global, current, stop);
    current = token.stop;
    return token;
  }
};
