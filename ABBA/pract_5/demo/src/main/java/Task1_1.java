import java.util.ArrayList;

public class Task1_1 {
    
    
    public static <E> ArrayList<E> removeDuplicates(ArrayList<E> list) {
        ArrayList<E> result = new ArrayList<>();
        
        for (E element : list) {
            if (!result.contains(element)) {
                result.add(element);
            }
        }
        
        return result;
    }
    
    
    public static void main(String[] args) {
        ArrayList<Integer> numbers = new ArrayList<>();
        numbers.add(5);
        numbers.add(2);
        numbers.add(5);
        numbers.add(8);
        numbers.add(2);
        numbers.add(9);
        
        System.out.println("Исходный список: " + numbers);
        ArrayList<Integer> unique = removeDuplicates(numbers);
        System.out.println("Без дубликатов: " + unique);
        
        
        ArrayList<String> words = new ArrayList<>();
        words.add("привет");
        words.add("мир");
        words.add("привет");
        words.add("java");
        
        System.out.println("\nИсходный список: " + words);
        ArrayList<String> uniqueWords = removeDuplicates(words);
        System.out.println("Без дубликатов: " + uniqueWords);
    }
}