// generated by Fast Light User Interface Designer (fluid) version 1.0400

#include "IAGUIMain.h"
#ifdef __APPLE__
#endif
#ifdef __LINUX__
#endif
#ifdef _WIN32
#endif
static const char *sHelpAbout = /* text inlined from ../../html/helpAbout.html */
"<html>\n    <body>\n        <font face=\"sans\">\n            <p>&nbsp;</p>\n\
            <p><center><font size=8><b>Iota <!--[ver-->v0.3.2b<!--]--></b></fo\
nt></center></p>\n            <p><center><font size=5><b>Voxel based Mesh Slic\
er for Color 3D Printing</b></font></center></p>\n            \n            <p\
>\n            Iota is a voxel based slicer that can handle textured meshes fo\
r 3d printing. Iota can\n            generate image slices for inkjet/powder b\
ased machines, GCode files for color FDM/FFF\n            printing with multip\
le extruders and mixing extruders, and DXF files for creating stacked\n       \
     models with laser cutters.\n            </p>\n\n            <ul>\n       \
         <li>GitHub <a href=\"https://matthiaswm.github.io/IotaSlicer/\">pages\
</a> containing latest binaries</li>\n                <li><a href=\"https://gi\
thub.com/MatthiasWM/IotaSlicer\">Source code</a> on GitHub</li>\n             \
   <li>Pre-alpha testing <a href=\"https://youtu.be/VXX4sS26Q60\">video</a></l\
i>\n            </ul>\n\n            <p>Milestones:</p>\n            <ul>\n   \
             <li><b>v0.1</b>: successful generation of GCode for single nozzle\
 single color printer\n                    with shells, lids, and infills</li>\
\n                <li><b>v0.2</b>: settings UI for build parameters and basic \
printer settings</li>\n                <li><b>v0.3</b>: automatic generation o\
f support for flat triangles</li>\n                <li>v0.4: material selectio\
n for support structures and body (dual extruder)</li>\n                <li>v0\
.5: code generation for belt printers (BlackBelt)</li>\n                <li>v0\
.6: multiple meshes per session, move, scale, and rotate meshes</li>\n        \
        <li>v0.7: load textured models (obj), render projected texture rim, se\
ams</li>\n                <li>v0.8: sort toolpath segments by color and print \
in dual hotend dual color</li>\n                <li>v0.9: support for mixing e\
xtruders and virtual extruders and waste columns</li>\n                <li>v0.\
10: dialogs to generate new printers</li>\n                <li>....</li>\n    \
            <li>v1.0: load colored and textured STL and OBJ files, new printer\
s, printer\n                    settings, build settings, reliable and repeata\
ble printouts, documentation,\n                    web page, user managment, f\
orum, automated builds and releases, etc. </li>\n                <li> new infi\
lls, more color mixing, material mixing, multi-mesh color, etc. etc.</li>\n   \
         </ul>\n        </font>\n    </body>\n</html>\n";
