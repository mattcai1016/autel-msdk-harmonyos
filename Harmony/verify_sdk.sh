#!/bin/bash

# Harmong SDK Verification Script
# This script verifies that the AutelMobileSdk is properly installed and configured

set -e  # Exit on any error

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Configuration
SDK_ROOT="entry/src/main/cpp/AutelMobileSdk"
REQUIRED_HEADERS=(
    "SdkApiManager.h"
    "ICamera.h"
    "IGimbal.h"
    "IFlightControl.h"
    "IFlightMission.h"
    "IFlightParams.h"
    "IDeviceMng.h"
    "IAirLink.h"
    "IVision.h"
    "IAlbum.h"
    "ISetting.h"
    "IMisc.h"
    "IMissionManager.h"
    "SdkConfig.h"
)

REQUIRED_LIBS=(
    "libautelsdk.so.1"
    "libautelsdk_protocol.so"
    "libDroneFormation.so"
    "libMappingPath.so"
    "libprotobuf.so.32"
    "libsimple_logger.so"
)

REQUIRED_BINS=(
    "Autelsdk_binaries"
)

# Function to print colored output
print_status() {
    local status=$1
    local message=$2
    
    case $status in
        "INFO")
            echo -e "${BLUE}[INFO]${NC} $message"
            ;;
        "SUCCESS")
            echo -e "${GREEN}[SUCCESS]${NC} $message"
            ;;
        "WARNING")
            echo -e "${YELLOW}[WARNING]${NC} $message"
            ;;
        "ERROR")
            echo -e "${RED}[ERROR]${NC} $message"
            ;;
    esac
}

# Function to check if file exists
check_file() {
    local file_path=$1
    local file_type=$2
    
    if [ -f "$file_path" ]; then
        print_status "SUCCESS" "Found $file_type: $file_path"
        return 0
    else
        print_status "ERROR" "Missing $file_type: $file_path"
        return 1
    fi
}

# Function to check if directory exists
check_directory() {
    local dir_path=$1
    local dir_type=$2
    
    if [ -d "$dir_path" ]; then
        print_status "SUCCESS" "Found $dir_type: $dir_path"
        return 0
    else
        print_status "ERROR" "Missing $dir_type: $dir_path"
        return 1
    fi
}

# Main verification function
verify_sdk() {
    print_status "INFO" "Starting AutelMobileSdk verification..."
    print_status "INFO" "SDK Root: $SDK_ROOT"
    
    local has_errors=false
    
    # Check if SDK root exists
    if [ ! -d "$SDK_ROOT" ]; then
        print_status "ERROR" "SDK root directory not found: $SDK_ROOT"
        print_status "ERROR" "Please ensure AutelMobileSdk is installed in the correct location"
        exit 1
    fi
    
    # Check include directory
    local include_dir="$SDK_ROOT/include"
    if ! check_directory "$include_dir" "include directory"; then
        has_errors=true
    fi
    
    # Check lib directory
    local lib_dirx86_64="$SDK_ROOT/libs/x86_64"
    if ! check_directory "$lib_dirx86_64" "library x86_64 directory"; then
        has_errors=true
    fi
    # Check lib directory
    local lib_dirarm64_v8a="$SDK_ROOT/libs/arm64-v8a"
    if ! check_directory "$lib_dirarm64_v8a" "library arm64-v8a directory"; then
        has_errors=true
    fi
    
    # Check required headers
    print_status "INFO" "Verifying required headers..."
    for header in "${REQUIRED_HEADERS[@]}"; do
        local header_path="$include_dir/$header"
        if ! check_file "$header_path" "header"; then
            has_errors=true
        fi
    done
    
    # Check required libraries
    print_status "INFO" "Verifying required libraries..."
    for lib in "${REQUIRED_LIBS[@]}"; do
        local lib_path="$lib_dirarm64_v8a/$lib"
        if ! check_file "$lib_path" "library"; then
            has_errors=true
        fi
        local lib_path1="$lib_dirx86_64/$lib"
        if ! check_file "$lib_path1" "library"; then
            has_errors=true
        fi
    done
    
    # Check file permissions
    print_status "INFO" "Checking file permissions..."
    for lib in "${REQUIRED_LIBS[@]}"; do
        local lib_path="$lib_dir/$lib"
        if [ -f "$lib_path" ]; then
            if [ -r "$lib_path" ]; then
                print_status "SUCCESS" "Library is readable: $lib"
            else
                print_status "ERROR" "Library is not readable: $lib"
                has_errors=true
            fi
        fi
    done
    
    # Check CMakeLists.txt compatibility
    print_status "INFO" "Checking CMakeLists.txt compatibility..."
    local cmake_file="entry/src/main/cpp/CMakeLists.txt"
    if [ -f "$cmake_file" ]; then
        if grep -q "SDK_ROOT" "$cmake_file"; then
            print_status "SUCCESS" "CMakeLists.txt contains SDK path configuration"
        else
            print_status "WARNING" "CMakeLists.txt may not be properly configured for SDK paths"
        fi
    else
        print_status "ERROR" "CMakeLists.txt not found: $cmake_file"
        has_errors=true
    fi
    
    # Check HarmonyOS SDK compatibility
    print_status "INFO" "Checking HarmonyOS SDK compatibility..."
    if command -v hvigor >/dev/null 2>&1; then
        print_status "SUCCESS" "Hvigor build tool is available"
    else
        print_status "WARNING" "Hvigor build tool not found in PATH"
    fi
    
    if [ -n "$HARMONYOS_SDK_PATH" ]; then
        print_status "SUCCESS" "HarmonyOS SDK path is set: $HARMONYOS_SDK_PATH"
    else
        print_status "WARNING" "HarmonyOS SDK path not set in environment"
    fi
    
    # Summary
    echo ""
    if [ "$has_errors" = true ]; then
        print_status "ERROR" "SDK verification failed. Please fix the errors above."
        print_status "INFO" "Common solutions:"
        print_status "INFO" "1. Download and install AutelMobileSdk"
        print_status "INFO" "2. Extract SDK to third_party/AutelMobileSdk/"
        print_status "INFO" "3. Ensure all required files are present"
        print_status "INFO" "4. Check file permissions"
        exit 1
    else
        print_status "SUCCESS" "SDK verification completed successfully!"
        print_status "INFO" "All required files and directories are present"
        print_status "INFO" "You can now build the Harmong SDK integration project"
    fi
}

# Function to show usage
show_usage() {
    echo "Usage: $0 [OPTIONS]"
    echo ""
    echo "Options:"
    echo "  -h, --help     Show this help message"
    echo "  -v, --verbose  Enable verbose output"
    echo "  -q, --quiet    Suppress non-error output"
    echo ""
    echo "This script verifies that the AutelMobileSdk is properly installed"
    echo "and configured for the Harmong SDK integration project."
}

# Parse command line arguments
VERBOSE=false
QUIET=false

while [[ $# -gt 0 ]]; do
    case $1 in
        -h|--help)
            show_usage
            exit 0
            ;;
        -v|--verbose)
            VERBOSE=true
            shift
            ;;
        -q|--quiet)
            QUIET=true
            shift
            ;;
        *)
            print_status "ERROR" "Unknown option: $1"
            show_usage
            exit 1
            ;;
    esac
done

# Run verification
verify_sdk 