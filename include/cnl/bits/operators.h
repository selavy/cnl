
//          Copyright John McFarlane 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file ../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

/// \file
/// \brief a place to centralize most duplicate arithmetic operator boilerplate

#if !defined(CNL_OPERATORS_H)
#define CNL_OPERATORS_H

#include <cnl/limits.h>
#include <cnl/bits/type_traits.h>

/// compositional numeric library
namespace cnl {
    namespace _impl {
        ////////////////////////////////////////////////////////////////////////////////
        // cnl::_impl::wants_generic_ops

        // true iff T wants generic operator overloads
        template<class T, class Enable = void>
        struct wants_generic_ops : std::false_type {
        };

        ////////////////////////////////////////////////////////////////////////////////
        // operation tags

        struct minus_op {
            template<class Rhs>
            constexpr auto operator()(Rhs const& rhs) const -> decltype(-rhs)
            {
                return -rhs;
            }
        };

        struct plus_op {
            template<class Rhs>
            constexpr auto operator()(Rhs const& rhs) const -> decltype(+rhs)
            {
                return +rhs;
            }
        };

        struct add_op {
            template<class Lhs, class Rhs>
            constexpr auto operator()(Lhs const& lhs, Rhs const& rhs) const -> decltype(lhs+rhs)
            {
                return lhs+rhs;
            }
        };

        struct subtract_op {
            template<class Lhs, class Rhs>
            constexpr auto operator()(Lhs const& lhs, Rhs const& rhs) const -> decltype(lhs-rhs)
            {
                return lhs-rhs;
            }
        };

        struct multiply_op {
            template<class Lhs, class Rhs>
            CNL_FORCE_INLINE constexpr auto operator()(Lhs const& lhs, Rhs const& rhs) const -> decltype(lhs*rhs)
            {
                return lhs*rhs;
            }
        };

        struct divide_op {
            template<class Lhs, class Rhs>
            constexpr auto operator()(Lhs const& lhs, Rhs const& rhs) const -> decltype(lhs/rhs)
            {
                return lhs/rhs;
            }
        };

        struct modulo_op {
            template<class Lhs, class Rhs>
            constexpr auto operator()(Lhs const& lhs, Rhs const& rhs) const -> decltype(lhs%rhs)
            {
                return lhs%rhs;
            }
        };

        struct bitwise_or_op {
            template<class Lhs, class Rhs>
            constexpr auto operator()(Lhs const& lhs, Rhs const& rhs) const -> decltype(lhs | rhs)
            {
                return lhs | rhs;
            }
        };

        struct bitwise_and_op {
            template<class Lhs, class Rhs>
            constexpr auto operator()(Lhs const& lhs, Rhs const& rhs) const -> decltype(lhs & rhs)
            {
                return lhs & rhs;
            }
        };

        struct bitwise_xor_op {
            template<class Lhs, class Rhs>
            constexpr auto operator()(Lhs const& lhs, Rhs const& rhs) const -> decltype(lhs ^ rhs)
            {
                return lhs ^ rhs;
            }
        };

        struct shift_left_op {
            template<class Lhs, class Rhs>
            constexpr auto operator()(Lhs const& lhs, Rhs const& rhs) const -> decltype(lhs << rhs)
            {
                return lhs << rhs;
            }
        };

        struct shift_right_op {
            template<class Lhs, class Rhs>
            constexpr auto operator()(Lhs const& lhs, Rhs const& rhs) const -> decltype(lhs >> rhs)
            {
                return lhs >> rhs;
            }
        };

        struct equal_op {
            template<class Lhs, class Rhs>
            constexpr auto operator()(Lhs const& lhs, Rhs const& rhs) const -> decltype(lhs==rhs)
            {
                return lhs==rhs;
            }
        };

        struct not_equal_op {
            template<class Lhs, class Rhs>
            constexpr auto operator()(Lhs const& lhs, Rhs const& rhs) const -> decltype(lhs!=rhs)
            {
                return lhs!=rhs;
            }
        };

        struct less_than_op {
            template<class Lhs, class Rhs>
            constexpr auto operator()(Lhs const& lhs, Rhs const& rhs) const -> decltype(lhs<rhs)
            {
                return lhs<rhs;
            }
        };

        struct greater_than_op {
            template<class Lhs, class Rhs>
            constexpr auto operator()(Lhs const& lhs, Rhs const& rhs) const -> decltype(lhs>rhs)
            {
                return lhs>rhs;
            }
        };

