namespace lexer {
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
