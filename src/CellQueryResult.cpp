#include <pyoscar/CellQueryResult.h>

#include <sserialize/spatial/CellQueryResult.h>

#include <boost/python.hpp>

namespace pyoscar {
namespace exporting {

BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(sserialize_CellQueryResult_flaten_overloads, flaten, 0, 1);
	
void export_sserialize_CellQueryResult() {
	using namespace boost::python;
	using MyClass = sserialize::CellQueryResult;
	class_<MyClass>("CellQueryResult")
		.def("size", &MyClass::cellCount)
		.def("cellId", &MyClass::cellId)
		.def("itemCount", &MyClass::idxSize)
		.def("cellItems", &MyClass::items)
		.def("allToFull", &MyClass::allToFull)
		.def("items", &MyClass::flaten, sserialize_CellQueryResult_flaten_overloads())
		.def(self + other<MyClass>())
		.def(self / other<MyClass>())
		.def(self - other<MyClass>())
		.def(self ^ other<MyClass>())
		.def(other<MyClass>() + self)
		.def(other<MyClass>() / self)
		.def(other<MyClass>() - self)
		.def(other<MyClass>() ^ self)
	;
}

}} //end namespace pyoscar::exporting
