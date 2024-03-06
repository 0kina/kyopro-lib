use cargo_snippet::snippet;

// validation
// Unionfind (https://judge.yosupo.jp/submission/194544)
#[snippet("snipunionfind")]
pub mod union_find {
    pub struct UnionFind {
        par: Vec<usize>,
        sz: Vec<u32>,
    }

    impl UnionFind {
        pub fn new(n: usize) -> UnionFind {
            let par = (0..n).into_iter().collect();
            let sz = vec![0; n];
            UnionFind { par, sz }
        }

        pub fn root(&mut self, x: usize) -> usize {
            if self.par[x] == x {
                return x;
            }
            self.par[x] = self.root(self.par[x]);
            self.par[x]
        }

        pub fn size(&mut self, x: usize) -> u32 {
            let rx = self.root(x);
            self.sz[rx]
        }

        pub fn unite(&mut self, x: usize, y: usize) -> bool {
            let mut rx = self.root(x);
            let mut ry = self.root(y);
            if rx == ry {
                return false;
            }
            if self.sz[rx] < self.sz[ry] {
                std::mem::swap(&mut rx, &mut ry);
            }
            self.par[ry] = rx;
            self.sz[rx] += self.sz[ry];
            true
        }

        pub fn same(&mut self, x: usize, y: usize) -> bool {
            let rx = self.root(x);
            let ry = self.root(y);
            rx == ry
        }
    }
}
