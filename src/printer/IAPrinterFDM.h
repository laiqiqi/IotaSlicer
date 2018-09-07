//
//  IAPrinterFDM.h
//
//  Copyright (c) 2013-2018 Matthias Melcher. All rights reserved.
//

#ifndef IA_PRINTER_FDM_H
#define IA_PRINTER_FDM_H


#include "printer/IAPrinter.h"

class Fl_Widget;
class Fl_Input_Choice;

/**
 * FDM, Fused Deposition Modeling, describes printers that extrude filament
 * to create 3D models.
 *
 * This printer driver writes GCode files.
 */
class IAPrinterFDM : public IAPrinter
{
    typedef IAPrinter super;
public:
    IAPrinterFDM(const char *name) : super(name) { }

    virtual void userSliceAs() override;
    virtual void sliceAndWrite(const char *filename=nullptr) override;

    virtual void buildSessionSettings() override;

    double layerHeight() { return pLayerHeight; }

protected:
    void userSetLayerHeight(Fl_Input_Choice *w);

private:
    static void userSetLayerHeightCB(Fl_Widget *w, void *d) {
        ((IAPrinterFDM*)d)->userSetLayerHeight((Fl_Input_Choice*)w); }

    double pLayerHeight = 0.2;
};


#endif /* IA_PRINTER_FDM_H */


