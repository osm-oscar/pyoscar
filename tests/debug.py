#!/usr/bin/env python3

import pyoscar

hdl = pyoscar.MainHandler()
hdl.energize("/home/daniel/documents/coding/oscar/builds/stretch/ultra/oscar-create/stgt_global")
engine = hdl.engine()
result = engine.query("jakob böhme weg stuttgart")
cells = result.cells()
items = cells.items()

store = engine.store()
for itemId in items:
	item = store.at(itemId)
	print(str(itemId) + str(item))

relhelp = hdl.relationHelpers()

keltenwege = engine.query("keltenweg #stuttgart @highway").cells().items()
for itemId1 in items:
	for itemId2 in keltenwege:
		if relhelp.intersect(itemId1, itemId2):
			print("The following entities intersect:")
			print(store.at(itemId1))
			print(store.at(itemId2))

# you can do this faster by only checking items that are in the same cells:
