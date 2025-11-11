import java.util.Arrays;

public class Task1_2 {
    
    
    public static <E> int linearSearch(E[] array, E key) {
        for (int i = 0; i < array.length; i++) {
            if (array[i].equals(key)) {
                return i;
            }
        }
        return -1;
    }
    
    
    public static void main(String[] args) {
        Integer[] numbers = {5, 2, 8, 12, 3, 7};
        System.out.println("Массив: " + Arrays.toString(numbers));
        int index1 = linearSearch(numbers, 8);
        System.out.println("Элемент 8 найден на позиции: " + index1);
        
        int index2 = linearSearch(numbers, 15);
        System.out.println("Элемент 15 найден на позиции: " + index2);
        
        
        String[] words = {"apple", "banana", "cherry", "date"};
        System.out.println("Массив: " + Arrays.toString(words));
        int index3 = linearSearch(words, "cherry");
        System.out.println("Элемент 'cherry' найден на позиции: " + index3);
        
        int index4 = linearSearch(words, "grape");
        System.out.println("Элемент 'grape' найден на позиции: " + index4);
    }
}