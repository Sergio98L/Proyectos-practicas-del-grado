package simulator.factories;

import org.json.JSONObject;

import simulator.model.Event;
import simulator.model.Weather;

public abstract class NewRoadEventBuilder extends Builder<Event>{

	protected int time;
	
	protected String id;
	
	protected String srcJunc;
	
	protected String destJunc;
	
	protected int maxSpeed;
	
	protected int contLimit;
	
	protected int length;
	
	protected Weather weather;
	
	
	NewRoadEventBuilder(String type) {
		super(type);
	}

	@Override
	protected Event createTheInstance(JSONObject data) {
		time = data.getInt("time");
		id = data.getString("id");
		srcJunc = data.getString("src");
		destJunc = data.getString("dest");
		maxSpeed = data.getInt("maxspeed");
		contLimit = data.getInt("co2limit");
		length = data.getInt("length");
		weather = Weather.valueOf(data.getString("weather").toUpperCase());
		

		return createRoad();
	}
	
	protected abstract Event createRoad();

}
