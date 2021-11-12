#pragma once
#include "../libs/quickjs/quickjs.h"
#include "../libs/quickjs/quickjs-libc.h"
// https://linuxtut.com/en/16cdbc69d4fd4a3dccbf/

namespace ofxQuick
{

    class js
    {
    public:
        inline static std::vector<std::function<JSValue(JSContext *, JSValueConst, int, JSValueConst *)>> _fmap;
        js() : _checkInterval(100)
        {
            _rt = JS_NewRuntime();
            _ctx = JS_NewContext(_rt);
            JS_SetContextOpaque(_ctx, (void *)this);
            registerStdAndOsModules();
            registerConsole();
            registerProperty("test", JS_NewInt32(_ctx, 32));
        }
        ~js()
        {
            JS_FreeContext(_ctx);
            JS_FreeRuntime(_rt);
        }

        void setup(std::string path, bool liveReload = true)
        {
            loadFileAndWatch(path);
        }

        void update()
        {
            watchFiles();
        }

        void loadFileAndWatch(std::string path)
        {
            _files.push_back(path);
            ifstream myfile(ofToDataPath(path));
            std::string data;
            if (myfile.is_open())
            {
                std::string line;
                while (getline(myfile, line))
                {
                    data += line;
                    data += "\n";
                }
                myfile.close();
            }

            ofLogVerbose("ofxQuick::js") << "successfull loaded js file";
            evaluate(data);
        }

        void clear()
        {
            _files.clear();
        }

        JSValue evaluate(std::string code)
        {
            auto cstring = code.c_str();

            auto value = JS_Eval(_ctx, cstring, strlen(cstring), "<input>", JS_EVAL_FLAG_STRICT);
            if (JS_IsException(value))
            {
                auto ex = JS_GetException(_ctx);
                auto msg = JS_GetPropertyStr(_ctx, ex, "message");
                auto stack = JS_GetPropertyStr(_ctx, ex, "stack");
                ofLogError() << "could not evaluate\n"
                             << code;
                ofLogNotice() << JS_ToCString(_ctx, msg);
                ofLogNotice() << JS_ToCString(_ctx, stack);
                return JS_UNDEFINED;
            }
            return value;
        }
        JSValue call(std::string name, std::vector<JSValue> args = {})
        {
            auto global = JS_GetGlobalObject(_ctx);
            auto fun = JS_GetPropertyStr(_ctx, global, name.c_str());
            JSValue argv[args.size()];
            for (auto i = 0; i < args.size(); i++)
            {
                argv[i] = args[i];
            };
            return JS_Call(_ctx, fun, global, args.size(), argv);
        }
        int callInt(std::string name, std::vector<JSValue> args = {})
        {
            auto value = call(name, args);
            int32_t result;
            JS_ToInt32(_ctx, &result, value);
            return result;
        }

        static JSValue js_console_log(JSContext *ctx, JSValueConst jsThis, int argc, JSValueConst *argv)
        {
            for (int i = 0; i < argc; ++i)
            {
                const char *str = JS_ToCString(ctx, argv[i]);
                ofLogNotice() << str;
                JS_FreeCString(ctx, str);
            }
            return JS_UNDEFINED;
        }
        static JSValue js_console_warn(JSContext *ctx, JSValueConst jsThis, int argc, JSValueConst *argv)
        {
            for (int i = 0; i < argc; ++i)
            {
                const char *str = JS_ToCString(ctx, argv[i]);
                ofLogWarning() << str;
                JS_FreeCString(ctx, str);
            }
            return JS_UNDEFINED;
        }
        static JSValue js_console_error(JSContext *ctx, JSValueConst jsThis, int argc, JSValueConst *argv)
        {
            for (int i = 0; i < argc; ++i)
            {
                const char *str = JS_ToCString(ctx, argv[i]);
                ofLogError() << str;
                JS_FreeCString(ctx, str);
            }
            return JS_UNDEFINED;
        }

