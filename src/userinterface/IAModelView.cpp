//
//  IAModelView.cpp
//
//  Copyright (c) 2013-2018 Matthias Melcher. All rights reserved.
//


#include "IAModelView.h"

#include "../Iota.h"
#include "IACamera.h"
#include "../geometry/IAMesh.h"
#include "../geometry/IASlice.h"
#include "../printer/IAPrinter.h"
#include "../userinterface/IAGUIMain.h"

#include <math.h>

#include <FL/gl.h>
#include <FL/glu.h>
#include <FL/Fl_Slider.H>


/**
 * Create a new OpenGL scene view.
 *
 * When constructed, the widget will connect itself with the current Fl_Group
 * in FLTK.
 */
IAModelView::IAModelView(int x, int y, int w, int h, const char *l)
:   Fl_Gl_Window(x, y, w, h, l),
    pPerspectiveCamera( new IAPerspectiveCamera(this) ),
    pTopCamera( new IAOrthoCamera(this, 0) ),
    pCurrentCamera( pPerspectiveCamera )
{
}


/**
 * Release all allocated resources.
 */
IAModelView::~IAModelView()
{
    delete pCurrentCamera;
}


/**
 * Handle all events that FLTK sends here.
 *
 * \todo FIXME: Handle all mouse input for manipulating the scene or the camera.
 * \todo Handle drag'n'drop events to add new models or textures.
 * \todo Handle copy and paste events.
 * \todo Handle context menus.
 */
int IAModelView::handle(int event)
{
    if (Fl_Window::handle(event))
        return 1;

    // click to select
    // shift to drag
    // ctrl to rotate
    // scroll to dolly fraction of distance
    static int px = 0, py = 0;
    double dx, dy;
    switch (event) {
        case FL_MOUSEWHEEL:
            pCurrentCamera->dolly(Fl::event_dx()*1.5, Fl::event_dy()*1.5);
            redraw();
            return 1;
        case FL_PUSH:
            px = Fl::event_x();
            py = Fl::event_y();
            return 1;
        case FL_DRAG:
        case FL_RELEASE:
            dx = px - Fl::event_x();
            dy = py - Fl::event_y();
            px = Fl::event_x();
            py = Fl::event_y();
            if ( (Fl::event_state()&(FL_SHIFT|FL_CTRL|FL_ALT|FL_META)) == FL_SHIFT) {
                pCurrentCamera->rotate(dx, dy);
            } else if ( (Fl::event_state()&(FL_SHIFT|FL_CTRL|FL_ALT|FL_META)) == FL_CTRL) {
                pCurrentCamera->drag(dx, dy);
            } else if ( (Fl::event_state()&(FL_SHIFT|FL_CTRL|FL_ALT|FL_META)) == (FL_CTRL|FL_SHIFT)) {
                pCurrentCamera->dolly(dx, dy);
            }
            redraw();
            return 1;
        case FL_DND_ENTER: return 1;
        case FL_DND_DRAG: return 1;
        case FL_DND_RELEASE: return 1;
        case FL_PASTE:
            Iota.loadAnyFileList(Fl::event_text());
            break;
    }
    return Fl_Gl_Window::handle(event);
}


/**
 * Update the preview slice if the Z slice leve changed and it needs to be rendered.
 * \todo This should be a function of IASlice.
 */
void IAModelView::updateSlice()
{
    // genrate a lid if we need one
    // TODO: refactor into slice class
    if (Iota.gShowSlice && Iota.gMeshSlice.pCurrentZ!=zSlider1->value()) {
        Iota.gMeshSlice.generateLidFrom(*Iota.gMeshList, zSlider1->value());
    }
}


/**
 * Initialize all shaders that we might want to use.
 */
void IAModelView::initializeShaders()
{
    if (!pShadersValid) {
//      setShaders();
        pShadersValid = true;
    }
}


/**
 * Initialize all standard OpenGL settings of the current view.
 */
void IAModelView::initializeView()
{
    if (!valid()) {
        gl_font(FL_HELVETICA, 16 );
        static GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
        static GLfloat mat_shininess[] = { 50.0 };
        static GLfloat light_position[] = { 1.0, -1.0, 1.0, 0.0 };
        static GLfloat light_ambient[] = { 0.3, 0.3, 0.3, 1.0};

        glClearColor (0.9, 0.9, 0.9, 0.0);
        glShadeModel (GL_SMOOTH);

        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
        glLightfv(GL_LIGHT0, GL_POSITION, light_position);
        glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);

        glEnable(GL_LIGHT0);
        glEnable(GL_NORMALIZE);

        glEnable(GL_BLEND);
        // glBlendFunc(GL_ONE, GL_ZERO);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glViewport(0,0,pixel_w(),pixel_h());

        if (!pShadersValid) initializeShaders();

        valid(1);
    }
}


/**
 * Initialize and activate textures for rendering.
 * \todo must move into a texture class
 */
void IAModelView::beginTextures()
{
    static Fl_RGB_Image *lTexture = nullptr;
    static GLuint tex = 0;
    if (lTexture != Iota.texture) {
        glGenTextures(1, &tex);
        glBindTexture(GL_TEXTURE_2D, tex);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, Iota.texture->w(), Iota.texture->h(),
                     0, GL_RGB, GL_UNSIGNED_BYTE, *Iota.texture->data());
        glEnable(GL_TEXTURE_2D);
        lTexture = Iota.texture;
    }
    if (Iota.texture) {
        glBindTexture(GL_TEXTURE_2D, tex);
    } else {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}


/**
 * Start drawing models.
 */
void IAModelView::beginModels()
{
    // initialize model drawing
    glPushMatrix();
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_DEPTH_TEST);
}


/**
 * End drawing models.
 */
void IAModelView::endModels()
{
    glPopMatrix();
}




/**
 * Draw the entire scene.
 */
void IAModelView::draw()
{
    if (!valid()) initializeView();

    // initialize the frame buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    updateSlice();
    beginTextures();

    pCurrentCamera->draw();
    Iota.gPrinter.draw();

    beginModels();
    if (Iota.gMeshList) {
        if (Iota.gShowSlice) {
            Iota.gMeshList->drawSliced(zSlider1->value());
        } else {
            Iota.gMeshList->drawFlat(Iota.gShowTexture);
        }
    }
    endModels();
    
    draw_children(); // draw FLTK user interface
}


/**
 * Draw FLTK child widgets
 */
void IAModelView::draw_children()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-0.5, w()-0.5, h()-0.5, -0.5, 1.0, -1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);

    Fl_Widget*const* a = array();
    for (int i=children(); i--;) {
        Fl_Widget& o = **a++;
        draw_child(o);
        draw_outside_label(o);
    }
}


void IAModelView::setTopView()
{
    pCurrentCamera = pTopCamera;
    redraw();
}


void IAModelView::setPerspectiveView()
{
    pCurrentCamera = pPerspectiveCamera;
    redraw();
}


