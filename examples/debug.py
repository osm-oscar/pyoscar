#!/usr/bin/env python3

import pyoscar
import argparse

cmdLineParser = argparse.ArgumentParser(description="Does some example queries")
cmdLineParser.add_argument('-f', help='path to oscar data', dest='f', nargs=1, type=str, required=True)

parsedArgs = cmdLineParser.parse_args()

hdl = pyoscar.MainHandler()
hdl.energize(parsedArgs.f[0])
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
			print(str(store.at(i)))
			print(str(store.at(j)))


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
relhelp.intersecting_items(
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

#let try to check if plochingen is at the confluence of neckar and fils

print("Try to check if neckar and fils intersect in Plochingen")
neckar = engine.query("!Neckar @waterway:river")
fils = engine.query("!Fils @waterway:river")
plochingen = engine.query(""" #"Plochingen" """)

# lets find our region
idOfPlochingen = 0

class FindPlochingenVisitor(pyoscar._pyoscar._GeoHierarchySubSetNodeVisitor):
	def __init__(self):
		pyoscar._pyoscar._GeoHierarchySubSetNodeVisitor.__init__(self, self)
		self.idOfPlochingen = -1
	def visit(self, node):
		itemId = graph.graphId2ItemId(node.graphId())
		item = store.at(itemId)
		if (item.hasKey("name") and item.value("name") == "Plochingen"):
			self.idOfPlochingen = itemId

visitor = FindPlochingenVisitor()
plochingen.graph().visit(visitor)

print("Plochingen is " + str(store.at(visitor.idOfPlochingen)))

if (visitor.idOfPlochingen != -1):
	neckar_fils_intersections = set()
	relhelp.intersecting_items(
		neckar,
		fils,
		pyoscar.RelationHelpersIntersectingItemsVisitor(
			lambda x, y : neckar_fils_intersections.update(set([x, y]))
		))
	print("The following neckar and fils parts intersect: " + str(neckar_fils_intersections))
	print("The osm ids of the intersecting parts are: " + str([store.at(itemId).osmId() for itemId in neckar_fils_intersections]))
	partsInPlochingen = [itemId for itemId in neckar_fils_intersections if relhelp.is_in(visitor.idOfPlochingen, itemId)]
	for itemId in partsInPlochingen:
		item = store.at(itemId)
		print("Item with id=" + str(itemId) + " and osmId=" + str(item.osmId()) + " is in Plochingen")
else:
	print("Did not find plochingen")

