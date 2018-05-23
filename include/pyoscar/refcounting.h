#pragma once

#include <sserialize/utility/refcounting.h>

namespace sserialize {

template<typename T>
T *
get_pointer(const sserialize::RCPtrWrapper<T> & p) {
  return const_cast<T*>(p.get());
}
	
} //end namespace sserialize


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

}} //end namespace boost::python
