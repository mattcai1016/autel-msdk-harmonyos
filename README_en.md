# MSDK Platform Examples

This directory contains example applications demonstrating the usage of MSDK across different platforms. Each platform-specific directory includes complete, runnable examples with detailed documentation.

## Directory Structure

```
examples/
├── README.md           # This file
├── Harmony/           # HarmonyOS platform examples
│   ├── README.md      # Platform-specific documentation
│   └── [examples]/    # Individual example applications
├── Linux/             # Linux platform examples
│   ├── README.md      # Platform-specific documentation
│   └── [examples]/    # Individual example applications
└── [other platforms]/ # Additional platform examples
```

## Platform-Specific Examples

### HarmonyOS
The `Harmony/` directory contains examples specifically designed for HarmonyOS platform. Each example demonstrates different aspects of MSDK integration and usage.

### Linux
The `Linux/` directory contains examples for Linux-based systems. These examples cover various MSDK features and use cases.

## Example Structure

Each example application follows this standard structure:

```
[example-name]/
├── README.md          # Example-specific documentation
├── src/              # Source code
├── include/          # Header files
├── CMakeLists.txt    # Build configuration
└── docs/             # Additional documentation
```

## Documentation Guidelines

Each example should include:

1. **Overview**: Brief description of what the example demonstrates
2. **Prerequisites**: Required dependencies and setup
3. **Build Instructions**: Step-by-step build process
4. **Usage**: How to run and use the example
5. **Code Explanation**: Key implementation details
6. **Expected Output**: Sample output or behavior
7. **Troubleshooting**: Common issues and solutions

## Contributing

When adding new examples:

1. Create a new directory under the appropriate platform folder
2. Follow the standard example structure
3. Include comprehensive documentation
4. Ensure the example is complete and runnable
5. Test the example on the target platform
6. Update this README.md if adding a new platform

## Support

For issues or questions regarding the examples, please:

1. Check the platform-specific README.md
2. Review the example's documentation
3. Open an issue in the project repository