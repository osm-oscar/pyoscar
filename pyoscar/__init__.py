#!/usr/bin/env python3
from ._pyoscar import *

### Use this to visit all descendants of a node of GeoHierarchySubSetNode
class GeoHierarchySubSetNodeVisitor(_pyoscar._GeoHierarchySubSetNodeVisitor):
	def __init__(self, visitor):
		_pyoscar._GeoHierarchySubSetNodeVisitor.__init__(self, self)
		if (not visitor is None):
			self.m_visitor = visitor

	def visit(self, x):
		if (not self.m_visitor is None):
			self.m_visitor(x)

class RelationHelpersIntersectingItemsVisitor(_pyoscar._RelationHelpersIntersectingItemsVisitor):
	def __init__(self, visitor):
		_pyoscar._RelationHelpersIntersectingItemsVisitor.__init__(self, self)
		self.m_visitor = visitor

	def visit(self, x, y):
		self.m_visitor(x, y)