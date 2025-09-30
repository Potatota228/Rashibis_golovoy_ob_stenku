package work;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.List;
public class Environment {
    private String username;
    private String VFS;
    private List<String> sslist;
    public boolean ss(String input) {
        Path filePath = Paths.get(input);
        try{
            setSS(Files.readAllLines(filePath));
            return true;
        }
        catch (IOException e){
            return false;
        }
        
    }
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
    public void setSS(List<String> sslist){
        this.sslist = sslist;
    }
    public List<String> getSS() {
        return sslist;
    }
    public String getVFS() {
        return VFS;
    }
}
