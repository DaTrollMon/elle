#include <cassert>
#include <sstream>

#include <elle/Size.hh>

#include <protocol/Packet.hh>

namespace infinit
{
  namespace protocol
  {
    class Packet::StreamBuffer: public elle::StreamBuffer
    {
    public:
      enum class Mode
      {
        fresh,
        eof,
        write,
      };

      StreamBuffer(Packet& p)
      : _packet(p)
      , _size(0)
      , _mode(Mode::fresh)
      {}

      virtual elle::Buffer write_buffer()
      {
        if (_mode == Mode::fresh)
          {
            assert(!_packet._data);
            _mode = Mode::write;
          }
        assert(_mode == Mode::write);
        // FIXME: Make buffer grow size parametrizable.
        static const elle::Size growth = 1024;
        _size += growth;
        _packet._data = reinterpret_cast<Packet::Byte*>(realloc(_packet._data, _size));
        return elle::Buffer(_packet._data + _size - growth, growth);
      }

      void flush(unsigned int size)
      {
        _packet._data_size += size;
      }

      virtual elle::Buffer read_buffer()
      {
        switch (_mode)
          {
            case Mode::eof:
              return elle::Buffer(0, 0);
            case Mode::fresh:
              assert(_packet._data);
              _mode = Mode::eof;
              return elle::Buffer(_packet._data, _packet._data_size);
          }
      }

    private:
      Mode _mode;
      Packet& _packet;
      elle::Size _size;
    };

    /*-------------.
    | Construction |
    `-------------*/

    Packet::Packet()
      : elle::IOStream(new StreamBuffer(*this))
      , _data(0)
      , _data_size(0)
    {}

    Packet::Packet(Packet&& source)
      : elle::IOStream(new StreamBuffer(*this))
      , _data(source._data)
      , _data_size(source._data_size)
    {
      source._data = 0;
      source._data_size = 0;
    }

    Packet::~Packet()
    {
      delete [] _data;
    }

    /*-----------.
    | Properties |
    `-----------*/

    elle::Size
    Packet::size() const
    {
      return this->_data_size;
    }

    /*--------.
    | Details |
    `--------*/

    Packet::Packet(Size data_size)
      : elle::IOStream(new StreamBuffer(*this))
      , _data(new Byte[data_size])
      , _data_size(data_size)
    {}
  }
}
