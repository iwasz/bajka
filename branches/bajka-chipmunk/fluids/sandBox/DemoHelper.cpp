/****************************************************************************
 *                                                                          *
 *  Author & Copyright (c) :  Lukasz Iwaszkiewicz                           *
 *  ~~~~~~~~~~~~~~~~~~~~~~~~  lukasz.iwaszkiewicz@gmail.com                 *
 *                                                                          *
 *  Date :                    Nov 3, 2009                                   *
 *  ~~~~~~                                                                  *
 *                                                                          *
 *      This program is free software;  you can redistribute it and / or    *
 *      modify it under the terms of the GNU General Public License. See    *
 *      COPYING file for details.                                           *
 *                                                                          *
 ****************************************************************************/

#include "DemoHelper.h"
#include "fluids/fluid_system.h"
#include <assert.h>

/*
 * Wzięte z void FluidSystem::SPH_CreateExample ( int n, int nmax )
 */
void DemoHelper::createDemo (FluidSystem *fluid, int demoNumber, int maxParticlesNum)
{
        assert (fluid);

        Vector3DF pos;
        Vector3DF min, max;

        fluid->Reset (maxParticlesNum);

        switch (demoNumber) {
        case 0:         // Wave pool

                // Wydaje mi się, że to tworzy jakieś ramy dla objętości (początkowe rozmiary cieczy?)
                fluid->SetVec (SPH_VOLMIN, Vector3DF (-30, -30, 0));
                fluid->SetVec (SPH_VOLMAX, Vector3DF (30, 30, 40));

                fluid->SetVec (SPH_INITMIN, Vector3DF (-20, -26, 10));
                fluid->SetVec (SPH_INITMAX, Vector3DF (20, 26, 40));

                fluid->SetParam (FORCE_XMIN_SIN, 12.0);
                fluid->SetParam (BOUND_ZMIN_SLOPE, 0.05);

                break;

        case 1:         // Dam break

                fluid->SetVec (SPH_VOLMIN, Vector3DF (-30, -14, 0));
                fluid->SetVec (SPH_VOLMAX, Vector3DF (30, 14, 60));

                fluid->SetVec (SPH_INITMIN, Vector3DF (0, -13, 0));
                fluid->SetVec (SPH_INITMAX, Vector3DF (29, 13, 30));

                fluid->SetVec (PLANE_GRAV_DIR, Vector3DF (0.0, 0, -9.8));

//        case 2:         // Dual-Wave pool
//                m_Vec [ SPH_VOLMIN ].Set ( -60, -5, 0 );
//                m_Vec [ SPH_VOLMAX ].Set ( 60, 5, 50 );
//                m_Vec [ SPH_INITMIN ].Set ( -46, -5, 0 );
//                m_Vec [ SPH_INITMAX ].Set ( 46, 5, 15 );
//                m_Param [ FORCE_XMIN_SIN ] = 8.0;
//                m_Param [ FORCE_XMAX_SIN ] = 8.0;
//                m_Vec [ PLANE_GRAV_DIR ].Set ( 0.0, 0, -9.8 );
//                break;
//        case 3:         // Swirl Stream
//                m_Vec [ SPH_VOLMIN ].Set ( -30, -30, 0 );
//                m_Vec [ SPH_VOLMAX ].Set ( 30, 30, 50 );
//                m_Vec [ SPH_INITMIN ].Set ( -30, -30, 0 );
//                m_Vec [ SPH_INITMAX ].Set ( 30, 30, 40 );
//                m_Vec [ EMIT_POS ].Set ( -20, -20, 22 );
//                m_Vec [ EMIT_RATE ].Set ( 1, 4, 0 );
//                m_Vec [ EMIT_ANG ].Set ( 0, 120, 1.5 );
//                m_Vec [ EMIT_DANG ].Set ( 0, 0, 0 );
//                m_Vec [ PLANE_GRAV_DIR ].Set ( 0.0, 0, -9.8 );
//                break;
//        case 4:         // Shockwave
//                m_Vec [ SPH_VOLMIN ].Set ( -60, -15, 0 );
//                m_Vec [ SPH_VOLMAX ].Set ( 60, 15, 50 );
//                m_Vec [ SPH_INITMIN ].Set ( -59, -14, 0 );
//                m_Vec [ SPH_INITMAX ].Set ( 59, 14, 30 );
//                m_Vec [ PLANE_GRAV_DIR ].Set ( 0.0, 0, -9.8 );
//                m_Toggle [ WALL_BARRIER ] = true;
//                m_Toggle [ WRAP_X ] = true;
//                break;
//        case 5:         // Zero gravity
//                m_Vec [ SPH_VOLMIN ].Set ( -40, -40, 0 );
//                m_Vec [ SPH_VOLMAX ].Set ( 40, 40, 50 );
//                m_Vec [ SPH_INITMIN ].Set ( -20, -20, 20 );
//                m_Vec [ SPH_INITMAX ].Set ( 20, 20, 40 );
//                m_Vec [ EMIT_POS ].Set ( -20, 0, 40 );
//                m_Vec [ EMIT_RATE ].Set ( 2, 1, 0 );
//                m_Vec [ EMIT_ANG ].Set ( 0, 120, 0.25 );
//                m_Vec [ PLANE_GRAV_DIR ].Set ( 0, 0, 0 );
//                m_Param [ SPH_INTSTIFF ] = 0.20;
//                break;
//        case 6:         // Point gravity
//                m_Vec [ SPH_VOLMIN ].Set ( -40, -40, 0 );
//                m_Vec [ SPH_VOLMAX ].Set ( 40, 40, 50 );
//                m_Vec [ SPH_INITMIN ].Set ( -20, -20, 20 );
//                m_Vec [ SPH_INITMAX ].Set ( 20, 20, 40 );
//                m_Param [ SPH_INTSTIFF ] = 0.50;
//                m_Vec [ EMIT_POS ].Set ( -20, 20, 25 );
//                m_Vec [ EMIT_RATE ].Set ( 1, 4, 0 );
//                m_Vec [ EMIT_ANG ].Set ( -20, 100, 2.0 );
//                m_Vec [ POINT_GRAV_POS ].Set ( 0, 0, 25 );
//                m_Vec [ PLANE_GRAV_DIR ].Set ( 0, 0, 0 );
//                m_Param [ POINT_GRAV ] = 3.5;
//                break;
//        case 7:         // Levy break
//                m_Vec [ SPH_VOLMIN ].Set ( -40, -40, 0 );
//                m_Vec [ SPH_VOLMAX ].Set ( 40, 40, 50 );
//                m_Vec [ SPH_INITMIN ].Set ( 10, -40, 0 );
//                m_Vec [ SPH_INITMAX ].Set ( 40, 40, 50 );
//                m_Vec [ EMIT_POS ].Set ( 34, 27, 16.6 );
//                m_Vec [ EMIT_RATE ].Set ( 2, 9, 0 );
//                m_Vec [ EMIT_ANG ].Set ( 118, 200, 1.0 );
//                m_Toggle [ LEVY_BARRIER ] = true;
//                m_Param [ BOUND_ZMIN_SLOPE ] = 0.1;
//                m_Vec [ PLANE_GRAV_DIR ].Set ( 0.0, 0, -9.8 );
//                break;
//        case 8:         // Drain
//                m_Vec [ SPH_VOLMIN ].Set ( -20, -20, 0 );
//                m_Vec [ SPH_VOLMAX ].Set ( 20, 20, 50 );
//                m_Vec [ SPH_INITMIN ].Set ( -15, -20, 20 );
//                m_Vec [ SPH_INITMAX ].Set ( 20, 20, 50 );
//                m_Vec [ EMIT_POS ].Set ( -16, -16, 30 );
//                m_Vec [ EMIT_RATE ].Set ( 1, 4, 0 );
//                m_Vec [ EMIT_ANG ].Set ( -20, 140, 1.8 );
//                m_Toggle [ DRAIN_BARRIER ] = true;
//                m_Vec [ PLANE_GRAV_DIR ].Set ( 0.0, 0, -9.8 );
//                break;
//        case 9:                 // Tumbler
//                m_Vec [ SPH_VOLMIN ].Set ( -30, -30, 0 );
//                m_Vec [ SPH_VOLMAX ].Set ( 30, 30, 50 );
//                m_Vec [ SPH_INITMIN ].Set ( 24, -29, 20 );
//                m_Vec [ SPH_INITMAX ].Set ( 29, 29, 40 );
//                m_Param [ SPH_VISC ] = 0.1;
//                m_Param [ SPH_INTSTIFF ] = 0.50;
//                m_Param [ SPH_EXTSTIFF ] = 8000;
//                //m_Param [ SPH_SMOOTHRADIUS ] = 0.01;
//                m_Param [ BOUND_ZMIN_SLOPE ] = 0.4;
//                m_Param [ FORCE_XMIN_SIN ] = 12.00;
//                m_Vec [ PLANE_GRAV_DIR ].Set ( 0.0, 0, -9.8 );
//                break;
//        case 10:                // Large sim
//                m_Vec [ SPH_VOLMIN ].Set ( -35, -35, 0 );
//                m_Vec [ SPH_VOLMAX ].Set ( 35, 35, 60 );
//                m_Vec [ SPH_INITMIN ].Set ( -5, -35, 0 );
//                m_Vec [ SPH_INITMAX ].Set ( 30, 0, 60 );
//                m_Vec [ PLANE_GRAV_DIR ].Set ( 0.0, 0, -9.8 );
//                break;
        default:
                break;
        }

        fluid->SPH_ComputeKernels ();

        fluid->SetParam (SPH_SIMSIZE, fluid->GetParam (SPH_SIMSCALE) * (fluid->GetVec(SPH_VOLMAX).z - fluid->GetVec(SPH_VOLMIN).z));
        fluid->SetParam (SPH_PDIST, pow (fluid->GetParam (SPH_PMASS) / fluid->GetParam (SPH_RESTDENSITY), 1 / 3.0));

        float ss = fluid->GetParam (SPH_PDIST) * 0.87 / fluid->GetParam (SPH_SIMSCALE);
        printf ( "Spacing: %f\n", ss);
        AddVolume (fluid, fluid->GetVec(SPH_INITMIN), fluid->GetVec(SPH_INITMAX), ss );       // Create the particles

        float cell_size = fluid->GetParam (SPH_SMOOTHRADIUS) * 2.0;                        // Grid cell size (2r)

        fluid->Grid_Setup (fluid->GetVec(SPH_VOLMIN), fluid->GetVec(SPH_VOLMAX), fluid->GetParam (SPH_SIMSCALE), cell_size, 1.0 );                                                                                             // Setup grid
        fluid->Grid_InsertParticles ();                                                                        // Insert particles

        #ifdef BUILD_CUDA
                FluidClearCUDA ();
                Sleep ( 500 );

                FluidSetupCUDA ( NumPoints(), sizeof(Fluid), *(float3*)& m_GridMin, *(float3*)& m_GridMax, *(float3*)& m_GridRes, *(float3*)& m_GridSize, (int) m_Vec[EMIT_RATE].x );

                Sleep ( 500 );

                FluidParamCUDA ( m_Param[SPH_SIMSCALE], m_Param[SPH_SMOOTHRADIUS], m_Param[SPH_PMASS], m_Param[SPH_RESTDENSITY], m_Param[SPH_INTSTIFF], m_Param[SPH_VISC] );
        #endif
}

