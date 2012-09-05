/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_IPOINTARRAY_H_
#define BAJKA_IPOINTARRAY_H_
#include "VertexBuffer.h"

namespace Model {

/**
 * Klasa modeli, które można przedstawić jako tablica punktów. Będą to różnego rodzaju
 * łamane linie, odcinki, prostokąty, trójkąty, etc. Dane zwrócone przez getPointArray
 * nadają się do użcia bezpośrednio w OpenGL.
 */
class IVertexBufferEnabled {
public:
        virtual ~IVertexBufferEnabled() {}
        virtual VertexBuffer getVertexBuffer () const = 0;
};

} /* namespace Model */
#endif /* IPOINTARRAY_H_ */
