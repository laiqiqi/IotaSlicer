//
//  IAToolpath.cpp
//
//  Copyright (c) 2013-2018 Matthias Melcher. All rights reserved.
//


#define RENDER_HEX_TOOLPATH


#include "IAToolpath.h"

#include "Iota.h"
#include "opengl/IAFramebuffer.h"
#include "printer/IAFDMPrinter.h"

#include <FL/gl.h>

#include <math.h>
#include <algorithm>


bool isBlack(uint8_t *rgb, IAVector3d v)
{
    IAVector3d s = v * (kFramebufferSize / 214.0);
    int xo = (int)s.x(), yo = (int)s.y();
    uint8_t *c = rgb + (xo+kFramebufferSize*yo)*3;
    if (c[0]<128 && c[1]<128 && c[2]<128) {
        return true;
    } else {
        return false;
    }
}

#if 0
/**
 * This hack slices long Toolpath Motions into smaller pieces if the color
 * of the object changes during that motion.
 */
void IAToolpath::colorize(uint8_t *rgb, IAToolpath *black, IAToolpath *white)
{
    for (auto &e: pList) {
        IAToolpathMotion *m = dynamic_cast<IAToolpathMotion*>(e);
        if (m) {
            if (!m->pIsRapid) {
#if 0 // simple way to find color by looking at the start point
                if (isBlack(rgb, m->pStart)) {
                    black->pList.push_back(m->clone());
                } else {
                    white->pList.push_back(m->clone());
                }
#else // look at the vector and check the point color at every milimeter, splicing motion if needed
                IAVector3d startVec = m->pStart;
                IAVector3d currStartVec = startVec;
                IAVector3d currVec = startVec;
                IAVector3d endVec = m->pEnd;
                IAVector3d deltaVec = endVec - startVec;
                double len = (endVec-startVec).length();
                double incr = 0.1;
                bool color = isBlack(rgb, startVec);
                for (double i=incr; i<len; i+=incr) {
                    currVec = startVec + (deltaVec*(i/len));
                    bool colorNow = isBlack(rgb, currVec);
                    if (colorNow!=color) {
                        IAToolpathMotion *mtn = new IAToolpathMotion(currStartVec, currVec);
                        if (color) { mtn->pColor = 0x444444; black->pList.push_back(mtn); }
                        else { mtn->pColor = 0xFFFFFF; white->pList.push_back(mtn); }
                        currStartVec = currVec;
                        color = colorNow;
                    }
                }
                if (currStartVec!=endVec) {
                    IAToolpathMotion *mtn = new IAToolpathMotion(currStartVec, endVec);
                    if (color) { mtn->pColor = 0x444444; black->pList.push_back(mtn); }
                    else { mtn->pColor = 0xFFFFFF; white->pList.push_back(mtn); }
                }
#endif
            } else {

            }
        }
    }
}
#endif


uint32_t getRGB(uint8_t *rgb, IAVector3d v)
{
    IAVector3d s = v * (kFramebufferSize / 214.0);
    int xo = (int)s.x(), yo = (int)s.y();
    uint8_t *c = rgb + (xo+kFramebufferSize*yo)*3;
    return ((c[0]<<16)|(c[1]<<8)|(c[2]));
}

bool differ(uint32_t c1, uint32_t c2)
{
    if (c1==c2) return false;
    int r1 = (c1>>16)&255, r2 = (c2>>16)&255, rd = r1-r2;
    if (rd>10 || rd<-10) return true;
    int g1 = (c1>>8)&255, g2 = (c2>>8)&255, gd = g1-g2;
    if (gd>10 || gd<-10) return true;
    int b1 = (c1>>0)&255, b2 = (c2>>0)&255, bd = b1-b2;
    if (bd>10 || bd<-10) return true;
    return false;
}


