#include <pyoscar/StaticOsmCompleter.h>
#include <liboscar/StaticOsmCompleter.h>

namespace pyoscar {
namespace exporting {
	
	
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(liboscar_Static_OsmCompleter_energize_overloads, energize, 0, 1);
	
void export_liboscar_Static_OsmCompleter() {
	using namespace boost::python;
	using MyClass = liboscar::Static::OsmCompleter;
	
	typedef sserialize::Static::spatial::GeoHierarchy::SubSet (MyClass:: *ClusteredCompleteMemFn)(std::string const &);
	
	ClusteredCompleteMemFn clusteredCompleteMemFn = &MyClass::clusteredComplete;
	
	
	class_<MyClass>("OsmCompleter")
		.def("setDataPath", &MyClass::setAllFilesFromPrefix, "Set the path to the data")
		.def("energize", &MyClass::energize, liboscar_Static_OsmCompleter_energize_overloads())
		.def("store", &MyClass::store, return_value_policy<copy_const_reference>(), "data base")
		.def("idxStore", &MyClass::indexStore, return_value_policy<copy_const_reference>(), "Index data base")
		.def("query", clusteredCompleteMemFn, "Issue a query") 
	;
}

}} //end n
