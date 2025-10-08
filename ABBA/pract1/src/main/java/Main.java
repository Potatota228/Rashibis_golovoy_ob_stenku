    public class Main {
        public static void main(String[]args){
         Car2 car1 = new Car2();
         car1.To_String();
         Car2 car2 = new Car2("TOYOTA","ABC123","yellow",2011);
         System.out.println("Age: " + car2.howOld());
         car2.To_String();
         Car2 car3 = new Car2("yellow");
         car3.To_String();
        }
    }
