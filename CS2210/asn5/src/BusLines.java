import java.io.*;
import java.util.*;

public class BusLines {

	/**
	 * Declare instance variables
	 */
	private Graph graph;
	private GraphNode start;
	private GraphNode dest;
	private int maxTransfers;

	/**
	 * Constructor for building a city map with its bus lines from the input file.
	 * If the input file does not exist, this method should throw a MapException.
	 */
	BusLines(String inputFile) throws MapException, GraphException {
		// exception for null input file
		if (inputFile == null) {
			throw new MapException("map");
		}
		try {
			BufferedReader in = new BufferedReader(new FileReader(inputFile)); // read input file
			String firstLine = in.readLine(); // reads first line
			String[] factors = firstLine.split(" "); // splits first line

			int width = Integer.parseInt(factors[1]); // assign width
			int height = Integer.parseInt(factors[2]); // assign height
			maxTransfers = Integer.parseInt(factors[3]); // assign max transfers

			int size = width * height; // assign size of graph
			graph = new Graph(size); // create graph
			String line1;
			String line2;
			int symbol = 0; // counter for current node name
			while (symbol < size) { // checks if line 2 is null
				line1 = in.readLine(); // read line 1
				line2 = in.readLine(); // read line 1
				for (int i = 0; i < line1.length(); i++) {
					// check for start and destination
					if (line1.charAt(i) == 'S') {
						this.start = graph.getNode(symbol);
						// System.out.println(symbol);
					}
					if (line1.charAt(i) == 'D') {
						this.dest = graph.getNode(symbol);
						// System.out.println(symbol);
					}
					// if odd character on line 1
					if (i % 2 == 1) {
						if (line1.charAt(i) != ' ' && line1.charAt(i) != '.' && line1.charAt(i) != 'S'
								&& line1.charAt(i) != 'D') { // check for bus line
							// System.out.println(symbol + "-o>" + (symbol + 1));
							graph.insertEdge(graph.getNode(symbol - 1), graph.getNode(symbol), line1.charAt(i));
						}
						// if even character on line 2
					} else if (i % 2 == 0) {
						if (line2 != null) { // check if line2 null
							if (line2.charAt(i) != ' ') { // check if not null
								// System.out.println(symbol + "-e>" + (symbol + width));
								graph.insertEdge(graph.getNode(symbol), graph.getNode(symbol + width), line2.charAt(i));
							}
						}
						symbol++;
					}
				}
			}
			in.close();

		} catch (IOException e) {
			System.out.println("not found");
		}

	}

	/**
	 * Returns the graph representing the map. This method throws a MapException if
	 * the graph could not be created.
	 */
	Graph getGraph() throws MapException {
		if (this.graph == null) {
			throw new MapException("did not create");
		}
		return this.graph;
	}

	/**
	 * Returns a Java Iterator containing the nodes along the path from the starting
	 * point to the destination, if such a path exists. If the path does not exist,
	 * this method returns the value null.
	 */
	Iterator<GraphNode> trip() throws GraphException {
		System.out.println("start: " + this.start.getName() + " destination: " + this.dest.getName()
				+ " max transfers: " + this.maxTransfers);
		Stack<GraphNode> stack = new Stack<GraphNode>(); // stack to check nodes
		Iterator<GraphNode> iter = null; // initialize iterator to be returned

		if (pathDFS(this.start, stack, maxTransfers, ' ') != false) { // checks each starting edge
			iter = stack.iterator(); // assigns current stack to iterator
		}

		return iter;
	}

	/**
	 * Uses DFS algorithm to recursively iterate through nodes until end is found.
	 * Modified to fit restrictions based on buslines and maximum transfers
	 * permitted.
	 */
	private boolean pathDFS(GraphNode curr, Stack<GraphNode> stack, int transfers, char currLine)
			throws GraphException {
		curr.setMark(true); // marks current node
		// System.out.println("curr node: " + curr.getName());
		stack.push(curr); // pushes current node to stack
		if (curr.getName() == this.dest.getName()) { // if current node is destination
			return true; // return that destination was found
		}
		// otherwise
		Iterator<GraphEdge> incident = this.graph.incidentEdges(curr); // get iterator for current node edges
		while (incident.hasNext()) {
			GraphEdge edge = incident.next(); // gets next edge
			GraphNode next = edge.secondEndpoint(); // gets endpoint of edge
			if (next.getMark() == false) { // as long as next node is unmarked
				if (curr.getName() == this.start.getName()) {
					currLine = edge.getBusLine();
				}
				if (edge.getBusLine() == currLine) { // if edge is on the same busline as current busline
					if (pathDFS(next, stack, transfers, currLine) == true) { // recursive call with next node
						return true; // until true
					}
				} else { // if edge is not on same busline
					if (transfers > 0) { // if current transfers are less than max Transfers
						transfers--; // increase transfers
						char prev = currLine; // get reference to current line
						currLine = edge.getBusLine(); // set current line to new line
						if (pathDFS(curr, stack, transfers, currLine) == true) { // recursive call with new current
																					// line
																					// to find destination
							return true;
						} else { // if new bus line does not lead to current
							transfers++; // decrease transfers
							currLine = prev; // set current line to previous line
						}
					}
				}
			}
			// otherwise ignore node and check next
		}
		GraphNode top = stack.pop(); // pops top if did not find destination from that node
		top.setMark(false); // unmarks so that node can be revisited
		return false; // return that destination not found at this node
	}
}
