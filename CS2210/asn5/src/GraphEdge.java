/**
 * Dat Vo 250983323
 */
public class GraphEdge {
    GraphNode u;
    GraphNode v;
    char busLine;

    /**
     * The constructor for the class. The first two parameters are the endpoints of
     * the edge. The last parameter is the bus line to which the street represented
     * by the edge belongs.
     **/
    GraphEdge(GraphNode u, GraphNode v, char busLine) {
        this.u = u;
        this.v = v;
        this.busLine = busLine;

    }

    GraphNode firstEndpoint() {
        return this.u;
    } // Returns the first endpoint of the edge.

    GraphNode secondEndpoint() {
        return this.v;
    } // Returns the second endpoint of the edge.

    char getBusLine() {
        return this.busLine;
    } // Returns the name of the busLine to which the edge belongs.

}