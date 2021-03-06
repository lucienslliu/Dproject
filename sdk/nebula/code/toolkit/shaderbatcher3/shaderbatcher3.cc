//------------------------------------------------------------------------------
//  shaderbatcher3.cc
//  (C) 2008 Radon Labs GmbH
//------------------------------------------------------------------------------
#include "stdneb.h"
#include "shaderbatcherapp.h"

//------------------------------------------------------------------------------
/**
*/
void __cdecl
main(int argc, const char** argv)
{
    Util::CmdLineArgs args(argc, argv);
    Toolkit::ShaderBatcherApp app;
    app.SetCompanyName("Radon Labs GmbH");
    app.SetAppName("Nebula3 Shader Batch Compiler");
    app.SetCmdLineArgs(args);
    if (app.Open())
    {
        app.Run();
        app.Close();
    }
    app.Exit();
}
