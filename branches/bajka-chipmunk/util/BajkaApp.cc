/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_opengl.h>

#include <iostream>
#include <cmath>
#include <ctime>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <boost/bind.hpp>

//#include "Image.h"
//#include "Model.h"
//#include "Events.h"
//#include "Util.h"
//#include "OpenGl.h"
//
//#include "sequence/Sequence.h"
//#include "mapping/Mapping.h"
//
////#include "Sdl.h"
//#include "View.h"

#include "BajkaApp.h"
//#include "Controller.h"
//#include "Model.h"

namespace Util {
//namespace M = Model;
//namespace V = View;
//namespace C = Controller;
namespace R = Reflection;
//using namespace Event;


/****************************************************************************/

BajkaConfig::BajkaConfig () : fullScreen (false), resX (640), resY (480), windowCaption ("BajkaApp")
{
}

/****************************************************************************/

void BajkaConfig::init ()
{
#if 1

        /* Initialize SDL for video output */
        if (SDL_Init (SDL_INIT_VIDEO) < 0) {
                fprintf (stderr, "Unable to initialize SDL: %s\n", SDL_GetError ());
                exit (1);
        }

        int flags;
        if (fullScreen) {
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

        /* Create a OpenGL screen */
        if (SDL_SetVideoMode (resX, resY, 0, flags) == NULL) {
                fprintf (stderr, "Unable to create OpenGL screen: %s\n", SDL_GetError ());
                SDL_Quit ();
                exit (2);
        }

        /* Set the title bar in environments that support it */
        SDL_WM_SetCaption (windowCaption.c_str (), NULL);

/*##########################################################################*/

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

        // Transformacje.
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        // gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 30.0);
        gluOrtho2D (-resX/2, resX/2, -resY/2, resY/2);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluOrtho2D (-resX/2, resX/2, -resY/2, resY/2);
//        glViewport (0, 0, (GLsizei) resX, (GLsizei) resY);

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

/*--------------------------------------------------------------------------*/
//
//        glColor3f (0.0, 0.0, 1.0);
//
//        glBegin (GL_LINE_LOOP);
//                glVertex2f (0, 0);
//                glVertex2f (0, 100);
//                glVertex2f (100, 100);
//                glVertex2f (100, 0);
//        glEnd ();
//
//        glClearColor((128.0f / 255.0f), 1.0f, 1.0f, 1.0f);

#endif
#if 0
        if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
            return ;
        }

        SDL_GL_SetAttribute(SDL_GL_RED_SIZE,            8);
        SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,          8);
        SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,           8);
        SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,          8);

        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,          16);
        SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,            32);

        SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE,        8);
        SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE,    8);
        SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE,        8);
        SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE,    8);

        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS,  1);

        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,  2);

        if((/*Surf_Display = */SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_GL_DOUBLEBUFFER | SDL_OPENGL)) == NULL) {
            return;
        }

        glClearColor(0, 0, 0, 0);

        glViewport(0, 0, 640, 480);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        glOrtho(0, 640, 480, 0, 1, -1);

        glMatrixMode(GL_MODELVIEW);

        glEnable(GL_TEXTURE_2D);

        glLoadIdentity();

/*--------------------------------------------------------------------------*/

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();

        glBegin(GL_QUADS);
            glColor3f(1, 0, 0); glVertex3f(0, 0, 0);
            glColor3f(1, 1, 0); glVertex3f(100, 0, 0);
            glColor3f(1, 0, 1); glVertex3f(100, 100, 0);
            glColor3f(1, 1, 1); glVertex3f(0, 100, 0);
        glEnd();


//        glColor3f (0.0, 0.0, 1.0);
//
//        glBegin (GL_LINE_LOOP);
//                glVertex2f (0, 0);
//                glVertex2f (0, 100);
//                glVertex2f (100, 100);
//                glVertex2f (100, 0);
//        glEnd ();

        glClearColor((128.0f / 255.0f), 1.0f, 1.0f, 1.0f);

        SDL_GL_SwapBuffers();

        return;
#endif
}

/*##########################################################################*/

