cmake_minimum_required(VERSION 3.16)
project(pyoscar)


#todo make this working with other python versions
set(Python_ADDITIONAL_VERSIONS 3.9 3.10)

find_package(PythonInterp REQUIRED)
find_package(PythonLibs REQUIRED)

find_package(Boost COMPONENTS python3 python-py39 python-py310)

#todo: check against which python version were linking and use the appropriate boost version
if (${Boost_PYTHON3_FOUND})
	set(MY_BOOST_LIBRARIES ${Boost_PYTHON3_LIBRARY})
elseif (${Boost_PYTHON-PY310_FOUND})
	set(MY_BOOST_LIBRARIES ${Boost_PYTHON-PY310_LIBRARY})
elseif (${Boost_PYTHON-PY39_FOUND})
	set(MY_BOOST_LIBRARIES ${Boost_PYTHON-PY39_LIBRARY})
else()
	message(FATAL_ERROR "Could not find any suitable boost python version")
endif()

add_subdirectory(vendor/liboscar liboscar)

set(SOURCES_CPP
	src/MainHandler.cpp
	src/OsmKeyValueObjectStore.cpp
	src/StaticOsmCompleter.cpp
	src/RelationHelpers.cpp
	src/ItemIndexStore.cpp
	src/ItemIndex.cpp
	src/CellQueryResult.cpp
	src/GeoHierarchy.cpp
	src/refcounting.cpp
	src/CellManipulation.cpp
	src/GeoShape.cpp
	src/GeoRect.cpp
	src/exports.cpp
)

set(SOURCES_H
	include/pyoscar/MainHandler.h
	include/pyoscar/OsmKeyValueObjectStore.h
	include/pyoscar/RelationHelpers.h
	include/pyoscar/ItemIndexStore.h
	include/pyoscar/ItemIndex.h
	include/pyoscar/CellQueryResult.h
	include/pyoscar/GeoHierarchy.h
	include/pyoscar/StaticOsmCompleter.h
	include/pyoscar/refcounting.h
	include/pyoscar/CellManipulation.h
	include/pyoscar/GeoRect.h
	include/pyoscar/GeoShape.h
)

PYTHON_ADD_MODULE(${PROJECT_NAME} ${SOURCES_CPP} ${SOURCES_H})

target_link_libraries(${PROJECT_NAME}
	${MY_BOOST_LIBRARIES}
	${PYTHON_LIBRARIES}
	liboscar
	${MY_BOOST_LIBRARIES}
)
target_include_directories(${PROJECT_NAME} PRIVATE
	${Boost_INCLUDE_DIRS}
	${PYTHON_INCLUDE_DIRS}
	${CMAKE_CURRENT_SOURCE_DIR}/include
)
