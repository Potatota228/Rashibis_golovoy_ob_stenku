package work.com;
import files.*;
import verysecret.*;
import work.*;
public class CdCommand implements Command{
    private Environment env;
public CdCommand(Environment env) {
        this.env = env;
    }
    @Override
    public String execute(String [] args){
        if (env.curDir.getName() == args[-1]){
            return ;
        }
        env.curDir.list();
        return "Sucsess";
    }
}
