package work;
import work.com.ExitCommand;
public class Environment {
    ExitCommand exit = new ExitCommand();
    private String username;
    private String VFS;
    public String setUN (String name){
        if (!name.equals(null) &&!name.isEmpty()){
            this.username=name;
            return "Welcome back, " + name;
        }
        return "Authorisation failed. If you belive that this is an error, report to the head office.";
    }
    public String getUN() {
        return username;
    }
    public boolean setVFS (String VFSPath){
        if (!VFSPath.isEmpty() && !VFSPath.equals(null)){
            this.VFS=VFSPath;
            return true;
        }
        return false;
    }
    public String getVFS() {
        return VFS;
    }
}
