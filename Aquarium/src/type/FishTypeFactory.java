package src.type;

import src.FishType;

final public class FishTypeFactory {

    private FishTypeFactory() {}

    public static FishType PoissonNain = new TypeNain();

    public static FishType PoissonRouge = new TypeRouge();

    public static FishType PoissonKoi = new TypeKoi();

    public static FishType getFishType(String name) {
        String typeName = name.replaceAll("[0-9]", "");
        switch(typeName)  {
            case "PoissonNain":
                return PoissonNain;
            case "PoissonRouge":
                return PoissonRouge;
            case "PoissonKoi" :
                return PoissonKoi;
            default:
                return PoissonNain;
        }
    }
}
