#include <cstdint>
#include <concepts>
#include <macros.hpp>
#include <iostream>
#include <cassert>

namespace modint
{
    template<std::unsigned_integral auto m> class modint
    {
        uintmax_t v = 0;

        public:
        ALWAYS_INLINE modint() = default;

        ALWAYS_INLINE modint(std::integral auto x)
        {
            x %= m;
            if (x < 0) x += m;
            v = x;
        }

        ALWAYS_INLINE constexpr uintmax_t val() const
        {
            return v;
        }

        ALWAYS_INLINE constexpr uintmax_t mod() const
        {
            return m;
        }

        ALWAYS_INLINE constexpr modint& operator++()
        {
            v++;
            if (v == m) v = 0;
            return *this;
        }

        ALWAYS_INLINE constexpr modint& operator--()
        {
            if (v == 0) v = m;
            v--;
            return *this;
        }

        ALWAYS_INLINE constexpr modint operator++(int)
        {
            modint res = *this;
            ++*this;
            return res;
        }

        ALWAYS_INLINE constexpr modint operator--(int)
        {
            modint res = *this;
            --*this;
            return res;
        }

        ALWAYS_INLINE constexpr modint& operator+=(const modint& rhs)
        {
            v += rhs.v;
            if (v >= m) v -= m;
            return *this;
        }

        ALWAYS_INLINE constexpr modint& operator-=(const modint& rhs)
        {
            v -= rhs.v;
            if (v >= m) v += m;
            return *this;
        }

        ALWAYS_INLINE constexpr modint& operator*=(const modint& rhs)
        {
            (v *= rhs.v) %= m;
            return *this;
        }

        ALWAYS_INLINE constexpr modint& operator/=(const modint& rhs)
        {
            return *this *= inv(rhs);
        }

        ALWAYS_INLINE constexpr modint& operator^=(const std::integral auto& rhs)
        {
            modint res = 1;
            for (uintmax_t t = rhs; t; t & 1 && (res *= *this, 0), *this *= *this, t >>= 1);
            return *this = res;
        }

        ALWAYS_INLINE constexpr friend modint operator+(modint lhs, const modint& rhs)
        {
            lhs += rhs;
            return lhs;
        }

        ALWAYS_INLINE constexpr friend modint operator-(modint lhs, const modint& rhs)
        {
            lhs -= rhs;
            return lhs;
        }

        ALWAYS_INLINE constexpr friend modint operator*(modint lhs, const modint& rhs)
        {
            lhs *= rhs;
            return lhs;
        }

        ALWAYS_INLINE constexpr friend modint operator/(modint lhs, const modint& rhs)
        {
            lhs /= rhs;
            return lhs;
        }

        ALWAYS_INLINE constexpr friend modint operator^(modint lhs, const std::integral auto& rhs)
        {
            lhs ^= rhs;
            return lhs;
        }

        ALWAYS_INLINE constexpr modint operator+()
        {
            return *this;
        }

        ALWAYS_INLINE constexpr modint operator-()
        {
            return modint() - *this;
        }
    };

    template<std::unsigned_integral auto m> ALWAYS_INLINE constexpr modint<m> inv(const modint<m>& obj)
    {
        modint<m> res, new_res = 1;
        uintmax_t t = obj.mod(), new_t = obj.val();
        for (modint<m> q; new_t; q = t / new_t, res -= q * new_res, t -= q.val() * new_t, std::swap(res, new_res), std::swap(t, new_t));
        assert(t == 1);
        return res;
    }

    template<std::unsigned_integral auto m> ALWAYS_INLINE std::ostream& operator<<(std::ostream& os, const modint<m>& obj)
    {
        return os << obj.val();
    }

    template<std::unsigned_integral auto m> ALWAYS_INLINE std::istream& operator>>(std::istream& is, modint<m>& obj)
    {
        std::string s;
        is >> s, obj = 0;
        for (char c : s)
        {
            if (!isdigit(c))
            {
                is.setstate(std::ios::failbit);
                break;
            }
            (obj *= 10) += c ^ 48;
        }
        return is;
    }

    class dynamic_modint;

    ALWAYS_INLINE constexpr dynamic_modint inv(const dynamic_modint& obj);

    class dynamic_modint
    {
        uintmax_t v = 0, m = 0;

        public:
        ALWAYS_INLINE dynamic_modint() = default;

