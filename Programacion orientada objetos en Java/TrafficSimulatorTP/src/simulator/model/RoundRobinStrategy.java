package simulator.model;
import java.util.List;

import simulator.model.LightSwitchingStrategy;
import simulator.model.Road;
import simulator.model.Vehicle;

public class RoundRobinStrategy implements LightSwitchingStrategy{

	private int timeSlot;
	
	public RoundRobinStrategy(int timeSlot) {
		this.timeSlot = timeSlot;
	}
	
	@Override
	public int chooseNextGreen(List<Road> roads, List<List<Vehicle>> qs, int currGreen, int lastSwitchingTime,
			int currTime) {
		if(roads.isEmpty()) {
			return -1;
		}
		if(currGreen == -1) {

			return 0;
		}
		if(currTime-lastSwitchingTime <this.timeSlot) {
			return currGreen;
		}
		else {
			return (currGreen+1) % roads.size();
		}
	}

}
