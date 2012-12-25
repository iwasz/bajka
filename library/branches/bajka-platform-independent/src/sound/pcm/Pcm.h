/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_SOUND_PCM_H_
#define BAJKA_SOUND_PCM_H_

#include <stdint.h>

namespace Sound {

/**
 * Ładuje cały plik z danymi PCM do bufora w pamięci. Zwolnić pamięć za pomocą delete [].
 */
extern void load (const char *path, void **data, size_t *bytesLen);

} /* namespace Sound */

#endif /* PCM_H_ */
