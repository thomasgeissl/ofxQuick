#include "./js.h"

void ofxQuick::js::saveContext()
{
    _savedCtx = JS_DupContext(_ctx);
}