#if 0
void IAToolpath::colorizeSoft(uint8_t *rgb, IAToolpath *dst)
{
    for (auto &e: pList) {
        IAToolpathMotion *m = dynamic_cast<IAToolpathMotion*>(e);
        if (m) {
            if (!m->pIsRapid) {
                IAVector3d startVec = m->pStart;
                IAVector3d currStartVec = startVec;
                IAVector3d currVec = startVec;
                IAVector3d endVec = m->pEnd;
                IAVector3d deltaVec = endVec - startVec;
                double len = (endVec-startVec).length();
                double incr = 0.1;
                uint32_t color = getRGB(rgb, startVec);
                for (double i=incr; i<len; i+=incr) {
                    currVec = startVec + (deltaVec*(i/len));
                    uint32_t colorNow = getRGB(rgb, currVec);
                    if (differ(colorNow, color)) {
                        IAToolpathMotion *mtn = new IAToolpathMotion(currStartVec, currVec);
                        mtn->setColor(color);
                        dst->pList.push_back(mtn);
                        currStartVec = currVec;
                        color = colorNow;
                    }
                }
                if (currStartVec!=endVec) {
                    IAToolpathMotion *mtn = new IAToolpathMotion(currStartVec, endVec);
                    mtn->setColor(color);
                    dst->pList.push_back(mtn);
                }
            } else {

            }
        }
    }
}
#endif



#ifdef __APPLE__
#pragma mark -
#endif
// =============================================================================



/**
 * Create a list of toolpaths for the entire printout.
 */
IAMachineToolpath::IAMachineToolpath(IAFDMPrinter *printer)
:   pPrinter( printer )
{
}


/**
 * Free all allocations.
 */
IAMachineToolpath::~IAMachineToolpath()
{
    purge();
}


/**
 * Free all allocations.
 */
void IAMachineToolpath::purge()
{
    for (auto &p: pToolpathListMap) {
        delete p.second;
    }
    pToolpathListMap.clear();
}


/**
 * Draw the toolpath into the scene at world coordinates.
 */
void IAMachineToolpath::draw(double lo, double hi)
{
    int i = 0;
    for (auto &p: pToolpathListMap) {
        if (i>=lo && i<=hi)
            p.second->draw();
        i++;
    }
}


/**
 * DRaw the toolpath of only one layer.
 */
void IAMachineToolpath::drawLayer(double z)
{
    auto p = findLayer(z);
    if (p)
        p->draw();
}


void IAMachineToolpath::optimize()
{
    for (auto &p: pToolpathListMap) {
        p.second->optimize();
    }
}


/**
 * Return a layer at the give z height, or nullptr if none found.
 */
IAToolpathList *IAMachineToolpath::findLayer(double z)
{
    int layer = roundLayerNumber(z);
    auto p = pToolpathListMap.find(layer);
    if (p==pToolpathListMap.end())
        return nullptr;
    else
        return p->second;
}


/**
 * Create a new toolpath for a layer at the give z height.
 */
IAToolpathList *IAMachineToolpath::createLayer(double z)
{
    int layer = roundLayerNumber(z);
    auto p = pToolpathListMap.find(layer);
    if (p==pToolpathListMap.end()) {
        IAToolpathList *tp = new IAToolpathList(z);
        pToolpathListMap.insert(std::make_pair(layer, tp));
        return tp;
    } else {
        return p->second;
    }
}


/**
 * Delete a toolpath at the give heigt.
 */
void IAMachineToolpath::deleteLayer(double z)
{
    int layer = roundLayerNumber(z);
    pToolpathListMap.erase(layer);
}


/**
 * Round the z height into a layer number to avoid imprecissions of floating
 * point math.
 */
int IAMachineToolpath::roundLayerNumber(double z)
{
    return (int)lround(z*1000.0);
}


/**
 * Create a bitmap of all tools/extruders used in this toolpath.
 */
unsigned int IAMachineToolpath::createToolmap()
{
    unsigned int toolmap = 0;
    for (auto &p: pToolpathListMap)
        toolmap |= p.second->createToolmap();
    return toolmap;
}


/**
 * Save the toolpath as a GCode file.
 */