        ALWAYS_INLINE dynamic_modint(std::unsigned_integral auto mod) : m(mod), v(0)
        {

        }

        ALWAYS_INLINE dynamic_modint(std::integral auto x, std::unsigned_integral auto mod) : m(mod)
        {
            x %= m;
            if (x < 0) x += m;
            v = x;
        }

        ALWAYS_INLINE constexpr uintmax_t val() const
        {
            return v;
        }

        ALWAYS_INLINE constexpr uintmax_t mod() const
        {
            return m;
        }

        ALWAYS_INLINE constexpr dynamic_modint& operator++()
        {
            v++;
            if (v == m) v = 0;
            return *this;
        }

        ALWAYS_INLINE constexpr dynamic_modint& operator--()
        {
            if (v == 0) v = m;
            v--;
            return *this;
        }

        ALWAYS_INLINE constexpr dynamic_modint operator++(int)
        {
            dynamic_modint res = *this;
            ++*this;
            return res;
        }

        ALWAYS_INLINE constexpr dynamic_modint operator--(int)
        {
            dynamic_modint res = *this;
            --*this;
            return res;
        }

        ALWAYS_INLINE constexpr dynamic_modint& operator+=(const dynamic_modint& rhs)
        {
            v += rhs.v;
            if (v >= m) v -= m;
            return *this;
        }

        ALWAYS_INLINE constexpr dynamic_modint& operator-=(const dynamic_modint& rhs)
        {
            v -= rhs.v;
            if (v >= m) v += m;
            return *this;
        }

        ALWAYS_INLINE constexpr dynamic_modint& operator*=(const dynamic_modint& rhs)
        {
            (v *= rhs.v) %= m;
            return *this;
        }

        ALWAYS_INLINE constexpr dynamic_modint& operator/=(const dynamic_modint& rhs)
        {
            return *this *= inv(rhs);
        }

        ALWAYS_INLINE constexpr dynamic_modint& operator^=(const std::integral auto& rhs)
        {
            dynamic_modint res = {1, m};
            for (uintmax_t t = rhs; t; t & 1 && (res *= *this, 0), *this *= *this, t >>= 1);
            return *this = res;
        }

        ALWAYS_INLINE constexpr friend dynamic_modint operator+(dynamic_modint lhs, dynamic_modint& rhs)
        {
            lhs += rhs;
            return lhs;
        }

        ALWAYS_INLINE constexpr friend dynamic_modint operator-(dynamic_modint lhs, const dynamic_modint& rhs)
        {
            lhs -= rhs;
            return lhs;
        }

        ALWAYS_INLINE constexpr friend dynamic_modint operator*(dynamic_modint lhs, const dynamic_modint& rhs)
        {
            lhs *= rhs;
            return lhs;
        }

        ALWAYS_INLINE constexpr friend dynamic_modint operator/(dynamic_modint lhs, const dynamic_modint& rhs)
        {
            lhs /= rhs;
            return lhs;
        }

        ALWAYS_INLINE constexpr friend dynamic_modint operator^(dynamic_modint lhs, const std::integral auto& rhs)
        {
            lhs ^= rhs;
            return lhs;
        }

        ALWAYS_INLINE constexpr dynamic_modint operator+()
        {
            return *this;
        }

        ALWAYS_INLINE constexpr dynamic_modint operator-()
        {
            return dynamic_modint() - *this;
        }
    };

    ALWAYS_INLINE constexpr dynamic_modint inv(const dynamic_modint& obj)
    {
        uintmax_t m = obj.mod();
        dynamic_modint res(0, m), new_res(1, m);
        uintmax_t t = obj.mod(), new_t = obj.val();
        for (dynamic_modint q(m); new_t; q = t / new_t, res -= q * new_res, t -= q.val() * new_t, std::swap(res, new_res), std::swap(t, new_t));
        assert(t == 1);
        return res;
    }

    ALWAYS_INLINE std::ostream& operator<<(std::ostream& os, const dynamic_modint& obj)
    {
        return os << obj.val();
    }

    ALWAYS_INLINE std::istream& operator>>(std::istream& is, dynamic_modint& obj)
    {
        std::string s;
        is >> s, obj = {0, obj.mod()};
        dynamic_modint f(10, obj.mod());
        for (char c : s)
        {
            if (!isdigit(c))
            {
                is.setstate(std::ios::failbit);
                break;
            }
            (obj *= f) += {c ^ 48, obj.mod()};
        }
        return is;
    }
}