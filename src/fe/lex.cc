namespace fae::fe::lex {
  using Token = fae::ir::Token;
}

namespace fae::fe::lex::internal {
  enum class Kind : u8 {
    ILLEGAL = 0,
    DIGIT,
    DOT,
    HASH,
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

namespace fae::fe::lex::internal::kind {
  using enum Kind;

  constexpr size_t NUM_VALUES = 12;

  constexpr Kind TABLE[256] = {
    [ '\0' ] = NIL,
    [ '\n' ] = LINEBREAK,
    [ '\r' ] = LINEBREAK,
    [ ' ' ] = SPACE,
    [ '!' ] = OPERATOR,
    [ '"' ] = QUOTE,
    [ '#' ] = HASH,
    [ '$' ] = OPERATOR,
    [ '%' ] = OPERATOR,
    [ '&' ] = OPERATOR,
    [ '(' ] = PUNCTUATION,
    [ ')' ] = PUNCTUATION,
    [ '*' ] = OPERATOR,
    [ '+' ] = OPERATOR,
    [ ',' ] = PUNCTUATION,
    [ '-' ] = OPERATOR,
    [ '.' ] = DOT,
    [ '/' ] = OPERATOR,
    [ '0' ] = DIGIT,
    [ '1' ] = DIGIT,
    [ '2' ] = DIGIT,
    [ '3' ] = DIGIT,
    [ '4' ] = DIGIT,
    [ '5' ] = DIGIT,
    [ '6' ] = DIGIT,
    [ '7' ] = DIGIT,
    [ '8' ] = DIGIT,
    [ '9' ] = DIGIT,
    [ ':' ] = PUNCTUATION,
    [ ';' ] = PUNCTUATION,
    [ '<' ] = OPERATOR,
    [ '=' ] = OPERATOR,
    [ '>' ] = OPERATOR,
    [ '?' ] = OPERATOR,
    [ '@' ] = OPERATOR,
    [ 'A' ] = LETTER,
    [ 'B' ] = LETTER,
    [ 'C' ] = LETTER,
    [ 'D' ] = LETTER,
    [ 'E' ] = LETTER,
    [ 'F' ] = LETTER,
    [ 'G' ] = LETTER,
    [ 'H' ] = LETTER,
    [ 'I' ] = LETTER,
    [ 'J' ] = LETTER,
    [ 'K' ] = LETTER,
    [ 'L' ] = LETTER,
    [ 'M' ] = LETTER,
    [ 'N' ] = LETTER,
    [ 'O' ] = LETTER,
    [ 'P' ] = LETTER,
    [ 'Q' ] = LETTER,
    [ 'R' ] = LETTER,
    [ 'S' ] = LETTER,
    [ 'T' ] = LETTER,
    [ 'U' ] = LETTER,
    [ 'V' ] = LETTER,
    [ 'W' ] = LETTER,
    [ 'X' ] = LETTER,
    [ 'Y' ] = LETTER,
    [ 'Z' ] = LETTER,
    [ '[' ] = PUNCTUATION,
    [ ']' ] = PUNCTUATION,
    [ '^' ] = OPERATOR,
    [ '_' ] = UNDERSCORE,
    [ 'a' ] = LETTER,
    [ 'b' ] = LETTER,
    [ 'c' ] = LETTER,
    [ 'd' ] = LETTER,
    [ 'e' ] = LETTER,
    [ 'f' ] = LETTER,
    [ 'g' ] = LETTER,
    [ 'h' ] = LETTER,
    [ 'i' ] = LETTER,
    [ 'j' ] = LETTER,
    [ 'k' ] = LETTER,
    [ 'l' ] = LETTER,
    [ 'm' ] = LETTER,
    [ 'n' ] = LETTER,
    [ 'o' ] = LETTER,
    [ 'p' ] = LETTER,
    [ 'q' ] = LETTER,
    [ 'r' ] = LETTER,
    [ 's' ] = LETTER,
    [ 't' ] = LETTER,
    [ 'u' ] = LETTER,
    [ 'v' ] = LETTER,
    [ 'w' ] = LETTER,
    [ 'x' ] = LETTER,
    [ 'y' ] = LETTER,
    [ 'z' ] = LETTER,
    [ '{' ] = PUNCTUATION,
    [ '|' ] = OPERATOR,
    [ '}' ] = PUNCTUATION,
    [ '~' ] = OPERATOR,
  };
}

namespace fae::fe::lex::internal {
  enum class State {
    RESTART = 0,
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

namespace fae::fe::lex::internal::state {
  using enum State;

  constexpr size_t NUM_VALUES_NONTERMINAL = 8;
  constexpr size_t NUM_VALUES_TERMINAL = 10;
  constexpr size_t NUM_VALUES = NUM_VALUES_NONTERMINAL + NUM_VALUES_TERMINAL;

  constexpr array<State, kind::NUM_VALUES> TABLE_RESTART = {
    STOP_ILLEGAL_CHARACTER,
    NUMBER,
    DOT,
    COMMENT,
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
    STOP_ILLEGAL_CHARACTER,
    NUMBER,
    DOT,
    COMMENT,
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
  };

