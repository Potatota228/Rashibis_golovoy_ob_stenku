package bikeproject;

public interface MountainParts {
 String TERRAIN = "off_road";
 String getSuspension();
 void setSuspension(String newValue);
 int getFrameSize();
 void setFrameSize(int newValue);
}
