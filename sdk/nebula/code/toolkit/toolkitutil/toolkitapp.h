#pragma once
//------------------------------------------------------------------------------
/**
    @class ToolkitUtil::ToolkitApp
    
    Base class for typical toolkit command line tools. Only provides a
    few helper methods, the actual application still must provide the
    complete Run() method.
    
    (C) 2008 Radon Labs GmbH
*/
#include "app/consoleapplication.h"
#include "toolkitutil/projectinfo.h"
#include "toolkitutil/platform.h"

//------------------------------------------------------------------------------
namespace ToolkitUtil
{
class ToolkitApp : public App::ConsoleApplication
{
public:
    /// constructor
    ToolkitApp();

protected:
    /// parse command line arguments
    virtual bool ParseCmdLineArgs();
    /// setup project info object
    virtual bool SetupProjectInfo();
    /// print help text
    virtual void ShowHelp();

    ProjectInfo projectInfo;
    Platform::Code platform;
    bool waitForKey;
};

} // namespace ToolkitUtil
//------------------------------------------------------------------------------
