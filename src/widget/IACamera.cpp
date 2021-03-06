//
//  IACamera.cpp
//
//  Copyright (c) 2013-2018 Matthias Melcher. All rights reserved.
//


#include "IACamera.h"

#include "Iota.h"
#include "widget/IASceneView.h"
#include "geometry/IAMath.h"
#include "printer/IAPrinter.h"

#include <FL/gl.h>
#include <FL/glu.h>

#include <math.h>


/**
 * Create a camera superclass.
 *
 * \param view Attach to this view. Should not be null.
 */
IACamera::IACamera(IASceneView *view)
:   pView( view )
{
}


/**
 * Set the point that we are looking at.
 *
 * \param v point in global space, copied.
 */
void IACamera::setInterest(IAVector3d &v)
{
    pInterest = v;
}



/**
 * Create a simple perspective camera.
 *
 * \param view Attach to this view. Should not be null.
 */
IAPerspectiveCamera::IAPerspectiveCamera(IASceneView *view)
:   super( view )
{
}


/**
 * User wants to rotate the camera.
 *
 * \param dx, dy rotate by these deltas
 */
void IAPerspectiveCamera::rotate(double dx, double dy)
{
    pZRotation += dx/100.0;
    pXRotation += dy/100.0;

    while (pZRotation>=M_PI*2.0) pZRotation -= M_PI*2.0;
    while (pZRotation<0.0) pZRotation += M_PI*2.0;

    if (pXRotation>M_PI*0.48) pXRotation = M_PI*0.48;
    if (pXRotation<-M_PI*0.48) pXRotation = -M_PI*0.48;
}


/**
 * User wants to drag the camera around.
 *
 * \param dx, dy drag by these deltas
 */
void IAPerspectiveCamera::drag(double dx, double dy)
{
    IAVector3d position = IAVector3d(0.0, -pDistance, 0.0);
    position.xRotate(pXRotation);
    position.zRotate(pZRotation);
    position += pInterest;

    IAVector3d printer = Iota.pCurrentPrinter->pPrintVolume;
    printer *= 0.5;
    printer -= position;
    double dist = printer.length();

    IAVector3d offset(dx, 0, -dy);
    // using pDistance works as well, but is not as nice
    offset *= 1.8*dist/(pView->w()+pView->h());
    offset.xRotate(pXRotation);
    offset.zRotate(pZRotation);
    pInterest += offset;
}


/**
 * User wants to get closer to the point of interest.
 *
 * \param dx, dy dolly or zoom by these deltas
 */
void IAPerspectiveCamera::dolly(double dx, double dy)
{
    pDistance = pDistance * (1.0+0.01*dy);
    if (pDistance<5.0) pDistance = 5.0;
}


/**
 * Replacement for the now deprecated gluLookAt function. Does the exact
 * same thing.
 *
 * \param eyeX, eyeY, eyeZ, lookAtX, lookAtY, lookAtZ, upX, upY, upZ see gluLookAt
 */
void iaGluLookAt(GLfloat eyeX, GLfloat eyeY, GLfloat eyeZ, GLfloat lookAtX, GLfloat lookAtY, GLfloat lookAtZ, GLfloat upX, GLfloat upY, GLfloat upZ) {
    IAVector3d fwd, side, up;
    fwd = IAVector3d(lookAtX-eyeX, lookAtY-eyeY, lookAtZ-eyeZ).normalized();
    up = IAVector3d(upX, upY, upZ);
    side = (fwd ^ up).normalized();
    up = side ^ fwd;
    GLdouble mat[16] = {
        side.x(), up.x(), -fwd.x(), 0,
        side.y(), up.y(), -fwd.y(), 0,
        side.z(), up.z(), -fwd.z(), 0,
        0, 0, 0, 1 };
    glMultMatrixd(mat);
    glTranslated(-eyeX, -eyeY, -eyeZ);
}


/**
 * Emit OpenGL commands to load the viewing and model matrices.
 */
void IAPerspectiveCamera::draw()
{
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    IAVector3d position = IAVector3d(0.0, -pDistance, 0.0);
    position.xRotate(pXRotation);
    position.zRotate(pZRotation);
    position += pInterest;

    IAVector3d printer = Iota.pCurrentPrinter->pPrintVolume;
    printer *= 0.5;
    printer -= position;
    double dist = printer.length();
    double aspect = (double(pView->pixel_w()))/(double(pView->pixel_h()));
    double nearPlane = ia_max(dist-2.0*Iota.pCurrentPrinter->pPrintVolumeRadius, 1.0);
    double farPlane = dist+2.0*Iota.pCurrentPrinter->pPrintVolumeRadius;

    //gluPerspective(50.0, aspect, nearPlane, farPlane);
    GLfloat fieldOfView = 50.0;
    GLfloat fH = tanf( float(fieldOfView / 360.0f * 3.14159f) ) * nearPlane;
    GLfloat fW = (GLfloat)(fH * aspect);
    glFrustum( -fW, fW, -fH, fH, nearPlane, farPlane );

    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity();
    iaGluLookAt((GLfloat)position.x(), (GLfloat)position.z(), -(GLfloat)position.y(),
		(GLfloat)pInterest.x(), (GLfloat)pInterest.z(), -(GLfloat)pInterest.y(),
              0.0f, 1.0f, 0.0f);
    glRotated(-90, 1.0, 0.0, 0.0);
}




/**
 * Create a simple orthographic camera.
 *
 * This camera is currently fixed to top view.
 *
 * \param view Attach to this view. Should not be null.
 * \param direction not used yet
 */
IAOrthoCamera::IAOrthoCamera(IASceneView *view, int direction)
:   super( view )
{
}


/**
 * User wants to rotate the camera.
 *
 * \param dx, dy rotate by these deltas
 */
void IAOrthoCamera::rotate(double dx, double dy)
{
    // Do we want to allow rotation?
}


/**
 * User wants to drag the camera around.
 *
 * \param dx, dy drag by these deltas
 */
void IAOrthoCamera::drag(double dx, double dy)
{
    IAVector3d offset(dx, -dy, 0);
    offset *= 4.0*pZoom/(pView->w()+pView->h());
    pInterest += offset;
}


/**
 * User wants to get closer to the point of interest.
 *
 * \param dx, dy dolly by these deltas
 */
void IAOrthoCamera::dolly(double dx, double dy)
{
    pZoom = pZoom * (1.0+0.01*dy);
    if (pZoom<1.0) pZoom = 1.0;
    if (pZoom>4.0*Iota.pCurrentPrinter->pPrintVolumeRadius) pZoom = 4.0*Iota.pCurrentPrinter->pPrintVolumeRadius;
}


/**
 * Emit OpenGL commands to load the viewing and model matrices.
 */
void IAOrthoCamera::draw()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    double aspect = (double(pView->pixel_w()))/(double(pView->pixel_h()));
    glOrtho(-pZoom*aspect, pZoom*aspect, -pZoom, pZoom, -Iota.pCurrentPrinter->pPrintVolumeRadius, Iota.pCurrentPrinter->pPrintVolumeRadius);
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity();
    glTranslated(-pInterest.x(), -pInterest.y(), -pInterest.z());
}



