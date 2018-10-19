#include <pyoscar/GeoShape.h>

#include <sserialize/Static/GeoShape.h>

#include <boost/python.hpp>

namespace pyoscar {
namespace exporting {
	
namespace {
	
std::string sserialize_Static_spatial_GeoShape_print(sserialize::Static::spatial::GeoShape const & x) {
	std::stringstream ss;
	ss << x.get()->toString();
	return ss.str();
}

std::string sserialize_Static_spatial_GeoShape_type(sserialize::Static::spatial::GeoShape const & x) {
	return sserialize::spatial::to_string( x.type() );
}

auto sserialize_Static_spatial_GeoShape_getPoint(sserialize::Static::spatial::GeoShape const & x) {
	return x.get<sserialize::spatial::GS_POINT>();
}

auto sserialize_Static_spatial_GeoShape_getWay(sserialize::Static::spatial::GeoShape const & x) {
	return x.get<sserialize::spatial::GS_WAY>();
}

auto sserialize_Static_spatial_GeoShape_getPolygon(sserialize::Static::spatial::GeoShape const & x) {
	return x.get<sserialize::spatial::GS_POLYGON>();
}

auto sserialize_Static_spatial_GeoShape_getMultiPolygon(sserialize::Static::spatial::GeoShape const & x) {
	return x.get<sserialize::spatial::GS_MULTI_POLYGON>();
}

double sserialize_spatial_GeoPoint_getLat(std::shared_ptr<sserialize::spatial::GeoPoint> const & x) {
	return x->lat();
}

double sserialize_spatial_GeoPoint_getLon(std::shared_ptr<sserialize::spatial::GeoPoint> const & x) {
	return x->lon();
}

std::shared_ptr<sserialize::spatial::GeoPoint> sserialize_Static_spatial_GeoWay_at(std::shared_ptr<sserialize::Static::spatial::GeoWay> const & x, uint32_t p) {
	return std::make_shared<sserialize::spatial::GeoPoint>(x->points().at(p));
}

uint32_t sserialize_Static_spatial_GeoMultiPolygon_numberOfInnerPolygons(std::shared_ptr<sserialize::Static::spatial::GeoMultiPolygon> const & x) {
	return x->innerPolygons().size();
}

uint32_t sserialize_Static_spatial_GeoMultiPolygon_numberOfOuterPolygons(std::shared_ptr<sserialize::Static::spatial::GeoMultiPolygon> const & x) {
	return x->innerPolygons().size();
}

auto sserialize_Static_spatial_GeoMultiPolygon_innerPolygon(std::shared_ptr<sserialize::Static::spatial::GeoMultiPolygon> const & x, uint32_t p) {
	return std::make_shared<sserialize::Static::spatial::GeoPolygon>( x->innerPolygons().at(p) );
}

auto sserialize_Static_spatial_GeoMultiPolygon_outerPolygon(std::shared_ptr<sserialize::Static::spatial::GeoMultiPolygon> const & x, uint32_t p) {
	return std::make_shared<sserialize::Static::spatial::GeoPolygon>( x->outerPolygons().at(p) );
}

}//protecting namespace

void export_sserialize_spatial_GeoShape() {
	using namespace boost::python;
	using MyClass = sserialize::spatial::GeoShape;
	
	typedef bool (MyClass:: *IntersectsGeoRect)(sserialize::spatial::GeoRect const &) const;
	
	IntersectsGeoRect intersectsGeoRect = &MyClass::intersects;
	
	class_<MyClass, bases<>, std::shared_ptr<MyClass>, boost::noncopyable>("GeoShape", no_init)
		.def("bbox", &MyClass::boundary)
		.def("intersects", intersectsGeoRect)
		.def("__str__", &MyClass::toString)
	;
}

void export_sserialize_spatial_GeoRegion() {
	using namespace boost::python;
	using MyClass = sserialize::spatial::GeoRegion;
	
	typedef bool (MyClass:: *IntersectsLine)(sserialize::spatial::GeoPoint const &, sserialize::spatial::GeoPoint const &) const;
	typedef bool (MyClass:: *IntersectsGeoRegion)(sserialize::spatial::GeoRegion const &) const;
	
	IntersectsLine intersectsLine = &MyClass::intersects;
	IntersectsGeoRegion intersectsGeoRegion = & MyClass::intersects;
	
	class_<MyClass, bases<sserialize::spatial::GeoShape>, std::shared_ptr<MyClass>, boost::noncopyable>("GeoRegion", no_init)
		.def("contains", &MyClass::contains)
		.def("intersects", intersectsLine)
		.def("intersects", intersectsGeoRegion)
		.def("__str__", &MyClass::toString)
	;
}

void export_sserialize_Static_spatial_GeoPoint() {
	using namespace boost::python;
	using MyClass = sserialize::Static::spatial::GeoPoint;
	
	class_<MyClass, bases<sserialize::spatial::GeoShape>, std::shared_ptr<MyClass>, boost::noncopyable>("GeoPoint", init<double, double>())
		.def("lat", &sserialize_spatial_GeoPoint_getLat)
		.def("lon", &sserialize_spatial_GeoPoint_getLon)
	;
}

void export_sserialize_Static_spatial_GeoWay() {
	using namespace boost::python;
	using MyClass = sserialize::Static::spatial::GeoWay;
	
	class_<MyClass, bases<sserialize::spatial::GeoRegion>, std::shared_ptr<MyClass>, boost::noncopyable>("GeoWay", init<>())
		.def("at", &sserialize_Static_spatial_GeoWay_at)
	;
}
void export_sserialize_Static_spatial_GeoPolygon() {
	using namespace boost::python;
	using MyClass = sserialize::Static::spatial::GeoPolygon;

	typedef bool (MyClass:: *EnclosesGeoPolygon)(sserialize::Static::spatial::GeoPolygon const &) const;
	typedef bool (MyClass:: *EnclosesGeoWay)(sserialize::Static::spatial::GeoWay const &) const;
	
	EnclosesGeoPolygon enclosesGeoPolygon = &MyClass::encloses;
	EnclosesGeoWay enclosesGeoWay = & MyClass::encloses;

	
	class_<MyClass, bases<sserialize::Static::spatial::GeoWay>, std::shared_ptr<MyClass>, boost::noncopyable>("GeoPolygon", init<>())
		.def("encloses", enclosesGeoPolygon)
		.def("encloses", enclosesGeoWay)
	;
}
void export_sserialize_Static_spatial_GeoMultiPolygon() {
	using namespace boost::python;
	using MyClass = sserialize::Static::spatial::GeoMultiPolygon;
	
	typedef bool (MyClass:: *EnclosesGeoPolygon)(sserialize::Static::spatial::GeoPolygon const &) const;
	typedef bool (MyClass:: *EnclosedGeoPolygon)(sserialize::Static::spatial::GeoPolygon const &) const;
	
	EnclosesGeoPolygon enclosesGeoPolygon = &MyClass::encloses;
	EnclosedGeoPolygon enclosedGeoPolygon = & MyClass::enclosed;

	class_<MyClass, bases<sserialize::spatial::GeoRegion>, std::shared_ptr<MyClass>, boost::noncopyable>("GeoPolygon", init<>())
		.def("numberOfInnerPolygons", &sserialize_Static_spatial_GeoMultiPolygon_numberOfInnerPolygons)
		.def("numberOfOuterPolygons", &sserialize_Static_spatial_GeoMultiPolygon_numberOfOuterPolygons)
		.def("innerPolygon", sserialize_Static_spatial_GeoMultiPolygon_innerPolygon)
		.def("outerPolygon", sserialize_Static_spatial_GeoMultiPolygon_outerPolygon)
		.def("encloses", enclosesGeoPolygon)
		.def("enclosed", enclosedGeoPolygon)
	;
}

void export_sserialize_Static_spatial_GeoShape() {
	using namespace boost::python;
	using MyClass = sserialize::Static::spatial::GeoShape;
	
	typedef bool (MyClass:: *IntersectsGeoShape)(MyClass const &) const;
	typedef bool (MyClass:: *IntersectsGeoRect)(sserialize::spatial::GeoRect const &) const;
	
	IntersectsGeoShape intersectsGeoShape = &MyClass::intersects;
	IntersectsGeoRect intersectsGeoRect = &MyClass::intersects;
	
	class_<MyClass>("GeoShapeBase", init<>())
	.def(init<MyClass>())
	.def("bbox", &MyClass::boundary, "Bounding box")
	.def("intersects", intersectsGeoShape, "True iff shape intersects the given GeoShape")
	.def("intersects", intersectsGeoRect, "True iff shape intersects the given bbox")
	.def("__str__", &sserialize_Static_spatial_GeoShape_print)
	.def("type", &sserialize_Static_spatial_GeoShape_type)
	.def("getPoint", &sserialize_Static_spatial_GeoShape_getPoint)
	.def("getWay", &sserialize_Static_spatial_GeoShape_getWay)
	.def("getPolygon", &sserialize_Static_spatial_GeoShape_getPolygon)
	.def("getMultiPolygon", &sserialize_Static_spatial_GeoShape_getMultiPolygon)
	;
}

void export_sserialize_Static_spatial_GeoShapes() {

	export_sserialize_spatial_GeoShape();
	export_sserialize_spatial_GeoRegion();
	export_sserialize_Static_spatial_GeoPoint();
	export_sserialize_Static_spatial_GeoWay();
	export_sserialize_Static_spatial_GeoPolygon();
	export_sserialize_Static_spatial_GeoMultiPolygon();
	export_sserialize_Static_spatial_GeoShape();
}

}} //end namespace pyoscar::exporting

