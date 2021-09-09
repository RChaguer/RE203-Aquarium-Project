package src.type;

import src.FishType;
import javafx.scene.image.Image;
import java.io.File;

public class TypeNain implements FishType {
    private Image img;

    public TypeNain() {
        img = new Image(new File("../src/assets/PoissonNain.png").toURI().toString());
    }

    public String getType() {
        return new String("PoissonNain");
    }

    public Image getImage() {
        return img;
    }
}
