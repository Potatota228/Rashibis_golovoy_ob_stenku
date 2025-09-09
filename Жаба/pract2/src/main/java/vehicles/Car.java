package vehicles;
public class Car extends Vehicle {
    public Car(String model, String license, String color, int year, String ownerName, int insuranceNumber, String engineType){
        super(model, license, color, year, ownerName, insuranceNumber, engineType);
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