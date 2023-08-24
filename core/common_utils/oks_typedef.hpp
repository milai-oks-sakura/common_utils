#ifndef COMMON_UTIL_OKS_TYPEDEF_HPP
#define COMMON_UTIL_OKS_TYPEDEF_HPP

namespace oks {

/**
 * @struct noncopyable
 * @brief 不可拷贝
 */
struct noncopyable {
 protected:
  noncopyable()                    = default;
  ~noncopyable()                   = default;
  noncopyable(const noncopyable &) = delete;
  noncopyable(noncopyable &&)      = delete;
  noncopyable &operator=(const noncopyable &) = delete;
  noncopyable &operator=(noncopyable &&) = delete;
};

/**
 * @struct Singleton
 * @brief 单例
 * @tparam Derived 派生类
 */
template <typename Derived>
struct Singleton : noncopyable {
 public:
  static Derived *Instance() {
    static Derived result;
    return &result;
  }

 protected:
  ~Singleton() = default;
  Singleton()  = default;
};

/**
 * @struct OksBase
 * @brief 基础模型
 * @tparam Derived 派生类
 */
template <typename Derived>
struct OksBase {
  OksBase()  = default;
  ~OksBase() = default;

  inline Derived &derived() {
    return *static_cast<Derived *>(this);
  }
  inline Derived &derived() const {
    return *static_cast<const Derived *>(this);
  }
  inline const Derived &const_derived() const {
    return *static_cast<const Derived *>(this);
  }
  inline Derived &cast_derived() const {
    return *const_cast<Derived *>(static_cast<const Derived *>(this));
  }
};

/**
 * @struct OksChild
 * @brief 对象树模型
 * @tparam Parent 父节点
 * @ref QT对象树模型
 */
template <typename Parent>
struct OksChild {
  OksChild(Parent *parent)
  : m_parent(parent) {}

  ~OksChild() = default;

 protected:
  Parent *m_parent;
};

template <typename Derived>
struct OksTrait;

}  // namespace oks

#endif  // COMMON_UTIL_OKS_TYPEDEF_HPP
