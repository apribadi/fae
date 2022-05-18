namespace fae::ast {

using Name = name::Name;

class Expr {
public:
  enum class Tag : u8;

  class Base;
  class Call;
  class Variable;

  explicit Expr(Call *);
  explicit Expr(Variable *);

  Base * operator->();

private:
  uintptr_t value;

  template<class T> explicit Expr(Tag, T *);
};

enum class Expr::Tag : u8 {
  CALL,
  VARIABLE,
};

class Expr::Base {
};

class Expr::Call : public Expr::Base {
  Name fun;
  Expr params[];
};

class Expr::Variable : public Expr::Base {
  Name name;
};

template<class T>
Expr::Expr(Tag tag, T * ptr) {
  static_assert(alignof(T) >= 8);

  uintptr_t p = reinterpret_cast<uintptr_t>(static_cast<Base *>(ptr));
  uintptr_t q = static_cast<uintptr_t>(tag);

  value = p | q;
}

Expr::Expr(Call * ptr) : Expr(Tag::CALL, ptr) { }
Expr::Expr(Variable * ptr) : Expr(Tag::VARIABLE, ptr) { }

}
