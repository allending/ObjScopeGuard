//
//  ADAppDelegate.m
//  ObjScopeGuard
//
//  Created by Allen Ding on 6/15/12.
//

#import "ADAppDelegate.h"
#import "ADScopeGuard.h"

@implementation ADAppDelegate

@synthesize window = _window;

- (void)testNestedScopeGuard {
    ON_SCOPE_EXIT(^{
        NSLog(@"This should show up after -testNestedScopeGuard");
    });
    
    NSLog(@"end of -testNestedScopeGuard");
}

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    MAKE_GUARD(^{
        NSLog(@"This should show up after -application:didFinishLaunchingWithOptions:");
        
        dispatch_async(dispatch_get_main_queue(), ^{
            NSLog(@"Block dispatched to the main queue after -application:didFinishLaunchingWithOptions: reached");
        });
    });

    self.window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
    self.window.rootViewController = [[UIViewController alloc] init];
    [self.window makeKeyAndVisible];

    // Test nesting of scope guards
    [self testNestedScopeGuard];
    
    NSLog(@"end of -application:didFinishLaunchingWithOptions:");
    return YES;
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
    NSLog(@"end of -applicationDidBecomeActive:");
}

@end
