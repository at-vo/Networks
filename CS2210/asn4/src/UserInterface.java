import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.StringTokenizer;

/**
 * User Interface Class
 * 
 * @author Dat Vo 250983323
 *
 */
public class UserInterface {
	/**
	 * Main Method
	 * 
	 * @param args
	 */
	public static void main(String[] args) {
		OrderedDictionary dict = new OrderedDictionary();

		/* read in dictionary file */
		try {
			BufferedReader in = new BufferedReader(new FileReader(args[0]));
			String word = in.readLine();
			String data;
			String type;

			while (word != null) {
				data = in.readLine();
				if (data.contains(".mid") || data.contains(".wav")) {
					type = "audio";
				} else if (data.contains(".jpg") || data.contains(".gif")) {
					type = "image";
				} else {
					type = "text";
				}
				try {
					dict.put(new Record(new Pair(word.toLowerCase(), type), data.toLowerCase()));
				} catch (DictionaryException e) {
					System.out.println("Record already in dictionary");
				}
				word = in.readLine();
			}

			in.close();
		} catch (IOException e) {
			System.out.println("file not found");
		}

		boolean notFinish = true;
		String line = "";
		StringReader keyboard;

		while (notFinish) {

			String word = "", type = "", data = "", prefix = "";

			keyboard = new StringReader();
			line = keyboard.read("Enter a command: ");
			StringTokenizer read = new StringTokenizer(line);

			if (read.hasMoreTokens()) {
				switch (read.nextToken().toLowerCase()) {
				case "get":
					if (read.hasMoreElements()) {
						word = read.nextToken();
						get(dict, word.toLowerCase());
					} else {
						System.out.println("invalid command.");
					}
					break;

				case "delete":
					if (read.hasMoreElements()) {
						word = read.nextToken();
						if (read.hasMoreElements()) {
							type = read.nextToken();
						} else {
							System.out.println("invalid command.");
						}
					} else {
						System.out.println("invalid command.");
					}
					del(dict, word.toLowerCase(), type);
					break;

				case "list":
					if (read.hasMoreElements()) {
						prefix = read.nextToken();
						list(dict, prefix.toLowerCase());
					} else {
						System.out.println("invalid command.");
					}
					break;

				case "put":
					if (read.hasMoreElements()) {
						word = read.nextToken();
						if (read.hasMoreElements()) {
							type = read.nextToken();
							if (read.hasMoreElements()) {
								data = "";
								while (read.hasMoreElements()) {
									if (!data.equals("")) {
										data += " " + read.nextToken();
									} else {
										data += read.nextToken();
									}
								}
								put(dict, word.toLowerCase(), type.toLowerCase(), data);
							} else {
								System.out.println("invalid command.");
							}
						} else {
							System.out.println("invalid command.");
						}
					} else {
						System.out.println("invalid command.");
					}
					break;

				case "smallest":
					smallest(dict);
					break;

				case "largest":
					largest(dict);
					break;

				case "finish":
					notFinish = false;
					break;
				default:
					System.out.println("invalid command.");
					break;
				}
			}
		}

	}

	/**
	 * get method
	 * 
	 * @param dict
	 * @param word
	 */
	private static void get(OrderedDictionary dict, String word) {

		String dataTypes[] = { "audio", "image", "text" };
		Record pred, succ;
		int track = 0;

		// displays each type of file type of word
		for (int i = 0; i < 3; i++) {
			Record record = dict.get(new Pair(word, dataTypes[i]));
			if (record != null) {
				if (record.getKey().getType().equals(dataTypes[0])) {
					try {
						SoundPlayer player = new SoundPlayer();
						player.play(record.getData());
					} catch (MultimediaException e) {
						System.out.println("no sound file");
					}
				} else if (record.getKey().getType().equals(dataTypes[1])) {
					try {
						PictureViewer viewer = new PictureViewer();
						viewer.show(record.getData());
					} catch (MultimediaException e) {
						System.out.println("no image file");
					}
				} else if (record.getKey().getType().equals(dataTypes[2])) {
					System.out.println(record.getData());
				}
			} else {
				track++;
			}
		}

		// if all 3 datatypes are not in dict
		if (track == 3) {
			System.out.format("The word %s is not in the ordered dictionary.\n", word);
			pred = dict.predecessor(new Pair(word, ""));
			succ = dict.successor(new Pair(word, "audio"));
			if (pred == null) {
				System.out.println("Preceding word: ");
			} else {
				System.out.format("Preceding word: %s\n", pred.getKey().getWord());
			}
			if (succ == null) {
				System.out.println("Following word: ");
			} else {
				System.out.format("Following word: %s\n", succ.getKey().getWord());
			}
		}

	}

	/**
	 * list method
	 * 
	 * @param dict
	 * @param prefix
	 */
	private static void list(OrderedDictionary dict, String prefix) {
		String list = "";
		String listArr[];
		Record record;
		String word;
		boolean found = false;

		// gets successor of prefix
		record = dict.successor(new Pair(prefix, "0"));
		while (record != null) {
			word = record.getKey().getWord();
			if (word.startsWith(prefix)) {
				list += ", " + word;
				found = true;
			}
			record = dict.successor(record.getKey());
		}

		// gets predecessor of prefix
		record = dict.predecessor(new Pair(prefix, "0"));
		while (record != null) {
			word = record.getKey().getWord();
			if (word.startsWith(prefix)) {
				list += ", " + word;
				found = true;
			}
			record = dict.predecessor(record.getKey());
		}

		if (list.equals("") && found == false) {
			System.out.format("no words in dictionary start with %s\n", prefix);
		} else {
			System.out.println(list.substring(2));
		}
	}

	/**
	 * del method
	 * 
	 * @param dict
	 * @param word
	 * @param type
	 */
	private static void del(OrderedDictionary dict, String word, String type) {
		try {
			dict.remove(new Pair(word, type));
		} catch (DictionaryException e) {
			System.out.format("No record in the ordered dictionary has key (%s,%s).\n", word, type);
		}
	}

	/**
	 * put method
	 * 
	 * @param dict
	 * @param word
	 * @param type
	 * @param data
	 */
	private static void put(OrderedDictionary dict, String word, String type, String data) {
		Pair pair = new Pair(word, type);
		Record record = new Record(pair, data);
		try {
			dict.put(record);
		} catch (DictionaryException e) {
			System.out.format("A record with the given key (%s,%s) is already in the ordered dictionary.\n", word,
					type);
		}
	}

	/**
	 * smallest method
	 * 
	 * @param dict
	 */
	private static void smallest(OrderedDictionary dict) {
		Record smallest = dict.smallest();
		System.out.format("%s, %s, %s\n", smallest.getKey().getWord(), smallest.getKey().getType(), smallest.getData());
	}

	/**
	 * largest method
	 * 
	 * @param dict
	 */
	private static void largest(OrderedDictionary dict) {
		Record largest = dict.largest();
		System.out.format("%s, %s, %s\n", largest.getKey().getWord(), largest.getKey().getType(), largest.getData());
	}

}
