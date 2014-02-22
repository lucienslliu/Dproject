#include "stdlogic.h"
#include "port.h"

//------------------------------------------------------------------------------
/**
*/
void Port::SetupAcceptedMessages()
{
    // overwrite in subclass
}

//------------------------------------------------------------------------------
/**
    Handle a specific message. Overwrite this method in a subclass.
    It is guaranteed that this method will only be called for messages
    which are accepted by AcceptMessage().
*/
void Port::HandleMessage(const Ptr<iMessage>& msg)
{
    // empty
}
