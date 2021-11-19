#pragma once
#include "./js.h"
static void registerEvents(JSContext *ctx)
{
    JSValue global = JS_GetGlobalObject(ctx);
    auto of = JS_GetPropertyStr(ctx, global, "of");

    JS_SetPropertyStr(ctx, of, "getMouseX", JS_NewCFunction(
                                                  ctx, [](JSContext *ctx, JSValueConst jsThis, int argc, JSValueConst *argv) -> JSValue
                                                  { return JS_NewInt32(ctx, ofGetMouseX()); },
                                                  "getMouseX", 0));
    JS_SetPropertyStr(ctx, of, "getMouseY", JS_NewCFunction(
                                                  ctx, [](JSContext *ctx, JSValueConst jsThis, int argc, JSValueConst *argv) -> JSValue
                                                  { return JS_NewInt32(ctx, ofGetMouseY()); },
                                                  "getMouseY", 0));
    // JS_SetPropertyStr(ctx, of, "getFrameRate", JS_NewCFunction(
    //                                                ctx, [](JSContext *ctx, JSValueConst jsThis, int argc, JSValueConst *argv) -> JSValue
    //                                                { return JS_NewFloat64(ctx, ofGetFrameRate()); },
    //                                                "getFrameRate", 0));
    // JS_SetPropertyStr(ctx, of, "getHeight", JS_NewCFunction(
    //                                             ctx, [](JSContext *ctx, JSValueConst jsThis, int argc, JSValueConst *argv) -> JSValue
    //                                             { return JS_NewInt32(ctx, ofGetHeight()); },
    //                                             "getHeight", 0));
    // JS_SetPropertyStr(ctx, of, "getLastFrameTime", JS_NewCFunction(
    //                                                    ctx, [](JSContext *ctx, JSValueConst jsThis, int argc, JSValueConst *argv) -> JSValue
    //                                                    { return JS_NewFloat64(ctx, ofGetLastFrameTime()); },
    //                                                    "getLastFrameTime", 0));

    // JS_FreeValue(ctx, global);
    // JS_FreeValue(ctx, of);
}
