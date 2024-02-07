package simulator.factories;

import static org.junit.Assert.assertTrue;
import static org.junit.jupiter.api.Assertions.assertNull;
import static org.junit.jupiter.api.Assertions.assertThrows;

import java.util.ArrayList;

import org.json.JSONObject;
import org.junit.jupiter.api.Test;

import simulator.factories.Builder;
import simulator.factories.BuilderBasedFactory;
import simulator.factories.Factory;
import simulator.factories.MostCrowdedStrategyBuilder;
import simulator.factories.MoveAllStrategyBuilder;
import simulator.factories.MoveFirstStrategyBuilder;
import simulator.factories.NewJunctionEventBuilder;
import simulator.factories.RoundRobinStrategyBuilder;
import simulator.model.DequeuingStrategy;
import simulator.model.Event;
import simulator.model.LightSwitchingStrategy;
import simulator.model.TrafficSimulator;

class NewJunctionEventBuilderTest {

	@Test
	void test_1() {

		TrafficSimulator ts = new TrafficSimulator();

		ArrayList<Builder<LightSwitchingStrategy>> lsbs = new ArrayList<>();
		lsbs.add(new RoundRobinStrategyBuilder());
		lsbs.add(new MostCrowdedStrategyBuilder());
		Factory<LightSwitchingStrategy> lssFactory = new BuilderBasedFactory<>(lsbs);

		ArrayList<Builder<DequeuingStrategy>> dqbs = new ArrayList<>();
		dqbs.add(new MoveFirstStrategyBuilder());
		dqbs.add(new MoveAllStrategyBuilder());
		Factory<DequeuingStrategy> dqsFactory = new BuilderBasedFactory<>(dqbs);

		String inputJson = "{\n" + "     \"type\" : \"new_junction\",\n" + "     \"data\" : {\n"
				+ "     	 \"time\" : 1,\n" + "         \"id\"   : \"j1\",\n" + "      	 \"coor\" : [100,200],\n"
				+ "      	 \"ls_strategy\" : { \"type\" : \"round_robin_lss\", \"data\" : {\"timeslot\" : 5} },\n"
				+ "      	 \"dq_strategy\" : { \"type\" : \"move_first_dqs\",  \"data\" : {} }\n" + "   	 }}";

		NewJunctionEventBuilder eb = new NewJunctionEventBuilder(lssFactory, dqsFactory);
		Event e = eb.createInstance(new JSONObject(inputJson));

		ts.addEvent(e);

		ts.advance();

		String s = "{\"time\":1,\"state\":{\"roads\":[],\"vehicles\":[],\"junctions\":[{\"green\":\"none\",\"queues\":[],\"id\":\"j1\"}]}}";

		assertTrue(new JSONObject(s).similar(ts.report()));

	}

	@Test
	void test_2() {

		ArrayList<Builder<LightSwitchingStrategy>> lsbs = new ArrayList<>();
		lsbs.add(new RoundRobinStrategyBuilder());
		lsbs.add(new MostCrowdedStrategyBuilder());
		Factory<LightSwitchingStrategy> lssFactory = new BuilderBasedFactory<>(lsbs);

		ArrayList<Builder<DequeuingStrategy>> dqbs = new ArrayList<>();
		dqbs.add(new MoveFirstStrategyBuilder());
		dqbs.add(new MoveAllStrategyBuilder());
		Factory<DequeuingStrategy> dqsFactory = new BuilderBasedFactory<>(dqbs);

		// error in id
		String inputJson = "{\n" + "     \"type\" : \"new_junction\",\n" + "     \"data\" : {\n"
				+ "     	 \"time\" : 1,\n" + "         \"id\"   : 44,\n" + "      	 \"coor\" : [100,200],\n"
				+ "      	 \"ls_strategy\" : { \"type\" : \"round_robin_lss\", \"data\" : {\"timeslot\" : 5} },\n"
				+ "      	 \"dq_strategy\" : { \"type\" : \"move_first_dqs\",  \"data\" : {} }\n" + "   	 }}";

		NewJunctionEventBuilder eb = new NewJunctionEventBuilder(lssFactory, dqsFactory);
		assertThrows(Exception.class, () -> eb.createInstance(new JSONObject(inputJson)));
	}

	@Test
	void test_3() {

		ArrayList<Builder<LightSwitchingStrategy>> lsbs = new ArrayList<>();
		lsbs.add(new RoundRobinStrategyBuilder());
		lsbs.add(new MostCrowdedStrategyBuilder());
		Factory<LightSwitchingStrategy> lssFactory = new BuilderBasedFactory<>(lsbs);

		ArrayList<Builder<DequeuingStrategy>> dqbs = new ArrayList<>();
		dqbs.add(new MoveFirstStrategyBuilder());
		dqbs.add(new MoveAllStrategyBuilder());
		Factory<DequeuingStrategy> dqsFactory = new BuilderBasedFactory<>(dqbs);

		// if there is no type field, it should throw an exception (it should be done
		// automatically by the json library when looking for such field)
		String inputJson = "{}";

		NewJunctionEventBuilder eb = new NewJunctionEventBuilder(lssFactory, dqsFactory);
		assertThrows(Exception.class, () -> eb.createInstance(new JSONObject(inputJson)));
	}

	@Test
	void test_4() {

		ArrayList<Builder<LightSwitchingStrategy>> lsbs = new ArrayList<>();
		lsbs.add(new RoundRobinStrategyBuilder());
		lsbs.add(new MostCrowdedStrategyBuilder());
		Factory<LightSwitchingStrategy> lssFactory = new BuilderBasedFactory<>(lsbs);

		ArrayList<Builder<DequeuingStrategy>> dqbs = new ArrayList<>();
		dqbs.add(new MoveFirstStrategyBuilder());
		dqbs.add(new MoveAllStrategyBuilder());
		Factory<DequeuingStrategy> dqsFactory = new BuilderBasedFactory<>(dqbs);

		// if the type is no new_junction, it should return null
		String inputJson = "{ \"type\" : \"bla\"}";

		NewJunctionEventBuilder eb = new NewJunctionEventBuilder(lssFactory, dqsFactory);
		assertNull(eb.createInstance(new JSONObject(inputJson)));
	}

}
