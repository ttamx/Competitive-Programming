import java.io.*;
import java.util.StringTokenizer;

public class grader {
    public static void main(String[] args) {
        new grader().run();
    }

    private void run() {
        br = new BufferedReader(new InputStreamReader(System.in));
        out = new PrintWriter(System.out);
        int n = nextInt();
        int c = nextInt();
        int[] l = new int[n - 1];
        int[] d = new int[n];
        for (int i = 0; i < n - 1; i++) {
            l[i] = nextInt();
        }
        for (int i = 0; i < n; i++) {
            d[i] = nextInt();
        }
        long res = new shortcut().find_shortcut(n, l, d, c);
        

        out.println(res);
        out.close();
    }

    BufferedReader br;
    StringTokenizer st;
    PrintWriter out;

    String next() {
        try {
            while (st == null || !st.hasMoreTokens()) {
                st = new StringTokenizer(br.readLine());
            }
            return st.nextToken();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    int nextInt() {
        return Integer.parseInt(next());
    }
}

