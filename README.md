# GoDareDI Framework

[![iOS](https://img.shields.io/badge/iOS-18.0+-blue.svg)](https://developer.apple.com/ios/)
[![Swift](https://img.shields.io/badge/Swift-6.0-orange.svg)](https://swift.org)
[![Xcode](https://img.shields.io/badge/Xcode-16.0+-blue.svg)](https://developer.apple.com/xcode/)
[![License](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)

**GoDareDI** is a powerful, type-safe Dependency Injection framework for iOS and macOS applications built with Swift. It provides advanced features including circular dependency detection, performance analytics, scope management, and comprehensive debugging tools.

## 🚀 Features

- **Type-Safe Dependency Injection**: Full compile-time safety with Swift generics
- **Circular Dependency Detection**: Automatic detection and prevention of circular dependencies
- **Scope Management**: Support for singleton, transient, and custom scopes
- **Performance Analytics**: Built-in performance monitoring and optimization insights
- **Debug Visualizer**: Interactive dependency graph visualization
- **ABI Stability**: Binary compatibility across Swift versions
- **Objective-C Compatibility**: Full `@objc` support for mixed-language projects
- **Token-Based Licensing**: Secure license validation system

## 📦 Installation

### Swift Package Manager (Recommended)

Add GoDareDI to your project using Swift Package Manager:

1. In Xcode, go to **File** → **Add Package Dependencies**
2. Enter the repository URL: `https://github.com/MohamedAbdelHafezAbozaid/GoDare.DI.git`
3. Select **Add Package**

Or add it to your `Package.swift`:

```swift
dependencies: [
    .package(url: "https://github.com/MohamedAbdelHafezAbozaid/GoDare.DI.git", from: "1.0.0")
]
```

### Manual Installation

1. Download the `GoDareDIFramework.xcframework` from the [Releases](https://github.com/MohamedAbdelHafezAbozaid/GoDare.DI/releases) page
2. Drag the XCFramework into your Xcode project
3. Add it to your target's **Frameworks and Libraries**

## 🎯 Quick Start

### 1. Get Your License Token

First, you need to register and generate a license token:

1. **Register at [GoDare.app](https://godare.app)**
2. **Register your app** in your dashboard
3. **Generate a token** for your application
4. **Copy the 64-character hex token**

Then set your GoDareDI license token:

```swift
import GoDareDIFramework

// Set your license token (64-character hex string)
try GoDareDILicense.setToken("your-64-character-hex-token-here")
```

### 2. Initialize the Container

```swift
func initializeApp() async {
    do {
        print("🚀 Initializing GoDareDI...")
        
        // Set your GoDareDI token (REQUIRED)
        // Get your token from https://godare.app after registering your app
        let token = "your-64-character-hex-token-from-godare-app"
        try GoDareDILicense.setToken(token)
        
        // Initialize with secure token validation
        let container: AdvancedDIContainer
        
        do {
            container = try await GoDareDISecureInit.initialize()
            print("✅ GoDareDI initialized with token validation")
        } catch GoDareDILicenseError.invalidLicense {
            print("⚠️ Token validation failed, falling back to local initialization...")
            container = AdvancedDIContainerImpl()
            print("✅ GoDareDI initialized locally (fallback mode)")
        } catch {
            print("⚠️ Token validation error: \(error), falling back to local initialization...")
            container = AdvancedDIContainerImpl()
            print("✅ GoDareDI initialized locally (fallback mode)")
        }
        
        // Register your dependencies
        try await registerDependencies(container: container)
        
        // Set scope and preload
        await container.setCurrentScope("default")
        try await container.preloadAllGeneric()
        
        print("✅ Dependencies preloaded successfully")
        
    } catch {
        print("❌ Failed to initialize GoDareDI: \(error)")
    }
}
```

### 3. Register Dependencies

Create a module to organize your dependency registrations:

```swift
struct CoreRegistration: DIModule {
    func registerDependencies(container: AdvancedDIContainer) {
        // Register a singleton
        container.register(NetworkService.self, scope: .singleton) { _ in
            NetworkServiceImpl()
        }
        
        // Register a transient dependency
        container.register(UserService.self, scope: .transient) { container in
            let networkService = try container.resolveSync(NetworkService.self)
            return UserServiceImpl(networkService: networkService)
        }
        
        // Register with custom scope
        container.register(AnalyticsService.self, scope: .custom("analytics")) { _ in
            AnalyticsServiceImpl()
        }
    }
}
```

### 4. Resolve Dependencies

```swift
// Resolve synchronously
let userService = try container.resolveSync(UserService.self)

// Resolve asynchronously
let userService = try await container.resolve(UserService.self)

// Resolve with custom scope
let analyticsService = try await container.resolve(AnalyticsService.self, scope: "analytics")
```

## 📚 Advanced Usage

### Custom Scopes

```swift
// Create custom scopes
await container.createScope("userSession")
await container.createScope("feature")

// Set current scope
await container.setCurrentScope("userSession")

// Register with custom scope
container.register(UserSession.self, scope: .custom("userSession")) { _ in
    UserSessionImpl()
}
```

### Circular Dependency Detection

GoDareDI automatically detects circular dependencies:

```swift
// This will throw a CircularDependencyException
container.register(ServiceA.self) { container in
    let serviceB = try container.resolveSync(ServiceB.self)
    return ServiceAImpl(serviceB: serviceB)
}

container.register(ServiceB.self) { container in
    let serviceA = try container.resolveSync(ServiceA.self) // ❌ Circular dependency!
    return ServiceBImpl(serviceA: serviceA)
}
```

### Performance Analytics

Monitor dependency resolution performance:

```swift
// Enable performance tracking
let config = DIContainerConfig(
    enablePerformanceTracking: true,
    enableAnalytics: true
)

let container = AdvancedDIContainerImpl(config: config)

// Get performance metrics
let metrics = await container.getPerformanceMetrics()
print("Average resolution time: \(metrics.averageResolutionTime)ms")
```

### Debug Visualization

Use the built-in dependency graph visualizer:

```swift
import SwiftUI

struct ContentView: View {
    var body: some View {
        NavigationView {
            DependencyGraphView(container: container)
        }
    }
}
```

## 🔧 API Reference

### Core Types

- `AdvancedDIContainer`: Main dependency injection container protocol
- `AdvancedDIContainerImpl`: Default implementation of the container
- `DIModule`: Protocol for organizing dependency registrations
- `DependencyScope`: Enum defining dependency lifetimes

### Scopes

- `.singleton`: Single instance shared across the application
- `.transient`: New instance created for each resolution
- `.custom(String)`: Custom scope for specific use cases

### Error Types

- `DependencyResolutionError`: General resolution errors
- `CircularDependencyException`: Circular dependency detected
- `GoDareDILicenseError`: License validation errors

## 🛡️ Security & Licensing

GoDareDI uses a secure token-based licensing system:

- **Token Format**: 64-character hexadecimal string
- **Validation**: Server-side validation with local fallback
- **Security**: Tokens are validated against our secure API

### How to Get Your License Token

1. **Register at [GoDare.app](https://godare.app)**
   - Create your account
   - Verify your email address

2. **Register Your App**
   - Log into your dashboard
   - Click "Register New App"
   - Provide your app details (name, bundle ID, etc.)

3. **Generate Token**
   - Select your registered app
   - Click "Generate Token"
   - Copy the 64-character hex token

4. **Use in Your App**
   ```swift
   try GoDareDILicense.setToken("your-generated-token")
   ```

The token is used for secure license validation and enables all framework features.

## 📱 Requirements

- **iOS**: 18.0+
- **macOS**: 10.15+
- **Swift**: 6.0+
- **Xcode**: 16.0+

## 🤝 Contributing

We welcome contributions! Please see our [Contributing Guidelines](CONTRIBUTING.md) for details.

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 🆘 Support

- **Documentation**: [docs.godare.app](https://docs.godare.app)
- **Issues**: [GitHub Issues](https://github.com/MohamedAbdelHafezAbozaid/GoDare.DI/issues)
- **Email**: support@godare.app
- **Discord**: [GoDare Community](https://discord.gg/godare)

## 🙏 Acknowledgments

- Inspired by modern DI frameworks and Swift's type system
- Built with performance and developer experience in mind
- Special thanks to the Swift community for their feedback and contributions

---

**Made with ❤️ by the GoDare Team**

[Website](https://godare.app) • [Documentation](https://docs.godare.app) • [Support](mailto:support@godare.app)
