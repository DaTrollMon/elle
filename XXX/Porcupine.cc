//
// ---------- header ----------------------------------------------------------
//
// project       nucleus
//
// license       infinit
//
// author        julien quintard   [sat oct  8 22:42:48 2011]
//

//
// ---------- includes --------------------------------------------------------
//

#include <XXX/Porcupine.hh>

using namespace nucleus::proton;

//
// ---------- definitions -----------------------------------------------------
//

///
/// XXX in bytes
///
const elle::Natural32                   Porcupine<>::Default::Length = 16;

///
/// XXX
///
elle::SecretKey                         Porcupine<>::Default::Secret;

//
// ---------- definitions -----------------------------------------------------
//

///
/// XXX
///
elle::Callback<
  elle::Status,
  elle::Parameters<
    Block*,
    Handle&
    >
  >                                     Porcupine<>::Attach;

///
/// XXX
///
elle::Callback<
  elle::Status,
  elle::Parameters<
    Handle&
    >
  >                                     Porcupine<>::Detach;

///
/// XXX
///
elle::Callback<
  elle::Status,
  elle::Parameters<
    Handle&
    >
  >                                     Porcupine<>::Load;

///
/// XXX
///
elle::Callback<
  elle::Status,
  elle::Parameters<
    Handle&
    >
  >                                     Porcupine<>::Unload;

//
// ---------- static methods --------------------------------------------------
//

///
/// this method initializes the porcupine.
///
elle::Status        Porcupine<>::Initialize(
  const elle::Callback<
  elle::Status,
  elle::Parameters<
    Block*,
    Handle&
    >
  >&                                                        attach,
  const elle::Callback<
  elle::Status,
  elle::Parameters<
    Handle&
    >
  >&                                                        detach,
  const elle::Callback<
  elle::Status,
  elle::Parameters<
    Handle&
    >
  >&                                                        load,
  const elle::Callback<
  elle::Status,
  elle::Parameters<
    Handle&
    >
  >&                                                        unload)
{
  // set the callbacks.
  Porcupine<>::Attach = attach;
  Porcupine<>::Detach = detach;
  Porcupine<>::Load = load;
  Porcupine<>::Unload = unload;

  // initialize the default secret key.
  //
  // this is required for nodules' footprint to be computed properly.
  if (Porcupine<>::Default::Secret.Create(
        elle::String(Porcupine<>::Default::Length, 'B')) == elle::StatusError)
    escape("unable to generate the default key");

  //
  // catalog-specific initialization.
  //
  {
    // initialize the seam.
    if (Seam<nucleus::Catalog>::Initialize() == elle::StatusError)
      escape("unable to initialize the seam");

    // initialize the quill.
    if (Quill<nucleus::Catalog>::Initialize() == elle::StatusError)
      escape("unable to initialize the quill");
  }

  // XXX

  return elle::StatusOk;
}

///
/// this method cleans the porcupine.
///
elle::Status        Porcupine<>::Clean()
{
  //
  // catalog-specific cleaning.
  //
  {
    // clean the quill.
    if (Quill<nucleus::Catalog>::Clean() == elle::StatusError)
      escape("unable to clean the quill");

    // clean the seam.
    if (Seam<nucleus::Catalog>::Clean() == elle::StatusError)
      escape("unable to clean the seam");
  }

  // XXX

  return elle::StatusOk;
}
