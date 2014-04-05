#ifndef ELLE_FILESYSTEM_HH
# define ELLE_FILESYSTEM_HH

# include <boost/filesystem.hpp>
# include <boost/filesystem/fstream.hpp>
# include <boost/functional/hash.hpp>

namespace std
{
  template<>
  struct hash<boost::filesystem::path>
  {
    typedef boost::filesystem::path argument_type;
    typedef std::size_t value_type;

    value_type
    operator()(argument_type const& p) const;
  };
}

# include <elle/filesystem.hxx>

#endif
