package src;

import java.io.File;

import javafx.application.Application;
import javafx.geometry.Point2D;
import javafx.scene.Scene;
import javafx.scene.image.Image;
import javafx.scene.layout.*;
import javafx.stage.Stage;

public class VisualApp extends Application {
    private Aquarium Aq;
    private Console console;
    static Point2D resolution;
    static private Config conf;

    public static void setConfig(Config c) {
        conf = c;
    }

    public static void setResolution(int width, int height) {
        resolution = new Point2D(width, height);
    }

    public void start(Stage stage) {
        Pane canvas = new Pane();
        BackgroundImage b = new BackgroundImage(

                new Image(new File("../src/assets/background.jpg").toURI().toString(), resolution.getX(),
                        resolution.getY(), false, true),
                BackgroundRepeat.REPEAT, BackgroundRepeat.NO_REPEAT, BackgroundPosition.DEFAULT,
                BackgroundSize.DEFAULT);

        canvas.setBackground(new Background(b));

        Aq = new Aquarium(canvas);
        Scene scene = new Scene(canvas, resolution.getX(), resolution.getY());
        console = new Console(Aq, 400, 400, conf);

        console.show();
        console.parser.client.config();
        stage.setScene(scene);
        stage.setTitle("Aquarium View N" + conf.getId());
        stage.setResizable(false);
        stage.show();
        stage.setOnCloseRequest(event -> {
            console.parser.client.send("log out");
            console.logOut();
            System.exit(0);
        });
        console.setOnCloseRequest(event -> {
            console.parser.client.send("log out");
            console.logOut();
            stage.close();
            System.exit(0);
        });
        Aq.start();

    }

    public void view(String... args) {
        VisualApp.setResolution(500, 500);
        VisualApp.setConfig(new Config(args[0]));
        VisualApp.launch(args);

    }
}
