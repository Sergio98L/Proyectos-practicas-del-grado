package simulator.model;

import java.util.List;

import simulator.misc.Pair;

public class SetWeatherEvent extends Event{
	
	private List<Pair<String,Weather>> ws;
	
	public SetWeatherEvent(int time, List<Pair<String,Weather>> ws) {
		super(time);
		this.ws = ws;
		if(ws == null) {
			throw new IllegalArgumentException("weather list is null");
		}
		
	}

	@Override
	void execute(RoadMap map) {
		for(Pair<String,Weather> w : ws) {
			if(map.getRoad(w.getFirst()) == null) {
				throw new IllegalArgumentException("no road to introduce weather");
			}else {
				map.getRoad(w.getFirst()).setWeather(w.getSecond());

			}
		}
	}
	@Override
	public String toString() {	
		
		String ret = "Change Weather:[";
		
		for(Pair<String,Weather> c : ws) {
			ret+= "(" + c.getFirst() + ", " + c.getSecond() + ")";
		}
		ret += "]";
	 return ret;
	}
}
