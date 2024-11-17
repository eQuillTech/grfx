//
//  test_c.h
//  Swift_C_test
//
//  Created by Phil Ahrenkiel on 6/16/19.
//  Copyright © 2019 Phil Ahrenkiel. All rights reserved.
//


#ifndef CPP_BRIDGE
#define CPP_BRIDGE

//#import <CoreData/CoreData.h>
#import "CoreGraphics/CoreGraphics.h"
//#import <UIKit/UIKit.h>
#include <iostream>
#include <stdio.h>


void drawString(CFStringRef s,CGPoint P);
void drawString(CFStringRef s,CGRect R);

/*
//
typedef struct tlbxBridge bridge;

#ifdef TLBX_BRIDGE
extern "C"
{
#endif

	bridge *create_tlbxBridge();
	void release_tlbxBridge(bridge *c);
	
	void tlbxMethod(bridge *c,double x);
	
#ifdef TLBX_BRIDGE
}
#endif
*/
#endif
