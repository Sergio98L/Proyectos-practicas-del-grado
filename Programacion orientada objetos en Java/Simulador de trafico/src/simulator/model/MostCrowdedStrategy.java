package simulator.model;

import java.util.List;

public class MostCrowdedStrategy implements LightSwitchingStrategy{

	private int timeSlot;
	
	public MostCrowdedStrategy(int timeSlot) {
		this.timeSlot = timeSlot;
	}
	
	@Override
	public int chooseNextGreen(List<Road> roads, List<List<Vehicle>> qs, int currGreen, int lastSwitchingTime,
			int currTime) {
		if(roads.isEmpty()) {
			return -1;
		}
		if(currGreen == -1) {
			
			int max = 0;
			int ind = 0;
			//roads y qs tienen la misma longitud asi que con un for normal recorro la lista de listas qs CON UN FOR NORMAL y me quedo CON EL INDICE de la carretera devulevo indice
			for(int i = 0; i < roads.size(); i++) {
				if(max < qs.get(i).size()) {
					max = qs.get(i).size();
					ind = i;
				}
			}
			return ind;
		}
		if(currTime-lastSwitchingTime <this.timeSlot) {
			return currGreen;
		}
		else {
			int max = 0;
			int ind = currGreen;
			for(int i = currGreen + 1; i < currGreen+1+roads.size();i++) {
				if(max < qs.get(i%roads.size()).size()) { //para asegurarte que es circular
					max = qs.get(i%roads.size()).size();
					ind = i%roads.size();
				}
			}
			return ind;
		}
	}

}
