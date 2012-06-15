# ObjScopeGuard #

Purpose:
- Tiny library intended for adding scope guard support to Objective-C projects.
A scope guard is a block of code that is run when the guard goes out of scope.
- This functionality is useful for cleanly specifying resource cleanup, logic 
that must always be applied before returning, logging, etc. in a more declarative manner.

Requirements:
- Xcode 4.3+
- Clang compiler
- Automatic Reference Counting (ARC) enabled

Example:

```
- (void)doComplicatedStuffWithCoreData {
    [self.managedObjectContent lock];
     ON_SCOPE_EXIT(^{
         // Unlock the context no matter how we return from method
         [self.managedObjectContext unlock];
     });
     // do complicated stuff with many return points
}
```

Usage:
- You need `ADScopeGuard.h` and `ADScopeGuard.m` present in your project, either as source
or as some form of library.
- `MAKE_GUARD(void_block)` and `ON_SCOPE_EXIT(void_block)` are used to create scope guards.
The void_block parameter is well ... a void block.

Notes:
- If Objective-C++ is being used, use Boost ScopeExit or something else instead.

Feedback:
- Allen Ding (@alding)
