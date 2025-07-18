# Harmony SDK Configuration Guide

This guide provides detailed configuration instructions for setting up and building the Harmony SDK integration project.

## Table of Contents

1. [Environment Setup](#environment-setup)
2. [Project Configuration](#project-configuration)
3. [Build Configuration](#build-configuration)
4. [SDK Integration](#sdk-integration)
5. [Development Environment](#development-environment)
6. [Deployment Configuration](#deployment-configuration)

## Environment Setup

### 1. Prerequisites Installation

#### HarmonyOS Development Environment
```bash
# Install DevEco Studio
# Download from: https://developer.harmonyos.com/en/develop/deveco-studio/

# Install HarmonyOS SDK
# API Level: 17 or later
# Build Tools: Latest version
```

#### Build Tools
```bash
# Install CMake (3.5.0 or later)
sudo apt-get install cmake  # Ubuntu/Debian
brew install cmake          # macOS
# Windows: Download from https://cmake.org/

# Install C++ compiler
sudo apt-get install build-essential  # Ubuntu/Debian
xcode-select --install                # macOS
# Windows: Install Visual Studio Build Tools
```

#### Node.js and npm
```bash
# Install Node.js (16.0 or later)
curl -fsSL https://deb.nodesource.com/setup_18.x | sudo -E bash -
sudo apt-get install -y nodejs

# Verify installation
node --version
npm --version
```

### 2. Project Structure Setup

```bash
# Clone the project
git clone <repository-url>
cd examples/Harmony

# Verify project structure
tree -L 4
# Expected structure:
# ├── entry/
# │   └── src/
# │       └── main/
# │           ├── cpp/
#                 └── AutelMobileSdk/
# │           ├── ets/
# │           └── resources/
# └── README.md
```

## Project Configuration

### 1. Package Configuration

#### Root Package (oh-package.json5)
```json5
{
  "name": "Harmony_sdk_example",
  "version": "1.0.0",
  "description": "Harmony SDK Integration Example",
  "main": "index.ets",
  "author": "Your Name",
  "license": "Apache-2.0",
  "dependencies": {},
  "devDependencies": {
    "@ohos/hypium": "1.0.0"
  },
  "repository": {
    "type": "git",
    "url": "https://github.com/your-repo/Harmony-sdk-example.git"
  }
}
```

#### Entry Module Package (entry/oh-package.json5)
```json5
{
  "name": "entry",
  "version": "1.0.0",
  "description": "Harmony SDK Entry Module",
  "main": "index.ets",
  "dependencies": {},
  "devDependencies": {
    "@ohos/hypium": "1.0.0"
  }
}
```

### 2. Build Configuration

#### Root Build Profile (build-profile.json5)
```json5
{
  "app": {
    "signingConfigs": [
      {
        "name": "default",
        "type": "HarmonyOS",
        "material": {
          "certpath": "signature/auto_debug.cer",
          "storePassword": "00000018A7F6B5DDD6C8F4E2A3B1C9D8E7F6A5B4C3D2E1F0",
          "keyAlias": "debugKey",
          "keyPassword": "00000018A7F6B5DDD6C8F4E2A3B1C9D8E7F6A5B4C3D2E1F0"
        }
      }
    ],
    "compileSdkVersion": 9,
    "compatibleSdkVersion": 9,
    "products": [
      {
        "name": "default",
        "signingConfig": "default"
      }
    ]
  },
  "modules": [
    {
      "name": "entry",
      "srcPath": "./entry",
      "targets": [
        {
          "name": "default",
          "applyToProducts": [
            "default"
          ]
        }
      ]
    }
  ]
}
```

#### Entry Module Build Profile (entry/build-profile.json5)
```json5
{
  "apiType": "OpenHarmony",
  "buildOption": {
    "externalNativeOptions": {
      "path": "./src/main/cpp/CMakeLists.txt",
      "arguments": "",
      "cppFlags": "",
      "cFlags": ""
    }
  },
  "targets": [
    {
      "name": "default",
      "runtimeOS": "HarmonyOS"
    }
  ]
}
```

### 3. Module Configuration

#### Entry Module (entry/src/main/module.json5)
```json5
{
  "module": {
    "name": "entry",
    "type": "entry",
    "description": "$string:module_desc",
    "mainElement": "EntryAbility",
    "deviceTypes": [
      "phone",
      "tablet"
    ],
    "deliveryWithInstall": true,
    "installationFree": false,
    "pages": "$profile:main_pages",
    "abilities": [
      {
        "name": "EntryAbility",
        "srcEntry": "./ets/entryability/EntryAbility.ets",
        "description": "$string:EntryAbility_desc",
        "icon": "$media:icon",
        "label": "$string:EntryAbility_label",
        "startWindowIcon": "$media:icon",
        "startWindowBackground": "$color:start_window_background",
        "exported": true,
        "skills": [
          {
            "entities": [
              "entity.system.home"
            ],
            "actions": [
              "action.system.home"
            ]
          }
        ]
      }
    ]
  }
}
```

## Build Configuration

### 1. CMake Configuration

#### Main CMakeLists.txt (entry/src/main/cpp/CMakeLists.txt)
```cmake
# Minimum CMake version
cmake_minimum_required(VERSION 3.5.0)
project(autelSdk)

# Set project root path
set(NATIVERENDER_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

# Include package find file if defined
if(DEFINED PACKAGE_FIND_FILE)
    include(${PACKAGE_FIND_FILE})
endif()

# Set AutelMobileSdk paths
set(AUTEL_SDK_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/AutelMobileSdk)
set(AUTEL_INCLUDE_DIR ${AUTEL_SDK_ROOT}/include)
set(AUTEL_LIB_DIR ${AUTEL_SDK_ROOT}/libs/${platform})

# Verify SDK paths
if(NOT EXISTS ${AUTEL_INCLUDE_DIR})
    message(FATAL_ERROR "AutelMobileSdk include directory not found: ${AUTEL_INCLUDE_DIR}")
endif()

if(NOT EXISTS ${AUTEL_LIB_DIR})
    message(FATAL_ERROR "AutelMobileSdk lib directory not found: ${AUTEL_LIB_DIR}")
endif()

# Include directories
include_directories(${NATIVERENDER_ROOT_PATH}
                    ${NATIVERENDER_ROOT_PATH}/include
                    ${AUTEL_INCLUDE_DIR})

# Compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0 -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DNDEBUG")

# Add library
add_library(autelSdk SHARED HarmonyMethods.cpp)

# Set library properties
set_target_properties(autelSdk PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

# Link libraries
target_link_libraries(autelSdk 
    PUBLIC 
    libace_napi.z.so 
    libhilog_ndk.z.so 
    librawfile.z.so
    
    ${AUTEL_LIB_DIR}/libautelsdk_protocol.so
    ${AUTEL_LIB_DIR}/libDroneFormation.so
    ${AUTEL_LIB_DIR}/libMappingPath.so
    ${AUTEL_LIB_DIR}/libprotobuf.so.32
    ${AUTEL_LIB_DIR}/libsimple_logger.so
    ${AUTEL_LIB_DIR}/libautelsdk.so.1
)

```

### 2. Hvigor Configuration

#### Root Hvigor (hvigorfile.ts)
```typescript
import { hvigor } from '@ohos/hvigor';

export default hvigor
  .project({
    name: 'Harmony_sdk_example',
    type: 'application'
  })
  .apply();
```

#### Entry Module Hvigor (entry/hvigorfile.ts)
```typescript
import { hvigor } from '@ohos/hvigor';

export default hvigor
  .project({
    name: 'entry',
    type: 'module'
  })
  .apply();
```

## SDK Integration

### 1. AutelMobileSdk Setup

#### Directory Structure
```
entry/src/main/cpp/AutelMobileSdk/
├── include/
│   ├── SdkApiManager.h
│   ├── ICamera.h
│   ├── IGimbal.h
│   └── ... (other headers)
├── lib/
│   ├── libautelsdk.so
│   └── ... (other libraries)
└── bin/
    ├── autelsdk_binaries
    └── ... (other binaries)
```

#### SDK Verification Script
```bash
#!/bin/bash
# verify_sdk.sh

SDK_ROOT="entry/src/main/cpp/AutelMobileSdk"
REQUIRED_HEADERS=("SdkApiManager.h" "ICamera.h" "IGimbal.h")
REQUIRED_LIBS=("libautelsdk.so" )

echo "Verifying AutelMobileSdk installation..."

# Check directories
if [ ! -d "$SDK_ROOT/include" ]; then
    echo "ERROR: Include directory not found"
    exit 1
fi

if [ ! -d "$SDK_ROOT/lib" ]; then
    echo "ERROR: Library directory not found"
    exit 1
fi

# Check headers
for header in "${REQUIRED_HEADERS[@]}"; do
    if [ ! -f "$SDK_ROOT/include/$header" ]; then
        echo "ERROR: Required header not found: $header"
        exit 1
    fi
done

# Check libraries
for lib in "${REQUIRED_LIBS[@]}"; do
    if [ ! -f "$SDK_ROOT/lib/$lib" ]; then
        echo "ERROR: Required library not found: $lib"
        exit 1
    fi
done

echo "SDK verification completed successfully!"
```

### 2. SDK Configuration

#### SDK Configuration File (SdkConfig.ini)
```ini
[SDK]
Version=1.0.0
DebugMode=true
LogLevel=INFO

[Paths]
IncludePath=entry/src/main/cpp/AutelMobileSdk/include
LibraryPath=entry/src/main/cpp/AutelMobileSdk/libs/${platform}/
BinaryPath=entry/src/main/cpp/AutelMobileSdk/bin

[Features]
Camera=true
Gimbal=true
FlightControl=true
Mission=true
```

## Development Environment

### 1. DevEco Studio Configuration

#### Project Settings
1. **Open Project**: Open the project in DevEco Studio
2. **SDK Configuration**: 
   - Go to File → Project Structure
   - Set HarmonyOS SDK path
   - Configure API level (9 or later)
3. **Build Configuration**:
   - Set build variant (debug/release)
   - Configure signing certificates

#### Code Style Configuration
```json
// .editorconfig
root = true

[*]
charset = utf-8
end_of_line = lf
insert_final_newline = true
trim_trailing_whitespace = true

[*.{cpp,h}]
indent_style = space
indent_size = 2

[*.{ts,ets}]
indent_style = space
indent_size = 2

[*.{json,json5}]
indent_style = space
indent_size = 2
```

### 2. Debug Configuration

#### Launch Configuration
```json
// .vscode/launch.json
{
  "version": "0.2.0",
  "configurations": [
    {
      "name": "Debug Harmony SDK",
      "type": "node",
      "request": "launch",
      "program": "${workspaceFolder}/entry/src/main/ets/pages/Index.ets",
      "args": [],
      "env": {
        "DEBUG": "Harmony:*"
      }
    }
  ]
}
```

#### Debug Scripts
```bash
#!/bin/bash
# debug.sh

echo "Starting Harmony SDK debug session..."

# Enable debug logging
export Harmony_DEBUG=true
export Harmony_LOG_LEVEL=DEBUG

# Build in debug mode
hvigor build --mode debug

# Install on device
hdc file send ./build/outputs/hap/debug/phone/entry-debug-unsigned.hap /data/local/tmp/
hdc shell bm install -p /data/local/tmp/entry-debug-unsigned.hap

# Start debugging
hdc shell hilog | grep Harmony
```

## Deployment Configuration

### 1. Release Configuration

#### Release Build Profile
```json5
// build-profile-release.json5
{
  "app": {
    "signingConfigs": [
      {
        "name": "release",
        "type": "HarmonyOS",
        "material": {
          "certpath": "signature/release.cer",
          "storePassword": "your-release-password",
          "keyAlias": "releaseKey",
          "keyPassword": "your-key-password"
        }
      }
    ],
    "products": [
      {
        "name": "release",
        "signingConfig": "release"
      }
    ]
  }
}
```

#### Release Script
```bash
#!/bin/bash
# release.sh

echo "Building release version..."

# Clean previous builds
hvigor clean

# Build release version
hvigor build --mode release

# Sign the application
hvigor sign --mode release

# Create release package
hvigor package --mode release

echo "Release build completed!"
```

### 2. CI/CD Configuration

#### GitHub Actions Workflow
```yaml
# .github/workflows/build.yml
name: Build Harmony SDK

on:
  push:
    branches: [ main ]
  pull_request:
    branches: [ main ]

jobs:
  build:
    runs-on: ubuntu-latest
    
    steps:
    - uses: actions/checkout@v3
    
    - name: Setup Node.js
      uses: actions/setup-node@v3
      with:
        node-version: '18'
    
    - name: Setup HarmonyOS SDK
      run: |
        # Download and setup HarmonyOS SDK
        # This is a placeholder for actual setup
    
    - name: Verify SDK
      run: |
        chmod +x verify_sdk.sh
        ./verify_sdk.sh
    
    - name: Build Project
      run: |
        hvigor build --mode debug
    
    - name: Run Tests
      run: |
        hvigor test
    
    - name: Upload Artifacts
      uses: actions/upload-artifact@v3
      with:
        name: Harmony-sdk-build
        path: build/outputs/
```

### 3. Environment Variables

#### Development Environment
```bash
# .env.development
Harmony_DEBUG=true
Harmony_LOG_LEVEL=DEBUG
Harmony_SDK_PATH=entry/src/main/cpp/AutelMobileSdk
Harmony_API_VERSION=9
```

#### Production Environment
```bash
# .env.production
Harmony_DEBUG=false
Harmony_LOG_LEVEL=WARN
Harmony_SDK_PATH=entry/src/main/cpp/AutelMobileSdk
Harmony_API_VERSION=9
```

## Troubleshooting

### 1. Common Build Issues

#### CMake Errors
```bash
# Error: Cannot find napi/native_api.h
# Solution: Ensure HarmonyOS SDK is properly installed
export HARMONYOS_SDK_PATH=/path/to/harmonyos/sdk

# Error: Cannot find AutelMobileSdk libraries
# Solution: Verify SDK installation
./verify_sdk.sh
```

#### Hvigor Errors
```bash
# Error: Module not found
# Solution: Check module.json5 configuration
hvigor clean
hvigor build --mode debug

# Error: Signing failed
# Solution: Check certificate configuration
hvigor sign --mode debug
```

### 2. Runtime Issues

#### SDK Initialization Failures
```bash
# Check logs
hdc shell hilog | grep Harmony

# Verify SDK files
hdc shell ls -la /data/local/tmp/libautelsdk.so
```

#### Permission Issues
```bash
# Grant necessary permissions
hdc shell chmod +x /data/local/tmp/lib*.so
```

## Configuration Checklist

- [ ] Environment setup completed
- [ ] SDK verification passed
- [ ] Build configuration tested
- [ ] Debug environment configured
- [ ] Release signing configured
- [ ] CI/CD pipeline tested
- [ ] Documentation updated
- [ ] Performance benchmarks met

## Support

For configuration issues:
1. Check the troubleshooting section
2. Verify all prerequisites are installed
3. Review build logs for specific errors
4. Consult the development guide
5. Contact the development team
