#include <pyoscar/RelationHelpers.h>

#include <boost/python.hpp>

namespace pyoscar {
	
RelationHelpers::RelationHelpers(const liboscar::Static::OsmKeyValueObjectStore & store, const sserialize::Static::ItemIndexStore & idxStore) :
m_store(store),
m_idxStore(idxStore)
{}

RelationHelpers::~RelationHelpers()
{}

bool
RelationHelpers::is_in(const liboscar::Static::OsmKeyValueObjectStoreItem & item1, const liboscar::Static::OsmKeyValueObjectStoreItem & item2) {
	const auto & gh = m_store.geoHierarchy();
	if (item1.isRegion()) {
		if (item2.isRegion()) {
			auto r1 = gh.regionFromStoreId(item1.id());
			auto r2 = gh.regionFromStoreId(item2.id());
			for(uint32_t i(0), s(r2.parentsSize()); i < s; ++i) {
				if (r2.parent(i) == r1.ghId()) {
					return true;
				}
			}
		}
		else {
			auto r1 = gh.regionFromStoreId(item1.id());
			auto r1cells = m_idxStore.at( r1.cellIndexPtr() );
			auto i2cells = sserialize::ItemIndex( item2.cells() );
			return (r1cells / i2cells).size();
		}
	}
	return false;
}


bool
RelationHelpers::intersect(const liboscar::Static::OsmKeyValueObjectStoreItem & item1, const liboscar::Static::OsmKeyValueObjectStoreItem & item2) {
	const auto & gh = m_store.geoHierarchy();
	if (item1.isRegion() && item2.isRegion()) {
		auto r1 = gh.regionFromStoreId(item1.id());
		auto r2 = gh.regionFromStoreId(item2.id());
		return (m_idxStore.at( r1.cellIndexPtr() ) / m_idxStore.at(r2.cellIndexPtr())).size();
	}
	else if (item1.isRegion() && !item2.isRegion()) {
		auto r = gh.regionFromStoreId(item1.id());
		auto rcells = m_idxStore.at( r.cellIndexPtr() );
		auto icells = sserialize::ItemIndex( item2.cells() );
		return (rcells / icells).size();
	}
	else if(!item1.isRegion() && item2.isRegion()) {
		auto r = gh.regionFromStoreId(item2.id());
		auto rcells = m_idxStore.at( r.cellIndexPtr() );
		auto icells = sserialize::ItemIndex( item1.cells() );
		return (rcells / icells).size();
	}
	else {
		return item1.geoShape().intersects(item2.geoShape());
	}
	return false;
}

namespace exporting {

void export_pyoscar_RelationHelpers() {
	using namespace boost::python;
	using MyClass = pyoscar::RelationHelpers;
	class_<MyClass>("RelationHelpers", init<liboscar::Static::OsmKeyValueObjectStore, sserialize::Static::ItemIndexStore>())
		.def("is_in", &MyClass::is_in)
		.def("intersect", &MyClass::intersect)
	;
}

}} //end namespace pyoscar::exporting
