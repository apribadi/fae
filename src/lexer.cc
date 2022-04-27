namespace lexer {
  namespace kind {
    enum t : u8 {
      DIGIT,
      DOT,
      HASH,
      ILLEGAL,
      LETTER,
      LINEBREAK,
      OPERATOR,
      PUNCTUATION,
      QUOTE,
      SPACE,
      STOP,
      UNDERSCORE,
    };

    constexpr size_t NUM = 12;

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

  namespace state {
    enum t {
      RESTART,
      START,
      COMMENT,
      DOT,
      IDENTIFIER,
      NUMBER,
      OPERATOR,
      STRING,
      STOP,
      STOP_DOT,
      STOP_IDENTIFIER,
      STOP_ILLEGAL_CHARACTER,
      STOP_ILLEGAL_TOKEN,
      STOP_NUMBER,
      STOP_OPERATOR,
      STOP_PUNCTUATION,
      STOP_PUNCTUATION_NOSPACE,
      STOP_STRING,
    };

    constexpr size_t NUM_NONTERMINAL = 8;
    constexpr size_t NUM_TERMINAL = 10;
    constexpr size_t NUM = NUM_NONTERMINAL + NUM_TERMINAL;

    constexpr array<t, kind::NUM> transition_restart = {
      NUMBER,
      DOT,
      COMMENT,
      STOP_ILLEGAL_CHARACTER,
      IDENTIFIER,
      RESTART,
      OPERATOR,
      STOP_PUNCTUATION,
      STRING,
      RESTART,
      STOP,
      IDENTIFIER,
    };

    constexpr array<t, kind::NUM> transition_start = {
      NUMBER,
      DOT,
      COMMENT,
      STOP_ILLEGAL_CHARACTER,
      IDENTIFIER,
      RESTART,
      OPERATOR,
      STOP_PUNCTUATION_NOSPACE,
      STRING,
      RESTART,
      STOP,
      IDENTIFIER,
    };

    constexpr array<t, kind::NUM> transition_comment = {
      COMMENT,
      COMMENT,
      COMMENT,
      COMMENT,
      COMMENT,
      RESTART,
      COMMENT,
      COMMENT,
      COMMENT,
      COMMENT,
      STOP,
      COMMENT,
    };

    constexpr array<t, kind::NUM> transition_dot = {
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

    constexpr array<t, kind::NUM> transition_identifier = {
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

    constexpr array<t, kind::NUM> transition_number = {
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

    constexpr array<t, kind::NUM> transition_operator = {
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
      STOP_OPERATOR,
    };

    constexpr array<t, kind::NUM> transition_string = {
      STRING,
      STRING,
      STRING,
      STRING,
      STRING,
      STRING,
      STRING,
      STRING,
      STOP_STRING,
      STRING,
      STOP_ILLEGAL_TOKEN,
      STRING,
    };

    constexpr array<array<t, kind::NUM>, NUM_NONTERMINAL> transition = {
      transition_restart,
      transition_start,
      transition_comment,
      transition_dot,
      transition_identifier,
      transition_number,
      transition_operator,
      transition_string,
    };
  }

  namespace table {
    class t {
    public:
      array<kind::t, 256> kind;
      array<array<state::t, kind::NUM>, state::NUM_NONTERMINAL> transition;
      array<token::t(*)(t const &, char const *, char const *, char const *, state::t), state::NUM> jump;
    };
  }

  token::t next__start(table::t const & table, char const * a, char const * b) {
    state::t s = table.transition[state::START][table.kind[static_cast<unsigned char>(* a)]];
    return table.jump[s](table, a, a, b, s);
  }

  token::t next__continue(table::t const & table, char const * a, char const * b, char const * c, state::t s) {
    a = s ? a : b + 1;
    b = b + 1;
    s = table.transition[s][table.kind[static_cast<unsigned char>(* b)]];
    [[clang::musttail]] return table.jump[s](table, a, b, c, s);
  }

  token::t next__stop(table::t const &, char const *, char const * b, char const * c, state::t) {
    if (b != c)
      return token::make(token::tag::ILLEGAL, b, b + 1);

    return token::make(token::tag::STOP, b, b);
  }

  token::t next__stop_dot(table::t const &, char const * a, char const * b, char const *, state::t) {
    if (b - a == 1)
      return token::make(token::tag::DOT, a, b);

    return token::make(token::tag::ILLEGAL, a, b);
  }

  token::t next__stop_identifier(table::t const &, char const * a, char const * b, char const *, state::t) {
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
    case 6:
      if (!bcmp(a, "return", 5)) return token::make(token::tag::RETURN, a, b);
      break;
    }

    return token::make(token::tag::IDENTIFIER, a, b);
  }

  token::t next__stop_illegal_character(table::t const &, char const * a, char const * b, char const *, state::t) {
    return token::make(token::tag::ILLEGAL, a, b + 1);
  }

  token::t next__stop_illegal_token(table::t const &, char const * a, char const * b, char const *, state::t) {
    return token::make(token::tag::ILLEGAL, a, b);
  }

  token::t next__stop_number(table::t const &, char const * a, char const * b, char const *, state::t) {
    return token::make(token::tag::NUMBER, a, b);
  }

  token::t next__stop_operator(table::t const &, char const * a, char const * b, char const *, state::t) {
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

  token::t next__stop_string(table::t const &, char const * a, char const * b, char const *, state::t) {
    return token::make(token::tag::STRING, a, b + 1);
  }

  token::t next__stop_punctuation(table::t const &, char const * a, char const * b, char const *, state::t) {
    switch (* a) {
      case ':': return token::make(token::tag::COLON, a, b + 1);
      case ',': return token::make(token::tag::COMMA, a, b + 1);
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

  token::t next__stop_punctuation_nospace(table::t const &, char const * a, char const * b, char const *, state::t) {
    switch (* a) {
      case ':': return token::make(token::tag::COLON, a, b + 1);
      case ',': return token::make(token::tag::COMMA, a, b + 1);
      case ';': return token::make(token::tag::SEMICOLON, a, b + 1);
      case '(': return token::make(token::tag::LPAREN_NOSPACE, a, b + 1);
      case '[': return token::make(token::tag::LBRACKET_NOSPACE, a, b + 1);
      case '{': return token::make(token::tag::LBRACE, a, b + 1);
      case ')': return token::make(token::tag::RPAREN, a, b + 1);
      case ']': return token::make(token::tag::RBRACKET, a, b + 1);
      case '}': return token::make(token::tag::RBRACE, a, b + 1);
    }

    return token::make(token::tag::ILLEGAL, a, b + 1);
  }

  constexpr table::t global_table = {
    kind::table,
    state::transition,
    {
      next__continue,
      NULL,
      next__continue,
      next__continue,
      next__continue,
      next__continue,
      next__continue,
      next__continue,
      next__stop,
      next__stop_dot,
      next__stop_identifier,
      next__stop_illegal_character,
      next__stop_illegal_token,
      next__stop_number,
      next__stop_operator,
      next__stop_punctuation,
      next__stop_punctuation_nospace,
      next__stop_string,
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
      token::t token = next__start(global_table, current, stop);
      current = token.stop;
      return token;
    }
  };
}
