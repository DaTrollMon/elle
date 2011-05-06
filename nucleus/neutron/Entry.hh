//
// ---------- header ----------------------------------------------------------
//
// project       nucleus
//
// license       infinit
//
// file          /home/mycure/infinit/nucleus/neutron/Entry.hh
//
// created       julien quintard   [fri apr  2 00:03:02 2010]
// updated       julien quintard   [thu may  5 13:39:47 2011]
//

#ifndef NUCLEUS_NEUTRON_ENTRY_HH
#define NUCLEUS_NEUTRON_ENTRY_HH

//
// ---------- includes --------------------------------------------------------
//

#include <elle/Elle.hh>

#include <nucleus/proton/Address.hh>

namespace nucleus
{
  namespace neutron
  {

//
// ---------- classes ---------------------------------------------------------
//

    ///
    /// this class represents a directory i.e catalog entry which is
    /// composed of a name and its object's corresponding address.
    ///
    class Entry:
      public elle::Object
    {
    public:
      //
      // constants
      //
      static const Entry		Null;

      //
      // types
      //
      typedef elle::String		S;

      //
      // constructors & destructors
      //
      Entry();
      Entry(const elle::String&,
	    const proton::Address&);

      //
      // interfaces
      //

      // object
      declare(Entry);
      elle::Boolean	operator==(const Entry&) const;

      // dumpable
      elle::Status	Dump(const elle::Natural32 = 0) const;

      // archivable
      elle::Status	Serialize(elle::Archive&) const;
      elle::Status	Extract(elle::Archive&);

      // rangeable
      elle::String&	Symbol();

      //
      // attributes
      //
      elle::String	name;
      proton::Address	address;
    };

  }
}

#endif
