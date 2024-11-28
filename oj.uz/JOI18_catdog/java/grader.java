import java.io.EOFException;
import java.io.IOException;

public class grader {
  public static void main(String[] args) throws IOException {
    catdog solver = new catdog();
    int N = readInt();
    int[] A = new int[N - 1];
    int[] B = new int[N - 1];
    for (int i = 0; i < N - 1; ++i) {
      A[i] = readInt();
      B[i] = readInt();
    }
    int Q = readInt();
    int[] T = new int[Q];
    int[] v = new int[Q];
    for (int j = 0; j < Q; ++j) {
      T[j] = readInt();
      v[j] = readInt();
    }
    solver.initialize(N, A, B);
    for (int j = 0; j < Q; ++j) {
      switch (T[j]) {
        case 1:
          System.out.println(solver.cat(v[j]));
          break;
        case 2:
          System.out.println(solver.dog(v[j]));
          break;
        case 3:
          System.out.println(solver.neighbor(v[j]));
          break;
        default:
          System.err.println("Error while reading input.");
          System.exit(1);
      }
    }
  }

  private static int readInt() throws IOException {
    int x = 0, c;
    for (; ; ) {
      c = System.in.read();
      if ('0' <= c && c <= '9') break;
      if (c == -1) throw new EOFException();
      if (c == '-') return -readInt();
    }
    for (; ; ) {
      x = x * 10 + (c - '0');
      c = System.in.read();
      if (!('0' <= c && c <= '9')) return x;
    }
  }
}
