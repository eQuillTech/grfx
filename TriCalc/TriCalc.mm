//
//  TriCalc
//
//  Created by Phil Ahrenkiel on 4/26/23.
//
#import <AppKit/AppKit.h>
#import <fstream>
#import <iomanip>
#include <CoreGraphics/CoreGraphics.h>
#import "TopoMesh.hpp"
#import "TriCalc.h"


@implementation TriCalc

+(TopoTri*)makeTri:(NSString*)imagePath
{
	NSImage *nsimage = [[NSImage alloc] initWithContentsOfFile:imagePath];
	CGImageRef image = [nsimage CGImageForProposedRect:nil context:nil hints:nil];
	
	CGSize imageSize;
	imageSize.width=CGImageGetWidth(image);
	imageSize.height=CGImageGetHeight(image);
	size_t imageBytesPerRow=CGImageGetBytesPerRow(image);
	size_t imageByteCount=(imageBytesPerRow*imageSize.height);
	
	CGColorSpaceRef imageColorSpaceRef=CGImageGetColorSpace(image);
	CGBitmapInfo imageBitmapInfo=CGImageGetBitmapInfo(image);
	size_t imageBitsPerPixel=CGImageGetBitsPerPixel(image);
	
 	//Create the context
 	void *imageBitmapData=calloc(imageByteCount,sizeof(uint8_t));
  if(imageBitmapData==NULL)
	{
		return nullptr;
	}

	//CGColorSpaceRef imageColorSpace=CGColorSpaceCreateWithName(imageColorSpaceName);
	CGContextRef imageContext=CGBitmapContextCreate
	(	imageBitmapData,
		imageSize.width,
		imageSize.height,
		imageBitsPerPixel, // bits per component
		imageBytesPerRow,
		imageColorSpaceRef,
		imageBitmapInfo
	);

	CGRect Rdest= CGRectMake(0,0,imageSize.width,imageSize.height);
	CGContextDrawImage(imageContext,Rdest,image);
	
	auto fimg=static_cast<float*>(imageBitmapData);
	std::size_t n=imageSize.width*imageSize.height;
	std::vector<float> data_img(fimg,fimg+n);
	auto topoTri = new TopoTri(  data_img,  // array of image data
		 imageSize.width, imageSize.height,  // Image dimensions
		 true,
		 -1,
		 0.001, // Resolution factor (0 - 1) for triangulation
		 true // Specifies whether to eliminate border apices
	);
	
	//double zMin,zMax;
	//getRange(data_img,imageSize.width,imageSize.height,zMin,zMax);

	MeshRange range=topoTri->_range;
	atr3 T(trf3::To,-range.min(2)*vtr3::Z);
	arr::dbl2 D=arr::dbl2::ident(3,3);
	D(0,0)=2./range.extent(0);D(1,1)=2./range.extent(1);D(2,2)=1./range.extent(2);
	T*=atr3(D,-vtr3(1.,1.,0.));
	//D(0,0)=1.;D(1,1)=1.;D(2,2)=1.;
	//T*=atr3(D,vtr3::zero);
	*topoTri*=T;
	
	std::cout<<"vertices: "<<topoTri->_vertex.size()<<"\n";
	std::size_t i=0;
	for(auto& pair:topoTri->_submesh)
	{
		auto submesh=pair.second;
		std::cout<<"submesh "<<i<<", triangles: "<<submesh->_tris.size()<<"\n";
		++i;
	}

	CGImageRelease(image);
  CGContextRelease(imageContext);
	free(imageBitmapData);
	NSLog(@"created mesh");
	return topoTri;
}

