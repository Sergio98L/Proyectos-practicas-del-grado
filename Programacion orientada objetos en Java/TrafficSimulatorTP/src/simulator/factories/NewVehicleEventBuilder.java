package simulator.factories;

import java.util.ArrayList;
import java.util.List;

import org.json.JSONArray;
import org.json.JSONObject;

import simulator.model.Event;
import simulator.model.NewVehicleEvent;

public class NewVehicleEventBuilder extends Builder<Event>{

	public NewVehicleEventBuilder() {
		super("new_vehicle");
	}

	@Override
	protected Event createTheInstance(JSONObject data) {
		
		List<String> itin= new ArrayList<String>();
		
		JSONArray ja = data.getJSONArray("itinerary");
				
		for(int i = 0;i < ja.length();i++) {
			itin.add(ja.getString(i));
		}
		return new NewVehicleEvent(data.getInt("time"),data.getString("id"),data.getInt("maxspeed"),data.getInt("class"),itin);
	}

}
