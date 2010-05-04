/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_opengl.h>

#include <Foreach.h>

#include <Container.h>
#include <ContainerFactory.h>

#include <iostream>
#include <cmath>
#include <ctime>
#include <cstring>
#include <cstdlib>
#include <cstdio>

#include "Image.h"
#include "Model.h"
#include "Events.h"
#include "Util.h"
#include "OpenGL.h"

#include "Controller.h"
#include "sequence/Sequence.h"
#include "mapping/Mapping.h"

#include "Sdl.h"
#include "Fluids.h"
#include "View.h"
#include "SnowflakeController.h"
#include "DemoFactory.h"

namespace M = Model;
namespace V = View;
namespace C = Controller;
namespace R = Reflection;

/*--------------------------------------------------------------------------*/



/*--------------------------------------------------------------------------*/

bool bTiming = false;
bool bRec = false;
int mFrame = 0;

// Globals
FluidSystem psys;

float window_width = 1024;
float window_height = 768;

Vector3DF obj_from, obj_angs;

float cam_fov;

int psys_rate = 0; // Particle stuff
int psys_freq = 1;
int psys_demo = 0;
//int             psys_nmax = 4096;
int psys_nmax = 2048;

int iClrMode = 0; // Tryb koloru. Martwi mnie, że podaje się to do phys-machine.
bool bPntDraw = false; // Coś ważnego, ale nie wiem co.

/*--------------------------------------------------------------------------*/

static unsigned int frameCnt = 0;

// Czyli to są takie handlery.
static GLuint texName;

int mouseX = 0;
int mouseY = 0;

/*##########################################################################*/

Ptr <Container2::BeanFactoryContainer> container;

Ptr <C::SimpleController> image01Ctr;
Ptr <SnowflakeController> sniezynkaCtr;
Ptr <C::SimpleController> backgroundCtr;
Ptr <C::SimpleController> screenCtr;

Ptr <Sdl::EventDispatcher> sdlDispatcher;
Ptr <Events::MouseButtonDispatcher> mouseButtonDispatcher;
Ptr <Events::MouseMotionDispatcher> mouseMotionDispatcher;
Ptr <Events::MouseMotionDispatcher> mouseMotionScreenMargin;
Ptr <Sdl::TimerDispatcher> timeDispatcher;

Ptr <C::SimpleController> fluidCtr;

//Ptr <M::Primitive> screen;
Ptr <M::PointSet> fluid;
Ptr <M::Item> image01;
Ptr <M::Item> sniezynka;
Ptr <M::Item> background;


Ptr <C::SimpleController> asia1;
Ptr <C::SimpleController> asia2;
Ptr <C::SimpleController> asia3;
Ptr <C::SimpleController> asia4;

Ptr <C::Table> table;

