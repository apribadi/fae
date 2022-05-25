namespace fae::data::ast {

using Name = fae::data::name::Name;

class Expr {
public:
  enum class Tag : u8;

  class Base;
  class Call;
  class Variable;

  explicit Expr(Tag, Base *);
  explicit Expr(Call *);
  explicit Expr(Variable *);

  Base * operator->();

  Tag tag();
  Base * ptr();
  template<class T> T * as();

private:
  uintptr_t value;
};

enum class Expr::Tag : u8 {
  CALL,
  VARIABLE,
};

class alignas(8) Expr::Base {
};

class Expr::Call : public Expr::Base {
public:
  u8 arity;
  Name name;
  Expr args[];

  explicit Call(u8 arity, Name name) : arity(arity), name(name) { }

  explicit Call(Name name, Expr arg0) : Call(1, name) {
    args[0] = arg0;
  }

  explicit Call(Name name, Expr arg0, Expr arg1) : Call(2, name) {
    args[0] = arg0;
    args[1] = arg1;
  }
};

class Expr::Variable : public Expr::Base {
  Name name;
};

Expr::Expr(Tag tag, Base * ptr) {
  static_assert(alignof(Base) >= 8);

  uintptr_t p = reinterpret_cast<uintptr_t>(ptr);
  uintptr_t q = static_cast<uintptr_t>(tag);

  value = p | q;
}

Expr::Expr(Call * ptr) : Expr(Tag::CALL, static_cast<Base *>(ptr)) { }

Expr::Expr(Variable * ptr) : Expr(Tag::VARIABLE, static_cast<Base *>(ptr)) { }

Expr::Tag Expr::tag() {
  return static_cast<Tag>(value & 0x7);
}

Expr::Base * Expr::ptr() {
  return reinterpret_cast<Base *>(value & ~0x7);
}

Expr::Base * Expr::operator->() {
  return ptr();
}

template<class T>
T * Expr::as() {
  return static_cast<T *>(ptr());
}

class Stmt {
};

}
