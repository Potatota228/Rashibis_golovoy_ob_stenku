package work;
import work.*;
import work.com.LsCommand;
import work.com.CdCommand;
import verysecret.*;
public class CommandProcessor {
    private Environment env;
    public CommandProcessor(Environment env) {
        this.env = env;
    }
    public String process(String input) {
        if (input == null) {
            return "ERROR";
        }
        if (input.contains("$HOME")) {
            input.replace("$HOME", "/home/" + env.getUN());
        }
        if (input.contains("$USER")) {
            input.replace("$USER", env.username);
        }
        if (input.contains("$PATH")) {
            input.replace("$PATH", "/home/" + env.username + "/secretDocs/");
        }
        if (input.contains("$SHELL")) {
            input.replace("$SHELL", "/bin/bash");
        }

        if (input.substring(0,3) == "lc"){
            lc.execute(input.substring(0,3) == "lc");
            
