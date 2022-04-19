cmake_minimum_required(VERSION 3.5)
project(vicon-datastream-sdk)

set (CMAKE_CXX_STANDARD 11)

find_package(Boost 1.5 COMPONENTS system thread REQUIRED)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/DataStream
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Declare a cpp library
add_library(ViconDataStreamSDK_CPP STATIC

    DataStream/ViconDataStreamSDKCore/CoreClient.cpp
    DataStream/ViconDataStreamSDKCore/CoreClientTimingLog.cpp
    DataStream/ViconDataStreamSDKCoreUtils/ClientUtils.cpp
    DataStream/ViconDataStreamSDKCoreUtils/AxisMapping.cpp
    DataStream/ViconDataStreamSDKCore/WirelessConfiguration.cpp
    DataStream/ViconCGStreamClientSDK/CGClient.cpp
    DataStream/ViconCGStreamClient/ViconCGStreamClient.cpp
    DataStream/ViconCGStreamClient/CGStreamReaderWriter.cpp
    DataStream/ViconCGStreamClient/ViconCGStreamBayer.cpp
    DataStream/ViconDataStreamSDK_CPP/DataStreamClient.cpp
    # StreamCommon
    # ViconCGStream
    # ViconCGStreamClient
    # ViconCGStreamClientSDK
    # ViconDataStreamSDKCore
)

target_link_libraries(ViconDataStreamSDK_CPP
    PRIVATE
        Boost::system
        Boost::thread
        Threads::Threads
)

target_include_directories(ViconDataStreamSDK_CPP PUBLIC
    DataStream/ViconDataStreamSDK_CPP
)

target_compile_definitions(ViconDataStreamSDK_CPP PRIVATE "_BUILD_STATIC_LIB")

add_library(ViconSDK::ViconSDK ALIAS ViconDataStreamSDK_CPP)