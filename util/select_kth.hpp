// O(N)で配列aの[start, end)の中でk番目に小さい値を求める
template<class T>
T select_kth(vector<T>& a, int start, int end, int k) {
    vector<T> v(a.begin() + start, a.begin() + end);
    nth_element(v.begin(), v.begin() + k, v.end());
    return v[k];
}
