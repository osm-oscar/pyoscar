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
	
} //end namespace pyoscar

BOOST_PYTHON_MODULE(pyoscar)
{
	using namespace boost::python;
	class_<pyoscar::MainHandler>("MainHandler")
		.def("energize", &pyoscar::MainHandler::energize)
	;
}

#endif
