#include <bit>
#include <macros.hpp>
#include <modint.hpp>

using mint = modint::dynamic_modint<0u>;

namespace prime
{
    uint8_t bases[] = "<\r\"\r%\r&i*5,6#\n\n\n\n\n++\"\"D5'\n(\n/\r+\r#\r(\n\r\n/7:#\n5\r\r>\nI\n%3\n&(+9\n\r\n\"'\n\r\n+\n)'.\n+)\r&\"%\n#\r\r\"\n\r\"\r'*'/\r/%0%\n'+\r\"%\r\n\n,%\n\n++3\r\n\"*/\n+:\r\n&\"\r&\n7\r,(\r'%\n\nG\n#&\"\n*(\n\n8*&\r(;&\n\n\n6R\",.\r\r\n'(<*.%*B\r\"\r\r&\"(\n&:0I%\n\r\n\r\"/\n\r\"\r\n\r)\n%\n,#\r35(%\r\n+'\n\r%\n3(=\r\r\"\r\n.#\n('B\n\n\r-\"#;K\n\n8\"#)((%\r\n'%#\n&\"\n++/#5\n\n\n<\n\n95\r#&*\n&6\r\n\r'\n6&\n\n\r\n\r)(\n(\n\r\r\n\n\"\r\r+\r2%E+##\"\"'\n5<'(/\"2;/\r'5\n3M*<\n\r\n/\n\n\n\"\n\n&\r\r\r''\n\n\r\n%,\"\")%#\r";

    ALWAYS_INLINE constexpr bool test(uint32_t n)
    {
        mint::set_mod(n);

        if (n < 2) return false;
        if (!(n ^ 2 && n ^ 3 && n ^ 5 && n ^ 7)) return true;
        if (!(n & 1 && n % 3 && n % 5 && n % 7)) return false;
        if (n < 121) return n ^ 1;

        mint x = bases[0xaff7b4ull * n >> 7 & 1023];
        uint32_t t = n - 1, d = std::countr_zero(t);
        x ^= (t >>= d);
        if (x.val() == 1) return true;
        for (uint32_t i = 0; i < d; i++)
        {
            if (x.val() == n - 1) return true;
            x ^= 2;
        }
        return false;
    }

    bool test(uint64_t n);
}
