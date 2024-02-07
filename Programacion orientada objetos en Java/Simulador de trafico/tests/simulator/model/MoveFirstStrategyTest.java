package simulator.model;

import static org.junit.jupiter.api.Assertions.assertTrue;

import java.util.Arrays;
import java.util.List;

import org.junit.jupiter.api.Test;

import simulator.misc.Utils;
import simulator.model.Junction;
import simulator.model.MoveFirstStrategy;
import simulator.model.RoundRobinStrategy;
import simulator.model.Vehicle;

public class MoveFirstStrategyTest {

	@Test
	void test_1() {
		//  junctions
		Junction j1 = new Junction("j1", new RoundRobinStrategy(10), new MoveFirstStrategy(), 0, 0);
		Junction j2 = new Junction("j2", new RoundRobinStrategy(10), new MoveFirstStrategy(), 0, 0);


		// vehicles entered from r1
		Vehicle vs[] = new Vehicle[5];
		for(int i=0; i<vs.length; i++)
			vs[i] = new Vehicle("v"+i, 50, 1, Arrays.asList(j1, j2));
		
		List<Vehicle> q = Utils.arrayToList(vs);
		
		MoveFirstStrategy st = new MoveFirstStrategy();
		List<Vehicle> nq = st.dequeue(q);

		assertTrue( nq.size() == 1);
		assertTrue( nq.get(0).equals(q.get(0)));
	}
}
