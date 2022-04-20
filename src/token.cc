namespace token {
  namespace tag {
    enum t : u8 {
      STOP,
      ILLEGAL,
      IDENTIFIER,
      NUMBER,
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
      GE,           // >=
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
        case IDENTIFIER: return "IDENTIFIER";
        case NUMBER: return "NUMBER";
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
        case ARRAY: return "ARRAY";
        case BEGIN: return "BEGIN";
        case BY: return "BY";
        case CASE: return "CASE";
        case CONST: return "CONST";
        case DIV: return "DIV";
        case DO: return "DO";
        case ELSE: return "ELSE";
        case ELSIF: return "ELSIF";
        case END: return "END";
        case FALSE: return "FALSE";
        case FOR: return "FOR";
        case IF: return "IF";
        case IMPORT: return "IMPORT";
        case IN: return "IN";
        case IS: return "IS";
        case MOD: return "MOD";
        case MODULE: return "MODULE";
        case NIL: return "NIL";
        case OF: return "OF";
        case OR: return "OR";
        case POINTER: return "???";
        case PROCEDURE: return "???";
        case RECORD: return "???";
        case REPEAT: return "???";
        case RETURN: return "???";
        case THEN: return "???";
        case TO: return "TO";
        case TRUE: return "???";
        case TYPE: return "???";
        case UNTIL: return "???";
        case VAR: return "???";
        case WHILE: return "???";
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
