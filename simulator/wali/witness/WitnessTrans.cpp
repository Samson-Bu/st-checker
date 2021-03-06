/*!
 * @author Nicholas Kidd
 */

#include "../Common.hpp"
#include "WitnessTrans.hpp"
#include "Visitor.hpp"

namespace wali
{
  namespace witness
  {
    WitnessTrans::WitnessTrans( const wfa::ITrans& t_ ) : Witness(t_.weight()),t(t_)
    {
      min_length = 0UL;
    }

    // Destructor does nothing.
    WitnessTrans::~WitnessTrans()
    {
    }

    //
    // Override Witness::accept
    //
    void WitnessTrans::accept( Visitor& v, bool visitOnce ATTR_UNUSED )
    {
      // TODO how does marking work...need a flag maybe
      (void) visitOnce;
      mark();
      if (v.visitTrans(this)) {
          v.postvisitTrans(this);
      }
    }

    // Overrides Witness::prettyPrint
    std::ostream& WitnessTrans::prettyPrint( std::ostream& o,size_t depth ) const
    {
      formatDepth(o,depth);
      o << "WitnessTrans: ";
      t.print(o) << std::endl;
      return o;
    }

    const wfa::Trans& WitnessTrans::getTrans() const
    {
      return t;
    }

  } // namespace witness

} // namespace wali

/*
 * $Id$
 */

