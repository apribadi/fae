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
    enum class Tag : u8 {
      CALL,
      IF,
      OP1,
      OP2,
      OP3,
      VARIABLE,
    };

    Tag const tag;

    explicit Expr(Tag tag) : tag(tag) { }
  };

  class Op1 : public Expr {
  public:
    Name const name;
    Expr const * const arg;

    explicit Op1(Name name, Expr const * arg) :
      Expr(Expr::Tag::OP1),
      name(name),
      arg(arg)
    { }
  };

  class Op2 : public Expr {
  public:
    Name const name;
    Expr const * const arg0;
    Expr const * const arg1;

    explicit Op2(Name name, Expr const * arg0, Expr const * arg1) :
      Expr(Expr::Tag::OP2),
      name(name),
      arg0(arg0),
      arg1(arg1)
    { }
  };
}
