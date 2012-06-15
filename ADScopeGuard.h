//
// ADScopeGuard.h
// ObjScopeGuard
//
// Copyright (c) 2012, Allen Ding
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 
// 1. Redistributions of source code must retain the above copyright notice, this
// list of conditions and the following disclaimer.
// 
// 2. Redistributions in binary form must reproduce the above copyright notice,
// this list of conditions and the following disclaimer in the documentation
// and/or other materials provided with the distribution.
// 
// 3.  Neither the name of Allen Ding nor the names of any contributors may be
// used to endorse or promote products derived from this software without specific
// prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//

#import <Foundation/Foundation.h>

// Purpose:
// Tiny library intended for adding scope guard support to Objective-C projects.
// A scope guard is a block of code that is run when the guard goes out of scope.
// 
// This functionality is useful for cleanly specifying resource cleanup, code
// that needs to be executed, logging, etc. in a more declarative manner.
// 
// Requirements:
// - Xcode 4.3+
// - Clang compiler
// - Automatic Reference Counting (ARC) enabled
// 
// Example:
//
// - (void)doComplicatedStuffWithCoreData {
//     [self.managedObjectContent lock];
//
//      ON_SCOPE_EXIT(^{
//          // Unlock the context no matter how we return from method
//          [self.managedObjectContext unlock];
//      });
//
//      // do complicated stuff with many return points
// }
// 
// Usage:
// - You need ADScopeGuard.h and ADScopeGuard.m present in your project, either as source
// or as some form of library.
// - MAKE_GUARD(void_block) and ON_SCOPE_EXIT(void_block) are used to create scope guards.
// The void_block parameter is well ... a void block.
//
// Notes:
// - If Objective-C++ is being used, use Boost ScopeExit or something else instead.
//

// Simple macros for generating unique variable name
#define AD_SCOPE_GUARD_CONCAT(x, y) x##y 
#define AD_SCOPE_GUARD_CONCAT_EXPANDING_ARGS(x, y) AD_SCOPE_GUARD_CONCAT(x, y)
#define AD_SCOPE_GUARD_UNIQUE_VAR_NAME AD_SCOPE_GUARD_CONCAT_EXPANDING_ARGS(ADScopeGuardReserved_scopeGuard, __COUNTER__)

// The actual macros you should use.
#define MAKE_GUARD(void_block) __strong ADScopeGuard *AD_SCOPE_GUARD_UNIQUE_VAR_NAME __attribute__((objc_precise_lifetime, unused)) = [[ADScopeGuard alloc] initWithBlock:void_block];
#define ON_SCOPE_EXIT(void_block) MAKE_GUARD(void_block)

// The ADScopeGuard class is pretty simple.
// It takes a block that is executed when the object is dealloced.
// You should not actually create instances of this class directly. Use the macros above.
//
@interface ADScopeGuard : NSObject

- (id)initWithBlock:(void (^)(void))block;

@end
