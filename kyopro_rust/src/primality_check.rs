use cargo_snippet::snippet;

#[snippet("snipprimalitycheck")]
pub mod primality_check {
    fn pow_mod(base: u64, mut exp: u64, md: u64) -> u64 {
        let mut base = base as u128;
        let md = md as u128;
        let mut res = 1 % md;
        base %= md;
        while exp > 0 {
            if exp & 1 != 0 {
                res = (res * base) % md;
            }
            base = (base * base) % md;
            exp >>= 1;
        }
        res as u64
    }

    fn miller_rabin(n: u64, test_list: &Vec<u64>) -> bool {
        let mut s = 0;
        let mut d = n - 1;
        while d % 2 == 0 {
            s += 1;
            d >>= 1;
        }
        for &a in test_list.iter() {
            if n <= a {
                return true;
            }
            let mut x = pow_mod(a, d, n) as u128;
            if x != 1 {
                let mut t = 0;
                while t < s {
                    if x as u64 == n - 1 {
                        break;
                    }
                    x = (x * x) % n as u128;
                    t += 1;
                }
                if t == s {
                    return false;
                }
            }
        }
        true
    }

    pub fn is_prime(n: u64) -> bool {
        if n <= 1 {
            return false;
        }
        if n == 2 {
            return true;
        }
        if n % 2 == 0 {
            return false;
        }
        if n < 4759123141 {
            return miller_rabin(n, &vec![2, 7, 61]);
        } else {
            return miller_rabin(n, &vec![2, 325, 9375, 28178, 450775, 9780504, 1795265022]);
        }
    }
}
