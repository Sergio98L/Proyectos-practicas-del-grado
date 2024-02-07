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
import simulator.model.SetWeatherEvent;
import simulator.model.Weather;

class SetWeatherEventTest {

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
		Event e = new SetWeatherEvent(10,Arrays.asList(new Pair<>("r1",Weather.CLOUDY),new Pair<>("r2",Weather.RAINY)));
		e.execute(map);

		assertEquals(Weather.CLOUDY, map.getRoad("r1").getWeather());
		assertEquals(Weather.RAINY, map.getRoad("r2").getWeather());
	}

}
