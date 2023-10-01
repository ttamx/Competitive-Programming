public class highway {
  void find_pair(int N, int[] U, int[] V, int A, int B) {
    int M = U.length;
    for (int j = 0; j < 50; ++j) {
      int[] w = new int[M];
      for (int i = 0; i < M; ++i) {
        w[i] = 0;
      }
      long toll = highway_lib.ask(w);
    }
    highway_lib.answer(0, N - 1);
  }
}
