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

namespace exporting {

void export_pyoscar_MainHandler() {
	using namespace boost::python;
	class_<pyoscar::MainHandler>("MainHandler")
		.def("energize", &pyoscar::MainHandler::energize)
		.def("engine", &pyoscar::MainHandler::engine, return_internal_reference<>())
		.def("relationHelpers", &pyoscar::MainHandler::relationHelpers)
	;
}

} //end namespace exporting
}//end namespace pyoscar
