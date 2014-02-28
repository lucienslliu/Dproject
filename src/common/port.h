#pragma once

#include "message.h"
#include "std_head.h"

class Port
{
public:
	Port() {};
	~Port() {};

public:
	/// override to register accepted messages
	virtual void SetupAcceptedMessages();
	/// send a message to the port
	//virtual void Send(const Ptr<iMessage>& msg);
	/// get the array of accepted messages (sorted)
	const std::vector<const ID*>& GetAcceptedMessages() const;    
	/// return true if port accepts this msg
	bool AcceptsMessage(const ID& msgId) const;
	/// handle a single accepted message
	virtual void HandleMessage(const Ptr<Message>& msg);

protected:
	/// register a single accepted message
	void RegisterMessage(const ID& msgId);

private:
	std::vector<const ID*> acceptedMessageIds;
};

//------------------------------------------------------------------------------
/**
*/
inline
void
Port::RegisterMessage(const ID& msgId)
{
	// ignore duplicate message ids (may happen when derived classes
	// process the same messages)
	if (true == AcceptsMessage(msgId))
	{
		this->acceptedMessageIds.push_back(&msgId);
	}
}

//------------------------------------------------------------------------------
/**
*/
inline
const std::vector<const ID*>&
Port::GetAcceptedMessages() const
{
	return this->acceptedMessageIds;
}

//------------------------------------------------------------------------------
/**
*/
inline
bool 
Port::AcceptsMessage(const ID& msgId) const
{
	return (this->acceptedMessageIds.end() != std::find(
		this->acceptedMessageIds.begin(), this->acceptedMessageIds.end(), &msgId));
}
