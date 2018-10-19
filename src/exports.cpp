#include <pyoscar/CellQueryResult.h>
#include <pyoscar/GeoHierarchy.h>
#include <pyoscar/ItemIndex.h>
#include <pyoscar/ItemIndexStore.h>
#include <pyoscar/MainHandler.h>
#include <pyoscar/OsmKeyValueObjectStore.h>
#include <pyoscar/RelationHelpers.h>
#include <pyoscar/StaticOsmCompleter.h>
#include <pyoscar/CellManipulation.h>
#include <pyoscar/GeoRect.h>
#include <pyoscar/GeoShape.h>

BOOST_PYTHON_MODULE(_pyoscar)
{
	using namespace pyoscar::exporting;

	export_sserialize_CellQueryResult();
	export_sserialize_ItemIndex();

	export_sserialize_spatial_GeoRect();
	export_sserialize_Static_spatial_GeoShapes();

	export_sserialize_Static_ItemIndexStore();

	export_sserialize_Static_spatial_GeoHierarchy_SubSetNode();
	export_sserialize_Static_spatial_GeoHierarchy_Cell();
	export_sserialize_Static_spatial_GeoHierarchy_Region();
	export_sserialize_Static_spatial_GeoHierarchy_SubSet();
	export_sserialize_Static_spatial_GeoHierarchy();

	export_liboscar_Static_OsmKeyValueObjectStoreItem();
	export_liboscar_Static_OsmKeyValueObjectStore();
	export_liboscar_Static_OsmCompleter();
	
	export_pyoscar_MainHandler();
	export_pyoscar_RelationHelpers();
	export_pyoscar_CellManipulation();
}
