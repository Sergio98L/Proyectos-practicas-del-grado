	package simulator.model;
	import java.util.List;

	import simulator.model.LightSwitchingStrategy;
	import simulator.model.Road;
	import simulator.model.Vehicle;

	public class VipsSemaforoStrategy  implements LightSwitchingStrategy{

		private int timeSlot;
		private String tag;
		
		public VipsSemaforoStrategy(int timeSlot,String tag) {
			this.timeSlot = timeSlot;
			this.tag = tag;
		}
		
		@Override
		public int chooseNextGreen(List<Road> roads, List<List<Vehicle>> qs, int currGreen, int lastSwitchingTime,int currTime) {
			boolean existenVips = false;			
			int i=0;
			int ind=0;
			//Recorre la lista de colas si haces qs.get(1) te devuelve la cola de la caretera de roads.get(1)	
			
			if(currGreen == -1) {	
				while(i <qs.size() && !existenVips){		
					for(Vehicle v : qs.get(i)) {
						if(v.getId().endsWith(tag))
							existenVips = true;
					}
				i++;								
				}
			ind = i;
			}
			else {			
				ind = currGreen;
				for(i = currGreen + 1; i < currGreen+1+roads.size();i++) {
					for(Vehicle v : qs.get(i%roads.size())) { //Busqueda circular
						if(v.getId().endsWith(tag)) {
							existenVips = true;
							ind = i%roads.size();
						}						
					}
				}				
			}
			if(existenVips) {
				return ind;
			}
			//Si no hay vip
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


