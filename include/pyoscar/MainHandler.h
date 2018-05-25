#pragma once

#include <boost/python.hpp>
#include <liboscar/StaticOsmCompleter.h>
#include <pyoscar/RelationHelpers.h>
#include <pyoscar/CellManipulation.h>

namespace pyoscar {
	
class MainHandler final {
public:
	MainHandler();
	~MainHandler();
public:
	bool energize(std::string path);
	liboscar::Static::OsmCompleter & engine();
	RelationHelpers relationHelpers();
	CellManipulation cellManipulator();
private:
	liboscar::Static::OsmCompleter m_cmp;
};

namespace exporting {
	
void export_pyoscar_MainHandler();
	
} //namespace exporting
} //end namespace pyoscar
