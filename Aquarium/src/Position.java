package src;

import javafx.geometry.Point2D;


public class Position {
    private String id;
    private Point2D coord;
    private int period;
    private int bundleX;
    private int bundleY;

    public Position(String id, double coordX, double coordY, int period, int bX, int bY) {
        this.id = id;
        coord = new Point2D(coordX, coordY);
        this.period = period;
        bundleX = bX;
        bundleY = bY;
    }

    String getId() {
        return id;
    }

    double getX() {
        return coord.getX();
    }

    double getY() {
        return coord.getY();
    }

    int getPeriod() {
        return period;
    }

    int getBundleX() {
        return bundleX;
    }

    int getBundleY() {
        return bundleY;
    }
}
