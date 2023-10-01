import java.io.*;
import java.util.StringTokenizer;

public class grader {

    public static void main(String[] args) throws IOException {
        new grader().run();
    }
    
    void run() {
        br = new BufferedReader(new InputStreamReader(System.in));
        out = new PrintWriter(System.out);
        int n = nextInt();
        int l = nextInt();
        int u = nextInt();
        int[] w = new int[n];
        for (int i = 0; i < n; i++) {
            w[i] = nextInt();
        }
        int[] res = new molecules().find_subset(l, u, w);
        
        
        out.println(res.length);
        for (int x : res) {
            out.print(x + " ");
        }
        out.println();
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
