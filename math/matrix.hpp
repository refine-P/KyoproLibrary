using vec = vector<ll>;
using mat = vector<vec>;

mat mul(mat& A, mat& B) {
	mat C(A.size(), vec(B[0].size(), 0));
	for (int i = 0; i < A.size(); i++) {
		for (int k = 0; k < B.size(); k++) {
			for (int j = 0; j < B[0].size(); j++) {
				C[i][j] += A[i][k] * B[k][j]; 
			}
		}
	}
	return C;
}

mat pow(mat A, ll n) {
	mat B(A.size(), vec(A.size(), 0));
	for (int i = 0; i < A.size(); i++) {
		B[i][i] = 1;
	}
	while (n > 0) {
		if (n & 1) B = mul(B, A);
		A = mul(A, A);
		n >>= 1;
	}
	return B;
}
