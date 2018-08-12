//
//  IAModelView.cpp
//
//  Copyright (c) 2013-2018 Matthias Melcher. All rights reserved.
//


#include "IAModelView.h"

#include "../main.h"
#include "../geometry/IAMesh.h"
#include "../geometry/IASlice.h"
#include "../printer/IAPrinter.h"

#include <math.h>

#include <FL/gl.h>
#include <FL/glu.h>
#include <FL/Fl_Slider.H>


IAModelView::IAModelView(int x, int y, int w, int h, const char *l)
: Fl_Gl_Window(x, y, w, h, l),
dx(0.0), dy(0.0)
{
}


int IAModelView::handle(int event) {
    // click to select
    // shift to drag
    // ctrl to rotate
    // scroll to dolly fraction of distance
    static int px = 0, py = 0;
    switch (event) {
        case FL_PUSH:
            px = Fl::event_x();
            py = Fl::event_y();
            return 1;
        case FL_DRAG:
        case FL_RELEASE:
            dx = dx + (px - Fl::event_x())*0.3;
            dy = dy + (py - Fl::event_y())*0.3;
            px = Fl::event_x();
            py = Fl::event_y();
            redraw();
            return 1;
    }
    return Fl_Gl_Window::handle(event);
}

void IAModelView::draw(IAMeshList *meshList, IASlice *meshSlice)
{
    double z1 = zSlider1->value();
    double z2 = zSlider2->value();
    //---- draw the model using the near and far plane for clipping
    if (meshList) {
        clipToSlice(z1, z2);
#if 0
        glDisable(GL_TEXTURE_2D);
        meshList->drawFlat(FL_RED);
        glDisable(GL_TEXTURE_2D);
#else
        glEnable(GL_TEXTURE_2D);
        meshList->drawFlat(FL_WHITE);
        glDisable(GL_TEXTURE_2D);
#endif
    }

    //---- draw the lid outline
    if (meshSlice) {
        dontClipToSlice();
#if 0
        glDisable(GL_TEXTURE_2D);
        glColor3ub(128, 255, 255);
        meshSlice->drawLidEdge();
        glDisable(GL_TEXTURE_2D);
#else
        glEnable(GL_TEXTURE_2D);
        glColor3ub(255, 255, 255);
        meshSlice->drawLidEdge();
        glDisable(GL_TEXTURE_2D);
#endif
    }

    dontClipToSlice();
}

void IAModelView::draw()
{
    static bool firstTime = true;
    if (firstTime) {
        firstTime = false;
        //      setShaders();
    }

    if (!valid()) {
        static GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
        static GLfloat mat_shininess[] = { 50.0 };
        //static GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
        static GLfloat light_position[] = { 1.0, -1.0, 1.0, 0.0 };
        static GLfloat light_ambient[] = { 0.3, 0.3, 0.3, 1.0};

        gl_font(FL_HELVETICA_BOLD, 16 );

        glClearColor (0.9, 0.9, 0.9, 0.0);
        glShadeModel (GL_SMOOTH);

        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
        glLightfv(GL_LIGHT0, GL_POSITION, light_position);
        glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);

        glEnable(GL_LIGHT0);
        glEnable(GL_NORMALIZE);

        glEnable(GL_BLEND);
        //      glBlendFunc(GL_ONE, GL_ZERO);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glViewport(0,0,pixel_w(),pixel_h());

        if (texture) {
            static GLuint tex = 0;
            glGenTextures(1, &tex);
            glBindTexture(GL_TEXTURE_2D, tex);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, texture->w(), texture->h(),
                         0, GL_RGB, GL_UNSIGNED_BYTE, *texture->data());
            glEnable(GL_TEXTURE_2D);
        }
    }

    double z1 = zSlider1->value();
    double z2 = zSlider2->value();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    if (gShowSlice) {
        glOrtho(-66.1,66.1,-66.1,66.1, -z1, -z1-z2); // mm
    } else {
        const double dist = 400.0;
        //            glOrtho(-66.1,66.1,-66.1,66.1,-66.1,66.1); // mm
        //            gluPerspective(40.0, (double(w()))/(double(h())), dist-gPrinter.pBuildVolumeRadius, dist+gPrinter.pBuildVolumeRadius);
        gluPerspective(50.0, (double(pixel_w()))/(double(pixel_h())), max(dist-gPrinter.pBuildVolumeRadius, 5.0), dist+gPrinter.pBuildVolumeRadius);
        // http://nehe.gamedev.net/article/replacement_for_gluperspective/21002/
        glTranslated(0.0, 0.0, -dist);
        glRotated(-90, 1.0, 0.0, 0.0);
    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();

    if (gShowSlice) {
        // show just the slice
        glDisable(GL_LIGHTING);
        glDisable(GL_DEPTH_TEST);

        //---- draw the untextured lid surface
        // change the z range to disable clipping
        dontClipToSlice();
#if 0
        gMeshSlice.drawFlat(FL_GREEN);
#else
        gMeshSlice.drawFlat(FL_DARK3);
#endif

        for (int n = 10; n>0; --n) {
            gMeshList.shrinkTo(0.2*n);
            IASlice meshSlice;
            meshSlice.generateFrom(gMeshList, zSlider1->value());
            draw(&gMeshList, &meshSlice);
        }
        gMeshList.shrinkTo(0.0);

        draw(&gMeshList, &gMeshSlice);

#if 0
        // set the z range again to enable drawing the shell
        glMatrixMode (GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-66.1,66.1,-66.1,66.1, -z1, -z1-z2); // mm
        glMatrixMode(GL_MODELVIEW);
        // the following code guarantees a hull of at least 1mm width
        //      double sd;
        //      glHint(GL_POLYGON_SMOOTH_HINT, );
        //      glDisable (GL_POLYGON_SMOOTH);
        //      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        //      for (sd = 0.2; sd<gMinimumShell; sd+=0.2) {
        //        drawModelShrunk(Fl_WHITE, sd);
        //      }
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
#endif
    } else {
        // show the 3d model
        gPrinter.draw();
        glRotated(-dy, 1.0, 0.0, 0.0);
        glRotated(-dx, 0.0, 1.0, 0.0);
        glEnable(GL_LIGHTING);
        glEnable(GL_DEPTH_TEST);
//        gMeshList.drawGouraud();
//        glEnable(GL_TEXTURE_2D);
        gMeshList.drawFlat(0x00cccccc);
    }
    glPopMatrix();

    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, pixel_w(), 0, pixel_h(), -10, 10); // mm
    glMatrixMode(GL_MODELVIEW);
    gl_color(FL_WHITE);
    char buf[1024];
    sprintf(buf, "Slice at %.4gmm", z1); gl_draw(buf, 10, 40);
    sprintf(buf, "%.4gmm thick", z2); gl_draw(buf, 10, 20);
}


void IAModelView::clipToSlice(double z1, double z2)
{
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-66.1,66.1,-66.1,66.1, -z1, -z1-z2); // mm
    glMatrixMode(GL_MODELVIEW);
}

void IAModelView::dontClipToSlice()
{
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-66.1,66.1,-66.1,66.1,-66.1,66.1); // mm
    glMatrixMode(GL_MODELVIEW);
}

