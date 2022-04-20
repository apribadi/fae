namespace lexer {
  // TODO:
  //
  // decimals
  // comments

  namespace kind {
    // add
    //
    // LPAREN
    // RPAREN
    // STAR
    // A_B_C_D_F
    // E
    // H
    // X
    // PLUS_MINUS
    // ANGLE_COLON
    //
    // remove
    //
    // ANGLE
    // COLON
    enum t : u8 {
      ANGLE,
      COLON,
      DIGIT,
      DOT,
      EQUAL,
      ILLEGAL,
      LETTER,
      OPERATOR,
      QUOTE,
      SPACE,
      STOP,
    };

    constexpr size_t COUNT = 11;

    char const * to_string(t t) {
      switch (t) {
        case ANGLE: return "ANGLE";
        case COLON: return "COLON";
        case DIGIT: return "DIGIT";
        case DOT: return "DOT";
        case EQUAL: return "EQUAL";
        case ILLEGAL: return "ILLEGAL";
        case LETTER: return "LETTER";
        case OPERATOR: return "OPERATOR";
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
      SPACE,    // line feed
      ILLEGAL,
      ILLEGAL,
      SPACE,    // carriage return
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      SPACE,    // ' '
      ILLEGAL,  // !
      QUOTE,    // "
      OPERATOR, // #
      ILLEGAL,  // $
      ILLEGAL,  // %
      OPERATOR, // &
      ILLEGAL,  // '
      OPERATOR, // (
      OPERATOR, // )
      OPERATOR, // *
      OPERATOR, // +
      OPERATOR, // ,
      OPERATOR, // -
      DOT,      // .
      OPERATOR, // /
      DIGIT,    // 0
      DIGIT,    // 1
      DIGIT,    // 2
      DIGIT,    // 3
      DIGIT,    // 4
      DIGIT,    // 5
      DIGIT,    // 6
      DIGIT,    // 7
      DIGIT,    // 8
      DIGIT,    // 9
      COLON,    // :
      OPERATOR, // ;
      ANGLE,    // <
      EQUAL,    // =
      ANGLE,    // >
      ILLEGAL,  // ?
      ILLEGAL,  // @
      LETTER,   // A
      LETTER,   // B
      LETTER,   // C
      LETTER,   // D
      LETTER,   // E
      LETTER,   // F
      LETTER,   // G
      LETTER,   // H
      LETTER,   // I
      LETTER,   // J
      LETTER,   // K
      LETTER,   // L
      LETTER,   // M
      LETTER,   // N
      LETTER,   // O
      LETTER,   // P
      LETTER,   // Q
      LETTER,   // R
      LETTER,   // S
      LETTER,   // T
      LETTER,   // U
      LETTER,   // V
      LETTER,   // W
      LETTER,   // X
      LETTER,   // Y
      LETTER,   // Z
      OPERATOR, // [
      ILLEGAL,  // 
      OPERATOR, // ]
      ILLEGAL,  // ^
      ILLEGAL,  // _
      ILLEGAL,  // `
      LETTER,   // a
      LETTER,   // b
      LETTER,   // c
      LETTER,   // d
      LETTER,   // e
      LETTER,   // f
      LETTER,   // g
      LETTER,   // h
      LETTER,   // i
      LETTER,   // j
      LETTER,   // k
      LETTER,   // l
      LETTER,   // m
      LETTER,   // n
      LETTER,   // o
      LETTER,   // p
      LETTER,   // q
      LETTER,   // r
      LETTER,   // s
      LETTER,   // t
      LETTER,   // u
      LETTER,   // v
      LETTER,   // w
      LETTER,   // x
      LETTER,   // y
      LETTER,   // z
      OPERATOR, // {
      OPERATOR, // |
      OPERATOR, // }
      OPERATOR, // ~
      ILLEGAL,  // 127
      ILLEGAL,  // 128
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL, // 255
    };
  }

  namespace state {
    enum t {
      START,
      ANGLE,
      COLON,
      DECIMAL,
      DOT,
      IDENTIFIER,
      ILLEGAL,
      INTEGER,
      COMPLETE_DECIMAL,
      COMPLETE_IDENTIFIER,
      COMPLETE_INTEGER,
      COMPLETE_OPERATOR,
      COMPLETE_OPERATOR_ADVANCE,
      COMPLETE_ILLEGAL,
      STOP,
    };

    constexpr size_t NONTERMINAL_COUNT = 8;
    constexpr size_t COUNT = 15;

    char const * to_string(t t) {
      switch (t) {
        case START: return "START";
        case ANGLE: return "ANGLE";
        case COLON: return "COLON";
        case DECIMAL: return "DECIMAL";
        case DOT: return "DOT";
        case IDENTIFIER: return "IDENTIFIER";
        case ILLEGAL: return "ILLEGAL";
        case INTEGER: return "INTEGER";
        case COMPLETE_DECIMAL: return "COMPLETE_DECIMAL";
        case COMPLETE_IDENTIFIER: return "COMPLETE_IDENTIFIER";
        case COMPLETE_INTEGER: return "COMPLETE_INTEGER";
        case COMPLETE_OPERATOR: return "COMPLETE_OPERATOR";
        case COMPLETE_OPERATOR_ADVANCE: return "COMPLETE_OPERATOR_ADVANCE";
        case COMPLETE_ILLEGAL: return "COMPLETE_ILLEGAL";
        case STOP: return "STOP";
      }

      return "???";
    }

    constexpr array<array<t, kind::COUNT>, NONTERMINAL_COUNT> table = {
      // START ->
      (array<t, kind::COUNT>) {
        ANGLE,
        COLON,
        INTEGER,
        DOT,
        COMPLETE_OPERATOR_ADVANCE,
        ILLEGAL,
        IDENTIFIER,
        COMPLETE_OPERATOR_ADVANCE,
        ILLEGAL,
        START,
        STOP,
      },

      // ANGLE ->
      {
        COMPLETE_OPERATOR,
        COMPLETE_OPERATOR,
        COMPLETE_OPERATOR,
        COMPLETE_OPERATOR,
        COMPLETE_OPERATOR_ADVANCE,
        COMPLETE_OPERATOR,
        COMPLETE_OPERATOR,
        COMPLETE_OPERATOR,
        COMPLETE_OPERATOR,
        COMPLETE_OPERATOR,
        COMPLETE_OPERATOR,
      },

      // COLON ->
      {
        COMPLETE_OPERATOR,
        COMPLETE_OPERATOR,
        COMPLETE_OPERATOR,
        COMPLETE_OPERATOR,
        COMPLETE_OPERATOR_ADVANCE,
        COMPLETE_OPERATOR,
        COMPLETE_OPERATOR,
        COMPLETE_OPERATOR,
        COMPLETE_OPERATOR,
        COMPLETE_OPERATOR,
        COMPLETE_OPERATOR,
      },

      // DECIMAL
      {
        COMPLETE_DECIMAL,
        COMPLETE_DECIMAL,
        DECIMAL,
        COMPLETE_DECIMAL,
        COMPLETE_DECIMAL,
        COMPLETE_DECIMAL,
        COMPLETE_DECIMAL,
        COMPLETE_DECIMAL,
        COMPLETE_DECIMAL,
        COMPLETE_DECIMAL,
        COMPLETE_DECIMAL,
      },

      // DOT ->
      {
        COMPLETE_OPERATOR,
        COMPLETE_OPERATOR,
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
        COMPLETE_IDENTIFIER,
        COMPLETE_IDENTIFIER,
        IDENTIFIER,
        COMPLETE_IDENTIFIER,
        COMPLETE_IDENTIFIER,
        COMPLETE_IDENTIFIER,
        IDENTIFIER,
        COMPLETE_IDENTIFIER,
        COMPLETE_IDENTIFIER,
        COMPLETE_IDENTIFIER,
        COMPLETE_IDENTIFIER,
      },

      // ILLEGAL
      {
        COMPLETE_ILLEGAL,
        COMPLETE_ILLEGAL,
        COMPLETE_ILLEGAL,
        COMPLETE_ILLEGAL,
        COMPLETE_ILLEGAL,
        ILLEGAL,
        COMPLETE_ILLEGAL,
        COMPLETE_ILLEGAL,
        COMPLETE_ILLEGAL,
        COMPLETE_ILLEGAL,
        COMPLETE_ILLEGAL,
      },

      // INTEGER
      {
        COMPLETE_INTEGER,
        COMPLETE_INTEGER,
        INTEGER,
        DECIMAL,
        COMPLETE_INTEGER,
        COMPLETE_INTEGER,
        COMPLETE_INTEGER,
        COMPLETE_INTEGER,
        COMPLETE_INTEGER,
        COMPLETE_INTEGER,
        COMPLETE_INTEGER,
      },
    };
  }

  using kont = token::t (void);

  namespace table {
    class t {
    public:
      array<kind::t, 256> kind;
      array<array<state::t, kind::COUNT>, state::NONTERMINAL_COUNT> state;
      array<token::t(*)(t const &, char const *, char const *, char const *, state::t), state::COUNT> jump;
    };
  }

  __attribute__ ((always_inline))
  token::t next__dispatch(table::t const & table, char const * a, char const * b, char const * c, state::t s) {
    s = table.state[s][table.kind[static_cast<unsigned char>(* b)]];
    [[clang::musttail]] return table.jump[s](table, a, b, c, s);
  }

  token::t next__restart(table::t const & table, char const *, char const * b, char const * c, state::t s) {
    [[clang::musttail]] return next__dispatch(table, b + 1, b + 1, c, s);
  }

  token::t next__continue(table::t const & table, char const * a, char const * b, char const * c, state::t s) {
    [[clang::musttail]] return next__dispatch(table, a, b + 1, c, s);
  }

  token::t next__complete_decimal(table::t const &, char const * a, char const * b, char const *, state::t) {
    return token::make(token::tag::DECIMAL, a, b);
  }

  token::t next__complete_identifier(table::t const &, char const * a, char const * b, char const *, state::t) {
    if (b - a == 2) {
      if (!bcmp(a, "BY", 2)) return token::make(token::tag::BY, a, b);
      if (!bcmp(a, "DO", 2)) return token::make(token::tag::DO, a, b);
      if (!bcmp(a, "IF", 2)) return token::make(token::tag::IF, a, b);
      if (!bcmp(a, "IN", 2)) return token::make(token::tag::IN, a, b);
      if (!bcmp(a, "IS", 2)) return token::make(token::tag::IS, a, b);
      if (!bcmp(a, "OF", 2)) return token::make(token::tag::OF, a, b);
      if (!bcmp(a, "OR", 2)) return token::make(token::tag::OR, a, b);
      if (!bcmp(a, "TO", 2)) return token::make(token::tag::TO, a, b);
    }
    else if (b - a == 3) {
      // TODO: more keywords
    }

    return token::make(token::tag::IDENTIFIER, a, b);
  }

  token::t next__complete_integer(table::t const &, char const * a, char const * b, char const *, state::t) {
    return token::make(token::tag::INTEGER, a, b);
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
        case ',': return token::make(token::tag::COMMA, a, b);
        case ';': return token::make(token::tag::SEMICOLON, a, b);
        case '|': return token::make(token::tag::PIPE, a, b);
        case '(': return token::make(token::tag::LPARENTHESIS, a, b);
        case '[': return token::make(token::tag::LBRACKET, a, b);
        case '{': return token::make(token::tag::LBRACE, a, b);
        case '^': return token::make(token::tag::CARET, a, b);
        case '=': return token::make(token::tag::EQUAL, a, b);
        case '#': return token::make(token::tag::HASH, a, b);
        case '<': return token::make(token::tag::LT, a, b);
        case '>': return token::make(token::tag::GT, a, b);
        case ':': return token::make(token::tag::COLON, a, b);
        case ')': return token::make(token::tag::RPARENTHESIS, a, b);
        case ']': return token::make(token::tag::RBRACKET, a, b);
        case '}': return token::make(token::tag::RBRACE, a, b);
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

  token::t next__complete_operator_inclusive(table::t const & table, char const * a, char const * b, char const * c, state::t s) {
    return next__complete_operator(table, a, b + 1, c, s);
  }

  token::t next__complete_illegal(table::t const &, char const * a, char const * b, char const *, state::t) {
    return token::make(token::tag::ILLEGAL, a, b);
  }

  token::t next__stop(table::t const &, char const * a, char const * b, char const *, state::t) {
    return token::make(token::tag::STOP, a, b);
  }

  constexpr table::t global_table = {
    kind::table,
    state::table,
    {
      next__restart,
      next__continue,
      next__continue,
      next__continue,
      next__continue,
      next__continue,
      next__continue,
      next__continue,
      next__complete_decimal,
      next__complete_identifier,
      next__complete_integer,
      next__complete_operator,
      next__complete_operator_inclusive,
      next__complete_illegal,
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
