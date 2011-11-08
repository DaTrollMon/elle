//
// ---------- header ----------------------------------------------------------
//
// project       hole
//
// license       infinit
//
// author        julien quintard   [wed aug 31 15:05:39 2011]
//

#ifndef HOLE_IMPLEMENTATIONS_SLUG_MACHINE_HH
#define HOLE_IMPLEMENTATIONS_SLUG_MACHINE_HH

//
// ---------- includes --------------------------------------------------------
//

#include <elle/Elle.hh>
#include <nucleus/Nucleus.hh>
#include <lune/Lune.hh>

#include <hole/implementations/slug/Guestlist.hh>
#include <hole/implementations/slug/Neighbourhood.hh>
#include <hole/implementations/slug/Cluster.hh>

namespace hole
{
  namespace implementations
  {
    namespace slug
    {

//
// ---------- classes ---------------------------------------------------------
//

      ///
      /// XXX represents the current host
      ///
      class Machine:
	public elle::Entity
      {
      public:
	//
	// constants
	//
	struct					Default
	{
	  static const elle::Natural16		Port;
	};

	static const elle::Natural32		Timeout;

	//
	// enumerations
	//
	enum State
	  {
	    StateUnknown,
	    StateAlone,
	    StateAttached
	  };

	//
	// constructors & destructors
	//
	Machine();
	~Machine();

	//
	// methods
	//
	elle::Status		Launch();

	elle::Status		Put(const nucleus::Address&,
				    const nucleus::ImmutableBlock&);
	elle::Status		Put(const nucleus::Address&,
				    const nucleus::MutableBlock&);
	elle::Status		Get(const nucleus::Address&,
				    nucleus::ImmutableBlock&);
	elle::Status		Get(const nucleus::Address&,
				    const nucleus::Version&,
				    nucleus::MutableBlock&);
	elle::Status		Kill(const nucleus::Address&);

	//
	// callbacks
	//
	elle::Status		Alone();

	elle::Status		Connection(elle::Gate*);
	elle::Status		Authenticate(const lune::Passport&,
					     const elle::Port&);
	elle::Status		Authenticated(const Cluster&);
	elle::Status		Sweep(Host*);
	elle::Status		Push(const nucleus::Address&,
				     const
				       nucleus::Derivable<nucleus::Block>&);
	elle::Status		Pull(const nucleus::Address&,
				     const nucleus::Version&);
	elle::Status		Wipe(const nucleus::Address&);

	//
	// interfaces
	//

	// dumpable
	elle::Status		Dump(const elle::Natural32 = 0) const;

	//
	// attributes
	//
	State			state;
	elle::Port		port;

	Guestlist		guestlist;
	Neighbourhood		neighbourhood;

	elle::Timer*		timer;
      };

    }
  }
}

#endif
