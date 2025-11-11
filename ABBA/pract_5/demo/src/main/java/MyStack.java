import java.util.ArrayList;


public class MyStack {
    private ArrayList<Object> list = new ArrayList<>();
    
    
    public boolean isEmpty() {
        return list.isEmpty();
    }
    
    
    public int getSize() {
        return list.size();
    }
    
    
    public Object peek() {
        if (isEmpty()) {
            throw new IllegalStateException("Стек пуст");
        }
        return list.get(getSize() - 1);
    }
    
    
    public Object pop() {
        if (isEmpty()) {
            throw new IllegalStateException("Стек пуст");
        }
        Object o = list.get(getSize() - 1);
        list.remove(getSize() - 1);
        return o;
    }
    
    
    public void push(Object o) {
        list.add(o);
    }
    
    @Override
    public String toString() {
        return "стек: " + list.toString();
    }
    
    
    public static void main(String[] args) {
        MyStack stack = new MyStack();
        
        stack.push("Java");
        stack.push("Python");
        stack.push("C++");
        
        System.out.println(stack);
        System.out.println("Размер: " + stack.getSize());
        System.out.println("Peek: " + stack.peek());
        
        System.out.println("\nУдаляем элементы: ");
        while (!stack.isEmpty()) {
            System.out.println("Pop: " + stack.pop());
        }
        
        System.out.println("Стек пуст: " + stack.isEmpty());
    }
}
