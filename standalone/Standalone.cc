//
// ---------- header ----------------------------------------------------------
//
// project       elle
//
// license       infinit
//
// file          /home/mycure/infinit/elle/standalone/Standalone.cc
//
// created       julien quintard   [sun may  2 11:00:51 2010]
// updated       julien quintard   [mon aug  1 10:28:45 2011]
//

//
// ---------- includes --------------------------------------------------------
//

#include <elle/standalone/Standalone.hh>

namespace elle
{
  namespace standalone
  {

//
// ---------- static methods --------------------------------------------------
//

    ///
    /// this method initializes the module.
    ///
    Status		Standalone::Initialize()
    {
      enter();

      // initialize the report.
      if (Report::Initialize() == StatusError)
	escape("unable to initialize the report");

      // initialize the log.
      if (Log::Initialize() == StatusError)
	escape("unable to initialize the log");

      leave();
    }

    ///
    /// this method cleans the module.
    ///
    Status		Standalone::Clean()
    {
      enter();

      // clean the log.
      if (Log::Clean() == StatusError)
	escape("unable to clean the log");

      // clean the report.
      if (Report::Clean() == StatusError)
	escape("unable to clean the report");

      leave();
    }

  }
}
