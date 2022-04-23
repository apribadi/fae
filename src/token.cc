namespace token {
  namespace tag {
    enum t : u8 {
      // special

      STOP,
      ILLEGAL,

      // identifier

      IDENTIFIER,
      IDENTIFIER_LPAREN,   // foo(
      IDENTIFIER_LBRACKET, // foo[

      // literal

      NUMBER,
      STRING,

      // punctuation

      COLON,     // :
      COMMA,     // ,
      DOT,       // .
      SEMICOLON, // ;
      LPAREN,    // (
      LBRACKET,  // [
      LBRACE,    // {
      RPAREN,    // )
      RBRACKET,  // ]
      RBRACE,    // }

      // operator

      ASSIGN,    // =

      EQ,        // ==
      NE,        // !=
      LT,        // <
      GT,        // >
      LE,        // <=
      GE,        // >=

      PLUS,      // +
      MINUS,     // -
      STAR,      // *
      SLASH,     // /

      AMPERSAND, // &
      AT,        // @
      BANG,      // !
      CARET,     // ^
      DOLLAR,    // $
      PERCENT,   // %
      PIPE,      // |
      QUERY,     // ?
      TILDE,     // ~

      // keyword

      AND,
      BREAK,
      ELIF,
      ELSE,
      END,
      FOR,
      FUN,
      IF,
      LET,
      LOOP,
      OR,
      WHILE,
    };

    char const * to_string(t t) {
      switch (t) {
        case STOP: return "STOP";
        case ILLEGAL: return "ILLEGAL";
        case IDENTIFIER: return "IDENTIFIER";
        case IDENTIFIER_LPAREN: return "IDENTIFIER_LPAREN";
        case IDENTIFIER_LBRACKET: return "IDENTIFIER_LBRACKET";
        case NUMBER: return "NUMBER";
        case STRING: return "STRING";
        case COLON: return "COLON";
        case COMMA: return "COMMA";
        case DOT: return "DOT";
        case SEMICOLON: return "SEMICOLON";
        case LPAREN: return "LPAREN";
        case LBRACKET: return "LBRACKET";
        case LBRACE: return "LBRACE";
        case RPAREN: return "RPAREN";
        case RBRACKET: return "RBRACKET";
        case RBRACE: return "RBRACE";
        case ASSIGN: return "ASSIGN";
        case EQ: return "EQ";
        case NE: return "NE";
        case LT: return "LT";
        case GT: return "GT";
        case LE: return "LE";
        case GE: return "GE";
        case PLUS: return "PLUS";
        case MINUS: return "MINUS";
        case STAR: return "STAR";
        case SLASH: return "SLASH";
        case AMPERSAND: return "AMPERSAND";
        case AT: return "AT";
        case BANG: return "BANG";
        case CARET: return "CARET";
        case DOLLAR: return "DOLLAR";
        case PERCENT: return "PERCENT";
        case PIPE: return "PIPE";
        case QUERY: return "QUERY";
        case TILDE: return "TILDE";
        case AND: return "AND";
        case BREAK: return "BREAK";
        case ELIF: return "ELIF";
        case ELSE: return "ELSE";
        case END: return "END";
        case FOR: return "FOR";
        case FUN: return "FUN";
        case IF: return "IF";
        case LET: return "LET";
        case LOOP: return "LOOP";
        case OR: return "OR";
        case WHILE: return "WHILE";
      }

      return "???";
    }
  }

  class t {
  public:
    tag::t tag;
    char const * start;
    char const * stop;
  };

  t make(tag::t tag, char const * start, char const * stop) {
    return { tag, start, stop };
  }

  void print(t t) {
    printf(
        "%s: \"%.*s\"\n",
        tag::to_string(t.tag),
        static_cast<int>(t.stop - t.start),
        t.start
      );
  }
}
