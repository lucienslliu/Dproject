//------------------------------------------------------------------------------
//  textrenderer.cc
//  (C) 2008 Radon Labs GmbH
//------------------------------------------------------------------------------
#include "stdneb.h"
#include "coregraphics/textrenderer.h"

namespace CoreGraphics
{
#if __WIN32__
__ImplementClass(CoreGraphics::TextRenderer, 'TXRR', Direct3D9::D3D9TextRenderer);
#elif __XBOX360__
__ImplementClass(CoreGraphics::TextRenderer, 'TXRR', Xbox360::Xbox360TextRenderer);
//#elif __WII__
//__ImplementClass(CoreGraphics::TextRenderer, 'DTXR', Wii::WiiTextRenderer);
#else
#error "TextRenderer class not implemented on this platform!"
#endif

__ImplementSingleton(CoreGraphics::TextRenderer);

//------------------------------------------------------------------------------
/**
*/
TextRenderer::TextRenderer()
{
    __ConstructSingleton;
}

//------------------------------------------------------------------------------
/**
*/
TextRenderer::~TextRenderer()
{
    __DestructSingleton;
}

} // namespace CoreGraphics
