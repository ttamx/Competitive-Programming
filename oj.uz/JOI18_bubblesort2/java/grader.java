import java.io.EOFException;
import java.io.IOException;

public class grader {
  public static void main(String[] args) throws IOException {
    int N = readInt();
    int Q = readInt();
    int[] A = new int[N];
    for (int i = 0; i < N; ++i) {
      A[i] = readInt();
    }
    int[] X = new int[Q];
    int[] V = new int[Q];
    for (int j = 0; j < Q; ++j) {
      X[j] = readInt();
      V[j] = readInt();
    }
    int[] answer = new bubblesort2().countScans(A, X, V);
    for (int j = 0; j < answer.length; ++j) {
      System.out.println(answer[j]);
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
