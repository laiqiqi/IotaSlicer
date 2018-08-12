//
//  main.h
//
//  Copyright (c) 2013-2018 Matthias Melcher. All rights reserved.
//

#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include "IAMesh.h"
#include "IASlice.h"
#include "printer/IAPrinter.h"

extern class Fl_Window *gMainWindow;
extern class Fl_Slider *zSlider1, *zSlider2;
extern class Fl_RGB_Image *texture;
extern IAMeshList gMeshList;
extern IASlice gMeshSlice;
extern IAPrinter gPrinter;
extern bool gShowSlice;
extern FILE *gOutFile;
extern double minX, maxX, minY, maxY, minZ, maxZ;

extern double min(double a, double b);
extern double max(double a, double b);
extern float min(float a, float b);
extern float max(float a, float b);

extern void sliceAll();
extern void menuQuit();

#endif /* MAIN_H */
