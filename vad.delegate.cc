#include <iostream>

// this class can only accept function pointer
template <class R, class... Args>
class dlgt {
  R (*_f)(Args...);
public:
  dlgt(R (*f)(Args...)): _f(f) {}
  R operator()(Args&&... args) { return (*_f)(std::forward<Args>(args)...); }
};
template <class R, class... Args>
dlgt<R, Args...> mk_dlgt(R (*f)(Args...)) { return dlgt<R, Args...>(f); }

char f() { return 1; }
int g(int x) { return x; }

int main() {
  auto d0 = mk_dlgt(&f);
  d0();
  return 0;
}