+(void)writeDat:(TopoTri*)topoTri file:(NSString*)filePath
{
	// topo data
	NSFileManager *filemgr = [NSFileManager defaultManager];
	
	if ([filemgr fileExistsAtPath:filePath] == YES)
  	NSLog(@"File exists");
	else
  	NSLog(@"File not found");

	size_t nVertices=topoTri->_vertex.size();
	NSMutableData *data=[NSMutableData dataWithBytes: &nVertices length: sizeof(size_t)];
	for(auto &vertex:topoTri->_vertex)
	{
		pnt3 &P=std::get<0>(vertex);
		[data appendData: [NSMutableData dataWithBytes: &P(0) length: sizeof(double)]];
		[data appendData: [NSMutableData dataWithBytes: &P(1) length: sizeof(double)]];
		[data appendData: [NSMutableData dataWithBytes: &P(2) length: sizeof(double)]];

		vtr3 &nV=std::get<1>(vertex);
		[data appendData: [NSMutableData dataWithBytes: &nV(0) length: sizeof(double)]];
		[data appendData: [NSMutableData dataWithBytes: &nV(1) length: sizeof(double)]];
		[data appendData: [NSMutableData dataWithBytes: &nV(2) length: sizeof(double)]];
	
		pnt2 &Ptex=std::get<2>(vertex);
		[data appendData: [NSMutableData dataWithBytes: &Ptex(0) length: sizeof(double)]];
		[data appendData: [NSMutableData dataWithBytes: &Ptex(1) length: sizeof(double)]];
	}
	for(auto &[key,submesh]:topoTri->_submesh)
	{
		size_t nKeyLength=key.length()+1;
		[data appendData: [NSMutableData dataWithBytes: &nKeyLength length: sizeof(size_t)]];

		[data appendData: [NSMutableData dataWithBytes: &key length: nKeyLength]];

		size_t nTriangs=submesh->numTriang();
		[data appendData: [NSMutableData dataWithBytes: &nTriangs length: sizeof(size_t)]];
		std::cout<<"submesh: "<<key<<", triangles: "<<nTriangs<<"\n";
		
		for(auto &index:submesh->_tris)
		{
			[data appendData: [NSMutableData dataWithBytes: &index._p[0] length: sizeof(long)]];
			[data appendData: [NSMutableData dataWithBytes: &index._p[1] length: sizeof(long)]];
			[data appendData: [NSMutableData dataWithBytes: &index._p[2] length: sizeof(long)]];
		}
	}
	[filemgr createFileAtPath:filePath contents: data attributes: nil];
	
	// now read back
	if([filemgr fileExistsAtPath:filePath])
	{
		NSLog(@"found file");
	}

	NSFileHandle *file = [NSFileHandle fileHandleForReadingAtPath: filePath];
	if (file == nil) {NSLog(@"Failed to open file"); return;}
	NSLog(@"created binary file");
}

+(void)writeObj:(TopoTri*)topoTri file:(NSString*)filePath
{
	// topo data
	NSFileManager *filemgr = [NSFileManager defaultManager];
	
	if ([filemgr fileExistsAtPath:filePath] == YES)
        NSLog (@"File exists");
	else
        NSLog (@"File not found");

	size_t nVertices=topoTri->_vertex.size();
	NSMutableData *data=[NSMutableData dataWithBytes: &nVertices length: sizeof(size_t)];
	std::ofstream oss([filePath UTF8String]);
	if(oss.is_open())
	{
		oss<< std::fixed << std::setprecision(4);
		for(auto &vertex:topoTri->_vertex)
		{
			pnt3 &P=std::get<0>(vertex);
			oss<< "v "<<P(0)<<" "<<P(1)<<" "<<P(2)<<"\n";
		}
		for(auto &vertex:topoTri->_vertex)
		{
			vtr3 &nV=std::get<1>(vertex);
			oss<< "vn "<<nV(0)<<" "<<nV(1)<<" "<<nV(2)<<"\n";
		}
		for(auto &vertex:topoTri->_vertex)
		{
			pnt2 &Ptex=std::get<2>(vertex);
			oss<< "vt "<<Ptex(0)<<" "<<Ptex(1)<<"\n";
		}
		for(auto &[key,submesh]:topoTri->_submesh)
		{
			size_t nKeyLength=key.length()+1;
			[data appendData: [NSMutableData dataWithBytes: &nKeyLength length: sizeof(size_t)]];

			[data appendData: [NSMutableData dataWithBytes: &key length: nKeyLength]];

			size_t nTriangs=submesh->numTriang();
			[data appendData: [NSMutableData dataWithBytes: &nTriangs length: sizeof(size_t)]];
				
			for(auto &index:submesh->_tris)
			{
				auto p0=index._p[0]+1;
				oss<< "f "<<p0<<"/"<<p0<<"/"<<p0;
				
				auto p1=index._p[1]+1;
				oss<< " "<<p1<<"/"<<p1<<"/"<<p1;
		
				auto p2=index._p[2]+1;
				oss<< " "<<p2<<"/"<<p2<<"/"<<p2<<"\n";
			}
		}
		oss.close();
	}
	
	// now read back
	if([filemgr fileExistsAtPath:filePath])
	{
		NSLog(@"found file");
	}

	NSFileHandle *file = [NSFileHandle fileHandleForReadingAtPath: filePath];
	if (file == nil) {NSLog(@"Failed to open file"); return;}
	NSLog(@"created obj file");
}

@end
