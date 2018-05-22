#include <pyoscar/MainHandler.h>
#include <pyoscar/OsmKeyValueObjectStore.h>

BOOST_PYTHON_MODULE(_pyoscar)
{
	using namespace pyoscar::exporting;
	export_pyoscar_MainHandler();
	export_liboscar_Static_OsmKeyValueObjectStore();
}