void BajkaApp::loop ()
{
        bool done = false;

        while (!done) {

                glMatrixMode (GL_MODELVIEW);
                glLoadIdentity ();
                glClearColor (0.35, 0.75, 1.0, 1.0);
                glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//                // Generuj eventy.
//                for (Event::DispatcherList::const_iterator i = dispatchers->begin (); i != dispatchers->end (); i++) {
//                        (*i)->run ();
//                }
//
                if (model) {
                        model->update ();
                }

                cpSpaceStep (Model::Space::getSpace (), 1.0 / 60.0);

                afterEvents ();

                glFlush ();
                // swap buffers to display, since we're double buffered.
                SDL_GL_SwapBuffers ();
                // Tak śmiga, że damy delay
                SDL_Delay (5);
        }
}

/****************************************************************************/

void BajkaApp::debug (Core::String const &msg)
{
        std::cerr << "+---------------DEBUG-------[" << msg << "]--------+" << std::endl;
}

/****************************************************************************/

void BajkaApp::destroy ()
{
        std::cerr << "+---------------QUIT----------------+" << std::endl;
        std::cerr << "gl version : " << glGetString(GL_VERSION) << std::endl;

        int i;
        glGetIntegerv (GL_MAX_TEXTURE_SIZE, &i);
        std::cerr << "max texture size : " << i << std::endl;

        SDL_Quit ();
}

/****************************************************************************/

void BajkaApp::setModel (Ptr <Model::IModel> m)
{
        model = m;
//        if (rootController) {
//                disconnect (rootController);
//        }
//
//        rootController = r;
//        connect (r);
}
//
///****************************************************************************/
//
//void BajkaApp::connect (Ptr <IObserver> o)
//{
//        std::for_each (dispatchers->begin (), dispatchers->end (), boost::bind (&IDispatcher::addObserver, _1, o));
//}
//
///****************************************************************************/
//
//void BajkaApp::disconnect (Ptr <IObserver> o)
//{
//        std::for_each (dispatchers->begin (), dispatchers->end (), boost::bind (&IDispatcher::removeObserver, _1, o));
//}

/*##########################################################################*/
} // Nam