  constexpr array<State, kind::NUM_VALUES> TABLE_IDENTIFIER = {
    STOP_IDENTIFIER,
    IDENTIFIER,
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
    STOP_NUMBER,
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

namespace fae::fe::lex::internal {
  using enum Token::Tag;

  struct Table {
    array<Kind, 256> classify;
    array<array<State, kind::NUM_VALUES>, state::NUM_VALUES_NONTERMINAL> transition;
    array<Token(*)(Table &, char *, char *, char *, State), state::NUM_VALUES> jump;
  };

  Token next__start(Table & table, char * a, char * b) {
    State s = table.transition[(u8) State::START][(u8) table.classify[(u8) (* a)]];
    return table.jump[(u8) s](table, a, a, b, s);
  }

  Token next__continue(Table & table, char * a, char * b, char * c, State s) {
    a = s == State::RESTART ? b + 1 : a;
    b = b + 1;
    s = table.transition[(u8) s][(u8) table.classify[(u8) (* b)]];
    [[clang::musttail]] return table.jump[(u8) s](table, a, b, c, s);
  }

  Token next__stop_dot(Table &, char * a, char * b, char *, State) {
    if (b - a == 1)
      return Token(DOT, a, b);

    return Token(ILLEGAL, a, b);
  }

  Token next__stop_identifier(Table &, char * a, char * b, char *, State) {
    switch (b - a) {
    case 2:
      if (!bcmp(a, "if", 2)) return Token(IF, a, b);
      if (!bcmp(a, "or", 2)) return Token(OR, a, b);
      break;
    case 3:
      if (!bcmp(a, "and", 3)) return Token(AND, a, b);
      if (!bcmp(a, "end", 3)) return Token(END, a, b);
      if (!bcmp(a, "for", 3)) return Token(FOR, a, b);
      if (!bcmp(a, "fun", 3)) return Token(FUN, a, b);
      if (!bcmp(a, "let", 3)) return Token(LET, a, b);
      break;
    case 4:
      if (!bcmp(a, "else", 4)) return Token(ELSE, a, b);
      if (!bcmp(a, "elif", 4)) return Token(ELIF, a, b);
      if (!bcmp(a, "loop", 4)) return Token(LOOP, a, b);
      break;
    case 5:
      if (!bcmp(a, "break", 5)) return Token(BREAK, a, b);
      if (!bcmp(a, "while", 5)) return Token(WHILE, a, b);
      break;
    case 6:
      if (!bcmp(a, "return", 5)) return Token(RETURN, a, b);
      break;
    }

    return Token(IDENTIFIER, a, b);
  }

  Token next__stop_illegal_character(Table &, char * a, char * b, char *, State) {
    return Token(ILLEGAL, a, b + 1);
  }

  Token next__stop_illegal_token(Table &, char * a, char * b, char *, State) {
    return Token(ILLEGAL, a, b);
  }

  Token next__stop_nil(Table &, char *, char * b, char * c, State) {
    if (b != c)
      return Token(ILLEGAL, b, b + 1);

    return Token(STOP, b, b);
  }

  Token next__stop_number(Table &, char * a, char * b, char *, State) {
    return Token(NUMBER, a, b);
  }

  Token next__stop_operator(Table &, char * a, char * b, char *, State) {
    if (b - a == 1) {
      switch (* a) {
        case '=': return Token(ASSIGN, a, b);
        case '<': return Token(LT, a, b);
        case '>': return Token(GT, a, b);
        case '+': return Token(PLUS, a, b);
        case '-': return Token(MINUS, a, b);
        case '*': return Token(STAR, a, b);
        case '/': return Token(SLASH, a, b);
        case '&': return Token(AMPERSAND, a, b);
        case '@': return Token(AT, a, b);
        case '!': return Token(BANG, a, b);
        case '^': return Token(CARET, a, b);
        case '$': return Token(DOLLAR, a, b);
        case '%': return Token(PERCENT, a, b);
        case '|': return Token(PIPE, a, b);
        case '?': return Token(QUERY, a, b);
        case '~': return Token(TILDE, a, b);
      }
    }
    else if (b - a == 2) {
      if (!bcmp(a, "==", 2)) return Token(EQ, a, b);
      if (!bcmp(a, "!=", 2)) return Token(NE, a, b);
      if (!bcmp(a, "<=", 2)) return Token(LE, a, b);
      if (!bcmp(a, ">=", 2)) return Token(GE, a, b);
    }

    return Token(ILLEGAL, a, b);
  }

  Token next__stop_string(Table &, char * a, char * b, char *, State) {
    return Token(STRING, a, b + 1);
  }

  Token next__stop_punctuation(Table &, char * a, char * b, char *, State) {
    switch (* a) {
      case ':': return Token(COLON, a, b + 1);
      case ',': return Token(COMMA, a, b + 1);
      case ';': return Token(SEMICOLON, a, b + 1);
      case '(': return Token(LPAREN, a, b + 1);
      case '[': return Token(LBRACKET, a, b + 1);
      case '{': return Token(LBRACE, a, b + 1);
      case ')': return Token(RPAREN, a, b + 1);
      case ']': return Token(RBRACKET, a, b + 1);
      case '}': return Token(RBRACE, a, b + 1);
    }

    return Token(ILLEGAL, a, b + 1);
  }

  Token next__stop_punctuation_no_space(Table &, char * a, char * b, char *, State) {
    switch (* a) {
      case ':': return Token(COLON, a, b + 1);
      case ',': return Token(COMMA, a, b + 1);
      case ';': return Token(SEMICOLON, a, b + 1);
      case '(': return Token(LPAREN_NOSPACE, a, b + 1);
      case '[': return Token(LBRACKET_NOSPACE, a, b + 1);
      case '{': return Token(LBRACE, a, b + 1);
      case ')': return Token(RPAREN, a, b + 1);
      case ']': return Token(RBRACKET, a, b + 1);
      case '}': return Token(RBRACE, a, b + 1);
    }

    return Token(ILLEGAL, a, b + 1);
  }

  Table global_table = {
    to_array(kind::TABLE),
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

namespace fae::fe::lex {
  Token next(char * start, char * stop) {
    return internal::next__start(internal::global_table, start, stop);
  }
}
