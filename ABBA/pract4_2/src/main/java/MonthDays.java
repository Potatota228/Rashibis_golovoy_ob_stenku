import java.util.InputMismatchException;
import java.util.Scanner;

public class MonthDays {
    public static void main(String[] args) {
        String[] months = {
            "январь", "февраль", "март", "апрель", "май",
            "июнь", "июль", "август", "сентябрь", "октябрь",
            "ноябрь", "декабрь"
        };
        int[] days = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

        Scanner sc = new Scanner(System.in);
        try {
            System.out.print("Введите номер месяца (1–12): ");
            int month = sc.nextInt();

            if (month == 2) {
                System.out.print("Введите год: ");
                int year = sc.nextInt();
                if (isLeapYear(year))
                    days[1] = 29;
            }

            System.out.println(months[month - 1] + " содержит " + days[month - 1] + " дней");
        } catch (ArrayIndexOutOfBoundsException e) {
            System.out.println("Недопустимое число месяца!");
        } catch (InputMismatchException e) {
            System.out.println("Введите только целое число!");
        }
    }

    public static boolean isLeapYear(int year) {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }
}