/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <Foreach.h>

#include "SimpleController.h"
//#include "geometry/Utils.h"
#include "IModel.h"
#include "IWidget.h"

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

bool SimpleController::ObserverHelper::checkArea (Event::MouseEvent *e)
{
        if (!myModel) {
                return false;
        }

        Geometry::Point p = e->getPosition();
//        SimpleControllerContext *ctx = static_cast <SimpleControllerContext *> (e->getContext ());
//        AffineMatrix matrix = ctx->topMaptrix ();
//        matrix.inverse ();
//        matrix.transform (&p);

        Point p2 = myModel->screenToModel (p);
//        std::cerr << "---> [" << p2 << "], enclose [" << myModel->enclose (p2) << "]" << std::endl;

//        if (myModel->enclose (p)) {
        if (myModel->enclose (p2)) {
                return true;
        }

        return false;
}

bool SimpleController::ObserverHelper::onButtonPress (Event::ButtonPressEvent *e)
{
        if (checkArea (e)) {
                return myController->onButtonPress (e);
        }

        return false;
}

bool SimpleController::ObserverHelper::onButtonRelease (Event::ButtonReleaseEvent *e)
{
        if (checkArea (e)) {
                return myController->onButtonRelease (e);
        }

        return false;
}

bool SimpleController::ObserverHelper::onMouseMotion (Event::MouseMotionEvent *e)
{
        if (checkArea (e)) {
                //std::cerr << "SimpleController::onMouseMotion : " << e->getPosition() << ", this=" << this << std::endl;
                //std::cerr << m(0,0) << ", " << m(0,3) << ", " << m(1,3) << ", " << std::endl;

                if (!pointerInside) {
                        pointerInside = true;
                        myController->onMouseOver (e);
                }

                return myController->onMouseMotion (e);
        }
        else {
                if (pointerInside) {
                        pointerInside = false;
                        myController->onMouseOut (e);
                }
        }

        return false;
}

bool SimpleController::ObserverHelper::onKeyDown (Event::KeyDownEvent *e)
{
        return myController->onKeyDown (e);
}

bool SimpleController::ObserverHelper::onKeyUp (Event::KeyUpEvent *e)
{
        return myController->onKeyUp (e);
}

bool SimpleController::ObserverHelper::onTimer (Event::TimerEvent *e)
{
        return myController->onTimer (e);
}

bool SimpleController::ObserverHelper::onQuit (Event::QuitEvent *e)
{
        return myController->onQuit (e);
}

/*##########################################################################*/

void SimpleController::init ()
{
        if (widget) {
                widget->init ();
        }

//        std::cerr << "this = " << this << std::endl;
}

/****************************************************************************/

void SimpleController::setChildren (const ControllerList &list)
{
        for (ControllerList::const_iterator i = list.begin (); i !=list.end (); ++i) {
                addChild (*i);
        }
}

/****************************************************************************/

void SimpleController::setModel (Ptr<Model::IModel> model)
{
        this->model = model;
        myHelper.myModel = model.get ();
        model->setTreeMaster (this);
}

/****************************************************************************/

/**
 * \todo To są szczegóły implementacji widgeta, które są w kontrolerze. Czyli się
 * trochę pomieszało. Teraz, kiedy jest TreeSlave/TreeMaster, możnaby tą metdoę
 * przenieść do widgeta i jako publiczną zrobić tylko draw, a post i pre jako protected.
 * Dzięki temu
 * 1. Implementacj będzie ukryta.
 * 2. Kontroler będzie wołać tylko draw i będzie łątwiej go przedefiniować w podklasach.
 */
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
        for (SimpleController::iterator i = begin (); i != end (); ++i) {
                (*i)->draw ();
        }
}

/**
 * Pierwsza metoda reagująca na event.
 * - Jeśli w evencie nie ma kontekstu (zamienna pomocnicza, z danymi dzielonymi
 * przez EventObservery), to jest on tworzony i dodawany do eventu.
 * -
 */
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

        /*
         * Uruchom własciwą metodę obsługi, ale nie bezpośrednio, tylko
         * najpierw przepuść event przez obiekt ObserverHelper, który
         * zdecyduje, czy procesować ten event, czy nie.
         *
         * TODO a czy tu nie powinien być sprawdzony wynik i ewentualnie,
         * jeśli nie jesteśmy w obszarze, to powinniśmy nie wywoływać dzieci?
         */
        event->runObserver (&myHelper);

        // Wywołania dla dzieci.
        for (SimpleController::iterator i = begin (); i != end (); ++i) {
                // TODO Zastanowić się jak to zrobić bez dynamic_cast!!!
                Event::AbstractObserver *a = dynamic_cast <Event::AbstractObserver *> (i->get ());

                if (!a->onEvent (event)) {
                        return false;
                }
        }

        if (getModel ()) {
                ctx->popMatrix ();
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
//        std::cerr << "SimpleController::onMouseMotion : " << e->getPosition () << ", this=[" << this << "]" << std::endl;
        return true;
}

/****************************************************************************/

//bool SimpleController::onTimer (Event::TimerEvent *e)
//{
//        std::cerr << "SimpleController::onTimer : " << e->getTicks () << ", this=[" << this << "]" << std::endl;
//        return true;
//}

/****************************************************************************/

bool SimpleController::onMouseOver (Event::MouseMotionEvent *e)
{
//        std::cerr << "SimpleController::onMouse-OVER : " << e->getPosition() << ", this=[" << this << "]" << std::endl;
        return true;
}

/****************************************************************************/

bool SimpleController::onMouseOut (Event::MouseMotionEvent *e)
{
//        std::cerr << "SimpleController::onMouse-OUT : " << e->getPosition() << ", this=[" << this << "]" << std::endl;
        return true;
}

}
