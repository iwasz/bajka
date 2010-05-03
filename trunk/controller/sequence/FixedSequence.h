///****************************************************************************
// *                                                                          *
// *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
// *  ~~~~~~~~                                                                *
// *  Date : Nov 22, 2009                                                     *
// *  ~~~~~~                                                                  *
// *  License : see COPYING file for details.                                 *
// *  ~~~~~~~~~                                                               *
// ****************************************************************************/
//
//#ifndef FIXEDSEQUENCE_H_
//#define FIXEDSEQUENCE_H_
//
//#include <List.h>
//#include "ISequence.h"
//
//namespace Controller {
//
///**
// * TODO, może z tego szablon zrobić? Ale co wtedy z konteterem IoC?
// */
//class FixedSequence : public ISequence <double> {
//public:
//
//        FixedSequence (const Core::List <double> &l) : list (l), current (l.begin ()) {}
//        virtual ~FixedSequence ();
//
//        bool hasNext () const { return list.size (); }
//        double next () const;
//
//private:
//
//        Core::List <double> list;
//        mutable Core::List <double>::const_iterator current;
//
//};
//
//}
//
//#	endif /* FIXEDSEQUENCE_H_ */
