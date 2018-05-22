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


	
}//end namespace pyoscar
