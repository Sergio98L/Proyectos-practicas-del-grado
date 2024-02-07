package simulator.model;

import static org.junit.jupiter.api.Assertions.*;

import java.util.ArrayList;
import java.util.Arrays;
import org.json.JSONObject;
import org.junit.jupiter.api.Test;

import simulator.model.CityRoad;
import simulator.model.Junction;
import simulator.model.MoveFirstStrategy;
import simulator.model.Road;
import simulator.model.RoundRobinStrategy;
import simulator.model.Vehicle;
import simulator.model.VehicleStatus;
import simulator.model.Weather;

class VehicleTest {

		
	@Test
	void getset_contamination_class() {

		// two junctions
		Junction j1 = new Junction("j1", new RoundRobinStrategy(10), new MoveFirstStrategy(), 0, 0);
		Junction j2 = new Junction("j2", new RoundRobinStrategy(10), new MoveFirstStrategy(), 0, 0);

		// a vehicle
		Vehicle v1 = new Vehicle("v1", 50, 1, Arrays.asList(j1, j2));

		// initial value is as provided in the constructor
		assertEquals(1, v1.getContClass());

		// setContClass changes the contamination class
		v1.setGradoContaminacion(4);
		assertEquals(4, v1.getContClass());

		// contamination class must be between 0 and 10 (inclusive)
		assertThrows(Exception.class, () -> v1.setGradoContaminacion(11));
		assertThrows(Exception.class, () -> v1.setGradoContaminacion(-1));
	}

	@Test
	void getset_test_speed() {

		// two junctions
		Junction j1 = new Junction("j1", new RoundRobinStrategy(10), new MoveFirstStrategy(), 0, 0);
		Junction j2 = new Junction("j2", new RoundRobinStrategy(10), new MoveFirstStrategy(), 0, 0);

		// a road
		@SuppressWarnings("unused")
		Road r1 = new CityRoad("r1", j1, j2, 100, 10, 1000, Weather.SUNNY);

		// a vehicle
		Vehicle v1 = new Vehicle("v1", 50, 1, Arrays.asList(j1, j2));

		// when vehicle is not traveling, setSpeed does nothing
		assertEquals(0, v1.getSpeed());
		v1.setSpeed(30);
		assertEquals(0, v1.getSpeed());

		// when vehicle is traveling, setSpeed changes the speed
		v1.moveToNextRoad();
		v1.setSpeed(30);
		assertEquals(30, v1.getSpeed());

		// when the maximum speed is exceeded, speed is set to maxSpeed
		v1.setSpeed(51);
		assertEquals(50, v1.getSpeed());

		// speed must be non-negative
		assertThrows(Exception.class, () -> v1.setSpeed(-1));

	}

	@Test
	void test_report() {
		// two junctions
		Junction j1 = new Junction("j1", new RoundRobinStrategy(10), new MoveFirstStrategy(), 0, 0);
		Junction j2 = new Junction("j2", new RoundRobinStrategy(10), new MoveFirstStrategy(), 0, 0);

		// a vehicle
		Vehicle v1 = new Vehicle("v1", 50, 1, Arrays.asList(j1, j2));
		
		// check that the report/toString is OK
		String s = "{\"distance\":0,\"co2\":0,\"id\":\"v1\",\"class\":1,\"speed\":0,\"status\":\"PENDING\"}";
		JSONObject jo = new JSONObject(s);
		
		JSONObject report = v1.report();
		assertTrue(jo.similar(report));
		
		assertEquals("v1", v1.getId());
	}
	
	// when asking for the itinerary, it should be returned as read only
	@Test
	void test_iterinary_is_readonly() {
		// two junctions
		Junction j1 = new Junction("j1", new RoundRobinStrategy(10), new MoveFirstStrategy(), 0, 0);
		Junction j2 = new Junction("j2", new RoundRobinStrategy(10), new MoveFirstStrategy(), 0, 0);
		Junction j3 = new Junction("j3", new RoundRobinStrategy(10), new MoveFirstStrategy(), 0, 0);

		// a vehicle
		Vehicle v1 = new Vehicle("v1", 50, 1, Arrays.asList(j1, j2));
		assertThrows(UnsupportedOperationException.class, () -> v1.getItinerary().add(j3));

	}
	
	// some basic tests of the different methods
	@Test
	void test_1() {

		// two junctions
		Junction j1 = new Junction("j1", new RoundRobinStrategy(10), new MoveFirstStrategy(), 0, 0);
		Junction j2 = new Junction("j2", new RoundRobinStrategy(10), new MoveFirstStrategy(), 0, 0);

		// a road
		Road r1 = new CityRoad("r1", j1, j2, 100, 10, 1000, Weather.SUNNY);

		// a vehicle
		Vehicle v1 = new Vehicle("v1", 50, 1, Arrays.asList(j1, j2));

		// the road should be null at the beginning
		assertNull(v1.getRoad());

		// the velocity should be 0
		assertEquals(0, v1.getSpeed());

		// the status of v1 should be PENDING
		assertEquals(VehicleStatus.PENDING, v1.getStatus());

		// no vehicle on the road yet
		assertEquals(0, r1.getVehicles().size());

		// enter the road
		v1.moveToNextRoad();

		// the status of v1 should be TRAVELING
		assertEquals(VehicleStatus.TRAVELING, v1.getStatus());

		// the road should be r1
		assertEquals(v1.getRoad(), r1);

		// the list of vehicles on r1 should be [v1]
		assertEquals(r1.getVehicles().size(), 1);
		assertEquals(r1.getVehicles().get(0), v1);

		// move the vehicle in road 'r1'
		r1.advance(0);

		// the last advance should move vehicle 'v1' for 50 units
		assertEquals(50, v1.getLocation());
		
		// check the vehicle's contamination
		assertEquals(50,v1.getTotalCO2());

		// check that the report/toString is OK
		String s = "{\"distance\":50,\"road\":\"r1\",\"co2\":50,\"location\":50,\"id\":\"v1\",\"class\":1,\"speed\":50,\"status\":\"TRAVELING\"}";
		JSONObject jo = new JSONObject(s);
		
		JSONObject report = v1.report();
		assertTrue(jo.similar(report));
	}

	@Test
	void error_handling() {
		
		// two junctions
		Junction j1 = new Junction("j1", new RoundRobinStrategy(10), new MoveFirstStrategy(), 0, 0);
		Junction j2 = new Junction("j2", new RoundRobinStrategy(10), new MoveFirstStrategy(), 0, 0);

		// id must be a non-empty string
		assertThrows(Exception.class, () -> new Vehicle(null, 50, 1, Arrays.asList(j1, j2)));
		assertThrows(Exception.class, () -> new Vehicle("", 50, 1, Arrays.asList(j1, j2)));

		// the maximum speed must be positive
		assertThrows(Exception.class, () -> new Vehicle("v", 0, 1, Arrays.asList(j1, j2)));

		// contamination class must be non-negative
		assertThrows(Exception.class, () -> new Vehicle("v", 100, -5, Arrays.asList(j1, j2)));

		// itinerary must be a list with at least two junctions
		assertThrows(Exception.class, () -> new Vehicle("v", 100, 5, null));
		assertThrows(Exception.class, () -> new Vehicle("v", 100, 5, new ArrayList<>()));
		assertThrows(Exception.class, () -> new Vehicle("v", 100, 5, Arrays.asList(j1)));

	}

}
