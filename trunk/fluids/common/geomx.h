/*
FLUIDS v.1 - SPH Fluid Simulator for CPU and GPU
Copyright (C) 2008. Rama Hoetzlein, http://www.rchoetzlein.com

ZLib license
This software is provided 'as-is', without any express or implied
warranty.  In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
claim that you wrote the original software. If you use this software
in a product, an acknowledgment in the product documentation would be
appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

#ifndef DEF_GEOM
#define DEF_GEOM

#include <vector>
#include <string>
#include "Point.h"

#define	ELEM_MAX			2147483640	// largest number of elements in a buffer (range of hval)
//#define ELEM_MAX			32768		// largest number of elements in a buffer (range of hval)
#define BUF_UNDEF			255
#define FPOS				2			// free position offsets

typedef unsigned char uchar;
typedef unsigned short ushort;
/// values in heap
typedef signed int hval;
/// values are typically references
typedef hval href;

class GeomAttr {
public:
        GeomAttr()	{ name = ""; buf = 0; stride = 0; offset = 0; }
        std::string	name;
        ushort		buf;
        ushort		stride;
        ushort		offset;
};

class GeomBuf {
public:
        GeomBuf()	{ dtype = 0; num = 0; max = 0; stride = 0; data = 0x0; }

        uchar		dtype;
        hval		num;
        hval		max;
        long		size;
        ushort		stride;

        // To bynajmniej nie są napisy, tylko obszar pamięci zawierający Point'y
        char*		data;
};

/**
 * Z tego co widze, to jest klasa, która bardzo nieudolnie implementuje model.
 * Bufory zawierają, punkty, cząstki, płyny, a następnie w podklasach ten model
 * jest konwertowany na wektor, na którym już są wykonywane algorytmy numeryczne.
 *
 * Czyli na tym poziomie operujemy na obiektach, które mają pozycję w przestrzeni
 * i ich atrubutach. Samej przestrzeni tu jeszcze chyba nie ma.
 */
class GeomX {
public:

        GeomX () : points (new Geometry::PointList) {}

        // Basic geometry setup

        /**
         * To poprostu zwalnia pamięć z mBuf (i usuwa elementy), oraz z mHeap.
         */
        void FreeBuffers ();

        /**
         * To powinna być metoda bufora GeomBuf. Resetuje go (zwalnia i przydziela znów pamięć).
         * @param b numer bufora
         * @param n
         */
        void ResetBuffer ( uchar b, int n );

        /**
         * Dodaje 1 nowy element do mBuf. To powinien być konstruktor GeomBuf,
         * bo robi dokładnie to co konstruktor + push_back.
         */
        int AddBuffer ( uchar typ, ushort stride, int max );
        int AddAttribute ( uchar b, std::string name, ushort stride );
        int AddAttribute ( uchar b, std::string name, ushort stride, bool bExtend );
        int GetAttribute ( std::string name );
        int GetAttrOffset ( std::string name );

        int NumElem ( uchar b )const				{ if ( b==BUF_UNDEF) return 0; else return mBuf[b].num; }
        int MaxElem ( uchar b )				{ if ( b==BUF_UNDEF) return 0; else return mBuf[b].max; }
        int GetStride ( uchar b )			{ return mBuf[b].stride; }
        char* GetElem ( uchar b, int n )	{ return mBuf[b].data + n*mBuf[b].stride; }
        char* RandomElem ( uchar b, href& ndx );
        char* AddElem ( uchar b, href& pos );
        int AddElem ( uchar b, char* data );
        bool DelElem ( uchar b, int n );
        char* GetStart ( uchar b )			{ return mBuf[b].data; }
        char* GetEnd ( uchar b )			{ return mBuf[b].data + mBuf[b].num*mBuf[b].stride; }
        GeomBuf* GetBuffer ( uchar b )		{ return &mBuf[b]; }
        GeomAttr* GetAttribute ( int n )		{ return &mAttribute[n]; }
        int GetNumBuf ()					{ return (int) mBuf.size(); }
        int GetNumAttr ()					{ return (int) mAttribute.size(); }

        std::vector<GeomBuf> &getMBuff () { return mBuf; }

//        Ptr <Model::PointList> getPoints () const { return points; }
//        void setPoints (Ptr <Model::PointList> p) { points = p; }

protected:

        /**
         * To jest wektor buforów, czyli takich (GeomBuf::data jest typu Point *) chyba
         * jakby elementów w symulacji. Te bufory mogą odzwierciedlać punkt, cząsteczkę
         * lub płyn.
         *
         * Czyli to jest model.
         */
        std::vector<GeomBuf> mBuf;
        // Dublujemy to co w mBuf
        Ptr <Model::PointList> points;

        /**
         * Atrybuty (o nazwach typu string) dotyczące buforów z wektora mBuf. Każdy
         * taki bufor (element) może mieć atrybuty jak kolor, prędkość etc.
         */
        std::vector<GeomAttr> mAttribute;

};

#endif
