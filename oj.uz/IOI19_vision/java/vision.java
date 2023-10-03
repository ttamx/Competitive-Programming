public class vision {
	public void construct_network(int H, int W, int K) {
		int[] Ns;
		Ns = new int[] {0, 1};
		int a = grader.add_and(Ns);
		Ns = new int[] {0, a};
		int b = grader.add_or(Ns);
		Ns = new int[] {0, 1, b};
		int c = grader.add_xor(Ns);
		grader.add_not(c);
	}
}
