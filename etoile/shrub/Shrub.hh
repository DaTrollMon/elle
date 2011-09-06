//
// ---------- header ----------------------------------------------------------
//
// project       etoile
//
// license       infinit
//
// file          /home/mycure/infinit/etoile/shrub/Shrub.hh
//
// created       julien quintard   [sat aug  6 17:31:57 2011]
// updated       julien quintard   [tue sep  6 18:03:42 2011]
//

#ifndef ETOILE_SHRUB_SHRUB_HH
#define ETOILE_SHRUB_SHRUB_HH

//
// ---------- includes --------------------------------------------------------
//

#include <elle/Elle.hh>

#include <etoile/shrub/Riffle.hh>
#include <etoile/shrub/Queue.hh>

#include <etoile/path/Slab.hh>
#include <etoile/path/Route.hh>
#include <etoile/path/Venue.hh>

namespace etoile
{
  ///
  /// this namespace contains everything related to the shrub i.e the
  /// path-specific cache.
  ///
  namespace shrub
  {

//
// ---------- classes ---------------------------------------------------------
//

    ///
    /// the shrub i.e path cache relies on the LRU algorithm by keeping two
    /// data structures: a map for looking up and a queue for removing the
    /// least recently used riffles quickly.
    ///
    /// to avoid using too much memory for these data structures, both point
    /// to the same data: riffles.
    ///
    /// noteworthy is that, since this cache is used for paths and that paths
    /// follow a pattern where /music/meshuggah is a subset of /music, the
    /// data structure for storing the paths is hierachical.
    ///
    /// indeed, the Riffle class keeps a name such as 'meshuggah' along with
    /// a map of all the child entries.
    ///
    /// this design has been chosen to speed up the resolution process. indeed,
    /// this cache is used when a path must be resolved into a venue. the
    /// objective of the cache is thus to find the longest part of a given
    /// path.
    ///
    /// for example, given /music/meshuggah/nothing/, the objective is to
    /// find the corresponding address of this directory object. instead of
    /// trying /music/meshuggah/nothing/, then /music/meshuggah/, then
    /// /music/ etc. the designed cache is capable of returning the longest
    /// match within a single pass because riffles are hierarchically
    /// organised.
    ///
    /// note that several parameters can be configured through the
    /// configuration file:
    ///
    ///   o status: indicates whether the shrub should be used for
    ///             caching paths.
    ///   o capacity: indicates the number of riffles the shrub can
    ///               maintain before rejecting additional entries.
    ///   o frequency: indicates, in milliseconds, how often the sweeper
    ///                should be triggered in order to evict expired riffles.
    ///                note that the frequency is expressed in milliseconds.
    ///   o lifespan: indicates the riffles' lifespan before being considered
    ///               as having expired. note that every update on a riffle
    ///               resets the "expiration timeout", so to speak. note
    ///               that the lifespan is expressed in seconds, not
    ///               milliseconds.
    ///
    class Shrub
    {
    public:
      //
      // static methods
      //
      static elle::Status	Initialize();
      static elle::Status	Clean();

      static elle::Status	Allocate(const elle::Natural32);

      static elle::Status	Resolve(const path::Route&,
					path::Venue&);
      static elle::Status	Update(const path::Route&,
				       const path::Venue&);
      static elle::Status	Evict(const path::Route&);

      static elle::Status	Show(const elle::Natural32 = 0);

      //
      // static callbacks
      //
      static elle::Status	Sweeper();

      //
      // static attributes
      //
      static Riffle*		Riffles;
      static Queue		Timestamps;

      static elle::Timer*	Timer;
    };

  }
}

#endif
