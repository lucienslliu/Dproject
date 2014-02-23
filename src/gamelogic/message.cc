//------------------------------------------------------------------------------
//  message.cc
//  (C) 2006 Radon Labs GmbH
//------------------------------------------------------------------------------

#include "stdlogic.h"
#include "message.h"

ImplementMsgId(Message)

//------------------------------------------------------------------------------
/**
*/
Message::Message() :
    handled(false)
{
    // empty
}

//------------------------------------------------------------------------------
/**
void
Message::Encode(const Ptr<IO::BinaryWriter>& writer)
{
    // empty
}
*/

//------------------------------------------------------------------------------
/**
void
Message::Decode(const Ptr<IO::BinaryReader>& reader)
{
    // empty
}
*/
