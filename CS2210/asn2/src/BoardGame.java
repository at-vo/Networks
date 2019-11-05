/**
 * Dat Vo 250983323 CS2210 ASN2 Board Game the algorithm for playgame to run tic
 * tac toe,
 */
public class BoardGame {

	/**
	 * Initialize Constants
	 */
	private static final int TABLE_SIZE = 9973;
	private static final char EMPTY = 'g';
	private static final char COMPUTER = 'o';
	private static final char HUMAN = 'b';

	/**
	 * Initialize Instance Variables
	 */
	private char[][] gameBoard;
	private int boardSize;
	private int emptyPos;
	private int maxLevel;

	/**
	 * Constructor for BoardGame
	 * 
	 * @param board_size
	 * @param empty_positions
	 * @param max_levels
	 */
	public BoardGame(int board_size, int empty_positions, int max_levels) {

		this.boardSize = board_size;
		this.emptyPos = empty_positions;
		this.maxLevel = max_levels;

		gameBoard = new char[board_size][board_size];

		for (int row = 0; row < board_size; row++) {
			for (int col = 0; col < board_size; col++) {
				gameBoard[row][col] = EMPTY;
			}
		}
	}

	/**
	 * HashDictionary Method returns an empty HashDictionary
	 * 
	 * @return a new hashDictionary object
	 */
	public HashDictionary makeDictionary() {

		HashDictionary toReturn = new HashDictionary(TABLE_SIZE);

		return toReturn;
	}

	/**
	 * isRepeatedConfig Method represents the content of gameBoard as a string then
	 * it checks whether the string representing the gameBoard is in dict
	 * 
	 * @param dict inputed dictionary
	 * @return score of this gameboard
	 */
	public int isRepeatedConfig(HashDictionary dict) {

		String gameString = getGameString(this.gameBoard);

		if (dict.getScore(gameString) != -1) {
			return dict.getScore(gameString);
		}
		return -1;
	}

	/**
	 * putConfig method first represents the content of gameBoard as a string then
	 * it inserts this string and its score in dict
	 * 
	 * @param dict  this hashDictionary
	 * @param score current score
	 */
	public void putConfig(HashDictionary dict, int score) {

		String gameString = getGameString(this.gameBoard);
		try {
			Configuration toPut = new Configuration(gameString, score);
			dict.put(toPut);
		} catch (DictionaryException e) {
			System.out.println("sysout");
		}
	}

	/**
	 * savePlay method stores symbol
	 * 
	 * @param row    current row
	 * @param col    current column
	 * @param symbol specified symbol
	 */
	public void savePlay(int row, int col, char symbol) {

		this.gameBoard[row][col] = symbol;
	}

	/**
	 * positionIsEmpty method
	 * 
	 * @param row current row
	 * @param col current column
	 * @return true if empty false otherwise
	 */
	public boolean positionIsEmpty(int row, int col) {

		if (this.gameBoard[row][col] == EMPTY) {
			return true;
		}
		return false;
	}

	/**
	 * tileOfComputer method
	 * 
	 * @param row current row
	 * @param col current column
	 * @return true if empty false otherwise
	 */
	public boolean tileOfComputer(int row, int col) {

		if (this.gameBoard[row][col] == COMPUTER) {
			return true;
		}
		return false;
	}

	/**
	 * tileOfHuman method
	 * 
	 * @param row current row
	 * @param col current column
	 * @return true if empty false otherwise
	 */
	public boolean tileOfHuman(int row, int col) {

		if (this.gameBoard[row][col] == HUMAN) {
			return true;
		}
		return false;
	}

