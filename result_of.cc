#include <iostream>
#include <type_traits>

template<class F>
typename std::result_of<F(int)>::type f(F& x) {
  std::cout << "callable\n";
  return x(0);
}

template<class T>
auto f(T x) {
  std::cout << "non-callable\n";
  return x;
}

int g(int x) {
  return 1;
}

int main() {
  f(g);
  f(1);
  return 0;
}
