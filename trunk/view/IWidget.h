/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  Date : Nov 22, 2009                                                     *
 *  ~~~~~~                                                                  *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef IWIDGET_H_
#define IWIDGET_H_

#include <List.h>
#include <Vector.h>

#include "IView.h"

namespace View {

class IWidget;
typedef Core::List <Ptr <IWidget> > WidgetList;
typedef Core::Vector <Ptr <IWidget> > WidgetVector;

/**
 * TODO Chyba już niepotrzebne, wystarczy sam IView.
 */
struct IWidget : public IView {

        virtual ~IWidget () {}

//        virtual void setCenter (const Model::Point &p) = 0;
//        virtual const Model::Point &getCenter () const = 0;
//
///*------Transformations-----------------------------------------------------*/
//
//        // Relative
//        virtual void translate (const Model::Point &p) = 0;
//        virtual void rotate (double r) = 0;
//        virtual void scale (double w, double h) = 0;
//
//        // Absolute
//        virtual void setTranslation (const Model::Point &p) = 0;
//        virtual void setRotation (double r) = 0;
//        virtual void setScale (double w, double h) = 0;



        /**
         * Inits this Widget. You must reimplemet this method if you want
         * your View to be statefull, and perform dynamic_pointer_cast to
         * your preffered model concrete type. Also ypu should call init
         * from parent class.
         */
        virtual void setModel (Ptr <Model::IModel> model) = 0;
        virtual Ptr <Model::IModel> getModel () const = 0;
};

}

#	endif /* IWIDGET_H_ */
