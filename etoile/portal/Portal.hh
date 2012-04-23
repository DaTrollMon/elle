//
// ---------- header ----------------------------------------------------------
//
// project       etoile
//
// license       infinit
//
// author        julien quintard   [mon oct 31 13:52:37 2011]
//

#ifndef ETOILE_PORTAL_PORTAL_HH
#define ETOILE_PORTAL_PORTAL_HH

//
// ---------- includes --------------------------------------------------------
//

#include <elle/types.hh>
#include <lune/Lune.hh>

#include <etoile/portal/Application.hh>

#include <elle/idiom/Close.hh>
# include <map>
#include <elle/idiom/Open.hh>

namespace etoile
{
  ///
  /// this namespace contains everything related to making the Etoile's
  /// interface accessible through messaging.
  ///
  /// note that in order to be used, the client application must provide
  /// a phrase which is generated by the user's instance of Infinit.
  ///
  namespace portal
  {

//
// ---------- classes ---------------------------------------------------------
//

    ///
    /// this class is responsible for managing the external applications
    /// connecting to Etoile and triggering operations.
    ///
    class Portal
    {
    public:
      //
      // types
      //
      typedef std::pair<elle::network::LocalSocket*, Application*>       Value;
      typedef std::map<elle::network::LocalSocket*, Application*>        Container;
      typedef Container::iterator                               Iterator;
      typedef Container::const_iterator                         Scoutor;

      //
      // static methods
      //
      static elle::Status       Initialize();
      static elle::Status       Clean();

      static elle::Status       Add(Application*);
      static elle::Status       Retrieve(elle::network::LocalSocket*,
                                         Application*&);
      static elle::Status       Remove(elle::network::LocalSocket*);

      static elle::Status       Show(const elle::Natural32 = 0);

      //
      // static callbacks
      //
      static elle::Status       Connection(elle::network::LocalSocket*);
      static elle::Status       Authenticate(const elle::String&);
      static elle::Status       Prolog();
      static elle::Status       Epilog();

      //
      // static attributes
      //
      static elle::String       Line;
      static Container          Applications;
    };

  }
}

//
// ---------- includes --------------------------------------------------------
//

#include <etoile/portal/Wrapper.hh>

#include <etoile/portal/Manifest.hh>

#endif
