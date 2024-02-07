package simulator.factories;

import static org.junit.Assert.assertTrue;
import static org.junit.jupiter.api.Assertions.*;

import java.util.ArrayList;

import org.json.JSONObject;
import org.junit.jupiter.api.Test;

import simulator.factories.Builder;
import simulator.factories.BuilderBasedFactory;
import simulator.factories.Factory;
import simulator.factories.MostCrowdedStrategyBuilder;
import simulator.factories.MoveAllStrategyBuilder;
import simulator.factories.MoveFirstStrategyBuilder;
import simulator.factories.NewCityRoadEventBuilder;
import simulator.factories.NewJunctionEventBuilder;
import simulator.factories.RoundRobinStrategyBuilder;
import simulator.model.DequeuingStrategy;
import simulator.model.LightSwitchingStrategy;
import simulator.model.TrafficSimulator;

class NewCityRoadEventBuilderTest {

	static private TrafficSimulator createSim() {
		TrafficSimulator ts = new TrafficSimulator();

		ArrayList<Builder<LightSwitchingStrategy>> lsbs = new ArrayList<>();
		lsbs.add(new RoundRobinStrategyBuilder());
		lsbs.add(new MostCrowdedStrategyBuilder());
		Factory<LightSwitchingStrategy> lssFactory = new BuilderBasedFactory<>(lsbs);

		ArrayList<Builder<DequeuingStrategy>> dqbs = new ArrayList<>();
		dqbs.add(new MoveFirstStrategyBuilder());
		dqbs.add(new MoveAllStrategyBuilder());
		Factory<DequeuingStrategy> dqsFactory = new BuilderBasedFactory<>(dqbs);

		String inputJson1 = "{\n" + "     \"type\" : \"new_junction\",\n" + "     \"data\" : {\n"
				+ "     	 \"time\" : 1,\n" + "         \"id\"   : \"j1\",\n" + "      	 \"coor\" : [100,200],\n"
				+ "      	 \"ls_strategy\" : { \"type\" : \"round_robin_lss\", \"data\" : {\"timeslot\" : 5} },\n"
				+ "      	 \"dq_strategy\" : { \"type\" : \"move_first_dqs\",  \"data\" : {} }\n" + "   	 }}";

		String inputJson2 = "{\n" + "     \"type\" : \"new_junction\",\n" + "     \"data\" : {\n"
				+ "     	 \"time\" : 1,\n" + "         \"id\"   : \"j2\",\n" + "      	 \"coor\" : [100,200],\n"
				+ "      	 \"ls_strategy\" : { \"type\" : \"round_robin_lss\", \"data\" : {\"timeslot\" : 5} },\n"
				+ "      	 \"dq_strategy\" : { \"type\" : \"move_first_dqs\",  \"data\" : {} }\n" + "   	 }}";

		NewJunctionEventBuilder jeb = new NewJunctionEventBuilder(lssFactory, dqsFactory);
		ts.addEvent(jeb.createInstance(new JSONObject(inputJson1)));
		ts.addEvent(jeb.createInstance(new JSONObject(inputJson2)));

		return ts;

	}

	@Test
	void test_1() {
		TrafficSimulator ts = createSim();

		String inputJson = "{\n" + "	  \"type\" : \"new_city_road\",\n" + "  	  \"data\" : {\n"
				+ "    	  \"time\"     : 1,\n" + "    	   \"id\"       : \"r1\",\n"
				+ "           \"src\"      : \"j1\",\n" + "           \"dest\"     : \"j2\",\n"
				+ "           \"length\"   : 10000,\n" + "           \"co2limit\" : 500,\n"
				+ "           \"maxspeed\" : 120,\n" + "           \"weather\"  : \"SUNNY\"\n" + "   	  }\n"
				+ "   	}";

		NewCityRoadEventBuilder reb = new NewCityRoadEventBuilder();
		ts.addEvent(reb.createInstance(new JSONObject(inputJson)));

		ts.advance();

		String s = "{\"time\":1,\"state\":{\"roads\":[{\"speedlimit\":120,\"co2\":0,\"weather\":\"SUNNY\",\"vehicles\":[],\"id\":\"r1\"}],\"vehicles\":[],\"junctions\":[{\"green\":\"none\",\"queues\":[],\"id\":\"j1\"},{\"green\":\"r1\",\"queues\":[{\"road\":\"r1\",\"vehicles\":[]}],\"id\":\"j2\"}]}}";

		assertTrue(new JSONObject(s).similar(ts.report()));

	}

	@Test
	void test_2() {

		// error in src junction
		String inputJson = "{\n" + "	  \"type\" : \"new_city_road\",\n" + "  	  \"data\" : {\n"
				+ "    	  \"time\"     : 1,\n" + "    	   \"id\"       : \"r1\",\n"
				+ "           \"src\"      : 99999,\n" + "           \"dest\"     : \"j2\",\n"
				+ "           \"length\"   : 10000,\n" + "           \"co2limit\" : 500,\n"
				+ "           \"maxspeed\" : 120,\n" + "           \"weather\"  : \"SUNNY\"\n" + "   	  }\n"
				+ "   	}";

		NewCityRoadEventBuilder reb = new NewCityRoadEventBuilder();
		assertThrows(Exception.class, () -> reb.createInstance(new JSONObject(inputJson)));

	}

	@Test
	void test_3() {
		// if no type an exception is thrown (by getString("type"))
		String inputJson = "{ }";

		NewCityRoadEventBuilder reb = new NewCityRoadEventBuilder();
		assertThrows(Exception.class, () -> reb.createInstance(new JSONObject(inputJson)));

	}
	@Test
	void test_4() {

		// if type is not new_city_road it returns null
		String inputJson = "{ \"type\" : \"bla\" }";

		NewCityRoadEventBuilder reb = new NewCityRoadEventBuilder();
		assertNull(reb.createInstance(new JSONObject(inputJson)));

	}

}
