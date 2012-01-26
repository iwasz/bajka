/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_MODEL_GROUP_H_
#define BAJKA_MODEL_GROUP_H_

#include "AbstractModel.h"

namespace Model {

/**
 * Podstawowa grupa modeli, czyli coś, co się rozciąga w nieskończoność (nie ma
 * swojego rozmiaru).
 */
class Group : public AbstractModel {
public:
	virtual ~Group() {}
};

} /* namespace Model */

#endif /* GROUP_H_ */
