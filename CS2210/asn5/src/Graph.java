import java.util.Iterator;
import java.util.Stack;
import java.util.ArrayList;;


/**
 * Dat Vo 250983323
 */
public class Graph {

	/**
	 * Declare constants
	 */
	final static boolean unchecked = false;

	/**
	 * Declare instance variables
	 */
	ListNode[] list;
	int size;

	/**
	 * Creates a graph with n nodes and no edges. This is the constructor for the
	 * class. The names of the nodes are 0, 1, . . . , n−1. *
	 */
	public Graph(int n) {
		this.size = n;
		this.list = new ListNode[size];

		// for every value < n add a node with that value
		for (int i = 0; i < n; i++) {
			GraphNode nextGraphNode = new GraphNode(i);
			nextGraphNode.setMark(unchecked); // mark all nodes unchecked
			ListNode newNode = new ListNode(nextGraphNode);
			this.list[i] = newNode;
			this.list[i].setEdges(new ListEdge(null)); // set edges of node as linked list of edges
		}

	}

	/**
	 * Adds an edge connecting u and v and belonging to the specified bus line. This
	 * method throws a GraphException if either node does not exist or if in the
	 * graph there is already an edge connecting the given nodes.
	 */
	public void insertEdge(GraphNode u, GraphNode v, char busLine) throws GraphException {
		if (!this.list[u.getName()].getGraphNode().equals(u)) {
			throw new GraphException("node not in graph" + u.getName() + " insert");
		} else if (!this.list[v.getName()].getGraphNode().equals(v)) {
			throw new GraphException("node not in graph " + v.getName() + " insert");
		}

		// this.list[v.getName()].setParent(this.list[u.getName()]);

		// make and insert u->v graphEdge
		GraphEdge uEdge = new GraphEdge(u, v, busLine);
		ListEdge ulook = this.list[u.getName()].getEdges();
		while (ulook.getGraphEdge() != null) {
			if (ulook.getGraphEdge().equals(uEdge)) {
				throw new GraphException("edge already in graph " + u.getName() + " insert");
			} else {
				ulook = ulook.getNext();
			}
		}
		// set edge in list and add null element node
		if (ulook.getGraphEdge() == null) {
			ulook.setGraphEdge(uEdge);
			ulook.setNext(new ListEdge(null));
		}

		// make and insert v->u graphEdge
		GraphEdge vEdge = new GraphEdge(v, u, busLine);
		ListEdge vlook = this.list[v.getName()].getEdges();
		while (vlook.getGraphEdge() != null) {
			if (vlook.getGraphEdge().equals(uEdge)) {
				throw new GraphException("edge already in graph " + v.getName() + " insert");
			} else {
				vlook = vlook.getNext();
			}
		}
		// set edge in list and add null element node
		if (vlook.getGraphEdge() == null) {
			vlook.setGraphEdge(vEdge);
			vlook.setNext(new ListEdge(null));
		}

	}

	/**
	 * Returns the node with the specified name. If no node with this name exists,
	 * the method should throw a GraphException.
	 */
	public GraphNode getNode(int name) throws GraphException {
		if (name >= this.size) {
			throw new GraphException("invalid graphnode " + name + " getNode");
		}
		GraphNode get = this.list[name].getGraphNode(); // gets from graph
		if (get != null) { // checks for null
			return get;
		} else {
			throw new GraphException("no node named, " + name + " getNode");
		}
	}

	/**
	 * Returns a Java Iterator storing all the edges incident on node u. It returns
	 * null if u does not have any edges incident on it.
	 */
	public Iterator<GraphEdge> incidentEdges(GraphNode u) throws GraphException {
		if (u.getName() >= this.size) {
			throw new GraphException("invalid graphnode " + u.getName() + " iterator");
		}
		Iterator<GraphEdge> iter;
		Stack<GraphEdge> arr = new Stack<GraphEdge>(); // make array list to store edges
		ArrayList<GraphEdge> ver = new ArrayList<GraphEdge>(); // make array list to store edges

		ListEdge look = this.list[u.getName()].getEdges(); // gets list of edges
		// while not a null graph edge iterate through list and add edge to list
		while (look.getGraphEdge() != null) {
			arr.add(look.getGraphEdge());
			look = look.getNext();
		}
		
		while (!arr.isEmpty()) {
			GraphEdge pop = arr.pop();
			ver.add(pop);
		}
		
		return iter = ver.iterator();
	}

	/**
	 * Returns the edge connecting nodes u and v. This method throws a
	 * GraphException if there is no edge between u and v.
	 */
	public GraphEdge getEdge(GraphNode u, GraphNode v) throws GraphException {
		if (u.getName() >= this.size) {
			throw new GraphException("invalid graphnode " + u.getName() + " getEdge");
		} else if (v.getName() >= this.size) {
			throw new GraphException("invalid graphnode " + v.getName() + " getEdge");
		}
		Iterator<GraphEdge> iter = incidentEdges(u); // call incidentEdges on node u
		GraphEdge found = null;
		while (iter.hasNext()) {
			GraphEdge check = iter.next(); // get next edge
			if (check.secondEndpoint().equals(v)) {
				found = check;
				break;
			}
		}
		if (found == null) { // if didnt find edge
			throw new GraphException("no edge from, GetEdge");
		} else {
			return found;
		}
	}

	/**
	 * Returns true if nodes u and v are adjacent; it returns false otherwise.
	 */
	public boolean areAdjacent(GraphNode u, GraphNode v) throws GraphException {
		if (u.getName() >= this.size) {
			throw new GraphException("invalid graphnode " + u.getName() + " Adjacent");
		} else if (v.getName() >= this.size) {
			throw new GraphException("invalid graphnode " + v.getName() + " Adjacent");
		}

		// check if v is beside u
		if (u.getName() == v.getName() - 1) {
			return true;
		} else if (u.getName() == v.getName() + 1) {
			return true;
		} else {
			return false;
		}
	}

	/**************************
	 * Private class ListNode *
	 **************************/
	private class ListNode {
		GraphNode graphNode;
		ListNode parent;
		ListEdge edges;

		public ListNode(GraphNode graphNode) {
			this.graphNode = graphNode;
		}

		public GraphNode getGraphNode() {
			return this.graphNode;
		}

		public void setGraphNode(GraphNode node) {
			this.graphNode = node;
		}

		public ListEdge getEdges() {
			return this.edges;
		}

		public void setEdges(ListEdge edge) {
			this.edges = edge;
		}

		/*
		 * public ListNode getParent() { return this.parent; }
		 * 
		 * public void setParent(ListNode parent) { this.parent = parent; }
		 */
	}

	/**************************
	 * Private class ListEdge *
	 **************************/
	private class ListEdge {
		ListEdge next;
		GraphEdge graphEdge;

		public ListEdge(GraphEdge graphEdge) {
			this.graphEdge = graphEdge;
		}

		public GraphEdge getGraphEdge() {
			return this.graphEdge;
		}

		public void setGraphEdge(GraphEdge graphEdge) {
			this.graphEdge = graphEdge;
		}

		public ListEdge getNext() {
			return this.next;
		}

		public void setNext(ListEdge next) {
			this.next = next;
		}

	}
}