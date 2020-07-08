// check if a derived type is a sub-type of a template
#include <iostream>

// B is not a type, B<T> is
template <typename T>
struct B {};

struct D: B<int> {};

// D is a type, but B is still not a type
template <typename D, template<typename...> typename B>
struct tmp0 {
  using U = typename std::remove_cv<D>::type;
  template <typename... T>
  static std::true_type test(B<T...>*);
  static std::false_type test(void*);
  using type = decltype(test(std::declval<U*>()));
};
template <typename D, template<typename...> typename B>
using tmp1 = typename tmp0<D, B>::type;
template <typename D, template<typename...> typename B>
constexpr bool is_subclass_template = tmp1<D, B>::value;

int main() {
  D d;
  std::cout << is_subclass_template<decltype(d), B>;
  // should print out true or 1
}
