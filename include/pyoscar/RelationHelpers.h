#pragma once

#include <liboscar/OsmKeyValueObjectStore.h>
#include <sserialize/Static/ItemIndexStore.h>

namespace pyoscar {
	
class RelationHelpers final {
public:
	RelationHelpers(const liboscar::Static::OsmKeyValueObjectStore & store, const sserialize::Static::ItemIndexStore & idxStore);
	~RelationHelpers();
	bool is_in(const liboscar::Static::OsmKeyValueObjectStoreItem & item1, const liboscar::Static::OsmKeyValueObjectStoreItem & item2);
	bool intersect(const liboscar::Static::OsmKeyValueObjectStoreItem & item1, const liboscar::Static::OsmKeyValueObjectStoreItem & item2);
private:
	liboscar::Static::OsmKeyValueObjectStore m_store;
	sserialize::Static::ItemIndexStore m_idxStore;
	
};
	
namespace exporting {
	
void export_pyoscar_RelationHelpers();
	
}//end namespace exporting
	
}//end namespace pyoscar
