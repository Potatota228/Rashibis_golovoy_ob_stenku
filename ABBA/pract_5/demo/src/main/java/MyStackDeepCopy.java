import java.util.ArrayList;


public class MyStackDeepCopy implements Cloneable {
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
    
    
    @Override
    public Object clone() {
        try {
            
            MyStackDeepCopy stackClone = (MyStackDeepCopy) super.clone();
            
            
            stackClone.list = new ArrayList<>();
            for (Object item : this.list) {
                
                
                stackClone.list.add(item);
            }
            
            return stackClone;
        } catch (CloneNotSupportedException ex) {
            return null;
        }
    }
    
    
    public static void main(String[] args) {
        MyStackDeepCopy stack1 = new MyStackDeepCopy();
        
        stack1.push("Java");
        stack1.push("Python");
        stack1.push("C++");
        
        System.out.println("Оригинальный стек: " + stack1);
        
        
        MyStackDeepCopy stack2 = (MyStackDeepCopy) stack1.clone();
        
        System.out.println("Клонированный стек: " + stack2);
        
        
        System.out.println("\nstack1 == stack2: " + (stack1 == stack2));
        
        
        stack2.push("Ruby");
        stack2.pop();
        stack2.pop();
        
        System.out.println("\nПосле изменения клона: ");
        System.out.println("Оригинальный стек: " + stack1);
        System.out.println("Клонированный стек: " + stack2);
        
        System.out.println("\nИзменения в клоне не влияют на оригинал");
    }
}