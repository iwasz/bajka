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

#	ifndef DEMOHELPER_H_
#	define DEMOHELPER_H_

#include "../common/vector.h"

class FluidSystem;

/**
 * Tu chcę wyrzucić wszystiemetody pomocnicze z tych 3 gównych klas. Czyli
 * te metody, które tworzą dema, a nie symulują.
 */
struct DemoHelper {

        virtual ~DemoHelper () {}

        /**
         * Główna metoda tworząca prezentację.
         */
        static void createDemo (FluidSystem *fluid, int demoNumber, int maxParticlesNum);

        /**
         * To dodaje do sceny sześcian z cząsteczek, które mają utworzyć potem płyn.
         */
        static void AddVolume (FluidSystem *fluid, Vector3DF min, Vector3DF max, float spacing);

};

#	endif /* DEMOHELPER_H_ */
