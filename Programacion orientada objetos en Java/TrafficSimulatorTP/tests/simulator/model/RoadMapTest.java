package simulator.model;

import static org.junit.jupiter.api.Assertions.*;

import java.util.Arrays;
import java.util.List;

import org.json.JSONObject;
import org.junit.jupiter.api.Test;

import simulator.model.CityRoad;
import simulator.model.Junction;
import simulator.model.MoveFirstStrategy;
import simulator.model.Road;
import simulator.model.RoadMap;
import simulator.model.RoundRobinStrategy;
import simulator.model.Vehicle;
import simulator.model.Weather;

class RoadMapTest {

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
	
		// check the getters of simulated objects works fine
		assertTrue(map.getJunction("j1").equals(j1));
		assertTrue(map.getJunction("j2").equals(j2));
		assertTrue(map.getJunction("j3").equals(j3));

		assertTrue(map.getRoad("r1").equals(r1));
		assertTrue(map.getRoad("r2").equals(r2));
		
		assertTrue(map.getVehicle("v1").equals(v1));
		assertTrue(map.getVehicle("v2").equals(v2));
		assertTrue(map.getVehicle("v3").equals(v3));
		
		// check that simulated objects are kept in the insertion order
		List<Junction> lj = map.getJunctions();
		assertEquals(j1, lj.get(0));
		assertEquals(j2, lj.get(1));
		assertEquals(j3, lj.get(2));

		List<Road> lr = map.getRoads();
		assertEquals(r1,lr.get(0));
		assertEquals(r2,lr.get(1));

		List<Vehicle> lv = map.getVehicles();
		assertEquals(v1, lv.get(0));
		assertEquals(v2, lv.get(1));
		assertEquals(v3, lv.get(2));

		// check the report
		String s = "{\"roads\":[{\"speedlimit\":100,\"co2\":0,\"weather\":\"SUNNY\",\"vehicles\":[],\"id\":\"r1\"},{\"speedlimit\":100,\"co2\":0,\"weather\":\"SUNNY\",\"vehicles\":[],\"id\":\"r2\"}],\"vehicles\":[{\"distance\":0,\"co2\":0,\"id\":\"v1\",\"class\":1,\"speed\":0,\"status\":\"PENDING\"},{\"distance\":0,\"co2\":0,\"id\":\"v2\",\"class\":1,\"speed\":0,\"status\":\"PENDING\"},{\"distance\":0,\"co2\":0,\"id\":\"v3\",\"class\":1,\"speed\":0,\"status\":\"PENDING\"},{\"distance\":0,\"co2\":0,\"id\":\"v4\",\"class\":1,\"speed\":0,\"status\":\"PENDING\"}],\"junctions\":[{\"green\":\"none\",\"queues\":[],\"id\":\"j1\"},{\"green\":\"none\",\"queues\":[{\"road\":\"r1\",\"vehicles\":[]}],\"id\":\"j2\"},{\"green\":\"none\",\"queues\":[{\"road\":\"r2\",\"vehicles\":[]}],\"id\":\"j3\"}]}";
		System.out.println(s);
		System.out.println(map.report().toString());
		assertTrue( new JSONObject(s).similar(map.report()));
	
	}

	@Test
	void error_handling() {
		RoadMap map = new RoadMap();
		
		//  junctions
		Junction j1 = new Junction("j1", new RoundRobinStrategy(10), new MoveFirstStrategy(), 0, 0);
		Junction j2 = new Junction("j2", new RoundRobinStrategy(10), new MoveFirstStrategy(), 0, 0);
		Junction j3 = new Junction("j3", new RoundRobinStrategy(10), new MoveFirstStrategy(), 0, 0);

		//  roads
		Road r1 = new CityRoad("r1", j1, j2, 100, 500, 1000, Weather.SUNNY);
		Road r2 = new CityRoad("r2", j1, j3, 100, 500, 1000, Weather.SUNNY);

		Vehicle v1 = new Vehicle("v1", 50, 1, Arrays.asList(j1, j2));
		Vehicle v2 = new Vehicle("v2", 50, 1, Arrays.asList(j1, j2));
		Vehicle v3 = new Vehicle("v3", 50, 1, Arrays.asList(j2, j3));
	
		map.addJunction(j1);
		map.addJunction(j2);
		map.addJunction(j3);
		
		map.addRoad(r1);
		map.addRoad(r2);
	
		map.addVehicle(v1);
		map.addVehicle(v2);
		
		// Invalid itinerary 
		assertThrows(Exception.class, () ->map.addVehicle(v3));


		// cannot add object with same id
		assertThrows(Exception.class, () -> map.addJunction(new Junction("j1", new RoundRobinStrategy(10), new MoveFirstStrategy(), 0, 0) ));
		assertThrows(Exception.class, () -> map.addRoad(new CityRoad("r1", j1, j2, 100, 500, 1000, Weather.SUNNY) ));
		assertThrows(Exception.class, () -> map.addVehicle(new Vehicle("v4", 50, 1, Arrays.asList(j2, j3))));
		

	}
}
