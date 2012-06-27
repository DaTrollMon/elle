#ifndef INFINIT_PROTOCOL_PACKET_HH
# define INFINIT_PROTOCOL_PACKET_HH

# include <memory>

# include <elle/IOStream.hh>
# include <elle/Size.hh>

namespace infinit
{
  namespace protocol
  {
    class Packet: public elle::IOStream
    {
    /*-------------.
    | Construction |
    `-------------*/
    public:
      typedef char Byte;
      typedef unsigned int Size;
      Packet();
      Packet(Packet&& source);
      ~Packet();

    /*-----------.
    | Properties |
    `-----------*/
    public:
      elle::Size size() const;

    /*--------.
    | Details |
    `--------*/
    private:
      class StreamBuffer;
      friend class StreamBuffer;
      Packet(Size data_size);
      Packet(const Packet&);
      friend class PacketStream;
      Byte* _data;
      unsigned int _data_size;
    };
  }
}

#endif
