package src;

import java.io.BufferedReader;
import java.io.IOException;
import java.util.LinkedList;

import java.net.SocketException;
import java.util.ArrayList;

public class ProtocoleReader implements Runnable {

    Console console;
    Client client;
    boolean getFishes;
    String answer;
    BufferedReader in;
    boolean running;
    protected LinkedList<String> commandList;

    public ProtocoleReader(Console c, BufferedReader in) {
        this.in = in;
        running = true;
        console = c;
        client = console.parser.client;
        getFishes = false;
        commandList = new LinkedList<String>();
    }

    public void addCommand(String s) {
        commandList.add(s);
    }

    public void run() {
        while (running) {
            try {
                try {
                    answer = in.readLine();

                    if (answer != null) {
                        console.writeLogs("< " + answer);

                        String[] args = answer.split(" |\\[|\\]|\\,");
                        switch (args[0]) {
                            case "greeting":
                                client.setStatus(true);
                                client.stopPing = false;
                                client.send("getFishes\n");

                                break;
                            case "bye":
                                console.logOut();
                                client.setStatus(false);
                                running = false;
                                console.display.appendText("\t-> " + answer + "\n");
                                break;
                            case "list":
                                if (!getFishes) {
                                    getFishes = true;
                                    client.send("getFishesContinuously\n");
                                }
                                handleDestination(args);
                                break;
                            case "No":
                                running = false;
                                client.stopPing = true;
                                break;
                            case "NOK":
                                console.display.appendText("\t-> " + answer + "\n");
                                if (!commandList.isEmpty()) {
                                    commandList.pop();
                                }
                                break;
                            case "OK":
                                console.display.appendText("\t-> " + answer + "\n");
                                if (!commandList.isEmpty()) {
                                    commandList.pop();
                                }
                                break;
                            case "pong":
                                client.outValue = client.outValue - 1;
                                break;
                            default:
                                break;
                        }
                    }
                } catch (SocketException e) {
                    running = false;
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    public void handleDestination(String[] args) {

        ArrayList<Position> ps = new ArrayList<Position>();
        for (int i = 2; i < args.length; i = i + 7) {
            String n = args[i];
            int x = Integer.parseInt(args[i + 2].split("x")[0]);
            int y = Integer.parseInt(args[i + 2].split("x")[1]);
            int period = Integer.parseInt(args[i + 4]);
            int bundleX = Integer.parseInt(args[i + 3].split("x")[0]);
            int bundleY = Integer.parseInt(args[i + 3].split("x")[1]);
            Position p = new Position(n, x * 5, y * 5, period * 60, bundleX, bundleY);
            ps.add(p);
        }
        console.aquarium.addPositions(ps);
    }
}