#pragma once

#if OF_VERSION_MAJOR == 0 && OF_VERSION_MINOR == 11
#include "./bindings/0-11/ofBindings.h"
#endif

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
            registerAppRunner(ctx);
            registerGraphics(ctx);
        }
    };
};