//namespace View {
//
//void Widget::preUpdate (Model::IModel *model)
//{
//        if (!visible) {
//                return;
//        }
//
//        glPushMatrix ();
//
//        if (model) {
//                glMultMatrixd (model->getMatrix ());
//        }
//}
//
////void Widget::update (Model::IModel *model)
////{
////
////}
//
//void Widget::postUpdate (Model::IModel *model)
//{
//        if (!visible) {
//                return;
//        }
//
//        glPopMatrix ();
//}
//
//void Rectangle::update (Model::IModel *model)
//{
//        // TODO Do wywalenia.
//        glColor3f (1.0, 0.0, 0.0);
//
//        // TODO Lub dynamic, dio zastanowienia się.
//        // TODO Kastować na ogólniejszy typ.
//        Model::Box *box = static_cast <Model::Box *> (model);
//
//        double x = box->getPosition ().getX ();
//        double y = box->getPosition ().getY ();
//
//        glBegin (GL_LINE_LOOP);
//                glVertex2f (x, y);
//                glVertex2f (x, y + box->getHeight ());
//                glVertex2f (x + box->getHeight (), y + box->getHeight ());
//                glVertex2f (x + box->getHeight (), y);
//        glEnd ();
//}
//
//void Circle::update (Model::IModel *model)
//{
//        // TODO Do wywalenia.
//        glColor3f (0.0, 1.0, 0.0);
//
//        // TODO Lub dynamic, dio zastanowienia się.
//        // TODO Kastować na ogólniejszy typ.
////        Model::CPCircle *box = static_cast <Model::CPCircle *> (model);
//
//        double x = model->getPosition ().getX ();
//        double y = model->getPosition ().getY ();
//
//        glBegin (GL_LINE_LOOP);
//                glVertex2f (x, y);
//                glVertex2f (x, y + 30);
//                glVertex2f (x + 30, y + 30);
//                glVertex2f (x + 30, y);
//        glEnd ();
//}
//
//} // Nam
//
//namespace Model {
//
//bool AbstractModel::update ()
//{
//        if (controller) {
//                controller->preUpdate (this, view);
//                controller->update (this, view);
//        }
//
//        if (view) {
//                view->preUpdate (this);
//                view->update (this);
//        }
//
//        std::for_each (begin (), end (), boost::mem_fn (&IModel::update));
//
//        if (controller) {
//                controller->postUpdate (this, view);
//        }
//
//        if (view) {
//                view->postUpdate (this);
//        }
//}
//
//
//cpSpace *CPSpace::space = NULL;
//
//CPSpace::CPSpace ()
//{
//        assert (!space);
//        space = cpSpaceNew ();
//}
//
//CPSpace::~CPSpace ()
//{
//        cpSpaceFree (space);
//}
//
//Geometry::Vector CPSpace::getGravity () const
//{
//        cpVect g = cpSpaceGetGravity (space);
//        return Geometry::Vector (g.x, g.y);
//}
//
//void CPSpace::setGravity (Geometry::Vector const &g)
//{
//        cpSpaceSetGravity (space, cpv (g.getX (), g.getY ()));
//}
//
//double const *CPSpace::getMatrix () const
//{
//        static Geometry::AffineMatrix one;
//        return one.data ().begin ();
//}
//
///*--------------------------------------------------------------------------*/
//
//CPBody::CPBody ()
//{
//        body = cpSpaceAddBody (CPSpace::getSpace (), cpBodyNew (1, 1));
//}
//
//CPBody::~CPBody ()
//{
//        cpBodyFree (body);
//}
//
//Geometry::Point CPBody::getPosition () const
//{
//        cpVect v = cpBodyGetPos (body);
//        return Geometry::Point (v.x, v.y);
//}
//
//void CPBody::setPosition (Geometry::Point const &p)
//{
//        cpBodySetPos (body, cpv (p.getX (), p.getY ()));
//        cpSpaceReindexShapesForBody (CPSpace::getSpace (), body);
//}
//
//double CPBody::getAngle () const
//{
//        return cpBodyGetAngle (body);
//}
//
//void CPBody::setAngle (double a)
//{
//        cpBodySetAngle (body, a);
//        cpSpaceReindexShapesForBody (CPSpace::getSpace (), body);
//}
//
//double const *CPBody::getMatrix () const
//{
//        // TODO!
//        static Geometry::AffineMatrix one;
//        return one.data ().begin ();
//}
//
//double CPBody::getMass () const
//{
//        return cpBodyGetMass (body);
//}
//
//void CPBody::setMass (double m)
//{
//        cpBodySetMass (body, m);
//}
//
//double CPBody::getInertia () const
//{
//        return cpBodyGetMoment (body);
//}
//
//void CPBody::setInertia (double i)
//{
//        cpBodySetMoment (body, i);
//}
//
//void CPBody::addInertia (double i)
//{
//        double tmp = cpBodyGetMoment (body);
//        cpBodySetMoment (body, i + tmp);
//}
//
///****************************************************************************/
//
//CPShape::~CPShape ()
//{
//        cpShapeFree (shape);
//}
//
//void CPShape::parentCallback (IModel *m)
//{
//        CPModel::parentCallback (m);
//        // TODO można zrobic cast w zalezności od define DEBUG/RELEASE.
//        CPBody *body = static_cast <CPBody *> (m);
//        double inertia = calculateInertia (body->getMass ());
//        body->addInertia (inertia);
//}
//
//double const *CPShape::getMatrix () const
//{
//        // TODO!
//        static Geometry::AffineMatrix one;
//        return one.data ().begin ();
//}
//
///****************************************************************************/
//
//CPCircle::CPCircle ()
//{
//
//}
//
//double CPCircle::calculateInertia (double mass) const
//{
//        return cpMomentForCircle (mass, 0, getRadius (), cpv (getPosition ().getX (), getPosition ().getY ()));
//}
//
//void CPCircle::parentCallback (IModel *m)
//{
//        CPBody *b = static_cast <CPBody *> (m);
//        shape = cpCircleShapeNew (b->getBody (), radius, cpv (position.getX (), position.getY ()));
//        CPShape::parentCallback (m);
//}
//
//double CPCircle::getRadius () const
//{
//        return cpCircleShapeGetRadius (shape);
//}
//
//void CPCircle::setRadius (double r)
//{
//        if (getParent ()) {
//                throw Util::OperationNotSupportedException ();
//        }
//
//        radius = r;
//}
//
//void CPCircle::setPosition (Geometry::Point const &p)
//{
//        if (getParent ()) {
//                throw Util::OperationNotSupportedException ();
//        }
//
//        position = p;
//}
//
//Geometry::Point CPCircle::getPosition () const
//{
//        cpVect v = cpCircleShapeGetOffset (shape);
//        return Geometry::Point (v.x, v.y);
//}
//
//
//}
