package interpreter;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import interpreter.Token;

public class Scanner {
    private String source; // The raw source code casted as a string
    private List<Token> tokens; // List of parsed tokens
    private int start; // Starting index of lexeme being scanned
    private int current; // Current index being scanned
    private int line; // Current line in the source code for errors

    Scanner(String source){
        this.source = source;
        this.tokens = new ArrayList<Token>();
        this.start = 0; 
        this.current = 0;
    }
}
