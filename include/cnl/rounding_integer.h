
//          Copyright John McFarlane 2015 - 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file ../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#if !defined(CNL_ROUNDING_INTEGER_H)
#define CNL_ROUNDING_INTEGER_H 1

#include "cnlint.h"
#include "limits.h"

#include "bits/number_base.h"
#include "numeric.h"

namespace cnl {

    struct closest_rounding_tag {
        template<class To, class From>
        static constexpr To convert(From const& from)
        {
            return static_cast<To>(intmax(from+((from>=0) ? .5 : -.5)));
        }
    };

    /// \brief An integer with customized rounding behavior.
    template<class Rep = int, class RoundingTag = closest_rounding_tag>
    class rounding_integer;

    namespace _rounding_integer_impl {
        ////////////////////////////////////////////////////////////////////////////////
        // cnl::_rounding_integer_impl::is_rounding_integer

        template<class T>
        struct is_rounding_integer : std::false_type {
        };

        template<class Rep, class RoundingTag>
        struct is_rounding_integer<rounding_integer<Rep, RoundingTag>> : std::true_type {
        };
    }

    template<class Rep, class RoundingTag>
    class rounding_integer : public _impl::number_base<rounding_integer<Rep, RoundingTag>, Rep> {
        static_assert(!_rounding_integer_impl::is_rounding_integer<Rep>::value,
                "rounding_integer of rounding_integer is not a supported");

        using super = _impl::number_base<rounding_integer<Rep, RoundingTag>, Rep>;
    public:
        using rounding = RoundingTag;

        using _base = _impl::number_base<rounding_integer<Rep, RoundingTag>, Rep>;

        constexpr rounding_integer() = default;

        template<class T, _impl::enable_if_t<numeric_limits<T>::is_integer, int> Dummy = 0>
        constexpr rounding_integer(T const& v)
                : super(static_cast<Rep>(v)) { }

        template<class T, _impl::enable_if_t<!numeric_limits<T>::is_integer, int> Dummy = 0>
        constexpr rounding_integer(T const& v)
                : super(rounding::template convert<Rep>(v)) { }

        template<class T>
        constexpr explicit operator T() const
        {
            return static_cast<T>(to_rep(*this));
        }
    };

    ////////////////////////////////////////////////////////////////////////////////
    // numeric type traits

    template<class Rep, class RoundingTag>
    struct digits<rounding_integer<Rep, RoundingTag>> : digits<Rep> {
    };

    template<class Rep, class RoundingTag, _digits_type MinNumBits>
    struct set_digits<rounding_integer<Rep, RoundingTag>, MinNumBits> {
        using type = rounding_integer<set_digits_t<Rep, MinNumBits>, RoundingTag>;
    };

    /// \brief \ref rounding_integer specialization of \ref from_rep
    /// \tparam ArchetypeRep ignored; replaced by \c Rep
    /// \tparam RoundingTag the \c RoundingTag of the generated type
    template<class ArchetypeRep, class RoundingTag>
    struct from_rep<rounding_integer<ArchetypeRep, RoundingTag>> {
        /// \brief generates an \ref rounding_integer equivalent to \c r in type and value
        template<typename Rep>
        constexpr auto operator()(Rep const& r) const
        -> rounding_integer<Rep, RoundingTag>
        {
            return r;
        }
    };

    /// \brief Overload of \ref to_rep(Number const& number) for \ref rounding_integer.
    template<class Rep, class RoundingTag>
    constexpr Rep to_rep(rounding_integer<Rep, RoundingTag> const& number)
    {
        using base_type = typename rounding_integer<Rep, RoundingTag>::_base;
        return to_rep(static_cast<base_type const&>(number));
    }

    namespace _impl {
        template<class Rep, class RoundingTag>
        struct get_rep<rounding_integer<Rep, RoundingTag>> {
            using type = Rep;
        };

        template<class OldRep, class RoundingTag, class NewRep>
        struct set_rep<rounding_integer<OldRep, RoundingTag>, NewRep> {
            using type = rounding_integer<NewRep, RoundingTag>;
        };
    }

    template<class Rep, class RoundingTag, class Value>
    struct from_value<rounding_integer<Rep, RoundingTag>, Value> {
        using type = rounding_integer<Value, RoundingTag>;
    };

    template<class Rep, class RoundingTag, class ValueRep, class ValueRoundingTag>
    struct from_value<rounding_integer<Rep, RoundingTag>, rounding_integer<ValueRep, ValueRoundingTag>> {
    private:
        // the common_type of two overflow tags is the stricter for some sense of strict
        using _overflow_tag = _impl::common_type_t<RoundingTag, ValueRoundingTag>;
        using _rep = from_value_t<Rep, ValueRep>;
    public:
        using type = rounding_integer<_rep, _overflow_tag>;
    };

    template<class Rep, class RoundingTag, CNL_IMPL_CONSTANT_VALUE_TYPE Value>
    struct from_value<rounding_integer<Rep, RoundingTag>, constant<Value>> {
        using _rep = typename std::conditional<digits<int>::value<used_bits(Value),
                decltype(Value),
                int>::type;
        using type = rounding_integer<_rep, RoundingTag>;
    };

    template<int Digits, int Radix, class Rep, class RoundingTag>
    struct shift<Digits, Radix, rounding_integer<Rep, RoundingTag>>
            : shift<Digits, Radix, _impl::number_base<rounding_integer<Rep, RoundingTag>, Rep>> {
    };

