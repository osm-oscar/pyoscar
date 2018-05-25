#include <pyoscar/MainHandler.h>

namespace pyoscar {
	
MainHandler::MainHandler() {}

MainHandler::~MainHandler() {}

bool MainHandler::energize(std::string path) {
	m_cmp.setAllFilesFromPrefix(path);
	try {
		m_cmp.energize(sserialize::spatial::GeoHierarchySubGraph::T_PASS_THROUGH);
	}
	catch (const std::exception & e) {
		std::cerr << "Failed to energize: " << e.what() << std::endl;
		return false;
	}
	return true;
}

liboscar::Static::OsmCompleter & MainHandler::engine() {
	return m_cmp;
}

RelationHelpers MainHandler::relationHelpers() {
	return RelationHelpers(m_cmp.store(), m_cmp.indexStore());
}

CellManipulation MainHandler::cellManipulator() {
	return CellManipulation(m_cmp.store(), m_cmp.indexStore());
}

namespace exporting {

void export_pyoscar_MainHandler() {
	using namespace boost::python;
	class_<pyoscar::MainHandler>("MainHandler")
		.def("energize", &pyoscar::MainHandler::energize, "Load data store at path p")
		.def("engine", &pyoscar::MainHandler::engine, return_internal_reference<>(), "Get query engine")
		.def("relationHelpers", &pyoscar::MainHandler::relationHelpers, "Get relation helpers")
		.def("cellManipulator", &pyoscar::MainHandler::cellManipulator, "Get cell manipulator")
	;
}

} //end namespace exporting
}//end namespace pyoscar
