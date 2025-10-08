package bikeproject;

public class MountainBike extends Bike implements MountainParts{

	private String suspension;
	private int frameSize;
	
	public MountainBike()
	{
		super();
		this.suspension = "good";
		this.type = "Mountain Bike";
		this.frameSize = 100;
	}
	
    public MountainBike(String handleBars, String frame, String tyres, String seatType, int numGears, 
    		            String suspension, String type, int frameSize) {
		super(handleBars, frame, tyres, seatType, numGears);
		this.suspension = suspension;
		this.type = "Mountain Bike";
		this.frameSize = frameSize;
	}
    
	@Override
	public void printDescription()
	{
		System.out.println("This bike is a " + this.getType() + " bike and has a " + this.getSuspension() + " suspension and a frame size of " + this.getFrameSize() + "inches.");
		
	}
	@Override
	public String getSuspension(){
		return this.suspension;
	}
	@Override
 	public void setSuspension(String newValue){
		this.suspension = newValue;
	}
		@Override
	public int getFrameSize(){
		return this.frameSize;
	}
	@Override
 	public void setFrameSize(int newValue){
		this.frameSize = newValue;
	}
}
