package work.com;
public class CdCommand {
    public CdCommand(){
        
    }
    public String main(String newDir) {
        if (newDir.equals("1") && !newDir.isEmpty()){
            return "The Directory is sucsessfully changed to " + newDir;
        }
        return "ERROR, Directory " + newDir + " doesn't exist.";
    }
}
