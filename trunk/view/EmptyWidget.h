/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef EMPTYWIDGET_H_
#define EMPTYWIDGET_H_

namespace View {

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

#	endif /* EMPTYWIDGET_H_ */
