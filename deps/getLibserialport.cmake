include(FetchContent)

# Declare all dependencies first
# Allows for us to control shared dependencies
FetchContent_Declare(libserialport
    GIT_REPOSITORY "https://github.com/sigrokproject/libserialport"
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
)

FetchContent_GetProperties(libserialport)

if(NOT libserialport_POPULATED)
    FetchContent_Populate(libserialport)

    execute_process(COMMAND ./autogen.sh
        WORKING_DIRECTORY
            ${libserialport_SOURCE_DIR}
    )
    execute_process(COMMAND ./configure
        WORKING_DIRECTORY
            ${libserialport_SOURCE_DIR}
    )
    execute_process(COMMAND make
        WORKING_DIRECTORY
            ${libserialport_SOURCE_DIR}
    )
endif()
