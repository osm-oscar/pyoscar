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


# We can do this faster by only checking items that are in the same cells:

neugereut_residential = engine.query(""" !@highway:residential #"Neugereut" """)
stuttgart_residential = engine.query(""" !@highway:residential #"Stuttgart" """)

#candidates in stuttgart and neugereut
stuttgart_filtered = stuttgart_residential.cells() / neugereut_residential.cells().allToFull()
neugereut_filtered = neugereut_residential.cells() / stuttgart_residential.cells().allToFull()

# the filtered results have the same size
assert(stuttgart_filtered.size() == neugereut_filtered.size())
# cellIds = [stuttgart_filtered.cellId(i) for i in range(0, stuttgart_filtered.size())]

for i in range(0, stuttgart_filtered.size()):
	assert(stuttgart_filtered.cellId(i) == neugereut_filtered.cellId(i))
	stuttgart_items = stuttgart_filtered.cellItems(i)
	neugereut_items = neugereut_filtered.cellItems(i)

	for i in stuttgart_items:
		for j in neugereut_items:
			if (i == j): # trivially intersects
				continue
			elif (relhelp.intersect(i, j)):
				print("Intersecting items: " + str(i) + " and " + str(j))

#the same thing, but this time in native code
print("The same in native code:")
relhelp.intersect(
	stuttgart_filtered,
	neugereut_filtered,
	pyoscar.RelationHelpersIntersectingItemsVisitor(
		lambda x, y : print(str(x) + ":" + str(y))
	))

q = engine.query(""" #"Stuttgart" """)
print("""Graph of the query #"Stuttgart" """)
q.graph().visit(pyoscar.GeoHierarchySubSetNodeVisitor(lambda x : print(x)))
graph = store.graph()
q.graph().visit(pyoscar.GeoHierarchySubSetNodeVisitor(lambda x : print(graph.region(x.graphId() ).itemId())))