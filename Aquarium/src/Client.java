package src;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.InetAddress;
import java.net.Socket;

public class Client {

    private boolean status;
    private Console console;
    private Socket socket;
    protected BufferedReader in;
    Config conf;
    protected boolean stopPing;
    protected Thread reader;
    protected Thread pinger;
    protected ProtocoleReader protocole;
    protected SendPing sendPing;
    protected int outValue;

    /**
     * constructor of the Client
     * 
     * @param c console that will use the Client
     */
    public Client(Console c, Config config) {
        status = false;
        conf = config;
        console = c;
        stopPing = false;
        outValue = 0;
    }

    void setStatus(boolean newStatus) {
        status = newStatus;
    }

    public boolean getStatus() {
        return status;
    }

    /**
     * check if the socket is connected
     * 
     * @return 1 if the socket is connected, 0 else
     */
    public boolean isConnected() {
        return (socket != null && socket.isConnected());
    }

    /**
     * configure the connexion
     */
    public void config() {
        conf.read();
        boolean connected = false;
        try {
            console.writeLogs("Tentative de connexion sur "
            + InetAddress.getByName(InetAddress.getLocalHost().toString().split("/")[1]) + " sur le port = "
            + conf.getPort() + "\n");
       
            if (!connected) {
                try {
                    socket = new Socket(conf.getAddress(), conf.getPort());
                    in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                    connected = true;
                } catch (IOException e) {
                    connected = false;
                }
            }
        } catch (IOException e) {
            connected = false;
        }
        if(connected){
            console.setTitle("Console N" + conf.getId() + " [Connected]");
            console.writeLogs("Connexion etablie.\n");
            if (conf.getId().equals("")) {
                send("hello");
            } else {
                send("hello in as N" + conf.getId());
            }
            protocole = new ProtocoleReader(console, in);
            sendPing = new SendPing(console, conf.getPort(), conf.getTimeOutValue() * 1000);
            reader = new Thread(protocole);
            pinger = new Thread(sendPing);
            reader.start();
            pinger.start();
        }
    }

    /**
     * allow to log out from the connexion
     */
    public void logOut() {
        try {
            if (socket != null) {
                reader.interrupt();
                pinger.interrupt();
                socket.close();
                socket = null;
            }
        } catch (IOException e) {
            System.out.println("Exception : " + e.toString());
            console.writeLogs("Exception lors de la fermeture de socket\n");
        }
    }

    /**
     * send a message on the socket
     * 
     * @param s message to send
     */
    public void send(String s) {
        if (isConnected()) {
            try {
                PrintWriter out = new PrintWriter(socket.getOutputStream());
                console.writeLogs("> " + s);
                out.println(s);
                out.flush();
            } catch (IOException e) {
            }
        }
    }

}
