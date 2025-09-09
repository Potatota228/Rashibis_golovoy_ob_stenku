package vehicles.app;
import vehicles.Vehicle;
import vehicles.Car;
import vehicles.ElectricCar;
public class testCar{
    public static void main(String[] args) {
        Vehicle car = new Car("Toyota Camry", "ABC123", "Red", 2020, 
                             "John Doe", 12345, "Gasoline");
        Vehicle electricCar = new ElectricCar("Tesla Model 3", "TESLA1", "White", 2022, 
                                            "Jane Smith", 67890, 75);
        
        // Изменение свойств с помощью сеттеров
        car.setIN(1234);
        car.setON("Michael Johnson");
        electricCar.setIN(99999);
        
        // Для electricCar нужно привести тип, чтобы получить доступ к специфическим методам
        ((ElectricCar) electricCar).setBC(85);
        
        // Вывод информации с помощью toString() + полиморфизм
        System.out.println("Car details:");
        System.out.println(car.toString());
        System.out.println("\nElectric Car details:");
        System.out.println(electricCar.toString());
        
        // Демонстрация инкапсуляции - доступ к полям только через методы
        System.out.println("\nAccessing fields through getters:");
        System.out.println("Car owner: " + car.getON());
        System.out.println("Electric Car battery: " + ((ElectricCar) electricCar).getBC() + " kWh");
    
    }
}
