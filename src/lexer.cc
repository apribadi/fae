namespace lexer {
  // TODO: lex comments
  // TODO: lex string literals

  namespace kind {
    enum t : u8 {
      DIGIT,
      DOT,
      ILLEGAL,
      LETTER,
      OPERATOR,
      PUNCTUATION,
      QUOTE,
      SPACE,
      STOP,
    };

    constexpr size_t COUNT = 9;

    char const * to_string(t t) {
      switch (t) {
        case DIGIT: return "DIGIT";
        case DOT: return "DOT";
        case ILLEGAL: return "ILLEGAL";
        case LETTER: return "LETTER";
        case OPERATOR: return "OPERATOR";
        case PUNCTUATION: return "PUNCTUATION";
        case QUOTE: return "QUOTE";
        case SPACE: return "SPACE";
        case STOP: return "STOP";
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
      SPACE,       // line feed
      ILLEGAL,
      ILLEGAL,
      SPACE,       // carriage return
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
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
      ILLEGAL,     // !
      QUOTE,       // "
      OPERATOR,    // #
      ILLEGAL,     // $
      ILLEGAL,     // %
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
      OPERATOR,    // :
      PUNCTUATION, // ;
      OPERATOR,    // <
      OPERATOR,    // =
      OPERATOR,    // >
      ILLEGAL,     // ?
      ILLEGAL,     // @
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
      ILLEGAL,     // 
      PUNCTUATION, // ]
      ILLEGAL,     // ^
      ILLEGAL,     // _
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
      DOT,
      IDENTIFIER,
      ILLEGAL,
      NUMBER,
      OPERATOR,
      COMPLETE_IDENTIFIER,
      COMPLETE_ILLEGAL,
      COMPLETE_NUMBER,
      COMPLETE_OPERATOR,
      COMPLETE_PUNCTUATION,
      STOP,
    };

    constexpr size_t NONTERMINAL_COUNT = 6;
    constexpr size_t COUNT = 12;

    char const * to_string(t t) {
      switch (t) {
        case START: return "START";
        case DOT: return "DOT";
        case IDENTIFIER: return "IDENTIFIER";
        case ILLEGAL: return "ILLEGAL";
        case NUMBER: return "NUMBER";
        case OPERATOR: return "OPERATOR";
        case COMPLETE_IDENTIFIER: return "COMPLETE_IDENTIFIER";
        case COMPLETE_ILLEGAL: return "COMPLETE_ILLEGAL";
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
        DOT,
        ILLEGAL,
        IDENTIFIER,
        OPERATOR,
        COMPLETE_PUNCTUATION,
        ILLEGAL,
        START,
        STOP,
      },

      // DOT
      {
        COMPLETE_OPERATOR,
        DOT,
        COMPLETE_OPERATOR,
        COMPLETE_OPERATOR,
        COMPLETE_OPERATOR,
        COMPLETE_OPERATOR,
        COMPLETE_OPERATOR,
        COMPLETE_OPERATOR,
        COMPLETE_OPERATOR,
      },

      // IDENTIFIER
      {
        IDENTIFIER,
        COMPLETE_IDENTIFIER,
        COMPLETE_IDENTIFIER,
        IDENTIFIER,
        COMPLETE_IDENTIFIER,
        COMPLETE_IDENTIFIER,
        COMPLETE_IDENTIFIER,
        COMPLETE_IDENTIFIER,
        COMPLETE_IDENTIFIER,
      },

      // ILLEGAL
      {
        COMPLETE_ILLEGAL,
        COMPLETE_ILLEGAL,
        ILLEGAL,
        COMPLETE_ILLEGAL,
        COMPLETE_ILLEGAL,
        COMPLETE_ILLEGAL,
        ILLEGAL,
        COMPLETE_ILLEGAL,
        COMPLETE_ILLEGAL,
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
      },

      // OPERATOR
      {
        COMPLETE_OPERATOR,
        COMPLETE_OPERATOR,
        COMPLETE_OPERATOR,
        COMPLETE_OPERATOR,
        OPERATOR,
        COMPLETE_OPERATOR,
        COMPLETE_OPERATOR,
        COMPLETE_OPERATOR,
        COMPLETE_OPERATOR,
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

  token::t next__complete_identifier(table::t const &, char const * a, char const * b, char const *, state::t) {
    switch (b - a) {
    case 2:
      if (!bcmp(a, "BY", 2)) return token::make(token::tag::BY, a, b);
      if (!bcmp(a, "DO", 2)) return token::make(token::tag::DO, a, b);
      if (!bcmp(a, "IF", 2)) return token::make(token::tag::IF, a, b);
      if (!bcmp(a, "IN", 2)) return token::make(token::tag::IN, a, b);
      if (!bcmp(a, "IS", 2)) return token::make(token::tag::IS, a, b);
      if (!bcmp(a, "OF", 2)) return token::make(token::tag::OF, a, b);
      if (!bcmp(a, "OR", 2)) return token::make(token::tag::OR, a, b);
      if (!bcmp(a, "TO", 2)) return token::make(token::tag::TO, a, b);
      break;
    case 3:
      if (!bcmp(a, "DIV", 3)) return token::make(token::tag::DIV, a, b);
      if (!bcmp(a, "END", 3)) return token::make(token::tag::END, a, b);
      if (!bcmp(a, "FOR", 3)) return token::make(token::tag::FOR, a, b);
      if (!bcmp(a, "MOD", 3)) return token::make(token::tag::MOD, a, b);
      if (!bcmp(a, "NIL", 3)) return token::make(token::tag::NIL, a, b);
      if (!bcmp(a, "VAR", 3)) return token::make(token::tag::VAR, a, b);
      break;
    case 4:
      if (!bcmp(a, "CASE", 4)) return token::make(token::tag::CASE, a, b);
      if (!bcmp(a, "ELSE", 4)) return token::make(token::tag::ELSE, a, b);
      if (!bcmp(a, "THEN", 4)) return token::make(token::tag::THEN, a, b);
      if (!bcmp(a, "TRUE", 4)) return token::make(token::tag::TRUE, a, b);
      if (!bcmp(a, "TYPE", 4)) return token::make(token::tag::TYPE, a, b);
      break;
    case 5:
      if (!bcmp(a, "ARRAY", 5)) return token::make(token::tag::ARRAY, a, b);
      if (!bcmp(a, "BEGIN", 5)) return token::make(token::tag::BEGIN, a, b);
      if (!bcmp(a, "CONST", 5)) return token::make(token::tag::CONST, a, b);
      if (!bcmp(a, "ELSIF", 5)) return token::make(token::tag::ELSIF, a, b);
      if (!bcmp(a, "FALSE", 5)) return token::make(token::tag::FALSE, a, b);
      if (!bcmp(a, "UNTIL", 5)) return token::make(token::tag::UNTIL, a, b);
      if (!bcmp(a, "WHILE", 5)) return token::make(token::tag::WHILE, a, b);
      break;
    case 6:
      if (!bcmp(a, "IMPORT", 6)) return token::make(token::tag::IMPORT, a, b);
      if (!bcmp(a, "MODULE", 6)) return token::make(token::tag::MODULE, a, b);
      if (!bcmp(a, "RECORD", 6)) return token::make(token::tag::RECORD, a, b);
      if (!bcmp(a, "REPEAT", 6)) return token::make(token::tag::REPEAT, a, b);
      if (!bcmp(a, "RETURN", 6)) return token::make(token::tag::RETURN, a, b);
      break;
    case 7:
      if (!bcmp(a, "POINTER", 7)) return token::make(token::tag::POINTER, a, b);
      break;
    case 9:
      if (!bcmp(a, "PROCEDURE", 9)) return token::make(token::tag::PROCEDURE, a, b);
      break;
    }

    return token::make(token::tag::IDENTIFIER, a, b);
  }

  token::t next__complete_illegal(table::t const &, char const * a, char const * b, char const *, state::t) {
    return token::make(token::tag::ILLEGAL, a, b);
  }

  token::t next__complete_number(table::t const &, char const * a, char const * b, char const *, state::t) {
    return token::make(token::tag::NUMBER, a, b);
  }

  token::t next__complete_operator(table::t const &, char const * a, char const * b, char const *, state::t) {
    if (b - a == 1) {
      switch (* a) {
        case '+': return token::make(token::tag::PLUS, a, b);
        case '-': return token::make(token::tag::MINUS, a, b);
        case '*': return token::make(token::tag::STAR, a, b);
        case '/': return token::make(token::tag::SLASH, a, b);
        case '~': return token::make(token::tag::TILDE, a, b);
        case '&': return token::make(token::tag::AMPERSAND, a, b);
        case '.': return token::make(token::tag::DOT, a, b);
        case '|': return token::make(token::tag::PIPE, a, b);
        case '^': return token::make(token::tag::CARET, a, b);
        case '=': return token::make(token::tag::EQUAL, a, b);
        case '#': return token::make(token::tag::HASH, a, b);
        case '<': return token::make(token::tag::LT, a, b);
        case '>': return token::make(token::tag::GT, a, b);
        case ':': return token::make(token::tag::COLON, a, b);
      }
    }
    else if (b - a == 2) {
      if (!bcmp(a, ":=", 2)) return token::make(token::tag::ASSIGNMENT, a, b);
      if (!bcmp(a, "<=", 2)) return token::make(token::tag::LE, a, b);
      if (!bcmp(a, ">=", 2)) return token::make(token::tag::GE, a, b);
      if (!bcmp(a, "..", 2)) return token::make(token::tag::DOTDOT, a, b);
    }

    return token::make(token::tag::ILLEGAL, a, b);
  }

  token::t next__complete_punctuation(table::t const &, char const * a, char const * b, char const *, state::t) {
    b = b + 1;

    switch (* a) {
      case ',': return token::make(token::tag::COMMA, a, b);
      case ';': return token::make(token::tag::SEMICOLON, a, b);
      case '(': return token::make(token::tag::LPARENTHESIS, a, b);
      case '[': return token::make(token::tag::LBRACKET, a, b);
      case '{': return token::make(token::tag::LBRACE, a, b);
      case ')': return token::make(token::tag::RPARENTHESIS, a, b);
      case ']': return token::make(token::tag::RBRACKET, a, b);
      case '}': return token::make(token::tag::RBRACE, a, b);
    }

    return token::make(token::tag::ILLEGAL, a, b);
  }

  token::t next__stop(table::t const &, char const * a, char const * b, char const * c, state::t) {
    if (b != c) {
      // Null byte in source. We produce an ILLEGAL token for each null byte,
      // though perhaps we could coalesce such tokens.

      return token::make(token::tag::ILLEGAL, a, b + 1);
    }

    return token::make(token::tag::STOP, a, b);
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
      next__complete_illegal,
      next__complete_number,
      next__complete_operator,
      next__complete_punctuation,
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
