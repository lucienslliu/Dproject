#pragma once
//------------------------------------------------------------------------------
/**
    @class Messaging::Message

    Messages are packets of data which can be sent to a message port.
    This implements a universal communication mechanism within the same
    thread, different threads, or even different machines.

    Messages are implemented as normal C++ objects which can encode and
    decode themselves from and to a stream.

    (C) 2006 Radon Labs GmbH
*/

//------------------------------------------------------------------------------
/**
    Message Id macros.
*/
#define DeclareMsgId \
public:\
    static ID Id; \
    virtual const ID& GetId() const;\
private:

#define ImplementMsgId(type) \
    ID type::Id; \
    const ID& type::GetId() const { return type::Id; }

class Port;
class Message
{
    //__DeclareClass(Message);
    DeclareMsgId;
public:
    /// constructor
    Message();
    /// return true if message is of the given id
    bool CheckId(const ID& id) const;
    /// encode message into a stream
    //virtual void Encode(const Ptr<IO::BinaryWriter>& writer);
    /// decode message from a stream
    //virtual void Decode(const Ptr<IO::BinaryReader>& reader);
    /// set the handled flag
    void SetHandled(bool b);
    /// return true if the message has been handled
    bool Handled() const;

protected:
    bool handled;
};

//------------------------------------------------------------------------------
/**
*/
inline bool
Message::CheckId(const ID& id) const
{
    return (id == this->GetId());
}

//------------------------------------------------------------------------------
/**
*/
inline void
Message::SetHandled(bool b)
{
    this->handled = b;
}

//------------------------------------------------------------------------------
/**
*/
inline bool
Message::Handled() const
{
    return this->handled;
}
