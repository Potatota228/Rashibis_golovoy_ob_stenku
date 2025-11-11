import java.util.Arrays;

public class Task1_4 {
    
    
    public static <E extends Comparable<E>> E max(E[][] array) {
        if (array == null || array.length == 0) {
            return null;
        }
        
        E maxElement = array[0][0];
        
        for (int i = 0; i < array.length; i++) {
            for (int j = 0; j < array[i].length; j++) {
                if (array[i][j].compareTo(maxElement) > 0) {
                    maxElement = array[i][j];
                }
            }
        }
        
        return maxElement;
    }
    
    
    public static void main(String[] args) {
        Integer[][] numbers = {
            {3, 5, 2},
            {8, 1, 9},
            {4, 7, 6}
        };
        System.out.println("Массив: " + Arrays.toString(numbers));
        Integer maxNumber = max(numbers);
        System.out.println("Наибольшее число в матрице: " + maxNumber);
        
        
        String[][] words = {
            {"apple", "zebra"},
            {"cat", "dog"},
            {"banana", "elephant"}
        };
        System.out.println("Массив: " + Arrays.toString(words));
        String maxWord = max(words);
        System.out.println("Наибольшее слово (лексикографически): " + maxWord);
    }
}