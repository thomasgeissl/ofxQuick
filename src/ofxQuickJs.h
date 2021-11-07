#pragma once
#include "../libs/quickjs/quickjs.h"
#include "../libs/quickjs/quickjs-libc.h"
// https://linuxtut.com/en/16cdbc69d4fd4a3dccbf/

class ofxQuickJs
{
public:
    inline static std::map<int, void *> _map;
    ofxQuickJs()
    {
        _rt = JS_NewRuntime();
        _ctx = JS_NewContext(_rt);
        JS_SetContextOpaque(_ctx, (void *) this);
        registerStdAndOsModules();
        registerConsole();
	    registerTest();
    }
    ~ofxQuickJs()
    {
        JS_FreeContext(_ctx);
        JS_FreeRuntime(_rt);
    }

    void setup(std::string path)
    {
        loadFileAndWatch(path);
    }
    void update()
    {
    }
    void draw()
    {
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

        ofLogVerbose("ofxQuickJs") << "successfull loaded js file";
        evaluate(data);
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
        // JSValue argv[] = {JS_NewInt32(_ctx, 5), JS_NewInt32(_ctx, 3)};
        JSValue argv[] = {};
        return JS_Call(_ctx, fun, global, sizeof(argv) / sizeof(JSValue), argv);
    }
    int callInt(std::string name, std::vector<JSValue> args = {})
    {
        auto value = call(name, args);
        int32_t result;
        JS_ToInt32(_ctx, &result, value);
        return result;
    }
    void test()
    {
        // std::string jsCode = "function foo(x, y) { return x + y; }";
        // evaluate(jsCode);
        // if (JS_IsException(JS_Eval(_ctx, fooCode, strlen(fooCode), "<input>", JS_EVAL_FLAG_STRICT)))
        // {
        //     JS_FreeContext(_ctx);
        //     JS_FreeRuntime(_rt);
        // }

        JSValue global = JS_GetGlobalObject(_ctx);
        JSValue foo = JS_GetPropertyStr(_ctx, global, "foo");
        JSValue argv[] = {JS_NewInt32(_ctx, 5), JS_NewInt32(_ctx, 3)};
        JSValue jsResult = JS_Call(_ctx, foo, global, sizeof(argv) / sizeof(JSValue), argv);
        int32_t result;
        JS_ToInt32(_ctx, &result, jsResult);
        ofLogNotice() << result;

        // JSValue used[] = {jsResult, argv[1], argv[0], foo, global};
        // for (int i = 0; i < sizeof(used) / sizeof(JSValue); ++i)
        // {
        //     JS_FreeValue(_ctx, used[i]);
        // }
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
    void registerMemberFunction(ListenerClass *listener, JSValue (ListenerClass::*listenerMethod)(JSContext *, JSValueConst, int, JSValueConst *))
    {
    }

    void registerFunction(std::string name, JSValue function)
    {
        JSValue global = JS_GetGlobalObject(_ctx);
        JS_SetPropertyStr(_ctx, global, name.c_str(), function);
    }
    void registerStdAndOsModules()
    {
        js_init_module_std(_ctx, "std");
        js_init_module_os(_ctx, "os");
    }
    int _magic;

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

    void registerTest()
    {
        JSValue global = JS_GetGlobalObject(_ctx);
        _map.insert( std::make_pair(_magic, this));
        JS_SetPropertyStr(_ctx, global, "test", JS_NewCFunctionMagic(_ctx, js_memmberfunction_wrapper_magic, "test", 0, JS_CFUNC_generic, _magic));
        _magic++;
        JS_FreeValue(_ctx, global);
    }

    JSContext *getContext()
    {
        return _ctx;
    }

    JSValue js_setTimeout(JSContext *ctx, JSValueConst thisVal, int argc, JSValueConst *argv)
    {
        return JS_EXCEPTION;
    }

    JSValue js_clearTimeout(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
    {
        return JS_EXCEPTION;
    }
	static JSValue js_memmberfunction_wrapper_magic(JSContext *ctx, JSValueConst jsThis, int argc, JSValueConst *argv, int magic){
        auto object = (ofxQuickJs *) (_map[magic]);
        return object->js_memberfunction(ctx, jsThis, argc, argv);
	}
    JSValue js_memberfunction(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv){
        ofLogNotice() << "member function";
        return JS_UNDEFINED;
    }

protected:
    JSRuntime *_rt;
    JSContext *_ctx;
    std::vector<std::string> _files;
};