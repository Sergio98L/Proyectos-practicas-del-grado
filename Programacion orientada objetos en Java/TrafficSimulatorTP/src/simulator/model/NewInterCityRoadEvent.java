package simulator.model;

public class NewInterCityRoadEvent extends NewRoadEvent{
	
	public NewInterCityRoadEvent(int time, String id, String srcJun, String destJunc, int length, int co2Limit, int maxSpeed, Weather weather){
		super(time, id, srcJun, destJunc, maxSpeed, co2Limit, length, weather);
	}

	public Road createRoad() {
		return new InterCityRoad(id, _srcJunction, _destJunction, maxSpeed, contLimit, length, weather);
	}
	
}

