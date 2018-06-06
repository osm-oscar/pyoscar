cmake_minimum_required(VERSION 3.9)
project(pyoscar)


#todo make this working with other python versions
set(Python_ADDITIONAL_VERSIONS 3.5 3.6 3.7)

find_package(PythonInterp 3.5 REQUIRED)
find_package(PythonLibs 3.5 REQUIRED)

find_package(Boost COMPONENTS python3 python-py35 python-py36 python-py37)

#todo: check against which python version were linking and use the appropriate boost version
if (${Boost_PYTHON3_FOUND})
	set(MY_BOOST_LIBRARIES ${Boost_PYTHON3_LIBRARY})
elseif (${Boost_PYTHON-PY37_FOUND})
	set(MY_BOOST_LIBRARIES ${Boost_PYTHON-PY37_LIBRARY})
elseif (${Boost_PYTHON-PY36_FOUND})
	set(MY_BOOST_LIBRARIES ${Boost_PYTHON-PY36_LIBRARY})
elseif (${Boost_PYTHON-PY35_FOUND})
	set(MY_BOOST_LIBRARIES ${Boost_PYTHON-PY35_LIBRARY})
else()
	message(FATAL_ERROR "Could not find any suitable boost python version")
endif()

add_subdirectory(vendor/liboscar liboscar)

include_directories(
	${Boost_INCLUDE_DIRS}
	${PYTHON_INCLUDE_DIRS}
	${LIBOSCAR_INCLUDE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

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
)

set(MY_LINK_LIBRARIES
	${MY_BOOST_LIBRARIES}
	${PYTHON_LIBRARIES}
	${LIBOSCAR_LINK_LIBRARIES}
	${MY_BOOST_LIBRARIES}
)

PYTHON_ADD_MODULE(${PROJECT_NAME} ${SOURCES_CPP} ${SOURCES_H})

target_link_libraries(${PROJECT_NAME} ${MY_LINK_LIBRARIES})
target_compile_definitions(${PROJECT_NAME} PUBLIC
	${LIBOSCAR_COMPILE_DEFINITIONS}
)
