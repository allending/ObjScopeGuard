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
    char *buffer = (char *)malloc(sizeof(int) * 1000);
    CFMutableAttributedStringRef attrString = CFAttributedStringCreateMutable(kCFAllocatorDefault, 0);
    
    MAKE_GUARD(^{
        NSLog(@"SCOPE_GUARD: This should show up after -application:didFinishLaunchingWithOptions:");
        

        NSLog(@"SCOPE_GUARD: Freeing memory allocated in -application:didFinishLaunchingWithOptions:");
        free(buffer);

        NSLog(@"SCOPE_GUARD: Releasing CFMutableAttributedStringRef created in -application:didFinishLaunchingWithOptions:");
        CFRelease(attrString);
        
        dispatch_async(dispatch_get_main_queue(), ^{
            NSLog(@"SCOPE_GUARD: Block dispatched to the main queue after -application:didFinishLaunchingWithOptions: reached");
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
