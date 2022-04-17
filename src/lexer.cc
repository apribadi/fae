namespace lexer {
  namespace category {
    enum class t : u8 {
      ANGLE,
      COLON,
      DIGIT,
      DOT,
      EQUAL,
      ILLEGAL,
      LETTER,
      NIL,
      OPERATOR,
      QUOTE,
      SPACE,
    };

    using enum t;

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
        case NIL: return "NIL";
        case OPERATOR: return "OPERATOR";
        case QUOTE: return "QUOTE";
        case SPACE: return "SPACE";
      }

      return "???";
    }

    constexpr array<t, 256> of_byte = {
      NIL,
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

    // TODO: reorder, because we need to
    // exclude spaces and comments from the
    // token.

    enum class t {
      START,
      ANGLE,
      COLON,
      DOT,
      IDENTIFIER,
      ILLEGAL,
      INTEGER,
      COMPLETE_IDENTIFIER,
      COMPLETE_INTEGER,
      COMPLETE_OPERATOR,
      COMPLETE_OPERATOR_ADVANCE,
      COMPLETE_ILLEGAL,
      STOP,
    };

    using enum t;

    constexpr size_t NONTERMINAL_COUNT = 7;
    constexpr size_t COUNT = 12;

    constexpr array<array<t, category::COUNT>, NONTERMINAL_COUNT> transition = {
      // START ->
      {
        ANGLE,
        COLON,
        INTEGER,
        DOT,
        EQUAL,
        ILLEGAL,
        IDENTIFIER,
        STOP,
        COMPLETE_OPERATOR,
        ILLEGAL,
        START,
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

      {
      },

      {
      },

      {
      },
    }
  }

  namespace dispatch {
    class t {
    private:
      array<category::t, 256> _of_byte = category::of_byte;

    public:
      category::t of_byte(byte x) const {
        return _of_byte[static_cast<size_t>(x)];
      }
    };
  }

  constexpr dispatch::t my_dispatch;

  class t {
  private:
    byte * start;
    byte * stop;
    byte * current;

  public:
    t(span<byte> source) :
      start(&source.front()),
      stop(&source.front() + source.size()),
      current(&source.front())
    {
      assert(source.size() > 0);
      assert(source[source.size() - 1] == byte(0));
    }
  };
}