    ////////////////////////////////////////////////////////////////////////////////
    // unary arithmetic

    namespace _impl {
        // for operands with a common tag
        template<class Operator, class Rep, class RoundingTag>
        struct unary_operator<Operator, rounding_integer<Rep, RoundingTag>> {
            constexpr auto operator()(rounding_integer<Rep, RoundingTag> const& operand) const
            -> decltype(from_rep<rounding_integer<decltype(Operator()(to_rep(operand))), RoundingTag>>{}(
                    Operator()(to_rep(operand))))
            {
                using result_type = rounding_integer<decltype(Operator()(to_rep(operand))), RoundingTag>;
                return from_rep<result_type>{}(Operator()(to_rep(operand)));
            }
        };
    }

    ////////////////////////////////////////////////////////////////////////////////
    // binary arithmetic

    namespace _impl {
        // for operands with a common tag
        template<class Operator, class LhsRep, class RhsRep, class RoundingTag>
        struct binary_operator<Operator, rounding_integer<LhsRep, RoundingTag>, rounding_integer<RhsRep, RoundingTag>,
                typename Operator::is_not_comparison> {
            constexpr auto operator()(
                    rounding_integer<LhsRep, RoundingTag> const& lhs,
                    rounding_integer<RhsRep, RoundingTag> const& rhs) const
            -> decltype(from_rep<rounding_integer<op_result<Operator, LhsRep, RhsRep>, RoundingTag>>{}(
                    Operator()(to_rep(lhs), to_rep(rhs))))
            {
                using result_type = rounding_integer<op_result<Operator, LhsRep, RhsRep>, RoundingTag>;
                return from_rep<result_type>{}(Operator()(to_rep(lhs), to_rep(rhs)));
            }
        };

        // comparison for operands with a common tag
        template<class Operator, class LhsRep, class RhsRep, class RoundingTag>
        struct binary_operator<Operator, rounding_integer<LhsRep, RoundingTag>, rounding_integer<RhsRep, RoundingTag>,
                typename Operator::is_comparison> {
        constexpr auto operator()(
                rounding_integer<LhsRep, RoundingTag> const& lhs,
                rounding_integer<RhsRep, RoundingTag> const& rhs) const
            -> decltype(Operator()(to_rep(lhs), to_rep(rhs)))
            {
                return Operator()(to_rep(lhs), to_rep(rhs));
            }
        };

        // for operands with different policies
        template<class Operator, class LhsRep, class LhsRoundingTag, class RhsRep, class RhsRoundingTag>
        struct binary_operator<Operator,
                rounding_integer<LhsRep, LhsRoundingTag>, rounding_integer<RhsRep, RhsRoundingTag>,
                typename Operator::is_comparison> {
            constexpr auto operator()(
                    rounding_integer<LhsRep, LhsRoundingTag> const& lhs,
                    rounding_integer<RhsRep, RhsRoundingTag> const& rhs) const
            -> decltype(binary_operator<Operator, rounding_integer<LhsRep, common_type_t<LhsRoundingTag, RhsRoundingTag>>, rounding_integer<LhsRep, common_type_t<LhsRoundingTag, RhsRoundingTag>>>()(lhs, rhs))
            {
                using common_tag = common_type_t<LhsRoundingTag, RhsRoundingTag>;
                return binary_operator<Operator, rounding_integer<LhsRep, common_tag>, rounding_integer<LhsRep, common_tag>>()(lhs, rhs);
            }
        };
    }

    ////////////////////////////////////////////////////////////////////////////////
    // binary bitwise

    template<class LhsRep, class LhsRoundingTag, class RhsInteger>
    constexpr auto operator<<(
            rounding_integer<LhsRep, LhsRoundingTag> const& lhs,
            RhsInteger const& rhs)
    -> decltype(from_rep<rounding_integer<decltype(to_rep(lhs) << rhs), LhsRoundingTag>>{}(to_rep(lhs) << rhs))
    {
        return from_rep<rounding_integer<
                decltype(to_rep(lhs) << rhs),
                LhsRoundingTag>>{}(to_rep(lhs) << rhs);
    }

    ////////////////////////////////////////////////////////////////////////////////
    // cnl::numeric_limits specialization for rounding_integer

    template<class Rep, class RoundingTag>
    struct numeric_limits<cnl::rounding_integer<Rep, RoundingTag>>
            : numeric_limits<cnl::_impl::number_base<cnl::rounding_integer<Rep, RoundingTag>, Rep>> {
        static constexpr bool is_integer = true;
    };

    template<class Rep, class RoundingTag>
    struct numeric_limits<cnl::rounding_integer<Rep, RoundingTag> const>
            : numeric_limits<cnl::_impl::number_base<cnl::rounding_integer<Rep, RoundingTag>, Rep>> {
        static constexpr bool is_integer = true;
    };
}

namespace std {
    ////////////////////////////////////////////////////////////////////////////////
    // std::numeric_limits specialization for rounding_integer

    template<class Rep, class RoundingTag>
    struct numeric_limits<cnl::rounding_integer<Rep, RoundingTag>>
            : cnl::numeric_limits<cnl::rounding_integer<Rep, RoundingTag>> {
    };

    template<class Rep, class RoundingTag>
    struct numeric_limits<cnl::rounding_integer<Rep, RoundingTag> const>
            : cnl::numeric_limits<cnl::rounding_integer<Rep, RoundingTag>> {
    };
}

#endif  // CNL_ROUNDING_INTEGER_H
