//
//  IAGcodeWriter.cpp
//
//  Copyright (c) 2013-2018 Matthias Melcher. All rights reserved.
//


#include "IAGcodeWriter.h"

#include "Iota.h"

#include <FL/gl.h>

#include <math.h>



IAGcodeWriter::IAGcodeWriter()
{
}


IAGcodeWriter::~IAGcodeWriter()
{
    if (pFile!=nullptr) close();
}


bool IAGcodeWriter::open(const char *filename)
{
    pFile = fopen(filename, "wb");
    if (!pFile) {
        // set error
        printf("Can't open file %s\n", filename);
        return false;
    }
    return true;
}


void IAGcodeWriter::sendNewLine(const char *comment)
{
    if (comment)
        fprintf(pFile, " ; %s", comment);
    fprintf(pFile, "\n");
}


void IAGcodeWriter::cmdHome()
{
    fprintf(pFile, "G28 ; home all axes\n");
    pPosition = { 0.0, 0.0, 0.0 };
}


void IAGcodeWriter::cmdSelectExtruder(int n)
{
    fprintf(pFile, "T%d ; select extruder\n", n);
}


void IAGcodeWriter::cmdExtrude(double distance, double feedrate)
{
    if (feedrate<0.0) feedrate = pPrintingF;
    // TODO: no need to send feedrate if it did not change
    // TODO: we need a different pE for each extruder
    fprintf(pFile, "G1 E%.4f F%.4f\n", pE+distance, feedrate);
    pE += distance;
    pF = feedrate;
}


void IAGcodeWriter::cmdRapidMove(double x, double y)
{
    IAVector3d p(x, y, pPosition.z());
    cmdRapidMove(p);
}


void IAGcodeWriter::cmdRapidMove(IAVector3d &v)
{
    sendRapidMoveTo(v);
    sendFeedrate(pRapidF);
    sendNewLine();
}


void IAGcodeWriter::cmdMove(double x, double y, double feedrate)
{
    IAVector3d p(x, y, pPosition.z());
    cmdMove(p, feedrate);
}


void IAGcodeWriter::cmdMove(IAVector3d &v, double feedrate)
{
    if (feedrate<0.0) feedrate = pF;
    double len = (v-pPosition).length();
    sendMoveTo(v);
    sendExtrusionAdd(len/pEFactor);
    sendFeedrate(feedrate);
    sendNewLine();
}


