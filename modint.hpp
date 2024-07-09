#include <cstdint>
#include <concepts>
#include <macros.hpp>
#include <iostream>
#include <cassert>

namespace modint
{
    template<std::unsigned_integral auto m> class static_modint
    {
        uintmax_t v = 0;

        public:
        ALWAYS_INLINE static_modint() = default;

        ALWAYS_INLINE static_modint(std::integral auto x)
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

        ALWAYS_INLINE constexpr static_modint& operator++()
        {
            v++;
            if (v == m) v = 0;
            return *this;
        }

        ALWAYS_INLINE constexpr static_modint& operator--()
        {
            if (v == 0) v = m;
            v--;
            return *this;
        }

        ALWAYS_INLINE constexpr static_modint operator++(int)
        {
            static_modint res = *this;
            ++*this;
            return res;
        }

        ALWAYS_INLINE constexpr static_modint operator--(int)
        {
            static_modint res = *this;
            --*this;
            return res;
        }

        ALWAYS_INLINE constexpr static_modint& operator+=(const static_modint& rhs)
        {
            v += rhs.v;
            if (v >= m) v -= m;
            return *this;
        }

        ALWAYS_INLINE constexpr static_modint& operator-=(const static_modint& rhs)
        {
            v -= rhs.v;
            if (v >= m) v += m;
            return *this;
        }

        ALWAYS_INLINE constexpr static_modint& operator*=(const static_modint& rhs)
        {
            (v *= rhs.v) %= m;
            return *this;
        }

        ALWAYS_INLINE constexpr static_modint& operator/=(const static_modint& rhs)
        {
            return *this *= inv(rhs);
        }

        ALWAYS_INLINE constexpr static_modint& operator^=(const std::integral auto& rhs)
        {
            static_modint res = 1;
            for (uintmax_t t = rhs; t; t & 1 && (res *= *this, 0), *this *= *this, t >>= 1);
            return *this = res;
        }

        ALWAYS_INLINE constexpr friend static_modint operator+(static_modint lhs, const static_modint& rhs)
        {
            lhs += rhs;
            return lhs;
        }

        ALWAYS_INLINE constexpr friend static_modint operator-(static_modint lhs, const static_modint& rhs)
        {
            lhs -= rhs;
            return lhs;
        }

        ALWAYS_INLINE constexpr friend static_modint operator*(static_modint lhs, const static_modint& rhs)
        {
            lhs *= rhs;
            return lhs;
        }

        ALWAYS_INLINE constexpr friend static_modint operator/(static_modint lhs, const static_modint& rhs)
        {
            lhs /= rhs;
            return lhs;
        }

        ALWAYS_INLINE constexpr friend static_modint operator^(static_modint lhs, const std::integral auto& rhs)
        {
            lhs ^= rhs;
            return lhs;
        }

        ALWAYS_INLINE constexpr static_modint operator+()
        {
            return *this;
        }

        ALWAYS_INLINE constexpr static_modint operator-()
        {
            return static_modint() - *this;
        }

        ALWAYS_INLINE constexpr friend static_modint inv(const static_modint& obj)
        {
            static_modint res, new_res = 1;
            uintmax_t t = obj.mod(), new_t = obj.val();
            for (static_modint q; new_t; q = t / new_t, res -= q * new_res, t -= q.val() * new_t, std::swap(res, new_res), std::swap(t, new_t));
            assert(t == 1);
            return res;
        }
    };

    template<std::unsigned_integral auto m> ALWAYS_INLINE std::ostream& operator<<(std::ostream& os, const static_modint<m>& obj)
    {
        return os << obj.val();
    }

    template<std::unsigned_integral auto m> ALWAYS_INLINE std::istream& operator>>(std::istream& is, static_modint<m>& obj)
    {
        std::string s;
        is >> s, obj = 0;
        bool neg = s[0] == '-';
        for (uintmax_t i = neg; i < s.size(); i++)
        {
            if (!isdigit(s[i]))
            {
                is.setstate(std::ios::failbit);
                break;
            }
            (obj *= 10) += s[i] ^ 48;
        }
        if (neg) obj = -obj;
        return is;
    }
    
    template<std::unsigned_integral auto id> class dynamic_modint
    {
        uintmax_t v = 0;
        static uintmax_t m;

        public:
        ALWAYS_INLINE dynamic_modint() = default;

        ALWAYS_INLINE dynamic_modint(std::integral auto x)
        {
            x %= mod();
            if (x < 0) x += mod();
            v = x;
        }

        ALWAYS_INLINE constexpr uintmax_t val() const
        {
            return v;
        }

        ALWAYS_INLINE constexpr uintmax_t mod() const
        {
            assert(m);
            return m;
        }

        ALWAYS_INLINE constexpr dynamic_modint& operator++()
        {
            v++;
            if (v == mod()) v = 0;
            return *this;
        }

        ALWAYS_INLINE constexpr dynamic_modint& operator--()
        {
            if (v == 0) v = mod();
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
            if (v >= m) v -= mod();
            return *this;
        }

        ALWAYS_INLINE constexpr dynamic_modint& operator-=(const dynamic_modint& rhs)
        {
            v -= rhs.v;
            if (v >= m) v += mod();
            return *this;
        }

        ALWAYS_INLINE constexpr dynamic_modint& operator*=(const dynamic_modint& rhs)
        {
            (v *= rhs.v) %= mod();
            return *this;
        }

        ALWAYS_INLINE constexpr dynamic_modint& operator/=(const dynamic_modint& rhs)
        {
            return *this *= inv(rhs);
        }

        ALWAYS_INLINE constexpr dynamic_modint& operator^=(const std::integral auto& rhs)
        {
            dynamic_modint res = 1;
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

        ALWAYS_INLINE constexpr friend dynamic_modint inv(const dynamic_modint& obj)
        {
            dynamic_modint res, new_res = 1;
            uintmax_t t = obj.mod(), new_t = obj.val();
            for (dynamic_modint q; new_t; q = t / new_t, res -= q * new_res, t -= q.val() * new_t, std::swap(res, new_res), std::swap(t, new_t));
            assert(t == 1);
            return res;
        }

        ALWAYS_INLINE static void set_mod(std::unsigned_integral auto mod)
        {
            m = mod;
        }
    };

    template<std::unsigned_integral auto id> uintmax_t dynamic_modint<id>::m(0);

    template<std::unsigned_integral auto id> ALWAYS_INLINE std::ostream& operator<<(std::ostream& os, const dynamic_modint<id>& obj)
    {
        return os << obj.val();
    }

    template<std::unsigned_integral auto id> ALWAYS_INLINE std::istream& operator>>(std::istream& is, dynamic_modint<id>& obj)
    {
        std::string s;
        is >> s, obj = 0;
        bool neg = s[0] == '-';
        for (uintmax_t i = neg; i < s.size(); i++)
        {
            if (!isdigit(s[i]))
            {
                is.setstate(std::ios::failbit);
                break;
            }
            (obj *= 10) += s[i] ^ 48;
        }
        if (neg) obj = -obj;
        return is;
    }
}
