//
//  FindMethods.c
//  SwizzleAllUIKit
//
//  Created by Bryce Pauken on 4/12/20.
//  Copyright © 2020 bryce.co. All rights reserved.
//

#include "FindMethods.h"

#import <objc/runtime.h>
#include <dlfcn.h>
#include <stdlib.h>
#include "SwizzleMethod.h"

/*
 Returns the base address of the framework/image
 associated with the given class.

 This is just the same starting address you might see
 in the Binary Images section of a crash report,
 or in the `image list` output of `lldb`.
 */
void *framework_address_for_class(Class class) {
    struct dl_info info;
    dladdr(class, &info);
    return info.dli_fbase;
}

// Swizzles all methods on a given class
void swizzle_class(Class class) {
    // For every method...
    unsigned int methodCount = 0;
    Method *methods = class_copyMethodList(class, &methodCount);
    for (int i=0; i<methodCount; i++) {
        // Call our previously-defined
        // `swizzle_method` function
        Method method = methods[i];
        swizzle_method(class, method);
    }

    free(methods);
}

void swizzle_uikit_classes() {
    // Get UIKit[Core]'s base address for comparison
    Class uiViewClass = objc_lookUpClass("UIView");

    void *uikitBaseAddress = framework_address_for_class(uiViewClass);

    // For every class...
    unsigned int classCount = 0;
    Class *classes = objc_copyClassList(&classCount);
    for (int i=0; i<classCount; i++) {
        Class class = classes[i];

        // Check if it's in the same image as UIView...
        void *classAddress = framework_address_for_class(class);
        if (classAddress != uikitBaseAddress) {
            continue;
        }

        Class superclass = class;
        BOOL isUIView = false;
        while ((superclass = class_getSuperclass(superclass))) {
            if (superclass == uiViewClass) {
                isUIView = true;
            }
        }

        if (!isUIView) {
            continue;
        }

        // And swizzle all its methods if so
        swizzle_class(class);
    }

    free(classes);
}
