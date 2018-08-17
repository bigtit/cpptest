#include <iostream>

template <class T>
using func = void(*)(T, T);

void ff(int, int) { return; }
void gg(char, char) { return; }

func<int> f = ff;
func<char> g = gg;
func<double> h = [](double, double){ return; };

int main() {
  f(1,1);
  g(1,1);
  return 0;
}
