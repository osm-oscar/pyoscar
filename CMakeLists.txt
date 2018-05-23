cmake_minimum_required(VERSION 3.9)
project(pyoscar)

set(Python_ADDITIONAL_VERSIONS 3.4 3.5 3.6 3.7)

find_package(PythonInterp 3 REQUIRED)
find_package(PythonLibs 3 REQUIRED)
find_package(Boost COMPONENTS python-py35 REQUIRED)

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
	src/exports.cpp
)

set(SOURCES_H
	include/pyoscar/MainHandler.h
	include/pyoscar/OsmKeyValueObjectStore.h
	include/pyoscar/RelationHelpers.h
	include/pyoscar/ItemIndexStore.h
	include/pyoscar/ItemIndex.h
	include/pyoscar/CellQueryResult.h
	include/pyoscar/StaticOsmCompleter.h
)

set(MY_LINK_LIBRARIES
	${Boost_LIBRARIES}
	${PYTHON_LIBRARIES}
	${Boost_LIBRARIES}
	${LIBOSCAR_LINK_LIBRARIES}
	${Boost_LIBRARIES}
)

PYTHON_ADD_MODULE(${PROJECT_NAME} ${SOURCES_CPP} ${SOURCES_H})

target_link_libraries(${PROJECT_NAME} ${MY_LINK_LIBRARIES})
target_compile_definitions(${PROJECT_NAME} PUBLIC
	${LIBOSCAR_COMPILE_DEFINITIONS}
)
