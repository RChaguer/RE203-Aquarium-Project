package src.type;

import src.FishType;
import javafx.scene.image.Image;
import java.io.File;

public class TypeRouge implements FishType {
    private Image img;

    public TypeRouge() {
        img = new Image(new File("../src/assets/PoissonRouge.png").toURI().toString());
    }

    public String getType() {
        return new String("PoissonRouge");
    }

    public Image getImage() {
        return img;
    }
}
