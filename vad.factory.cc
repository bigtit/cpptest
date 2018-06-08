#include <iostream>

template <class T, class... Args>
T* get_inst(Args... args) { return new T(std::forward<Args>(args)...); }

struct A {
  A(int) {}
};
struct B {
  B(double) {}
};
struct C {
  C(char, int, double) {}
};

int main() {
  auto pa = get_inst<A>(1);
  auto pb = get_inst<B>(1.1);
  auto pc = get_inst<C>(1, 1, 1.1);
  return 0;
}
