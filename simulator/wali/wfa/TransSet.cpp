/*!
 * @author Nicholas Kidd
 */

#include "ITrans.hpp"
#include "Trans.hpp"
#include "TransSet.hpp"
#include "TransFunctor.hpp"

#if IMPL_LIST
#   define IMPLFIND( impl,t ) std::find<wali::wfa::TransSet::iterator,wali::wfa::ITransEq>(impl.begin(),impl.end(),t)
#else
#   define IMPLFIND( impl,t ) impl.find(t)
#endif

namespace wali {

  namespace wfa {

    ITrans* TransSet::erase( ITrans* t ) {
      ITrans* tret = NULL;
      iterator it = find(t);
      if( it != end() ) {
        tret = *it;
        impl.erase(it);
      }
      return tret;
    }

    ITrans* TransSet::erase( Key from, Key stack, Key to ) {
      Trans terase(from,stack,to,0);
      return erase(&terase);
    }

    TransSet::iterator TransSet::find( Key from, Key stack, Key to ) {
      Trans terase(from,stack,to,0);
      ITrans* why = &terase;
      return IMPLFIND(impl,why);
    }

    TransSet::const_iterator TransSet::find( Key from, Key stack, Key to ) const {
      Trans terase(from,stack,to,0);
      return find(&terase);
    }

    TransSet::iterator TransSet::find( ITrans* t ) {
      return IMPLFIND(impl,t);
    }

    TransSet::const_iterator TransSet::find( ITrans* t ) const {
      return IMPLFIND(impl,t);
    }

    namespace details {
      template <typename IteratorType,
                typename FunctorType>
      void each(IteratorType it,
                IteratorType END,
                FunctorType & tf)
      {
        for( ; it != END ; it++ ) {
          tf(*it);
        }
      }
    }
        
    void TransSet::each( TransFunctor& tf )
    {
      details::each(begin(), end(), tf);
    }

    void TransSet::each( ConstTransFunctor& tf ) const
    {
      details::each(impl.begin(), impl.end(), tf);
    }
        
    void TransSet::each( boost::function<void(ITrans * t)> & tf )
    {
      details::each(begin(), end(), tf);
    }

    void TransSet::each( boost::function<void(ITrans const * t)> & tf ) const
    {
      details::each(impl.begin(), impl.end(), tf);
    }

    bool TransSet::insert( ITrans* t )
    {
      bool b = true;
#if IMPL_LIST
      impl.push_back(t);
#else
      b = impl.insert(t).second;
      // BEGIN DEBUGGING
      // We should never insert the same transition twice
      if( !b ) {
        t->print( *waliErr << "\tERROR" ) << std::endl;
        assert(b);
      }
      // END DEBUGGING
#endif
      return b;
    }

    std::ostream& TransSet::print( std::ostream& o ) const {
      const_iterator it = begin();
      const_iterator itEND = end();
      bool first = true;
      o << "{";
      for( ; it != itEND ; it++,first=false ) {
        if( !first )
          o << ", ";
        (*it)->print(o);
      }
      o << "}";
      return o;
    }

    size_t TransSet::size() const {
      return impl.size();
    }

  } // namespace wfa

} // namespace wali
