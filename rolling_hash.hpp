typedef unsigned long long ull;

const ull B = 100000007; //ハッシュの基数

//bの中にaが存在する？
bool containSubString(string a, string b) {
    int al = a.length(), bl = b.length();
    if (al > bl) return false;
    
    //Bのal乗を計算
    ull t = 1;
    for (int i = 0; i < al; i++) t *= B;
    
    //aとbの最初のal文字に関するハッシュ値を計算
    ull ah = 0, bh = 0;
    for (int i = 0; i < al; i++) ah = ah * B + a[i];
    for (int i = 0; i < al; i++) bh = bh * B + b[i];
    
    //bの場所を一つずつ進めながらハッシュ値をチェック
    for (int i = 0; i + al <= bl; i++) {
        if (ah == bh) return true; //bのi文字目からのal文字が一致
        if (i + al < bl) bh = bh * B + b[i + al] - t * b[i];
    }
    
    return false;
}

//bの中にaは何個ある？
int countSubString(string a, string b) {
    int al = a.length(), bl = b.length();
    if (al > bl) return 0;
    
    //Bのal乗を計算
    ull t = 1;
    for (int i = 0; i < al; i++) t *= B;
    
    //aとbの最初のal文字に関するハッシュ値を計算
    ull ah = 0, bh = 0;
    for (int i = 0; i < al; i++) ah = ah * B + a[i];
    for (int i = 0; i < al; i++) bh = bh * B + b[i];
    
    int ret = 0;
    //bの場所を一つずつ進めながらハッシュ値をチェック
    for (int i = 0; i + al <= bl; i++) {
        if (ah == bh) ret++; //bのi文字目からのal文字が一致
        if (i + al < bl) bh = bh * B + b[i + al] - t * b[i];
    }
    
    return ret;
}
