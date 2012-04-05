/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifdef ANDROID

#include <android_native_app_glue.h>
#include <android/log.h>
#include <Container.h>
#include <ContainerFactory.h>
#include <inputFormat/mxml/MXmlMetaService.h>

using namespace Container;

void android_main(struct android_app* state) {

    // Make sure glue isn't stripped.
    app_dummy();

    Ptr <BeanFactoryContainer> container = ContainerFactory::createContainer (MXmlMetaService::parseFile ("main.xml"));
    std::string mainText = vcast <std::string> (container->getBean ("main"));
    __android_log_print (ANDROID_LOG_INFO, "bajka", mainText.c_str ());

//    struct engine engine;
//    memset(&engine, 0, sizeof(engine));
//    state->userData = &engine;
//    state->onAppCmd = engine_handle_cmd;
//    state->onInputEvent = engine_handle_input;
//    engine.app = state;
//
//    // Prepare to monitor accelerometer
//    engine.sensorManager = ASensorManager_getInstance();
//    engine.accelerometerSensor = ASensorManager_getDefaultSensor(engine.sensorManager,
//            ASENSOR_TYPE_ACCELEROMETER);
//    engine.sensorEventQueue = ASensorManager_createEventQueue(engine.sensorManager,
//            state->looper, LOOPER_ID_USER, NULL, NULL);
//
//    if (state->savedState != NULL) {
//        // We are starting with a previous saved state; restore from it.
//        engine.state = *(struct saved_state*)state->savedState;
//    }
//
//    // loop waiting for stuff to do.
//
//    while (1) {
//        // Read all pending events.
//        int ident;
//        int events;
//        struct android_poll_source* source;
//
//        // If not animating, we will block forever waiting for events.
//        // If animating, we loop until all events are read, then continue
//        // to draw the next frame of animation.
//        while ((ident=ALooper_pollAll(engine.animating ? 0 : -1, NULL, &events,
//                (void**)&source)) >= 0) {
//
//            // Process this event.
//            if (source != NULL) {
//                source->process(state, source);
//            }
//
//            // If a sensor has data, process it now.
//            if (ident == LOOPER_ID_USER) {
//                if (engine.accelerometerSensor != NULL) {
//                    ASensorEvent event;
//                    while (ASensorEventQueue_getEvents(engine.sensorEventQueue,
//                            &event, 1) > 0) {
//                        LOGI("accelerometer: x=%f y=%f z=%f",
//                                event.acceleration.x, event.acceleration.y,
//                                event.acceleration.z);
//                    }
//                }
//            }
//
//            // Check if we are exiting.
//            if (state->destroyRequested != 0) {
//                engine_term_display(&engine);
//                return;
//            }
//        }
//
//        if (engine.animating) {
//            // Done with events; draw next animation frame.
//            engine.state.angle += .01f;
//            if (engine.state.angle > 1) {
//                engine.state.angle = 0;
//            }
//
//            // Drawing is throttled to the screen update rate, so there
//            // is no need to do timing here.
//            engine_draw_frame(&engine);
//        }
//    }
}

#endif


