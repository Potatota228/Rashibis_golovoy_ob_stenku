package vehicles.app;
import vehicles.Car2;
import vehicles.ElectricCar2;
import vehicles.Vehicle2;
public class testCar2{
    public static void main(String[] args) {
        //Созданы экземпляры классов Car и ElectricCar. 
        Vehicle2 car = new Car2("Toyota Camry", "ABC123", "Red", 2020, 
                             "John Doe", 12345, "Gasoline");
        Vehicle2 electricCar = new ElectricCar2("Tesla Model 3", "TESLA1", "White", 2022, 
                                            "Jane Doe", 67890, 75);
        
        // Изменение свойств с помощью сеттеров
        car.setYR(1234);
        car.setON("Michael Johnson");
        electricCar.setIN(99999);

        
        // Вывод информации о транспортных средствах в консоль с помощью метода toString().
        System.out.println("Car details:");
        System.out.println(car.toString());
        System.out.println("\nElectric Car details:");
        //Получение информации о емкости батареи у электромобиля. 
         System.out.println("Battery capacity " + ((ElectricCar2) electricCar).getBC());
        System.out.println(electricCar.toString());
    }
}
