#pragma once
#ifndef DEBUG_RENDERCONSOLEHANDLER_H
#define DEBUG_RENDERCONSOLEHANDLER_H
//------------------------------------------------------------------------------
/**
    @class Render::RenderConsoleHandler
    
    Outputs the console. Saves all output texts which go to the standard console 
    and renders it on screen.
    Allows scrolling with up and down arrow keys.
    
    (C) 2008 Radon Labs GmbH
*/
#include "io/consolehandler.h"
#include "util/list.h"

//------------------------------------------------------------------------------
namespace Debug
{
class RenderConsoleHandler : public IO::ConsoleHandler
{
    __DeclareClass(RenderConsoleHandler);
public:
    /// constructor
    RenderConsoleHandler();
    
    /// called by console to output data
    virtual void Print(const Util::String& s);
    /// called by console with serious error
    virtual void Error(const Util::String& s);
    /// called by console to output warning
    virtual void Warning(const Util::String& s);
    /// called by console to output debug string
    virtual void DebugOut(const Util::String& s);
    /// called by Console::Update()
    virtual void Update();

private:
    Util::List<Util::String> linebuffer;
    uint bufferSize;
    uint linesVisible;
    int curIndex;
};

}; // namespace Render
//------------------------------------------------------------------------------
#endif