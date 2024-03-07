use cargo_snippet::snippet;

// validation
// Shortest Path (https://judge.yosupo.jp/submission/195418)
#[snippet("snipdijkstra")]
pub mod dijkstra {
    use std::cmp::Reverse;
    use std::collections::BinaryHeap;
    pub struct Dijkstra<'a, T: std::ops::Add<Output = T> + Copy + Ord> {
        start: usize,
        parent: Vec<usize>,
        distance: Vec<T>,
        graph: &'a Vec<Vec<(usize, T)>>,
        inf: T
    }

    impl<'a, T: std::ops::Add<Output = T> + Copy + Ord> Dijkstra<'a, T> {
        /// `graph`は重み付き有向グラフの隣接リスト表現
        pub fn new(s: usize, graph: &'a Vec<Vec<(usize, T)>>, zero: T, inf: T) -> Dijkstra<T> {
            let mut edges = Vec::new();
            let n = graph.len();
            for u in 0..n {
                for &(v, c) in graph[u].iter() {
                    edges.push((u, v, c));
                }
            }
            let parent = vec![n; n];
            let mut distance = vec![inf; n];
            distance[s] = zero;
            let mut dijk = Dijkstra {
                start: s,
                parent,
                distance,
                graph,
                inf: inf
            };
            dijk.construct();
            dijk
        }

        fn construct(&mut self) {
            let mut pque = BinaryHeap::new();
            pque.push(Reverse((self.distance[self.start], self.start)));
            while pque.len() > 0 {
                let (d, v) = pque.pop().unwrap().0;
                if d >= self.distance[v] {
                    continue;
                }
                for &(vv, dd) in self.graph[v].iter() {
                    let new_d = d + dd;
                    if new_d >= self.distance[vv] {
                        continue;
                    }
                    self.parent[vv] = v;
                    self.distance[vv] = new_d;
                    pque.push(Reverse((new_d, vv)));
                }
            }
        }

        pub fn path_to(&self, v: usize) -> Option<Vec<usize>> {
            if self.distance[v] == self.inf {
                return None;
            }
            let mut path = vec![v];
            while path[path.len() - 1] != self.start {
                path.push(self.parent[path[path.len() - 1]]);
            }
            path.reverse();
            Some(path)
        }

        pub fn distance_to(&self, v: usize) -> Option<T> {
            if self.distance[v] == self.inf {
                return None
            }
            Some(self.distance[v])
        }
    }
}
