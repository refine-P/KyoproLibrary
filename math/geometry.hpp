using P = complex<double>;

#define EPS 1e-10
#define EQ(a,b) (abs((a)-(b)) < EPS)
#define EQV(a,b) (EQ((a).real(),(b).real()) && EQ((a).imag(),(b).imag()))

//内積
double dot(P a, P b) {
    return a.real() * b.real() + a.imag() * b.imag();
}

//外積
double cross(P a, P b) {
    return a.real() * b.imag() - a.imag() * b.real();
}

//点の進行方向
int ccw(P a, P b, P c) {
    b -= a;
    c -= a;
    if (cross(b, c) > 0) return 1;   //counter clockwise
    if (cross(b, c) < 0) return -1;  //clockwise
    if (dot(b, c) < 0) return 2;     //c--a--b on line
    if (abs(b) < abs(c)) return -2;  //a--b--c on line
    return 0;  //a--c--b(b==c含む) on line
}

//2直線の直交判定
bool is_orthogonal(P a1, P a2, P b1, P b2) {
    return EQ(dot(a1 - a2, b1 - b2), 0.0);
}

//2直線の平行判定
bool is_parallel(P a1, P a2, P b1, P b2) {
    return EQ(cross(a1 - a2, b1 - b2), 0.0);
}

//点cが直線a,b上にあるか
bool is_point_on_line(P a, P b, P c) {
    return is_parallel(c, a, b, a);
}

//点cが線分a,b上にあるか
bool is_point_on_segment(P a, P b, P c) {
    return abs(a - c) + abs(c - b) < abs(a - b) + EPS;
}

//点a,bを通る直線と点cとの距離
double is_distance_l_p(P a, P b, P c) {
    return abs(cross(b - a, c - a)) / abs(b - a);
}

//点a,bを通る線分と点cとの距離
double is_distance_s_p(P a, P b, P c) {
    if (dot(b - a, c - a) < EPS) return abs(c - a);
    if (dot(a - b, c - b) < EPS) return abs(c - b);
    return is_distance_l_p(a, b, c);
}

//線分a1,a2と線分b1,b2の交差判定
bool is_intersected_s(P a1, P a2, P b1, P b2) {
    return cross(a1 - a2, b1 - a1) * cross(a1 - a2, b2 - a1) < EPS &&
           cross(b1 - b2, a1 - b1) * cross(b1 - b2, a2 - b1) < EPS;
}

//線分a1,a2と線分b1,b2の交点計算
P intersection_s(P a1, P a2, P b1, P b2) {
    P b = b1 - b2;
    double d1 = abs(cross(b, a1 - b1));
    double d2 = abs(cross(b, a2 - b1));
    double t = d1 / (d1 + d2);
    return a1 + (a2 - a1) * t;
}

//直線a1,a2と直線b1,b2の交点計算
P intersection_l(P a1, P a2, P b1, P b2) {
    P a = a2 - a1;
    P b = b2 - b1;
    return a1 + a * cross(b, b1 - a1) / cross(b, a);
}

vector<P> convex_hull(vector<P>& ps) {
    auto comp = [](const P& p1, const P& p2) { //辞書順で比較
        return (p1.real() != p2.real() ? p1.real() < p2.real() : p1.imag() < p2.imag());
    };
    sort(ps.begin(), ps.end(), comp);

    vector<P> res;
    for (P& p : ps) {
        while (res.size() > 1 && cross(res.back() - *prev(res.end(), 2), p - res.back()) < 0) {
            res.pop_back();
        }
        res.push_back(p);
    }

    for (int i = (int)ps.size() - 2, t = res.size(); i >= 0; i--) {
        while (res.size() > t && cross(res.back() - *prev(res.end(), 2), ps[i] - res.back()) < 0) {
            res.pop_back();
        }
        res.push_back(ps[i]);        
    }
    res.pop_back();
    return res;
}
