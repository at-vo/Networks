/**
 * Dat Vo 250983323
 */
public class GraphNode {
    private int name;
    private boolean mark;

    /**
     * This is the constructor for the class and it creates an unmarked node with the given name. 
     */
    public GraphNode(int name) {
        this.name = name;
    }
    public void setMark(boolean mark){
        this.mark = mark;
    }// Marks the node with the specified value.

    public boolean getMark() {
        return this.mark;
    } // Returns the value with which the node has been marked.

    public int getName() {
        return this.name;
    } // Returns the name of the node.
}
