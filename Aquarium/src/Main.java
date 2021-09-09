package src;

public class Main {
    public static final String ANSI_RESET = "\u001B[0m";
    public static final String ANSI_RED = "\u001B[31m";
    public static void main(String[] args) {
        try{
            VisualApp pp = new VisualApp();
            pp.view(args);
        }
        catch(Exception e){
            System.err.println(ANSI_RED + "Error while executing, if you are on linux try 'make lib_config' and rerun" + ANSI_RESET);
        }
    }
}
