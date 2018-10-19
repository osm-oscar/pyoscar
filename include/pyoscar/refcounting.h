#pragma once

#include <sserialize/utility/refcounting.h>
#include <memory>

namespace sserialize {

template<typename T>
T *
get_pointer(const sserialize::RCPtrWrapper<T> & p) {
  return const_cast<T*>(p.get());
}
	
} //end namespace sserialize

namespace std {

template<typename T>
T *
get_pointer(const std::shared_ptr<T> & p) {
  return const_cast<T*>(p.get());
}

} //end namespace std

// namespace boost {
// 
// template<typename T>
// T *
// get_pointer(const sserialize::RCPtrWrapper<T> & p) {
//   return const_cast<T*>(p.get());
// }
// 
// } //end namespace boost

#include <boost/python.hpp>

namespace boost {
namespace python {

template <typename T>
struct pointee< sserialize::RCPtrWrapper<T> > {
	typedef T type;
};

template <typename T>
struct pointee< std::shared_ptr<T> > {
	typedef T type;
};

}} //end namespace boost::python
