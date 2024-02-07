package simulator.factories;

import simulator.model.Event;
import simulator.model.NewInterCityRoadEvent;

public class NewInterCityRoadEventBuilder extends NewRoadEventBuilder{

	public NewInterCityRoadEventBuilder() {
		super("new_inter_city_road");
	}

	@Override
	protected Event createRoad() {
		return new NewInterCityRoadEvent(time,id,srcJunc,destJunc,length,contLimit,maxSpeed,weather);
	}
}
