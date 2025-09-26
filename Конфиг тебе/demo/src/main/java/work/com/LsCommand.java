package work.com;
public class LsCommand {
    public LsCommand(){
    }
    public String main(String newDir) {
        if (newDir.equals("1")){
            return "File 1; File 2; File 3";
        }
        return "ERROR, because error";
    }
}
