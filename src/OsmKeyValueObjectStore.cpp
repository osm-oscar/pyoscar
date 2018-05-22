#include <pyoscar/OsmKeyValueObjectStore.h>

#include <liboscar/OsmKeyValueObjectStore.h>

#include <boost/python.hpp>

namespace pyoscar {
namespace exporting {

void export_liboscar_Static_OsmKeyValueObjectStoreItem() {
	using namespace boost::python;
	using MyClass = liboscar::Static::OsmKeyValueObjectStoreItem;
	class_<MyClass>("OsmKeyValueObjectStoreItem")
		.def("id", &MyClass::id)
		.def("isRegion", &MyClass::isRegion)
		.def("osmId", &MyClass::osmId)
		.def("dump", &MyClass::dump)
	;
}

void export_liboscar_Static_OsmKeyValueObjectStore() {
	using namespace boost::python;
	using MyClass = liboscar::Static::OsmKeyValueObjectStore;
	class_<MyClass>("OsmKeyValueObjectStore")
		.def("size", &MyClass::size)
		.def("at", &MyClass::at)
	;
}
	
}} //end namespace pyoscar::exporting
