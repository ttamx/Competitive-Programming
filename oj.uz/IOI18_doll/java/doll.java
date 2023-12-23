public class doll {
  void create_circuit(int M, int[] A) {
    int N = A.length;
    int[] C = new int[M + 1];
    C[0] = -1;
    for (int i = 1; i <= M; ++i) {
      C[i] = 1;
    }
    int[] X = new int[N], Y = new int[N];
    for (int k = 0; k < N; ++k) {
      X[k] = Y[k] = A[k];
    }
    doll_lib.answer(C, X, Y);
  }
}
