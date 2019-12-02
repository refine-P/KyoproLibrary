constexpr double ticks_per_sec = 2800000000;
constexpr double ticks_per_sec_inv = 1.0 / ticks_per_sec;
inline double rdtsc() { // in seconds
    uint32_t lo, hi;
    asm volatile ("rdtsc" : "=a" (lo), "=d" (hi));
    return (((uint64_t)hi << 32) | lo) * ticks_per_sec_inv;
}
constexpr double TLE = 3; // sec
constexpr double time_limit = TLE * 0.98;

unsigned int randxor()
{
    static unsigned int x=123456789,y=362436069,z=521288629,w=88675123;
    unsigned int t;
    t=(x^(x<<11));x=y;y=z;z=w; return( w=(w^(w>>19))^(t^(t>>8)) );
}

template<typename hoge>
void my_shuffle(vector<hoge>& v) {
	int sz = v.size();
	for (int i = sz - 1; i >= 1; i--) {
		swap(v[i], v[randxor() % (i + 1)]);
	}
}
