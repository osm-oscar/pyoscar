#pragma once

#include <liboscar/OsmKeyValueObjectStore.h>
#include <sserialize/Static/ItemIndexStore.h>
#include <sserialize/spatial/CellQueryResult.h>
#include <sserialize/utility/assert.h>
#include <sserialize/algorithm/hashspecializations.h>

namespace pyoscar {
	
class RelationHelpers final {
public:
	RelationHelpers(const liboscar::Static::OsmKeyValueObjectStore & store, const sserialize::Static::ItemIndexStore & idxStore);
	~RelationHelpers();
	bool is_in(uint32_t itemId1, uint32_t itemId2) const;
	bool intersect(uint32_t itemId1, uint32_t itemId2) const;
	
	bool is_in(const liboscar::Static::OsmKeyValueObjectStoreItem & item1, const liboscar::Static::OsmKeyValueObjectStoreItem & item2) const;
	bool intersect(const liboscar::Static::OsmKeyValueObjectStoreItem & item1, const liboscar::Static::OsmKeyValueObjectStoreItem & item2) const;
	
	template<typename TVisitor>
	void intersecting_items(const sserialize::CellQueryResult & first, const sserialize::CellQueryResult & second, TVisitor visitor) const;
private:
	liboscar::Static::OsmKeyValueObjectStore m_store;
	sserialize::Static::ItemIndexStore m_idxStore;
};
	
namespace exporting {
	
void export_pyoscar_RelationHelpers();
	
}//end namespace exporting
	
}//end namespace pyoscar

//Implementation

namespace pyoscar {


template<typename TVisitor>
void
RelationHelpers::intersecting_items(
	const sserialize::CellQueryResult & first,
	const sserialize::CellQueryResult & second,
	TVisitor visitor) const
{
	sserialize::CellQueryResult::const_iterator itFirst(first.begin()), itSecond(second.begin());
	sserialize::CellQueryResult::const_iterator endFirst(first.end()), endSecond(second.end());
	std::unordered_set< std::pair<uint32_t, uint32_t> > checked;
	for(; itFirst != endFirst && itSecond != endSecond; ) {
		if (itFirst.cellId() < itSecond.cellId()) {
			++itFirst;
			continue;
		}
		else if (itSecond.cellId() < itFirst.cellId()) {
			++itSecond;
			continue;
		}
		SSERIALIZE_CHEAP_ASSERT_EQUAL(itFirst.cellId(), itSecond.cellId());
		sserialize::ItemIndex itemsFirst = itFirst.items();
		sserialize::ItemIndex itemsSecond = itSecond.items();
		for(auto xfirst : itemsFirst) {
			for(auto xsecond : itemsSecond) {
				if (checked.count(std::pair<uint32_t, uint32_t>(xfirst, xsecond)) ||
					checked.count(std::pair<uint32_t, uint32_t>(xsecond, xfirst)) )
				{
					continue;
				}
				if (xfirst == xsecond || intersect(xfirst, xsecond)) {
					visitor(xfirst, xsecond);
				}
			}
		}
		++itFirst;
		++itSecond;
	}
}

}//end namespace pyoscar
