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

        /// Wywouje doDraw, jeśli tylko visible jest true.
        void draw ();

        /**
         * Sprawdza visible == true i jeśli tak, to dokonuje transformacji na
         * macierzy openGL.
         */
        virtual void preDraw ();

        /**
         * Sprawdza visible == true i jeśli tak, to zdejmuje transformacje na
         * macierzy Open GL i przed tem wykonuje draw dla Dzieci tego widgeta,
         * ale tylko dla tych, które są bezpośredniododane do niego, a nie tych,
         * do których ma dostęp za pośrednictwem kontrolera.
         */
        virtual void postDraw ();

        virtual bool getVisible () const { return visible; }
        _m (setVisible) virtual void setVisible (bool v) { visible = v; }

private:

        bool visible;

        _m (setModel)
        _m (getModel)
        _m (setChildren)
        _e (AbstractWidget)
};

}

#	endif /* ABSTRACTWIDGET_H_ */
