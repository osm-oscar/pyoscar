#include <pyoscar/OsmKeyValueObjectStore.h>

#include <liboscar/OsmKeyValueObjectStore.h>

#include <sserialize/spatial/DistanceCalculator.h>

#include <boost/python.hpp>

namespace pyoscar {
namespace exporting {
	
namespace { //protecting namespace
	
std::string print_item(const liboscar::Static::OsmKeyValueObjectStoreItem & item) {
	std::stringstream ss;
	item.print(ss, false);
	return ss.str();
}

uint32_t findKey_item(const liboscar::Static::OsmKeyValueObjectStoreItem & item, const std::string & key) {
	return item.findKey(key);
}

uint32_t findValue_item(const liboscar::Static::OsmKeyValueObjectStoreItem & item, const std::string & value) {
	return item.findValue(value);
}

uint32_t hasKey_item(const liboscar::Static::OsmKeyValueObjectStoreItem & item, const std::string & key) {
	return item.findKey(key) < item.npos;
}

sserialize::spatial::GeoRect boundary_item(const liboscar::Static::OsmKeyValueObjectStoreItem & item) {
	return item.geoShape().boundary();
}

double distance_item(const liboscar::Static::OsmKeyValueObjectStoreItem & item, const liboscar::Static::OsmKeyValueObjectStoreItem & other) {
	sserialize::spatial::DistanceCalculator dc( sserialize::spatial::DistanceCalculator::DCT_GEODESIC_FAST );
	return item.geoShape().get()->distance(*(other.geoShape().get()), dc);
}

}//end protecting namespace

void export_liboscar_Static_OsmKeyValueObjectStoreItem() {
	using namespace boost::python;
	using MyClass = liboscar::Static::OsmKeyValueObjectStoreItem;
	
	typedef std::string (MyClass:: *ValueByPos)(uint32_t) const;
	typedef std::string (MyClass:: *ValueByKey)(const std::string&) const;
	
	ValueByPos valueByPos = &MyClass::value;
	ValueByKey valueByKey = &MyClass::value; 
	
	class_<MyClass>("OsmKeyValueObjectStoreItem")
		.def("id", &MyClass::id)
		.def("isRegion", &MyClass::isRegion)
		.def("osmId", &MyClass::osmId)
		.def("dump", &MyClass::dump)
		.def("__str__", &print_item)
		.def("bbox", &boundary_item)
		.def("size", &MyClass::size, "Number of tags")
		.def("key", &MyClass::key, "Return key at position i")
		.def("value", valueByPos, "Return value at position i")
		.def("value", valueByKey, "Return value by key, empty if not present")
		.def("findKey", &findKey_item, "Return index of key, 0xFFFFFFFF if not present")
		.def("findValue", &findValue_item, "Return index of value, 0xFFFFFFFF if not present")
		.def("hasKey", &hasKey_item, "true iff item has the specified key")
		.def("distance", &distance_item, "Approximate distance to the given item in meters")
	;
}

void export_liboscar_Static_OsmKeyValueObjectStore() {
	using namespace boost::python;
	using MyClass = liboscar::Static::OsmKeyValueObjectStore;
	class_<MyClass>("OsmKeyValueObjectStore")
		.def("size", &MyClass::size)
		.def("at", &MyClass::at)
		.def("graph", &MyClass::geoHierarchy, return_value_policy<copy_const_reference>())
	;
}
	
}} //end namespace pyoscar::exporting
