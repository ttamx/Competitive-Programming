import java.io.EOFException;
import java.io.IOException;
import java.io.PrintWriter;

public class grader {
  public static void main(String[] args) throws IOException {
    int H = read_int();
    int W = read_int();
    int Q = read_int();
    int[] R = new int[H * W];
    int[] C = new int[H * W];
    for (int i = 0; i < H * W; ++i) {
      R[i] = read_int();
      C[i] = read_int();
    }
    int[] A = new int[Q];
    int[] B = new int[Q];
    for (int j = 0; j < Q; ++j) {
      A[j] = read_int();
      B[j] = read_int();
    }

    seats user = new seats();
    user.give_initial_chart(H, W, R, C);
    PrintWriter writer = new PrintWriter(System.out);
    for (int j = 0; j < Q; ++j) {
      int answer = user.swap_seats(A[j], B[j]);
      writer.println(answer);
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
