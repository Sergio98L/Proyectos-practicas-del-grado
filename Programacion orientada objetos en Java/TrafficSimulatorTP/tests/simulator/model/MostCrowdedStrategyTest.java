package simulator.model;

import static org.junit.jupiter.api.Assertions.*;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

import org.junit.jupiter.api.Test;

import simulator.misc.Utils;
import simulator.model.CityRoad;
import simulator.model.Junction;
import simulator.model.MostCrowdedStrategy;
import simulator.model.MoveFirstStrategy;
import simulator.model.Road;
import simulator.model.RoundRobinStrategy;
import simulator.model.Vehicle;
import simulator.model.Weather;

class MostCrowdedStrategyTest {

	
	@Test
	void test_1() {
		
		//  junctions
		Junction j1 = new Junction("j1", new RoundRobinStrategy(10), new MoveFirstStrategy(), 0, 0);
		Junction j2 = new Junction("j2", new RoundRobinStrategy(10), new MoveFirstStrategy(), 0, 0);
		Junction j3 = new Junction("j3", new RoundRobinStrategy(10), new MoveFirstStrategy(), 0, 0);

		//  roads
		Road r1 = new CityRoad("r1", j1, j2, 100, 500, 1000, Weather.SUNNY);
		Road r2 = new CityRoad("r1", j3, j2, 100, 500, 1000, Weather.SUNNY);


		// vehicles entered from r1
		Vehicle vs1[] = new Vehicle[5];
		for(int i=0; i<vs1.length; i++)
			vs1[i] = new Vehicle("v"+i, 50, 1, Arrays.asList(j1, j2));

		// vehicles entered from r2
		Vehicle vs2[] = new Vehicle[5];
		for(int i=0; i<vs2.length; i++)
			vs2[i] = new Vehicle("v"+i, 50, 1, Arrays.asList(j1, j2));


		List<Road> rs = new ArrayList<>();
		rs.add(r1);
		rs.add(r2);

		List<List<Vehicle>> q = new ArrayList<>();
		q.add( Utils.arrayToList(vs1));
		q.add( Utils.arrayToList(vs2));
		
		MostCrowdedStrategy st = new MostCrowdedStrategy(3);

		assertEquals(0, st.chooseNextGreen(rs, q, -1, 0, 11));
		assertEquals(0, st.chooseNextGreen(rs, q, 0, 11, 12));
		assertEquals(0, st.chooseNextGreen(rs, q, 0, 11, 13));
		assertEquals(1, st.chooseNextGreen(rs, q, 0, 11, 14));

		
		q.get(0).remove(0);
		assertEquals(1, st.chooseNextGreen(rs, q, -1, 0, 11));
		q.get(1).remove(0);
		assertEquals(1, st.chooseNextGreen(rs, q, 1, 11, 12));
		q.get(1).remove(0);
		assertEquals(1, st.chooseNextGreen(rs, q, 1, 11, 13));
		q.get(1).remove(0);
		assertEquals(0, st.chooseNextGreen(rs, q, 1, 11, 14));
//		(List<Road> roads, List<List<Vehicle>> qs, int currGreen, int lastSwitchingTime,
//				int currTime
	}

}
