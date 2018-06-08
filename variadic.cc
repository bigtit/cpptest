#include <iostream>

void p() { std::cout << '\n'; }
template <class T, class... U>
void p(T t, U... u) { std::cout << "p: " << t << std::endl; p(u...); }

template <class T>
T sum(T t) { return t; }
template <class T, class... Ts>
T sum(T t, Ts... ts) { return t+sum<T>(ts...); }

template <class T>
void pa(T t) { std::cout << t << std::endl; }
template <class... Ts>
void expand(Ts... ts) { int arr[] = {(pa(ts), 0)...}; }

template <class T, class... Ts>
struct tsize: std::integral_constant<int, tsize<T>::value + tsize<Ts...>::value> {};
template <class T>
struct tsize<T>: std::integral_constant<int, sizeof(T)> {};

template <int...>
struct idxseq {};
template <int N, int... Idxs>
struct makeidx: makeidx<N-1, N-1, Idxs...> {};
template <int... Idxs>
struct makeidx<0, Idxs...> { using type = idxseq<Idxs...>; }; // partial specialization

template <int N, int... Idxs>
struct makeidx2 { using type = typename makeidx2<N-1, N-1, Idxs...>::type;  };
template <int... Idxs>
struct makeidx2<0, Idxs...> { using type = idxseq<Idxs...>; };

// first specialize to the most specific pattern then others
template <size_t a, size_t... r>
struct intmax: std::integral_constant<size_t, a>=intmax<r...>::value? a: intmax<r...>::value> {};
template <size_t a>
struct intmax<a>: std::integral_constant<size_t, a> {};

// template <size_t a, size_t...>
// struct intmax2: std::integral_constant<size_t, a> {};
// when invoke <a1, r...>, compiler cannot fit it into <a> case???
template <size_t a1, size_t a2, size_t... r>
struct intmax2<a1, a2, r...>: std::integral_constant<size_t, (a1>a2? intmax2<a1, r...>::value: intmax2<a2, r...>::value)> {};
// template <size_t a>
// struct intmax2<a>: std::integral_constant<size_t, a> {};

int main() {
  p(1,2,3,4);
  std::cout << sum(1,2,3,4,5) << std::endl;
  expand(1,2,3,4);
  std::cout << tsize<int, double, char, short, int>::value << std::endl;
  using T = makeidx<4>::type;
  std::cout << typeid(T).name() << std::endl;
  using T2 = makeidx2<4>::type;
  std::cout << typeid(T2).name() << std::endl;

  std::cout << intmax<2,5,1,7>::value << std::endl;
  std::cout << intmax2<2,5,1,7>::value << std::endl;

  return 0;
}
