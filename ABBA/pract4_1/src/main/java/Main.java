import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);

        while (true) {
            System.out.print("\n --------------------\n Выберите фигуру: \n 1. Треугольник \n 2. Прямоугольник \n 3. Квадрат \n 4. Круг\n 5. Все фигуры\n 6. Сравнение\n 0. Выход\n");

            int choice = input.nextInt();

            switch (choice) {
                case 1 -> {
                    try {
                        System.out.print("Введите первую сторону треугольника: ");
                        double side1 = input.nextDouble();

                        System.out.print("Введите вторую сторону треугольника: ");
                        double side2 = input.nextDouble();

                        System.out.print("Введите третью сторону треугольника: ");
                        double side3 = input.nextDouble();

                        System.out.print("Введите цвет треугольника: ");
                        String color = input.next();

                        System.out.print("Закрашен ли треугольник? (true/false): ");
                        boolean filled = input.nextBoolean();

                        Triangle triangle = new Triangle(side1, side2, side3);
                        triangle.setColor(color);
                        triangle.setFilled(filled);

                        System.out.println("\nИнформация о треугольнике");
                        System.out.println(triangle.toString());
                        System.out.println("Площадь: " + triangle.getArea());
                        System.out.println("Периметр: " + triangle.getPerimeter());
                        System.out.println("Цвет: " + triangle.getColor());
                        System.out.println("Закрашен: " + triangle.isFilled());
                        System.out.println("Как закрашивать: " + triangle.howToColor());
                    } catch (IllegalTriangleException e) {
                        System.out.println("Ошибка: " + e.getMessage());
                    } catch (Exception e) {
                        System.out.println("Неверный ввод. Попробуйте снова.");
                        input.nextLine();
                    }
                    break;
                }

                case 2 -> {
                    try {
                        System.out.print("Введите ширину прямоугольника: ");
                        double width = input.nextDouble();

                        System.out.print("Введите высоту прямоугольника: ");
                        double height = input.nextDouble();

                        System.out.print("Введите цвет прямоугольника: ");
                        String color = input.next();

                        System.out.print("Закрашен ли прямоугольник? (true/false): ");
                        boolean filled = input.nextBoolean();

                        Rectangle rectangle = new Rectangle(width, height);
                        rectangle.setColor(color);
                        rectangle.setFilled(filled);

                        System.out.println("\n Информация о прямоугольнике");
                        System.out.println(rectangle.toString());
                        System.out.println("Площадь: " + rectangle.getArea());
                        System.out.println("Периметр: " + rectangle.getPerimeter());
                        System.out.println("Цвет: " + rectangle.getColor());
                        System.out.println("Закрашен: " + rectangle.isFilled());
                        System.out.println("Как закрашивать: " + rectangle.howToColor());
                    } catch (Exception e) {
                        System.out.println("Неверный ввод. Попробуйте снова.");
                        input.nextLine();
                    }
                    break;
                }
                case 3 -> {
                    try {
                        System.out.print("Введите длину стороны квадрата: ");
                        double side = input.nextDouble();

                        System.out.print("Введите цвет квадрата: ");
                        String color = input.next();

                        System.out.print("Закрашен ли квадрат? (true/false): ");
                        boolean filled = input.nextBoolean();

                        Square square = new Square(side);
                        square.setColor(color);
                        square.setFilled(filled);

                        System.out.println("\n Информация о квадрате");
                        System.out.println(square.toString());
                        System.out.println("Площадь: " + square.getArea());
                        System.out.println("Периметр: " + square.getPerimeter());
                        System.out.println("Цвет: " + square.getColor());
                        System.out.println("Закрашен: " + square.isFilled());
                        System.out.println("Как закрашивать: " + square.howToColor());
                    } catch (Exception e) {
                        System.out.println("Неверный ввод. Попробуйте снова.");
                        input.nextLine();
                    }
                    break;
                }
                
                case 4 -> {
                    try {
                        System.out.print("Введите радиус круга: ");
                        double radius = input.nextDouble();

                        System.out.print("Введите цвет круга: ");
                        String color = input.next();

                        System.out.print("Закрашен ли круг? (true/false): ");
                        boolean filled = input.nextBoolean();

                        Circle circle = new Circle();
                        circle.setColor(color);
                        circle.setFilled(filled);

                        System.out.println("\n Информация о квадрате");
                        System.out.println(circle.toString());
                        System.out.println("Площадь: " + circle.getArea());
                        System.out.println("Периметр: " + circle.getPerimeter());
                        System.out.println("Цвет: " + circle.getColor());
                        System.out.println("Закрашен: " + circle.isFilled());
                        System.out.println("Как закрашивать: " + circle.howToColor());
                    } catch (Exception e) {
                        System.out.println("Неверный ввод. Попробуйте снова.");
                        input.nextLine();
                    }
                    break;
                }
            
                case 5 -> {
                    try {
                        System.out.println("Создание неправильного треугольника (1, 2, 10):");
                        Triangle badTriangle = new Triangle(1, 2, 10);
                    } catch (IllegalTriangleException e) {
                    System.out.println("Ошибка: " + e.getMessage());
                    }

                    // Правильный треугольник
                    try {
                        System.out.println("\nСоздание правильного треугольника (3, 4, 5):");
                        Triangle triangle = new Triangle(3, 4, 5);
                        triangle.setColor("синий");
                        triangle.setFilled(true);

                        System.out.println(triangle);
                        System.out.println("Площадь: " + triangle.getArea());
                        System.out.println("Периметр: " + triangle.getPerimeter());
                        System.out.println("Цвет: " + triangle.getColor());
                        System.out.println("Закрашен: " + triangle.isFilled());
                        System.out.println("Как закрашивать: " + triangle.howToColor());
                    } catch (IllegalTriangleException e) {
                        System.out.println("Ошибка: " + e.getMessage());
                    }

                    // Прямоугольник
                    System.out.println("\nСоздание прямоугольника (5x8):");
                    Rectangle rect = new Rectangle(5, 8);
                    rect.setColor("зелёный");
                    rect.setFilled(false);

                    System.out.println(rect);
                    System.out.println("Площадь: " + rect.getArea());
                    System.out.println("Периметр: " + rect.getPerimeter());
                    System.out.println("Цвет: " + rect.getColor());
                    System.out.println("Закрашен: " + rect.isFilled());
                    System.out.println("Как закрашивать: " + rect.howToColor());

                    // 4. Квадрат
                    System.out.println("\nСоздание квадрата (сторона = 6):");
                    Square square = new Square(6);
                    square.setColor("красный");
                    square.setFilled(true);

                    System.out.println(square);
                    System.out.println("Площадь: " + square.getArea());
                    System.out.println("Периметр: " + square.getPerimeter());
                    System.out.println("Цвет: " + square.getColor());
                    System.out.println("Закрашен: " + square.isFilled());
                    System.out.println("Как закрашивать: " + square.howToColor());

                    //5. Круг
                    System.out.println("\nСоздание круга (сторона = 6):");
                    Circle circle = new Circle(6);
                    circle.setColor("красный");
                    circle.setFilled(true);

                    System.out.println(circle);
                    System.out.println("Площадь: " + circle.getArea());
                    System.out.println("Периметр: " + circle.getPerimeter());
                    System.out.println("Цвет: " + circle.getColor());
                    System.out.println("Закрашен: " + circle.isFilled());
                    System.out.println("Как закрашивать: " + circle.howToColor());

                    System.out.println("\n Проверка завершена успешно");
                    break;
                }
                
                 case 6 -> {
                    System.out.println("\nСоздание круга 1 (радиус = 3):");
                    ComparableCircle circle1 = new ComparableCircle(3);

                    System.out.println("\nСоздание круга 2 (радиус = 6):");
                    ComparableCircle circle2 = new ComparableCircle(6);

                    System.out.println("\nСоздание прямоугольника 1 (1x2):");
                    Rectangle rect1 = new Rectangle(1, 2);

                    System.out.println("\nСоздание прямоугольника 2 (2x3):");
                    Rectangle rect2 = new Rectangle(2, 3);

                    int res1 = circle1.compareTo(circle2);
                    int res2 = circle1.compareTo(rect1);
                    int res3 = rect1.compareTo(rect2);

                    int[] results = {res1, res2, res3};
                    String[] figure1Names = {"Круг 1", "Круг 1", "Прямоугольник 1"};
                    String[] figure2Names = {"Круг 2", "Прямоугольник 1", "Прямоугольник 2"};

                    for (int i = 0; i < results.length; i++) {
                        switch (results[i]) {
                            case 1 -> System.out.println("\n" + figure1Names[i] + " больше, чем " + figure2Names[i]);
                            case 0 -> System.out.println("\n" + figure1Names[i] + " равна " + figure2Names[i]);
                            case -1 -> System.out.println("\n" + figure1Names[i] + " меньше, чем " + figure2Names[i]);
                            default -> System.out.println("\n" + "Неизвестный результат сравнения между " + figure1Names[i] + " и " + figure2Names[i]);
                        }
                    }
                    break;
                 }
                case 0 -> {
                    System.out.println("Выход из программы...");
                    input.close();
                    return;
                }

                default -> System.out.println("Неверный выбор. Попробуйте снова.");
            }
        }
    }
}
