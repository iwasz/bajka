/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_SCENE_H_
#define BAJKA_SCENE_H_

namespace Model {
class IModelManager;
}

namespace Util {

class Scene {
public:

        Scene (Model::IModelManager *modelManager);
        ~Scene ();

        void onStep ();

private:

        struct Impl;
        Impl *impl;
};

} /* namespace Util */
#endif /* SCENE_H_ */
