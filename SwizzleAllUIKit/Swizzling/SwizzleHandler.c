//
//  SwizzleHandler.c
//  SwizzleAllUIKit
//
//  Created by Bryce Pauken on 4/12/20.
//  Copyright © 2020 bryce.co. All rights reserved.
//

#include <stdio.h>
#import "MethodStorage.h"
#import "SwizzleMethod.h"

// MARK: - Common Swizzle Handler

void *common_swizzle_handler(long trampolineAddress) {
    // Find trampoline's address relative
    // to the first trampoline
    long offsetInTrampolines = trampolineAddress
        - (long)trampoline_start;

    // Divide by trampoline size to get
    // the index of our trampoline
    long trampolineIndex =  (offsetInTrampolines / trampolineSize) - 1;

    // Look up original method info
    SwizzledMethod sm = swizzledMethods[trampolineIndex];

    // Log the method name
    printf("-[%s %s]\n",
        class_getName(sm.class),
        sel_getName(method_getName(sm.method)));

    // Return the address of the original implementation
    return sm.originalImplementation;
}
