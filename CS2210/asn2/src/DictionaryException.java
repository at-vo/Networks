/**
 * Dat Vo 250983323 CS2210 ASN2
 * Dictionary Exception to be used in put and remove methods of HashDictionary Class
 */
public class DictionaryException extends RuntimeException{
    
    public DictionaryException(String e){
        super ("The" + e+ " in the dictionary");
    }
}
