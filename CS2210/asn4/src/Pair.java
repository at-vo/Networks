public class Pair {

	String word;
	String type;

	/**
	 * 
	 * @param word
	 * @param type
	 */
	public Pair(String word, String type) {
		// A constructor which initializes a new Pair object
		// with the specified word and type.
		this.word = word;
		this.type = type;
	}
	/**
	 * 
	 * @return
	 */
	public String getWord() {
		// Returns the word stored in this Pair object.
		return this.word;
	}
	/**
	 * 
	 * @return
	 */
	public String getType() {
		// Returns the type stored in this Pair object.
		return this.type;
	}
	/**
	 * 
	 * @param k
	 * @return
	 */
	public int compareTo(Pair k) {
		// Returns 0 if the key stored in this Pair object is equal to
		// k, returns -1 if the key stored in this Pair object is smaller than k, and it
		// returns 1 otherwise.
		if (this.word.equals(k.getWord()) && this.type.equals(k.getType())) {
			return 0;
		}
		else{
			int compWord = this.word.compareTo(k.getWord());
			if (compWord < 0){return -1;}
			else if (compWord == 0){
				int compType = this.type.compareTo(k.getType());
				if (compType < 0){return -1;}
			}
		}
		return 1;
	}
}
