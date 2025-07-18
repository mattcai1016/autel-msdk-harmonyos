# Harmony SDK Integration Example

This example demonstrates how to integrate the Autel Mobile SDK with HarmonyOS applications using the Native API (NAPI) bridge.

## Overview

The Harmony SDK Integration example provides a complete implementation of:

- Native C++ SDK integration using NAPI
- TypeScript/ArkTS UI interface
- Error handling and logging
- Resource management and localization

## Project Structure

```
examples/MsdkHarmony/
├── entry/src/main/
│   ├── cpp/                    # Native C++ implementation
│   │   ├── AutelSdkMethods.cpp # NAPI bridge functions
│   │   ├── CMakeLists.txt      # C++ build configuration
│   │   ├── types/              # Type definitions
│   │   └── AutelMobileSdk/     # SDK dependencies
│   │       ├── include/        # SDK headers
│   │       │   ├── key_manager/
│   │       │   ├── data_type/
│   │       │   ├── autelsdk-support/
│   │       │   └── *.h         # SDK header files
│   │       └── libs/           # SDK libraries
│   │           ├── arm64-v8a/  # ARM64 libraries
│   │           └── x86_64/     # x86_64 libraries
│   ├── ets/                    # TypeScript/ArkTS UI
│   │   ├── pages/
│   │   │   └── Index.ets       # Main UI component
│   │   ├── common/utils/
│   │   │   └── Logger.ets      # Logging utility
│   │   ├── entryability/       # Entry ability
│   │   └── entrybackupability/ # Backup ability
│   ├── resources/              # Localization resources
│   │   ├── base/element/
│   │   │   ├── string.json     # UI text resources
│   │   │   └── color.json      # Color definitions
│   │   ├── zh_CN/             # Chinese localization
│   │   └── en_US/             # English localization
│   └── module.json5           # Module configuration
├── AppScope/                   # Application scope
│   ├── app.json5              # App configuration
│   └── resources/             # App-level resources
├── docs/                      # Documentation
│   ├── harmony应用msdk.md     # Main documentation
│   ├── 异步回调接口API_Lv2_Async_Usage_Guide.md
│   ├── 多级模块接口API_Lv2_Usage_Guide.md
│   └── *.cpp, *.d.ts, *.ets  # API examples
├── screenshots/               # Project screenshots
├── hvigor/                   # Build configuration
├── oh_modules/               # Dependencies
├── .hvigor/                  # Build cache
├── .idea/                    # IDE configuration
├── verify_sdk.sh            # SDK verification script
├── log.txt                  # Build logs
├── oh-package.json5         # Package configuration
├── build-profile.json5      # Build profile
├── hvigorfile.ts           # Build script
├── CONFIGURATION_GUIDE.md  # Configuration guide
├── DEVELOPMENT_GUIDE.md    # Development guide
├── LICENSE                 # License file
├── .clangd                 # Clangd configuration
├── .clang-format          # Code formatting rules
└── .clang-tidy            # Code analysis rules
```

## Features

### Core SDK Functions

- **SDK Initialization**: Initialize the Autel Mobile SDK with debug mode support
- **Version Management**: Get SDK version and full version information
- **Resource Management**: Proper SDK cleanup and resource management

### UI Features

- **Interactive Interface**: User-friendly buttons for all SDK operations
- **Status Display**: Real-time status updates and error messages
- **Loading Indicators**: Visual feedback during operations
- **Localization**: Multi-language support through resource files
- **Error Handling**: Comprehensive error display and logging

### Technical Features

- **NAPI Bridge**: Robust C++ to TypeScript communication
- **Exception Handling**: Comprehensive error handling in both C++ and TypeScript
- **Logging**: Detailed logging for debugging and monitoring
- **Memory Management**: Proper resource cleanup and memory management
- **Type Safety**: Strong typing for all API calls and responses

## Prerequisites

1. **HarmonyOS Development Environment**
   
   - DevEco Studio 4.0 or later
   - HarmonyOS SDK API 17 or later
   - Node.js 16.0 or later

2. **Autel Mobile SDK**
   
   - Autel Mobile SDK libraries and headers
   - Proper SDK licensing and registration

3. **Build Tools**
   
   - CMake 3.5.0 or later
   - C++ compiler supporting C++11 or later

## Installation

1. **Clone the Repository**
   
   ```bash
   git clone <repository-url>
   cd examples/Harmony
   ```

