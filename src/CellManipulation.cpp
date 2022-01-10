#include <pyoscar/CellManipulation.h>

#include <boost/python.hpp>

namespace pyoscar {
	

CellManipulation::CellManipulation(const liboscar::Static::OsmKeyValueObjectStore & store, const sserialize::Static::ItemIndexStore & idxStore) :
m_dilator(store.cellCenterOfMass(), store.cellGraph())
{}

CellManipulation::~CellManipulation() {}

sserialize::CellQueryResult
CellManipulation::dilate(const sserialize::CellQueryResult & cqr, double distance) {
	return sserialize::CellQueryResult(m_dilator.dilate(cqr, distance*1000, 1), cqr.cellInfo(), cqr.idxStore(), cqr.flags() & cqr.FF_MASK_CELL_ITEM_IDS) + cqr;
}


namespace exporting {
	
void export_pyoscar_CellManipulation() {
	using namespace boost::python;
	using MyClass = pyoscar::CellManipulation;
	class_<MyClass>("CellManipulation", init<liboscar::Static::OsmKeyValueObjectStore, sserialize::Static::ItemIndexStore>())
		.def("dilate", &MyClass::dilate, "Approximately dilate cells by d kilometers")
	;
}
	
}//end namespace exporting

}//end namespace pyoscar