void InitGL (int w, int h)
{
        glShadeModel(GL_FLAT);
        glDisable (GL_DEPTH_TEST);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        /*
         * Alpha blending. Niestety tekstura jest w niektorych miejscach
         * przezroczysta, ale wystaje spodniej niebieski kolor prostokątu.
         */
        glEnable (GL_BLEND);
        glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

/*##########################################################################*/

        // Widget structure (can be set in IoC container).
//        image01->setPath ("../gfx/pointer64.png");
//        sniezynka->setPath ("../gfx/snowflake2.png");
//        sniezynka->setPath ("../gfx/fx_leaf4.png");
//        sniezynka->setScale (0.25, 0.25);

//        background->setPath ("../gfx/main02.png");

        obj_from.x = 0;
        obj_from.y = 0;
        obj_from.z = 20; // emitter

        obj_angs.x = 118.7;
        obj_angs.y = 200;
        obj_angs.z = 1.0;

        psys.Initialize (BFLUID, psys_nmax);

        // Kod usunięty z FluidSystem
        DemoHelper::createDemo (&psys, 1, psys_nmax);

        psys.SetVec (EMIT_ANG, Vector3DF (obj_angs.x, obj_angs.y, obj_angs.z));
        psys.SetVec (EMIT_POS, Vector3DF (obj_from.x, obj_from.y, obj_from.z));

        psys.SetParam (PNT_DRAWMODE, int(bPntDraw ? 1 : 0));
        psys.SetParam (CLR_MODE, iClrMode);

/*--------------------------------------------------------------------------*/
#define TRY_CATCH

#if defined (TRY_CATCH)
        try {
#endif
                container = Container2::XmlContainerFactory::createContainer ("main.xml");

//                image01Ctr = Util::WidgetFactory::createImage ("../gfx/pointer64.png");
                image01Ctr = vcast <Ptr <C::SimpleController> > (container->getBean ("cursor"));


//                sniezynkaCtr = DemoFactory::createSniezynka ("../gfx/snowflake2.png");
                sniezynkaCtr = vcast <Ptr <SnowflakeController> > (container->getBean ("snowFlake"));

        //        backgroundCtr = Util::WidgetFactory::createImage ("../gfx/main02.png");
        //        screenCtr = Util::WidgetFactory::createScreen ();


                screenCtr = vcast <Ptr <C::SimpleController> > (container->getBean ("screen"));
                backgroundCtr = vcast <Ptr <C::SimpleController> > (container->getBean ("background"));

//                asia1 = Util::WidgetFactory::createImage ("../gfx/box/1.png");
//                asia2 = Util::WidgetFactory::createImage ("../gfx/box/2.png");
//                asia3 = Util::WidgetFactory::createImage ("../gfx/box/3.png");
//                asia4 = Util::WidgetFactory::createImage ("../gfx/box/4.png");

//                asia1 = vcast <Ptr <C::SimpleController> > (container->getBean ("box1"));
//                asia2 = vcast <Ptr <C::SimpleController> > (container->getBean ("box2"));
//                asia3 = vcast <Ptr <C::SimpleController> > (container->getBean ("box3"));
//                asia4 = vcast <Ptr <C::SimpleController> > (container->getBean ("box4"));


//                table = Util::WidgetFactory::createTable (2, 2);
                table = vcast <Ptr <C::Table> > (container->getBean ("table"));
//                Ptr <M::Item> tableM = dynamic_pointer_cast <M::Item> (table->getModel ());
//                tableM->translate (Model::Point (-320, -70));

//                C::ControllerList list;
//                list.add (asia1);
//                list.add (asia2);
//                list.add (asia3);
//                list.add (asia4);
//                table->setChildren (list);

//                table->addChild (asia1);
//                table->addChild (asia2);
//                table->addChild (asia3);
//                table->addChild (asia4);

//                table->init ();

                sdlDispatcher = Ptr <Sdl::EventDispatcher> (new Sdl::EventDispatcher ());
                mouseButtonDispatcher = Ptr <Events::MouseButtonDispatcher> (new Events::MouseButtonDispatcher ());
                mouseMotionDispatcher = Ptr <Events::MouseMotionDispatcher> (new Events::MouseMotionDispatcher ());
                mouseMotionScreenMargin = Ptr <Events::MouseMotionDispatcher> (new Events::MouseMotionDispatcher ());
                timeDispatcher = Ptr <Sdl::TimerDispatcher> (new Sdl::TimerDispatcher ());

                fluidCtr = DemoFactory::createFluid ();

        //        screen = dynamic_pointer_cast <M::Primitive> (screenCtr->getModel ());
                fluid = dynamic_pointer_cast <M::PointSet> (fluidCtr->getModel ());
                image01 = dynamic_pointer_cast <M::Item> (image01Ctr->getModel ());
                sniezynka = dynamic_pointer_cast <M::Item> (sniezynkaCtr->getModel ());
//                background = dynamic_pointer_cast <M::Item> (backgroundCtr->getModel ());

        /*--------------------------------------------------------------------------*/

                fluid->setColor (Model::Color::fromInt (65, 105, 225));
                fluid->setPoints (psys.getPoints ());

                fluid->translate (Model::Point (0.0, -200.0));
//                background->translate (Model::Point (-512.0, -512.0));

                sniezynka->setTranslatePoint (Model::Point (-100, 120));
                sniezynka->setCenter (Model::Point (0, 0));

                Ptr <Controller::StepSequence <double> > seq (new Controller::StepSequence <double> ());
                seq->setInitial (0.0);
                seq->setStep (2);
                seq->setStepNumber (180);

                Ptr <Controller::RotationMapping> rot (new Controller::RotationMapping ());
                rot->setModel (sniezynka);
                rot->setSequence (seq);
                sniezynkaCtr->setMapping (rot);

                Ptr <Controller::StepSequence <Model::Point> > seqMove (new Controller::StepSequence <Model::Point> ());
                seqMove->setInitial (Model::Point (-50, 250));
                seqMove->setStep (Model::Point (0.25, -1.75));
                seqMove->setStepNumber (400);

                Ptr <Controller::TranslationMapping> mov (new Controller::TranslationMapping ());
                mov->setModel (sniezynka);
                mov->setSequence (seqMove);
                sniezynkaCtr->movMap = mov;

                screenCtr->addChild (fluidCtr);
                screenCtr->addChild (sniezynkaCtr);
                screenCtr->addChild (backgroundCtr);
                screenCtr->addChild (table);
                screenCtr->addChild (image01Ctr);

//        screen->setFillColor (Model::Color::fromInt (89, 191, 255));

/*##########################################################################*/

        //        sdlDispatcher->Events::AbstractObservable <Events::MouseButtonEvent>::addObserver (mouseButtonDispatcher);
        ////        sdlDispatcher->addMouseMotionObservable (mouseMotionDispatcher);
                sdlDispatcher->Events::AbstractObservable <Events::MouseMotionEvent>::addObserver (mouseMotionScreenMargin);

                // To powinno iść ze screen (screen->getViewPort, albo coś).
                mouseMotionScreenMargin->setArea (Model::Rectangle (1, 1, 638, 478));
                mouseMotionScreenMargin->setMode (Events::MouseMotionDispatcher::OUT);

                timeDispatcher->setTickInterval (15);
                timeDispatcher->addObserver (sniezynkaCtr);

#if defined (TRY_CATCH)
        }
        catch (const Core::Exception &e) {
                std::cerr << e.getMessage () << std::endl;
                exit (1);
        }
        catch (...) {
                std::cerr << "Unknown exception" << std::endl;
                exit (1);
        }
#endif

/*##########################################################################*/

        // Transformacje.
        glViewport (0, 0, (GLsizei) w, (GLsizei) h);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
//        gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 30.0);
        gluOrtho2D (-320, 320, -240, 240);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        GLfloat params[100];
        glGetFloatv (GL_ALIASED_POINT_SIZE_RANGE, params);
        std::cerr << "GL_ALIASED_POINT_SIZE_RANGE : " << params[0] << ", " << params[1] << std::endl;

        glGetFloatv (GL_SMOOTH_POINT_SIZE_RANGE, params);
        std::cerr << "GL_SMOOTH_POINT_SIZE_RANGE : " << params[0] << ", " << params[1] << std::endl;

        glGetFloatv (GL_SMOOTH_POINT_SIZE_GRANULARITY, params);
        std::cerr << "GL_SMOOTH_POINT_SIZE_GRANULARITY : " << params[0] << ", " << params[1] << std::endl;

        glDisable (GL_POINT_SMOOTH);
        std::cerr << "is enabled GL_POINT_SMOOTH : " << ((glIsEnabled (GL_POINT_SMOOTH)) ? ("true") : ("false")) << std::endl;

        glPointSize (3);
        glGetFloatv (GL_POINT_SIZE, params);
        std::cerr << "GL_POINT_SIZE : " << params[0] << std::endl;

}

