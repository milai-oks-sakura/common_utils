#ifndef COMMON_UTIL_OKS_TYPEDEF_EXTENSION_HPP
#define COMMON_UTIL_OKS_TYPEDEF_EXTENSION_HPP

// ===== C/CXX STANDARD LIBRARY =====
#include <list>
#include <memory>
// ===== THIRD LIBRARY =====

// ===== SELF LIBRARY =====
#include <common_utils/oks_typedef.hpp>
#include <utility>

namespace oks {

template <typename Context, typename Derived>
struct Observer : OksBase<Derived> {
  using Base = OksBase<Derived>;
  inline void update(const Context* context) {
    return this->derived().update_impl(context);
  };
};

template <typename Derived, typename Context>
struct Subject {
 public:
  Subject(const std::shared_ptr<Context>& context)
  : m_context(context){};

  ~Subject() = default;

  inline void add(const std::shared_ptr<Observer<Derived, Context>>& observer) {
    l_observer.push_back(observer);
  }

  inline void del(const std::shared_ptr<Observer<Derived, Context>>& observer) {
    l_observer.remove(observer);
  }

 protected:
  inline void notify() {
    for (auto& observer : l_observer) {
      observer->update(m_context.get());
    }
  }

 private:
  std::list<std::shared_ptr<Observer<Derived, Context>>> l_observer;

  std::shared_ptr<Context> m_context;
};

template <typename Derived>
struct Prototype : OksBase<Derived> {
 public:
  inline std::unique_ptr<Derived> clone() const {
    return this->derived().clone_impl();
  }
};

template <typename Product, typename Derived>
struct SimpleFactory : OksBase<Derived> {
  template <typename... Args>
  inline std::unique_ptr<Product> create(Args... args) {
    return this->derived().create_impl(args...);
  }
};

template <typename Product, typename Derived>
using Builder = SimpleFactory<Product, Derived>;

template <typename Notifier>
struct Decorator {
 public:
  Decorator(std::unique_ptr<Notifier> notifier)
  : m_notifier(notifier) {}

  ~Decorator() = default;

  inline Notifier* get() const {
    return m_notifier.get();
  }

  inline Notifier* operator->() const {
    return m_notifier.get();
  }

 protected:
  std::unique_ptr<Notifier> m_notifier;
};

template <typename Derived, typename Request>
struct Handler : OksBase<Derived> {
 public:
  inline void set_next(Handler* next) {
    m_next = next;
  }

  inline bool can_handle(const Request& request) const {
    return this->derived().can_handle_impl(request);
  }

  inline auto handle(const Request& request) -> decltype(std::declval<Derived>().handle_impl(request)) {
    if (can_handle(request)) {
      return this->derived().handle_impl(request);
    } else {
      if (m_next) {
        return m_next->handle(request);
      } else {
        return decltype(std::declval<Derived>().handle_impl(request)){};
      }
    }
  }

 protected:
  Handler* m_next = nullptr;
};

}  // namespace oks

#endif  // COMMON_UTIL_OKS_TYPEDEF_EXTENSION_HPP
