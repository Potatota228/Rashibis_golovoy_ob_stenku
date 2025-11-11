import java.util.Arrays;

public class Task1_3 {
    
    
    static class Circle implements Comparable<Circle> {
        private double radius;
        
        public Circle(double radius) {
            this.radius = radius;
        }
        
        public double getRadius() {
            return radius;
        }
        
        @Override
        public int compareTo(Circle other) {
            if (this.radius > other.radius) {
                return 1;
            } else if (this.radius < other.radius) {
                return -1;
            } else {
                return 0;
            }
        }
        
        @Override
        public String toString() {
            return "Circle(radius=" + radius + ")";
        }
    }
    
    
    public static <E extends Comparable<E>> E max(E[] array) {
        if (array == null || array.length == 0) {
            return null;
        }
        
        E maxElement = array[0];
        
        for (int i = 1; i < array.length; i++) {
            if (array[i].compareTo(maxElement) > 0) {
                maxElement = array[i];
            }
        }
        
        return maxElement;
    }
    
    
    public static void main(String[] args) {
        Circle[] circles = {
            new Circle(5.0),
            new Circle(2.3),
            new Circle(8.5),
            new Circle(3.7),
            new Circle(6.2)
        };
        System.out.println("Массив: " + Arrays.toString(circles));
        Circle maxCircle = max(circles);
        System.out.println("Наибольший круг: " + maxCircle);
        
        
        Integer[] numbers = {5, 12, 3, 8, 15, 7};
        System.out.println("Массив: " + Arrays.toString(numbers));
        Integer maxNumber = max(numbers);
        System.out.println("Наибольшее число: " + maxNumber);
    }
}