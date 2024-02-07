package simulator.factories;


import org.json.JSONArray;
import org.json.JSONObject;

import simulator.model.DequeuingStrategy;
import simulator.model.Event;
import simulator.model.LightSwitchingStrategy;
import simulator.model.NewJunctionEvent;

public class NewJunctionEventBuilder extends Builder<Event>{

	private Factory<LightSwitchingStrategy> lssFactory;
	
	private Factory<DequeuingStrategy> dqFactory;
	
	public NewJunctionEventBuilder(Factory<LightSwitchingStrategy> lssFactory, Factory<DequeuingStrategy> dqFactory) {
		super("new_junction");
		this.lssFactory = lssFactory;
		this.dqFactory = dqFactory;
	}

	@Override
	protected Event createTheInstance(JSONObject data) {
		JSONObject lsStrategy = data.getJSONObject("ls_strategy");
		LightSwitchingStrategy l = lssFactory.createInstance(lsStrategy);
		
		JSONObject dqStrategy = data.getJSONObject("dq_strategy");
		DequeuingStrategy dq = dqFactory.createInstance(dqStrategy);
		
		JSONArray coor = data.getJSONArray("coor");
		
		return new NewJunctionEvent(data.getInt("time"),data.getString("id"),l,dq,coor.getInt(0),coor.getInt(1));
	}

}
