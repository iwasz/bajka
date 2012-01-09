/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_ABSTRACTMODEL_H_
#define BAJKA_ABSTRACTMODEL_H_

#include "IModel.h"

namespace Model {

class AbstractModel : public IModel {
public:

        AbstractModel () : parent (0), view (0), controller (0) {}
        virtual ~AbstractModel () {}

        virtual bool update ();

/*--------------------------------------------------------------------------*/

        IModel *getParent () { return parent; }
        void setParent (IModel *m) { parent = m; }
        void parentCallback (IModel *m) {}

        ModelVector &getChildren () { return children; }
        // Todo pętla setParent
        void setChildren (ModelVector const &c) { children = c; }
        void addChild (IModel *m) { children.push_back (m); m->setParent (this); m->parentCallback (this); }
        ModelVector::iterator begin () { return children.begin (); }
        ModelVector::iterator end () { return children.end (); }

/*--------------------------------------------------------------------------*/

        View::IView *getView () { return view; }
        void setView (View::IView *v) { view = v; }

        Controller::IController *getController () { return controller; }
        void setController (Controller::IController *c) { controller = c; }

private:

        IModel *parent;
        ModelVector children;
        View::IView *view;
        Controller::IController *controller;

};

} /* namespace Model1 */

#	endif /* ABSTRACTMODEL_H_ */
