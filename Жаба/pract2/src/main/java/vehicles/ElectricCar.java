package vehicles;
public class ElectricCar extends Car {
    public ElectricCar(){
        super();
        this.engineType = "Electric";
    }
    private int batteryCapacity;
    public int getBC(){
        return batteryCapacity;
    }
    public void setBC(int batteryCapacity){
        this.batteryCapacity = batteryCapacity;
}
}