package bikeproject;

public class RoadBike extends Bike implements RoadParts{
	
	private int  tyreWidth, postHeight;
	
	public RoadBike()
	{
		super();
		this.type ="Road Bike";
		this.postHeight = 20;
		this.tyreWidth = 40;
	} 
	
	public RoadBike(int postHeight)
	{
		super();
		this.type ="Road Bike";
		this.postHeight = postHeight;
		this.tyreWidth = 40;
	}
		
	public RoadBike(String handleBars, String frame, String tyres, String seatType, int numGears,
			int tyreWidth, int postHeight) {
		super(handleBars, frame, tyres, seatType, numGears);
		this.type ="Road Bike";
		this.tyreWidth = tyreWidth;
		this.postHeight = postHeight;
	}
	@Override
	public void printDescription()
	{
		System.out.println("This bike is a " + this.getType() + " and has a " + this.getTyreWidth() + "mm tyres and a post height of " + this.getPostHeight() + ".");
	}
	@Override
	public int getTyreWidth(){
		return this.tyreWidth;
	}
	@Override
	public void setTyreWidth(int newValue){
		this.tyreWidth = newValue;
	}
		@Override
	public int getPostHeight(){
		return this.postHeight;
	}
	@Override
	public void setPostHeight(int newValue){
		this.postHeight = newValue;
	}
}