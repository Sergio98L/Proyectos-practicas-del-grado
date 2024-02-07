package simulator.factories;

import org.json.JSONObject;

import simulator.model.DequeuingStrategy;
import simulator.model.MoveVipsStrategy;

public class MoveVipsStrategyBuilder extends Builder<DequeuingStrategy>{
	
	public MoveVipsStrategyBuilder() {
		super("vip_dqs");
		}

	@Override
	protected DequeuingStrategy createTheInstance(JSONObject data) {
		if(!data.has("viptag")) {
			throw new IllegalArgumentException();
		}
		return new MoveVipsStrategy(data.getInt("timeslot"),data.getString("viptag"));
	}

}