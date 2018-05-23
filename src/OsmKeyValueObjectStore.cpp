#include <pyoscar/OsmKeyValueObjectStore.h>

#include <liboscar/OsmKeyValueObjectStore.h>

#include <boost/python.hpp>

namespace pyoscar {
namespace exporting {
	
namespace { //protecting namespace
	
std::string print_item(const liboscar::Static::OsmKeyValueObjectStoreItem & item) {
	std::stringstream ss;
	item.print(ss, false);
	return ss.str();
}

}//end protecting namespace

void export_liboscar_Static_OsmKeyValueObjectStoreItem() {
	using namespace boost::python;
	using MyClass = liboscar::Static::OsmKeyValueObjectStoreItem;
	class_<MyClass>("OsmKeyValueObjectStoreItem")
		.def("id", &MyClass::id)
		.def("isRegion", &MyClass::isRegion)
		.def("osmId", &MyClass::osmId)
		.def("dump", &MyClass::dump)
		.def("__str__", &print_item)
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
