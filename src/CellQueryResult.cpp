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
		.def("size", &MyClass::cellCount, "Number of cells")
		.def("cellId", &MyClass::cellId, "Id of the cell at position i")
		.def("itemCount", &MyClass::idxSize, "Number of items in cell at position i")
		.def("cellItems", &MyClass::items, "Items of cell at position i")
		.def("allToFull", &MyClass::allToFull, "Turn all cells into full match cells")
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
