public class meetings {
  long[] minimum_costs(int[] H, int[] L, int[] R) {
    int Q = L.length;
    long[] C = new long[Q];
    for (int j = 0; j < Q; ++j) {
      C[j] = H[L[j]];
    }
    return C;
  }
}
