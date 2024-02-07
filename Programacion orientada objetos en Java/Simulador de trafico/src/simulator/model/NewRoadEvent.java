package simulator.model;

public abstract class NewRoadEvent extends Event{

	protected String id;
	
	protected String srcJunc;
	
	protected String destJunc;
	
	protected Junction _srcJunction;
	
	protected Junction _destJunction;
	
	protected int maxSpeed;
	
	protected int contLimit;
	
	protected int length;
	
	protected Weather weather;
	
	public NewRoadEvent(int time,String id, String srcJunc, String destJunc,
			int maxSpeed,int contLimit, int length, Weather weather) {
		super(time);
		this.id = id;
		this.srcJunc = srcJunc;
		this.destJunc = destJunc;
		this.maxSpeed = maxSpeed;
		this.contLimit = contLimit;
		this.length = length;
		this.weather = weather;
	}

	@Override
	void execute(RoadMap map) {
		_srcJunction = map.getJunction(srcJunc);
		_destJunction = map.getJunction(destJunc);
		map.addRoad(createRoad());
	}

	public abstract Road createRoad(); 
	
	@Override
	public String toString() {
		return "New Road '"+ id +"'";
	}
}
