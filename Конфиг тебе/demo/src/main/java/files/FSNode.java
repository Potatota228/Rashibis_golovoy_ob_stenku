package files;
abstract class FSNode {
    public String name;
    public Directory parent;
    public String CFN;
    public FSNode(String name, Directory parent) {
        this.name = name;
        this.parent = parent;
    }

    public String getName() {
        return name;
    }

    public Directory getParent() {
        return parent;
    }
    public String getPath(String path){
        if (this.getParent() != null){
            return this.getParent().getPath(path) + "/" + this.getName();
        }
        return this.getName();
        
    }
    public abstract boolean isDirectory();
}
