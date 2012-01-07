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

#include <time.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "common_defs.h"
#include "sandBox/DemoHelper.h"
#include "sandBox/OpenGLHelper.h"

#ifdef BUILD_CUDA
#include "fluid_system_host.cuh"
#endif
#include "fluid_system.h"
#include "gl_helper.h"

#ifdef _MSC_VER						// Windows
#include <gl/glut.h>
#else								// Linux
#include <GL/glut.h>
#endif

bool bTiming = false;
bool bRec = false;
int mFrame = 0;

// Globals
FluidSystem psys;

float window_width = 1024;
float window_height = 768;

Vector3DF obj_from, obj_angs;

float cam_fov;

int psys_rate = 0; // Particle stuff
int psys_freq = 1;
int psys_demo = 0;
//int             psys_nmax = 4096;
int psys_nmax = 2048;

int iClrMode = 0; // Tryb koloru. Martwi mnie, że podaje się to do phys-machine.
bool bPntDraw = false; // Coś ważnego, ale nie wiem co.

OpenGLDisplay openGLDisplay;
IDisplay *disp = &openGLDisplay;

/*##########################################################################*/

/**
 * Główna pętla programu.
 */
void display () 
{
	// 1. Do simulation!
        psys.Run ();

        // 2. Draw the results of simulation.
        disp->drawParticles (psys.getMBuff (), psys.NumPoints ());
}

/**
 * Odpalane kiedy rozmiar okna sie zmienia, oraz przy pierwszym uruchomieniu.
 * @param width
 * @param height
 */
void reshape (int width, int height)
{
        // set window height and width
        window_width = (float) width;
        window_height = (float) height;
        glViewport (0, 0, width, height);
}

void UpdateEmit ()
{
        obj_from = psys.GetVec (EMIT_POS);
        obj_angs = psys.GetVec (EMIT_ANG);
}

void init (int argc, char **argv)
{
        disp->init (argc, argv);

        // OpenGL callbacks
        glutDisplayFunc (display);
        glutReshapeFunc (reshape);

/*--------------------------------------------------------------------------*/

        obj_from.x = 0;
        obj_from.y = 0;
        obj_from.z = 20; // emitter

        obj_angs.x = 118.7;
        obj_angs.y = 200;
        obj_angs.z = 1.0;

        psys.Initialize (BFLUID, psys_nmax);

        // Kod usunięty z FluidSystem
        DemoHelper::createDemo (&psys, 1, psys_nmax);

        psys.SetVec (EMIT_ANG, Vector3DF (obj_angs.x, obj_angs.y, obj_angs.z));
        psys.SetVec (EMIT_POS, Vector3DF (obj_from.x, obj_from.y, obj_from.z));

        psys.SetParam (PNT_DRAWMODE, int(bPntDraw ? 1 : 0));
        psys.SetParam (CLR_MODE, iClrMode);
}


int main ( int argc, char **argv )
{

	/*
	 * Inicjuje parametry w GeomX i PointSet (duużo parametrów),
	 * rezerwuje pamięć i tworzy struktury dla pierwszego demka.
	 */
	init (argc, argv);

        // wait for something to happen
        glutMainLoop ();

        return 0;
}
