/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  Date : Nov 21, 2009                                                     *
 *  ~~~~~~                                                                  *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef VIEW_H_
#define VIEW_H_

/**
 * \defgroup View
 * Widok, czyli V w MVC. Klasy związane z widokami. Implementują samo rysowanie jakichś konkretnych
 * rzeczy. Mogą to być kształty, figury etc, ale mogą też być jakieś sekwencje animacji, przejścia, efekty.
 */

#include "Circle.h"
#include "Image.h"
#include "IView.h"
#include "Primitive.h"
#include "Rectangle.h"
#include "Text.h"
#include "View.h"
#include "Widget.h"
#include "draw/Draw.h"
#include "ClearScreen.h"
#include "ClearScreenGrid.h"
#include "LoopImage.h"
#include "resource/Resource.h"
#include "openGl/OpenGl.h"

#	endif /* VIEW_H_ */
