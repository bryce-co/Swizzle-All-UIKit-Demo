//
//  SwizzleMethod.c
//  SwizzleAllUIKit
//
//  Created by Bryce Pauken on 4/12/20.
//  Copyright © 2020 bryce.co. All rights reserved.
//

#include "SwizzleMethod.h"

#include <objc/runtime.h>
#include "MethodStorage.h"

int usedTrampolinesCount = 0;

void swizzle_method(Class class, Method method) {
    // Store information about the given method,
    // including its original implementation
    IMP originalImp = method_getImplementation(method);
    swizzledMethods[usedTrampolinesCount] = (SwizzledMethod){
        class,
        method,
        originalImp
    };

    // Get a reference to the next unused trampoline
    void *nextTrampoline = trampoline_start
        + (usedTrampolinesCount * trampolineSize);
    usedTrampolinesCount++;

    // Set the method's implementation
    // to that next trampoline
    long *imp = (void *)method + 0x10;
    *imp = (long)nextTrampoline;
}