static const char *sHelpLicenses = /* text inlined from ../../html/helpLicenses.html */
"<html>\n    <body>\n        <font face=\"sans\">\n            <p>&nbsp;</p>\n\
            <p><center><font size=8><b>Iota <!--[ver-->v0.3.2b<!--]--></b></fo\
nt></center></p>\n            <p><center><font size=5><b>Voxel based Mesh Slic\
er for Color 3D Printing</b></font></center></p>\n\n            <h3>Iota uses \
<a href=\"http://www.fltk.org/\">FLTK</a></h3>\n            <p>\n            \
\"FLTK (pronounced \"fulltick\") is a cross-platform C++ GUI toolkit for\n    \
        UNIX(r)/Linux(r) (X11), Microsoft(r) Windows(r), and MacOS(r) X. FLTK\
\n            provides modern GUI functionality without the bloat and supports\
 3D\n            graphics via OpenGL(r) and its built-in GLUT emulation.\"\n  \
          </p>\n            <p>\n            FLTK is provided under the terms \
of the\n            <a href=\"http://www.fltk.org/COPYING.php\">GNU Library Pu\
blic License</a>,\n            Version 2 with exceptions that allow for static\
 linking.\n            </p>\n\n            <h3>Iota uses <a href=\"http://www.\
lua.org/home.html\">Lua</a></h3>\n            <p>\n            \"Lua is a powe\
rful, efficient, lightweight, embeddable scripting\n            language. It s\
upports procedural programming, object-oriented\n            programming, func\
tional programming, data-driven programming,\n            and data description\
.\"\n            </p>\n            <p>\n            <a href=\"http://www.lua.o\
rg/license.html\">Lua</a>\n            is free software distributed under the \
terms of the MIT license\n            reproduced here. Lua may be used for any\
 purpose, including\n            commercial purposes, at absolutely no cost. N\
o paperwork, no\n            royalties, no GNU-like \"copyleft\" restrictions,\
 either. Just\n            download it and use it.\n            </p>\n\n      \
      <h3>Iota uses <a href=\"https://www.opengl.org\">OpenGL</a></h3>\n      \
      <p>\n            \"OpenGL is the premier environment for developing port\
able, interactive\n            2D and 3D graphics applications. Since its intr\
oduction in 1992, OpenGL\n            has become the industry\'s most widely u\
sed and supported 2D and 3D\n            graphics application programming inte\
rface (API), bringing thousands of\n            applications to a wide variety\
 of computer platforms. OpenGL fosters\n            innovation and speeds appl\
ication development by incorporating a broad\n            set of rendering, te\
xture mapping, special effects, and other powerful\n            visualization \
functions. Developers can leverage the power of OpenGL\n            across all\
 popular desktop and workstation platforms, ensuring wide\n            applica\
tion deployment.\"\n            </p>\n            <p>\n            End users, \
independent software vendors, and others writing code based\n            on th\
e OpenGL API are free from licensing requirements.\n            </p>\n\n      \
      <h3>Iota uses <a href=\"https://code.google.com/archive/p/lib3ds/\">lib3\
ds</a></h3>\n            <p>\n            lib3ds is an overall software librar\
y for managing 3D-Studio Release 3\n            and 4 \".3DS\" files. It is a \
free alternative to Autodesk\'s 3DS File\n            Toolkit for managing 3DS\
 files.\n            </p>\n            <p>\n            License: <a href=\"htt\
ps://www.gnu.org/licenses/lgpl.html\">GNU Lesser GPL</a>\n            </p>\n\n\
            <h3>Iota uses <a href=\"http://potrace.sourceforge.net/\">potrace<\
/a> by Peter Selinger</h3>\n            <p>\n            \"Potrace(TM) is a to\
ol for tracing a bitmap, which means, transforming\n            a bitmap into \
a smooth, scalable image.\"\n            </p>\n            <p>\n            Th\
is program is free software; you can redistribute it and/or modify\n          \
  it under the terms of the GNU General Public License as published by\n      \
      the Free Software Foundation; either version 2, or (at your option)\n   \
         any later version.\n            </p>\n\n            <h3>Iota uses <a \
href=\"http://www.antigrain.com/research/adaptive_bezier/index.html\">Adaptive\
 Subdivision of Bezier Curves</a> by Maxim Shemanarev</h3>\n            <p>\n \
           \"An attempt to achieve perfect result in Bezier curve approximatio\
n.\"\n            </p>\n            <p>\n            AGG is free software; you\
 can redistribute it and/or\n            modify it under the terms of the GNU \
General Public License\n            as published by the Free Software Foundati\
on; either version 2\n            of the License, or (at your option) any late\
r version.</p>\n\n            <h3>Iota includes <a href=\"https://www.thingive\
rse.com/thing:2906756\">Hex surface vase</a> by <a href=\"https://www.dr-lex.b\
e\">DrLex</a></h3>\n            <p>\n            Hex surface vase (spiral prin\
t) by DrLex is licensed under the Creative\n            Commons - Attribution \
license.</p>\n\n<!--\n            <h3>Iota includes <a href=\"http://www.3dben\
chy.com\">#3DBenchy</a></h3>\n            <p>\n            \"#3DBenchy is a 3D\
 model specifically designed for testing and\n            benchmarking 3D prin\
ters.\"</p>\n            <p>\n            <a href=\"http://www.3dbenchy.com/li\
cense/\">#3DBenchy</a> by\n            Creative-Tools.com is licensed under a \
Creative Commons\n            Attribution-NoDerivatives 4.0 International Lice\
nse. Permissions\n            beyond the scope and typical usage examples are \
explained below.</p>\n            <p>\n            Feel free to redistribute t\
he unmodified #3DBenchy STL file as you\n            please. Such as ... bundl\
ing the STL or pre-sliced print file with\n            3D printer kits, etc.</\
p>\n-->\n        </font>\n\n    </body>\n</html>\n";

Fl_Double_Window *wMainWindow=(Fl_Double_Window *)0;

static void cb_New(Fl_Menu_*, void*) {
  Iota.userMenuFileNewProject();
}

static void cb_Open(Fl_Menu_*, void*) {
  Iota.userMenuFileOpen();
}

static void cb_wRecentFiles(Fl_Menu_*, void*) {
  Iota.userMenuOpenRecentFile(0);
}

static void cb_(Fl_Menu_*, void*) {
  Iota.userMenuOpenRecentFile(1);
}

static void cb_1(Fl_Menu_*, void*) {
  Iota.userMenuOpenRecentFile(2);
}

static void cb_2(Fl_Menu_*, void*) {
  Iota.userMenuOpenRecentFile(3);
}

static void cb_3(Fl_Menu_*, void*) {
  Iota.userMenuOpenRecentFile(4);
}

static void cb_4(Fl_Menu_*, void*) {
  Iota.userMenuOpenRecentFile(5);
}

static void cb_5(Fl_Menu_*, void*) {
  Iota.userMenuOpenRecentFile(6);
}

static void cb_6(Fl_Menu_*, void*) {
  Iota.userMenuOpenRecentFile(7);
}

static void cb_7(Fl_Menu_*, void*) {
  Iota.userMenuOpenRecentFile(8);
}

static void cb_8(Fl_Menu_*, void*) {
  Iota.userMenuOpenRecentFile(9);
}

static void cb_Clear(Fl_Menu_*, void*) {
  Iota.userMenuClearRecentFileList();
}

static void cb_Quit(Fl_Menu_*, void*) {
  Iota.userMenuFileQuit();
}

static void cb_Save(Fl_Menu_*, void*) {
  Iota.userMenuSliceSave();
}

static void cb_Save1(Fl_Menu_*, void*) {
  Iota.userMenuSliceSaveAs();
}

static void cb_Clean(Fl_Menu_*, void*) {
  Iota.userMenuSliceClean();
}

static void cb_Slice(Fl_Menu_*, void*) {
  Iota.userMenuSliceSliceAll();
}

static void cb_Manage(Fl_Menu_*, void*) {
  Iota.userMenuSettingsManagePrinter();
}

