namespace lexer {
  // TODO: lex comments
  // TODO: lex string literals

  namespace kind {
    enum t : u8 {
      DIGIT,
      DOT,
      HASH,
      ILLEGAL,
      LBRACKET,
      LETTER,
      LINEBREAK,
      LPAREN,
      OPERATOR,
      PUNCTUATION,
      QUOTE,
      SPACE,
      STOP,
      UNDERSCORE,
    };

    constexpr size_t COUNT = 14;

    char const * to_string(t t) {
      switch (t) {
        case DIGIT: return "DIGIT";
        case DOT: return "DOT";
        case ILLEGAL: return "ILLEGAL";
        case LBRACKET: return "LBRACKET";
        case LETTER: return "LETTER";
        case LINEBREAK: return "LINEBREAK";
        case LPAREN: return "LPAREN";
        case OPERATOR: return "OPERATOR";
        case PUNCTUATION: return "PUNCTUATION";
        case QUOTE: return "QUOTE";
        case SPACE: return "SPACE";
        case STOP: return "STOP";
        case UNDERSCORE: return "UNDERSCORE";
      }

      return "???";
    }

    constexpr array<t, 256> table = {
      STOP,
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
      LPAREN,      // (
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
      LBRACKET,    // [
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

  namespace state {
    enum t {
      START,
      COMMENT,
      IDENTIFIER,
      NUMBER,
      OPERATOR,
      STRING,
      COMPLETE_IDENTIFIER,
      COMPLETE_IDENTIFIER_LBRACKET,
      COMPLETE_IDENTIFIER_LPAREN,
      COMPLETE_ILLEGAL_CHARACTER,
      COMPLETE_NUMBER,
      COMPLETE_OPERATOR,
      COMPLETE_PUNCTUATION,
      COMPLETE_STRING,
      COMPLETE_STRING_UNCLOSED,
      STOP,
    };

    constexpr size_t NONTERMINAL_COUNT = 6;
    constexpr size_t COUNT = 16;

    char const * to_string(t t) {
      switch (t) {
        case START: return "START";
        case COMMENT: return "COMMENT";
        case IDENTIFIER: return "IDENTIFIER";
        case NUMBER: return "NUMBER";
        case OPERATOR: return "OPERATOR";
        case COMPLETE_IDENTIFIER: return "COMPLETE_IDENTIFIER";
        case COMPLETE_ILLEGAL_CHARACTER: return "COMPLETE_ILLEGAL_CHARACTER";
        case COMPLETE_NUMBER: return "COMPLETE_NUMBER";
        case COMPLETE_OPERATOR: return "COMPLETE_OPERATOR";
        case COMPLETE_PUNCTUATION: return "COMPLETE_PUNCTUATION";
        case STOP: return "STOP";
      }

      return "???";
    }

    constexpr array<array<t, kind::COUNT>, NONTERMINAL_COUNT> transition = {
      // START ->
      (array<t, kind::COUNT>) {
        NUMBER,
        COMPLETE_PUNCTUATION,
        COMMENT,
        COMPLETE_ILLEGAL_CHARACTER,
        COMPLETE_PUNCTUATION,
        IDENTIFIER,
        START,
        COMPLETE_PUNCTUATION,
        OPERATOR,
        COMPLETE_PUNCTUATION,
        STRING,
        START,
        STOP,
        IDENTIFIER,
      },

      // COMMENT
      {
        COMMENT,
        COMMENT,
        COMMENT,
        COMMENT,
        COMMENT,
        COMMENT,
        START,
        COMMENT,
        COMMENT,
        COMMENT,
        COMMENT,
        COMMENT,
        STOP,
        COMMENT,
      },

      // IDENTIFIER
      {
        IDENTIFIER,
        COMPLETE_IDENTIFIER,
        COMPLETE_IDENTIFIER,
        COMPLETE_IDENTIFIER,
        COMPLETE_IDENTIFIER_LBRACKET,
        IDENTIFIER,
        COMPLETE_IDENTIFIER,
        COMPLETE_IDENTIFIER_LPAREN,
        COMPLETE_IDENTIFIER,
        COMPLETE_IDENTIFIER,
        COMPLETE_IDENTIFIER,
        COMPLETE_IDENTIFIER,
        COMPLETE_IDENTIFIER,
        IDENTIFIER,
      },

      // NUMBER
      {
        NUMBER,
        NUMBER,
        COMPLETE_NUMBER,
        COMPLETE_NUMBER,
        COMPLETE_NUMBER,
        COMPLETE_NUMBER,
        COMPLETE_NUMBER,
        COMPLETE_NUMBER,
        COMPLETE_NUMBER,
        COMPLETE_NUMBER,
        COMPLETE_NUMBER,
        COMPLETE_NUMBER,
        COMPLETE_NUMBER,
        COMPLETE_NUMBER,
      },

      // OPERATOR
      {
        COMPLETE_OPERATOR,
        COMPLETE_OPERATOR,
        COMPLETE_OPERATOR,
        COMPLETE_OPERATOR,
        COMPLETE_OPERATOR,
        COMPLETE_OPERATOR,
        COMPLETE_OPERATOR,
        COMPLETE_OPERATOR,
        OPERATOR,
        COMPLETE_OPERATOR,
        COMPLETE_OPERATOR,
        COMPLETE_OPERATOR,
        COMPLETE_OPERATOR,
        COMPLETE_OPERATOR,
      },

      // STRING
      {
        STRING,
        STRING,
        STRING,
        STRING,
        STRING,
        STRING,
        STRING,
        STRING,
        STRING,
        STRING,
        COMPLETE_STRING,
        STRING,
        COMPLETE_STRING_UNCLOSED,
        STRING,
      },

    };
  }

  namespace table {
    class t {
    public:
      array<kind::t, 256> kind;
      array<array<state::t, kind::COUNT>, state::NONTERMINAL_COUNT> transition;
      array<token::t(*)(t const &, char const *, char const *, char const *, state::t), state::COUNT> jump;
    };
  }

  __attribute__ ((always_inline))
  token::t next__dispatch(table::t const & table, char const * a, char const * b, char const * c, state::t s) {
    s = table.transition[s][table.kind[static_cast<unsigned char>(* b)]];
    [[clang::musttail]] return table.jump[s](table, a, b, c, s);
  }

  token::t next__restart(table::t const & table, char const *, char const * b, char const * c, state::t s) {
    [[clang::musttail]] return next__dispatch(table, b + 1, b + 1, c, s);
  }

  token::t next__continue(table::t const & table, char const * a, char const * b, char const * c, state::t s) {
    [[clang::musttail]] return next__dispatch(table, a, b + 1, c, s);
  }

  token::t next__complete_identifier(table::t const &, char const * a, char const * b, char const *, state::t s) {
    switch (b - a) {
    case 2:
      if (!bcmp(a, "if", 2)) return token::make(token::tag::IF, a, b);
      if (!bcmp(a, "or", 2)) return token::make(token::tag::OR, a, b);
      break;
    case 3:
      if (!bcmp(a, "and", 3)) return token::make(token::tag::AND, a, b);
      if (!bcmp(a, "end", 3)) return token::make(token::tag::END, a, b);
      if (!bcmp(a, "for", 3)) return token::make(token::tag::FOR, a, b);
      if (!bcmp(a, "fun", 3)) return token::make(token::tag::FUN, a, b);
      if (!bcmp(a, "let", 3)) return token::make(token::tag::LET, a, b);
      break;
    case 4:
      if (!bcmp(a, "else", 4)) return token::make(token::tag::ELSE, a, b);
      if (!bcmp(a, "elif", 4)) return token::make(token::tag::ELIF, a, b);
      if (!bcmp(a, "loop", 4)) return token::make(token::tag::LOOP, a, b);
      break;
    case 5:
      if (!bcmp(a, "break", 5)) return token::make(token::tag::BREAK, a, b);
      if (!bcmp(a, "while", 5)) return token::make(token::tag::WHILE, a, b);
      break;
    }

    if (s == state::COMPLETE_IDENTIFIER_LBRACKET)
      return token::make(token::tag::IDENTIFIER_LBRACKET, a, b + 1);

    if (s == state::COMPLETE_IDENTIFIER_LPAREN)
      return token::make(token::tag::IDENTIFIER_LPAREN, a, b + 1);

    return token::make(token::tag::IDENTIFIER, a, b);
  }

  token::t next__complete_illegal_character(table::t const &, char const * a, char const * b, char const *, state::t) {
    return token::make(token::tag::ILLEGAL, a, b + 1);
  }

  token::t next__complete_number(table::t const &, char const * a, char const * b, char const *, state::t) {
    return token::make(token::tag::NUMBER, a, b);
  }

  token::t next__complete_operator(table::t const &, char const * a, char const * b, char const *, state::t) {
    if (b - a == 1) {
      switch (* a) {
        case '=': return token::make(token::tag::ASSIGN, a, b);
        case '<': return token::make(token::tag::LT, a, b);
        case '>': return token::make(token::tag::GT, a, b);
        case '+': return token::make(token::tag::PLUS, a, b);
        case '-': return token::make(token::tag::MINUS, a, b);
        case '*': return token::make(token::tag::STAR, a, b);
        case '/': return token::make(token::tag::SLASH, a, b);
        case '&': return token::make(token::tag::AMPERSAND, a, b);
        case '@': return token::make(token::tag::AT, a, b);
        case '!': return token::make(token::tag::BANG, a, b);
        case '^': return token::make(token::tag::CARET, a, b);
        case '$': return token::make(token::tag::DOLLAR, a, b);
        case '%': return token::make(token::tag::PERCENT, a, b);
        case '|': return token::make(token::tag::PIPE, a, b);
        case '?': return token::make(token::tag::QUERY, a, b);
        case '~': return token::make(token::tag::TILDE, a, b);
      }
    }
    else if (b - a == 2) {
      if (!bcmp(a, "==", 2)) return token::make(token::tag::EQ, a, b);
      if (!bcmp(a, "!=", 2)) return token::make(token::tag::NE, a, b);
      if (!bcmp(a, "<=", 2)) return token::make(token::tag::LE, a, b);
      if (!bcmp(a, ">=", 2)) return token::make(token::tag::GE, a, b);
    }

    return token::make(token::tag::ILLEGAL, a, b);
  }

  token::t next__complete_string(table::t const &, char const * a, char const * b, char const *, state::t s) {
    if (s == state::COMPLETE_STRING_UNCLOSED)
      return token::make(token::tag::ILLEGAL, a, b);

    return token::make(token::tag::STRING, a, b + 1);
  }

  token::t next__complete_punctuation(table::t const &, char const * a, char const * b, char const *, state::t) {
    switch (* a) {
      case ':': return token::make(token::tag::COLON, a, b + 1);
      case ',': return token::make(token::tag::COMMA, a, b + 1);
      case '.': return token::make(token::tag::DOT, a, b + 1);
      case ';': return token::make(token::tag::SEMICOLON, a, b + 1);
      case '(': return token::make(token::tag::LPAREN, a, b + 1);
      case '[': return token::make(token::tag::LBRACKET, a, b + 1);
      case '{': return token::make(token::tag::LBRACE, a, b + 1);
      case ')': return token::make(token::tag::RPAREN, a, b + 1);
      case ']': return token::make(token::tag::RBRACKET, a, b + 1);
      case '}': return token::make(token::tag::RBRACE, a, b + 1);
    }

    return token::make(token::tag::ILLEGAL, a, b + 1);
  }

  token::t next__stop(table::t const &, char const *, char const * b, char const * c, state::t) {
    if (b != c)
      return token::make(token::tag::ILLEGAL, b, b + 1);
    else
      return token::make(token::tag::STOP, b, b);
  }

  constexpr table::t global_table = {
    kind::table,
    state::transition,
    {
      next__restart,
      next__continue,
      next__continue,
      next__continue,
      next__continue,
      next__continue,
      next__complete_identifier,
      next__complete_identifier,
      next__complete_identifier,
      next__complete_illegal_character,
      next__complete_number,
      next__complete_operator,
      next__complete_punctuation,
      next__complete_string,
      next__complete_string,
      next__stop,
    }
  };

  class t {
  private:
    char const * start;
    char const * stop;
    char const * current;

  public:
    t(span<char> source) {
      size_t n = source.size();

      assert(n > 0);
      assert(source[n - 1] == '\0');

      start = &source[0];
      stop = &source[n - 1];
      current = start;
    }

    token::t next() {
      token::t token = next__dispatch(global_table, current, current, stop, state::START);
      current = token.stop;
      return token;
    }
  };
}
