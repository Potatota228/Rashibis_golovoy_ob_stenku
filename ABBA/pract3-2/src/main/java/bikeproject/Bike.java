package bikeproject;

public class Bike implements BikeParts{

	private String handleBars, frame, tyres, seatType;
	protected String type;
	private int numGears;
	private final String make;
	public Bike(){
		this.handleBars = "drop";
		this.frame = "tourer";
		this.tyres = "semi-grip";
		this.seatType = "comfort";
		this.numGears = 14;
		this.make = "Oracle Cycles";

	}
	public Bike(String handleBars, String frame, String tyres, String seatType, int numGears) {
		this.handleBars = handleBars;
		this.frame = frame;
		this.tyres = tyres;
		this.seatType = seatType;
		this.numGears = numGears;
		this.make = "Oracle Cycles";
	}

	protected void printDescription()
	{
		System.out.println("\n" + this.make + "\n" 
				          + "This bike has " + this.handleBars + " handlebars on a " 
				          + this.frame + " frame with " + this.numGears + " gears."  
				          + "\nIt has a " + this.seatType + " seat with " + this.tyres + " tyres.");
	}
	@Override
	public String getHandleBars(){
		return this.handleBars;
	}
	@Override
    public void setHandleBars(String newValue){
		this.handleBars = newValue;
	}
	@Override
    public String getFrame(){
		return this.frame;
	}
	@Override
    public void setFrame(String newValue){
		this.frame = newValue;
	}

	@Override
    public String getTyres(){
		return this.tyres;
	}
	@Override
    public void setTyres(String newValue){
		this.tyres = newValue;
	}
	@Override
    public String getSeatType(){
		return this.seatType;
	}
	@Override
    public void setSeatType(String newValue){
		this.seatType = newValue;
	}
	@Override
    public String getType(){
		return this.type;
	}
	@Override
    public void setType(String newValue){
		this.type = newValue;
	}

}
	
	

