//
//  UIView+SwizzleAllUIKit.m
//  SwizzleAllUIKit
//
//  Created by Bryce Pauken on 4/12/20.
//  Copyright © 2020 bryce.co. All rights reserved.
//

@import ObjectiveC;
@import UIKit;

#import "FindMethods.h"

@implementation UIView (BeginSwizzle)

+ (void)load {
    swizzle_uikit_classes();
}

@end
