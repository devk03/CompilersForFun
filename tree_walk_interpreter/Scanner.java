package tree_walk_interpreter;

import static tree_walk_interpreter.TokenType.*;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Scanner {
    private String source;
    private List<Token> tokens;
    private int start;
    private int current;
    private int line;

    Scanner(String source) {
        this.source = source;
        this.tokens = new ArrayList<Token>();
        this.start = 0;
        this.current = 0;
        this.line = 1;
    }

    public List<Token> scanTokens() {
        while (!isAtEnd()) {
            start = current;
            scanToken();
        }
        tokens.add(new Token(TokenType.EOF, "", null, line));
        return tokens;
    }

    private boolean isAtEnd(){
        return current >= source.length();
    }

    private void scanToken() {
        char c = advance();
        switch (c) {
            case '(': addToken(LEFT_PAREN); break;
            case ')': addToken(RIGHT_PAREN); break;
            case '{': addToken(LEFT_BRACE); break;
            case '}': addToken(RIGHT_BRACE); break;
            case ',': addToken(COMMA); break;
            case '.': addToken(DOT); break;
            case '-': addToken(MINUS); break;
            case '+': addToken(PLUS); break;
            case ';': addToken(SEMICOLON); break;
            case '*': addToken(STAR); break;
            case '!': addToken((match('=')) ? BANG_EQUAL : BANG); break;
            case '=': addToken((match('=')) ? EQUAL_EQUAL : EQUAL); break;
            case '>': addToken((match('=')) ? GREATER_EQUAL : GREATER); break;
            case '<': addToken((match('=')) ? LESS_EQUAL : LESS); break;
            case '/':
                if (match('/')) {
                    while(peek()!='\n' && !isAtEnd()) advance();
                } else {
                    addToken(SLASH);
                }
                break;
            case ' ':
            case '\t':
            case '\r':
                break;
            case '\n': line ++; break;
            case '"': string(); break;
            default:
                Lox.error(line, "Unexpected Character: " + c);
                break;
            }
    }

    private char peek(){
        if (isAtEnd()) return '\0';
        return source.charAt(current);
    }

    private boolean match(char expected) {
        if (isAtEnd()) return false;
        if (source.charAt(current) == expected) {
            current++;
            return true;
        }
        return false;
    }
    
    private char advance(){
        return source.charAt(current++);
    }

    private void addToken(TokenType type){
        addToken(type, null);
    }

    private void addToken(TokenType type, Object literal) {
        String text = source.substring(start, current);
        tokens.add(new Token(type, text, literal, line));
    }

    private void string() {

        while (peek()!='"' && !isAtEnd()){
            if (peek()=='\n') line++;
            advance();
        }

        if (isAtEnd()) {Lox.error(line, "Unterminated string."); return;}
        
        advance();

        String value = source.substring(start + 1, current - 1);
        addToken(STRING, value);
    }
}