2. **Setup SDK Dependencies**
   
   - Ensure Autel Mobile SDK is properly installed in `third_party/AutelMobileSdk/`
   - Verify all required libraries are present in the `lib/` directory
   - Check that headers are available in the `include/` directory

3. **Build Configuration**
   
   - The project uses CMake for C++ compilation
   - NAPI module is automatically registered during build
   - TypeScript/ArkTS code is compiled by the HarmonyOS build system

## Usage

### Basic SDK Operations

1. **Initialize SDK**
   
   ```typescript
   const result = await HarmonySdk.initSdk(true); // Enable debug mode
   if (result.success) {
     console.log('SDK initialized successfully');
   }
   ```

2. **Get SDK Version**
   
   ```typescript
   const result = await HarmonySdk.getSdkVersion();
   if (result.success) {
     console.log('SDK Version:', result.version);
   }
   ```

3. **Destroy SDK**
   
   ```typescript
   const result = await HarmonySdk.destroySdk();
   if (result.success) {
     console.log('SDK destroyed successfully');
   }
   ```

### Error Handling

All SDK functions return a consistent result object:

```typescript
interface SdkResult {
  success: boolean;
  message: string;
  [key: string]: any; // Additional data specific to each function
}
```

Example error handling:

```typescript
try {
  const result = await HarmonySdk.initSdk(true);
  if (result.success) {
    // Handle success
    console.log(result.message);
  } else {
    // Handle error
    console.error('SDK Error:', result.message);
  }
} catch (error) {
  // Handle exception
  console.error('Exception:', error);
}
```

### Logging

The application includes comprehensive logging:

```typescript
import Logger from '../common/utils/Logger';

// Log levels
Logger.info('Information message');
Logger.debug('Debug message');
Logger.warn('Warning message');
Logger.error('Error message');
Logger.fatal('Fatal error message');
```

## API Reference

### HarmonySdk Module

#### `initSdk(debugMode: boolean): Promise<SdkResult>`

Initializes the Harmony SDK.

- **Parameters:**
  - `debugMode`: Enable debug mode for detailed logging
- **Returns:** Promise with initialization result

#### `getSdkVersion(): Promise<SdkResult>`

Retrieves the SDK version.

- **Returns:** Promise with version information in `result.version`

#### `getSdkFullVersion(): Promise<SdkResult>`

Retrieves the full SDK version information.

- **Returns:** Promise with full version in `result.fullVersion`

#### `destroySdk(): Promise<SdkResult>`

Destroys the SDK and cleans up resources.

- **Returns:** Promise with destruction result

## Building and Running

1. **Open in DevEco Studio**
   
   ```bash
   # Open the project in DevEco Studio
   # Or use command line build
   ```

2. **Build the Project**
   
   ```bash
   # Build C++ components
   cd entry/src/main/cpp
   mkdir build && cd build
   cmake ..
   make
   
   # Build HarmonyOS application
   # Use DevEco Studio or hvigor build system
   ```

3. **Run on Device**
   
   - Connect a HarmonyOS device or emulator
   - Deploy the application
   - Test SDK functionality through the UI

## Troubleshooting

### Common Issues

1. **SDK Not Found**
   
   - Verify Autel Mobile SDK is properly installed
   - Check library paths in CMakeLists.txt
   - Ensure all required dependencies are present

2. **Initialization Failures**
   
   - Check SDK licensing and registration
   - Verify device compatibility
   - Review debug logs for detailed error information

3. **Build Errors**
   
   - Ensure CMake version compatibility
   - Check C++ compiler support
   - Verify HarmonyOS SDK installation

4. **Runtime Errors**
   
   - Check device permissions
   - Verify SDK initialization order
   - Review application logs

### Debug Mode

Enable debug mode for detailed logging:

```typescript
const result = await HarmonySdk.initSdk(true);
```

Debug logs will be available in the device logs and can be viewed using:

```bash
hdc shell hilog
```

## Contributing

1. Follow the existing code style and patterns
2. Add comprehensive error handling
3. Include proper logging for new features
4. Update documentation for any API changes
5. Test thoroughly on target devices

## License

This project is licensed under the Apache License 2.0. See the LICENSE file for details.

## Support

For issues and questions:

1. Check the troubleshooting section
2. Review the logs for error details
3. Consult the Autel Mobile SDK documentation
4. Contact the development team

## Version History

- **v1.0.0**: Initial implementation with basic SDK integration
- **v1.1.0**: Added comprehensive error handling and logging
- **v1.2.0**: Enhanced UI with localization support
- **v1.3.0**: Added additional SDK functions and validation 
