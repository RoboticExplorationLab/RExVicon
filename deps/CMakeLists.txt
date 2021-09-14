include(FetchContent)

# Declare all dependencies first
# Allows for us to control shared dependencies
FetchContent_Declare(fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt
  GIT_TAG d141cdbeb0fb422a3fb7173b285fd38e0d1772dc # version 8.0.1
)

FetchContent_MakeAvailable(fmt)

########################################
# Download GoogleTest from source
########################################
if (${${OPTION_PREFIX}_BUILD_TESTS})
  FetchContent_Declare(googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
  )

  # For Windows: Prevent overriding the parent project's compiler/linker settings
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

  FetchContent_MakeAvailable(googletest)
endif()