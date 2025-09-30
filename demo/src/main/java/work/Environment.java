package work;

import files.Directory;

public class Environment {
    public String username;
    public Directory curDir;
    public Environment(String username, Directory curDir){
        this.username = username;
        this.curDir = curDir;
    }
    void setCurDir(Directory curDir){
        this.curDir=curDir;
    }
     public Directory getCurDir() {
        return curDir;
    }
    void setUN(String username){
        this.username=username;
    }
     public String getUN() {
        return username;
    }
}
