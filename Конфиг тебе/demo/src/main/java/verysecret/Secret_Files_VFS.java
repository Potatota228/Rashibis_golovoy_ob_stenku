
package verysecret;
import files.Directory;
import files.File;
import work.Environment;
import work.com.CdCommand;
import work.com.LsCommand;
import work.prettyGUI;
public class Secret_Files_VFS {
    public static void main(String[] args) {
    prettyGUI gui = new prettyGUI();
        gui.CreateGUI();
    //Добавить иницилизацию по имени? Прикольно было бы
    Directory root = new Directory("/",null);
    Environment env =  new Environment("bruh", root);
    LsCommand ls = new LsCommand(env);
    CdCommand cd = new CdCommand(env);
    Directory bin = new Directory("bin", root);
    Directory home = new Directory("home", root);
    Directory Delta1 = new Directory("Delta1", root);
    File one = new File("Ленин гриб", Delta1, "А вы знали что ленин гриб");
    File two = new File("ABOBA", Delta1, "ABOBA");
    }
}