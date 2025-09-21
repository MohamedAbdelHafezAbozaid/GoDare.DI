//
//  GoDareDI.h
//  GoDareDIFramework
//
//  Created by mohamed ahmed on 21/09/2025.
//

#import <Foundation/Foundation.h>

//! Project version number for GoDareDI.
FOUNDATION_EXPORT double GoDareDIVersionNumber;

//! Project version string for GoDareDI.
FOUNDATION_EXPORT const unsigned char GoDareDIVersionString[];

// In this header, you should import all the public headers of your framework using statements like #import <GoDareDIFramework/PublicHeader.h>

// License and Security - Objective-C Compatible (NSObject-based classes)
#import <GoDareDIFramework/GoDareDILicense-Swift.h>
#import <GoDareDIFramework/GoDareDISecureInit-Swift.h>
#import <GoDareDIFramework/GoDareDILicenseError-Swift.h>

// Analytics - Objective-C Compatible (NSObject-based classes)
#import <GoDareDIFramework/DefaultDIAnalyticsProvider-Swift.h>
#import <GoDareDIFramework/ConsoleDIAnalyticsProvider-Swift.h>

// Crashlytics - Objective-C Compatible (NSObject-based classes)
#import <GoDareDIFramework/DefaultDICrashlyticsProvider-Swift.h>
#import <GoDareDIFramework/DICrashlyticsConfig-Swift.h>
#import <GoDareDIFramework/CrashlyticsLogLevel-Swift.h>
#import <GoDareDIFramework/DICrashlyticsManager-Swift.h>

// Token Validation - Objective-C Compatible (NSObject-based classes)
#import <GoDareDIFramework/DefaultDITokenValidationProvider-Swift.h>
#import <GoDareDIFramework/TokenValidationResult-Swift.h>
#import <GoDareDIFramework/DITokenValidationError-Swift.h>

// Note: The following APIs are Swift-only and not Objective-C compatible:
// - AdvancedDIContainer (uses generics and async/await)
// - AdvancedDIContainerImpl (uses generics and async/await)
// - DIModule (uses generics)
// - DependencyScope, DependencyLifetime, etc. (Swift enums)
// - DependencyGraph, GraphAnalysis, etc. (complex Swift structs)
// - PerformanceMetrics, PerformanceTrend (Swift structs/enums)
// - ContainerBuilder (actor-based, Swift-only)
// - DependencyGraphView (SwiftUI, Swift-only)

// Note: SwiftUI components like DependencyGraphView are not Objective-C compatible
// and will be available only in Swift code