        template <class ListenerClass>
        void registerMemberFunction(std::string name, ListenerClass *listener, JSValue (ListenerClass::*memberFunction)(JSContext *, JSValueConst, int, JSValueConst *))
        {
            JSValue global = JS_GetGlobalObject(_ctx);
            ofxQuick::js::_fmap.push_back(std::bind(memberFunction, listener, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
            JS_SetPropertyStr(_ctx, global, name.c_str(), JS_NewCFunctionMagic(_ctx, js_memmberfunction_wrapper_magic, name.c_str(), 0, JS_CFUNC_generic_magic, ofxQuick::js::_fmap.size() - 1));
            JS_FreeValue(_ctx, global);
            ofLogVerbose("ofxQuick::js") << "successfully registered member function " << ofxQuick::js::_fmap.size() - 1;
        }

        void registerProperty(std::string name, JSValue value)
        {
            JSValue global = JS_GetGlobalObject(_ctx);
            JS_SetPropertyStr(_ctx, global, name.c_str(), value);
            JS_FreeValue(_ctx, global);
        }
        void registerStdAndOsModules()
        {
            js_init_module_std(_ctx, "std");
            js_init_module_os(_ctx, "os");
        }

        void registerConsole()
        {
            JSValue global = JS_GetGlobalObject(_ctx);
            JSValue console = JS_NewObject(_ctx);
            JS_SetPropertyStr(_ctx, global, "console", console);
            JS_SetPropertyStr(_ctx, console, "log", JS_NewCFunction(_ctx, js_console_log, "log", 1));
            JS_SetPropertyStr(_ctx, console, "warn", JS_NewCFunction(_ctx, js_console_warn, "warn", 1));
            JS_SetPropertyStr(_ctx, console, "error", JS_NewCFunction(_ctx, js_console_error, "error", 1));

            JS_FreeValue(_ctx, global);
        }

        JSContext *getContext()
        {
            return _ctx;
        }

        int getInt(std::string name){
            JSValue global = JS_GetGlobalObject(_ctx);
            auto value = JS_GetPropertyStr(_ctx, global, name.c_str());
            int32_t result;
            JS_ToInt32(_ctx, &result, value);
            return result;
        }
        int getFloat(std::string name){
            JSValue global = JS_GetGlobalObject(_ctx);
            auto value = JS_GetPropertyStr(_ctx, global, name.c_str());
            double result;
            JS_ToFloat64(_ctx, &result, value);
            return result;
        }
        std::string getString(std::string name){
            JSValue global = JS_GetGlobalObject(_ctx);
            auto value = JS_GetPropertyStr(_ctx, global, name.c_str());
            return JS_ToCString(_ctx, value);
        }

        JSValue js_setTimeout(JSContext *ctx, JSValueConst jsThis, int argc, JSValueConst *argv)
        {
            return JS_EXCEPTION;
        }

        JSValue js_clearTimeout(JSContext *ctx, JSValueConst jsThis, int argc, JSValueConst *argv)
        {
            return JS_EXCEPTION;
        }
        static JSValue js_memmberfunction_wrapper_magic(JSContext *ctx, JSValueConst jsThis, int argc, JSValueConst *argv, int index)
        {
            return ofxQuick::js::_fmap[index](ctx, jsThis, argc, argv);
        }

        std::time_t getTouchTimestamp(std::string path)
        {
            return std::filesystem::last_write_time(path);
        }
        void watchFiles()
        {
            if(_files.size() == 0){
                return;
            }
            int timestamp = ofGetElapsedTimeMillis();

            if (timestamp - _checkTimestamp > _checkInterval)
            {
                auto touchedTimestamp = getTouchTimestamp(_files[0]);
                if(touchedTimestamp > _touchedTimestamp){
                    clear();
                    loadFileAndWatch(_files[0]);
                    ofNotifyEvent(_fileReloadedEvent, _files[0], this); 
                    _touchedTimestamp = touchedTimestamp;
                }

                _checkTimestamp = timestamp;
            }
        }

        void setInt(std::string name, int value){
            registerProperty(name, JS_NewInt32(_ctx, value));
        }
        void setFloat(std::string name, float value){
            registerProperty(name, JS_NewFloat64(_ctx, value));
        }
        void setString(std::string name, std::string value){
            registerProperty(name, JS_NewString(_ctx, value.c_str()));
        }
        JSRuntime *_rt;
        JSContext *_ctx;
        std::vector<std::string> _files;
        int _checkTimestamp;
        int _checkInterval;
        int _touchedTimestamp;
        ofEvent<std::string> _fileReloadedEvent;
    };
};