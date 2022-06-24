namespace fae::ir::ast {

  using Name = fae::ir::Name;

  class Call;
  class Decl;
  class Expr;
  class If;
  class Op1;
  class Op2;
  class Op3;
  class Seq;
  class Stmt;
  class Var;

  class Expr {
  public:
    enum class Tag : u8;

    Tag tag;

    explicit Expr(Tag tag) : tag(tag) { }
  };

  enum class Expr::Tag : u8 {
    CALL,
    IF,
    OP1,
    OP2,
    OP3,
    VARIABLE,
  };

  using enum Expr::Tag;

  class Op1 : public Expr {
  public:
    Name name;
    Expr * arg;

    explicit Op1(Name name, Expr * arg) : Expr(OP1), name(name), arg(arg) { }
  };

  class Op2 : public Expr {
  public:
    Name name;
    Expr * arg0;
    Expr * arg1;

    explicit Op2(Name name, Expr * arg0, Expr * arg1) :
      Expr(Expr::Tag::OP2),
      name(name),
      arg0(arg0),
      arg1(arg1)
    { }
  };
}
