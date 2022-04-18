namespace token {
  namespace tag {
    enum t : u8 {
      STOP,
      ILLEGAL,
      INTEGER,
      DECIMAL,
      IDENTIFIER,
      PLUS,         // +
      MINUS,        // -
      STAR,         // *
      SLASH,        // /
      TILDE,        // ~
      AMPERSAND,    // &
      DOT,          // .
      COMMA,        // ,
      SEMICOLON,    // ;
      PIPE,         // |
      LPARENTHESIS, // (
      LBRACKET,     // [
      LBRACE,       // {
      ASSIGNMENT,   // :=
      CARET,        // ^
      EQUAL,        // =
      HASH,         // #
      LT,           // <
      GT,           // >
      LE,           // <=
      GE,           // >
      DOTDOT,       // ..
      COLON,        // :
      RPARENTHESIS, // )
      RBRACKET,     // ]
      RBRACE,       // }
			ARRAY,
      BEGIN,
      BY,
      CASE,
      CONST,
      DIV,
      DO,
      ELSE,
      ELSIF,
      END,
      FALSE,
      FOR,
      IF,
      IMPORT,
      IN,
      IS,
      MOD,
      MODULE,
      NIL,
      OF,
      OR,
      POINTER,
      PROCEDURE,
      RECORD,
      REPEAT,
      RETURN,
      THEN,
      TO,
      TRUE,
      TYPE,
      UNTIL,
      VAR,
      WHILE,
    };

    char const * to_string(t t) {
      switch (t) {
        case STOP: return "STOP";
        case ILLEGAL: return "ILLEGAL";
        case INTEGER: return "INTEGER";
        case DECIMAL: return "DECIMAL";
        case IDENTIFIER: return "IDENTIFIER";
        case PLUS: return "PLUS";
        case MINUS: return "MINUS";
        case STAR: return "STAR";
        case SLASH: return "SLASH";
        case TILDE: return "TILDE";
        case AMPERSAND: return "AMPERSAND";
        case DOT: return "DOT";
        case COMMA: return "COMMA";
        case SEMICOLON: return "SEMICOLON";
        case PIPE: return "PIPE";
        case LPARENTHESIS: return "LPARENTHESIS";
        case LBRACKET: return "LBRACKET";
        case LBRACE: return "LBRACE";
        case ASSIGNMENT: return "ASSIGNMENT";
        case CARET: return "CARET";
        case EQUAL: return "EQUAL";
        case HASH: return "HASH";
        case LT: return "LT";
        case GT: return "GT";
        case LE: return "LE";
        case GE: return "GE";
        case DOTDOT: return "DOTDOT";
        case COLON: return "COLON";
        case RPARENTHESIS: return "RPARENTHESIS";
        case RBRACKET: return "RBRACKET";
        case RBRACE: return "RBRACE";
        /*
        ARRAY,
        BEGIN,
        BY,
        CASE,
        CONST,
        DIV,
        DO,
        ELSE,
        ELSIF,
        END,
        FALSE,
        FOR,
        IF,
        IMPORT,
        IN,
        IS,
        MOD,
        MODULE,
        NIL,
        OF,
        OR,
        POINTER,
        PROCEDURE,
        RECORD,
        REPEAT,
        RETURN,
        THEN,
        TO,
        TRUE,
        TYPE,
        UNTIL,
        VAR,
        WHILE,
        */
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
        "tag = %s, \"%.*s\"\n",
        tag::to_string(t.tag),
        static_cast<int>(t.stop - t.start),
        reinterpret_cast<char const *>(t.start)
      );
  }
}