        struct less_than_or_equal_op {
            template<class Lhs, class Rhs>
            constexpr auto operator()(Lhs const& lhs, Rhs const& rhs) const -> decltype(lhs<=rhs)
            {
                return lhs<=rhs;
            }
        };

        struct greater_than_or_equal_op {
            template<class Lhs, class Rhs>
            constexpr auto operator()(Lhs const& lhs, Rhs const& rhs) const -> decltype(lhs>=rhs)
            {
                return lhs>=rhs;
            }
        };

        struct assign_add_op {
            using binary = add_op;

            template<class Lhs, class Rhs>
            constexpr auto operator()(Lhs& lhs, Rhs const& rhs) const -> decltype(lhs += rhs)
            {
                return lhs += rhs;
            }
        };

        struct assign_subtract_op {
            using binary = subtract_op;

            template<class Lhs, class Rhs>
            constexpr auto operator()(Lhs& lhs, Rhs const& rhs) const -> decltype(lhs -= rhs)
            {
                return lhs -= rhs;
            }
        };

        struct assign_multiply_op {
            using binary = multiply_op;

            template<class Lhs, class Rhs>
            constexpr auto operator()(Lhs& lhs, Rhs const& rhs) const -> decltype(lhs *= rhs)
            {
                return lhs *= rhs;
            }
        };

        struct assign_divide_op {
            using binary = divide_op;

            template<class Lhs, class Rhs>
            constexpr auto operator()(Lhs& lhs, Rhs const& rhs) const -> decltype(lhs /= rhs)
            {
                return lhs /= rhs;
            }
        };

        struct assign_modulo_op {
            using binary = modulo_op;

            template<class Lhs, class Rhs>
            constexpr auto operator()(Lhs& lhs, Rhs const& rhs) const -> decltype(lhs %= rhs)
            {
                return lhs %= rhs;
            }
        };

        struct assign_bitwise_or_op {
            using binary = bitwise_or_op;

            template<class Lhs, class Rhs>
            constexpr auto operator()(Lhs& lhs, Rhs const& rhs) const -> decltype(lhs |= rhs)
            {
                return lhs |= rhs;
            }
        };

        struct assign_bitwise_and_op {
            using binary = bitwise_and_op;

            template<class Lhs, class Rhs>
            constexpr auto operator()(Lhs& lhs, Rhs const& rhs) const -> decltype(lhs &= rhs)
            {
                return lhs &= rhs;
            }
        };

        struct assign_bitwise_xor_op {
            using binary = bitwise_xor_op;

            template<class Lhs, class Rhs>
            constexpr auto operator()(Lhs& lhs, Rhs const& rhs) const -> decltype(lhs ^= rhs)
            {
                return lhs ^= rhs;
            }
        };

        struct assign_shift_left_op {
            using binary = shift_left_op;

            template<class Lhs, class Rhs>
            constexpr auto operator()(Lhs& lhs, Rhs const& rhs) const -> decltype(lhs <<= rhs)
            {
                return lhs <<= rhs;
            }
        };

        struct assign_shift_right_op {
            using binary = shift_right_op;

            template<class Lhs, class Rhs>
            constexpr auto operator()(Lhs& lhs, Rhs const& rhs) const -> decltype(lhs >>= rhs)
            {
                return lhs >>= rhs;
            }
        };

        static constexpr plus_op plus_tag{};
        static constexpr minus_op minus_tag{};

        static constexpr add_op add_tag{};
        static constexpr subtract_op subtract_tag{};
        static constexpr multiply_op multiply_tag{};
        static constexpr divide_op divide_tag{};
        static constexpr modulo_op modulo_tag{};

        static constexpr bitwise_or_op bitwise_or_tag{};
        static constexpr bitwise_and_op bitwise_and_tag{};
        static constexpr bitwise_xor_op bitwise_xor_tag{};
        static constexpr shift_left_op shift_left_tag{};
        static constexpr shift_right_op shift_right_tag{};

        static constexpr equal_op equal_tag{};
        static constexpr not_equal_op not_equal_tag{};
        static constexpr less_than_op less_than_tag{};
        static constexpr greater_than_op greater_than_tag{};
        static constexpr less_than_or_equal_op less_than_or_equal_tag{};
        static constexpr greater_than_or_equal_op greater_than_or_equal_tag{};

