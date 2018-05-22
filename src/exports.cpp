#include <pyoscar/MainHandler.h>
#include <pyoscar/OsmKeyValueObjectStore.h>
#include <pyoscar/StaticOsmCompleter.h>

BOOST_PYTHON_MODULE(_pyoscar)
{
	using namespace pyoscar::exporting;
	export_pyoscar_MainHandler();
	export_liboscar_Static_OsmKeyValueObjectStoreItem();
	export_liboscar_Static_OsmKeyValueObjectStore();
	export_liboscar_Static_OsmCompleter();
}
