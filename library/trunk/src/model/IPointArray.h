/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_IPOINTARRAY_H_
#define BAJKA_IPOINTARRAY_H_

namespace Model {

/**
 * Klasa modeli, które można przedstawić jako tablica punktów. Będą to różnego rodzaju
 * łamane linie, odcinki, prostokąty, trójkąty, etc. Dane zwrócone przez getPointArray
 * nadają się do użcia bezpośrednio w OpenGL.
 */
class IPointArray {
public:
        virtual ~IPointArray() {}

        virtual void *getPointArray () const = 0;
        virtual size_t getNumberOfPoints () const = 0;
};

} /* namespace Model */
#endif /* IPOINTARRAY_H_ */
