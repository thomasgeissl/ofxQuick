#pragma once
#include "./js.h"
namespace ofxQuick
{
    class listener
    {
    public:
        virtual void onRegisterCustomBindings(){}
        virtual void onFileLoaded(std::string &file){}
    };
};