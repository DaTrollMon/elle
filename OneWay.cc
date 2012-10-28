#include <elle/cryptography/OneWay.hh>
#include <elle/cryptography/cryptography.hh>

#include <elle/idiom/Close.hh>
# include <openssl/evp.h>
# include <openssl/err.h>
#include <elle/idiom/Open.hh>

namespace elle
{
  namespace cryptography
  {

    ///
    /// this method hashes the given plain, returning a digest object.
    ///
    Status              OneWay::Hash(const Plain&               plain,
                                     Digest&                    digest)
    {
      // Make sure the cryptographic system is set up.
      cryptography::require();

      static ::EVP_MD const* Algorithm = ::EVP_sha256();

      ::EVP_MD_CTX      context;
      unsigned int      size;

      // allocate the digest's contents.
      if (digest.region.Prepare(EVP_MD_size(Algorithm)) == Status::Error)
        escape("unable to allocate memory for the digest");

      // initialise the context.
      ::EVP_MD_CTX_init(&context);

      // initialise the digest.
      if (::EVP_DigestInit_ex(&context, Algorithm, nullptr) <= 0 ||
      // update the digest with the given data.
          ::EVP_DigestUpdate(&context,
                             plain.contents,
                             plain.size) <= 0 ||
      // finalise the digest.
          ::EVP_DigestFinal_ex(&context,
                               reinterpret_cast<unsigned char*>(digest.region.contents),
                               static_cast<unsigned int*>(&size)) <= 0)
        {
          (void) ::EVP_MD_CTX_cleanup(&context); // no matter if we can cleanup the context
          escape("%s", ::ERR_error_string(ERR_get_error(), nullptr));
        }

      // set the size.
      digest.region.size = size;

      // clean the context.
      if (::EVP_MD_CTX_cleanup(&context) <= 0)
        escape("%s", ::ERR_error_string(ERR_get_error(), nullptr));

      return Status::Ok;
    }

  }
}
