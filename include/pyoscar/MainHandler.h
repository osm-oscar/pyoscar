#ifndef PYOSCAR_MAIN_HANDLER_H
#define PYOSCAR_MAIN_HANDLER_H
#include <boost/python.hpp>
#include <liboscar/StaticOsmCompleter.h>

namespace pyoscar {
	
class MainHandler final {
public:
	MainHandler();
	~MainHandler();
public:
	bool energize(std::string path);
private:
	liboscar::Static::OsmCompleter m_cmp;
};

namespace exporting {
	
void export_pyoscar_MainHandler();
	
} //namespace exporting
} //end namespace pyoscar

#endif
