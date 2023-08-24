#ifndef COMMON_UTIL_OKS_PYTHON_HPP
#define COMMON_UTIL_OKS_PYTHON_HPP

#include <Python.h>
#include <object.h>

namespace oks {

template <typename Derived>
struct PythonBase : PyObject {
  static PyMethodDef*  methods();
  static PyTypeObject* cls();
};

}  // namespace oks

#endif  // COMMON_UTIL_OKS_PYTHON_HPP
