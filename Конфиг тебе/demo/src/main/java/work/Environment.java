package work;
public class Environment {
    private String username;
    // public Directory curDir;
    public Environment(String username){
        this.username = username;
        // this.curDir = curDir;
    }
     public static void main(String[] args) {

     }
    // void setCurDir(Directory curDir){
    //     this.curDir=curDir;
    // }
    //  public Directory getCurDir() {
    //     return curDir;
    //}
    void setUN(String username){
        this.username=username;
    }
     public String getUN() {
        return username;
    }
}
