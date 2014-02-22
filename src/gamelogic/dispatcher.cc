//------------------------------------------------------------------------------
//  message/dispatcher.cc
//  (C) 2005 RadonLabs GmbH
//------------------------------------------------------------------------------
#include "stdlogic.h"
#include "dispatcher.h"

//------------------------------------------------------------------------------
/**
*/
Dispatcher::Dispatcher() :
    idPorts(64, 64)
{
    // empty
}

//------------------------------------------------------------------------------
/**
    Attach a new message port.

    @param  port    pointer to a message port object
*/
void
Dispatcher::AttachPort(const Ptr<Port>& port)
{
    ASSERT(port);
    ASSERT(!this->HasPort(port));

    // add to port array
    this->portArray.push_back(port);

    // get the array of accepted messages from the port, and add each message
    // to our own accepted messages, and create a mapping of message ids to ports
	const std::vector<const ID*>& idArray = port->GetAcceptedMessages();
    for (unsigned i = 0; i < idArray.size(); i++)
    {
        const ID* msgIdPtr = idArray[i];
        this->RegisterMessage(*msgIdPtr);
        if (this->idPortMap.end() != this->idPortMap.find(msgIdPtr))
        {
            // need to add a new empty entry
            std::vector<Ptr<Port> > emptyArray;
            this->idPorts.push_back(emptyArray);
			this->idPortMap.insert(std::make_pair(msgIdPtr, this->idPorts.size() - 1));
        }
        this->idPorts[this->idPortMap[msgIdPtr]].push_back(port);
    }
}

//------------------------------------------------------------------------------
/**
    Remove a message port object.

    @param  handler     pointer to message port object to be removed
*/
void
Dispatcher::RemovePort(const Ptr<Port>& port)
{
    ASSERT(0 != port);
    ASSERT(this->HasPort(port));

    // remove the port from the id/port map
    const std::vector<const ID*>& idArray = port->GetAcceptedMessages();
    for (unsigned i = 0; i < idArray.size(); i++)
    {
        const ID* msgIdPtr = idArray[i];
        if (this->idPortMap.end() != this->idPortMap.find(msgIdPtr))
        {            
            std::vector<Ptr<Port> >& ports = this->idPorts[this->idPortMap[msgIdPtr]];
			std::vector<Ptr<Port> >::iterator it = std::find_if(ports.begin(), ports.end(), port);
            ASSERT(ports.end() != it);
            ports.erase(it);
        }        
    }

    // NOTE: there's no way to remove the message from our accepted messages,
    // so that's not a bug!

    // finally remove the port from the ports array
	std::vector<Ptr<Port> >::iterator it = std::find_if(this->portArray.begin(), this->portArray.end(), port);
    ASSERT(this->portArray.end() != it);
    this->portArray.erase(it);
}

//------------------------------------------------------------------------------
/**
    Return true if a port is already attached.
*/
bool
Dispatcher::HasPort(const Ptr<Port>& port) const
{
	ASSERT(0 != port);
	std::vector<Ptr<Port> >::const_iterator it = std::find_if(this->portArray.begin(), this->portArray.end(), port);
    return (this->portArray.end() != it);
}

//------------------------------------------------------------------------------
/**
    Handle a message. The message will only be distributed to ports
    which accept the message.
*/
void
Dispatcher::HandleMessage(const Ptr<iMessage>& msg)
{
    const ID* msgIdPtr = &(msg->GetID());
	std::map<const ID*, int>::iterator it = this->idPortMap.find(msgIdPtr);
    if (this->idPortMap.end() != it)
    {
        const std::vector<Ptr<Port> >& portArray = this->idPorts[it->second];
        unsigned portIndex;
        for (portIndex = 0; portIndex < portArray.size(); portIndex++)
        {
            portArray[portIndex]->HandleMessage(msg);
        }
    }
}
