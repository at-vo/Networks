public class OrderedDictionary implements OrderedDictionaryADT {

	private DictNode root;

	public OrderedDictionary() {
		Record input = null;
		this.root = new DictNode(input);

	}

	/**
	 * Returns the Record object with key k, or it returns null if such a record is
	 * not in the dictionary.
	 */
	public Record get(Pair k) {
		DictNode curr = this.root;
		if (curr.getElement() == null) {
			return null;
		} else {
			while (curr.getElement() != null) {
				int comp = k.compareTo(curr.getElement().getKey()); // compares current key to k
				if (comp == 1) {
					curr = curr.getRight(); // goes right if k greater
				} else if (comp == -1) {
					curr = curr.getLeft(); // goes left if k smaller
				} else if (comp == 0) {
					return curr.getElement(); // returns k when found

				}
			}
			return null; // returns null when reaches a null so key not found
		}

	}

	/**
	 * Returns the Node object with key k, or it returns null if such a record is
	 * not in the dictionary.
	 * 
	 * @param k
	 * @return
	 */
	public DictNode getNode(Pair k) {
		DictNode curr = this.root;
		if (curr == null) {
			return null;
		} else {
			while (curr.getElement() != null) {
				int comp = k.compareTo(curr.getElement().getKey());
				if (comp == 1) {
					curr = curr.getRight();
				} else if (comp == -1) {
					curr = curr.getLeft();
				} else if (comp == 0) {
					return curr;

				}
			}
			return null;
		}

	}

	/**
	 * Inserts r into the ordered dictionary. It throws a DictionaryException if a
	 * record with the same key as r is already in the dictionary.
	 */
	public void put(Record r) throws DictionaryException {

		// if empty dictionary
		if (this.root.getElement() == null) {
			this.root.setElement(r); // sets root
			// creates two leaf nodes that point to root
			this.root.setLeft(new DictNode(this.root));
			this.root.setRight(new DictNode(this.root));
		}
		// if key already in dictionary
		else if (get(r.getKey()) != null) {
			throw new DictionaryException("key already");
		} else {
			DictNode curr = this.root;
			// find leaf node
			while (curr.getElement() != null) {
				int comp = r.getKey().compareTo(curr.getElement().getKey());
				if (comp == 1) {
					curr = curr.getRight();
				} else if (comp == -1) {
					curr = curr.getLeft();
				}
			}
			curr.setElement(r); // sets new element in leaf
			// creates two leaf nodes that point to element put
			curr.setLeft(new DictNode(curr));
			curr.setRight(new DictNode(curr));
		}
	}

	/**
	 * Removes the record with key k from the dictionary. It throws a
	 * DictionaryException if the record is not in the dictionary.
	 */
	public void remove(Pair k) throws DictionaryException {
		if (get(k) == null || this.root.getElement() == null) {
			throw new DictionaryException("key not");
		} else {
			DictNode curr = getNode(k); // gets the node to be removed
			DictNode parRem = curr.getParent(); // gets parent of node to be removed

			// if the root is to be removed and it is a leaf
			if (this.root.getLeft().getElement() == null && this.root.getRight().getElement() == null) {
				Record input = null;
				this.root = new DictNode(input);
			}

			// if node to be removed has leaf children
			else if (curr.getLeft().getElement() == null && curr.getRight().getElement() == null) {
				if (parRem.getLeft() == curr) {
					parRem.setLeft(new DictNode(parRem));
				} else if (parRem.getRight() == curr) {
					parRem.setRight(new DictNode(parRem));
				}
			} else {
				Record succeed = successor(curr.getElement().getKey()); // find successor of k
				DictNode look = null;
				if (succeed != null) {
					look = getNode(succeed.getKey()); // finds node of successor
				}
				// if null successor then greatest element
				// therefore makes sure it does not have leaf child
				else if (succeed == null && curr.getLeft().getElement() != null) {
					succeed = predecessor(curr.getElement().getKey());
					DictNode left = curr.getLeft();
					look = getNode(succeed.getKey());
					DictNode lookPar = look.getParent();
					if (look.getLeft().getElement() != null) {
						DictNode pnt = look.getLeft();
						lookPar.setRight(pnt);
					}
					parRem.setRight(look);
					look.setParent(parRem);
					look.setLeft(left);
				}
				// if successor is the root
				if (succeed == this.root.getElement()) {
					DictNode newRoot = this.root.getLeft();
					parRem.setRight(look);
					look.setParent(parRem);
					newRoot.setParent(null);
				}
				// if successor children are leaves
				else if (look.getLeft().getElement() == null && look.getRight().getElement() == null) {
					look.setLeft(curr.getLeft());
					look.setRight(curr.getRight());
					if (parRem.getLeft() == curr) {
						parRem.setLeft(look);
					} else if (parRem.getRight() == curr) {
						parRem.setRight(look);
					}
					look.setParent(parRem);
				}
				// if successor is right child of node to be removed
				else if (curr.getRight() == look) {
					if (curr.getLeft().getElement() != null) {
						look.setLeft(curr.getLeft());
					}
					if (parRem.getLeft() == curr) {
						parRem.setLeft(look);
					} else if (parRem.getRight() == curr) {
						parRem.setRight(look);
					}
					look.setParent(parRem);
				}
			}

		}

	}

	/**
	 * Returns the successor of k (the record from the ordered dictionary with
	 * smallest key larger than k); it returns null if the given key has no
	 * successor. The given key DOES NOT need to be in the dictionary.
	 */
	public Record successor(Pair k) {
		if (this.root.getElement() == null) {
			return null;
		} else {
			DictNode curr = getNode(k);
			// key not in dict
			if (curr == null) {
				DictNode node = this.root;
				while (node.getRight().getElement() != null) {
					int comp = k.compareTo(node.getElement().getKey());
					if (comp == 1) {
						node = node.getRight();
					} else {
						break;
					}
				}
				while (node.getLeft().getElement() != null && node.getLeft().getElement().getKey().compareTo(k) == 1) {
					node = node.getLeft();
				}
				return node.getElement();

				// if key in dict
			} else {
				if (curr.getElement() != null && curr.getRight().getElement() != null) {
					curr = curr.getRight();
					while (curr.getLeft().getElement() != null) {
						curr = curr.getLeft();
					}
					return curr.getElement();
				} else {
					DictNode pred = curr.getParent();
					while (curr != this.root && pred.getRight() == curr) {
						curr = pred;
						pred = curr.getParent();
					}
					if (curr == this.root) {
						return null;

					} else {
						return pred.getElement();
					}
				}
			}
		}
	}

	/**
	 * Returns the predecessor of k (the record from the ordered dictionary with
	 * largest key smaller than k; it returns null if the given key has no
	 * predecessor. The given key DOES NOT need to be in the dictionary.
	 */
	public Record predecessor(Pair k) {
		boolean found = false;
		if (this.root.getElement() == null) {
			return null;
		} else {
			DictNode curr = getNode(k);
			// key not in dict
			if (curr == null) {
				DictNode node = this.root;
				while (node.getLeft().getElement() != null) {
					int comp = k.compareTo(node.getElement().getKey());
					if (comp == -1) {
						node = node.getLeft();
					} else {
						break;
					}
				}
				while (node.getRight().getElement() != null
						&& node.getRight().getElement().getKey().compareTo(k) == -1) {
					node = node.getRight();
				}
				return node.getElement();

				// if key in dict
			} else {
				if (curr.getElement() != null && curr.getLeft().getElement() != null) {
					curr = curr.getLeft();
					while (curr.getRight().getElement() != null) {
						curr = curr.getRight();
					}
					return curr.getElement();
				} else {
					DictNode pred = curr.getParent();
					while (curr != this.root && pred.getLeft() == curr) {
						curr = pred;
						pred = curr.getParent();
					}
					if (curr == this.root) {
						return null;

					} else {
						return pred.getElement();
					}
				}
			}

		}

	}

	/**
	 * Returns the record with smallest key in the ordered dictionary. Returns null
	 * if the dictionary is empty.
	 */
	public Record smallest() {
		if (this.root.getElement() == null) {
			return null;
		}
		DictNode curr = this.root;
		while (curr.getLeft().getElement() != null) {
			curr = curr.getLeft();
		}
		return curr.getElement();
	}

	/**
	 * Returns the record with largest key in the ordered dictionary. Returns null
	 * if the dictionary is empty.
	 */
	public Record largest() {
		if (this.root.getElement() == null) {
			return null;
		}
		DictNode curr = this.root;
		while (curr.getRight().getElement() != null) {
			curr = curr.getRight();
		}
		return curr.getElement();
	}

	/**
	 * DictNode private class
	 */
	private class DictNode {
		private DictNode left;
		private DictNode right;
		private DictNode parent;
		private Record element;

		public DictNode(Record element) {
			this.left = null;
			this.right = null;
			this.parent = null;
			this.element = element;
		}

		public DictNode(DictNode parent) {
			this.left = null;
			this.right = null;
			this.parent = parent;
			this.element = null;
		}

		public DictNode getLeft() {
			return this.left;
		}

		public DictNode getRight() {
			return this.right;
		}

		public boolean isLeaf() {
			return this.element == null;
		}

		public boolean isNodeLeaf() {
			return this.right.isLeaf() && this.left.isLeaf();
		}

		public DictNode getParent() {
			return this.parent;
		}

		public void setLeft(DictNode node) {
			this.left = node;
		}

		public void setRight(DictNode node) {
			this.right = node;
		}

		public void setParent(DictNode parent) {
			this.parent = parent;
		}

		public Record getElement() {
			return this.element;
		}

		public void setElement(Record element) {
			this.element = element;
		}
	}
}