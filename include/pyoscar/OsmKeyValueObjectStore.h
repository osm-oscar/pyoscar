#ifndef PYOSCAR_OSM_KEY_VALUE_OBJECT_STORE_H
#define PYOSCAR_OSM_KEY_VALUE_OBJECT_STORE_H
#include <boost/python.hpp>
#include <liboscar/OsmKeyValueObjectStore.h>

namespace pyoscar {
namespace exporting {
	
	void export_liboscar_Static_OsmKeyValueObjectStore();
	
}} //end namespace pyoscar::exporting
#endif
