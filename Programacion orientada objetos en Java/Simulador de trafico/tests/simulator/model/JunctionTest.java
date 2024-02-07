package simulator.model;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

import simulator.model.InterCityRoad;
import simulator.model.Junction;
import simulator.model.MoveFirstStrategy;
import simulator.model.Road;
import simulator.model.RoundRobinStrategy;
import simulator.model.Weather;

class JunctionTest {

	@Test
	void test_1() {
		// junctions
		Junction j1 = new Junction("j1", new RoundRobinStrategy(10), new MoveFirstStrategy(), 0, 0);
		Junction j2 = new Junction("j2", new RoundRobinStrategy(10), new MoveFirstStrategy(), 0, 0);
		Junction j3 = new Junction("j3", new RoundRobinStrategy(10), new MoveFirstStrategy(), 0, 0);
		Junction j4 = new Junction("j4", new RoundRobinStrategy(10), new MoveFirstStrategy(), 0, 0);
		Junction j5 = new Junction("j5", new RoundRobinStrategy(10), new MoveFirstStrategy(), 0, 0);

		// roads
		Road r1 = new InterCityRoad("r1", j1, j3, 100, 500, 1000, Weather.SUNNY);
		Road r2 = new InterCityRoad("r2", j2, j3, 100, 500, 1000, Weather.SUNNY);
		Road r3 = new InterCityRoad("r3", j3, j4, 100, 500, 1000, Weather.SUNNY);
		Road r4 = new InterCityRoad("r4", j3, j5, 100, 500, 1000, Weather.SUNNY);
		
		// check that junctions stores roads correctly
		assertEquals(r1, j1.roadTo(j3));
		assertEquals(r2, j2.roadTo(j3));
		assertEquals(r3, j3.roadTo(j4));
		assertEquals(r4, j3.roadTo(j5));
		
		assertNull(j1.roadTo(j4));
		assertNull(j2.roadTo(j4));
		assertNull(j3.roadTo(j1));
		assertNull(j3.roadTo(j2));

	}
	
	@Test
	void error_handling() {
		// id must be a non-empty string
		assertThrows(Exception.class, () -> new Junction(null, new RoundRobinStrategy(10), new MoveFirstStrategy(), 0, 0));
		assertThrows(Exception.class, () -> new Junction("", new RoundRobinStrategy(10), new MoveFirstStrategy(), 0, 0));
		
		// strategies cannot be null
		assertThrows(Exception.class, () -> new Junction("j1", null, new MoveFirstStrategy(), 0, 0));
		assertThrows(Exception.class, () -> new Junction("j1", new RoundRobinStrategy(10), null, 0, 0));
		
		// coordinates are non-negative
		assertThrows(Exception.class, () -> new Junction("j1", new RoundRobinStrategy(10), new MoveFirstStrategy(), -1, 0));
		assertThrows(Exception.class, () -> new Junction("j1", new RoundRobinStrategy(10), new MoveFirstStrategy(), 0, -1));
	}

}
