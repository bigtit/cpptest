#include <iostream>
#include <type_traits>

template<class F>
typename std::enable_if<std::is_function<typename std::remove_all_extents<F>::type>::value, void>::type f(F& x) {
  std::cout << "callable\n";
  auto a = x(0);
}

template<class T>
typename std::enable_if<std::is_arithmetic<T>::value, T>::type f(T x) {
  std::cout << "non-callable\n";
  return x;
}

int g(int x) {
  std::cout << "invoke g\n";
  return 1;
}

int main() {
   f(g);
  // std::cout << std::is_function<decltype(g)>::value << std::endl;

  f(1);
  return 0;
}
