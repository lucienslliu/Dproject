//------------------------------------------------------------------------------
//  buildresdict3.cc
//  (C) 2008 Radon Labs GmbH
//------------------------------------------------------------------------------
#include "stdneb.h"
#include "resourcedictionaryapp.h"

//------------------------------------------------------------------------------
/**
*/
void __cdecl
main(int argc, const char** argv)
{
    Util::CmdLineArgs args(argc, argv);
    Toolkit:: ResourceDictionaryApp app;
    app.SetCompanyName("Radon Labs GmbH");
    app.SetAppName("Nebula3 Resource Dictionary Builder");
    app.SetCmdLineArgs(args);
    if (app.Open())
    {
        app.Run();
        app.Close();
    }
    app.Exit();
}
