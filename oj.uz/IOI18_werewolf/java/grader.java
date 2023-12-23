import java.io.EOFException;
import java.io.IOException;
import java.io.PrintWriter;

public class grader {
  public static void main(String[] args) throws IOException {
    int N = read_int();
    int M = read_int();
    int Q = read_int();
    int[] X = new int[M];
    int[] Y = new int[M];
    int[] S = new int[Q];
    int[] E = new int[Q];
    int[] L = new int[Q];
    int[] R = new int[Q];
    for (int j = 0; j < M; ++j) {
      X[j] = read_int();
      Y[j] = read_int();
    }
    for (int i = 0; i < Q; ++i) {
      S[i] = read_int();
      E[i] = read_int();
      L[i] = read_int();
      R[i] = read_int();
    }

    int[] A = new werewolf().check_validity(N, X, Y, S, E, L, R);
    PrintWriter writer = new PrintWriter(System.out);
    for (int i = 0; i < A.length; ++i) {
      writer.println(A[i]);
    }
    writer.close();
  }

  private static int read_int() throws IOException {
    int x = 0, c;
    for (;;) {
      c = System.in.read();
      if (c == -1) { throw new EOFException(); }
      if ('0' <= c && c <= '9') { break; }
      if (c == '-') { return -read_int(); }
    }
    for (;;) {
      x = x * 10 + (c - '0');
      c = System.in.read();
      if (!('0' <= c && c <= '9')) { return x; }
    }
  }
}
