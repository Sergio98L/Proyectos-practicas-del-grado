package simulator.model;

import java.util.ArrayList;
import java.util.List;

public class LessContaminationStrategy implements DequeuingStrategy{

	
	private int limit;
	
	public LessContaminationStrategy(int limit) {
		this.limit = limit;
	}
	
	@Override
	public List<Vehicle> dequeue(List<Vehicle> q) {
		List<Vehicle> aux = new ArrayList<Vehicle>();
		int cont =0;
		
	
		if(!q.isEmpty()) {
			
			
			
			if(q.size() <= limit ) {
				return q;
			}
		
			for(cont=0;cont <limit ;cont++) {
				boolean menorEncontrado = false;
				Vehicle minCont = q.get(0);
				
				for(int i=0; i < q.size();i++) {				
					if(q.get(i).getContClass() < minCont.getContClass()) {
						minCont = q.get(i);
						menorEncontrado = true;
					}
				}
				if(menorEncontrado) {
					aux.add(minCont);
					q.remove(minCont);
				}					
			}
		}
		return aux;
	}
}
