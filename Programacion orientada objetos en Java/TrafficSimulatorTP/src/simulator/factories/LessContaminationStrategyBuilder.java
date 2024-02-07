package simulator.factories;

import org.json.JSONObject;

import simulator.model.DequeuingStrategy;
import simulator.model.LessContaminationStrategy;

public class LessContaminationStrategyBuilder extends Builder<DequeuingStrategy>{
	
	public LessContaminationStrategyBuilder() {
		super("less_cont_dqs");
	}

	
	protected DequeuingStrategy createTheInstance(JSONObject data) {
		LessContaminationStrategy ts = new LessContaminationStrategy(1); 
		if(data != null) {
			if(data.has("limit")) {
				ts = new LessContaminationStrategy(data.getInt("limit"));
			}
		}
		return ts;
	}
}
