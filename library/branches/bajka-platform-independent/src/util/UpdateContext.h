/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef UPDATECONTEXT_H_
#define UPDATECONTEXT_H_

namespace View {
class GLContext;
}

namespace Util {
class Config;

/**
 * Kazdy model w kazdej metodzie update dostanie takie DTO.
 */
struct  UpdateContext {

        UpdateContext () : glContext (NULL), config (NULL) {}

        View::GLContext *glContext;
        Util::Config *config;
};

} /* namespace Util */
#endif /* UPDATECONTEXT_H_ */
