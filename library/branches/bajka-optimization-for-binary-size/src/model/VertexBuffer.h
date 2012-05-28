/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef VERTEXBUFFER_H_
#define VERTEXBUFFER_H_

#include <cstddef>

namespace Model {

/**
 * Klasa DTO przechowująca informacje o buforze z punktami. Wykorzystana do
 * zwracania dużych ilości danych z modeli do widoków.
 */
struct VertexBuffer {

        // ? takie typy?
        enum PointType { FLOAT, DOUBLE, SHORT, INT, FIXED };

        VertexBuffer () : buffer (NULL), extraSegment (NULL) {}

        void *buffer;
        PointType pointType;
        size_t numVertices;
        size_t stride;

        void *extraSegment;

};

} /* namespace Model */
#endif /* VERTEXBUFFER_H_ */
