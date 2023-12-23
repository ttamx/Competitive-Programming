import java.util.Scanner;

public class trilib {
    static int n;
    static long[] x, y;
    static int queries=0;
    static boolean is_inited = false;


    static void init() {
        if (is_inited)
            return;

	is_inited=true;

        Scanner in = new Scanner(System.in);

        n = in.nextInt();
        x = new long[n+1];
        y = new long[n+1];

        for (int i=1; i<=n; i++) {
		x[i] = in.nextInt();
                y[i] = in.nextInt(); 
        }
    }

    public static int get_n() {
        init();
        return n;
    }

    public static boolean is_clockwise(int a, int b, int c) {
	init();
	assert(a>=1 && a<=n);
	assert(b>=1 && b<=n);
	assert(c>=1 && c<=n);
	assert(a!=b && a!=c && b!=c);
	queries++;
        if(queries == 1000 * 1000 + 1)
            System.out.format("Too many queries!");
	return (x[b]-x[a])*(y[c]-y[a])-(x[c]-x[a])*(y[b]-y[a])<0;
    }

    public static void give_answer(int s) {
 	init();
    System.out.format("%d\n", s);
    }
}
