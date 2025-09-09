import java.util.Scanner;
public class RBtoYN {
    public static void main (String[]args){
        final double ROUBLES_PER_YUAN = 11.91;
        int yuan;
        double roubles;
        Scanner input = new Scanner(System.in); // Даем себе возможность читать ввод с консоли
        System.out.println("Введите сумму в китайских юанях: ");
        yuan = input.nextInt();
        roubles = ROUBLES_PER_YUAN * yuan;
        System.out.println("Сумма в рублях равна: " + roubles);
    }
}
