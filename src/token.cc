namespace token {
  enum class Tag : u8 {
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
}

namespace token::tag {
  char const * ToString(Tag tag) {
    switch (tag) {
      case Tag::STOP: return "STOP";
      case Tag::ILLEGAL: return "ILLEGAL";
      case Tag::IDENTIFIER: return "IDENTIFIER";
      case Tag::NUMBER: return "NUMBER";
      case Tag::STRING: return "STRING";
      case Tag::COLON: return "COLON";
      case Tag::COMMA: return "COMMA";
      case Tag::DOT: return "DOT";
      case Tag::SEMICOLON: return "SEMICOLON";
      case Tag::LPAREN: return "LPAREN";
      case Tag::LPAREN_NOSPACE: return "LPAREN_NOSPACE";
      case Tag::LBRACKET: return "LBRACKET";
      case Tag::LBRACKET_NOSPACE: return "LBRACKET_NOSPACE";
      case Tag::LBRACE: return "LBRACE";
      case Tag::RPAREN: return "RPAREN";
      case Tag::RBRACKET: return "RBRACKET";
      case Tag::RBRACE: return "RBRACE";
      case Tag::ASSIGN: return "ASSIGN";
      case Tag::EQ: return "EQ";
      case Tag::NE: return "NE";
      case Tag::LT: return "LT";
      case Tag::GT: return "GT";
      case Tag::LE: return "LE";
      case Tag::GE: return "GE";
      case Tag::PLUS: return "PLUS";
      case Tag::MINUS: return "MINUS";
      case Tag::STAR: return "STAR";
      case Tag::SLASH: return "SLASH";
      case Tag::AMPERSAND: return "AMPERSAND";
      case Tag::AT: return "AT";
      case Tag::BANG: return "BANG";
      case Tag::CARET: return "CARET";
      case Tag::DOLLAR: return "DOLLAR";
      case Tag::PERCENT: return "PERCENT";
      case Tag::PIPE: return "PIPE";
      case Tag::QUERY: return "QUERY";
      case Tag::TILDE: return "TILDE";
      case Tag::AND: return "AND";
      case Tag::BREAK: return "BREAK";
      case Tag::ELIF: return "ELIF";
      case Tag::ELSE: return "ELSE";
      case Tag::END: return "END";
      case Tag::FOR: return "FOR";
      case Tag::FUN: return "FUN";
      case Tag::IF: return "IF";
      case Tag::LET: return "LET";
      case Tag::LOOP: return "LOOP";
      case Tag::OR: return "OR";
      case Tag::RETURN: return "RETURN";
      case Tag::WHILE: return "WHILE";
    }

    return "???";
  }
}

struct Token {
  token::Tag tag;
  char const * start;
  char const * stop;
};

namespace token {
  Token Make(Tag tag, char const * start, char const * stop) {
    return { tag, start, stop };
  }

  void Print(Token const & tok) {
    printf(
        "%s: \"%.*s\"\n",
        token::tag::ToString(tok.tag),
        static_cast<int>(tok.stop - tok.start),
        tok.start
      );
  }
}

