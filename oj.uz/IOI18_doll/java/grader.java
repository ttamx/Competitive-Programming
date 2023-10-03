import java.io.EOFException;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.PrintWriter;

public class grader {
  public static void main(String[] args) throws IOException {
    doll_lib.run();
  }
}

class doll_lib {
  private static final int P_MAX = 20000000;
  private static final int S_MAX = 400000;

  private static int M, N;
  private static int[] A;

  private static boolean answered;
  private static int S;
  private static int[] IC, IX, IY;

  public static void answer(int[] C, int[] X, int[] Y) {
    if (answered) {
      wrong_answer("answered not exactly once");
    }
    answered = true;
    if (C.length != M + 1) {
      wrong_answer("wrong array length");
    }
    if (X.length != Y.length) {
      wrong_answer("wrong array length");
    }
    S = X.length;
    IC = C;
    IX = X;
    IY = Y;
  }

  private static boolean is_initialized = false;

  public static void run() throws FileNotFoundException, IOException {
    if (is_initialized) {
      System.out.println("Error: run() must not be called twice.");
      System.exit(1);
    }
    is_initialized = true;

    M = read_int();
    N = read_int();
    A = new int[N];
    for (int i = 0; i < N; ++i) {
      A[i] = read_int();
    }

    answered = false;
    new doll().create_circuit(M, A);
    if (!answered) {
      wrong_answer("answered not exactly once");
    }
    PrintWriter writer_out = new PrintWriter("out.txt");
    writer_out.println(S);
    for (int i = 0; i <= M; ++i) {
      writer_out.println(IC[i]);
    }
    for (int j = 1; j <= S; ++j) {
      writer_out.println(IX[j - 1] + " " + IY[j - 1]);
    }
    writer_out.close();
    simulate();
  }

  private static void simulate() throws FileNotFoundException {
    if (S > S_MAX) {
      wrong_answer("over " + S_MAX + " switches");
    }
    for (int i = 0; i <= M; ++i) {
      if (!(-S <= IC[i] && IC[i] <= M)) {
        wrong_answer("wrong serial number");
      }
    }
    for (int j = 1; j <= S; ++j) {
      if (!(-S <= IX[j - 1] && IX[j - 1] <= M)) {
        wrong_answer("wrong serial number");
      }
      if (!(-S <= IY[j - 1] && IY[j - 1] <= M)) {
        wrong_answer("wrong serial number");
      }
    }

    int P = 0;
    boolean[] state = new boolean[S + 1];
    int pos = IC[0];
    int k = 0;
    PrintWriter writer_log = new PrintWriter("log.txt");
    writer_log.println(0);
    for (;;) {
      writer_log.println(pos);
      if (pos < 0) {
        if (++P > P_MAX) {
          writer_log.close();
          wrong_answer("over " + P_MAX + " inversions");
        }
        state[-pos] = !state[-pos];
        pos = state[-pos] ? IX[-(1 + pos)] : IY[-(1 + pos)];
      } else {
        if (pos == 0) {
          break;
        }
        if (k >= N) {
          writer_log.close();
          wrong_answer("wrong motion");
        }
        if (pos != A[k++]) {
          writer_log.close();
          wrong_answer("wrong motion");
        }
        pos = IC[pos];
      }
    }
    writer_log.close();
    if (k != N) {
      wrong_answer("wrong motion");
    }
    for (int j = 1; j <= S; ++j) {
      if (state[j]) {
        wrong_answer("state 'Y'");
      }
    }
    System.out.println("Accepted: " + S + " " + P);
  }

  private static void wrong_answer(String MSG) {
    System.out.println("Wrong Answer: " + MSG);
    System.exit(0);
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
