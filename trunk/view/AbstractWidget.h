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
#include "tree/TreeMasterSlave.h"

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
class AbstractWidget :
        public IWidget,
        public Util::TreeMasterSlave <View::IWidget> {
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

/*------Zawieranie----------------------------------------------------------*/

        _m (setChildren)
        void setChildren (WidgetList const &list);

        void addChild (ChildType e);
        void removeChild (ChildType e);
        void clearChildren ();

/*--------------------------------------------------------------------------*/

        _m (setModel) virtual void setModel (Ptr <Model::IModel> model);
        _m (getModel) virtual Ptr <Model::IModel> getModel () { return model; }

protected:

        void setParent (ParentType e);

private:

        Ptr <Model::IModel> model;
        bool visible;

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
