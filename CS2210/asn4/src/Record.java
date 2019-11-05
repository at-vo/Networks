
public class Record {

    Pair key;
    String data;

    public Record(Pair key, String data) {
        /*
         * A constructor which initializes a new Record object with the specified key
         * and data. If the type in the key is â€œaudioâ€? or â€œimageâ€?, then data
         * stores the name of the corresponding audio or image file.
         */
        this.key = key;
        this.data = data;

    }

    public Pair getKey() {
        /* Returns the key stored in this Record object. */
        return this.key;
        
    }

    public String getData() {
        /* Returns the data stored in this Record object. */
        return this.data;
    }

}
