#include <iostream>

auto f(int x) {
  return ++x;
}

int main() {
  std::cout << f(10) << std::endl;
  return 0;
}
