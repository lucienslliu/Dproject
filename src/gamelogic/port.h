#pragma once

#include "imessage.h"

class Port
{
public:
	Port();
	~Port();

public:
	/// override to register accepted messages
	virtual void SetupAcceptedMessages();
	/// send a message to the port
	virtual void Send(const Ptr<iMessage>& msg);
	/// get the array of accepted messages (sorted)
	const std::vector<const ID*>& GetAcceptedMessages() const;    
	/// return true if port accepts this msg
	bool AcceptsMessage(const ID& msgId) const;
	/// handle a single accepted message
	virtual void HandleMessage(const Ptr<iMessage>& msg);

protected:
	/// register a single accepted message
	void RegisterMessage(const ID& msgId);

private:
	std::vector<const ID*> acceptedMessageIds;
};
