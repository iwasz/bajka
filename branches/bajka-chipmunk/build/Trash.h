/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  Date : Nov 17, 2009                                                     *
 *  ~~~~~~                                                                  *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef TRASH_H_
#define TRASH_H_
#if 0

struct IWidgetContainer {

        virtual ~IWidgetContainer () {}

        virtual Ptr <WidgetList> getChildren () const = 0;
        virtual void setChildren (Ptr <WidgetList> list) const = 0;
        virtual void addChildren (Ptr <WidgetList> list) const = 0;
        virtual void addChild (Ptr <IWidget> widget) const = 0;

};

/**
 * Multiple children
 */
class AbstractWidgetContainer : public IWidgetContainer {
public :

        virtual ~AbstractWidgetContainer () {}

        virtual Ptr <WidgetList> getChildren () const { return children; }
        virtual void setChildren (Ptr <WidgetList> list) { children = list; }
        virtual void addChildren (Ptr <WidgetList> list) { children->addAll (*list); }
        virtual void addChild (Ptr <IWidget> widget) { children->add (widget); }

protected:

        AbstractWidgetContainer () {}

private:

        Ptr <WidgetList> children;

};

/**
 * Only one child.
 */
class AbstractWidgetBin : public AbstractWidgetContainer {
public:

        virtual ~AbstractWidgetBin () {}

//        Ptr <WidgetList> getChildren () const { return children; }
//        void setChildren (Ptr <WidgetList> list) { children = list; }
//        void addChildren (Ptr <WidgetList> list) { children->addAll (list); }
//        void addChild (Ptr <IWidget> widget) { children->add (widget); }

        virtual void setChild (Ptr <IWidget> child) { this->child = child; }
        virtual Ptr <IWidget> getChild () const { return child; }

protected:

        AbstractWidgetBin () {}

private:

        Ptr <IWidget> child;

};

#       endif
#	endif /* TRASH_H_ */
