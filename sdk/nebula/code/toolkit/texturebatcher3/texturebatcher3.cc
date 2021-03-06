//------------------------------------------------------------------------------
//  texturebatcher3.cc
//  (C) 2008 Radon Labs GmbH
//------------------------------------------------------------------------------
#include "stdneb.h"
#include "texturebatcherapp.h"

//------------------------------------------------------------------------------
/**
*/
void __cdecl
main(int argc, const char** argv)
{
    Util::CmdLineArgs args(argc, argv);
    Toolkit::TextureBatcherApp app;
    app.SetCompanyName("Radon Labs GmbH");
    app.SetAppName("Nebula3 Texture Batch Converter");
    app.SetCmdLineArgs(args);
    if (app.Open())
    {
        app.Run();
        app.Close();
    }
    app.Exit();
}
