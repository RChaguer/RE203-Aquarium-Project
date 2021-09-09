package src;

/*
  Sends a ping to the server each second.
 */

public class SendPing implements Runnable {

  private int port;
  Console console;
  int time;
  boolean running;

  public SendPing(Console c, int p, int t) {
    port = p;
    console = c;
    time = t;
    running = true;
  }

  public void run() {
    try {

      while (running) {
        Thread.sleep(time);
        if(console.parser.client.stopPing){
           running = false;
           break;
         } else {
           console.parser.client.outValue +=1;
           console.parser.client.send("ping " + port);
           if(console.parser.client.outValue >= 2) {
             running = false;
             console.parser.client.outValue = 0;
             console.logOut();
             break;
           }
        }
      }

    } catch (InterruptedException e) {
    }

  }

}