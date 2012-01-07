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

#include "point_set.h"

int PointSet::m_pcurr = -1;

PointSet::PointSet ()
{	
	m_GridRes.Set ( 0, 0, 0 );
	m_pcurr = -1;
	Reset ();
}

int PointSet::GetGridCell ( int x, int y, int z )
{
	return (int) ( (z*m_GridRes.y + y)*m_GridRes.x + x);
}

Point* PointSet::firstGridParticle ( int gc, int& p )
{
	m_pcurr = m_Grid [ gc ];
	if ( m_pcurr == -1 ) return 0x0;
	p = m_pcurr;
	return (Point*) (mBuf[0].data + m_pcurr * mBuf[0].stride);
}

Point* PointSet::nextGridParticle ( int& p )
{
	Point* pnt = 0x0;
	if ( m_pcurr != -1 ) {
		pnt = (Point*) (mBuf[0].data + m_pcurr * mBuf[0].stride);
		p = m_pcurr;
		m_pcurr = pnt->next;
	}	
	return pnt;
}

unsigned short* PointSet::getNeighborTable ( int n, int& cnt )
{
	cnt = m_NC[n];
	if ( cnt == 0 ) return 0x0;
	return &m_Neighbor[n][0];
}

void PointSet::Reset ()
{
	// Reset number of particles
//	ResetBuffer ( 0 );	

	m_Time = 0;
	m_DT = 0.1;
	m_Param[POINT_GRAV] = 100.0;
	m_Param[PLANE_GRAV] = 0.0;
	
	m_Vec[ POINT_GRAV_POS].Set(0,0,50.0);
	m_Vec[ PLANE_GRAV_DIR].Set(0,0,-9.8);
	m_Vec[ EMIT_RATE ].Set ( 1, 10, 0 );
	m_Vec[ EMIT_POS ].Set ( 50, 0, 35 );	
	m_Vec[ EMIT_ANG ].Set ( 90, 45, 50.0 );	
	m_Vec[ EMIT_DANG ].Set ( 0, 0, 0 );	
	m_Vec[ EMIT_SPREAD ].Set ( 4, 4, 1 );	
}

int PointSet::AddPoint ()
{
	xref ndx;	
	AddElem ( 0, ndx );	
	return ndx;
}

int PointSet::AddPointReuse ()
{
	xref ndx;	
	if ( NumPoints() < mBuf[0].max-1 )
		AddElem ( 0, ndx );
	else
		RandomElem ( 0, ndx );
	return ndx;
}

/**
 * Aktualne rysowanie.
 */
void PointSet::Draw (float* view_mat, float)
{

}

void PointSet::Emit ( float spacing )
{
	Particle* p;
	Vector3DF dir;
	Vector3DF pos;
	float ang_rand, tilt_rand;
	float rnd = m_Vec[EMIT_RATE].y * 0.15;	
	int x = (int) sqrt(m_Vec[EMIT_RATE].y);

	for ( int n = 0; n < m_Vec[EMIT_RATE].y; n++ ) {
		ang_rand = (float(rand()*2.0/RAND_MAX) - 1.0) * m_Vec[EMIT_SPREAD].x;
		tilt_rand = (float(rand()*2.0/RAND_MAX) - 1.0) * m_Vec[EMIT_SPREAD].y;
		dir.x = cos ( ( m_Vec[EMIT_ANG].x + ang_rand) * DEGtoRAD ) * sin( ( m_Vec[EMIT_ANG].y + tilt_rand) * DEGtoRAD ) * m_Vec[EMIT_ANG].z;
		dir.y = sin ( ( m_Vec[EMIT_ANG].x + ang_rand) * DEGtoRAD ) * sin( ( m_Vec[EMIT_ANG].y + tilt_rand) * DEGtoRAD ) * m_Vec[EMIT_ANG].z;
		dir.z = cos ( ( m_Vec[EMIT_ANG].y + tilt_rand) * DEGtoRAD ) * m_Vec[EMIT_ANG].z;
		pos = m_Vec[EMIT_POS];
		pos.x += spacing * (n/x);
		pos.y += spacing * (n%x);
		
		p = (Particle*) GetElem( 0, AddPointReuse () );
		p->pos = pos;
		p->vel = dir;
		p->vel_eval = dir;
		p->age = 0;	
		p->clr = COLORA ( m_Time/10.0, m_Time/5.0, m_Time /4.0, 1 );
	}
}


// Ideal grid cell size (gs) = 2 * smoothing radius = 0.02*2 = 0.04
// Ideal domain size = k*gs/d = k*0.02*2/0.005 = k*8 = {8, 16, 24, 32, 40, 48, ..}
//    (k = number of cells, gs = cell size, d = simulation scale)
void PointSet::Grid_Setup ( Vector3DF min, Vector3DF max, float sim_scale, float cell_size, float border )
{
	float world_cellsize = cell_size / sim_scale;
	m_Grid.clear ();
	m_GridMin = min;	m_GridMin -= border;
	m_GridMax = max;	m_GridMax += border;
	m_GridSize = m_GridMax;
	m_GridSize -= m_GridMin;
	m_GridCellsize = world_cellsize;
	m_GridRes.x = ceil ( m_GridSize.x / world_cellsize );		// Determine grid resolution
	m_GridRes.y = ceil ( m_GridSize.y / world_cellsize );
	m_GridRes.z = ceil ( m_GridSize.z / world_cellsize );
	m_GridSize.x = m_GridRes.x * cell_size / sim_scale;				// Adjust grid size to multiple of cell size
	m_GridSize.y = m_GridRes.y * cell_size / sim_scale;
	m_GridSize.z = m_GridRes.z * cell_size / sim_scale;
	m_GridDelta = m_GridRes;		// delta = translate from world space to cell #
	m_GridDelta /= m_GridSize;
	m_GridTotal = (int)(m_GridSize.x * m_GridSize.y * m_GridSize.z);

	m_Grid.clear ();
	m_GridCnt.clear ();

	m_Grid.reserve ( m_GridTotal );
	m_GridCnt.reserve ( m_GridTotal );	
	for (int n=0; n < m_GridTotal; n++) {
		m_Grid.push_back ( -1 );
		m_GridCnt.push_back ( 0 );
	}

}

