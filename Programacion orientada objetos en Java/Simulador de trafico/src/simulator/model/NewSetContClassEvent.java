package simulator.model;

import java.util.List;

import simulator.misc.Pair;

public class NewSetContClassEvent extends Event {
	
	private List<Pair<String,Integer>> cs;
	
	public NewSetContClassEvent(int time, List<Pair<String,Integer>> cs) {
		super(time);
		this.cs = cs;
		if(cs == null) {
			throw new IllegalArgumentException("weather list is null");
		}
	}


	@Override
	void execute(RoadMap map) {
		for(Pair<String,Integer> c : cs) {
			
			if(map.getVehicle(c.getFirst()) != null) {
				map.getVehicle(c.getFirst()).setGradoContaminacion(c.getSecond());
			}
			else {
				throw new IllegalArgumentException("no road to introduce weather");
			}
		}		
	}
	public String toString() {
		String ret = "Change C02 class:[";
		
		for(Pair<String,Integer> c : cs) {
			ret+= "(" + c.getFirst() + ", " + c.getSecond() + ")";
		}
		ret += "]";
	 return ret;
	}
}


