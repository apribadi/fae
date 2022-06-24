namespace fae::ir {
  struct Token {
    enum class Tag : u8;

    Tag tag;
    char * start;
    char * stop;

    explicit Token(Tag, char *, char *);
    void print();
  };

  enum class Token::Tag : u8 {
    // special

    STOP,
    ILLEGAL,

    // identifier

    IDENTIFIER,

    // literal

    NUMBER,
    STRING,

    // punctuation

    COLON,            // :
    COMMA,            // ,
    DOT,              // .
    SEMICOLON,        // ;
    LPAREN,           // (
    LPAREN_NOSPACE,   // (
    LBRACKET,         // [
    LBRACKET_NOSPACE, // [
    LBRACE,           // {
    RPAREN,           // )
    RBRACKET,         // ]
    RBRACE,           // }

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
    RETURN,
    WHILE,
  };

  Token::Token(Tag tag, char * start, char * stop) : tag(tag), start(start), stop(stop) { }
}

namespace fae::ir::token::internal {
  char const * to_string(Token::Tag tag) {
    using enum Token::Tag;

    switch (tag) {
      case STOP: return "STOP";
      case ILLEGAL: return "ILLEGAL";
      case IDENTIFIER: return "IDENTIFIER";
      case NUMBER: return "NUMBER";
      case STRING: return "STRING";
      case COLON: return "COLON";
      case COMMA: return "COMMA";
      case DOT: return "DOT";
      case SEMICOLON: return "SEMICOLON";
      case LPAREN: return "LPAREN";
      case LPAREN_NOSPACE: return "LPAREN_NOSPACE";
      case LBRACKET: return "LBRACKET";
      case LBRACKET_NOSPACE: return "LBRACKET_NOSPACE";
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
      case RETURN: return "RETURN";
      case WHILE: return "WHILE";
    }

    return "???";
  }
}

namespace fae::ir::token {
  void print(Token & tok) {
    printf(
        "%s: \"%.*s\"\n",
        internal::to_string(tok.tag),
        static_cast<int>(tok.stop - tok.start),
        tok.start
      );
  }
}
