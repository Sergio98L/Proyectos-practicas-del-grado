package simulator.factories;

import simulator.model.Event;
import simulator.model.NewCityRoadEvent;

public class NewCityRoadEventBuilder extends NewRoadEventBuilder{

	public NewCityRoadEventBuilder() {
		super("new_city_road");
	}
	
	@Override
	protected Event createRoad() {
		return new NewCityRoadEvent(time,id,srcJunc,destJunc,length,contLimit,maxSpeed,weather);
	}

}
