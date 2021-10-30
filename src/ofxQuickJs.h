#pragma once
#include "./quickjs/quickjs.h"
// https://linuxtut.com/en/16cdbc69d4fd4a3dccbf/

class ofxQuickJs
{
public:
    ofxQuickJs()
    {
        rt = JS_NewRuntime();
        ctx = JS_NewContext(rt);
    }
    ~ofxQuickJs()
    {
        JS_FreeContext(ctx);
        JS_FreeRuntime(rt);
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

    bool evaluate(std::string value)
    {
        auto cstring = value.c_str();
        return JS_IsException(JS_Eval(ctx, cstring, strlen(cstring), "<input>", JS_EVAL_FLAG_STRICT));
    }
    JSValue call(std::string name, std::vector<JSValue> args = {})
    {
        auto global = JS_GetGlobalObject(ctx);
        auto fun = JS_GetPropertyStr(ctx, global, name.c_str());
        // JSValue argv[] = {JS_NewInt32(ctx, 5), JS_NewInt32(ctx, 3)};
        JSValue argv[] = {};
        return JS_Call(ctx, fun, global, sizeof(argv) / sizeof(JSValue), argv);
    }
    int callInt(std::string name, std::vector<JSValue> args = {})
    {
        auto value = call(name, args);
        int32_t result;
        JS_ToInt32(ctx, &result, value);
        return result;
    }
    void test()
    {
        // std::string jsCode = "function foo(x, y) { return x + y; }";
        // evaluate(jsCode);
        // if (JS_IsException(JS_Eval(ctx, fooCode, strlen(fooCode), "<input>", JS_EVAL_FLAG_STRICT)))
        // {
        //     JS_FreeContext(ctx);
        //     JS_FreeRuntime(rt);
        // }

        JSValue global = JS_GetGlobalObject(ctx);
        JSValue foo = JS_GetPropertyStr(ctx, global, "foo");
        JSValue argv[] = {JS_NewInt32(ctx, 5), JS_NewInt32(ctx, 3)};
        JSValue jsResult = JS_Call(ctx, foo, global, sizeof(argv) / sizeof(JSValue), argv);
        int32_t result;
        JS_ToInt32(ctx, &result, jsResult);
        ofLogNotice() << result;

        // JSValue used[] = {jsResult, argv[1], argv[0], foo, global};
        // for (int i = 0; i < sizeof(used) / sizeof(JSValue); ++i)
        // {
        //     JS_FreeValue(ctx, used[i]);
        // }
    }

protected:
    JSRuntime *rt;
    JSContext *ctx;
    std::vector<std::string> _files;
};