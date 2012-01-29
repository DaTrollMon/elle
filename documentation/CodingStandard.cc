//
// ---------- header ----------------------------------------------------------
//
// project       documentation
//
// license       infinit
//
// author        julien quintard   [fri jan 27 15:07:03 2012]
//

//
// ---------- includes --------------------------------------------------------
//

#include <package/module/CodingStandard.hh>
#include <infinit-dependency-1.hh>
#include <infinit-dependency-2.hh>

#include <idiom/Close.hh>
# include <system-dependecy.h>
# include <library-dependency.h>
#include <idiom/Open.hh>

namespace package
{
  namespace module
  {

//
// ---------- definitions -----------------------------------------------------
//

    ///
    /// this variable is a constant.
    ///
    const Natural32             CodingStandard::Constant1;

    ///
    /// this variable is a static attribute.
    ///
    Natural32                   CodingStandard::Attribute1;

//
// ---------- static methods --------------------------------------------------
//

    ///
    /// description of the method.
    ///
    Status              CodingStandard::Method1()
    {
      enter();

      // nothing to do.

      leave();
    }

//
// ---------- constructors & destructors --------------------------------------
//

    ///
    /// description of the constructor.
    ///
    CodingStandard::CodingStandard():
      attribute1(1),
      attribute2(2),
      attribute3(3)
    {
    }

//
// ---------- methods ---------------------------------------------------------
//

    ///
    /// description of the method.
    ///
    template <typename T>
    Status              CodingStandard::Method3(const Natural32 n,
                                                T&              object)
    {
      enter();

      // do something.
      if (object.Compute(n) == StatusError)
        escape("unable to do something");

      leave();
    }

  }
}

#endif
