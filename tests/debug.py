#!/usr/bin/env python3

import pyoscar

hdl = pyoscar.MainHandler()
hdl.energize("/home/daniel/documents/coding/oscar/builds/stretch/ultra/oscar-create/stgt_global")
engine = hdl.engine()
result = engine.query("jakob böhme weg stuttgart @highway")
cells = result.cells()
items = cells.items()

store = engine.store()
for itemId in items:
	item = store.at(itemId)
	print(str(itemId) + str(item))

relhelp = hdl.relationHelpers()

keltenwege = engine.query("keltenweg #stuttgart steinhaldenfeld @highway").cells().items()
print("""Query "keltenweg #stuttgart @highway" has """ + str(keltenwege.size()) + " items")
for itemId1 in items:
	for itemId2 in keltenwege:
		print("Checking " + str(itemId1) + " with " + str(itemId2))
		if relhelp.intersect(itemId1, itemId2):
			print("The following entities intersect:")
			print(store.at(itemId1))
			print(store.at(itemId2))

neckar = engine.query("!Neckar @waterway").cells().items()
print("Checking " + str(neckar.size()) + " segments of the river neckar")
for i in neckar:
	for j in neckar:
		if (relhelp.intersect(i, j) and i != j):
			print("The following parts of the Neckar intersect:")
			print(store.at(i))
			print(store.at(j))


# you can do this faster by only checking items that are in the same cells:
