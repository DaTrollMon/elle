//
// ---------- header ----------------------------------------------------------
//
// project       diary
//
// license       infinit
//
// author        julien quintard   [sun jun 26 22:48:13 2011]
//

//
// ---------- includes --------------------------------------------------------
//

#include <satellites/diary/unix/Memoirs.hh>

#include <satellites/diary/unix/Crux.hh>
#include <satellites/diary/unix/Record.hh>
#include <satellites/diary/unix/Replay.hh>
#include <satellites/diary/unix/Upcall.hh>

#if defined(INFINIT_LINUX)
# include <horizon/linux/Linux.hh>
#elif defined(INFINIT_MACOSX)
# include <horizon/macosx/MacOSX.hh>
#endif

namespace satellite
{
  #undef unix
  namespace unix
  {

//
// ---------- constructors & destructors --------------------------------------
//

    ///
    /// default constructor.
    ///
    Memoirs::Memoirs():
      mode(Memoirs::ModeUnknown)
    {
    }

    ///
    /// destructor.
    ///
    Memoirs::~Memoirs()
    {
      // nothing to do.
    }

//
// ---------- methods ---------------------------------------------------------
//

    ///
    /// this method sets up the memoirs with the FUSE operations to
    /// which the upcalls must be forwarded through the memoirs.
    ///
    /// besides, this method initializes the recording session.
    ///
    elle::Status        Memoirs::Initialize(const elle::String& mountpoint,
                                            const elle::String& mirror)
    {
      // set up the crux.
      if (Crux::Setup(mirror) == elle::Status::Error)
        escape("unable to set up the crux");

      // set the mode.
      this->mode = Memoirs::ModeRecord;

      this->archive.Reset();

      // initialize the record.
      if (Record::Initialize(this, mountpoint) == elle::Status::Error)
        escape("unable to initialize the record");

      // set the attributes.
      this->fuse = Crux::Operations;

      return elle::Status::Ok;
    }

    ///
    /// this method sets up the memoirs with the FUSE operations to
    /// which the upcalls must be forwarded through the memoirs.
    ///
    /// besides, this method initializes the replaying session.
    ///
    elle::Status        Memoirs::Initialize(const elle::Natural32 from,
                                            const elle::Natural32 to)
    {
      // set the mode.
      this->mode = Memoirs::ModeReplay;

      // set the offsets.
      this->offsets.from = from;
      this->offsets.to = to;

      // initialize the replay.
      if (Replay::Initialize(this) == elle::Status::Error)
        escape("unable to initialize the replay");

#if defined(INFINIT_LINUX)
      // set the attributes.
      this->fuse = horizon::linux::FUSE::Operations;
#elif defined(INFINIT_MACOSX)
      // set the attributes.
      this->fuse = horizon::macosx::FUSE::Operations;
#endif

      return elle::Status::Ok;
    }

    ///
    /// this method cleans the memoirs.
    ///
    elle::Status        Memoirs::Clean()
    {
      // depending on the mode.
      switch (this->mode)
        {
        case Memoirs::ModeRecord:
          {
            // clean the record.
            if (Record::Clean() == elle::Status::Error)
              escape("unable to clean the recording session");

            break;
          }
        case Memoirs::ModeReplay:
          {
            // clean the replay.
            if (Replay::Clean() == elle::Status::Error)
              escape("unable to clean the replaying session");

            break;
          }
        case Memoirs::ModeUnknown:
          {
            break;
          }
        }

      return elle::Status::Ok;
    }

    ///
    /// this method writes an upcall in the memoirs.
    ///
    elle::Status        Memoirs::Write(const Upcall&            upcall)
    {
      // check the memoirs mode.
      if (this->mode != Memoirs::ModeRecord)
        escape("unable to write an upcall in a non-recording memoirs");

      // serialize the upcall.
      try
        {
          this->archive.Writer() << upcall;
        }
      catch (std::exception const& err)
        {
          escape("unable to serialize the upcall: %s", err.what());
        }

      return elle::Status::Ok;
    }

    ///
    /// this method reads an upcall from the memoirs.
    ///
    elle::Status        Memoirs::Read(Upcall&                   upcall)
    {
      // check the memoirs mode.
      if (this->mode != Memoirs::ModeReplay)
        escape("unable to read an upcall from a non-replaying memoirs");

      if (this->archive.Size() >= this->offset)
        escape("Nothing to read!");

      try
        {
          elle::WeakBuffer(
              this->archive.Contents() + this->offset,
              this->archive.Size() - this->offset
          ).Reader() >> upcall;
        }
      catch (std::exception const& err)
        {
          escape("unable to extract the upcall: %s", err.what());
        }

      return elle::Status::Ok;
    }

    ///
    /// this method returns true if the end of the memoirs has been reached.
    ///
    elle::Status        Memoirs::End() const
    {
      if (this->archive.Size() <= this->offset)
        return elle::Status::True;

      return elle::Status::False;
    }

//
// ---------- dumpable --------------------------------------------------------
//

    ///
    /// this function dumps an memoirs object.
    ///
    elle::Status        Memoirs::Dump(elle::Natural32           margin) const
    {
      elle::String      alignment(margin, ' ');

      // display the name.
      std::cout << alignment << "[Memoirs]" << std::endl;

      // dump the parent class.
      if (satellite::Memoirs::Dump(margin + 2) == elle::Status::Error)
        escape("unable to dump the parent class");

      // display the name.
      std::cout << alignment << elle::Dumpable::Shift
                << "[Mode] " << this->mode << std::endl;

      // display the name.
      std::cout << alignment << elle::Dumpable::Shift
                << "[Offsets] "
                << this->offsets.from
                << ", "
                << this->offsets.to << std::endl;

      return elle::Status::Ok;
    }

  }
}
