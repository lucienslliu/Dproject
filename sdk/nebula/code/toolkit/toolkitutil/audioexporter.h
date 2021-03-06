#pragma once
//------------------------------------------------------------------------------
/**
    @class ToolkitUtil::AudioExporter
    
    Multiplatform batch exporter class for audio content.
    
    (C) 2008 Radon Labs GmbH
*/
#include "toolkitutil/platform.h"
#include "util/string.h"

//------------------------------------------------------------------------------
namespace ToolkitUtil
{
class AudioExporter
{
public:
    /// constructor
    AudioExporter();
    /// destructor
    ~AudioExporter();
    
    /// set target platform
    void SetPlatform(Platform::Code platform);
    /// set path to exporter tool
    void SetToolPath(const Util::String& toolPath);
    /// set force conversion flag (otherwise check timestamps)
    void SetForceFlag(bool b);
    /// set path to XACT project file
    void SetProjectFile(const Util::String& projectFile);
    /// set destination path
    void SetDstDir(const Util::String& dstDir);

    /// perform export
    bool Export();

private:
    /// export for Win32 or Xbox360 platform
    bool ExportWin360();

    Platform::Code platform;
    Util::String toolPath;
    Util::String projectFile;
    Util::String dstDir;
    bool force;
};

//------------------------------------------------------------------------------
/**
*/
inline void
AudioExporter::SetPlatform(Platform::Code p)
{
    this->platform = p;
}

//------------------------------------------------------------------------------
/**
*/
inline void
AudioExporter::SetForceFlag(bool b)
{
    this->force = b;
}

//------------------------------------------------------------------------------
/**
*/
inline void
AudioExporter::SetToolPath(const Util::String& p)
{
    this->toolPath = p;
}

//------------------------------------------------------------------------------
/**
*/
inline void
AudioExporter::SetProjectFile(const Util::String& f)
{
    this->projectFile = f;
}

//------------------------------------------------------------------------------
/**
*/
inline void
AudioExporter::SetDstDir(const Util::String& d)
{
    this->dstDir = d;
}

} // namespace ToolkitUtil
//------------------------------------------------------------------------------
    