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

#ifndef DEF_POINT_SET
#define DEF_POINT_SET

#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "common_defs.h"
#include "geomx.h"
#include "vector.h"

typedef signed int		xref;

#define MAX_NEIGHBOR		80

#define MAX_PARAM			21

// Scalar params
#define PNT_DRAWMODE		0
        #define PNT_SPHERE			0
        #define PNT_POINT			1
#define PNT_DRAWSIZE		1
#define POINT_GRAV			2
#define PLANE_GRAV			3

// Vector params
#define EMIT_POS			0
#define EMIT_ANG			1
#define EMIT_DANG			2
#define EMIT_SPREAD			3
#define EMIT_RATE			4
#define POINT_GRAV_POS		5
#define PLANE_GRAV_DIR		6


#define BPOINT	0
#define BPARTICLE 1

struct Point {
        Vector3DF pos;
        DWORD clr;
        int next;
};

struct Particle {
        Vector3DF pos;
        DWORD clr;
        int next;
        Vector3DF vel;
        Vector3DF vel_eval;
        unsigned short age;
};

/**
 * Tu z tego co rozumiem przechodzimy do domeny liczb całkowitych i mamy
 * już takie pojęcia jak objętość i przestrzeń. Zdaje się, że wykrywane są
 * też kolizje (jeśli tak, to dziedziczenie PointSet <- FluidSystem ma sens).
 */
class PointSet : public GeomX {
public:
        PointSet ();
        virtual ~PointSet () {}

        // Point Sets
        virtual void Draw ( float* view_mat, float rad );
        virtual void Reset ();
        virtual int AddPoint ();
        virtual int AddPointReuse ();

        Point* GetPoint (int n) { return (Point*) GetElem (0, n); }
        int NumPoints () { return NumElem (0); }

        // Particle system
        virtual void Run () = 0;
        virtual void Advance () = 0;
        virtual void Emit (float spacing);

        // Parameters
        void SetParam (int p, float v )		{ m_Param[p] = v; }
        float GetParam ( int p )			{ return (float) m_Param[p]; }
        Vector3DF GetVec ( int p )			{ return m_Vec[p]; }
        void SetVec ( int p, Vector3DF v )	{ m_Vec[p] = v; }
        void Toggle ( int p )				{ m_Toggle[p] = !m_Toggle[p]; }
        bool GetToggle ( int p )			{ return m_Toggle[p]; }
        float GetDT()						{ return (float) m_DT; }

        // Spatial Subdivision
        void Grid_Setup ( Vector3DF min, Vector3DF max, float sim_scale, float cell_size, float border );
        void Grid_Create ();
        void Grid_InsertParticles ();
        void Grid_FindCells ( Vector3DF p, float radius );
        int Grid_FindCell ( Vector3DF p );

        Vector3DF GetGridRes ()		{ return m_GridRes; }
        Vector3DF GetGridMin ()		{ return m_GridMin; }
        Vector3DF GetGridMax ()		{ return m_GridMax; }
        Vector3DF GetGridDelta ()	{ return m_GridDelta; }
        int GetGridCell ( int x, int y, int z );

        Point* firstGridParticle ( int gc, int& p );
        Point* nextGridParticle ( int& p );

        unsigned short* getNeighborTable ( int n, int& cnt );


        // USUŃ
        Ptr <Model::PointList> getPoints () const;


protected:

        int m_Frame;


        /**
         * Parameters
         * Tylko 21 elementów.
         */
        double	m_Param [ MAX_PARAM ]; // see defines above

        /**
         * To są chyba ściany.
         * Tylko 21 elementów.
         */
        Vector3DF m_Vec [ MAX_PARAM ];

        /**
         * Tylko 21 elementów.
         */
        bool m_Toggle[MAX_PARAM];


        // Particle System
        double m_DT;
        double m_Time;

/*--------------------------------------------------------------------------*/

        /**
         * Spatial Grid. Przy 2048 cząsteczkach osiąga rozmiar 190124.
         * Jest to wektor, który z tego co widzę indeksuje się offsetem,
         * który da się wyliczyć z pozycji Cząsteczki i odzwierciedla komórki.
         *
         * Odzwierciedla on sześcian o rozmiarach m_GridSize, czyli 65 * 65 * 45, co daje 190125 komórek (cells).
         * Każda z komórek zawiera numer pierwszego punktu (n), natomiast te punkty z GemoX::mBuf::data są ułożone
         * w linked list (dowiązanie poprzez next). W ten sposób mamy definicję gdzie jest który punkt w domenie
         * liczb całkowitych.
         */
        std::vector<int> m_Grid;

        /**
         * jak wyżej, tylko mamy ilość punktów w danej komórce.
         */
        std::vector<int> m_GridCnt;

/*--------------------------------------------------------------------------*/

        /**
         * Aktualna ilość cells.
         * Przy 2048 cząsteczkach osiąga rozmiar 190124. Zatem
         * rozmiar m_Grid. Czyli grid zawiera cells.
         */
        int m_GridTotal; // total # cells

        /**
         * volume of grid (may not match domain volume exactly)
         * m_GridMin = {x = -31, y = -31, z = -1}
         */
        Vector3DF m_GridMin;

        /**
         * m_GridMax = {x = 31, y = 31, z = 41}
         */
        Vector3DF m_GridMax;

        /**
         * resolution in each axis
         * m_GridRes = {x = 13, y = 13, z = 9}
         */
        Vector3DF m_GridRes;

        /**
         * physical size in each axis
         * m_GridSize = {x = 64.9999924, y = 64.9999924, z = 44.9999962}
         */
        Vector3DF m_GridSize;

        /**
         * m_GridDelta = {x = 0.200000018, y = 0.200000018, z = 0.200000018}
         */
        Vector3DF m_GridDelta;

        /**
         * m_GridCellsize = 4.99999952
         */
        float m_GridCellsize;

        /**
         * m_GridCell = {0 <repeats 27 times>}
         */
        int m_GridCell[27];

        /**
         * Neighbor Table - czyli chyba odzwierciedla dane dot. relacji między
         * cząsteczkami - może chodzi o collision detection? MAX_NEIGHBOR = 80.
         */
        unsigned short m_NC[65536]; // neighbor table (600k)
        unsigned short m_Neighbor[65536][MAX_NEIGHBOR];
        float m_NDist[65536][MAX_NEIGHBOR];

        /// -1
        static int m_pcurr;
};

#endif
