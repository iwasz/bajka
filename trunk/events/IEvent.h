/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  Date : Nov 18, 2009                                                     *
 *  ~~~~~~                                                                  *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef IEVENT_H_
#define IEVENT_H_

#include <Pointer.h>
#include <List.h>
#include <Foreach.h>

namespace Events {

struct IEvent {
        virtual ~IEvent () {}
};

template <typename Event>
struct IObserver;

/**
 *
 */
template <typename Event>
struct IObservable {

        virtual ~IObservable () {}

        virtual void addObserver (Ptr <IObserver <Event> > observer) = 0;
        virtual void notifyObservers (const Event &event) = 0;
};

//typedef Core::List <Ptr <IObservable> > ObservableList;

/**
 *
 */
template <typename Event>
struct IObserver {

        virtual ~IObserver () {}
        virtual void update (const IObservable <Event> &observable, const Event &event) = 0;

};

//typedef Core::List <Ptr <IObserver> > ObserverList;

/**
 * Convenience implementation of IObservable. Implements IObserver
 * management (add, count), and emission.
 */
template <typename Event>
class AbstractObservable : public IObservable <Event> {
public:

        virtual ~AbstractObservable () {}

        virtual void addObserver (Ptr <IObserver <Event> > observer) { observers.add (observer); }
        virtual void notifyObservers (const Event &event);

protected:

        AbstractObservable () {}

private:

        typedef Core::List <Ptr <IObserver <Event> > > ObserverList;
        ObserverList observers;
};

template <typename Event>
void AbstractObservable <Event>::notifyObservers (const Event &event)
{
        foreach (Ptr <IObserver <Event> > observer, observers) {
                observer->update (*this, event);
        }
}

} // nam

#	endif /* IEVENT_H_ */