void IAGcodeWriter::macroInit()
{
    fprintf(pFile, "; generated by Iota Slicer\n");
    cmdComment("");
    cmdComment("==== Macro Init");
    fprintf(pFile, "G21 ; set units to millimeters\n");
    fprintf(pFile, "G90 ; use absolute coordinates\n");
    fprintf(pFile, "G28 ; home all axes\n");
    fprintf(pFile, "G1 Z5 F5000 ; lift nozzle\n");
    fprintf(pFile, "M140 S60 ; set bed temperature\n");
    fprintf(pFile, "T1\n");
    fprintf(pFile, "M82 ; use absolute distances for extrusion\n");
    fprintf(pFile, "M104 S230 ; set extruder temperature\n");
    fprintf(pFile, "T0\n");
    fprintf(pFile, "M82 ; use absolute distances for extrusion\n");
    fprintf(pFile, "M104 S230 ; set extruder temperature\n");
    fprintf(pFile, "M109 S230 ; set temperature and wait for it to be reached\n");
    fprintf(pFile, "M190 S60 ; wait for bed temperature\n");
    cmdResetExtruder();
    sendMoveTo(pPosition); sendExtrusionAdd(-1.0); sendFeedrate(1800.0); sendNewLine("retract extruder");
    fprintf(pFile, "M106 S255 P0 ; fan on\n");
    fprintf(pFile, "M106 S255 P1 ; fan on\n");
    fprintf(pFile, "M106 S255 P2 ; fan on\n");
    fprintf(pFile, "G4 S0.1 ; dwell\n");
    // C=523.251, D=587.330, E=659.255, F=698.456, G=783.991, A=880, B=987.767, C=1046.50
    fprintf(pFile, "M300 S523.251 P100 ; beep\n");
    fprintf(pFile, "M300 S587.330 P100 ; beep\n");
    fprintf(pFile, "M300 S659.255 P100 ; beep\n");
    fprintf(pFile, "M300 S698.456 P100 ; beep\n");
    fprintf(pFile, "M300 S783.991 P100 ; beep\n");
#if 0
    sendMoveTo(pPosition);
    sendExtrusionAdd(8);
    sendFeedrate(1800);
    sendNewLine("purge some filament");
#else
    macroPurgeExtruder(0);
    macroPurgeExtruder(1);
#endif
    IAVector3d v = { 0.0, 0.0, 0.2 };
    cmdRapidMove(v);
    cmdComment("");

/*
 ; generated by Slic3r 1.3.0-dev on 2018-08-21 at 17:52:14

 ; external perimeters extrusion width = 0.44mm (3.38mm^3/s)
 ; perimeters extrusion width = 0.48mm (7.54mm^3/s)
 ; infill extrusion width = 0.48mm (10.05mm^3/s)
 ; solid infill extrusion width = 0.48mm (2.51mm^3/s)
 ; top infill extrusion width = 0.48mm (1.88mm^3/s)

 M104 S200 ; set temperature
 G28 ; home all axes
 G1 Z5 F5000 ; lift nozzle

 ; Filament gcode

 M109 S200 ; set temperature and wait for it to be reached
 G21 ; set units to millimeters
 G90 ; use absolute coordinates
 M82 ; use absolute distances for extrusion
 G92 E0
 G1 E-1.00000 F1800.00000
 G92 E0
 G1 Z0.350 F7800.000
 G1 X59.286 Y76.833 F7800.000
 G1 E1.00000 F1800.00000
 G1 F1800
 G1 X61.438 Y76.040 E1.07096
 G1 X62.618 Y75.934 E1.10761
 G1 X137.387 Y75.934 E3.42107
 G1 X139.646 Y76.331 E3.49203
 G1 X141.634 Y77.474 E3.56299
 G1 X143.113 Y79.227 E3.63395
 G1 X143.906 Y81.379 E3.70492
 G1 X144.012 Y82.559 E3.74157
 G1 X144.012 Y112.443 E4.66623
 G1 X143.615 Y114.702 E4.73720
 G1 X142.471 Y116.690 E4.80816
 G1 X140.719 Y118.169 E4.87912
 G1 X138.209 Y119.017 E4.96110
 G1 X98.209 Y124.017 E6.20838
 G1 X97.387 Y124.068 E6.23385
 G1 X72.618 Y124.068 E7.00024
 G1 X69.655 Y123.369 E7.09443
 G1 X59.655 Y118.369 E7.44037
 G1 X57.812 Y117.004 E7.51133
 G1 X56.545 Y115.092 E7.58229
 G1 X55.993 Y112.443 E7.66600
 G1 X55.993 Y82.559 E8.59067
 G1 X56.390 Y80.300 E8.66163
 G1 X57.533 Y78.312 E8.73259
 G1 X59.240 Y76.871 E8.80170
 G1 E7.80170 F1800.00000
 G92 E0
 G1 X74.147 Y110.876 F7800.000
 G1 E1.00000 F1800.00000
 G1 F1800

 G1 X110.300 Y103.962 E12.89263
 G1 X109.705 Y103.964 E12.90324
 G1 X109.028 Y104.640 E12.92028
 G1 X109.028 Y104.054 E12.93073
 G1 X109.616 Y104.053 E12.94120
 G1 E11.94120 F1800.00000
 G92 E0
 G1 Z1.250 F7800.000
 G1 X91.424 Y93.567 F7800.000
 G1 E1.00000 F1800.00000
 G1 F3600
 G1 X96.351 Y93.590 E1.08758
 G1 X96.351 Y116.407 E1.49322
 G1 X73.644 Y116.407 E1.89689
 G1 X73.598 Y111.441 E1.98517
 G1 X63.657 Y111.410 E2.16190
 G1 X63.654 Y83.595 E2.65640
 G1 X91.356 Y83.595 E3.14888
 G1 X91.424 Y93.507 E3.32509
 G1 X91.838 Y93.150 F7800.000
 G1 F3600
 G1 X96.770 Y93.173 E3.41276
 G1 X96.770 Y116.826 E3.83326
 G1 X73.229 Y116.826 E4.25175

*/
}

void IAGcodeWriter::macroShutdown()
{
    cmdComment("");
    cmdComment("==== Macro Shutdown");
    cmdResetExtruder();
    fprintf(pFile, "T1 M104 S0 ; set extruder temperature\n");
    fprintf(pFile, "T0\n");
    fprintf(pFile, "M104 S0 ; set extruder temperature\n");
    fprintf(pFile, "M140 S0 ; set bed temperature\n");
    fprintf(pFile, "M106 S0 P0 ; fan off\n");
    fprintf(pFile, "M106 S0 P1 ; fan off\n");
    fprintf(pFile, "M106 S0 P2 ; fan off\n");
    fprintf(pFile, "G28 X0 Y0  ; home X and Y axis\n");
    fprintf(pFile, "M84 ; disable motors\n");

    fprintf(pFile, "G4 S0.1 ; dwell\n");
    fprintf(pFile, "M300 S783.991 P100 ; beep\n");
    fprintf(pFile, "M300 S698.456 P100 ; beep\n");
    fprintf(pFile, "M300 S659.255 P100 ; beep\n");
    fprintf(pFile, "M300 S587.330 P100 ; beep\n");
    fprintf(pFile, "M300 S523.251 P100 ; beep\n");
    cmdComment("");
}