/*
 * Wzięte z void PointSet::AddVolume ( Vector3DF min, Vector3DF max, float spacing )
 */
void DemoHelper::AddVolume (FluidSystem *fluid, Vector3DF min, Vector3DF max, float spacing)
{
        assert (fluid);

        Vector3DF pos;
        Point* p;
        float dx, dy, dz;
        dx = max.x-min.x;
        dy = max.y-min.y;
        dz = max.z-min.z;

        float x = min.x;
        float y = min.y;
        float z = min.z;

        for (float z = max.z; z >= min.z; z -= spacing ) {
//                for (float y = min.y; y <= max.y; y += spacing ) {
                        for (float x = min.x; x <= max.x; x += spacing ) {

                                // GetPoint to jest już jakiś bardziej zaawansowany getter.
                                p = fluid->GetPoint (fluid->AddPointReuse ());
                                pos.Set ( x, y, z);
                                //pos.x += -0.05 + float( rand() * 0.1 ) / RAND_MAX;
                                //pos.y += -0.05 + float( rand() * 0.1 ) / RAND_MAX;
                                //pos.z += -0.05 + float( rand() * 0.1 ) / RAND_MAX;
                                p->pos = pos;
                                p->clr = COLORA( (x-min.x)/dx, (y-min.y)/dy, (z-min.z)/dz, 1);
                        }
                }
//        }
}
