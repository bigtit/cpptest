#include <iostream>
#include <type_traits>

template <class F>
class ff {
public:
  using fntype = typename std::decay<F>::type;
  ff(F& f): fn(f) {}
  void run() { fn(); }
private:
  fntype fn;
};

int g() {
  std::cout << "invoke g()\n";
  return 1;
}
class A {
public:
  static void g() { std::cout << "invoke A::g\n"; }
};

int main() {
  ff<decltype(g)> x(g);
  x.run();
  ff<decltype(A::g)> y(A::g);
  y.run();
  return 0;
}
