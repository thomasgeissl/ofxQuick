#pragma once
#include "ofMain.h"
#include "../libs/quickjs/quickjs.h"

#pragma once
#include "./js.h"
namespace ofxQuick
{
    class ofBindings
    {
    public:
        static void setup(JSContext *ctx)
        {
            JSValue global = JS_GetGlobalObject(ctx);
            JSValue of = JS_NewObject(ctx);
            JS_SetPropertyStr(ctx, global, "of", of);
            JS_SetPropertyStr(ctx, of, "setColor", JS_NewCFunction(
                                                       ctx, [](JSContext *ctx, JSValueConst jsThis, int argc, JSValueConst *argv) -> JSValue
                                                       {
                                                           ofColor color;
                                                           int32_t value;
                                                           JS_ToInt32(ctx, &value, argv[0]);
                                                           color.r = value;
                                                           JS_ToInt32(ctx, &value, argv[1]);
                                                           color.g = value;
                                                           JS_ToInt32(ctx, &value, argv[2]);
                                                           color.b = value;

                                                           ofSetColor(color);
                                                           return JS_UNDEFINED;
                                                       },
                                                       "setColor", 3));

            JS_SetPropertyStr(ctx, of, "drawRectangle", JS_NewCFunction(
                                                            ctx, [](JSContext *ctx, JSValueConst jsThis, int argc, JSValueConst *argv) -> JSValue
                                                            {
                                                                ofRectangle rectangle;
                                                                int32_t value;
                                                                JS_ToInt32(ctx, &value, argv[0]);
                                                                rectangle.x = value;
                                                                JS_ToInt32(ctx, &value, argv[1]);
                                                                rectangle.y = value;
                                                                JS_ToInt32(ctx, &value, argv[2]);
                                                                rectangle.width = value;
                                                                JS_ToInt32(ctx, &value, argv[3]);
                                                                rectangle.height = value;

                                                                ofDrawRectangle(rectangle);
                                                                return JS_UNDEFINED;
                                                            },
                                                            "drawRectangle", 4));
            // JS_FreeValue(ctx, global);
            // JS_FreeValue(ctx, of);
        }
    };
};
