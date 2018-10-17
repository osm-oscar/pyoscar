# Setup
## Cloning

```Bash
git clone --recursive https://github.com/dbahrdt/pyoscar
```

## Updating
```Bash
git --rebase pull && git submodule update && git submodule foreach --recursive git submodule update
```
Don't forget to rebuild the library

## Pre-requisites
Remember to install the development files well. On Debian the relevant packages usually have a "dev" suffix.

 - Python 3
 - Boost-Python
 - zlib-dev
 - CGAL
 - cryptopp
 - icu
 - ragel
 - cppunit


## building
```Bash
mkdir build
cd build
cmake ../
make
```

# Sample data

Sample data files can be found here:

http://data.oscar-web.de/

For the germany data set, download all files from:
http://data.oscar-web.de/archive/de/

place them in a single folder:

```Bash
export OSCAR_DATA_PATH=your_path

cd ${OSCAR_DATA_PATH}
wget http://data.oscar-web.de/archive/de/index
wget http://data.oscar-web.de/archive/de/kvstore
wget http://data.oscar-web.de/archive/de/textsearch
```

# Using pyoscar
## Load the package:
```python
import pyoscar
```

## Load the data
```python
import pyoscar
import os

hdl = pyoscar.MainHandler()
hdl.energize(os.environ['OSCAR_DATA_PATH'])
```
## Issuing a query
```python
engine = hdl.engine()
result = engine.query("@highway in Stuttgart")
```

## Getting all cells
```python
cells = result.cells()
```

## Getting all item ids
```python
items = cells.items()
```

## Get the real item
```python
store = cmp.store()
for itemid in items:
	item = store.at(itemid)
	#do something?
```

# Semantics
## The Graph and the Store

OSCAR uses two ids to reference items and regions.
The store is indexed using an `itemId` whereas the Inclusion-Dag/Graph is indexed using a `graphId`.
Conversion between the two is only necessary for regions and is possible by using the functions `pyoscar.GeoHierarchy.itemId2GraphId` and `pyoscar.GeoHierarchy.graphId2StoreId` respectivley.
