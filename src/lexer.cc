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
      ILLEGAL, 

      ILLEGAL, // 128
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
      ILLEGAL,
    };
  }

  namespace dispatch {
    class t {
    public:
      array<category::t, 256> category_of_byte;
    };
  }

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
