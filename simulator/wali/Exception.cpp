/*!
 * @author Nicholas Kidd
 */

#include "Common.hpp"
#include "Exception.hpp"

namespace wali
{
  /****
   * class Exception
   ****/

  Exception::Exception()
    : msg( "wpds::Exception" ) {}

  Exception::Exception( const std::string & s )
    : msg( s ) {}

  Exception::~Exception() {}

  std::ostream & Exception::print( std::ostream & o ) const
  {
    o << "[wpds::Exception] " << msg;
    return o;
  }

}

