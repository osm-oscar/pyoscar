#include <pyoscar/GeoRect.h>

#include <sserialize/spatial/GeoRect.h>

#include <boost/python.hpp>

namespace pyoscar {
namespace exporting {
	
namespace {
std::string print_GeoRect(sserialize::spatial::GeoRect const & x) {
	std::stringstream ss;
	ss << x;
	return ss.str();
}

}//protecting namespace

void export_sserialize_spatial_GeoRect() {
	using namespace boost::python;
	using MyClass = sserialize::spatial::GeoRect;
	
	typedef bool (MyClass:: *ContainsPoint)(double, double) const;
	typedef bool (MyClass:: *ContainsGeoRect)(MyClass const &) const;
	
	ContainsPoint containsPoint = &MyClass::contains;
	ContainsGeoRect containsGeoRect = &MyClass::contains;
	
	class_<MyClass>("BBox", init<>())
	.def(init<MyClass>())
	.def(init<double, double, double, double>("BBox(latMin, latMax, lonMin, lonMax)"))
	.def(init<double, double, double>("(Lat, Lon, diagonalInMeter) Lat and Lon are the center of the created BBox"))
	.def("diamater", &MyClass::diagInM, "Diameter of this bbox")
	.def("contains", containsPoint, "True iff bbox contains given point (lat, lon)")
	.def("contains", containsGeoRect, "True iff bbox contains other bbox")
	.def("__str__", &print_GeoRect)
	;
	
}
	
}} //end namespace pyoscar::exporting