void IAGcodeWriter::macroPurgeExtruder(int t)
{
    cmdComment("");
    cmdComment("==== Macro Purge Extruder %d", t);
    if (t==0) {
        // The tool 0 box is mounted in a very bad place and can just barely be reached.
        // We need to drive the head in a circle to actually wipe, and make a bee line
        // so that waste goes into the waste box. Phew. Also, when usug repetier FW, the
        // width needs to be corrected so that we reach the waste container at all.
        // Wipe tool 0
        // Box:     200, 0, 10
        // Wipe:    180, 0, 10
        cmdRapidMove(90,  0);
        cmdSelectExtruder(t);
        cmdResetExtruder();
        cmdRapidMove(180,  0);
        cmdRapidMove(180, 20);
        cmdRapidMove(199, 20);
        cmdRapidMove(199,  0);
        cmdRapidMove(180,  0);
        cmdRapidMove(180, 20);
        cmdRapidMove(199, 20);
        cmdRapidMove(199,  0);
        cmdExtrude(30);
        cmdRapidMove(180,  0);
        cmdRapidMove(180, 20);
        cmdRapidMove(199, 20);
        cmdRapidMove(199,  0);
        cmdRapidMove(180,  0);
        cmdRapidMove(180, 20);
        cmdRapidMove(199, 20);
        cmdRapidMove(199,  0);
        cmdRapidMove(180,  0);
        cmdRapidMove(180, 20);
        cmdResetExtruder();
    } else if (t==1) {
        // The tool 1 box is located a little bit better, but in order to reach it,
        // tool 0 must be active. I am not even sure if we can send a command to extrude
        // to head 1 without changing the position back onto the bed. In effect, we would
        // have change the minimum position for x to minus whatever the offest is between heads.
        // Maybe that's why in the original firmware, the *right* head is tool 0, and
        // the *left* head ist tool 1?
        // Wipe tool 1
        // Box:     T0! 0, 0, 10
        // Wipe:    T0! 0, 20, 10
        // but can we extrude T1 without changing the position? Maybe by using relative
        // positioning?
        cmdRapidMove(90,  0);
        cmdSelectExtruder(t);
        cmdResetExtruder();
        cmdRapidMove( 0,  0);
        cmdRapidMove( 0, 20);
        cmdRapidMove(20, 20);
        cmdRapidMove(20,  0);
        cmdRapidMove( 0,  0);
        cmdExtrude(30);
        cmdRapidMove( 0, 20);
        cmdRapidMove(20, 20);
        cmdRapidMove(20,  0);
        cmdRapidMove( 0,  0);
        cmdRapidMove( 0, 20);
        cmdRapidMove(20, 20);
        cmdRapidMove(20,  0);
        cmdRapidMove( 0,  0);
        cmdRapidMove( 0, 20);
        cmdRapidMove(20, 20);
        cmdRapidMove(20,  0);
        cmdResetExtruder();
    }
    cmdComment("");
}


void IAGcodeWriter::sendMoveTo(IAVector3d &v)
{
    fprintf(pFile, "G1 ");
    sendPosition(v);
}


void IAGcodeWriter::sendRapidMoveTo(IAVector3d &v)
{
    fprintf(pFile, "G0 ");
    sendPosition(v);
}


void IAGcodeWriter::sendPosition(IAVector3d &v)
{
    if (v.x()!=pPosition.x())
        fprintf(pFile, "X%.3f ", v.x());
    if (v.y()!=pPosition.y())
        fprintf(pFile, "Y%.3f ", v.y());
    if (v.z()!=pPosition.z())
        fprintf(pFile, "Z%.3f ", v.z());
    pPosition = v;
}


void IAGcodeWriter::sendFeedrate(double f)
{
    if (f!=pF) { fprintf(pFile, "F%.1f ", f); pF = f; }
}


void IAGcodeWriter::sendExtrusionAdd(double e)
{
    double newE = pE + e;
    if (newE!=pE) { fprintf(pFile, "E%.5f ", newE); pE = newE; }
}


void IAGcodeWriter::cmdResetExtruder()
{
    fprintf(pFile, "G92 E0 ; reset extruder\n");
    pE = 0.0;
}


void IAGcodeWriter::cmdComment(const char *format, ...)
{
    fprintf(pFile, "; ");
    va_list va;
    va_start(va, format);
    vfprintf(pFile, format, va);
    va_end(va);
    fprintf(pFile, "\n");
}


void IAGcodeWriter::close()
{
    if (pFile!=nullptr) {
        fclose(pFile);
        pFile = nullptr;
    }
}




