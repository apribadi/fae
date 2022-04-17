namespace token {
  namespace tag {
    enum class t : u8 {
      // misc

      END_OF_FILE,
      ILLEGAL_CHARACTER,

      IDENTIFIER,
      INTEGER,
      DECIMAL,

      // operators

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

      // keywords

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
  }

  class t {
  public:
    tag::t tag;
    char * start;
    char * stop;
  };
}
