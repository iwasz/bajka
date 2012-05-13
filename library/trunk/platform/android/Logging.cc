/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Logging.h"
#include <string>
#include <boost/lexical_cast.hpp>

static std::string actionToString (int32_t action);
static std::string flagsToString (int32_t flags);
static std::string metaStateToString (int32_t metaState);
static std::string edgeFlagsToString (int32_t edgeFlags);

void logEvent (AInputEvent *androidEvent)
{
        if (AInputEvent_getType (androidEvent) == AINPUT_EVENT_TYPE_MOTION) {

                int32_t action = AMotionEvent_getAction (androidEvent);
                std::string actionStr = actionToString (action);

                int32_t flags = AMotionEvent_getFlags (androidEvent);
                std::string flagsStr = flagsToString (flags);

                int32_t metaState = AMotionEvent_getMetaState (androidEvent);
                std::string metaStateStr = metaStateToString (metaState);

                int32_t edgeFlags = AMotionEvent_getEdgeFlags (androidEvent);
                std::string edgeFlagsStr = edgeFlagsToString (edgeFlags);

                int64_t downTime = AMotionEvent_getDownTime (androidEvent);
                int64_t eventTime = AMotionEvent_getEventTime (androidEvent);

                float xOffset =  AMotionEvent_getXOffset (androidEvent);
                float yOffset = AMotionEvent_getYOffset (androidEvent);

                float xPrecission = AMotionEvent_getXPrecision (androidEvent);
                float yPrecission = AMotionEvent_getYPrecision (androidEvent);

                size_t pointerCount = AMotionEvent_getPointerCount (androidEvent);

                LOGI ("MOTION : action=%s, flags=%s, meta=%s, edge=%s, dTime=%lld, eTime=%lld, offset=(%.2f, %.2f), prec=(%.2f, %.2f)",
                                actionStr.c_str (), flagsStr.c_str (), metaStateStr.c_str (), edgeFlagsStr.c_str (),
                                downTime, eventTime, xOffset, yOffset, xPrecission, yPrecission);

                for (size_t i = 0; i < pointerCount; ++i) {

                        float rawX = AMotionEvent_getRawX(androidEvent, i);
                        float rawY = AMotionEvent_getRawY(androidEvent, i);
                        float x = AMotionEvent_getX(androidEvent, i);
                        float y = AMotionEvent_getY(androidEvent, i);
                        float pressure = AMotionEvent_getPressure(androidEvent, i);
                        float size = AMotionEvent_getSize(androidEvent, i);
                        float touchMajor = AMotionEvent_getTouchMajor(androidEvent, i);
                        float touchMinor = AMotionEvent_getTouchMinor(androidEvent, i);
                        float toolMajor = AMotionEvent_getToolMajor(androidEvent, i);
                        float toolMinor = AMotionEvent_getToolMinor(androidEvent, i);
                        float orientation = AMotionEvent_getOrientation(androidEvent, i);

                        LOGI ("  POINTER(%d) : raw=(%.2f, %.2f), pos=(%.2f, %.2f), pressure=%.2f, size=%.2f, touch=(%.2f, %.2f), tool=(%.2f, %.2f), orient=%.2f",
                                        i, rawX, rawY, x, y, pressure, size, touchMajor, touchMinor, toolMajor, toolMinor, orientation);
                }

        }
}

static std::string actionToString (int32_t action)
{
        switch (action & AMOTION_EVENT_ACTION_MASK) {
        case AMOTION_EVENT_ACTION_DOWN:
                return "AMOTION_EVENT_ACTION_DOWN";

        case AMOTION_EVENT_ACTION_UP:
                return "AMOTION_EVENT_ACTION_UP";

        case AMOTION_EVENT_ACTION_MOVE:
                return "AMOTION_EVENT_ACTION_MOVE";

        case AMOTION_EVENT_ACTION_CANCEL:
                return "AMOTION_EVENT_ACTION_CANCEL";

        case AMOTION_EVENT_ACTION_OUTSIDE:
                return "AMOTION_EVENT_ACTION_OUTSIDE";

        case AMOTION_EVENT_ACTION_POINTER_DOWN:
                return "AMOTION_EVENT_ACTION_POINTER_DOWN (" + boost::lexical_cast <std::string> (action & AMOTION_EVENT_ACTION_POINTER_INDEX_MASK) + ")";

        case AMOTION_EVENT_ACTION_POINTER_UP:
                return "AMOTION_EVENT_ACTION_POINTER_UP (" + boost::lexical_cast <std::string> (action & AMOTION_EVENT_ACTION_POINTER_INDEX_MASK) + ")";

        default:
                return "UNKNOWN";
        }
}

static std::string flagsToString (int32_t flags)
{
        if (flags == AMOTION_EVENT_FLAG_WINDOW_IS_OBSCURED) {
                return "AMOTION_EVENT_FLAG_WINDOW_IS_OBSCURED";
        }

        return "UNKNOWN";
}

static std::string metaStateToString (int32_t metaState)
{
        switch (metaState) {
        case AMETA_NONE:
                return "AMETA_NONE";

        case AMETA_ALT_ON:
                return "AMETA_ALT_ON";

        case AMETA_ALT_LEFT_ON:
                return "AMETA_ALT_LEFT_ON";

        case AMETA_ALT_RIGHT_ON:
                return "AMETA_ALT_RIGHT_ON";

        case AMETA_SHIFT_ON:
                return "AMETA_SHIFT_ON";

        case AMETA_SHIFT_LEFT_ON:
                return "AMETA_SHIFT_LEFT_ON";

        case AMETA_SHIFT_RIGHT_ON:
                return "AMETA_SHIFT_RIGHT_ON";

        case AMETA_SYM_ON:
                return "AMETA_SYM_ON";

        default:
                return "UNKNOWN";
        }
}

static std::string edgeFlagsToString (int32_t edgeFlags)
{
        switch (edgeFlags) {
        case AMOTION_EVENT_EDGE_FLAG_NONE:
                return "AMOTION_EVENT_EDGE_FLAG_NONE";

        case AMOTION_EVENT_EDGE_FLAG_TOP:
                return "AMOTION_EVENT_EDGE_FLAG_TOP";

        case AMOTION_EVENT_EDGE_FLAG_BOTTOM:
                return "AMOTION_EVENT_EDGE_FLAG_BOTTOM";

        case AMOTION_EVENT_EDGE_FLAG_LEFT:
                return "AMOTION_EVENT_EDGE_FLAG_LEFT";

        case AMOTION_EVENT_EDGE_FLAG_RIGHT:
                return "AMOTION_EVENT_EDGE_FLAG_RIGHT";

        default:
                return "UNKNOWN";
        }
}
