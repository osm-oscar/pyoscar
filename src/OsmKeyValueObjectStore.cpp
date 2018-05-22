#include <pyoscar/OsmKeyValueObjectStore.h>

namespace pyoscar {
namespace exporting {
	
void export_liboscar_Static_OsmKeyValueObjectStore() {
	using namespace boost::python;
	class_<liboscar::Static::OsmKeyValueObjectStore>("OsmKeyValueObjectStore")
		.def("size", &liboscar::Static::OsmKeyValueObjectStore::size)
		.def("at", &liboscar::Static::OsmKeyValueObjectStore::at)
	;
}
	
}} //end namespace pyoscar::exporting
