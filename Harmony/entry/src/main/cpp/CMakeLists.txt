# the minimum version of CMake.
cmake_minimum_required(VERSION 3.4.1)
project(MsdkHarmony)


set(NATIVERENDER_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

if(DEFINED PACKAGE_FIND_FILE)
    include(${PACKAGE_FIND_FILE})
endif()

# Set AutelMobileSdk paths
#set(AUTEL_SDK_ROOT ${NATIVERENDER_ROOT_PATH}/AutelMobileSdk)
#set(AUTEL_INCLUDE_DIR ${AUTEL_SDK_ROOT}/include)
#set(AUTEL_LIB_DIR ${AUTEL_SDK_ROOT}/libs/${CMAKE_OHOS_ARCH_ABI})
#set(AUTEL_BIN_DIR ${AUTEL_SDK_ROOT}/bin)

# Add library
add_library(autel_sdk SHARED AutelSdkMethods.cpp)

# Set target properties
#set_target_properties(autel_sdk PROPERTIES
#    CXX_STANDARD 17
#    CXX_STANDARD_REQUIRED ON
#)

#target_link_directories(autel_sdk PUBLIC
#    ${AUTEL_LIB_DIR}
#)

#target_include_directories(autel_sdk PRIVATE
#     ${NATIVERENDER_ROOT_PATH}
#     ${AUTEL_INCLUDE_DIR}
#     ${AUTEL_INCLUDE_DIR}/key_manager
#     ${AUTEL_INCLUDE_DIR}/data_type
#)

#set_target_properties(autel_sdk PROPERTIES
#    INSTALL_RPATH "${AUTEL_LIB_DIR}"
#    INSTALL_RPATH_USE_LINK_PATH TRUE
#)

message(Warn "current target=${CMAKE_OHOS_ARCH_ABI}")
# Link libraries
target_link_libraries(autel_sdk
    PUBLIC
    libace_napi.z.so
    libhilog_ndk.z.so
    librawfile.z.so

    #${AUTEL_LIB_DIR}/libsimple_logger.so
    #${AUTEL_LIB_DIR}/libMappingPath.so
    #${AUTEL_LIB_DIR}/libDroneFormation.so
    #${AUTEL_LIB_DIR}/libprotobuf.so.32
    #${AUTEL_LIB_DIR}/libautelsdk_protocol.so
    #${AUTEL_LIB_DIR}/libautelsdk.so.1
    ${NATIVERENDER_ROOT_PATH}/../../../libs/${OHOS_ARCH}/libnativeAdd.so
)

#    ${AUTEL_LIB_DIR}/libautelch.so
# Print debug information
#message(STATUS "AUTEL_SDK_ROOT: ${AUTEL_SDK_ROOT}")
#message(STATUS "AUTEL_INCLUDE_DIR: ${AUTEL_INCLUDE_DIR}")
#message(STATUS "AUTEL_LIB_DIR: ${AUTEL_LIB_DIR}")