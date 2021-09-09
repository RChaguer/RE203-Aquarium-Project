package src;

import javafx.scene.control.TextArea;

/**
 * class that define the parser, to parse the different orders of the user
 */
public class Parser {

    protected Console console;
    protected Client client;

    public Parser(Console c, TextArea t, Config conf) {
        console = c;
        console.display = t;
        client = new Client(console, conf);
    }

    /**
     * function that will parse a string
     * 
     * @param s string to parse
     */
    synchronized public void parser(String s) {
        String[] args = s.split(" |\\, ");
        switch (args[0]) {
            case "status":
                if (args.length == 1) {
                    if (client.isConnected()) {
                        console.display.appendText("\t -> OK : Connecte au controleur" + System.lineSeparator());
                    } else
                        console.display.appendText("\t -> NOK : Connexion non trouvee." + System.lineSeparator());
                } else
                    console.display.appendText(
                            "\t -> NOK. la commande 'status' n'a pas d'arguments." + System.lineSeparator());
                break;
            case "reconnect":
                client.config();
                break;
            default:
                client.protocole.addCommand(s);
                client.send(s);
                break;
        }
    }

}
