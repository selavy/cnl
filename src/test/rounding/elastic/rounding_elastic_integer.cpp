
//          Copyright John McFarlane 2015 - 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file ../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <cnl/elastic_integer.h>
#include <cnl/rounding_integer.h>

namespace cnl {
    // rounding elastic integer
    template<
            int IntegerDigits,
            class RoundingTag = rounding_integer<>::rounding,
            class Narrowest = int>
    using rounding_elastic_integer = rounding_integer<
            elastic_integer<
                    IntegerDigits,
                    Narrowest>,
            RoundingTag>;

    template<
            class RoundingTag = rounding_integer<>::rounding,
            class Narrowest = int,
            class Input = int>
    rounding_elastic_integer<
            numeric_limits<Input>::digits,
            RoundingTag,
            Narrowest>
    constexpr make_rounding_elastic(Input const& input)
    {
        return input;
    }
}

namespace {
    using cnl::rounding_elastic_integer;
    using std::is_same;
    using cnl::_impl::identical;

    namespace default_parameters {
        using cnl::rounding_integer;
        using cnl::elastic_integer;

        static_assert(
                is_same<rounding_elastic_integer<1>::rep::rep, int>::value,
                "cnl::rounding_integer parameter default test failed");
    }

    namespace test_make_rounding_elastic {
        static_assert(identical(rounding_elastic_integer<1>{1}, rounding_elastic_integer<1>{1}), "");
        static_assert(identical(cnl::make_rounding_elastic(cnl::int16{7}), rounding_elastic_integer<15>{7}), "");
    }

    namespace test_multiply {
        static_assert(identical(rounding_elastic_integer<3>{7}*rounding_elastic_integer<4>{10}, rounding_elastic_integer<7>{70}), "rounding_elastic_integer operator*");
        //static_assert(identical(rounding_elastic_integer<3>{3}*.25, rounding_elastic_integer<3>{.75}), "rounding_elastic_integer operator*");
    }

    namespace test_scale {
        static_assert(identical(rounding_elastic_integer<3>{7}*rounding_elastic_integer<4>{10}, rounding_elastic_integer<7>{70}), "rounding_elastic_integer operator*");
    }
}