bool IAMachineToolpath::saveGCode(const char *filename /*, printer */)
{
    double minLayerTime = pPrinter->minimumLayerTime();

    bool ret = false;
    IAGcodeWriter w(pPrinter);
    if (w.open(filename)) {
        w.resetTotalTime();
        unsigned int toolmap = createToolmap();
        w.sendInitSequence(toolmap);
        for (auto &p: pToolpathListMap) {
            w.cmdComment("");
            w.cmdComment("==== layer at z=%.2f", p.first / 1000.0);
            w.cmdComment("");
            w.cmdResetExtruder();
            w.resetLayerTime();
            // send all motion commands
            p.second->saveGCode(w);
            double layerTime = w.getLayerTime();
            printf("Layer at %.2f will print in %.2f seconds\n", p.first / 1000.0, layerTime);
            /** \todo tune this parameter */
            if (layerTime>0.0 && layerTime<minLayerTime) {
                IAVector3d prev = w.position();
                IAVector3d pause = Iota.pMesh->pMin
                                 - IAVector3d(10.0, 10.0, 0.0)
                                 + Iota.pMesh->position(); /** \bug in world coordinates */
                pause.setMax(IAVector3d(0.0, 0.0, 0.0));
                pause.z( prev.z() );
                w.cmdRetract();
                w.cmdRapidMove(pause);
                w.cmdDwell(minLayerTime-layerTime);
                w.cmdRapidMove(prev);
                w.cmdUnretract();
            }
        }
        w.sendShutdownSequence();
        printf("Total print time is %.2f minutes\n", w.getTotalTime()/60.0);
        w.close();
        ret = true;
    }
    return ret;
}


#ifdef __APPLE__
#pragma mark -
#endif
// =============================================================================


/**
 * Manage a list of toolpath types.
 */
IAToolpathList::IAToolpathList(double z)
{
}


/**
 * Delete a toolpath.
 */
IAToolpathList::~IAToolpathList()
{
    purge();
}


/**
 * Delete all resources.
 */
void IAToolpathList::purge()
{
    for (auto &tt: pToolpathList)
        delete tt;
    pToolpathList.clear();
}


/**
 * Check if this toolpath list is empty.
 *
 * \return true if the list is empty or all paths in the list are empty.
 */
bool IAToolpathList::isEmpty()
{
    if (pToolpathList.size()==0)
        return true;
    for (auto &tt: pToolpathList)
        if (!tt->isEmpty())
            return false;
    return true;
}


/**
 * Add another toolpath type to the list.
 */
void IAToolpathList::add(IAToolpath *tt, int tool, int group, int priority)
{
    tt->pTool = tool;
    tt->pGroup = group;
    tt->pPriority = priority;
    pToolpathList.push_back(tt);
}


/**
 * Move toolpaths from another list to this list.
 */
void IAToolpathList::move(IAToolpathList *tl)
{
    for (auto &tt: tl->pToolpathList) {
        pToolpathList.push_back(tt);
    }
    tl->pToolpathList.clear();
}


/**
 * Add another toolpath list to the list.
 */
void IAToolpathList::add(IAToolpathList *tl, int tool, int group, int priority)
{
    for (auto &tt: tl->pToolpathList) {
        add(tt->clone(), tool, group, priority);
    }
}


void IAToolpathList::add(IAToolpathList *tl)
{
    for (auto &tt: tl->pToolpathList) {
        add(tt->clone(), tt->pTool, tt->pGroup, tt->pPriority);
    }
}


/**
 * Draw the current toolpath into the scene viewer at world coordinates.
 */
void IAToolpathList::draw()
{
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    glColor3f(0, 1, 0);
    for (auto &tt: pToolpathList) {
        tt->draw();
    }
}


void IAToolpathList::drawFlat(double w)
{
    /**
     \todo draw connection between lines.
     */
    for (auto &tt: pToolpathList) {
        tt->drawFlat(w);
    }
}


void IAToolpathList::drawFlatToBitmap(IAFramebuffer *fb, double w, int color)
{
    /**
     \todo draw connection between lines.
     */
    for (auto &tt: pToolpathList) {
        tt->drawFlatToBitmap(fb, w, color);
    }
}


/**
 * Create a bitmap of all tools/extruders used in this toolpath.
 */
unsigned int IAToolpathList::createToolmap()
{
    unsigned int toolmap = 0;
    for (auto &p: pToolpathList)
        toolmap |= p->createToolmap();
    return toolmap;
}


/**
 * Save the toolpath as a GCode file.
 */
void IAToolpathList::saveGCode(IAGcodeWriter &w)
{
    w.cmdComment("Send generated toolpath...");
    for (auto &tt: pToolpathList) {
        tt->saveGCode(w);
    }
}


/**
 * Save the toolpath as a DXF file.
 */
void IAToolpathList::saveDXF(const char *filename)
{
    IADxfWriter w;
    if (w.open(filename)) {
        for (auto &tt: pToolpathList) {
            tt->saveDXF(w);
        }
        w.close();
    }
}


