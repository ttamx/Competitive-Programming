import java.io.EOFException;
import java.io.IOException;

public class grader {
  public static void main(String[] args) throws IOException {
    highway_lib.run();
  }
}

class highway_lib {
  private static final int MAX_NUM_CALLS = 100;
  private static final long INF = 1L << 61;

  private static int N, M, A, B, S, T;
  private static int[] U, V;
  private static int[][] graph_adj, graph_ei;

  private static boolean answered, wrong_pair;
  private static int num_calls;

  static long ask(int[] w) {
    if (num_calls >= MAX_NUM_CALLS) {
      wrong_answer("more than 100 calls to ask");
    }
    ++num_calls;
    if (w.length != M) {
      wrong_answer("w is invalid");
    }
    for (int i = 0; i < M; ++i) {
      if (!(w[i] == 0 || w[i] == 1)) {
        wrong_answer("w is invalid");
      }
    }

    boolean[] visited = new boolean[N];
    long[] current_dist = new long[N];
    int[] qa = new int[M + 2], qb = new int[M + 2];
    int qa_top = 0, qa_end = 0;
    int qb_top = 0, qb_end = 0;
    for (int v = 0; v < N; ++v) {
      visited[v] = false;
      current_dist[v] = INF;
    }
    qa[qa_end++] = S;
    current_dist[S] = 0;
    while (qa_top != qa_end || qb_top != qb_end) {
      int v;
      if (qb_top == qb_end
          || (qa_top != qa_end && current_dist[qa[qa_top]] <= current_dist[qb[qb_top]])) {
        v = qa[qa_top++];
      } else {
        v = qb[qb_top++];
      }
      if (visited[v])
        continue;
      visited[v] = true;
      long d = current_dist[v];
      if (v == T) {
        return d;
      }
      for (int j = 0; j < graph_adj[v].length; ++j) {
        int vv = graph_adj[v][j];
        int ei = graph_ei[v][j];
        if (!visited[vv]) {
          if (w[ei] == 0) {
            if (current_dist[vv] > d + A) {
              current_dist[vv] = d + A;
              qa[qa_end++] = vv;
            }
          } else {
            if (current_dist[vv] > d + B) {
              current_dist[vv] = d + B;
              qb[qb_end++] = vv;
            }
          }
        }
      }
    }
    return -1;
  }

  static void answer(int s, int t) {
    if (answered) {
      wrong_answer("answered not exactly once");
    }
    answered = true;
    if (!((s == S && t == T) || (s == T && t == S))) {
      wrong_pair = true;
    }
  }

  private static boolean is_initialized = false;

  static void run() throws IOException {
    if (is_initialized) {
      System.out.println("Error: run() must not be called twice.");
      System.exit(1);
    }
    is_initialized = true;

    N = read_int();
    M = read_int();
    A = read_int();
    B = read_int();
    S = read_int();
    T = read_int();
    U = new int[M];
    V = new int[M];
    for (int i = 0; i < M; ++i) {
      U[i] = read_int();
      V[i] = read_int();
    }
    int[] degree = new int[N];
    for (int v = 0; v < N; ++v) {
      degree[v] = 0;
    }
    for (int i = 0; i < M; ++i) {
      ++degree[U[i]];
      ++degree[V[i]];
    }
    graph_adj = new int[N][];
    graph_ei = new int[N][];
    for (int v = 0; v < N; ++v) {
      graph_adj[v] = new int[degree[v]];
      graph_ei[v] = new int[degree[v]];
    }
    for (int i = 0; i < M; ++i) {
      --degree[U[i]];
      graph_adj[U[i]][degree[U[i]]] = V[i];
      graph_ei[U[i]][degree[U[i]]] = i;
      --degree[V[i]];
      graph_adj[V[i]][degree[V[i]]] = U[i];
      graph_ei[V[i]][degree[V[i]]] = i;
    }

    answered = false;
    wrong_pair = false;
    num_calls = 0;
    new highway().find_pair(N, U, V, A, B);
    if (!answered) {
      wrong_answer("answered not exactly once");
    }
    if (wrong_pair) {
      wrong_answer("{s, t} is wrong");
    }
    System.out.println("Accepted: " + num_calls);
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
