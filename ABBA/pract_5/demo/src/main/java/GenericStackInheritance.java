import java.util.ArrayList;
import java.util.Scanner;


public class GenericStackInheritance<E> extends ArrayList<E> {
    
    
    public GenericStackInheritance() {
        super();
    }
    
    
    public int getSize() {
        return size();
    }
    
    
    public E peek() {
        if (isEmpty()) {
            throw new IllegalStateException("Стек пуст");
        }
        return get(getSize() - 1);
    }
    
    
    public void push(E o) {
        add(o);
    }
    
    
    public E pop() {
        if (isEmpty()) {
            throw new IllegalStateException("Стек пуст");
        }
        E o = get(getSize() - 1);
        remove(getSize() - 1);
        return o;
    }
    
    @Override
    public String toString() {
        return "стек: " + super.toString();
    }
    
    
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        GenericStackInheritance<String> stack = new GenericStackInheritance<>();
        
        System.out.println("Введите 5 строк: ");
        
        for (int i = 1; i <= 5; i++) {
            System.out.print("Строка " + i + ": ");
            String input = scanner.nextLine();
            stack.push(input);
        }
        
        System.out.println("\nСтроки в обратном порядке: ");
        
        while (!stack.isEmpty()) {
            System.out.println(stack.pop());
        }
        
        scanner.close();
    }
}