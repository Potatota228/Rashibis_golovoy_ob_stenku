package vehicles;
public abstract class Vehicle2 {
    String model;
    String license;
    String color;
    int year;
    int age;
    String ownerName;
    int insuranceNumber;
    abstract String vehicleType();
    protected String engineType;
    public Vehicle2(String model, String license, String color, int year, 
                  String ownerName, int insuranceNumber, String engineType){
                  this.model = model;
                  this.license = license;
                  this.color = color;
                  this.year = year;
                  this.ownerName = ownerName;
                  this.insuranceNumber = insuranceNumber;
                  this.engineType = engineType;  
                  }
        public String getON(){
        return ownerName;
    }
    public int getIN(){
        return insuranceNumber;
    }
    public void setON(String ownerName){
        this.ownerName = ownerName;
    }
    public void setIN(int insuranceNumber){
        this.insuranceNumber = insuranceNumber;
    }
    public String getET(){
        return engineType;
    }
    public void setET(String engineType){
        this.engineType = engineType;
    }
    public int getYR(int year){
        return year;
    }
    public void setYR(int year){
        this.year = year;
    }
    public String toString() {
        return "Model: " + model + ", License: " + license + 
               ", Color: " + color + ", Year: " + year + 
               ", Owner: " + ownerName + ", Insurance: " + insuranceNumber + 
               ", Engine: " + engineType;
    }

}
