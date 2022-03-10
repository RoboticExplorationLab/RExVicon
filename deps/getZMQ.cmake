include(FetchContent)

FetchContent_Declare(libzmq
  GIT_REPOSITORY https://github.com/zeromq/libzmq
  GIT_TAG 4097855ddaaa65ed7b5e8cb86d143842a594eebd # version 4.3.4
)
FetchContent_Declare(cppzmq
  GIT_REPOSITORY https://github.com/zeromq/cppzmq.git
  GIT_TAG 267d300d1c99381a0fbc7e060ae2899e51f5e425 # version 4.8.0
)

if(NOT libzmq_POPULATED)
  FetchContent_Populate(libzmq)
  set(ZMQ_BUILD_TESTS OFF CACHE BOOL "Test suite for libzmq")
  # To enable building on macOS, see github issue https://github.com/zeromq/libzmq/issues/4085
  set(WITH_TLS OFF CACHE INTERNAL "Disable TLS support")
  add_subdirectory(${libzmq_SOURCE_DIR} ${libzmq_BINARY_DIR})
endif()

if(NOT cppzmq_POPULATED)
  FetchContent_Populate(cppzmq)
  set(ZeroMQ_DIR ${PROJECT_BINARY_DIR}/_deps/libzmq-build/)
  set(CPPZMQ_BUILD_TESTS OFF CACHE BOOL "Test suite for cppzmq")
  add_subdirectory(${cppzmq_SOURCE_DIR} ${cppzmq_BINARY_DIR})
endif()