#include <pyoscar/GeoHierarchy.h>

#include <sserialize/Static/GeoHierarchy.h>

#include <boost/python.hpp>

namespace pyoscar {
namespace exporting {
	
// void export_sserialize_Static_spatial_GeoHierarchy_SubSetNode() {
// 	using namespace boost::python;
// 	using MyClass = sserialize::Static::spatial::detail::SubSet::Node;
// 	class_<MyClass, MyClass::NodePtr>("GeoHierarchySubSetNode")
// 		.def("graphId", &MyClass::ghId)
// 		.def("size", &MyClass::size)
// 		.def("at", &MyClass::at)
// 		.def("maxItemsSize", &MyClass::maxItemsSize)
// 		.def("__iter__", iterator<MyClass>())
// 	;
// }

void export_sserialize_Static_spatial_GeoHierarchy_SubSet() {
	using namespace boost::python;
	using MyClass = sserialize::Static::spatial::detail::SubSet;
	class_<MyClass>("GeoHierarchySubSet")
		.def("cells", &MyClass::cqr, return_value_policy<copy_const_reference>())
// 		.def("graph", &MyClass::root)
		.def("items", &MyClass::items)
	;
}

void export_sserialize_Static_spatial_GeoHierarchy_Cell() {
	using namespace boost::python;
	using MyClass = sserialize::Static::spatial::detail::Cell;
	class_<MyClass>("GeoHierarchyCell")
		.def("itemCount", &MyClass::itemCount)
		.def("ancestorCount", &MyClass::parentsSize)
		.def("ancestorId", &MyClass::parent)
	;
}

void export_sserialize_Static_spatial_GeoHierarchy_Region() {
	using namespace boost::python;
	using MyClass = sserialize::Static::spatial::detail::Region;
	class_<MyClass>("GeoHierarchyRegion")
		.def("itemsCount", &MyClass::itemsCount)
		.def("childrenCount", &MyClass::childrenSize)
		.def("ancestorCount", &MyClass::parentsSize)
		.def("ancestorId", &MyClass::parent)
		.def("childId", &MyClass::child)
	;
}

void export_sserialize_Static_spatial_GeoHierarchy() {
	using namespace boost::python;
	using MyClass = sserialize::Static::spatial::GeoHierarchy;
	class_<MyClass>("GeoHierarchy")
		.def("numberOfRegions", &MyClass::regionSize)
		.def("numberOfCells", &MyClass::cellSize)
		.def("region", &MyClass::region)
		.def("cell", &MyClass::cell)
		.def("regionFromItemId", &MyClass::regionFromStoreId)
		.def("regionId2ItemId", &MyClass::storeIdToGhId)
	;
}

}} //end namespace pyoscar::exporting
