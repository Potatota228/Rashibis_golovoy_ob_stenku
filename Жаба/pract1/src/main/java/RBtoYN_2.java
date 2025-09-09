import java.util.Scanner;
public class RBtoYN_2 {
    public static void main (String[]args){
        final double ROUBLES_PER_YUAN = 11.91;
        int yuan;
        double roubles;
        int rroubles;
        Scanner input = new Scanner(System.in); // Даем себе возможность читать ввод с консоли
        System.out.println("Введите сумму в китайских юанях: ");
        yuan = input.nextInt();
        roubles = ROUBLES_PER_YUAN * yuan;
        rroubles = (int)Math.round(roubles);
        if ((yuan/10>=1 && yuan%100<=19) || (yuan%10==5) || (yuan%10==6) || (yuan%10==7) || (yuan%10==8) || (yuan%10==9) || (yuan%10==0))
            System.out.println("При конвертации, сумма в " + yuan + " китайских юаней составляет " + rroubles + " в рублях");
        else if (yuan%10==1)
             System.out.println("При конвертации, сумма в " + yuan + " китайский юань составляет " + rroubles + " в рублях");
        else if ((yuan%10==2) || (yuan%10==3) || (yuan%10==4))
            System.out.println("При конвертации, сумма в " + yuan + " китайских юаня составляет " + rroubles + " в рублях");
    }
}
