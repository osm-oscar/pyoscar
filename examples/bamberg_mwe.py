#!/usr/bin/env python3
import pyoscar
import argparse

cmdLineParser = argparse.ArgumentParser(description="Does a debug query")
cmdLineParser.add_argument('-f', help='path to oscar data', dest='f', nargs=1, type=str, required=True)

parsedArgs = cmdLineParser.parse_args()

hdl = pyoscar.MainHandler()
hdl.energize(parsedArgs.f[0])
engine = hdl.engine()


result = engine.query("#Bamberg @admin_level:6 @railway:station")
cells = result.cells()
items = cells.items()
store = engine.store()
graph = store.graph()
relhelp = hdl.relationHelpers()
for itemId in items:
	item = store.at(itemId)
	if (item.hasKey("name") and item.value("name") == "Bamberg"):
		value=itemId
		print(value)
	print(str(item))
	print(str(itemId) + "Osm id is " + str(item.osmId()))
