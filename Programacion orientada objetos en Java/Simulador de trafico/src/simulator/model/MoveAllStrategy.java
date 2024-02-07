package simulator.model;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

public class MoveAllStrategy implements DequeuingStrategy{

	@Override
	public List<Vehicle> dequeue(List<Vehicle> q) {
		
		List<Vehicle> list = new ArrayList<Vehicle>();
		
		Iterator<Vehicle> it = q.iterator();
		
		while (it.hasNext()) {
			list.add(it.next());
		}
		
		return list;
	}

}
