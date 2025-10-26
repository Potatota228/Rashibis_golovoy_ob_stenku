public class Square extends GeometricObject implements Colorable {
    private double side;

    public Square() {
        this(0);
    }

    public Square(double side) {
        this.side = side;
    }

    public double getSide() { return side; }
    public void setSide(double side) { this.side = side; }

    @Override
    public double getArea() {
        return side * side;
    }

    @Override
    public double getPerimeter() {
        return 4 * side;
    }

    @Override
    public String toString() {
        return "Квадрат со стороной " + side;
    }
        @Override
    public String howToColor(){
        return "Раскрасьте все четыре стороны";
    }
}
