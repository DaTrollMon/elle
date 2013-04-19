#include <execinfo.h>

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elle/compiler.hh>


static ELLE_COMPILER_ATTRIBUTE_NORETURN
void
noreturn()
{
  throw std::runtime_error("");
}

static
void
test_noreturn()
{
  try
  {
    noreturn();
  }
  catch (...)
  {}
}

ELLE_COMPILER_ATTRIBUTE_ALWAYS_INLINE inline
void
always_inline()
{
  // I have no decent idea to check if this is actually inlined. Even
  // ::backtrace is subject to offsets and won't work.
}

void
test_always_inline()
{
  always_inline();
}


void
test_pretty_function()
{
  BOOST_CHECK_EQUAL(ELLE_COMPILER_PRETTY_FUNCTION,
                    "void test_pretty_function()");
}

static
bool
test_suite()
{
  boost::unit_test::test_suite* exn = BOOST_TEST_SUITE("Exception");
  boost::unit_test::framework::master_test_suite().add(exn);
  exn->add(BOOST_TEST_CASE(test_noreturn));
  exn->add(BOOST_TEST_CASE(test_always_inline));
  exn->add(BOOST_TEST_CASE(test_pretty_function));

  return true;
}

int
main(int argc, char** argv)
{
  return ::boost::unit_test::unit_test_main(test_suite, argc, argv);
}
