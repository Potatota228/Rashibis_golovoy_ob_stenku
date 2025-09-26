package work.com;

public class ExitCommand {
    public ExitCommand(){
        
    }
     public void exitProgram() {
        try{
        Thread.sleep(2000);
        System.exit(0);
        }
        catch (InterruptedException e) {
        System.exit(0);
        }
    }
}
