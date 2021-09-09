package src;

import java.util.*;

import javafx.animation.AnimationTimer;
import javafx.application.Platform;
import javafx.scene.layout.Pane;
import java.util.Map;

public class Aquarium extends AnimationTimer {
    static int FPS = 80;
    long rateCounter = 0;
    long counter = 0;
    Pane canvas;
    int rate = 0;
    public Map<String, Fish> fishes;

    public Aquarium(Pane c) {
        fishes = new HashMap<String, Fish>();
        canvas = c;
    }

    public void addFish(String fishTypeName, double initX, double initY, int sizeX, int sizeY) {
        Fish newFish = new Fish(fishTypeName, initX, initY, sizeX, sizeY);
        fishes.put(fishTypeName, newFish);
    }

    public boolean hasFish(String fishTypeName) {
        for (String key : fishes.keySet()) {
            if (key.contentEquals(fishTypeName))
                return true;
        }
        return false;
    }

    public void addPositions(List<Position> ps) {
        Platform.runLater(() -> {
            if (ps == null) {
                canvas.getChildren().clear();
                fishes.clear();
            } else {
                Fish f;
                for (Position p : ps) {
                    f = fishes.get(p.getId());
                    if (f != null) {
                        f.addMove(p);
                        fishes.put(p.getId(), f);
                        f.fishIsInView();
                    } else {
                        Fish newFish = new Fish(p.getId(), p.getX(), p.getY(), p.getBundleX(), p.getBundleY());
                        fishes.put(p.getId(), newFish);
                        newFish.fishStart();
                        canvas.getChildren().add(newFish.getNode());
                        newFish.fishIsInView();
                    }
                }

                for (Fish fish : fishes.values()) {
                    if (fish.fishNotInView())
                        deleteFish(fish);
                    else
                        fish.fishNoMoreInView();
                }
            }
        });

    }

    public void getFishes() {
        Platform.runLater(() -> {
            fishes.keySet().toString();
        });
    }

    public void deleteFish(Fish f) {
        fishes.remove(f.getId());
        canvas.getChildren().remove(f.getNode());
    }

    public void move() {
        for (Fish f : fishes.values()) {
            f.move();
        }
    }

    public void update() {
        for (Fish f : fishes.values()) {
            if (!f.isStarted()) {
                canvas.getChildren().add(f.getNode());
                f.fishStart();
            }
            if (f.isDeleted()) {
                canvas.getChildren().remove(f.getNode());
                fishes.remove(f.getId());
            }
        }
    }

    public void handle(long now) {
        if (counter == 0L) {
            counter = now;
            rateCounter = now;
        }
        if (now - rateCounter > (1e9)) {
            rateCounter = now;
            rate = 0;
        }
        if (now - counter > (1e9 / FPS)) {
            counter = now;
            this.move();
            rate++;
        }

    }
}
