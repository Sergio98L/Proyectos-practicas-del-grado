package simulator.model;

import java.util.ArrayList;
import java.util.List;

public class MoveVipsStrategy implements DequeuingStrategy{
	
	private int limit;
	private String tag;
	
		public MoveVipsStrategy(int limit,String tag) {
			this.limit = limit;
			this.tag = tag;
		}
	
		public List<Vehicle> dequeue(List<Vehicle> q) {
			
			List<Vehicle> list = new ArrayList<Vehicle>();
			int nVip=0; 
			if(!q.isEmpty()) {
								
				for(Vehicle v: q) {
					if(nVip < limit) {
						if(v.getId().endsWith(tag)) {
							list.add(v);
							q.remove(v);
						}
					}					
					nVip++;
				}
				for(Vehicle v: q) {				
						if(!v.getId().endsWith(tag)) {
							list.add(v);	
						}
					}								
			}
			
			return list;
		}

	}
