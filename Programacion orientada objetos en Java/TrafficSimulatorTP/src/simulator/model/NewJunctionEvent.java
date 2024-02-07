package simulator.model;

public class NewJunctionEvent extends Event{
	
	private String id;
	
	private LightSwitchingStrategy lsStrategy;
	
	private DequeuingStrategy dqStrategy;
	
	int xCoor;
	
	int yCoor;
	
	public NewJunctionEvent(int time, String id, LightSwitchingStrategy lsStrategy, DequeuingStrategy dqStrategy, int xCoor, int yCoor) {
		super(time);
		this.id = id;
		this.lsStrategy = lsStrategy;
		this.dqStrategy = dqStrategy;
		this.xCoor = xCoor;
		this.yCoor = yCoor;
	}

	@Override
	void execute(RoadMap map) {
		map.addJunction(new Junction(id, lsStrategy, dqStrategy, xCoor, yCoor));		
	}
	@Override
	public String toString() {
	return "New Junction '"+id+"'";
	} 
}
