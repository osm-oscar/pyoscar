#include <pyoscar/GeoHierarchy.h>
#include <pyoscar/refcounting.h>

#include <sserialize/Static/GeoHierarchy.h>

namespace pyoscar {
namespace exporting {
	
class SubSetNodeVisitor {
public:
	using Node = sserialize::Static::spatial::detail::SubSet::Node;
	using value_type = Node::NodePtr;
public:
	SubSetNodeVisitor(PyObject* self) :
	self(self)
	{}
	void operator()(const value_type & v) {
		boost::python::call_method<void>(self, "visit", v);
	}
private:
    PyObject* self;
};

void
sserialize_Static_spatial_GeoHierarchy_SubSetNodeVisitImp(
	const sserialize::Static::spatial::detail::SubSet::Node::NodePtr & self,
	SubSetNodeVisitor & visitor)
{
	visitor(self);
	for(const auto & x : *self) {
		sserialize_Static_spatial_GeoHierarchy_SubSetNodeVisitImp(x, visitor);
	}
}

void
sserialize_Static_spatial_GeoHierarchy_SubSetNodeVisit(
	const sserialize::Static::spatial::detail::SubSet::Node::NodePtr & self,
	SubSetNodeVisitor visitor)
{
	sserialize_Static_spatial_GeoHierarchy_SubSetNodeVisitImp(self, visitor);
}

std::string
sserialize_Static_spatial_GeoHierarchy_SubSetNodeToString(
	const sserialize::Static::spatial::detail::SubSet::Node::NodePtr & self)
{
	std::stringstream ss;
	ss << "Region{graphId: " << self->ghId() << ", maxItems: " << self->maxItemsSize() << ", children: [";
	bool hasPrev = false;
	for(const auto & x : *self) {
		if (hasPrev) {
			ss << ",";
		}
		hasPrev = true;
		ss << x->ghId();
	}
	ss << "]}";
	return ss.str();
}

void export_sserialize_Static_spatial_GeoHierarchy_SubSetNode() {
	using namespace boost::python;
	using MyClass = sserialize::Static::spatial::detail::SubSet::Node;
	
	typedef MyClass::NodePtr const & (MyClass:: *AtMemFn)(uint32_t) const;
	typedef uint32_t (MyClass:: *MaxItemsSizeMemFn)() const;
	typedef MyClass::NodePtr const & (MyClass:: *AtMemFn)(uint32_t) const;
	
	AtMemFn atMemFn = &MyClass::at;
	MaxItemsSizeMemFn maxItemsSizeMemFn = &MyClass::maxItemsSize;
	
	class_<SubSetNodeVisitor, boost::noncopyable >("_GeoHierarchySubSetNodeVisitor", init<PyObject*>() );
	
	class_<MyClass, bases<>, MyClass::NodePtr, boost::noncopyable>("GeoHierarchySubSetNode", init<uint32_t, uint32_t>())
		.def("graphId", &MyClass::ghId)
		.def("size", &MyClass::size)
		.def("at", atMemFn, return_value_policy<return_by_value>())
		.def("maxItemsSize", maxItemsSizeMemFn)
		.def("__iter__", iterator<MyClass>())
		.def("visit", &sserialize_Static_spatial_GeoHierarchy_SubSetNodeVisit)
		.def("__str__", &sserialize_Static_spatial_GeoHierarchy_SubSetNodeToString)
	;
// 	register_ptr_to_python< MyClass::NodePtr >();
}

void export_sserialize_Static_spatial_GeoHierarchy_SubSet() {
	using namespace boost::python;
	using MyClass = sserialize::Static::spatial::detail::SubSet;
	class_<MyClass>("GeoHierarchySubSet")
		.def("cells", &MyClass::cqr, return_value_policy<copy_const_reference>())
		.def("graph", &MyClass::root, return_value_policy<copy_const_reference>())
		.def("items", &MyClass::items)
	;
}

void export_sserialize_Static_spatial_GeoHierarchy_Cell() {
	using namespace boost::python;
	using MyClass = sserialize::Static::spatial::detail::Cell;
	class_<MyClass>("GeoHierarchyCell")
		.def("itemCount", &MyClass::itemCount)
		.def("ancestorCount", &MyClass::parentsSize)
		.def("ancestorId", &MyClass::parent)
	;
}

void export_sserialize_Static_spatial_GeoHierarchy_Region() {
	using namespace boost::python;
	using MyClass = sserialize::Static::spatial::detail::Region;
	class_<MyClass>("GeoHierarchyRegion")
		.def("graphId", &MyClass::ghId)
		.def("itemId", &MyClass::storeId)
		.def("itemsCount", &MyClass::itemsCount)
		.def("childrenCount", &MyClass::childrenSize)
		.def("ancestorCount", &MyClass::parentsSize)
		.def("ancestorId", &MyClass::parent)
		.def("childId", &MyClass::child)
	;
}

void export_sserialize_Static_spatial_GeoHierarchy() {
	using namespace boost::python;
	using MyClass = sserialize::Static::spatial::GeoHierarchy;
	class_<MyClass>("GeoHierarchy")
		.def("numberOfRegions", &MyClass::regionSize)
		.def("numberOfCells", &MyClass::cellSize)
		.def("region", &MyClass::region)
		.def("cell", &MyClass::cell)
		.def("regionFromItemId", &MyClass::regionFromStoreId)
		.def("itemId2GraphId", &MyClass::storeIdToGhId)
		.def("graphId2ItemId", &MyClass::ghIdToStoreId)
	;
}

}} //end namespace pyoscar::exporting
