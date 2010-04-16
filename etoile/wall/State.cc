//
// ---------- header ----------------------------------------------------------
//
// project       etoile
//
// license       infinit
//
// file          /home/mycure/infinit/etoile/wall/State.cc
//
// created       julien quintard   [wed mar 31 16:21:17 2010]
// updated       julien quintard   [thu apr 15 13:54:26 2010]
//

//
// ---------- includes --------------------------------------------------------
//

#include <etoile/wall/State.hh>

namespace etoile
{
  namespace wall
  {

//
// ---------- definitions -----------------------------------------------------
//

    ///
    /// this defines a empty, unused hence null state.
    ///
    const State			State::Null;

//
// ---------- methods ---------------------------------------------------------
//

    ///
    /// this method generates the state according to the given object.
    ///
    Status		State::Create(const kernel::Object&	object)
    {
      enter();

      // set the genre.
      this->genre = object.meta.genre;

      // set the stamps.
      this->stamps.creation = object.meta.stamp;
      this->stamps.modification = object.data.stamp;

      // set the size
      this->size = object.data.size;

      // set the owner.
      this->keys.owner = object.owner.K;

      // set the author depending on the mode.
      switch (object.author.role)
	{
	case kernel::RoleOwner:
	  {
	    this->keys.author = object.owner.K;

	    break;
	  }
	default:
	  {
	    // XXX
	    printf("UNIMPLEMENTED\n");	
	  }
	}

      // set the versions.
      this->versions.meta = object.meta.version;
      this->versions.data = object.data.version;

      leave();
    }

//
// ---------- entity ----------------------------------------------------------
//

    ///
    /// this operator compares two objects.
    ///
    Boolean		State::operator==(const State&		element) const
    {
      enter();

      // check the address as this may actually be the same object.
      if (this == &element)
	true();

      // compare the attributes.
      if ((this->genre != element.genre) ||
	  (this->stamps.creation != element.stamps.creation) ||
	  (this->stamps.modification != element.stamps.modification) ||
	  (this->size != element.size) ||
	  (this->keys.owner != element.keys.owner) ||
	  (this->keys.author != element.keys.author) ||
	  (this->versions.meta != element.versions.meta) ||
	  (this->versions.data != element.versions.data))
	false();

      true();
    }

    ///
    /// this macro-function call generates the entity.
    ///
    embed(Entity, State);

//
// ---------- dumpable --------------------------------------------------------
//

    ///
    /// this method dumps the state object.
    ///
    Status		State::Dump(const Natural32		margin) const
    {
      String		alignment(margin, ' ');

      enter();

      std::cout << alignment << "[State]" << std::endl;

      // dump the genre.
      std::cout << alignment << Dumpable::Shift << "[Genre] "
		<< this->genre << std::endl;

      //
      // dump the stamps.
      //
      {
	std::cout << alignment << Dumpable::Shift << "[Stamps]" << std::endl;

	// dump the creation time.
	std::cout << alignment << Dumpable::Shift << Dumpable::Shift
		  << "[Creation]" << std::endl;

	if (this->stamps.creation.Dump(margin + 6) == StatusError)
	  escape("unable to dump the creation time");

	// dump the modification time.
	std::cout << alignment << Dumpable::Shift << Dumpable::Shift
		  << "[Modification]" << std::endl;

	if (this->stamps.modification.Dump(margin + 6) == StatusError)
	  escape("unable to dump the modification time");
      }

      // dump the size.
      std::cout << alignment << Dumpable::Shift << "[Size] "
		<< std::dec << this->size << std::endl;

      //
      // dump the public keys.
      //
      {
	std::cout << alignment << Dumpable::Shift << "[Keys]" << std::endl;

	// dump the owner public key.
	std::cout << alignment << Dumpable::Shift << Dumpable::Shift
		  << "[Owner]" << std::endl;

	if (this->keys.owner.Dump(margin + 6) == StatusError)
	  escape("unable to dump the owner public key");

	// dump the author public key.
	std::cout << alignment << Dumpable::Shift << Dumpable::Shift
		  << "[Author]" << std::endl;

	if (this->keys.author.Dump(margin + 6) == StatusError)
	  escape("unable to dump the author public key");
      }

      //
      // dump the versions.
      //
      {
	std::cout << alignment << Dumpable::Shift << "[Versions]" << std::endl;

	// dump the meta version.
	std::cout << alignment << Dumpable::Shift << Dumpable::Shift
		  << "[Meta] " << std::dec << this->versions.meta << std::endl;

	// dump the data version.
	std::cout << alignment << Dumpable::Shift << Dumpable::Shift
		  << "[Data] " << std::dec << this->versions.data << std::endl;
      }

      leave();
    }

//
// ---------- archivable ------------------------------------------------------
//

    ///
    /// this method serializes the state.
    ///
    Status		State::Serialize(Archive&		archive) const
    {
      enter();

      // serialize the attributes.
      if (archive.Serialize(this->genre,
			    this->stamps.creation,
			    this->stamps.modification,
			    this->size,
			    this->keys.owner,
			    this->keys.author,
			    this->versions.meta,
			    this->versions.data) == StatusError)
	escape("unable to serialize the attributes");

      leave();
    }

    ///
    /// this method extracts the state.
    ///
    Status		State::Extract(Archive&			archive)
    {
      enter();

      // extract the attributes.
      if (archive.Extract(this->genre,
			  this->stamps.creation,
			  this->stamps.modification,
			  this->size,
			  this->keys.owner,
			  this->keys.author,
			  this->versions.meta,
			  this->versions.data) == StatusError)
	escape("unable to extract the attributes");

      leave();
    }

  }
}
