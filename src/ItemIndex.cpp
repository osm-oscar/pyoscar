#include <pyoscar/ItemIndex.h>

#include <sserialize/containers/ItemIndex.h>

#include <boost/python.hpp>

namespace pyoscar {
namespace exporting {

void export_sserialize_ItemIndex() {
	using namespace boost::python;
	using MyClass = sserialize::ItemIndex;
	class_<MyClass>("ItemIndex")
		.def("size", &MyClass::size)
		.def("at", &MyClass::at)
		.def("__iter__", iterator<MyClass>())
	;
}

}} //end namespace pyoscar::exporting
