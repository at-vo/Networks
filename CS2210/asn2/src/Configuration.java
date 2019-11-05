/**
 * Dat Vo 250983323 CS2210 ASN2
 * Configuration creates a configuration object that stores the string representation of the current game board
 */
public class Configuration {

	/* Instance Variables*/
	private String config;
	private int score;

	/**
	 * Configuration method
	 * @param config stores current gameboard as a string
	 * @param score stores score
	 */
	public Configuration (String config, int score) {
		
		this.config = config;
		this.score = score;
		
	}
	
	/**
	 * getStringConfiguration method
	 * @return configuration string
	 */
	public String getStringConfiguration() {
		return this.config;
	}
	
	/**
	 * getScore method
	 * @return score of configuration object
	 */
	public int getScore() {
		return this.score;
	}
}
