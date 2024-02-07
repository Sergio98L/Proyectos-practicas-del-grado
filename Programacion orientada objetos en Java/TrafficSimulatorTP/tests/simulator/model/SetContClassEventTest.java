package simulator.model;

import static org.junit.jupiter.api.Assertions.*;

import java.util.Arrays;
import org.junit.jupiter.api.Test;

import simulator.misc.Pair;
import simulator.model.CityRoad;
import simulator.model.Event;
import simulator.model.Junction;
import simulator.model.MoveFirstStrategy;
import simulator.model.Road;
import simulator.model.RoadMap;
import simulator.model.RoundRobinStrategy;
import simulator.model.Vehicle;
import simulator.model.Weather;

class SetContClassEventTest {

	@Test
	void test_1() {
		RoadMap map = new RoadMap();
		
		//  junctions
		Junction j1 = new Junction("j1", new RoundRobinStrategy(10), new MoveFirstStrategy(), 0, 0);
		Junction j2 = new Junction("j2", new RoundRobinStrategy(10), new MoveFirstStrategy(), 0, 0);
		Junction j3 = new Junction("j3", new RoundRobinStrategy(10), new MoveFirstStrategy(), 0, 0);

		//  roads
		Road r1 = new CityRoad("r1", j1, j2, 100, 500, 1000, Weather.SUNNY);
		Road r2 = new CityRoad("r2", j2, j3, 100, 500, 1000, Weather.SUNNY);

		Vehicle v1 = new Vehicle("v1", 50, 1, Arrays.asList(j1, j2));
		Vehicle v2 = new Vehicle("v2", 50, 1, Arrays.asList(j1, j2));
		Vehicle v3 = new Vehicle("v3", 50, 1, Arrays.asList(j2, j3));
		Vehicle v4 = new Vehicle("v4", 50, 1, Arrays.asList(j2, j3));
	
		map.addJunction(j1);
		map.addJunction(j2);
		map.addJunction(j3);

		map.addRoad(r1);
		map.addRoad(r2);

		map.addVehicle(v1);
		map.addVehicle(v2);
		map.addVehicle(v3);
		map.addVehicle(v4);

		Event e = new NewSetContClassEvent(10,Arrays.asList(new Pair<>("v1",4),new Pair<>("v3",7)));
		e.execute(map);
		assertEquals(4, map.getVehicle("v1").getContClass());
		assertEquals(7, map.getVehicle("v3").getContClass());

	}

}
