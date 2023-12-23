import java.io.EOFException;
import java.io.IOException;
import java.io.PrintWriter;

public class grader {
  public static void main(String[] args) throws IOException {
    int N = read_int();
    int Q = read_int();
    int[] H = new int[N];
    for (int i = 0; i < N; ++i) {
      H[i] = read_int();
    }
    int[] L = new int[Q];
    int[] R = new int[Q];
    for (int j = 0; j < Q; ++j) {
      L[j] = read_int();
      R[j] = read_int();
    }

    long[] C = new meetings().minimum_costs(H, L, R);
    PrintWriter writer = new PrintWriter(System.out);
    for (int j = 0; j < C.length; ++j) {
      writer.println(C[j]);
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
