// an ugly functor wrapper/delegate
// can accept function ptr/lambda/class with overloaded () operator
#include <iostream>
#include <utility>
#include <memory>

// okay, the basic idea is that when we create a func object using: regular function ptr/lambda/c++ functor
// we have to save something inside our func object,
// and we should make the `something` run
//
// a simple idea is that we save the pointer of these 3 kinds of method
// but how can we run it?
// so the `something` should not be a bare pointer but with the information about these methods
//
// another thing is:
// we run the func object by () operator
// thus we send args into () operator
// then the internal `something` should obtain these args and run
//
// the idea that use R and Args... instead of direct T is
// it's very hard to deduce return and args type from T
//
// here is the idea:
// we have to store R, Args..., as well as T the raw type of function
// but for func class, as a wrapper, we only show R and Args
// thus we have to store T inside func, resulting in nested template inside
// and to discard T outside, we have to use function templates to automatically deduce T from the function
// intuitively, constructor is a good one for this purpose
// additionally, since T should be inside func class, we have to wrap the function as a class,
// which can use T as template arguments, otherwise we have to write T in the top template arguments to be not ok

// while it's not that elegant we have to give two types of information when create a func object:
// 1. class template to provide R and Args, for () operator
// 2. raw function to give T, to call the actual functionality
// which makes sense since T can be function pointer, lambda or functor
// and 1. is the formalised representation of the raw function, while 2. is the actual type
// in words, the workaround with three different types of function objects is because:
// it's hard to deduce return and argument types from types of them by a general method

// just a declaration
template <class> class func;
// partial specialization
template <class R, class... Args> class func<R(Args...)> {
  public:
    class ffunc0 {
      public:
        virtual ~ffunc0() = default;
        virtual R run(Args...) = 0;
    };
    template <class F> class ffunc: public ffunc0 {
      public:
        ffunc(const F& f): _f(f) {}
        ~ffunc() {}
        R run(Args... args) { return _f(std::forward<Args>(args)...); }
      private: // private is ok even if we define _fp as its superclass, since superclass is virtual
               //we can confirm that _fp is in derived class thus has private _f member
        F _f; // actual funtor stored here so that we can match any functor using F
    };
    // notice that T is the type of functor, kind of redundant here
    func() = delete;
    template <class F> func(F f) { _fp = std::make_shared<ffunc<F>>(f); }
    // func(const func& f): _fp(f._fp) {}
    // func& operator=(const func& f) { _fp = f._fp; return *this; }
    R operator()(Args... args) { return _fp->run(std::forward<Args>(args)...); }
  private:
    // the problem is we do not know how to instantiate ffunc without F before we get any functor
    // a solution is create a superclass that does not use template
    //
    // another problem is raw pointer cannot free automatically, resulting in a dangling pointer
    // thus use shared_ptr instead
    std::shared_ptr<ffunc0> _fp;
};

// test codes
int f0() { std::cout << "f0: function pointer\n"; return 0; }
auto f1 = [](char){ std::cout << "f1: lambda\n"; return 1.0; };
struct f2 {
  int operator()(double) { std::cout << "f2: class functor\n"; return 0; }
};

int main() {
  func<int()> fn0(f0);
  func<double(char)> fn1(f1);
  func<int(double)> fn2(f2{});
  fn0();
  fn1(1);
  fn2(1.0);
  return 0;
}
