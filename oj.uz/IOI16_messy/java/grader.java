import java.io.IOException;
import java.io.InputStream;
import java.util.Arrays;
import java.util.HashSet;
import java.util.InputMismatchException;
import java.util.Set;

/**
 * @author egor@egork.net
 */
public class grader {
    private static Set<String> set = new HashSet<>();
    private static boolean compiled = false;
    private static int n;
    private static int[] p;
    private static int w;
    private static int r;

    public static void main(String[] args) {
        InputReader in = new InputReader(System.in);
        n = in.readInt();
        w = in.readInt();
        r = in.readInt();
        p = new int[n];
        for (int i = 0; i < n; i++) {
            p[i] = in.readInt();
        }
        int[] answer = new messy().restore_permutation(n, w, r);
        
        if (answer.length != n) {
            wa();
        }
        
        
        System.out.print(answer[0]);
        for (int i = 1; i < n; i++) {
            System.out.print(" " + answer[i]);
        }
        System.out.println();
    }
    
    private static void wa() {
        System.out.println("WA");
        System.exit(0);
    }

    public static void add_element(String x) {
        if (--w < 0 || compiled || !check(x)) {
            wa();
        }
        set.add(x);
    }

    private static boolean check(String x) {
        if (x.length() != n) {
            return false;
        }
        for (int i = 0; i < n; i++) {
            if (x.charAt(i) != '0' && x.charAt(i) != '1') {
                return false;
            }
        }
        return true;
    }

    public static boolean check_element(String x) {
        if (--r < 0 || !compiled || !check(x)) {
            wa();
        }
        return set.contains(x);
    }

    public static void compile_set() {
        if (compiled) {
            wa();
        }
        compiled = true;
        Set<String> compiledSet = new HashSet<>();
        char[] compiledElement = new char[n];
        for (String s : set) {
            for (int i = 0; i < n; i++) {
                compiledElement[i] = s.charAt(p[i]);
            }
            compiledSet.add(new String(compiledElement));
        }
        set = compiledSet;
    }
}

class InputReader {
    private InputStream stream;
    private byte[] buf = new byte[1024];
    private int curChar;
    private int numChars;

    public InputReader(InputStream stream) {
        this.stream = stream;
    }

    public int read() {
        if (numChars == -1) {
            throw new InputMismatchException();
        }
        if (curChar >= numChars) {
            curChar = 0;
            try {
                numChars = stream.read(buf);
            } catch (IOException e) {
                throw new InputMismatchException();
            }
            if (numChars <= 0) {
                return -1;
            }
        }
        return buf[curChar++];
    }

    public int readInt() {
        int c = read();
        while (isSpaceChar(c)) {
            c = read();
        }
        int sgn = 1;
        if (c == '-') {
            sgn = -1;
            c = read();
        }
        int res = 0;
        do {
            if (c < '0' || c > '9') {
                throw new InputMismatchException();
            }
            res *= 10;
            res += c - '0';
            c = read();
        } while (!isSpaceChar(c));
        return res * sgn;
    }

    public static boolean isSpaceChar(int c) {
        return c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == -1;
    }
}
