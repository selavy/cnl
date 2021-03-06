
//          Copyright John McFarlane 2015 - 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file ../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

/// \file
/// \brief definitions supporting generic treatment of numeric types

#if !defined(CNL_ENCOMPASSES)
#define CNL_ENCOMPASSES 1

#include <cnl/num_traits.h>

/// compositional numeric library
namespace cnl {
    namespace _impl {
        ////////////////////////////////////////////////////////////////////////////////
        // cnl::_impl::encompasses

        template<class T, class Enable = void>
        struct unsigned_or_float;

        template<class T>
        struct unsigned_or_float<T, enable_if_t<numeric_limits<T>::is_iec559>> {
            using type = T;
        };

        template<class T>
        struct unsigned_or_float<T, enable_if_t<!numeric_limits<T>::is_iec559>> : make_unsigned<T> {
        };

        template<class T>
        using unsigned_or_float_t = typename unsigned_or_float<T>::type;

        template<class Encompasser, bool EncompasserSigned,
                class Encompassed, bool EncompassedSigned>
        struct encompasses_signedness
                : std::integral_constant<bool, ::cnl::digits<Encompasser>::value >= ::cnl::digits<Encompassed>::value> {
        };

        template<class Encompasser, class Encompassed>
        struct encompasses_signedness<Encompasser, false, Encompassed, true> : std::false_type {
        };

        // true if Encompassed can be cast to Encompasser without chance of overflow
        template<class Encompasser, class Encompassed>
        struct encompasses
                : encompasses_signedness<
                        Encompasser, ::cnl::is_signed<Encompasser>::value,
                        Encompassed, ::cnl::is_signed<Encompassed>::value> {
        };
    }
}
#endif  // CNL_ENCOMPASSES