/****************************************************************************/

/* The main drawing function. */
void DrawGLScene ()
{

/*------ciecz---------------------------------------------------------------*/

        // 1. Do simulation!
//        psys.Run ();

        // Do wywalenia kiedyś.
        fluid->setPoints (psys.getPoints ());
        image01->setTranslatePoint (Model::Point (mouseX - 320, 240 - mouseY));

        screenCtr->draw ();

/*--------------------------------------------------------------------------*/

        frameCnt++;
        // Tak śmiga, że damy delay
        SDL_Delay (5);
}

/**
 *
 */
int main (int argc, char **argv)
{

        int done;

        /* Initialize SDL for video output */
        if (SDL_Init (SDL_INIT_VIDEO) < 0) {
                fprintf (stderr, "Unable to initialize SDL: %s\n", SDL_GetError ());
                exit (1);
        }

        bool fullscreen = (argc > 1);
        int flags;
        if (fullscreen) {
            flags = SDL_OPENGL | SDL_FULLSCREEN;
            SDL_GL_SetAttribute(SDL_GL_RED_SIZE,   8);
            SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
            SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,  8);
            SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,  8);
            SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
        }
        else {
                flags = SDL_OPENGL;
        }

        /* Create a 640x480 OpenGL screen */
        if (SDL_SetVideoMode (640, 480, 0, flags) == NULL) {
                fprintf (stderr, "Unable to create OpenGL screen: %s\n", SDL_GetError ());
                SDL_Quit ();
                exit (2);
        }

        /* Set the title bar in environments that support it */
        SDL_WM_SetCaption ("test", NULL);

        /* Loop, drawing and checking events */
        InitGL (640, 480);
//        makeCheckImage();
//        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        done = 0;

        OpenGL::GLUtil::init ();

        while (!done) {

                timeDispatcher->run ();

                SDL_Event event;

                while (SDL_PollEvent (&event)) {

                        sdlDispatcher->run (&event);


                        if (event.type == SDL_QUIT) {
                                done = 1;
                        }
                        if (event.type == SDL_KEYDOWN) {
                                if (event.key.keysym.sym == SDLK_ESCAPE) {
                                        done = 1;
                                }
                        }

                        if (event.type == SDL_MOUSEMOTION) {
                                //std::cerr << event.motion.x << " " << event.motion.y << std::endl;
                                mouseX = event.motion.x;
                                mouseY = event.motion.y;
                        }

                        if (event.type == SDL_MOUSEBUTTONDOWN) {
                                static bool b = false;
                                b = !b;

                                if (b) {
                                }
                                else {
                                }
                        }

                }

                DrawGLScene ();
        }

/****************************************************************************/

        std::cerr << "number of frames : " << frameCnt << std::endl;
        std::cerr << "gl version : " << glGetString(GL_VERSION) << std::endl;

        int i;
        glGetIntegerv (GL_MAX_TEXTURE_SIZE, &i);
        std::cerr << "max texture size : " << i << std::endl;


/****************************************************************************/

        SDL_Quit ();
        return 0;
}