void IAToolpathList::optimize()
{
    std::sort(pToolpathList.begin(), pToolpathList.end(), IAToolpath::comparePriorityAscending);
    // -- optimize my travel distance: if Toolpaths are in the same group,
    // with the same priority, and the same tool, sort them so that traveling
    // between toolpaths is short
    size_t i, j, n = pToolpathList.size();
    if (n) for (i=0; i<n-1; i++) {
        IAToolpath *ta = pToolpathList[i];
        IAToolpath *tx = pToolpathList[i+1];
        size_t x = i+1;
        if (   ta->pGroup==tx->pGroup
            && ta->pPriority==tx->pPriority
            && ta->pTool==tx->pTool)
        {
            double dist = (ta->tFirst-tx->tFirst).length();
            for (j=i+2; j<n; j++) {
                IAToolpath *tb = pToolpathList[j];
                if (   ta->pGroup==tb->pGroup
                    && ta->pPriority==tb->pPriority
                    && ta->pTool==tx->pTool )
                {
                    double dist2 = (ta->tFirst-tb->tFirst).length();
                    if (dist2<dist) {
                        dist = dist2;
                        tx = tb;
                        x = j;
                    }
                } else {
                    break;
                }
            }
            if (x!=i+1) {
                IAToolpath *tmp = pToolpathList[x];
                pToolpathList[x] = pToolpathList[i+1];
                pToolpathList[i+1] = tmp;
            }
        }
    }
}



#ifdef __APPLE__
#pragma mark -
#endif
// =============================================================================


/**
 * Manage a single toolpath.
 */
IAToolpath::IAToolpath(double z)
:   tFirst( 0.0, 0.0, z ),
    tPrev( 0.0, 0.0, z ),
    pZ( z )
{
}


/**
 * Delete a toolpath.
 */
IAToolpath::~IAToolpath()
{
    purge();
}


/**
 * Create a duplicate of this Toolpath.
 *
 * \param[in] t is set if the object was already created by a derived class.
 * \return a copy of this toolpath, caller must \em delete
 */
IAToolpath *IAToolpath::clone(IAToolpath *t)
{
    if (!t)
        t = new IAToolpath(pZ);
    t->tFirst = tFirst;
    t->tPrev = tPrev;
    t->pZ = pZ;
    t->pTool = pTool;
    t->pGroup = pGroup;
    t->pPriority = pPriority;
    for (auto &e: pElementList)
        t->pElementList.push_back(e->clone());
    return t;
}


/**
 * Clear a toolpath for its next use.
 */
void IAToolpath::purge()
{
    for (auto &el: pElementList)
        delete el;
    pElementList.clear();
    tFirst = { 0.0, 0.0, pZ };
    tPrev = { 0.0, 0.0, pZ };
}


bool IAToolpath::comparePriorityAscending(const IAToolpath *a, const IAToolpath *b)
{
    // first, sort by the extruder index
    if ( a->pTool < b->pTool )
        return true;
    if ( a->pTool > b->pTool )
        return false;

    // next, sort by the group number
    if ( a->pGroup < b->pGroup )
        return true;
    if ( a->pGroup > b->pGroup )
        return false;

    // finally, sort by the priority within the group
    if ( a->pPriority < b->pPriority )
        return true;
    
    return false;
}



/**
 * Draw the current toolpath into the scene viewer at world coordinates.
 */
void IAToolpath::draw()
{
    switch (pTool) {
        case -1: glColor3f(1.0, 0.0, 0.0); break;
        case  0: glColor3f(1.0, 1.0, 1.0); break;
        case  1: glColor3f(0.3, 0.3, 0.3); break;
    }
    for (auto &e: pElementList) {
        e->draw();
    }
}


void IAToolpath::drawFlat(double w)
{
    /**
     \todo draw connection between lines.
     */
    for (auto &e: pElementList) {
        e->drawFlat(w);
    }
}


void IAToolpath::drawFlatToBitmap(IAFramebuffer *fb, double w, int color)
{
    /**
     \todo draw connection between lines.
     */
    for (auto &e: pElementList) {
        e->drawFlatToBitmap(fb, w, color);
    }
}


/**
 * Start a new path.
 */
void IAToolpath::startPath(double x, double y)
{
    IAVector3d next(x, y, pZ);
    tFirst = next;
    pElementList.push_back(new IAToolpathMotion(tPrev, next, true));
    tPrev = next;
}


