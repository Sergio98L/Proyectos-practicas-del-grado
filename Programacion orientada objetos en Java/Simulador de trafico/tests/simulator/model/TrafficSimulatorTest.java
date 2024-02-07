package simulator.model;

import static org.junit.jupiter.api.Assertions.*;

import java.util.Arrays;
import org.json.JSONObject;
import org.junit.jupiter.api.Test;

import simulator.misc.Pair;
import simulator.model.MoveFirstStrategy;
import simulator.model.NewCityRoadEvent;
import simulator.model.NewJunctionEvent;
import simulator.model.NewVehicleEvent;
import simulator.model.RoundRobinStrategy;
import simulator.model.SetWeatherEvent;
import simulator.model.TrafficSimulator;
import simulator.model.Weather;

class TrafficSimulatorTest {

	@Test
	void test_1() {
		TrafficSimulator ts = new TrafficSimulator();
		
		ts.addEvent(new NewJunctionEvent(1,"j1", new RoundRobinStrategy(10), new MoveFirstStrategy(), 0, 0));
		ts.addEvent(new NewJunctionEvent(1,"j2", new RoundRobinStrategy(10), new MoveFirstStrategy(), 0, 0));
		ts.addEvent(new NewJunctionEvent(1,"j3", new RoundRobinStrategy(10), new MoveFirstStrategy(), 0, 0));
		ts.addEvent(new NewCityRoadEvent(1, "r1", "j1", "j2", 1000, 500, 100, Weather.SUNNY));
		ts.addEvent(new NewCityRoadEvent(1, "r2", "j2", "j3", 1000, 500, 100, Weather.SUNNY));
		ts.addEvent(new NewVehicleEvent(1,"v1", 50, 1, Arrays.asList("j1", "j2")));
		ts.addEvent(new NewVehicleEvent(1,"v2", 50, 1, Arrays.asList("j1", "j2")));
		ts.addEvent(new NewVehicleEvent(1,"v3", 50, 1, Arrays.asList("j1", "j2")));

		ts.addEvent(new SetWeatherEvent(3,Arrays.asList(new Pair<>("r1",Weather.CLOUDY),new Pair<>("r2",Weather.RAINY))));
		ts.addEvent( new NewSetContClassEvent(5, Arrays.asList(new Pair<>("v1",4),new Pair<>("v3",7))));

		
		ts.advance();
		String s = "{\"time\":1,\"state\":{\"roads\":[{\"speedlimit\":100,\"co2\":150,\"weather\":\"SUNNY\",\"vehicles\":[\"v1\",\"v2\",\"v3\"],\"id\":\"r1\"},{\"speedlimit\":100,\"co2\":0,\"weather\":\"SUNNY\",\"vehicles\":[],\"id\":\"r2\"}],\"vehicles\":[{\"distance\":50,\"road\":\"r1\",\"co2\":50,\"location\":50,\"id\":\"v1\",\"class\":1,\"speed\":50,\"status\":\"TRAVELING\"},{\"distance\":50,\"road\":\"r1\",\"co2\":50,\"location\":50,\"id\":\"v2\",\"class\":1,\"speed\":50,\"status\":\"TRAVELING\"},{\"distance\":50,\"road\":\"r1\",\"co2\":50,\"location\":50,\"id\":\"v3\",\"class\":1,\"speed\":50,\"status\":\"TRAVELING\"}],\"junctions\":[{\"green\":\"none\",\"queues\":[],\"id\":\"j1\"},{\"green\":\"r1\",\"queues\":[{\"road\":\"r1\",\"vehicles\":[]}],\"id\":\"j2\"},{\"green\":\"r2\",\"queues\":[{\"road\":\"r2\",\"vehicles\":[]}],\"id\":\"j3\"}]}}";
		System.out.println(s);
		System.out.println(ts.report());
		assertTrue(new JSONObject(s).similar(ts.report()));

		ts.advance();
		ts.advance();
		
		s = "{\"time\":3,\"state\":{\"roads\":[{\"speedlimit\":100,\"co2\":446,\"weather\":\"CLOUDY\",\"vehicles\":[\"v1\",\"v2\",\"v3\"],\"id\":\"r1\"},{\"speedlimit\":100,\"co2\":0,\"weather\":\"RAINY\",\"vehicles\":[],\"id\":\"r2\"}],\"vehicles\":[{\"distance\":150,\"road\":\"r1\",\"co2\":150,\"location\":150,\"id\":\"v1\",\"class\":1,\"speed\":50,\"status\":\"TRAVELING\"},{\"distance\":150,\"road\":\"r1\",\"co2\":150,\"location\":150,\"id\":\"v2\",\"class\":1,\"speed\":50,\"status\":\"TRAVELING\"},{\"distance\":150,\"road\":\"r1\",\"co2\":150,\"location\":150,\"id\":\"v3\",\"class\":1,\"speed\":50,\"status\":\"TRAVELING\"}],\"junctions\":[{\"green\":\"none\",\"queues\":[],\"id\":\"j1\"},{\"green\":\"r1\",\"queues\":[{\"road\":\"r1\",\"vehicles\":[]}],\"id\":\"j2\"},{\"green\":\"r2\",\"queues\":[{\"road\":\"r2\",\"vehicles\":[]}],\"id\":\"j3\"}]}}";
		assertTrue(new JSONObject(s).similar(ts.report()));

		ts.advance();
		ts.advance();

		s = "{\"time\":5,\"state\":{\"roads\":[{\"speedlimit\":100,\"co2\":1094,\"weather\":\"CLOUDY\",\"vehicles\":[\"v1\",\"v2\",\"v3\"],\"id\":\"r1\"},{\"speedlimit\":100,\"co2\":0,\"weather\":\"RAINY\",\"vehicles\":[],\"id\":\"r2\"}],\"vehicles\":[{\"distance\":250,\"road\":\"r1\",\"co2\":400,\"location\":250,\"id\":\"v1\",\"class\":4,\"speed\":50,\"status\":\"TRAVELING\"},{\"distance\":250,\"road\":\"r1\",\"co2\":250,\"location\":250,\"id\":\"v2\",\"class\":1,\"speed\":50,\"status\":\"TRAVELING\"},{\"distance\":236,\"road\":\"r1\",\"co2\":452,\"location\":236,\"id\":\"v3\",\"class\":7,\"speed\":36,\"status\":\"TRAVELING\"}],\"junctions\":[{\"green\":\"none\",\"queues\":[],\"id\":\"j1\"},{\"green\":\"r1\",\"queues\":[{\"road\":\"r1\",\"vehicles\":[]}],\"id\":\"j2\"},{\"green\":\"r2\",\"queues\":[{\"road\":\"r2\",\"vehicles\":[]}],\"id\":\"j3\"}]}}";
		assertTrue(new JSONObject(s).similar(ts.report()));

	}
}
