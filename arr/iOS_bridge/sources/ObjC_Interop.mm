//
//  ObjC_Interop.m
//  invaders
//
//  Created by Phil Ahrenkiel on 9/24/22.
//  Copyright © 2022 Phil Ahrenkiel. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "ObjC_Interop.h"
#include <iostream>

std::string defaultFontName("Georgia");
float defaultFontSize(14.0);

@implementation ObjC_Interop
//using namespace std;

//
-(void)drawString:(CFStringRef)s point:(CGPoint)P
{
	NSString *ns=(NSString *)CFBridgingRelease(s);
	NSString *nsFont=[[NSString alloc] initWithUTF8String:defaultFontName.c_str()];

	[ns drawAtPoint:P withAttributes:@{NSFontAttributeName:[PlatformFont fontWithName:nsFont size:defaultFontSize]}];
}

//
-(void)drawString:(CFStringRef)s rect:(CGRect)R
{
	NSString *ns=(NSString *)CFBridgingRelease(s);
	NSString *nsFont=[[NSString alloc] initWithUTF8String:defaultFontName.c_str()];

	[ns drawInRect:R withAttributes:@{NSFontAttributeName:[PlatformFont fontWithName:nsFont size:defaultFontSize]}];

}

@end

//Provide access from C++
void drawString(CFStringRef s,CGPoint P)
{
	ObjC_Interop *objC=[ObjC_Interop alloc];
	[objC drawString:s point:P];
}
void drawString(CFStringRef s,CGRect R)
{
	ObjC_Interop *objC=[ObjC_Interop alloc];
	[objC drawString:s rect:R];
}
