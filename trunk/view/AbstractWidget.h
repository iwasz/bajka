/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ABSTRACTWIDGET_H_
#define ABSTRACTWIDGET_H_

#include "TreeWidget.h"

namespace View {

/**
 * Convenience class.
 * Every widget is also a "container" for other widgets. It simply
 * means that transformations aplied to the prent will be also
 * applied to its children (for example translating the parent
 * means also to translate the children).
 *
 * Oczywiście zawieranie nie jest zaimplementowane w warstwie widoku, tylko w warstwie kontrolera.
 * \ingroup View
 */
class AbstractWidget : public TreeWidget {
public:
        __d

        AbstractWidget () : visible (true) {}
        virtual ~AbstractWidget () {}

        // Domyślnie nic się tu nie dzieje.
        virtual void init ();

/*------Rysowanie-----------------------------------------------------------*/

        void draw ();

        virtual void preDraw ();
        virtual void postDraw ();

        virtual void doTransform ();
        virtual void doChildren ();
        virtual void doDraw () = 0;

        virtual bool getVisible () const { return visible; }
        _m (setVisible) virtual void setVisible (bool v) { visible = v; }

private:

        Ptr <Model::IModel> model;
        bool visible;

        _m (setModel)
        _m (getModel)
        _m (setChildren)
        _e (AbstractWidget)
};

/**
 * Nic nie rysuje (potrzebne w kontrolerze
 * do transformacji na wszystkich dzieciach).
 * \ingroup View
 */
class EmptyWidget : public AbstractWidget {
public:
        __c (void)
        _b ("AbstractWidget")
        virtual ~EmptyWidget () {}
        void doDraw () {}
        _e (EmptyWidget)
};

}

#	endif /* ABSTRACTWIDGET_H_ */