/**
 * Add a motion segment to the path.
 */
void IAToolpath::continuePath(double x, double y)
{
    IAVector3d next(x, y, pZ);
    if (!(tPrev==next))
        pElementList.push_back(new IAToolpathMotion(tPrev, next));
    tPrev = next;
}


/**
 * Create a loop by moving back to the very first vector.
 */
void IAToolpath::closePath()
{
    if (!(tPrev==tFirst))
        pElementList.push_back(new IAToolpathMotion(tPrev, tFirst));
}


/**
 * Create a bitmap of all tools/extruders used in this toolpath.
 */
unsigned int IAToolpath::createToolmap()
{
    if (pTool==-1) return 1;
    return 1<<pTool;
}


/**
 * Save the toolpath as a GCode file.
 */
void IAToolpath::saveGCode(IAGcodeWriter &w)
{
    w.requestTool(pTool);
    for (auto &e: pElementList) {
        e->saveGCode(w);
    }
}


/**
 * Save the toolpath as a DXF file.
 */
void IAToolpath::saveDXF(IADxfWriter &w)
{
    for (auto &e: pElementList) {
        e->saveDXF(w);
    }
}


#ifdef __APPLE__
#pragma mark -
#endif
// =============================================================================


IAToolpathLoop::IAToolpathLoop(double z)
:   IAToolpath( z )
{
}


IAToolpathLoop::~IAToolpathLoop()
{
}


IAToolpath *IAToolpathLoop::clone(IAToolpath *t)
{
    if (!t)
        t = new IAToolpathLoop(pZ);
    return super::clone(t);
}


#ifdef __APPLE__
#pragma mark -
#endif
// =============================================================================


/**
 * Create any sort of toolpath element.
 */
IAToolpathElement::IAToolpathElement()
{
}


/**
 * Destroy an element.
 */
IAToolpathElement::~IAToolpathElement()
{
}


IAToolpathElement *IAToolpathElement::clone()
{
    return new IAToolpathElement();
}


/**
 * Draw any element.
 */
void IAToolpathElement::draw()
{
    // nothing to here
}


//#ifdef __APPLE__
//#pragma mark -
//#endif
//// =============================================================================
//
//
//
///**
// * Create any sort of toolpath element.
// */
//IAToolpathExtruder::IAToolpathExtruder(int tool)
//:   pTool( tool )
//{
//}
//
//
///**
// * Destroy an element.
// */
//IAToolpathExtruder::~IAToolpathExtruder()
//{
//}
//
//
//IAToolpathElement *IAToolpathExtruder::clone()
//{
//    IAToolpathExtruder *tpe = new IAToolpathExtruder(pTool);
//    return tpe;
//}
//
//
///**
// * Save the toolpath element as a GCode file.
// */
//void IAToolpathExtruder::saveGCode(IAGcodeWriter &w)
//{
//    assert(0); // this must be implemented again
//#if 0
//    w.cmdComment("");
//    w.cmdComment("---- Change to extruder %d", pTool);
//    // deactivate the other extruder
//    int otherTool = 1-pTool;
//    w.cmdSelectExtruder(otherTool);
//    w.cmdResetExtruder();
//    w.cmdExtrude(-4.0);
//
//    // activate the new extruder
//    w.cmdSelectExtruder(pTool);
//    w.cmdResetExtruder();
//    w.cmdExtrude(4.0);
//    int x = pTool ? 100 : 48;
//    int pw = 20;
//    w.cmdRapidMove(x, 10.0);
//    int i;
//    for (i=0; i<4; i++) {
//        w.cmdPrintMove(x+pw, 10.0+i);
//        w.cmdPrintMove(x+pw, 10.0+i+0.5);
//        w.cmdMove(x, 10.0+i+0.5);
//        w.cmdMove(x, 10.0+i+1.0);
//    }
//    w.cmdSelectExtruder(pTool); // redundant
//    w.cmdResetExtruder();
//    w.cmdComment("Extruder %d ready", pTool);
//    w.cmdComment("");
//#endif
//}


#ifdef __APPLE__
#pragma mark -
#endif
// =============================================================================


/**
 * Create a toolpath for a head motion to a new position.
 */
IAToolpathMotion::IAToolpathMotion(IAVector3d &a, IAVector3d &b, bool rapid)
:   IAToolpathElement(),
    pStart( a ),
    pEnd( b ),
    pIsRapid( rapid )
{
}


