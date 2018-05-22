#pragma once

#include <liboscar/OsmKeyValueObjectStore.h>

namespace pyoscar {
	
class RelationHelpers {
public:
	RelationHelpers();
	void is_in(const liboscar::Static::OsmKeyValueObjectStoreItem & item1, const liboscar::Static::OsmKeyValueObjectStoreItem & item2);
};
	
namespace exporting {
	
void export_pyoscar_RelationHelpers();
	
}//end namespace exporting
	
}//end namespace pyoscar
