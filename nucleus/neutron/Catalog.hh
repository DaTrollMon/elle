//
// ---------- header ----------------------------------------------------------
//
// project       nucleus
//
// license       infinit
//
// file          /home/mycure/infinit/nucleus/neutron/Catalog.hh
//
// created       julien quintard   [mon jul 27 10:19:21 2009]
// updated       julien quintard   [wed may  4 23:10:53 2011]
//

#ifndef NUCLEUS_NEUTRON_CATALOG_HH
#define NUCLEUS_NEUTRON_CATALOG_HH

//
// ---------- includes --------------------------------------------------------
//

#include <elle/Elle.hh>

#include <nucleus/neutron/State.hh>
#include <nucleus/neutron/Offset.hh>
#include <nucleus/neutron/Range.hh>
#include <nucleus/neutron/Entry.hh>

namespace nucleus
{
  namespace neutron
  {

//
// ---------- classes ---------------------------------------------------------
//

    ///
    /// this class represents the content of a directory and is composed
    /// of a set of tuples (name, address).
    ///
    /// \todo XXX note that, for now, all the entries are stored in a single
    /// block until an advanced, multi-block-based, data structure is
    /// developed.
    ///
    class Catalog:
      public elle::Object
    {
    public:
      //
      // constructors & destructors
      //
      Catalog();

      //
      // methods
      //
      elle::Status	Add(Entry*);
      elle::Status	Exist(const elle::String&);
      elle::Status	Lookup(const elle::String&,
			       Entry*&);
      elle::Status	Consult(const Index&,
				const Size&,
				Range<Entry>&) const;
      elle::Status	Rename(const elle::String&,
			       const elle::String&);
      elle::Status	Remove(const elle::String&);
      elle::Status	Capacity(Offset&) const;

      //
      // interfaces
      //

      // object
      declare(Catalog);

      // dumpable
      elle::Status	Dump(const elle::Natural32 = 0) const;

      // archivable
      elle::Status	Serialize(elle::Archive&) const;
      elle::Status	Extract(elle::Archive&);

      //
      // attributes
      //
      State		state;

      Range<Entry>	range;
    };

  }
}

#endif
