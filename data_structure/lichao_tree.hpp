// 参照: https://github.com/LumaKernel/lib-cpp/blob/master/src/dynamic-programming/convex-hull-trick/LiChaoTree.cpp
// 最小化: Comp = less<T>, 最大化: Comp = greater<T> 
template<class T = ll, class Comp = less<T> >
struct LiChaoTree {
	using Line = pair<T, T>;
	static inline T f(const Line& line, T x) { return line.first * x + line.second; }

	static Comp comp;

	int n;
	vector<Line> data;
	vector<int> used;
	vector<T> xs;

private:
	// [l, r)
	void add(int l, int r, const Line& line) {
		int l0 = l, r0 = r;
		int sz = 1;
		for (l += n, r += n; l < r; l >>= 1, r >>= 1, sz <<= 1) {
			if (l & 1) add(l, l0, l0 + sz, line), l0 += sz, ++l;
			if (r & 1) --r, r0 -= sz, add(r, r0, r0 + sz, line);
		}
	}

	void add(int k, int l, int r, Line line) {
		if (!used[k]) {
			used[k] = true;
			data[k] = line;
			return;
		}

		T cur_ly = f(data[k], xs[l]), cur_ry = f(data[k], xs[r - 1]);
		T nex_ly = f(line, xs[l]), nex_ry = f(line, xs[r - 1]);
		
		if (comp(cur_ly, nex_ly) && comp(cur_ry, nex_ry)) return;
		if (comp(nex_ly, cur_ly) && comp(nex_ry, cur_ry)) {
			data[k] = line;
			return;
		}
		
		if (r - l == 1) return;

		int m = (l + r) >> 1;
		if (comp(cur_ly, nex_ly)) swap(data[k], line);
		if (comp(f(line, xs[m]), f(data[k], xs[m]))) {
			swap(data[k], line);
			add((k << 1) | 1, m, r, line);
		} else {
			add(k << 1, l, m, line);
		}
	}

public:
	// 前処理（事前にクエリのx座標を渡す必要あり）
	void addx(T x) { xs.emplace_back(x); }
	void prebuild() {
		sort(xs.begin(), xs.end());
		xs.erase(unique(xs.begin(), xs.end()), xs.end());

		int sz = xs.size();
		n = 1;
		while (n < sz) n <<= 1;
		xs.resize(n, xs.back());

		data.resize(n << 1);
		used.resize(n << 1);
	}

	// 直線追加: ax + b
	void add(T a, T b) { add(0, n, Line(a, b)); }

	// 線分追加: ax + b (l <= x <= r)
	void add(T a, T b, T l, T r) {
		int li = lower_bound(xs.begin(), xs.end(), l) - xs.begin();
		int ri = upper_bound(xs.begin(), xs.end(), r) - xs.begin();
		add(li, ri, Line(a, b));
	}

	// ax+bが最小/最大となる(a,b)を取得
	Line get(T x) {
		int idx = -1;
		for (int i = lower_bound(xs.begin(), xs.end(), x) - xs.begin() + n; i > 0; i >>= 1) {
			if (!used[i]) continue;
			if (idx == -1 || comp(f(data[i], x), f(data[idx], x))) idx = i;
		}
		assert(idx > 0 && idx < (n << 1));
		return data[idx];
	}

	// ax+bの最小/最大値を取得
	T query(T x) { return f(get(x), x); }
};

template<class T, class Comp>
Comp LiChaoTree<T, Comp>::comp;