        static constexpr assign_add_op assign_add_tag{};
        static constexpr assign_subtract_op assign_subtract_tag{};
        static constexpr assign_multiply_op assign_multiply_tag{};
        static constexpr assign_divide_op assign_divide_tag{};
        static constexpr assign_modulo_op assign_modulo_tag{};

        static constexpr assign_bitwise_or_op assign_bitwise_or_tag{};
        static constexpr assign_bitwise_and_op assign_bitwise_and_tag{};
        static constexpr assign_bitwise_xor_op assign_bitwise_xor_tag{};
        static constexpr assign_shift_left_op assign_shift_left_tag{};
        static constexpr assign_shift_right_op assign_shift_right_tag{};

        ////////////////////////////////////////////////////////////////////////////////
        // cnl::_impl::rep_op_result

        template<class Operator, class Lhs, class Rhs>
        using op_result = decltype(Operator()(std::declval<Lhs>(), std::declval<Rhs>()));

        ////////////////////////////////////////////////////////////////////////////////
        // generic operators

        // can be specialized for any types without need for excessive boilerplate;
        // will only match operands for which cnl::_impl::wants_generic_ops is defined
        template<class Operator, class Operand, class Enable = void>
        struct unary_operator;

        template<class Operator, class LhsOperand, class RhsOperand, class Enable = void>
        struct binary_operator;

        template<class Operator, class LhsOperand, class RhsOperand, class Enable = void>
        struct comparison_operator;

        template<class Operator, class LhsOperand, class RhsOperand, class Enable = void>
        struct compound_assignment_operator {
            constexpr LhsOperand& operator()(LhsOperand& lhs, RhsOperand const& rhs) const
            {
                return lhs = static_cast<LhsOperand>(
                        binary_operator<typename Operator::binary, LhsOperand, RhsOperand>()(lhs, rhs));
            }
        };
    }

    namespace _operators_impl {
        ////////////////////////////////////////////////////////////////////////////////
        // cnl::_operators_impl::enable_unary_t

        template<class Operand, class T>
        using enable_unary_t = ::cnl::_impl::enable_if_t<_impl::wants_generic_ops<Operand>::value, T>;

        ////////////////////////////////////////////////////////////////////////////////
        // cnl::_operators_impl::enable_unary_t

        template<class LhsOperand, class RhsOperand>
        struct enable_binary;

        template<class LhsOperand, int LhsSize, class RhsOperand>
        struct enable_binary<LhsOperand[LhsSize], RhsOperand> : std::false_type {
        };

        template<class LhsOperand, class RhsOperand, int RhsSize>
        struct enable_binary<LhsOperand, RhsOperand[RhsSize]> : std::false_type {
        };

        template<class LhsOperand, class RhsOperand>
        struct enable_binary
                : std::integral_constant<
                        bool,
                        (numeric_limits<LhsOperand>::is_specialized && numeric_limits<RhsOperand>::is_specialized)
                                && (_impl::wants_generic_ops<LhsOperand>::value
                                        || _impl::wants_generic_ops<RhsOperand>::value)> {
        };

        template<class LhsOperand, class RhsOperand, class T>
        using enable_binary_t = _impl::enable_if_t<enable_binary<LhsOperand, RhsOperand>::value, T>;
    }

    ////////////////////////////////////////////////////////////////////////////////
    // operator overloads

    // unary operators
#define CNL_DEFINE_UNARY_OPERATOR(OP, NAME) \
    template<class Operand> \
    constexpr auto operator OP (Operand const& operand) \
    -> decltype(cnl::_impl::unary_operator<cnl::_operators_impl::enable_unary_t< \
            Operand, cnl::_impl::NAME>, Operand>()(operand)) \
    { \
        return cnl::_impl::unary_operator<cnl::_impl::NAME, Operand>()(operand); \
    }

    CNL_DEFINE_UNARY_OPERATOR(+, plus_op);

    CNL_DEFINE_UNARY_OPERATOR(-, minus_op);

    // binary operators
#define CNL_DEFINE_BINARY_OPERATOR(OP, NAME) \
    template<class LhsOperand, class RhsOperand> \
    CNL_FORCE_INLINE constexpr auto operator OP (LhsOperand const& lhs, RhsOperand const& rhs) \
    -> decltype(cnl::_impl::binary_operator<cnl::_operators_impl::enable_binary_t< \
            LhsOperand, RhsOperand, cnl::_impl::NAME>, LhsOperand, RhsOperand>()(lhs, rhs)) \
    { \
        return cnl::_impl::binary_operator<cnl::_impl::NAME, LhsOperand, RhsOperand>()(lhs, rhs); \
    }

