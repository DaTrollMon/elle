//
// ---------- header ----------------------------------------------------------
//
// project       infinit
//
// license       infinit (c)
//
// file          /home/mycure/infinit/etoile/kernel/Token.hh
//
// created       julien quintard   [fri jul 24 16:28:56 2009]
// updated       julien quintard   [wed apr 14 12:07:47 2010]
//

#ifndef ETOILE_KERNEL_TOKEN_HH
#define ETOILE_KERNEL_TOKEN_HH

//
// ---------- includes --------------------------------------------------------
//

#include <elle/Elle.hh>

namespace etoile
{
  namespace kernel
  {

//
// ---------- classes ---------------------------------------------------------
//

    ///
    /// a token is a secret key enabling a user to access encrypted
    /// data. however, in order to allow only the proper user to
    /// use this key, it is encrypted with the user's public key.
    ///
    class Token:
      public Entity,
      public Dumpable, public Archivable
    {
    public:
      //
      // constants
      //
      static const Token		Null;

      //
      // constructors & destructors
      //
      Token();
      Token(const Token&);
      ~Token();

      //
      // methods
      //
      Status		Update(const SecretKey&,
			       const PublicKey&);

      //
      // interfaces
      //

      // entity
      declare(Entity, Token);
      Boolean		operator==(const Token&) const;

      // dumpable
      Status		Dump(const Natural32 = 0) const;

      // archivable
      Status		Serialize(Archive&) const;
      Status		Extract(Archive&);

      //
      // attributes
      //
      Code*		code;
    };

  }
}

#endif
