package vehicles;
public class Car {
    private String ownerName;
    private int insuranceNumber;
    protected String engineType;
    public Car(){
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
}