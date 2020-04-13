//
//  MethodStorage.h
//  SwizzleAllUIKit
//
//  Created by Bryce Pauken on 4/12/20.
//  Copyright © 2020 bryce.co. All rights reserved.
//

#ifndef MethodStorage_h
#define MethodStorage_h

#include <objc/runtime.h>

/**
 Stores information about a given method
 */
typedef struct SwizzledMethod {
    Class class;
    Method method;
    IMP originalImplementation;
} SwizzledMethod;

/**
 Storage for our swizzled methods
 */
extern SwizzledMethod swizzledMethods[75000];

#endif /* MethodStorage_h */
