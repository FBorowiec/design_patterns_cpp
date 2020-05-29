#include <iostream>
#include <memory>
#include <string>

namespace structural {
namespace bridge_pattern {

template <typename T>
class Pimpl {
 public:
  Pimpl();

  template <typename... Args>
  Pimpl(Args&&... args);

  ~Pimpl();

  T* operator->();
  T& operator*();

 private:
  std::unique_ptr<T> impl;
};

// Important NOT to have the implementation details in the header file but hide it from the consumer in a cpp file----|

template <typename T>
Pimpl<T>::Pimpl() : impl(new T) {}

template <typename T>
template <typename... Args>
Pimpl<T>::Pimpl(Args&&... args) : impl(new T{std::forward<Args>(args)...}) {}

template <typename T>
Pimpl<T>::~Pimpl() {}

template <typename T>
T* Pimpl<T>::operator->() {
  return *impl.get();
}

template <typename T>
T& Pimpl<T>::operator*() {
  return impl.get();
}

// Consumer
class Foo {
 public:
  class Impl;

 private:
  Pimpl<Impl> impl;
};

class Foo::Impl {
  // implementation details
};

}  // namespace bridge_pattern
}  // namespace structural
