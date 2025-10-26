public class ComparableCircle extends Circle {

    public ComparableCircle(double radius) {
        super(radius);
    }
    
    @Override
    public int compareTo(GeometricObject o) {
        if (o instanceof ComparableCircle)
            return Double.compare(this.getArea(), ((ComparableCircle) o).getArea());
        else
            return super.compareTo(o);
    }
}