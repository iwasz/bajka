///****************************************************************************
// *                                                                          *
// *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
// *  ~~~~~~~~                                                                *
// *  License : see COPYING file for details.                                 *
// *  ~~~~~~~~~                                                               *
// ****************************************************************************/
//
//#include <iostream>
//#include <cmath>
//#include <ctime>
//#include <cstring>
//#include <cstdlib>
//#include <cstdio>
//#include <boost/bind.hpp>
//#include <cstdlib>
//#include <SDL.h>
//#include <Platform.h>
////#include <util/AbstractShellImpl.h>
//#include <util/ReflectionMacros.h>
//#include <util/Exceptions.h>
//#include <view/freetype/Freetype.h>
//#include "GraphicsService.h"
//#include "Shell.h"
//#include "EventDispatcher.h"
//
//namespace M = Model;
//namespace V = View;
//namespace C = Controller;
//namespace E = Event;
//namespace U = Util;
//
///****************************************************************************/
//
//struct Shell::Impl {
//        EventDispatcher dispatcher;
//};
//
///****************************************************************************/
//
//Shell Shell::instance_;
//
//Util::IShell *shell () { return &Shell::instance_; }
//Util::Config *config () { return shell ()->getConfig (); }
//View::GLContext *glContext () { return shell ()->getGLContext (); }
//
//Shell::Shell () : myimpl (new Impl) {}
//Shell::~Shell () { delete myimpl; }
//
///****************************************************************************/
//
//void Shell::dispatchEvents ()
//{
//        myimpl->dispatcher.pollAndDispatch (impl->model, impl->eventIndex, &impl->pointerInsideIndex, getGLContext ());
//}
//
///****************************************************************************/
//
//void Shell::init ()
//{
//	// TODO - to musi być na początku init dependent
//        //impl->glContext.init (impl->config);
//
//}
//
///****************************************************************************/
//
//void Shell::destroy ()
//{
//        AbstractShell::destroy ();
//        freeSdl ();
//}
//
///****************************************************************************/
//
//void Shell::reset ()
//{
//        AbstractShell::reset ();
//        myimpl->dispatcher.reset ();
//}
//
//
