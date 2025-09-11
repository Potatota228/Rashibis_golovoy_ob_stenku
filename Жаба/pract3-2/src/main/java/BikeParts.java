package bikeproject
public interface BikeParts {
    String MAKE = "Oracle Cycles";
    String getHandleBars();
    void setHandleBars(String handleBars);

    String getFrame();
    void setFrame(String frame);

    String getType();
    void setType(String type);

    String getTyres();
    void setTyres(String tyres);

    String getSeatType();
    void setSeatType(String seat);
}
