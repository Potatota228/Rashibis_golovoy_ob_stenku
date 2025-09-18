package work.com;
import files.*;
import verysecret.*;
import work.*;
public class LsCommand implements Command {
    private Environment env;

    public LsCommand(Environment env) {
        this.env = env;
    }
    @Override
    public String execute(String [] args){
        if 
        env.curDir.list();
        return "Sucsess";
    }
}
