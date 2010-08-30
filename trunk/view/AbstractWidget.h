/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ABSTRACTWIDGET_H_
#define ABSTRACTWIDGET_H_

#include "IWidget.h"
#include "IModel.h"

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
class AbstractWidget : public IWidget {
public:
        __d

        AbstractWidget () : visible (true) {}
        virtual ~AbstractWidget () {}

        _m (setModel) virtual void setModel (Ptr <Model::IModel> model) { this->model = model; }
        _m (getModel) virtual Ptr <Model::IModel> getModel () const { return model; }

        virtual bool getVisible () const { return visible; }
        _m (setVisible) virtual void setVisible (bool v) { visible = v; }

        // Domyślnie nic się tu nie dzieje.
        virtual void init () {}

        void draw ()
        {
                if (visible) {
                        doTransform ();
                        doDraw ();
                }
        }

        virtual void preDraw ();
        virtual void postDraw ();

        virtual void doTransform ();
        virtual void doDraw () = 0;

protected:

        Ptr <Model::IModel> model;
        bool visible;

        _e (AbstractWidget)
};

/**
 * Nic nie rysuje (potrzebne w kontrolerze
 * do transformacji na wszystkich dzieciach).
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