IAToolpathElement *IAToolpathMotion::clone()
{
    IAToolpathMotion *mtn = new IAToolpathMotion(pStart, pEnd, pIsRapid);
    mtn->pColor = pColor;
    return mtn;
}


/**
 * Draw the toolpath motion into the scene viewer.
 *
 * \todo make the extrusion hexagonal so we can represent the squashing
 *       by the layer height. Also, use the current E factor to calculate the
 *       expected width of the extrusion and draw that.
 * \todo add lids or connecotrs to the next extrusion.
 * \todo this should be cached
 */
void IAToolpathMotion::draw()
{
#ifdef RENDER_HEX_TOOLPATH
    if (pIsRapid) {
//        glDisable(GL_LIGHTING);
//        glColor3f(1.0, 1.0, 0.0);
//        glEnable(GL_LIGHTING);
    } else {
        double r=0.2;
        IAVector3d d = (pEnd - pStart).normalized();
        IAVector3d n0 = { d.y(), -d.x(), 0.0 };
        IAVector3d n1 = { 0.0, 0.0, 1.0 };
        IAVector3d n2 = { -d.y(), d.x(), 0.0 };
        IAVector3d n3 = { 0.0, 0.0, -1.0 };
        IAVector3d p0, p1, p2, p3;

        if (pColor!=0xFFFFFFFF)
            glColor3ub(pColor>>16, pColor>>8, pColor);

        glBegin(GL_QUADS);
        glNormal3dv(n0.dataPointer());
        p0 = pStart + n0*r; glVertex3dv(p0.dataPointer());
        glNormal3dv(n0.dataPointer());
        p1 = pEnd + n0*r; glVertex3dv(p1.dataPointer());
        glNormal3dv(n1.dataPointer());
        p2 = pEnd + n1*r; glVertex3dv(p2.dataPointer());
        glNormal3dv(n1.dataPointer());
        p3 = pStart + n1*r; glVertex3dv(p3.dataPointer());
        glEnd();

        glBegin(GL_QUADS);
        glNormal3dv(n1.dataPointer());
        p0 = pStart + n1*r; glVertex3dv(p0.dataPointer());
        glNormal3dv(n1.dataPointer());
        p1 = pEnd + n1*r; glVertex3dv(p1.dataPointer());
        glNormal3dv(n2.dataPointer());
        p2 = pEnd + n2*r; glVertex3dv(p2.dataPointer());
        glNormal3dv(n2.dataPointer());
        p3 = pStart + n2*r; glVertex3dv(p3.dataPointer());
        glEnd();

        glBegin(GL_QUADS);
        glNormal3dv(n2.dataPointer());
        p0 = pStart + n2*r; glVertex3dv(p0.dataPointer());
        glNormal3dv(n2.dataPointer());
        p1 = pEnd + n2*r; glVertex3dv(p1.dataPointer());
        glNormal3dv(n3.dataPointer());
        p2 = pEnd + n3*r; glVertex3dv(p2.dataPointer());
        glNormal3dv(n3.dataPointer());
        p3 = pStart + n3*r; glVertex3dv(p3.dataPointer());
        glEnd();

        glBegin(GL_QUADS);
        glNormal3dv(n3.dataPointer());
        p0 = pStart + n3*r; glVertex3dv(p0.dataPointer());
        glNormal3dv(n3.dataPointer());
        p1 = pEnd + n3*r; glVertex3dv(p1.dataPointer());
        glNormal3dv(n0.dataPointer());
        p2 = pEnd + n0*r; glVertex3dv(p2.dataPointer());
        glNormal3dv(n0.dataPointer());
        p3 = pStart + n0*r; glVertex3dv(p3.dataPointer());
        glEnd();

    }
#else
    if (pIsRapid) {
        glLineWidth(1.0);
        glColor3f(1.0, 1.0, 0.0);
    } else {
        glLineWidth(2.0);
        glColor3f(1.0, 0.0, 1.0);
    }
    glBegin(GL_LINES);
    glVertex3dv(pStart.dataPointer());
    glVertex3dv(pEnd.dataPointer());
    glEnd();
    glLineWidth(1.0);
#endif
}


/**
 * Draw the toolpath motion into the scene viewer.
 */
