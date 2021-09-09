package src;

import javafx.application.Platform;
import javafx.event.EventHandler;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.control.Label;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import javafx.scene.input.KeyEvent;
import javafx.scene.input.MouseButton;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.Pane;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;

import java.io.File;
import java.io.IOException;
import java.nio.charset.Charset;
import java.nio.file.*;
import java.util.*;

import static javafx.scene.control.Alert.AlertType.*;

public class Console extends Stage {

    private ToolBar toolbar;
    protected Parser parser;
    protected Path logsPath;
    Aquarium aquarium;

    // Display
    Pane entry;
    VBox vb;
    protected TextArea display;
    private TextField input;
    private int width;
    private int height;
    private Config conf;

    // History
    protected List<String> history;
    protected int historyCount = 0;

    public Console(Aquarium a, int w, int h, Config conf) {
        aquarium = a;
        width = w;
        height = h;
        // this.setX(Screen.getPrimary().getVisualBounds().getWidth()-width-100);
        // this.setY(100);

        initDisplay();
        this.conf = conf;
        parser = new Parser(this, display, conf);
        this.setTitle("Console N" + conf.getId() + " [Disconnected]");
    }

    private void initDisplay() {
        // this.setResizable(false);

        entry = new Pane();

        display = new TextArea();
        display.setEditable(false);
        history = new ArrayList<>();

        initTab();
        initInput();

        vb = new VBox();
        display.setMinHeight(height - input.getHeight() - toolbar.getHeight() - 50);
        display.setMaxHeight(height - input.getHeight() - toolbar.getHeight() - 50);
        vb.getChildren().addAll(toolbar, display, input);
        entry.getChildren().add(vb);

        this.setScene(new Scene(entry, width, height));
    }

    private void initInput() {
        input = new TextField();
        input.setPrefColumnCount(20);
        input.addEventHandler(KeyEvent.KEY_RELEASED, keyEvent -> {
            switch (keyEvent.getCode()) {
                case ENTER:
                    String action = input.getText();
                    history.add(action);
                    historyCount = history.size();
                    display.appendText("$ " + action + System.lineSeparator());
                    input.clear();
                    parser.parser(action);
                    break;
                case UP:
                    if (historyCount == 0) {
                        break;
                    }
                    historyCount--;
                    input.setText(history.get(historyCount));
                    input.selectAll();
                    break;
                case DOWN:
                    if (historyCount == history.size() - 1) {
                        historyCount = history.size();
                        input.clear();
                        break;
                    }
                    if (historyCount < history.size()) {
                        historyCount++;
                        input.setText(history.get(historyCount));
                        input.selectAll();
                    }
                    break;
                default:
                    historyCount = history.size();
                    break;
            }
        });
    }

    public void logOut() {
        Platform.runLater(() -> {
            parser.client.logOut();
            aquarium.addPositions(null);
            this.setTitle("Console N" + conf.getId() + " [Disconnected]");
        });
    }

    private void initTab() {

        Label tab1 = new Label("Fishes");
        initInfoTab(tab1, "Fishes", "Fishes available : ",
                "Here the fishes available : " + System.lineSeparator() + aquarium.fishes.keySet().toString());

        Label tab2 = new Label("Mobility Models");
        initInfoTab(tab2, "Mobility Models", "Mobility models available : ", "Here the models available : "
                + System.lineSeparator() + "RandomWayPoint \nHorizontal \n Vertical\n DontMove\n");

        Label tab3 = new Label("Help");
        initInfoTab(tab3, "Help", "Commands available : ",
                "Here the command available : " + System.lineSeparator() + " - status " + System.lineSeparator()
                        + " - startFish name " + System.lineSeparator() + " - addFish name x y w h modelMoving "
                        + System.lineSeparator() + " - delFish name " + System.lineSeparator());

        Label tab4 = new Label("About");
        initInfoTab(tab4, "About", "About the software",
                "Group project:" + System.lineSeparator() + " Houssam BAHHOU" + System.lineSeparator() + " Reda CHAGUER"
                        + System.lineSeparator() + " Zaid ZERRAD" + System.lineSeparator() + " Asmae ZIANI"
                        + System.lineSeparator());

        toolbar = new ToolBar(tab1, new Separator(), tab2, new Separator(), tab3, new Separator(), tab4);
    }

    public void writeLogs(String s) {
        try {
            File file = new File("../logs_N" + conf.getId() + ".txt");
            file.createNewFile();
            Files.write(file.toPath(), Arrays.asList(s), Charset.forName("UTF-8"), StandardOpenOption.APPEND);
        } catch (IOException e) {
            System.out.println("Probleme lors de l'ecriture des logs : " + e.toString());
        }
    }

    /**
     * initialise a tab
     * 
     * @param l       label of the new tab
     * @param title   title of the new tab
     * @param header  header of the new tab
     * @param content content of the new tab
     */
    private void initInfoTab(Label l, String title, String header, String content) {
        l.setOnMouseClicked(new EventHandler<MouseEvent>() {
            public void handle(MouseEvent e) {
                if (e.getButton() == MouseButton.PRIMARY) {
                    Alert alert = new Alert(INFORMATION);
                    alert.setHeaderText(header);
                    alert.setTitle(title);
                    alert.setHeight(400);
                    if (title == "Fishes") {
                        alert.setContentText(System.lineSeparator() + aquarium.fishes.keySet().toString());
                    } else {
                        alert.setContentText(content);
                    }
                    alert.showAndWait().ifPresent(response -> {
                        if (response == ButtonType.OK) {
                            alert.close();
                        }
                    });
                }
            }
        });
    }

}
