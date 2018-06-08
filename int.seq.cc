#include <iostream>
#include <type_traits>

template <int... ns>
struct seq0 {};
template <int... ns>
struct seq_gen;
template <int i, int... ns>
struct seq_gen<i, ns...> { using type = typename seq_gen<i-1, i-1, ns...>::type; };
template <int... ns>
struct seq_gen<0, ns...> { using type = seq0<ns...>; };
// user interface
template <int n>
using seq_t = typename seq_gen<n>::type;

int main() {
  // complexity is O(n) not very efficient
  std::cout << typeid(seq_t<10>).name() << std::endl;

  return 0;
}
