import java.util.ArrayList;
import java.util.Scanner;


public class MyStackInheritance extends ArrayList<Object> {
    
    
    @Override
    public boolean isEmpty() {
        return super.isEmpty();
    }
    
    
    public int getSize() {
        return size();
    }
    
    
    public Object peek() {
        if (isEmpty()) {
            throw new IllegalStateException("Стек пуст");
        }
        return get(getSize() - 1);
    }
    
    
    public Object pop() {
        if (isEmpty()) {
            throw new IllegalStateException("Стек пуст");
        }
        Object o = get(getSize() - 1);
        remove(getSize() - 1);
        return o;
    }
    
    
    public void push(Object o) {
        add(o);
    }
    
    @Override
    public String toString() {
        return "стек: " + super.toString();
    }
    
    
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        MyStackInheritance stack = new MyStackInheritance();
        
        System.out.println("Введите пять строк: ");
        
        for (int i = 1; i <= 5; i++) {
            System.out.print("Строка " + i + ": ");
            String input = scanner.nextLine();
            stack.push(input);
        }
        
        System.out.println("\nВведённые строки в обратном порядке: ");
        
        while (!stack.isEmpty()) {
            System.out.println(stack.pop());
        }
        
        scanner.close();
    }
}