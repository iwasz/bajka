/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <Foreach.h>
#include "SimpleController.h"

namespace Controller {
using namespace Geometry;

/****************************************************************************/

void SimpleControllerContext::pushMatrix (const AffineMatrix &m)
{
        if (stack.empty ()) {
                stack.push (m);
        }
        else {
                AffineMatrix &t = stack.top ();
                stack.push (boost::numeric::ublas::prod (t, m));
        }
}

/****************************************************************************/

void SimpleControllerContext::popMatrix ()
{
        if (!stack.empty ()) {
             stack.pop ();
        }
}

/****************************************************************************/

const AffineMatrix &SimpleControllerContext::topMaptrix () const
{
        if (!stack.empty ()) {
             return stack.top ();
        }

        throw Core::UnsupportedOperationException ("Stack empty.");
}

/*##########################################################################*/

void SimpleController::init ()
{
        if (widget) {
                widget->init ();
        }

        std::cerr << "this = " << this << std::endl;
}

/****************************************************************************/

void SimpleController::draw ()
{
        // If render is set to false, we skip drawing this Widget.
        if (!getRender ()) {
                return;
        }

        if (widget) {
                widget->preDraw ();
                widget->draw ();
        }

        doChildren ();

        if (widget) {
                widget->postDraw ();
        }
}

/****************************************************************************/

void SimpleController::doChildren ()
{
        foreach (Ptr <IController> child, children) {
                child->draw ();
        }
}

/****************************************************************************/

bool SimpleController::onEvent (Event::IEvent *event)
{
        // Uwaga, inny kontekst spowoduje wywalenie się programu.
        SimpleControllerContext *ctx = static_cast <SimpleControllerContext *> (event->getContext ());
        bool deleteContext = false;

        if (!ctx) {
                ctx = new SimpleControllerContext;
                event->setContext (ctx);
                deleteContext = true;
        }

        /*
         * Jeśli event nie jest obsługiwany, to nawet nie zostanie
         * przekazany dalej do potomków.
         */
        if (!acceptEvent (event)) {
                if (deleteContext) {
                        delete ctx;
                        event->setContext (NULL);
                }

                return true;
        }

        if (getModel ()) {
                // Przemnóż aktualną macierz w kontekście przez tą z aktualnie rozpatrywanego kontrolera.
                ctx->pushMatrix (getModel ()->getMatrix ());
        }

        // Uruchom własciwą metodę obsługi.
        event->runObserver (this);

        // Wywołania dla dzieci.
        foreach (Ptr <IController> ctr, children) {
                // TODO Zastanowić się jak to zrobić bez dynamic_cast!!!
                Event::AbstractObserver *a = dynamic_cast <Event::AbstractObserver *> (ctr.get ());

                if (!a->onEvent (event)) {
                        return false;
                }
        }

        // Usuń kontekst - tylko raz per event.
        if (deleteContext) {
                delete ctx;
                event->setContext (NULL);
        }

        return true;
}

/****************************************************************************/

bool SimpleController::onMouseMotion (Event::MouseMotionEvent *e)
{
        if (!getModel ()) {
                return false;
        }

        Geometry::Point p = e->getPosition();
        SimpleControllerContext *ctx = static_cast <SimpleControllerContext *> (e->getContext ());
        const AffineMatrix &matrix = ctx->topMaptrix ();
        // Przetransformuj p przez matrix.
        p = matrix.transform (p);

        if (getModel ()->enclose (p)) {
                std::cerr << "SimpleController::onMouseMotion : " << e->getPosition() << ", this=" << this << ", affine = " << matrix.toString () << std::endl;
                // std::cerr << matrix(0,3) << ", " << matrix(1,3) << std::endl;
        }

        return true;
}

/****************************************************************************/

bool SimpleController::onTimer (Event::TimerEvent *e)
{
        std::cerr << "SimpleController::onTimer : " << e->getTicks () << ", this=" << this << std::endl;
        return true;
}

}