void IAToolpathMotion::drawFlat(double w)
{
    if (!pIsRapid) {
#if 1
        /**
         \todo this should draw a cap depending on the previous line.
         \todo this is the brute force approach which could be made so much
         faster. This approach just draws an octagon, extende by a line.
         */
        IAVector3d d = pEnd - pStart;
        IAVector3d u = d.normalized();
        double xo = u.x() * w * 0.5, x7 = xo * 0.7;
        double yo = u.y() * w * 0.5, y7 = yo * 0.7;;
        glBegin(GL_POLYGON);
        glVertex3d(pStart.x()-xo, pStart.y()-yo, pStart.z());
        glVertex3d(pStart.x()-x7-y7, pStart.y()-y7+x7, pStart.z());
        glVertex3d(pStart.x()-yo, pStart.y()+xo, pStart.z());
        glVertex3d(pEnd.x()-yo, pEnd.y()+xo, pEnd.z());
        glVertex3d(pEnd.x()+x7-y7, pEnd.y()+y7+x7, pEnd.z());
        glVertex3d(pEnd.x()+xo, pEnd.y()+yo, pEnd.z());
        glVertex3d(pEnd.x()+x7+y7, pEnd.y()+y7-x7, pEnd.z());
        glVertex3d(pEnd.x()+yo, pEnd.y()-xo, pEnd.z());
        glVertex3d(pStart.x()+yo, pStart.y()-xo, pStart.z());
        glVertex3d(pStart.x()-x7+y7, pStart.y()-y7-x7, pStart.z());
        glEnd();
#else
        /** \bug line width! */
        glBegin(GL_LINES);
        glVertex3dv(pStart.dataPointer());
        glVertex3dv(pEnd.dataPointer());
        glEnd();
#endif
    }
}


/**
 * Draw the toolpath motion into the scene viewer.
 */
void IAToolpathMotion::drawFlatToBitmap(IAFramebuffer *fb, double w, int color)
{
    if (!pIsRapid) {
        /**
         \todo this should draw a cap depending on the previous line.
         \todo this is the brute force approach which could be made so much
         faster. This approach just draws an octagon, extende by a line.
         */
        IAVector3d d = pEnd - pStart;
        IAVector3d u = d.normalized();
        double xo = u.x() * w * 0.5, x7 = xo * 0.7;
        double yo = u.y() * w * 0.5, y7 = yo * 0.7;;
        fb->beginComplexPolygon();
        fb->addPoint(pStart.x()-xo, pStart.y()-yo);
        fb->addPoint(pStart.x()-x7-y7, pStart.y()-y7+x7);
        fb->addPoint(pStart.x()-yo, pStart.y()+xo);
        fb->addPoint(pEnd.x()-yo, pEnd.y()+xo);
        fb->addPoint(pEnd.x()+x7-y7, pEnd.y()+y7+x7);
        fb->addPoint(pEnd.x()+xo, pEnd.y()+yo);
        fb->addPoint(pEnd.x()+x7+y7, pEnd.y()+y7-x7);
        fb->addPoint(pEnd.x()+yo, pEnd.y()-xo);
        fb->addPoint(pStart.x()+yo, pStart.y()-xo);
        fb->addPoint(pStart.x()-x7+y7, pStart.y()-y7-x7);
        fb->endComplexPolygon(color);
    }
}


/**
 * Save the toolpath element as a GCode file.
 */
void IAToolpathMotion::saveGCode(IAGcodeWriter &w)
{
    if (pIsRapid) {
        w.cmdRetractMove(pEnd);
//        bool retract = ((pEnd-pStart).length() > 5.0);
//        if (retract) w.cmdRetract();
//        w.cmdRapidMove(pEnd);
//        if (retract) w.cmdUnretract();
    } else {
        if (w.position()!=pStart) {
            w.cmdRetractMove(pStart);
//            bool retract = ((w.position()-pStart).length() > 5.0);
//            if (retract) w.cmdRetract();
//            w.cmdRapidMove(pStart);
//            if (retract) w.cmdUnretract();
        }
        w.cmdPrintMove(pEnd);
    }
}


/**
 * Save the toolpath element as line in a DXF file.
 */
void IAToolpathMotion::saveDXF(IADxfWriter &g)
{
    if (!pIsRapid) {
        g.cmdLine(pStart, pEnd);
    }
}



