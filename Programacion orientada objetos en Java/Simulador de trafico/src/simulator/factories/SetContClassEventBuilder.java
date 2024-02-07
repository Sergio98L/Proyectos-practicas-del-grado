package simulator.factories;

import java.util.ArrayList;
import java.util.List;

import org.json.JSONArray;
import org.json.JSONObject;

import simulator.misc.Pair;
import simulator.model.Event;
import simulator.model.NewSetContClassEvent;


public class SetContClassEventBuilder extends Builder<Event>{

	public SetContClassEventBuilder() {
		super("set_cont_class");
	}

	@Override
	protected Event createTheInstance(JSONObject data) {
		List<Pair<String,Integer>> l = new ArrayList<Pair<String,Integer>>();
		JSONArray ja = data.getJSONArray("info");
		
		for(int i = 0; i < ja.length(); i++) {
			
			JSONObject jo = ja.getJSONObject(i);
			Pair<String, Integer> pair = new Pair<String, Integer>(jo.getString("vehicle"),jo.getInt("class"));
			l.add(pair);
		}
		return new NewSetContClassEvent(data.getInt("time"),l);
	}

}
