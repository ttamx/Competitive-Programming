import java.util.ArrayList;
import java.io.File;
import java.io.PrintWriter;

public class grader {
	private static final int MAX_INSTRUCTIONS = 10_000;
	private static final int MAX_INPUTS = 1_000_000;

	private static final int AND = 0;
	private static final int OR = 1;
	private static final int XOR = 2;
	private static final int NOT = 3;

	private static boolean increasing(int a, int b, int c) {
		return a <= b && b <= c;
	}

	private static void error(String message) {
		System.out.println(message);
		System.exit(0);
	}
	
	private static class InstructionNetwork {

		private static class Instruction {
			private int type;
			private int[] input_indexes;

			private Instruction(int type, int[] input_indexes) {
				this.type = type;
				this.input_indexes = input_indexes.clone();
			}

			private int apply(int a, int b) {
				switch (type) {
					case AND:
						return a & b;
					case OR:
						return a | b;
					case XOR:
						return a ^ b;
					default:
						return 0;
				}
			}

			private int compute(ArrayList<Integer> memory_cells) {
				int r = memory_cells.get(input_indexes[0]);
				if (type == NOT)
					return 1 - r;
				for (int j = 1; j < input_indexes.length; j++)
					r = apply(r, memory_cells.get(input_indexes[j]));
				return r;
			}
		}

		private int input_size;
		private int total_inputs;
		private ArrayList<Instruction> instructions;
		
		private InstructionNetwork(int input_size) {
			this.input_size = input_size;
			this.total_inputs = 0;
			this.instructions = new ArrayList<Instruction>();
		}
		
		private int add_instruction(int type, int[] input_indexes) {
			if (input_indexes.length == 0)
				error("Instruction with no inputs");

			if (instructions.size() + 1 > MAX_INSTRUCTIONS)
				error("Too many instructions");
			
			if (total_inputs + input_indexes.length > MAX_INPUTS)
				error("Too many inputs");

			instructions.add(new Instruction(type, input_indexes));
			total_inputs += input_indexes.length;
			int new_index = input_size + instructions.size() - 1;
			
			for (int input_index : input_indexes)
				if (!increasing(0, input_index, new_index-1))
					error("Invalid index");
			
			return new_index;
		}
		
		private int compute(ArrayList<Integer> memory_cells) {
			for (Instruction instruction : instructions)
				memory_cells.add(instruction.compute(memory_cells));
			return memory_cells.get(memory_cells.size()-1);
		}
	}


	private static InstructionNetwork instructionNetwork;

	public static void main(String[] args) throws Exception {
		InputReader inputReader = new InputReader(System.in);
		int H = inputReader.readInt();
		int W = inputReader.readInt();
		int K = inputReader.readInt();

		PrintWriter log_file = new PrintWriter(new File("log.txt"));

		instructionNetwork = new InstructionNetwork(H * W);
		vision solver = new vision();
		solver.construct_network(H, W, K);
		
		while (true) {
			int rowA = inputReader.readInt();
			if (rowA == -1)
				break;
			int colA = inputReader.readInt();
			int rowB = inputReader.readInt();
			int colB = inputReader.readInt();
			
			if ((!increasing(0, rowA, H-1)) ||
				(!increasing(0, colA, W-1)) ||
				(!increasing(0, rowB, H-1)) ||
				(!increasing(0, colB, W-1)) ||
				(rowA == rowB && colA == colB)) {
				System.out.println("-1");
				log_file.println("-1");
				System.out.flush();
				log_file.flush();
				continue;
			}

			ArrayList<Integer> memory_cells = new ArrayList<>();
			for (int row = 0; row < H; row++)
				for (int col = 0; col < W; col++) {
					boolean active = (row == rowA && col == colA) || (row == rowB && col == colB);
					memory_cells.add(active ? 1 : 0);
				}
			int computation_result = instructionNetwork.compute(memory_cells);
			
			System.out.println(computation_result);
			System.out.flush();

			for(int i = 0; i < memory_cells.size(); i++)
				log_file.print(String.format(i > 0 ? " %d" : "%d", memory_cells.get(i)));
			log_file.println();
			log_file.flush();
		}
		inputReader.close();
		log_file.close();
	}

	public static int add_and(int[] Ns) {
		return instructionNetwork.add_instruction(AND, Ns);
	}

	public static int add_or(int[] Ns) {
		return instructionNetwork.add_instruction(OR, Ns);
	}

	public static int add_xor(int[] Ns) {
		return instructionNetwork.add_instruction(XOR, Ns);
	}

	public static int add_not(int N) {
		int[] Ns = {N};
		return instructionNetwork.add_instruction(NOT, Ns);
	}
}


class InputReader implements java.io.Closeable {
	private java.io.InputStream stream;
	private byte[] buf = new byte[1024];
	private int curChar;
	private int numChars;

	public InputReader(java.io.InputStream stream) {
		this.stream = stream;
	}
	
	@Override
	public void close() {
		try {
			this.stream.close();
		} catch (java.io.IOException e) {
		}
	}

	public int read() {
		if (numChars == -1) {
			throw new java.util.InputMismatchException();
		}
		if (curChar >= numChars) {
			curChar = 0;
			try {
				numChars = stream.read(buf);
			} catch (java.io.IOException e) {
				throw new java.util.InputMismatchException();
			}
			if (numChars <= 0) {
				return -1;
			}
		}
		return buf[curChar++];
	}

	public int readInt() {
		int c = eatWhite();
		int sgn = 1;
		if (c == '-') {
			sgn = -1;
			c = read();
		}
		int res = 0;
		do {
			if (c < '0' || c > '9') {
				throw new java.util.InputMismatchException();
			}
			res *= 10;
			res += c - '0';
			c = read();
		} while (!isSpaceChar(c));
		return res * sgn;
	}

	public String readString() {
		int c = eatWhite();
		StringBuilder res = new StringBuilder();
		do {
			if (Character.isValidCodePoint(c))
				res.appendCodePoint(c);
			c = read();
		} while (!isSpaceChar(c));
		return res.toString();
	}

	public String readLine() {
		StringBuilder res = new StringBuilder();
		while (true) {
			int c = read();
			if (c == '\n' || c == '\r' || c == -1)
				break;
			if (Character.isValidCodePoint(c))
				res.appendCodePoint(c);
		}
		return res.toString();
	}

	private int eatWhite() {
		int c = read();
		while (isSpaceChar(c)) {
			c = read();
		}
		return c;
	}

	public static boolean isSpaceChar(int c) {
		return c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == -1;
	}
}
