package files;
import java.util.*;

public class Directory extends FSNode {
    private Map<String, FSNode> children = new HashMap<>(); //хэш массив имя-FSNode (либо файл либо директория)

    public Directory(String name, Directory parent) {
        super(name, parent);
    }

    public void add(FSNode node) {
        children.put(node.getName(), node);
    }

    public FSNode get(String name) {
        return children.get(name);
    }

    public Collection<FSNode> list() {
        return children.values();
    }

    @Override
    public boolean isDirectory() {
        return true;
    }
}
