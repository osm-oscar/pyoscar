#!/usr/bin/env python3
from ._pyoscar import *
from ._pyoscar import _GeoHierarchySubSetNodeVisitor as GeoHierarchySubSetNodeVisitorBase
from ._pyoscar import _RelationHelpersIntersectingItemsVisitor as RelationHelpersIntersectingItemsVisitorBase

### Use this to visit all descendants of a node of GeoHierarchySubSetNode
class GeoHierarchySubSetNodeVisitor(GeoHierarchySubSetNodeVisitorBase):
	def __init__(self, visitor):
		GeoHierarchySubSetNodeVisitorBase.__init__(self, self)
		if (not visitor is None):
			self.m_visitor = visitor

	def visit(self, x):
		if (not self.m_visitor is None):
			self.m_visitor(x)

class RelationHelpersIntersectingItemsVisitor(RelationHelpersIntersectingItemsVisitorBase):
	def __init__(self, visitor):
		RelationHelpersIntersectingItemsVisitorBase.__init__(self, self)
		self.m_visitor = visitor

	def visit(self, x, y):
		self.m_visitor(x, y)