static void cb_Test(Fl_Menu_*, void*) {
  Iota.lua.dostring("Iota:quit()");
}

static void cb_Versioneer(Fl_Menu_*, void*) {
  Iota.userMenuHelpVersioneer();
}

static void cb_About(Fl_Menu_*, void*) {
  Iota.userMenuHelpAbout();
}

Fl_Menu_Item menu_[] = {
 {"File", 0,  0, 0, 64, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"New Project", FL_COMMAND|0x6e,  (Fl_Callback*)cb_New, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"Open...", FL_COMMAND|0x6f,  (Fl_Callback*)cb_Open, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"Open Recent", 0,  0, 0, 192, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"", 0x80031,  (Fl_Callback*)cb_wRecentFiles, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"", 0x80032,  (Fl_Callback*)cb_, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"", 0x80033,  (Fl_Callback*)cb_1, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"", 0x80034,  (Fl_Callback*)cb_2, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"", 0x80035,  (Fl_Callback*)cb_3, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"", 0x80036,  (Fl_Callback*)cb_4, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"", 0x80037,  (Fl_Callback*)cb_5, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"", 0x80038,  (Fl_Callback*)cb_6, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"", 0x80039,  (Fl_Callback*)cb_7, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"", 0x80030,  (Fl_Callback*)cb_8, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"Clear List", 0,  (Fl_Callback*)cb_Clear, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {0,0,0,0,0,0,0,0,0},
 {"Save Project", 0,  0, 0, 1, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"Save Project As...", 0,  0, 0, 129, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"Print 2D...", 0,  0, 0, 129, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"Quit", FL_COMMAND|0x71,  (Fl_Callback*)cb_Quit, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {0,0,0,0,0,0,0,0,0},
 {"Edit", 0,  0, 0, 64, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"Undo", 0,  0, 0, 1, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"Redo", 0,  0, 0, 1, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"Duplicate", 0,  0, 0, 1, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"Delete", 0,  0, 0, 1, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"Select All", 0,  0, 0, 1, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"Inverst Selection", 0,  0, 0, 1, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"Arrange All", 0,  0, 0, 1, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {0,0,0,0,0,0,0,0,0},
 {"View", 0,  0, 0, 64, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"Reset", 0,  0, 0, 1, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {0,0,0,0,0,0,0,0,0},
 {"Slice", 0,  0, 0, 64, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"Run 3D Print...", FL_COMMAND|0x72,  0, 0, 1, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"Save Slices", FL_COMMAND|0x75,  (Fl_Callback*)cb_Save, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"Save Slices As...", FL_COMMAND|0x10075,  (Fl_Callback*)cb_Save1, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"Clean", FL_COMMAND|0x1006b,  (Fl_Callback*)cb_Clean, 0, 128, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"Slice All", FL_COMMAND|0x62,  (Fl_Callback*)cb_Slice, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"Slice Selected", FL_COMMAND|0x80062,  0, 0, 1, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {0,0,0,0,0,0,0,0,0},
 {"Settings", 0,  0, 0, 64, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"Manage Printers...", FL_COMMAND|0x2c,  (Fl_Callback*)cb_Manage, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"Manage Materials...", 0,  0, 0, 1, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {0,0,0,0,0,0,0,0,0},
 {"Help", 0,  0, 0, 64, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"Test Lua", 0,  (Fl_Callback*)cb_Test, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"Versioneer...", 0,  (Fl_Callback*)cb_Versioneer, 0, 128, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"About...", 0,  (Fl_Callback*)cb_About, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {0,0,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,0,0}
};

IASceneView *gSceneView=(IASceneView *)0;

static void cb_txt(IAGLButton*, void*) {
  Iota.gShowTexture = !Iota.gShowTexture;
gSceneView->redraw();
}

static void cb_slc(IAGLButton*, void*) {
  Iota.gShowSlice = !Iota.gShowSlice;
gSceneView->redraw();
}

static void cb_prsp(IAGLButton*, void*) {
  gSceneView->setPerspectiveView();
gSceneView->redraw();
}

static void cb_top(IAGLButton*, void*) {
  gSceneView->setTopView();
gSceneView->redraw();
}

IAGLRangeSlider *zRangeSlider=(IAGLRangeSlider *)0;

static void cb_zRangeSlider(IAGLRangeSlider*, void*) {
  Iota.gShowSlice = true;
if (Iota.pCurrentPrinter)
    Iota.pCurrentPrinter->rangeSliderChanged();
gSceneView->redraw();
}

Fl_Choice *wPrinterChoice=(Fl_Choice *)0;

static void cb_wPrinterChoice(Fl_Choice* o, void*) {
  Iota.userMainSelectPrinter();
o->redraw();
}

Fl_Tree *wSessionSettings=(Fl_Tree *)0;

Fl_Double_Window* createIotaAppWindow() {
  { wMainWindow = new Fl_Double_Window(850, 600, "Iota Slicer");
    { Fl_Menu_Bar* o = new Fl_Menu_Bar(0, 0, 850, 28);
      o->menu(menu_);
    } // Fl_Menu_Bar* o
    { Fl_Group* o = new Fl_Group(0, 28, 850, 572);
      { gSceneView = new IASceneView(0, 28, 600, 572);
        gSceneView->box(FL_NO_BOX);
        gSceneView->color(FL_BACKGROUND_COLOR);
        gSceneView->selection_color(FL_BACKGROUND_COLOR);
        gSceneView->labeltype(FL_NORMAL_LABEL);
        gSceneView->labelfont(0);
        gSceneView->labelsize(14);
        gSceneView->labelcolor(FL_FOREGROUND_COLOR);
        gSceneView->align(Fl_Align(FL_ALIGN_TOP));
        gSceneView->when(FL_WHEN_RELEASE);
        { // Placeholder to sneakily call begin()
          Fl_Box* o = new Fl_Box(24, 52, 28, 28);
          o->hide();
          gSceneView->begin();
        } // Fl_Box* o
        { Fl_Group* o = new Fl_Group(0, 28, 600, 572);
          { Fl_Group* o = new Fl_Group(10, 38, 35, 552);
            { IAGLButton* o = new IAGLButton(10, 38, 35, 25, "txt");
              o->box(FL_UP_BOX);
              o->color(FL_BACKGROUND_COLOR);
              o->selection_color((Fl_Color)236);
              o->labeltype(FL_NORMAL_LABEL);
              o->labelfont(0);
              o->labelsize(14);
              o->labelcolor(FL_FOREGROUND_COLOR);
              o->callback((Fl_Callback*)cb_txt);
              o->align(Fl_Align(FL_ALIGN_CENTER));
              o->when(FL_WHEN_RELEASE);
            } // IAGLButton* o
            { IAGLButton* o = new IAGLButton(10, 73, 35, 25, "slc");
              o->box(FL_UP_BOX);
              o->color(FL_BACKGROUND_COLOR);
              o->selection_color((Fl_Color)236);
              o->labeltype(FL_NORMAL_LABEL);
              o->labelfont(0);
              o->labelsize(14);
              o->labelcolor(FL_FOREGROUND_COLOR);
              o->callback((Fl_Callback*)cb_slc);
              o->align(Fl_Align(FL_ALIGN_CENTER));
              o->when(FL_WHEN_RELEASE);
            } // IAGLButton* o
            { Fl_Box* o = new Fl_Box(10, 138, 35, 418);
              Fl_Group::current()->resizable(o);
            } // Fl_Box* o
            o->end();
          } // Fl_Group* o
          { Fl_Group* o = new Fl_Group(48, 38, 504, 552);
            o->end();
            Fl_Group::current()->resizable(o);
          } // Fl_Group* o
          { Fl_Group* o = new Fl_Group(555, 38, 35, 552);
            { IAGLButton* o = new IAGLButton(555, 38, 35, 25, "prsp");
              o->box(FL_UP_BOX);
              o->color(FL_BACKGROUND_COLOR);
              o->selection_color((Fl_Color)236);
              o->labeltype(FL_NORMAL_LABEL);
              o->labelfont(0);
              o->labelsize(14);
              o->labelcolor(FL_FOREGROUND_COLOR);
              o->callback((Fl_Callback*)cb_prsp);
              o->align(Fl_Align(FL_ALIGN_CENTER));
              o->when(FL_WHEN_RELEASE);
            } // IAGLButton* o
            { IAGLButton* o = new IAGLButton(555, 73, 35, 25, "top");
              o->box(FL_UP_BOX);
              o->color(FL_BACKGROUND_COLOR);
              o->selection_color((Fl_Color)236);
              o->labeltype(FL_NORMAL_LABEL);
              o->labelfont(0);
              o->labelsize(14);
              o->labelcolor(FL_FOREGROUND_COLOR);
              o->callback((Fl_Callback*)cb_top);
              o->align(Fl_Align(FL_ALIGN_CENTER));
              o->when(FL_WHEN_RELEASE);
            } // IAGLButton* o
            { zRangeSlider = new IAGLRangeSlider(555, 104, 35, 452);
              zRangeSlider->box(FL_DOWN_BOX);
              zRangeSlider->color(FL_BACKGROUND_COLOR);
              zRangeSlider->selection_color(FL_BACKGROUND_COLOR);
              zRangeSlider->labeltype(FL_NORMAL_LABEL);
              zRangeSlider->labelfont(0);
              zRangeSlider->labelsize(14);
              zRangeSlider->labelcolor(FL_FOREGROUND_COLOR);
              zRangeSlider->maximum(250);
              zRangeSlider->callback((Fl_Callback*)cb_zRangeSlider);
              zRangeSlider->align(Fl_Align(FL_ALIGN_BOTTOM));
              zRangeSlider->when(FL_WHEN_CHANGED);
              Fl_Group::current()->resizable(zRangeSlider);
            } // IAGLRangeSlider* zRangeSlider
            o->end();
          } // Fl_Group* o
          // o->parent()->remove(o); gSceneView->add(o);
          o->resize(0, 0, gSceneView->w(), gSceneView->h());  gSceneView->resizable(o);
          o->end();
        } // Fl_Group* o
        gSceneView->end();
        Fl_Group::current()->resizable(gSceneView);
      } // IASceneView* gSceneView
      { // Properties Column
        Fl_Group* o = new Fl_Group(600, 28, 250, 572);
        o->box(FL_FLAT_BOX);
        { // Properties inset
          Fl_Group* o = new Fl_Group(605, 33, 240, 562);
          o->box(FL_FLAT_BOX);
          { // Session settings container
            Fl_Group* o = new Fl_Group(605, 33, 240, 562);
            o->labelsize(12);
            o->align(Fl_Align(FL_ALIGN_CENTER|FL_ALIGN_INSIDE));
            { wPrinterChoice = new Fl_Choice(605, 33, 240, 28);
              wPrinterChoice->box(FL_UP_BOX);
              wPrinterChoice->down_box(FL_DOWN_BOX);
              wPrinterChoice->color(FL_DARK1);
              wPrinterChoice->labelsize(12);
              wPrinterChoice->textsize(12);
              wPrinterChoice->callback((Fl_Callback*)cb_wPrinterChoice);
              wPrinterChoice->align(Fl_Align(FL_ALIGN_CENTER));
            } // Fl_Choice* wPrinterChoice
            { wSessionSettings = new Fl_Tree(605, 62, 240, 475);
              Fl_Group::current()->resizable(wSessionSettings);
            } // Fl_Tree* wSessionSettings
            o->end();
            Fl_Group::current()->resizable(o);
          } // Fl_Group* o
          o->end();
          Fl_Group::current()->resizable(o);
        } // Fl_Group* o
        o->end();
      } // Fl_Group* o
      o->end();
      Fl_Group::current()->resizable(o);
    } // Fl_Group* o
    wMainWindow->end();
  } // Fl_Double_Window* wMainWindow
  return wMainWindow;
}

static void cb_OK(Fl_Button* o, void*) {
  o->window()->hide();
}

Fl_Double_Window* createIotaAboutWindow() {
  Fl_Double_Window* w;
  { Fl_Double_Window* o = new Fl_Double_Window(600, 400, "About Iota");
    w = o; if (w) {/* empty */}
    { Fl_Group* o = new Fl_Group(10, 10, 584, 344);
      { Fl_Tabs* o = new Fl_Tabs(10, 10, 580, 340);
        { Fl_Group* o = new Fl_Group(10, 35, 580, 315, "About");
          o->box(FL_UP_BOX);
          { Fl_Help_View* o = new Fl_Help_View(12, 37, 576, 311);
            o->box(FL_FLAT_BOX);
            o->color(FL_BACKGROUND_COLOR);
            o->labelfont(8);
            Fl_Group::current()->resizable(o);
            o->value((const char*)sHelpAbout);
            o->textsize(14);
            o->textfont(FL_HELVETICA);
          } // Fl_Help_View* o
          o->end();
          Fl_Group::current()->resizable(o);
        } // Fl_Group* o
        { Fl_Group* o = new Fl_Group(10, 35, 580, 315, "Licenses");
          o->box(FL_UP_BOX);
          o->hide();
          { Fl_Help_View* o = new Fl_Help_View(12, 37, 576, 311);
            o->box(FL_FLAT_BOX);
            o->color(FL_BACKGROUND_COLOR);
            Fl_Group::current()->resizable(o);
            o->value((const char*)sHelpLicenses);
            o->textsize(14);
            o->textfont(FL_HELVETICA);
          } // Fl_Help_View* o
          o->end();
        } // Fl_Group* o
        o->end();
        Fl_Group::current()->resizable(o);
      } // Fl_Tabs* o
      o->end();
      Fl_Group::current()->resizable(o);
    } // Fl_Group* o
    { Fl_Group* o = new Fl_Group(10, 360, 580, 28);
      { Fl_Button* o = new Fl_Button(430, 360, 120, 28, "OK");
        o->callback((Fl_Callback*)cb_OK);
      } // Fl_Button* o
      { Fl_Box* o = new Fl_Box(10, 360, 418, 28);
        Fl_Group::current()->resizable(o);
      } // Fl_Box* o
      o->end();
    } // Fl_Group* o
    o->set_modal();
    o->end();
  } // Fl_Double_Window* o
  return w;
}

Fl_Double_Window *wSettingsWindow=(Fl_Double_Window *)0;

static void cb_wSettingsWindow(Fl_Double_Window* o, void*) {
  Iota.userDialogSettingPrinterDeselect();
o->hide();
}

static void cb_filesaveas(Fl_Button*, void*) {
  Iota.userDialogSettingPrinterDeselect();
}

static void cb_circle(Fl_Button*, void*) {
  Iota.userDialogSettingPrinterDeselect();
}

Fl_Browser *wSettingsPrinterList=(Fl_Browser *)0;

static void cb_wSettingsPrinterList(Fl_Browser*, void*) {
  Iota.userDialogSettingPrinterDeselect();
Iota.userDialogSettingPrinterSelect();
}

Fl_Button *wSettingPrinterAdd=(Fl_Button *)0;

static void cb_wSettingPrinterAdd(Fl_Button*, void*) {
  Iota.userDialogSettingPrinterAdd();
}

static void cb_9(Fl_Button*, void*) {
  Iota.userDialogSettingPrinterRemove();
}

Fl_Tree *wSettingsPrinterProperties=(Fl_Tree *)0;

Fl_Double_Window* createSettingWindow() {
  { // /// \todo save position and size
    wSettingsWindow = new Fl_Double_Window(640, 400, "Settings");
    wSettingsWindow->callback((Fl_Callback*)cb_wSettingsWindow);
    { // /// \todo implement the tab style selection of panes
      Fl_Pack* o = new Fl_Pack(0, 0, 640, 48);
      o->type(1);
      { // /// \todo add general settings below
        Fl_Group* o = new Fl_Group(0, 2, 50, 44, "General");
        o->box(FL_FLAT_BOX);
        o->labelsize(10);
        o->align(Fl_Align(FL_ALIGN_BOTTOM|FL_ALIGN_INSIDE));
        { // /// \todo find a new icon
          Fl_Button* o = new Fl_Button(0, 2, 50, 36, "@filesaveas");
          o->box(FL_NO_BOX);
          o->labelsize(20);
          o->labelcolor((Fl_Color)40);
          o->callback((Fl_Callback*)cb_filesaveas);
          o->align(Fl_Align(FL_ALIGN_CENTER|FL_ALIGN_INSIDE));
        } // Fl_Button* o
        o->end();
      } // Fl_Group* o
      { Fl_Group* o = new Fl_Group(50, 2, 50, 44, "3D Printer");
        o->box(FL_FLAT_BOX);
        o->color(FL_DARK1);
        o->labelsize(10);
        o->align(Fl_Align(FL_ALIGN_BOTTOM|FL_ALIGN_INSIDE));
        { // /// \todo find a new icon
          Fl_Button* o = new Fl_Button(50, 2, 50, 36, "@fileprint");
          o->box(FL_NO_BOX);
          o->labelsize(20);
          o->labelcolor((Fl_Color)40);
          o->align(Fl_Align(FL_ALIGN_CENTER|FL_ALIGN_INSIDE));
        } // Fl_Button* o
        o->end();
      } // Fl_Group* o
      { Fl_Group* o = new Fl_Group(100, 2, 50, 44, "Material");
        o->box(FL_FLAT_BOX);
        o->labelsize(10);
        o->align(Fl_Align(FL_ALIGN_BOTTOM|FL_ALIGN_INSIDE));
        { // /// \todo find a new icon
          Fl_Button* o = new Fl_Button(100, 2, 50, 36, "@circle");
          o->box(FL_NO_BOX);
          o->labelsize(20);
          o->labelcolor((Fl_Color)40);
          o->callback((Fl_Callback*)cb_circle);
          o->align(Fl_Align(FL_ALIGN_CENTER|FL_ALIGN_INSIDE));
        } // Fl_Button* o
        o->end();
      } // Fl_Group* o
      o->end();
    } // Fl_Pack* o
    { Fl_Box* o = new Fl_Box(0, 48, 640, 4);
      o->box(FL_DOWN_BOX);
    } // Fl_Box* o
    { Fl_Group* o = new Fl_Group(0, 52, 640, 348);
      o->box(FL_FLAT_BOX);
      o->color((Fl_Color)51);
      { Fl_Group* o = new Fl_Group(9, 62, 151, 328);
        o->box(FL_THIN_DOWN_BOX);
        o->color(FL_LIGHT3);
        { Fl_Box* o = new Fl_Box(11, 63, 148, 20, "3D Printer");
          o->box(FL_THIN_UP_BOX);
          o->color(FL_LIGHT2);
          o->labelsize(13);
        } // Fl_Box* o
        { wSettingsPrinterList = new Fl_Browser(11, 83, 148, 286);
          wSettingsPrinterList->type(2);
          wSettingsPrinterList->box(FL_FLAT_BOX);
          wSettingsPrinterList->color((Fl_Color)55);
          wSettingsPrinterList->textsize(12);
          wSettingsPrinterList->callback((Fl_Callback*)cb_wSettingsPrinterList);
          Fl_Group::current()->resizable(wSettingsPrinterList);
        } // Fl_Browser* wSettingsPrinterList
        { Fl_Group* o = new Fl_Group(11, 369, 148, 20);
          o->box(FL_THIN_UP_BOX);
          o->color(FL_LIGHT2);
          { wSettingPrinterAdd = new Fl_Button(12, 370, 18, 18, "+");
            wSettingPrinterAdd->box(FL_NO_BOX);
            wSettingPrinterAdd->color(FL_LIGHT2);
            wSettingPrinterAdd->callback((Fl_Callback*)cb_wSettingPrinterAdd);
          } // Fl_Button* wSettingPrinterAdd
          { Fl_Button* o = new Fl_Button(30, 370, 18, 18, "-");
            o->box(FL_NO_BOX);
            o->color(FL_LIGHT2);
            o->callback((Fl_Callback*)cb_9);
          } // Fl_Button* o
          { // /// \todo ICON, choose form internet templates? 
            Fl_Button* o = new Fl_Button(48, 370, 18, 18, "@-22>");
            o->box(FL_NO_BOX);
            o->color(FL_LIGHT2);
            o->labelcolor((Fl_Color)42);
            o->hide();
          } // Fl_Button* o
          o->end();
        } // Fl_Group* o
        o->end();
      } // Fl_Group* o
      { Fl_Group* o = new Fl_Group(170, 62, 460, 328);
        o->box(FL_THIN_DOWN_BOX);
        o->color(FL_LIGHT3);
        { wSettingsPrinterProperties = new Fl_Tree(172, 64, 456, 324);
          wSettingsPrinterProperties->box(FL_FLAT_BOX);
          wSettingsPrinterProperties->color((Fl_Color)55);
          Fl_Group::current()->resizable(wSettingsPrinterProperties);
        } // Fl_Tree* wSettingsPrinterProperties
        o->end();
        Fl_Group::current()->resizable(o);
      } // Fl_Group* o
      o->end();
      Fl_Group::current()->resizable(o);
    } // Fl_Group* o
    wSettingsWindow->set_modal();
    wSettingsWindow->size_range(640, 320, 640, 2048);
    wSettingsWindow->end();
  } // Fl_Double_Window* wSettingsWindow
  return wSettingsWindow;
}

void IAVersioneerDialog::cb_wBasePath_i(Fl_Input*, void*) {
  setProjectPath();
}
void IAVersioneerDialog::cb_wBasePath(Fl_Input* o, void* v) {
  ((IAVersioneerDialog*)(o->parent()->user_data()))->cb_wBasePath_i(o,v);
}

void IAVersioneerDialog::cb_fileopen_i(Fl_Button*, void*) {
  selectProjectPath();
}
void IAVersioneerDialog::cb_fileopen(Fl_Button* o, void* v) {
  ((IAVersioneerDialog*)(o->parent()->user_data()))->cb_fileopen_i(o,v);
}

Fl_Menu_Item IAVersioneerDialog::menu_wClass[] = {
 {"-", 0,  0, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 12, 0},
 {"a", 0,  0, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 12, 0},
 {"b", 0,  0, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 12, 0},
 {0,0,0,0,0,0,0,0,0}
};

void IAVersioneerDialog::cb_wMajorPlus_i(Fl_Button*, void*) {
  majorPlus();
}
void IAVersioneerDialog::cb_wMajorPlus(Fl_Button* o, void* v) {
  ((IAVersioneerDialog*)(o->parent()->user_data()))->cb_wMajorPlus_i(o,v);
}

void IAVersioneerDialog::cb_wMinorPlus_i(Fl_Button*, void*) {
  minorPlus();
}
void IAVersioneerDialog::cb_wMinorPlus(Fl_Button* o, void* v) {
  ((IAVersioneerDialog*)(o->parent()->user_data()))->cb_wMinorPlus_i(o,v);
}

void IAVersioneerDialog::cb_wBuildPlus_i(Fl_Button*, void*) {
  buildPlus();
}
void IAVersioneerDialog::cb_wBuildPlus(Fl_Button* o, void* v) {
  ((IAVersioneerDialog*)(o->parent()->user_data()))->cb_wBuildPlus_i(o,v);
}

void IAVersioneerDialog::cb_Apply_i(Fl_Button*, void*) {
  saveSettings();
applySettings();
}
void IAVersioneerDialog::cb_Apply(Fl_Button* o, void* v) {
  ((IAVersioneerDialog*)(o->parent()->user_data()))->cb_Apply_i(o,v);
}

void IAVersioneerDialog::cb_wFLTKPath_i(Fl_Input*, void*) {
  setFLTKPath();
}
void IAVersioneerDialog::cb_wFLTKPath(Fl_Input* o, void* v) {
  ((IAVersioneerDialog*)(o->parent()->user_data()))->cb_wFLTKPath_i(o,v);
}

void IAVersioneerDialog::cb_fileopen1_i(Fl_Button*, void*) {
  selectFLTKPath();
}
void IAVersioneerDialog::cb_fileopen1(Fl_Button* o, void* v) {
  ((IAVersioneerDialog*)(o->parent()->user_data()))->cb_fileopen1_i(o,v);
}

void IAVersioneerDialog::cb_Update_i(Fl_Button*, void*) {
  saveSettings();
updateFLTK();
}
void IAVersioneerDialog::cb_Update(Fl_Button* o, void* v) {
  ((IAVersioneerDialog*)(o->parent()->user_data()))->cb_Update_i(o,v);
}

void IAVersioneerDialog::cb_wArchivePath_i(Fl_Input*, void*) {
  setProjectPath();
}
void IAVersioneerDialog::cb_wArchivePath(Fl_Input* o, void* v) {
  ((IAVersioneerDialog*)(o->parent()->user_data()))->cb_wArchivePath_i(o,v);
}

void IAVersioneerDialog::cb_fileopen2_i(Fl_Button*, void*) {
  selectArchivePath();
}
void IAVersioneerDialog::cb_fileopen2(Fl_Button* o, void* v) {
  ((IAVersioneerDialog*)(o->parent()->user_data()))->cb_fileopen2_i(o,v);
}

void IAVersioneerDialog::cb_Create_i(Fl_Button*, void*) {
  saveSettings();
createArchive();
// recompile in release mode
// pack into zip archive
// move to release folder
// ? upload;
}
void IAVersioneerDialog::cb_Create(Fl_Button* o, void* v) {
  ((IAVersioneerDialog*)(o->parent()->user_data()))->cb_Create_i(o,v);
}

void IAVersioneerDialog::cb_git_i(Fl_Button*, void*) {
  saveSettings();
gitTag();
}
void IAVersioneerDialog::cb_git(Fl_Button* o, void* v) {
  ((IAVersioneerDialog*)(o->parent()->user_data()))->cb_git_i(o,v);
}

void IAVersioneerDialog::cb_Close_i(Fl_Button*, void*) {
  wVersionWindow->hide();
}
void IAVersioneerDialog::cb_Close(Fl_Button* o, void* v) {
  ((IAVersioneerDialog*)(o->parent()->user_data()))->cb_Close_i(o,v);
}

Fl_Double_Window * IAVersioneerDialog::createWindow() {
  { wVersionWindow = new Fl_Double_Window(532, 431, "Versioneer for Iota Slicer");
    wVersionWindow->user_data((void*)(this));
    { wBasePath = new Fl_Input(105, 18, 265, 20, "IotaBase Path");
      wBasePath->labelsize(12);
      wBasePath->textsize(12);
      wBasePath->callback((Fl_Callback*)cb_wBasePath);
    } // Fl_Input* wBasePath
    { Fl_Button* o = new Fl_Button(369, 18, 33, 20, "@fileopen");
      o->labelcolor((Fl_Color)3);
      o->callback((Fl_Callback*)cb_fileopen);
    } // Fl_Button* o
    { Fl_Box* o = new Fl_Box(88, 47, 0, 20, "Version");
      o->labelsize(12);
      o->align(Fl_Align(FL_ALIGN_LEFT));
    } // Fl_Box* o
    { wMajor = new Fl_Input(105, 47, 52, 20);
      wMajor->labelsize(12);
      wMajor->textsize(12);
    } // Fl_Input* wMajor
    { Fl_Box* o = new Fl_Box(157, 47, 15, 20, ".");
      o->labelsize(12);
    } // Fl_Box* o
    { wMinor = new Fl_Input(172, 47, 52, 20);
      wMinor->labelsize(12);
      wMinor->textsize(12);
    } // Fl_Input* wMinor
    { Fl_Box* o = new Fl_Box(224, 47, 15, 20, ".");
      o->labelsize(12);
    } // Fl_Box* o
    { wBuild = new Fl_Input(239, 47, 52, 20);
      wBuild->labelsize(12);
      wBuild->textsize(12);
    } // Fl_Input* wBuild
    { wClass = new Fl_Input_Choice(293, 47, 64, 20);
      wClass->labelsize(12);
      wClass->textsize(12);
      wClass->menu(menu_wClass);
    } // Fl_Input_Choice* wClass
    { wMajorPlus = new Fl_Button(133, 70, 24, 20, "+");
      wMajorPlus->labelsize(12);
      wMajorPlus->callback((Fl_Callback*)cb_wMajorPlus);
    } // Fl_Button* wMajorPlus
    { wMinorPlus = new Fl_Button(200, 70, 24, 20, "+");
      wMinorPlus->labelsize(12);
      wMinorPlus->callback((Fl_Callback*)cb_wMinorPlus);
    } // Fl_Button* wMinorPlus
    { wBuildPlus = new Fl_Button(267, 70, 24, 20, "+");
      wBuildPlus->labelsize(12);
      wBuildPlus->callback((Fl_Callback*)cb_wBuildPlus);
    } // Fl_Button* wBuildPlus
    { Fl_Button* o = new Fl_Button(420, 67, 90, 24, "Apply to FIles");
      o->labelsize(12);
      o->callback((Fl_Callback*)cb_Apply);
    } // Fl_Button* o
    { wTerminal = new Fl_Simple_Terminal(12, 244, 510, 164);
      wTerminal->box(FL_DOWN_FRAME);
      wTerminal->color(FL_BACKGROUND2_COLOR);
      wTerminal->selection_color(FL_SELECTION_COLOR);
      wTerminal->labeltype(FL_NORMAL_LABEL);
      wTerminal->labelfont(0);
      wTerminal->labelsize(14);
      wTerminal->labelcolor(FL_FOREGROUND_COLOR);
      wTerminal->align(Fl_Align(FL_ALIGN_TOP));
      wTerminal->when(FL_WHEN_RELEASE);
    } // Fl_Simple_Terminal* wTerminal
    { wFLTKPath = new Fl_Input(107, 99, 265, 20, "Path to FLTK");
      wFLTKPath->labelsize(12);
      wFLTKPath->textsize(12);
      wFLTKPath->callback((Fl_Callback*)cb_wFLTKPath);
    } // Fl_Input* wFLTKPath
    { Fl_Button* o = new Fl_Button(371, 99, 33, 20, "@fileopen");
      o->labelcolor((Fl_Color)3);
      o->callback((Fl_Callback*)cb_fileopen1);
    } // Fl_Button* o
    { Fl_Button* o = new Fl_Button(422, 97, 90, 24, "Update FLTK");
      o->labelsize(12);
      o->callback((Fl_Callback*)cb_Update);
    } // Fl_Button* o
    { wArchivePath = new Fl_Input(107, 130, 265, 20, "Archive Path");
      wArchivePath->labelsize(12);
      wArchivePath->textsize(12);
      wArchivePath->callback((Fl_Callback*)cb_wArchivePath);
    } // Fl_Input* wArchivePath
    { Fl_Button* o = new Fl_Button(371, 130, 33, 20, "@fileopen");
      o->labelcolor((Fl_Color)3);
      o->callback((Fl_Callback*)cb_fileopen2);
    } // Fl_Button* o
    { Fl_Button* o = new Fl_Button(422, 128, 90, 24, "Create Archive");
      o->labelsize(12);
      o->callback((Fl_Callback*)cb_Create);
    } // Fl_Button* o
    { Fl_Button* o = new Fl_Button(422, 160, 90, 24, "git tag && push");
      o->labelsize(12);
      o->callback((Fl_Callback*)cb_git);
    } // Fl_Button* o
    { Fl_Button* o = new Fl_Button(422, 191, 90, 24, "Close Dialog");
      o->labelsize(12);
      o->callback((Fl_Callback*)cb_Close);
    } // Fl_Button* o
    wVersionWindow->end();
  } // Fl_Double_Window* wVersionWindow
  return wVersionWindow;
}

void IAVersioneerDialog::setProjectPath() {
}

void IAVersioneerDialog::selectProjectPath() {
}

void IAVersioneerDialog::majorPlus() {
}

void IAVersioneerDialog::minorPlus() {
}

void IAVersioneerDialog::buildPlus() {
}

void IAVersioneerDialog::saveSettings() {
}

void IAVersioneerDialog::setFLTKPath() {
}

void IAVersioneerDialog::selectFLTKPath() {
}

void IAVersioneerDialog::updateFLTK() {
}

void IAVersioneerDialog::setArchivePath() {
}

void IAVersioneerDialog::selectArchivePath() {
}

void IAVersioneerDialog::createArchive() {
}

void IAVersioneerDialog::gitTag() {
}

void IAVersioneerDialog::applySettings() {
}

IAVersioneerDialog::IAVersioneerDialog() {
}

IAVersioneerDialog::~IAVersioneerDialog() {
}
