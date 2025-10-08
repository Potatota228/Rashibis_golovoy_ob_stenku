public class Car2 {
    String model;
    String license;
    String color;
    int year;
    int age;
    final int curYear = 2025;
    public Car2(){
    }
    public Car2(String model, String license, String color, int year){
        this.model = model;
        this.license = license;
        this.color = color;
        this.year = year;
    }
    public Car2(String color){
        this.color = color;
    }
     public void To_String() {
        System.out.println("Model: " + model);
        System.out.println("License: " + license);
        System.out.println("Color: " + color);
        System.out.println("Year: " + year);
        System.out.println("-------------------");
     }
    public String getModel() {
        return model;
    }
    
    public String getLicense() {
        return license;
    }
    
    public String getColor() {
        return color;
    }
    
    public int getYear() {
        return year;
    }
    
    public void setModel(String model) {
        this.model = model;
    }
    
    public void setLicense(String license) {
        this.license = license;
    }
    
    public void setColor(String color) {
        this.color = color;
    }
    
    public void setYear(int year) {
        this.year = year;
    }
    public int howOld(){
        return curYear - year;
    }
}
