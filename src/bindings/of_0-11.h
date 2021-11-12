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

            JS_SetPropertyStr(ctx, of, "getFrameNum", JS_NewCFunction(
                                                          ctx, [](JSContext *ctx, JSValueConst jsThis, int argc, JSValueConst *argv) -> JSValue
                                                          { return JS_NewInt64(ctx, ofGetFrameNum()); },
                                                          "getFrameNum", 0));
            JS_SetPropertyStr(ctx, of, "getFrameRate", JS_NewCFunction(
                                                           ctx, [](JSContext *ctx, JSValueConst jsThis, int argc, JSValueConst *argv) -> JSValue
                                                           { return JS_NewFloat64(ctx, ofGetFrameRate()); },
                                                           "getFrameRate", 0));
            JS_SetPropertyStr(ctx, of, "getHeight", JS_NewCFunction(
                                                        ctx, [](JSContext *ctx, JSValueConst jsThis, int argc, JSValueConst *argv) -> JSValue
                                                        { return JS_NewInt32(ctx, ofGetHeight()); },
                                                        "getHeight", 0));
            JS_SetPropertyStr(ctx, of, "getLastFrameTime", JS_NewCFunction(
                                                               ctx, [](JSContext *ctx, JSValueConst jsThis, int argc, JSValueConst *argv) -> JSValue
                                                               { return JS_NewFloat64(ctx, ofGetLastFrameTime()); },
                                                               "getLastFrameTime", 0));
            JS_SetPropertyStr(ctx, of, "getScreenHeight", JS_NewCFunction(
                                                              ctx, [](JSContext *ctx, JSValueConst jsThis, int argc, JSValueConst *argv) -> JSValue
                                                              { return JS_NewInt32(ctx, ofGetScreenHeight()); },
                                                              "getScreenHeight", 0));

            JS_SetPropertyStr(ctx, of, "getTargetFrameRate", JS_NewCFunction(
                                                                 ctx, [](JSContext *ctx, JSValueConst jsThis, int argc, JSValueConst *argv) -> JSValue
                                                                 { return JS_NewFloat64(ctx, ofGetTargetFrameRate()); },
                                                                 "getScreenHeight", 0));

            JS_SetPropertyStr(ctx, of, "getWidth", JS_NewCFunction(
                                                       ctx, [](JSContext *ctx, JSValueConst jsThis, int argc, JSValueConst *argv) -> JSValue
                                                       { return JS_NewInt32(ctx, ofGetWidth()); },
                                                       "getWidth", 0));

            JS_SetPropertyStr(ctx, of, "getWindowHeight", JS_NewCFunction(
                                                              ctx, [](JSContext *ctx, JSValueConst jsThis, int argc, JSValueConst *argv) -> JSValue
                                                              { return JS_NewInt32(ctx, ofGetWindowHeight()); },
                                                              "getWindowHeight", 0));
            JS_SetPropertyStr(ctx, of, "getWindowPositionX", JS_NewCFunction(
                                                                 ctx, [](JSContext *ctx, JSValueConst jsThis, int argc, JSValueConst *argv) -> JSValue
                                                                 { return JS_NewInt32(ctx, ofGetWindowPositionX()); },
                                                                 "getWindowPositionX", 0));
            JS_SetPropertyStr(ctx, of, "getWindowPositionY", JS_NewCFunction(
                                                                 ctx, [](JSContext *ctx, JSValueConst jsThis, int argc, JSValueConst *argv) -> JSValue
                                                                 { return JS_NewInt32(ctx, ofGetWindowPositionY()); },
                                                                 "getWindowPositionY", 0));
            JS_SetPropertyStr(ctx, of, "getWindowRect", JS_NewCFunction(
                                                            ctx, [](JSContext *ctx, JSValueConst jsThis, int argc, JSValueConst *argv) -> JSValue
                                                            {
                                                                auto value = ofGetWindowRect();
                                                                auto jsValue = JS_NewObject(ctx);
                                                                JS_SetPropertyStr(ctx, jsValue, "x", JS_NewInt32(ctx, value.x));
                                                                JS_SetPropertyStr(ctx, jsValue, "y", JS_NewInt32(ctx, value.y));
                                                                JS_SetPropertyStr(ctx, jsValue, "width", JS_NewInt32(ctx, value.width));
                                                                JS_SetPropertyStr(ctx, jsValue, "height", JS_NewInt32(ctx, value.height));
                                                                return jsValue;
                                                            },
                                                            "getWindowRect", 0));
            JS_SetPropertyStr(ctx, of, "getWindowSize", JS_NewCFunction(
                                                            ctx, [](JSContext *ctx, JSValueConst jsThis, int argc, JSValueConst *argv) -> JSValue
                                                            {
                                                                auto value = ofGetWindowSize();
                                                                auto jsValue = JS_NewObject(ctx);
                                                                JS_SetPropertyStr(ctx, jsValue, "width", JS_NewInt32(ctx, value.x));
                                                                JS_SetPropertyStr(ctx, jsValue, "height", JS_NewInt32(ctx, value.y));
                                                                return jsValue;
                                                            },
                                                            "getWindowSize", 0));
            JS_SetPropertyStr(ctx, of, "getWindowWidth", JS_NewCFunction(
                                                             ctx, [](JSContext *ctx, JSValueConst jsThis, int argc, JSValueConst *argv) -> JSValue
                                                             { return JS_NewInt32(ctx, ofGetWindowWidth()); },
                                                             "getWindowWidth", 0));
            JS_SetPropertyStr(ctx, of, "hideCursor", JS_NewCFunction(
                                                         ctx, [](JSContext *ctx, JSValueConst jsThis, int argc, JSValueConst *argv) -> JSValue
                                                         {
                                                             ofHideCursor();
                                                             return JS_UNDEFINED;
                                                         },
                                                         "hideCursor", 0));
            JS_SetPropertyStr(ctx, of, "randomHeight", JS_NewCFunction(
                                                           ctx, [](JSContext *ctx, JSValueConst jsThis, int argc, JSValueConst *argv) -> JSValue
                                                           { return JS_NewInt32(ctx, ofRandomHeight()); },
                                                           "randomHeight", 0));
            JS_SetPropertyStr(ctx, of, "randomWidth", JS_NewCFunction(
                                                          ctx, [](JSContext *ctx, JSValueConst jsThis, int argc, JSValueConst *argv) -> JSValue
                                                          { return JS_NewInt32(ctx, ofRandomWidth()); },
                                                          "randomWidth", 0));
            JS_SetPropertyStr(ctx, of, "setClipboardString", JS_NewCFunction(
                                                                 ctx, [](JSContext *ctx, JSValueConst jsThis, int argc, JSValueConst *argv) -> JSValue
                                                                 {
                                                                     auto value = JS_ToCString(ctx, argv[0]);
                                                                     ofSetClipboardString(value);
                                                                     return JS_UNDEFINED;
                                                                 },
                                                                 "setClipboardString", 1));

            JS_SetPropertyStr(ctx, of, "setEscapeQuitsApp", JS_NewCFunction(
                                                                ctx, [](JSContext *ctx, JSValueConst jsThis, int argc, JSValueConst *argv) -> JSValue
                                                                {
                                                                    auto value = JS_ToBool(ctx, argv[0]);
                                                                    ofSetEscapeQuitsApp(value);
                                                                    return JS_UNDEFINED;
                                                                },
                                                                "setEscapeQuitsApp", 1));

            JS_SetPropertyStr(ctx, of, "setFrameRate", JS_NewCFunction(
                                                           ctx, [](JSContext *ctx, JSValueConst jsThis, int argc, JSValueConst *argv) -> JSValue
                                                           {
                                                               double value;
                                                               JS_ToFloat64(ctx, &value, argv[0]);
                                                               ofSetFrameRate(value);
                                                               return JS_UNDEFINED;
                                                           },
                                                           "setFrameRate", 1));

            JS_SetPropertyStr(ctx, of, "setFullScreen", JS_NewCFunction(
                                                            ctx, [](JSContext *ctx, JSValueConst jsThis, int argc, JSValueConst *argv) -> JSValue
                                                            {
                                                                auto value = JS_ToBool(ctx, argv[0]);
                                                                ofSetFullScreen(value);
                                                                return JS_UNDEFINED;
                                                            },
                                                            "setFullScreen", 1));
            JS_SetPropertyStr(ctx, of, "setVerticalSync", JS_NewCFunction(
                                                              ctx, [](JSContext *ctx, JSValueConst jsThis, int argc, JSValueConst *argv) -> JSValue
                                                              {
                                                                  auto value = JS_ToBool(ctx, argv[0]);
                                                                  ofSetVerticalSync(value);
                                                                  return JS_UNDEFINED;
                                                              },
                                                              "setVerticalSync", 1));
            JS_SetPropertyStr(ctx, of, "setWindowPosition", JS_NewCFunction(
                                                                ctx, [](JSContext *ctx, JSValueConst jsThis, int argc, JSValueConst *argv) -> JSValue
                                                                {
                                                                    int x, y;
                                                                    JS_ToInt32(ctx, &x, argv[0]);
                                                                    JS_ToInt32(ctx, &y, argv[1]);
                                                                    ofSetWindowPosition(x, y);
                                                                    return JS_UNDEFINED;
                                                                },
                                                                "setWindowPosition", 2));
            JS_SetPropertyStr(ctx, of, "setWindowShape", JS_NewCFunction(
                                                             ctx, [](JSContext *ctx, JSValueConst jsThis, int argc, JSValueConst *argv) -> JSValue
                                                             {
                                                                 int width, height;
                                                                 JS_ToInt32(ctx, &width, argv[0]);
                                                                 JS_ToInt32(ctx, &height, argv[1]);
                                                                 ofSetWindowShape(width, height);
                                                                 return JS_UNDEFINED;
                                                             },
                                                             "setWindowShape", 2));

            JS_SetPropertyStr(ctx, of, "setWindowTitle", JS_NewCFunction(
                                                             ctx, [](JSContext *ctx, JSValueConst jsThis, int argc, JSValueConst *argv) -> JSValue
                                                             {
                                                                 auto value = JS_ToCString(ctx, argv[0]);
                                                                 ofSetWindowTitle(value);
                                                                 return JS_UNDEFINED;
                                                             },
                                                             "setWindowTitle", 1));
            JS_SetPropertyStr(ctx, of, "showCursor", JS_NewCFunction(
                                                         ctx, [](JSContext *ctx, JSValueConst jsThis, int argc, JSValueConst *argv) -> JSValue
                                                         {
                                                             ofShowCursor();
                                                             return JS_UNDEFINED;
                                                         },
                                                         "showCursor", 0));
            JS_SetPropertyStr(ctx, of, "toggleFullscreen", JS_NewCFunction(
                                                               ctx, [](JSContext *ctx, JSValueConst jsThis, int argc, JSValueConst *argv) -> JSValue
                                                               {
                                                                   ofToggleFullscreen();
                                                                   return JS_UNDEFINED;
                                                               },
                                                               "toggleFullscreen", 0));

            // JS_FreeValue(ctx, global);
            // JS_FreeValue(ctx, of);
        }
    };
};
