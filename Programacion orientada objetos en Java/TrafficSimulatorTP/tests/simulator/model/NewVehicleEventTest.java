package simulator.model;

import static org.junit.jupiter.api.Assertions.*;

import java.util.Arrays;
import java.util.List;

import org.junit.jupiter.api.Test;

import simulator.model.CityRoad;
import simulator.model.Event;
import simulator.model.Junction;
import simulator.model.MoveFirstStrategy;
import simulator.model.NewVehicleEvent;
import simulator.model.Road;
import simulator.model.RoadMap;
import simulator.model.RoundRobinStrategy;
import simulator.model.Vehicle;
import simulator.model.Weather;

class NewVehicleEventTest {

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

		map.addJunction(j1);
		map.addJunction(j2);
		map.addJunction(j3);

		map.addRoad(r1);
		map.addRoad(r2);

		// add a new vehicle via an event
		Event e = new NewVehicleEvent(10,"v1", 50, 1, Arrays.asList("j1", "j2"));
		e.execute(map);
		
		// check that the vehicle was added to the map correctly
		List<Vehicle> l = map.getVehicles();
		
		assertEquals(1, l.size());
		
		Vehicle v = l.get(0);
		
		assertEquals("v1", v.getId());
		assertEquals(50, v.getMaxSpeed());
		assertEquals(1, v.getContClass());
		assertEquals(Arrays.asList(j1,j2), v.getItinerary());
	}

}
