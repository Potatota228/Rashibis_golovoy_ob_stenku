package vehicles;

public class ElectricCar2 extends Car2 implements ElectricVehicle2 {

    private int batteryCapacity;

    public ElectricCar2(String model, String license, String color, int year, String ownerName,
            int insuranceNumber, int batteryCapacity) {
        super(model, license, color, year, ownerName, insuranceNumber, "Electric");
        this.batteryCapacity = batteryCapacity;
    }

    @Override
    public int getBC() {
        return batteryCapacity;
    }

    @Override
    public void setBC(int batteryCapacity) {
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
