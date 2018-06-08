#include <iostream>

class singleton {
  int data;
  singleton(): data(0) {}
  ~singleton() { std::cout << "singleton destructor\n"; }
public:
  singleton(const singleton&) = delete;
  singleton& operator=(const singleton&) = delete;

  static singleton& get_inst() {
    static singleton inst; // one object per class
    return inst;
  }
  int get_value() { return data; }
  int set_value(int x) { return data = x; }
};

int main() {
  {
    auto& s = singleton::get_inst();
    auto& t = singleton::get_inst();
    s.set_value(9);
    std::cout << t.get_value();
  }
  std::cout << "hello\n";
  return 0;
}
