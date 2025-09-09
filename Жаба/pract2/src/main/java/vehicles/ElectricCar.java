package vehicles;
public class ElectricCar extends Car {
    private int batteryCapacity;
    public ElectricCar(String model, String license, String color, int year, String ownerName,
                        int insuranceNumber, int batteryCapacity){
        super(model, license, color, year, ownerName, insuranceNumber, "Electric");
        this.batteryCapacity = batteryCapacity;
    }
    public int getBC(){
        return batteryCapacity;
    }
    public void setBC(int batteryCapacity){
        this.batteryCapacity = batteryCapacity;
    }
        @Override
    public String vehicleType() {
        return "Electric Car";
    }
    @Override
    public String toString() {
        return vehicleType() + " - " + super.toString();
    }
}