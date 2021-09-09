package src.type;

import src.FishType;
import javafx.scene.image.Image;
import java.io.File;

public class TypeKoi implements FishType {
    private Image img;

    public TypeKoi() {
        img = new Image(new File("../src/assets/PoissonKoi.png").toURI().toString());
    }

    public String getType() {
        return new String("PoissonKoi");
    }

    public Image getImage() {
        return img;
    }
}
