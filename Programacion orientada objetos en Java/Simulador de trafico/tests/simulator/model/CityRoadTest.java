package simulator.model;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;
import static org.junit.jupiter.api.Assertions.assertTrue;

import java.util.Arrays;

import org.json.JSONObject;
import org.junit.jupiter.api.Test;

import simulator.model.CityRoad;
import simulator.model.Junction;
import simulator.model.MoveFirstStrategy;
import simulator.model.Road;
import simulator.model.RoundRobinStrategy;
import simulator.model.Vehicle;
import simulator.model.Weather;

class CityRoadTest {

	@Test
	void test_basic_info() {
		// two junctions
		Junction j1 = new Junction("j1", new RoundRobinStrategy(10), new MoveFirstStrategy(), 0, 0);
		Junction j2 = new Junction("j2", new RoundRobinStrategy(10), new MoveFirstStrategy(), 0, 0);

		// a road
		Road r1 = new CityRoad("r1", j1, j2, 100, 500, 1000, Weather.SUNNY);

		// src/dest
		assertEquals(j1, r1.getSrc());
		assertEquals(j2, r1.getDest());

		// test set/get weather
		assertEquals(Weather.SUNNY, r1.getWeather());
		r1.setWeather(Weather.CLOUDY);
		assertEquals(Weather.CLOUDY, r1.getWeather());

		// length
		assertEquals(1000, r1.getLength());

		// max speed
		assertEquals(100, r1.getMaxSpeed());

		// current speed limit
		assertEquals(100, r1.getSpeedLimit());

		// contamination limit
		assertEquals(500, r1.getContLimit());

		// total contamination
		assertEquals(0, r1.getTotalCO2());

	}

	// one vehicle overtakes another
	@Test
	void test_1() {

		// two junctions
		Junction j1 = new Junction("j1", new RoundRobinStrategy(10), new MoveFirstStrategy(), 0, 0);
		Junction j2 = new Junction("j2", new RoundRobinStrategy(10), new MoveFirstStrategy(), 0, 0);

		// a road
		Road r1 = new CityRoad("r1", j1, j2, 100, 10, 1000, Weather.SUNNY);

		// a vehicle
		Vehicle v1 = new Vehicle("v1", 50, 1, Arrays.asList(j1, j2));
		Vehicle v2 = new Vehicle("v2", 100, 3, Arrays.asList(j1, j2));

		// enter the road
		v1.moveToNextRoad();
		v2.moveToNextRoad();

		// at the beginning the order is [v1,v2]
		assertEquals(v1, r1.getVehicles().get(0));
		assertEquals(v2, r1.getVehicles().get(1));

		// move the vehicle in road 'r1'
		r1.advance(0);

		// the road should be r1
		assertEquals(v2, r1.getVehicles().get(0));
		assertEquals(v1, r1.getVehicles().get(1));

		// speed of v2 was changed
		assertEquals(50, v1.getSpeed());
		assertEquals(72, v2.getSpeed());

		// check correctness of totoal co2
		assertEquals(266, r1.getTotalCO2());
		assertEquals(50, v1.getTotalCO2());
		assertEquals(216, v2.getTotalCO2());

		r1.setWeather(Weather.STORM);
		r1.advance(1);

		// speed of v2 was changed
		assertEquals(50, v1.getSpeed());
		assertEquals(72, v2.getSpeed());

		// check correctness of totoal co2
		assertEquals(522, r1.getTotalCO2());
		assertEquals(100, v1.getTotalCO2());
		assertEquals(432, v2.getTotalCO2());
	}

	@Test
	void test_report() {

		// two junctions
		Junction j1 = new Junction("j1", new RoundRobinStrategy(10), new MoveFirstStrategy(), 0, 0);
		Junction j2 = new Junction("j2", new RoundRobinStrategy(10), new MoveFirstStrategy(), 0, 0);

		// a road
		Road r1 = new CityRoad("r1", j1, j2, 100, 10, 1000, Weather.SUNNY);

		// a vehicle
		Vehicle v1 = new Vehicle("v1", 50, 1, Arrays.asList(j1, j2));
		Vehicle v2 = new Vehicle("v2", 100, 3, Arrays.asList(j1, j2));

		// enter the road
		v1.moveToNextRoad();
		v2.moveToNextRoad();

		String s = "{\"speedlimit\":100,\"co2\":0,\"weather\":\"SUNNY\",\"vehicles\":[\"v1\",\"v2\"],\"id\":\"r1\"}";

		assertTrue(new JSONObject(s).similar(r1.report()));

		r1.advance(1);

		s = "{\"speedlimit\":100,\"co2\":266,\"weather\":\"SUNNY\",\"vehicles\":[\"v2\",\"v1\"],\"id\":\"r1\"}";
		assertTrue(new JSONObject(s).similar(r1.report()));
	}

	// list of vehicles is returned as unmodifiable
	@Test
	void test_list_of_vehicles_is_readonly() {

		// two junctions
		Junction j1 = new Junction("j1", new RoundRobinStrategy(10), new MoveFirstStrategy(), 0, 0);
		Junction j2 = new Junction("j2", new RoundRobinStrategy(10), new MoveFirstStrategy(), 0, 0);

		// a road
		Road r1 = new CityRoad("r1", j1, j2, 100, 10, 1000, Weather.SUNNY);

		// a vehicle
		Vehicle v1 = new Vehicle("v1", 50, 1, Arrays.asList(j1, j2));

		assertThrows(UnsupportedOperationException.class, () -> r1.getVehicles().add(v1));

	}

	@Test
	void error_handling() {
		// two junctions
		Junction j1 = new Junction("j1", new RoundRobinStrategy(10), new MoveFirstStrategy(), 0, 0);
		Junction j2 = new Junction("j2", new RoundRobinStrategy(10), new MoveFirstStrategy(), 0, 0);

		// id must be a non-empty string
		assertThrows(Exception.class, () -> new CityRoad(null, j1, j2, 100, 500, 1000, Weather.SUNNY));
		assertThrows(Exception.class, () -> new CityRoad("", j1, j2, 100, 500, 1000, Weather.SUNNY));

		// max speed must be positive
		assertThrows(Exception.class, () -> new CityRoad("r1", j1, j2, 0, 500, 1000, Weather.SUNNY));
		assertThrows(Exception.class, () -> new CityRoad("r1", j1, j2, -1, 500, 1000, Weather.SUNNY));

		// contamination limit must be non-negative
		assertThrows(Exception.class, () -> new CityRoad("r1", j1, j2, 100, -1, 1000, Weather.SUNNY));

		// contamination limit must be positive
		assertThrows(Exception.class, () -> new CityRoad("r1", j1, j2, 100, 500, 0, Weather.SUNNY));
		assertThrows(Exception.class, () -> new CityRoad("r1", j1, j2, 100, 500, -1, Weather.SUNNY));

		// weather cannot be null
		assertThrows(Exception.class, () -> new CityRoad("r1", j1, j2, 100, 500, 1000, null));

		// weather cannot be set to null
		assertThrows(Exception.class, () -> new CityRoad("r1", j1, j2, 100, 500, 1000, Weather.SUNNY).setWeather(null));

	}

}
