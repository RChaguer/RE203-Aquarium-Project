package src;

import java.awt.geom.Point2D;
import java.util.LinkedList;

import src.type.FishTypeFactory;
import javafx.scene.image.*;

public class Fish {
    private String id;
    private ImageView node;
    private FishType type;
    private Point2D speed;
    private boolean started;
    private boolean isStatic;
    private boolean stillInView;
    private boolean deleted;
    private Position current_pos;
    private LinkedList<Position> pos;

    public Fish(String t, double initX, double initY, int sizeX, int sizeY) {

        // Init Fish Id
        this.id = t;

        // Init Fish Types
        type = FishTypeFactory.getFishType(t);

        // Init Initial Fish Location & Image
        started = false;
        deleted = false;
        node = new ImageView(type.getImage());
        node.setX(initX);
        node.setY(initY);
        node.setFitWidth(sizeX);
        node.setFitHeight(sizeY);

        // Init Speed
        speed = new Point2D.Double();
        pos = new LinkedList<Position>();
        isStatic = false;
    }

    public String getId() {
        return id;
    }

    public String getType() {
        return type.getType();
    }

    public ImageView getNode() {
        return node;
    }

    public boolean isOnDestination() {
        if ((Math.abs(current_pos.getX() - node.getX()) <= Math.abs(speed.getX())
                && Math.abs(current_pos.getY() - node.getY()) <= Math.abs(speed.getY()))) {
            node.setX(current_pos.getX());
            node.setY(current_pos.getY());
            return true;
        }
        return false;
    }

    public boolean isStarted() {
        return started;
    }

    public boolean isStatic() {
        return isStatic;
    }

    public boolean isDeleted() {
        return deleted;
    }

    public void addMove(Position p) {
        pos.add(p);
    }

    public void fishStart() {
        started = true;
        if (pos.isEmpty())
            isStatic = true;
        else {
            current_pos = pos.poll();
            if (current_pos.getPeriod() > 0) {
                speed.setLocation((current_pos.getX() - node.getX()) / (current_pos.getPeriod()),
                        (current_pos.getY() - node.getY()) / (current_pos.getPeriod()));
                angleCalculate(current_pos);
            } else {
                node.setX(current_pos.getX());
                node.setY(current_pos.getY());
            }
        }
    }

    public void fishDelete() {
        deleted = true;
    }

    public void fishIsInView() {
        stillInView = true;
    }

    public void fishNoMoreInView() {
        stillInView = false;
    }

    public boolean fishNotInView() {
        return !stillInView;
    }

    public void move() {
        if (started) {
            if (!isStatic) {
                if (!isOnDestination()) {
                    node.setX(node.getX() + speed.getX());
                    node.setY(node.getY() + speed.getY());
                } else {
                    if (pos.isEmpty()) {
                        isStatic = true;
                    } else {
                        current_pos = pos.poll();
                        if (current_pos.getPeriod() > 0) {
                            speed.setLocation((current_pos.getX() - node.getX()) / (current_pos.getPeriod()),
                                    (current_pos.getY() - node.getY()) / (current_pos.getPeriod()));
                            angleCalculate(current_pos);
                        } else {
                            node.setX(current_pos.getX());
                            node.setY(current_pos.getY());
                        }
                    }
                }
            } else {
                if (!pos.isEmpty()) {
                    isStatic = false;
                    current_pos = pos.poll();
                    if (current_pos.getPeriod() > 0) {
                        speed.setLocation((current_pos.getX() - node.getX()) / (current_pos.getPeriod()),
                                (current_pos.getY() - node.getY()) / (current_pos.getPeriod()));
                        angleCalculate(current_pos);
                    } else {
                        node.setX(current_pos.getX());
                        node.setY(current_pos.getY());
                    }
                }
            }
        }
    }

    private void angleCalculate(Position p) {
        if (speed.getX() > 0) {
            node.setScaleX(-1);
            node.setRotate(180 + Math.atan2(node.getY() - p.getY(), node.getX() - p.getX()) * 180 / Math.PI);
        } else {
            node.setScaleX(1);
            node.setRotate(Math.atan2(node.getY() - p.getY(), node.getX() - p.getX()) * 180 / Math.PI);
        }
    }

    public void rotateImage(int degree) {
        node.setRotate(degree);
    }

    @Override
    public String toString() {
        return type.getType();
    }

    public boolean equals(String _id) {
        return id.equals(_id);
    }

}