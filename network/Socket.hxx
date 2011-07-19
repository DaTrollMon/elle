//
// ---------- header ----------------------------------------------------------
//
// project       elle
//
// license       infinit
//
// file          /home/mycure/infinit/elle/network/Socket.hxx
//
// created       julien quintard   [sun jul 17 15:39:02 2011]
// updated       julien quintard   [tue jul 19 11:35:15 2011]
//

#ifndef ELLE_NETWORK_SOCKET_HXX
#define ELLE_NETWORK_SOCKET_HXX

//
// ---------- includes --------------------------------------------------------
//

#include <elle/network/Channel.hh>
#include <elle/network/Slot.hh>

#include <elle/standalone/Maid.hh>
#include <elle/standalone/Report.hh>

namespace elle
{
  namespace network
  {

//
// ---------- methods ---------------------------------------------------------
//

    ///
    /// this method sends a packet in an asynchronous manner.
    ///
    template <typename I>
    Status		Socket::Send(const I			inputs,
				     const Event&		event,
				     const Address&		address)
    {
      enter();

      switch (this->type)
	{
	case Socket::TypeDoor:
	case Socket::TypeGate:
	  {
	    Channel*	socket = static_cast<Channel*>(this);

	    return (socket->Send(inputs, event));
	  }
	case Socket::TypeSlot:
	  {
	    Slot*	socket = static_cast<Slot*>(this);

	    return (socket->Send(address, inputs, event));
	  }
	default:
	  {
	    escape("unknown or unhandled socket type '%u'\n",
		   this->type);
	  }
	}

      escape("invalid socket type");
    }

    ///
    /// this method receives a packet by blocking.
    ///
    template <typename O>
    Status		Socket::Receive(const Event&		event,
					O			outputs)
    {
      enter();

      switch (this->type)
	{
	case Socket::TypeDoor:
	case Socket::TypeGate:
	  {
	    Channel*	socket = static_cast<Channel*>(this);

	    return (socket->Receive(event, outputs));
	  }
	case Socket::TypeSlot:
	  {
	    Slot*	socket = static_cast<Slot*>(this);

	    return (socket->Receive(event, outputs));
	  }
	default:
	  {
	    escape("unknown or unhandled socket type '%u'\n",
		   this->type);
	  }
	}

      leave();
    }

    ///
    /// this method sends and receives an associated response in a
    /// synchronous way.
    ///
    template <typename I,
	      typename O>
    Status		Socket::Call(const I			inputs,
				     O				outputs,
				     const Address&		address)
    {
      enter();

      switch (this->type)
	{
	case Socket::TypeDoor:
	case Socket::TypeGate:
	  {
	    Channel*	socket = static_cast<Channel*>(this);

	    return (socket->Call(inputs, outputs));
	  }
	case Socket::TypeSlot:
	  {
	    Slot*	socket = static_cast<Slot*>(this);

	    return (socket->Call(address, inputs, outputs));
	  }
	default:
	  {
	    escape("unknown or unhandled socket type '%u'\n",
		   this->type);
	  }
	}

      leave();
    }

    ///
    /// this method replies to the freshly received call.
    ///
    template <typename I>
    Status		Socket::Reply(const I			inputs,
				      Session*			session)
    {
      enter();

      switch (this->type)
	{
	case Socket::TypeDoor:
	case Socket::TypeGate:
	  {
	    Channel*	socket = static_cast<Channel*>(this);

	    return (socket->Reply(inputs, session));
	  }
	case Socket::TypeSlot:
	  {
	    Slot*	socket = static_cast<Slot*>(this);

	    return (socket->Reply(inputs, session));
	  }
	default:
	  {
	    escape("unknown or unhandled socket type '%u'",
		   this->type);
	  }
	}

      leave();
    }

  }
}

#endif