	/**
	 * wins method looks for adjacent tiles of type symbol
	 * 
	 * @param symbol specificied symbol
	 * @return true if symbol wins
	 */
	public boolean wins(char symbol) {

		for (int row = 0; row < boardSize; row++) {
			int DiagTop = 0;
			int diagBottom = 0;
			int colCount = 0;
			int rowCount = 0;
			int diag = boardSize - 1; // keeps track of the diagonal from the bottom left to top right

			for (int col = 0; col < boardSize; col++) {
				if (gameBoard[row][col] == symbol) {
					rowCount++;
				}
				if (gameBoard[col][row] == symbol) {
					colCount++;
				}

				if (gameBoard[col][col] == symbol) {
					DiagTop++;
				}

				if (gameBoard[col][diag] == symbol) {
					diagBottom++;
				}
				diag--;

				if (colCount == boardSize || rowCount == boardSize) { // winning condition for rows and columns
					return true;
				}
				if (DiagTop == boardSize || diagBottom == boardSize) { // winning condition for diagonals
					return true;
				}
			}
		}

		return false;
	}

	/**
	 * isDraw method configuration corresponding to gameBoard is a draw assuming
	 * that the player that will perform the next move uses tiles of the type
	 * specified by symbol
	 * 
	 * @param symbol          specified symbol
	 * @param empty_positions number of empty positions
	 * @return true if a draw false if not
	 */
	public boolean isDraw(char symbol, int empty_positions) {
		this.emptyPos = empty_positions;

		if (wins(HUMAN) == false && wins(COMPUTER) == false) { // initial draw condition

			/* For empty position = 0 */
			if (this.emptyPos == 0) {
				for (int row = 0; row < boardSize; row++) {
					for (int col = 0; col < boardSize; col++) {
						if (gameBoard[row][col] == EMPTY) {
							return false;
						}
					}
				}
				return true;

				/* For empty position > 0 */
			} else if (this.emptyPos > 0) {

				int emptyCount = 0;
				for (int row = 0; row < boardSize; row++) {
					for (int col = 0; col < boardSize; col++) {
						if (gameBoard[row][col] == EMPTY) { // checks how many empty positions are on the board
							emptyCount++;
						}
					}
				}

				if (emptyCount == this.emptyPos) { // checks if the number of empty positions are equal to the ones on
													// the board
					for (int row = 0; row < boardSize; row++) {
						for (int col = 0; col < boardSize; col++) {
							int colCheck; // checks columns around a tile
							if (gameBoard[row][col] == EMPTY) {
								colCheck = row - 1;
								if (colCheck >= 0) {
									for (int colLeft = 0; colLeft < boardSize; colLeft++) { // check left of empty
										if (gameBoard[colCheck][colLeft] == symbol) {
											return false;
										}
									}
								}
								colCheck = row;
								for (int colCenter = 0; colCenter < boardSize; colCenter++) { // check empty column
									if (gameBoard[colCheck][colCenter] == symbol) {
										return false;
									}
								}
								colCheck = row + 1;
								if (colCheck < boardSize) {
									for (int colRight = 0; colRight < boardSize; colRight++) { // check right of empty
										if (gameBoard[colCheck][colRight] == symbol) {
											return false;
										}
									}
								}
								return true;
							}
						}
					}
				}
			}
		}
		return false;

	}

	/**
	 * evalBoard method
	 * 
	 * @param symbol          specified symbol
	 * @param empty_positions number of empty positions
	 * @return 3 if computer wins, 0 if human wins, 2 if draw, 1 otherwise
	 */
	public int evalBoard(char symbol, int empty_positions) {
		if (wins(COMPUTER)) {
			return 3;
		} else if (wins(HUMAN)) {
			return 0;
		} else if (isDraw(symbol, empty_positions)) {
			return 2;
		}
		return 1;
	}

	/**
	 * getGameString method creates string of current gameboard
	 * 
	 * @param board current gameboard
	 * @return string of gameboard
	 */
	private String getGameString(char[][] board) {
		String gameString = "";

		for (int row = 0; row < boardSize; row++) {
			for (int col = 0; col < boardSize; col++) {
				gameString += gameBoard[row][col];
			}
		}
		return gameString;
	}

}