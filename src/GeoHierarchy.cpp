#include <pyoscar/GeoHierarchy.h>

#include <sserialize/Static/GeoHierarchy.h>

#include <boost/python.hpp>

namespace pyoscar {
namespace exporting {

void export_sserialize_Static_spatial_GeoHierarchy() {
	using namespace boost::python;
	using MyClass = sserialize::Static::spatial::GeoHierarchy;
	class_<MyClass>("GeoHierarchy")
		.def("regionsSize", &MyClass::regionsSize)
		.def("region", &MyClass::region)
		.def("region", &MyClass::region)
		.def("cell", &MyClass::cell)
	;
}

void export_sserialize_Static_spatial_GeoHierarchy_SubSet();
void export_sserialize_Static_spatial_GeoHierarchy_Region();
void export_sserialize_Static_spatial_GeoHierarchy_Cell();

}} //end namespace pyoscar::exporting
