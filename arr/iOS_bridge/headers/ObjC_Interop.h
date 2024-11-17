//
//  ObjC_Interop.h
//  invaders
//
//  Created by Phil Ahrenkiel on 9/24/22.
//  Copyright © 2022 Phil Ahrenkiel. All rights reserved.
//

//#ifndef _OBJC_INTEROP_
//#define _OBJC_INTEROP_

//#import <CoreData/CoreData.h>
#import "CoreGraphics/CoreGraphics.h"

//#ifndef TARGET_IOS
//#define TARGET_IOS
//#endif

#if defined(TARGET_IOS) || defined(TARGET_TVOS)
#import <UIKit/UIKit.h>
#define PlatformFont UIFont
#else
//#import <AppKit/AppKit.h>
#define PlatformFont NSFont
#endif

#include <iostream>

//class bridgeClass;

@interface ObjC_Interop:NSObject
{
@public

	//long pointerToBridge;

};

//-(void)drawString:(CFStringRef)s;
-(void)drawString:(CFStringRef)s point:(CGPoint)P;
-(void)drawString:(CFStringRef)s rect:(CGRect)R;

//-(void)storeBridgePointer:(long)ptr;

@end

//#endif //_OBJC_INTEROP_
