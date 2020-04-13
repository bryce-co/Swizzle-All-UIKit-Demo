//
//  SwizzleMethod.h
//  SwizzleAllUIKit
//
//  Created by Bryce Pauken on 4/12/20.
//  Copyright © 2020 bryce.co. All rights reserved.
//

#ifndef SwizzleMethod_h
#define SwizzleMethod_h

#include <objc/runtime.h>

/**
 Reference to the first trampoline
 */
extern void trampoline_start(void);

/**
 Size of any given trampoline
 */
static int trampolineSize = 5;

/**
 Swizzles a class and adds its original
 information to the shared method storage
 */
void swizzle_method(Class class, Method method);

#endif /* SwizzleMethod_h */
