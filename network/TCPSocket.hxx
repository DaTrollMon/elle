#ifndef ELLE_NETWORK_TCPSOCKET_HXX
#define ELLE_NETWORK_TCPSOCKET_HXX

#include <elle/idiom/Close.hh>
# include <reactor/scheduler.hh>
# include <reactor/thread.hh>
#include <elle/idiom/Open.hh>

#include <elle/concurrency/Event.hh>
#include <elle/concurrency/Program.hh>
#include <elle/standalone/Maid.hh>
#include <elle/standalone/Report.hh>

#include <elle/network/Packet.hh>
#include <elle/network/Header.hh>
#include <elle/network/Data.hh>
#include <elle/network/Parcel.hh>

#include <elle/Manifest.hh>

#include <elle/idiom/Close.hh>
#include <elle/log.hh>
#include <elle/idiom/Open.hh>

namespace elle
{
  namespace network
  {

//
// ---------- methods ---------------------------------------------------------
//

    ///
    /// this method sends a packet.
    ///
    template <typename I>
    Status              TCPSocket::Send(const I                 inputs,
                                        const Event&            event)
    {
      Packet            packet;
      Data              data;
      Header            header;

      // create an data for the inputs.
      if (data.Create() == StatusError)
        escape("unable to create the data");

      // serialize the inputs.
      if (inputs.Serialize(data) == StatusError)
        escape("unable to serialize the inputs");

      // create the header now that we know that final archive's size.
      if (header.Create(event,
                        inputs.tag,
                        data.size) == StatusError)
        escape("unable to create the header");

      // prepare the packet.
      if (packet.Create() == StatusError)
        escape("unable to create the packet");

      // serialize the the header and data.
      if (packet.Serialize(header, data) == StatusError)
        escape("unable to serialize the header and data");

      // write the socket.
      this->Write(packet);

      return StatusOk;
    }

    ///
    /// this method receives a packet by blocking.
    ///
    template <typename O>
    Status
    TCPSocket::Receive(Event& event, O outputs)
    {
      ELLE_LOG_TRACE_COMPONENT("Infinit.Network");
      Parcel* parcel;

      // block the current fiber until the given event is received.
      ELLE_LOG_TRACE("wait on event %s", event.Identifier());
      scheduler().current()->wait(event.Signal());
      parcel = event.Signal().Value();

      assert(parcel != nullptr && "The event should have filled the parcel");

      // check the tag.
      if (parcel->header->tag != outputs.tag)
        {
          //
          // in this case, the blocked fiber received a message whose
          // tag does not match the expected one.
          //
          Tag           tag = parcel->header->tag;

          // first, test if the message received is an error, if so, append
          // the report to the local one.
          if (tag == TagError)
            {
              Report    report;

              // extract the error message.
              if (report.Extract(*parcel->data) == StatusError)
                escape("unable to extract the error message");

              // report the remote error.
              transpose(report);
            }
          else
            escape("fiber was awaken by a packet with the wrong tag");

          // in any case, return an error from the Receive() method.
          escape("received a packet with an unexpected tag '%u'",
                 tag);
        }

      // extract the arguments.
      if (outputs.Extract(*parcel->data) == StatusError)
        escape("unable to extract the arguments");

      return StatusOk;
    }

    ///
    /// this method sends and waits for an appropriate response.
    ///
    template <typename I,
              typename O>
    Status              TCPSocket::Call(const I                 inputs,
                                        O                       outputs)
    {
      ELLE_LOG_TRACE_COMPONENT("Infinit.Network");
      Event             event;

      // generate an event to link the request with the response.
      if (event.Generate() == StatusError)
        escape("unable to generate the event");

      // send the inputs.
      ELLE_LOG_TRACE("call tag %s on event %s and await tag %s",
                     inputs.tag, event.Identifier(), outputs.tag);
      if (this->Send(inputs, event) == StatusError)
        escape("unable to send the inputs");

      // wait for the reply.
      if (this->Receive(event, outputs) == StatusError)
        escape("unable to receive the outputs");

      event.Cleanup();

      return StatusOk;
    }

    ///
    /// this method replies to the message which has just been received i.e
    /// whose tag is specified in the current session.
    ///
    template <typename I>
    Status              TCPSocket::Reply(const I                inputs)
    {
      if (this->Send(inputs, current_context().parcel->header->event) == StatusError)
        escape("unable to send the reply");
      current_context().parcel->header->event.Cleanup();

      return StatusOk;
    }

  }
}

#endif
