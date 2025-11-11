public class GenericStackArray<E> {
    private E[] elements;
    private int size = 0;
    private static final int DEFAULT_CAPACITY = 10;
    
    
    public GenericStackArray() {
        elements = (E[]) new Object[DEFAULT_CAPACITY];
    }
    
    
    public int getSize() {
        return size;
    }
    
    
    public E peek() {
        if (isEmpty()) {
            throw new IllegalStateException("Стек пуст");
        }
        return elements[size - 1];
    }
    
    
    public void push(E o) {
        if (size >= elements.length) {
            
            E[] newArray = (E[]) new Object[elements.length * 2];
            
            System.arraycopy(elements, 0, newArray, 0, elements.length);
            elements = newArray;
        }
        elements[size++] = o;
    }
    
    
    public E pop() {
        if (isEmpty()) {
            throw new IllegalStateException("Стек пуст");
        }
        E o = elements[--size];
        elements[size] = null; 
        return o;
    }
    
    
    public boolean isEmpty() {
        return size == 0;
    }
    
    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder("стек: [");
        for (int i = 0; i < size; i++) {
            sb.append(elements[i]);
            if (i < size - 1) {
                sb.append(", ");
            }
        }
        sb.append("]");
        return sb.toString();
    }
    
    
    public static void main(String[] args) {
        GenericStackArray<String> stack = new GenericStackArray<>();
        
        stack.push("Привет");
        stack.push("Мир");
        stack.push("Java");
        
        System.out.println(stack);
        System.out.println("Размер стека: " + stack.getSize());
        
        System.out.println("Peek: " + stack.peek());
        System.out.println("Pop: " + stack.pop());
        System.out.println("Pop: " + stack.pop());
        
        System.out.println(stack);
        System.out.println("Размер стека: " + stack.getSize());
        
        
        GenericStackArray<Integer> numbers = new GenericStackArray<>();
        for (int i = 1; i <= 15; i++) {
            numbers.push(i);
        }
        System.out.println("\nЧисловой " + numbers);
    }
}