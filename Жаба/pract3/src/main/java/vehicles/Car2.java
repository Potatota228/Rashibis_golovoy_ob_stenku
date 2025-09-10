package vehicles;
public class Car2 extends Vehicle2 {
    public Car2(String model, String license, String color, int year, String ownerName, int insuranceNumber, String engineType){
        super(model, license, color, year, ownerName, insuranceNumber, "Combustion");
    }
    @Override
    public String vehicleType(){
        return "Car";
    }
    @Override
    public String toString() {
        return vehicleType() + " - " + super.toString();
    }
}