    CNL_DEFINE_BINARY_OPERATOR(+, add_op);

    CNL_DEFINE_BINARY_OPERATOR(-, subtract_op);

    CNL_DEFINE_BINARY_OPERATOR(*, multiply_op);

    CNL_DEFINE_BINARY_OPERATOR(/, divide_op);

    CNL_DEFINE_BINARY_OPERATOR(%, modulo_op);

    CNL_DEFINE_BINARY_OPERATOR(|, bitwise_or_op);

    CNL_DEFINE_BINARY_OPERATOR(&, bitwise_and_op);

    CNL_DEFINE_BINARY_OPERATOR(^, bitwise_xor_op);

    CNL_DEFINE_BINARY_OPERATOR(<<, shift_left_op);

    CNL_DEFINE_BINARY_OPERATOR(>>, shift_right_op);

    // comparison operators
#define CNL_DEFINE_COMPARISON_OPERATOR(OP, NAME) \
    template<class LhsOperand, class RhsOperand> \
    constexpr auto operator OP (LhsOperand const& lhs, RhsOperand const& rhs) \
    -> cnl::_operators_impl::enable_binary_t<LhsOperand, RhsOperand, decltype( \
            cnl::_impl::comparison_operator<cnl::_impl::NAME, LhsOperand, RhsOperand>()(lhs, rhs))> \
    { \
        return cnl::_impl::comparison_operator<cnl::_impl::NAME, LhsOperand, RhsOperand>()(lhs, rhs); \
    }

    CNL_DEFINE_COMPARISON_OPERATOR(==, equal_op);

    CNL_DEFINE_COMPARISON_OPERATOR(!=, not_equal_op);

    CNL_DEFINE_COMPARISON_OPERATOR(<, less_than_op);

    CNL_DEFINE_COMPARISON_OPERATOR(>, greater_than_op);

    CNL_DEFINE_COMPARISON_OPERATOR(<=, less_than_or_equal_op);

    CNL_DEFINE_COMPARISON_OPERATOR(>=, greater_than_or_equal_op);

    // compound assignment operators
#define CNL_DEFINE_COMPOUND_ASSIGNMENT_OPERATOR(OP, NAME) \
    template<class LhsOperand, class RhsOperand> \
    constexpr auto operator OP (LhsOperand& lhs, RhsOperand const& rhs) \
    -> cnl::_operators_impl::enable_binary_t<LhsOperand, RhsOperand, decltype( \
            cnl::_impl::compound_assignment_operator<cnl::_impl::NAME, LhsOperand, RhsOperand>()(lhs, rhs))> \
    { \
        return cnl::_impl::compound_assignment_operator<cnl::_impl::NAME, LhsOperand, RhsOperand>()(lhs, rhs); \
    }

    CNL_DEFINE_COMPOUND_ASSIGNMENT_OPERATOR(+=, assign_add_op);

    CNL_DEFINE_COMPOUND_ASSIGNMENT_OPERATOR(-=, assign_subtract_op);

    CNL_DEFINE_COMPOUND_ASSIGNMENT_OPERATOR(*=, assign_multiply_op);

    CNL_DEFINE_COMPOUND_ASSIGNMENT_OPERATOR(/=, assign_divide_op);

    CNL_DEFINE_COMPOUND_ASSIGNMENT_OPERATOR(%=, assign_modulo_op);

    CNL_DEFINE_COMPOUND_ASSIGNMENT_OPERATOR(|=, assign_bitwise_or_op);

    CNL_DEFINE_COMPOUND_ASSIGNMENT_OPERATOR(&=, assign_bitwise_and_op);

    CNL_DEFINE_COMPOUND_ASSIGNMENT_OPERATOR(^=, assign_bitwise_xor_op);

    CNL_DEFINE_COMPOUND_ASSIGNMENT_OPERATOR(<<=, assign_shift_left_op);

    CNL_DEFINE_COMPOUND_ASSIGNMENT_OPERATOR(>>=, assign_shift_right_op);
}

#endif //CNL_OPERATORS_H
