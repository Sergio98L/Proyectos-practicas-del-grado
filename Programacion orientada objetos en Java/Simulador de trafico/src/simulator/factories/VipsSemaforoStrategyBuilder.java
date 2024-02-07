package simulator.factories;

import org.json.JSONObject;

import simulator.model.LightSwitchingStrategy;
import simulator.model.VipsSemaforoStrategy;


public class VipsSemaforoStrategyBuilder extends Builder<LightSwitchingStrategy>{

	public VipsSemaforoStrategyBuilder() {
		super("vip_lss");
	}

	@Override
	protected LightSwitchingStrategy createTheInstance(JSONObject data) {
		VipsSemaforoStrategy ts = new VipsSemaforoStrategy(1,"vip");
		
		if(data != null) {
			if(data.has("timeslot")) {
				if(data.has("viptag")) {
					ts = new VipsSemaforoStrategy( data.getInt("timeslot"),data.getString("viptag"));
				}else {
					ts = new VipsSemaforoStrategy( data.getInt("timeslot"),"vip");
				}				
			}
		}
		return ts;
	}
}