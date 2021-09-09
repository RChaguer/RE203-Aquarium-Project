package src;
import java.io.*;

public class Config{
    private String config_file;
    private String id;
    private int port;
    private int timeOutValue;
    private String resources;
    private String address;

    public Config(String file) {
        this.config_file=file;
        this.port=0;
        this.address="";
        this.id="";
        this.resources="";
        this.timeOutValue=0;
    }

    /**
     * Format du fichier config attendue:
     *          | controller-address = a.b.c.d
     *          | id = N1
     *          | controller-port = 1234 
     *          | display-time-out-value = 30
     *          | resources = ./fishes
     */
    public void read() {
        try {
            InputStream input = new FileInputStream(this.config_file);
            InputStreamReader reader = new InputStreamReader(input);
            PrintWriter writer = new PrintWriter("../logs.txt");
            writer.print("");
            writer.close();
            BufferedReader buff = new BufferedReader(reader);
            String line;
            String[] parts;
            
            line = buff.readLine();
            parts = line.split(" ");
            this.address = parts[2];

            line = buff.readLine();
            parts = line.split(" ");
            if(parts.length == 2) {
                this.id = "";
            }else {
                this.id = parts[2];
            }
            line = buff.readLine();
            parts = line.split(" ");
            this.port = Integer.parseInt(parts[2]);

            line = buff.readLine();
            parts = line.split(" ");
            this.timeOutValue = Integer.parseInt(parts[2]);

            line = buff.readLine();
            parts = line.split(" ");
            this.resources = parts[2];

            buff.close();
        } catch (Exception e) {
            System.out.println("Config file: "+ e);    
        }
    }

    public int getPort() {
        return this.port;
    }

    public String getAddress() {
        return this.address;
    }

    public String getId() {
        return this.id;
    }

    public String getResources() {
        return this.resources;
    }

    public int getTimeOutValue() {
        return this.timeOutValue;
    }

    @Override
    public String toString() {
        return config_file;
    }

}