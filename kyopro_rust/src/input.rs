use cargo_snippet::snippet;

#[snippet("snipinput")]
pub mod input {
    use std::{fmt::Debug, io, str::FromStr, string::String};
    fn get_line_inner<R: io::BufRead>(mut reader: R) -> String {
        let mut s = std::string::String::new();
        reader.read_line(&mut s).unwrap();
        s.trim().to_owned()
    }

    #[cfg(not(test))]
    fn get_line() -> String {
        get_line_inner(std::io::stdin().lock())
    }

    #[cfg(test)]
    fn get_line() -> String {
        let reader = std::io::Cursor::new(b"2 4 5\n");
        get_line_inner(reader)
    }

    pub fn input_vec<T>() -> Vec<T>
    where
        T: FromStr,
        <T as FromStr>::Err: Debug,
    {
        let s = get_line();
        let ws = s.split_whitespace();
        let mut values = Vec::<T>::new();
        for w in ws {
            values.push(w.parse().unwrap());
        }
        values
    }

    pub fn input_val<T>() -> T
    where
        T: FromStr,
        <T as FromStr>::Err: Debug,
    {
        input_vec::<T>().swap_remove(0)
    }

    pub fn input_pair<T, U>() -> (T, U)
    where
        T: FromStr,
        <T as FromStr>::Err: Debug,
        U: FromStr,
        <U as FromStr>::Err: Debug,
    {
        let p = input_vec::<String>();
        let t = T::from_str(&p[0]).unwrap();
        let u = U::from_str(&p[1]).unwrap();
        (t, u)
    }
}

#[cfg(test)]
mod test_input {
    use super::*;

    #[test]
    fn test_input_vec_usize() {
        let result = input::input_vec::<usize>();
        assert_eq!(result, vec![2usize, 4usize, 5usize]);
    }
}