/**
 * Wstawia początkowe n cząsteczek do cell-grida.
 */
void PointSet::Grid_InsertParticles ()
{
	char *dat1, *dat1_end;
	Point *p;
	int gs;
	int gx, gy, gz;
	
	// Poniższa pętla inicjuje wartości mBuf[i].data->next = -1. Te wartości są typu Point.
	dat1_end = mBuf[0].data + NumPoints()*mBuf[0].stride;
	for ( dat1 = mBuf[0].data; dat1 < dat1_end; dat1 += mBuf[0].stride ) 
		((Point*) dat1)->next = -1;	

	// Jak widać inicjuje te 2 wektory.
	for (int n=0; n < m_GridTotal; n++) {
		m_Grid[n] = -1;
		m_GridCnt[n] = 0;
	}

	/*
	 * Iteruje przez wszystkie punkty 2gi raz (wcześniej ustawiono next = -1).
	 * Z tego co widzę, te punkty mają współrzędne typu float i mają nadane
	 * wartości początkowe (wylosowane?). Punkty pochodzą z GeomX.
	 */
	dat1_end = mBuf[0].data + NumPoints()*mBuf[0].stride;
	int n = 0;
	for ( dat1 = mBuf[0].data; dat1 < dat1_end; dat1 += mBuf[0].stride ) {
		p = (Point*) dat1;
		gx = (int)( (p->pos.x - m_GridMin.x) * m_GridDelta.x); // Determine grid cell
		gy = (int)( (p->pos.y - m_GridMin.y) * m_GridDelta.y);
		gz = (int)( (p->pos.z - m_GridMin.z) * m_GridDelta.z);
		gs = (int)( (gz*m_GridRes.y + gy)*m_GridRes.x + gx); // Grid shift?
		if ( gs >= 0 && gs < m_GridTotal ) {
			p->next = m_Grid[gs]; // p->next ma teraz numer cząsteczki.
			m_Grid[gs] = n; // Ustaw numer cząsteczki w m_Grid
			m_GridCnt[gs]++; // Ilość cząsteczek w danej komórce
		}
		n++;
	}
}

int PointSet::Grid_FindCell ( Vector3DF p )
{
	int gc;

	int x = (int) (p.x - m_GridMin.x) * m_GridDelta.x;
	int y = (int) (p.y - m_GridMin.y) * m_GridDelta.y;
	int z = (int) (p.z - m_GridMin.z) * m_GridDelta.z;

	gc = (int) ((z * m_GridRes.y + y) * m_GridRes.x + x);

	if (gc < 0 || gc > m_GridTotal) {
                return -1;
	}

        return gc;
}

void PointSet::Grid_FindCells ( Vector3DF p, float radius )
{
	// Compute sphere range
	int sph_min_x = (int)((-radius + p.x - m_GridMin.x) * m_GridDelta.x);
	int sph_min_y = (int)((-radius + p.y - m_GridMin.y) * m_GridDelta.y);
	int sph_min_z = (int)((-radius + p.z - m_GridMin.z) * m_GridDelta.z);

	if ( sph_min_x < 0 ) sph_min_x = 0;
	if ( sph_min_y < 0 ) sph_min_y = 0;
	if ( sph_min_z < 0 ) sph_min_z = 0;

	m_GridCell[0] = (int)((sph_min_z * m_GridRes.y + sph_min_y) * m_GridRes.x + sph_min_x);
	m_GridCell[1] = m_GridCell[0] + 1;
	m_GridCell[2] = (int)(m_GridCell[0] + m_GridRes.x);
	m_GridCell[3] = m_GridCell[2] + 1;

	if ( sph_min_z+1 < m_GridRes.z ) {
		m_GridCell[4] = (int)(m_GridCell[0] + m_GridRes.y*m_GridRes.x);
		m_GridCell[5] = m_GridCell[4] + 1;
		m_GridCell[6] = (int)(m_GridCell[4] + m_GridRes.x);
		m_GridCell[7] = m_GridCell[6] + 1;
	}
	if ( sph_min_x+1 >= m_GridRes.x ) {
		m_GridCell[1] = -1;		m_GridCell[3] = -1;		
		m_GridCell[5] = -1;		m_GridCell[7] = -1;
	}
	if ( sph_min_y+1 >= m_GridRes.y ) {
		m_GridCell[2] = -1;		m_GridCell[3] = -1;
		m_GridCell[6] = -1;		m_GridCell[7] = -1;
	}
}

Ptr <Model::PointList> PointSet::getPoints () const
{
        Ptr <Model::PointList> ret (new Model::PointList);

        char* dat;
        Point* p;
        dat = mBuf[0].data;

        /*
         * Iteruj przez wszystkie punkty - punktów jest w mojej symulacji tylko 400.
         * I bardzo szczęśliwe jest to, że końcowy odbiorca dostaje do dyspozycji
         * (prawie-wektor) obiektów Point.
         */
        for (int n = 0; n < NumElem (0); n++) {

                p = (Point*) dat;

                // Przykładowe pos jednego z punktów : {x = 0.318198085, y = -12.8199997, z = 29.6597519}
                ret->push_back (Model::Point (p->pos.x * 8.5, p->pos.z * 8.0));
                dat += mBuf[0].stride;
        }

        return ret;
}
