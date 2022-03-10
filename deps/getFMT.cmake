include(FetchContent)

# Declare all dependencies first
# Allows for us to control shared dependencies
FetchContent_Declare(fmt
	GIT_REPOSITORY https://github.com/fmtlib/fmt
	GIT_TAG d141cdbeb0fb422a3fb7173b285fd38e0d1772dc # version 8.0.1
)

FetchContent_GetProperties(fmt)
if(NOT fmt_POPULATED)
  FetchContent_Populate(fmt)
  # set(fmt_DIR ${PROJECT_BINARY_DIR}/_deps/fmt-build/)
  add_subdirectory(${fmt_SOURCE_DIR} ${fmt_BINARY_DIR})
endif()
