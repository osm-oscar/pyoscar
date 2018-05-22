#include <pyoscar/ItemIndexStore.h>

#include <sserialize/Static/ItemIndexStore.h>

#include <boost/python.hpp>

namespace pyoscar {
namespace exporting {

void export_sserialize_Static_ItemIndexStore() {
	using namespace boost::python;
	using MyClass = sserialize::Static::ItemIndexStore;
	class_<MyClass>("ItemIndexStore")
		.def("size", &MyClass::size)
		.def("at", &MyClass::at)
	;
}

}} //end namespace pyoscar::exporting
