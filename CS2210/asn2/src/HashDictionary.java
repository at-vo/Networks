/**
 * Dat Vo 250983323 CS2210 ASN2
 */
public class HashDictionary implements DictionaryADT {

	/**
	 * Initialize instance variables
	 */
	private int size;
	private DictNode[] hashTable;

	/**
	 * constructor for hash dictionary that creates a dictionary of inputed size
	 */
	public HashDictionary(int size) {

		this.size = size;
		hashTable = new DictNode[this.size];
	}

	/**
	 * put method that places a configuration within a certain hash code returns a 1
	 * on each collision and a 0 if no collisions
	 */
	public int put(Configuration data) throws DictionaryException {

		int hash = hashFunction(data.getStringConfiguration()); // gets hash code of configuration
		DictNode toPut = new DictNode(data); // create node with configuration in it
		DictNode head = hashTable[hash]; // reference to hashtable entry of hashcode

		if (head == null) {
			hashTable[hash] = toPut;
			return 0;
		}
		while (head != null) {
			if (head.getElement().getStringConfiguration().equals(data.getStringConfiguration())) {

				throw new DictionaryException("configuration is");
			} else if (head.getNext() == null) {
				head.setNext(toPut);
				return 1;
			}
			head = head.getNext();
		}
		return 0;

	}

	/**
	 * Remove method that removes inputed configuration
	 */
	public void remove(String config) throws DictionaryException {
		int hash = hashFunction(config);
		boolean found = false;
		DictNode toFind = hashTable[hash];
		DictNode temp;

		if (toFind != null) {
			if (toFind.getElement().getStringConfiguration().equals(config) && toFind.getNext() == null) {
				found = true;
				hashTable[hash] = null;
			} else if (toFind.getElement().getStringConfiguration().equals(config) && toFind.getNext() != null) {
				found = true;
				toFind.setNext(toFind.getNext());
			} else {
				while (toFind.getNext() != null) {
					temp = toFind.getNext();
					if (temp.getElement().getStringConfiguration().equals(config)) {
						found = true;
						if (temp.getNext() != null) {
							toFind.setNext(temp.getNext());
						} else {
							temp = null;
						}
					}
					toFind = toFind.getNext();
				}
			}
		}
		if (found == false) {
			throw new DictionaryException("configuration is not");
		}

	}

	/**
	 * GetScore method that returns the score associated with a certain
	 * configuration
	 */
	public int getScore(String config) {

		int hash = hashFunction(config);
		DictNode toFind = hashTable[hash];
		while (toFind != null) {
			if (toFind.getElement().getStringConfiguration().equals(config)) {
				return toFind.getElement().getScore();
			}
			toFind = toFind.getNext();
		}
		return -1;

	}

	/**
	 * Hash function method that returns the hash code int associated with a string
	 * configuration
	 */
	private int hashFunction(String hashElement) {
		int hash = 0;
		int len = hashElement.length();
		for (int i = 0; i < len; i++) {
			hash = (31 * hash + (int) hashElement.charAt(i)) % this.size;
		}

		return hash % this.size;
	}

	/**
	 * Class DictNode used for creating a linked list
	 */
	private class DictNode {
		private DictNode next;
		private Configuration element;

		public DictNode() {
			this.next = null;
			this.element = null;
		}

		public DictNode(Configuration element) {
			this.next = null;
			this.element = element;
		}

		public DictNode getNext() {
			return this.next;
		}

		public void setNext(DictNode node) {
			this.next = node;
		}

		public Configuration getElement() {
			return this.element;
		}

		public void setElement(Configuration element) {
			this.element = element;
		}
	}

}
