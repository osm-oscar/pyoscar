#pragma once

#include <sserialize/Static/CQRDilator.h>

#include <liboscar/OsmKeyValueObjectStore.h>
#include <sserialize/Static/ItemIndexStore.h>

namespace pyoscar {
	
class CellManipulation final {
public:
	CellManipulation(const liboscar::Static::OsmKeyValueObjectStore & store, const sserialize::Static::ItemIndexStore & idxStore);
	~CellManipulation();
	sserialize::CellQueryResult dilate(const sserialize::CellQueryResult & cqr, double distance);
private:
	sserialize::Static::CQRDilator m_dilator;
};

namespace exporting {
	
void export_pyoscar_CellManipulation();
	
}//end namespace exporting
	
}//end namespace pyoscar
