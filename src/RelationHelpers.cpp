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
RelationHelpers::is_in(uint32_t itemId1, uint32_t itemId2) const {
	return is_in(m_store.at(itemId1), m_store.at(itemId2));
}

bool
RelationHelpers::intersect(uint32_t itemId1, uint32_t itemId2) const {
	return intersect(m_store.at(itemId1), m_store.at(itemId2));
}

bool
RelationHelpers::is_in(const liboscar::Static::OsmKeyValueObjectStoreItem & item1, const liboscar::Static::OsmKeyValueObjectStoreItem & item2) const {
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
RelationHelpers::intersect(const liboscar::Static::OsmKeyValueObjectStoreItem & item1, const liboscar::Static::OsmKeyValueObjectStoreItem & item2) const {
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
	
class RelationHelpersIntersectingItemsVisitor {
public:
public:
	RelationHelpersIntersectingItemsVisitor(PyObject* self) :
	self(self)
	{}
	bool operator()(uint32_t first, uint32_t second) {
		boost::python::call_method<void>(self, "visit", first, second);
	}
private:
    PyObject* self;
};

namespace {
void RelationHelpers_intersecting_items(
	const RelationHelpers & self,
	const sserialize::CellQueryResult & first,
	const sserialize::CellQueryResult & second,
	RelationHelpersIntersectingItemsVisitor visitor)
{
	self.intersecting_items(first, second, visitor);
}
}

void export_pyoscar_RelationHelpers() {
	using namespace boost::python;
	using MyClass = pyoscar::RelationHelpers;
	
	typedef bool (MyClass:: *Binary_predicate_ids)(uint32_t, uint32_t) const;
	typedef bool (MyClass:: *Binary_predicate_items)(const liboscar::Static::OsmKeyValueObjectStoreItem &, const liboscar::Static::OsmKeyValueObjectStoreItem &) const;
	
	Binary_predicate_ids is_in_ids = &MyClass::is_in;
	Binary_predicate_ids intersect_ids = &MyClass::intersect;
	
	Binary_predicate_items is_in_items = &MyClass::is_in;
	Binary_predicate_items intersect_items = &MyClass::intersect;
	
	class_<RelationHelpersIntersectingItemsVisitor, boost::noncopyable >("_RelationHelpersIntersectingItemsVisitor", init<PyObject*>() );
	
	class_<MyClass>("RelationHelpers", init<liboscar::Static::OsmKeyValueObjectStore, sserialize::Static::ItemIndexStore>())
		.def("is_in", is_in_ids)
		.def("intersect", intersect_ids)
		.def("is_in", is_in_items)
		.def("intersect", intersect_items)
		.def("intersect", &RelationHelpers_intersecting_items)
	;
}

}} //end namespace pyoscar::exporting
