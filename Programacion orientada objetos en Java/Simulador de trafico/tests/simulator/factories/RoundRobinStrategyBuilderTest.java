package simulator.factories;

import static org.junit.jupiter.api.Assertions.*;

import org.json.JSONObject;
import org.junit.jupiter.api.Test;

import simulator.factories.RoundRobinStrategyBuilder;
import simulator.model.LightSwitchingStrategy;
import simulator.model.RoundRobinStrategy;

class RoundRobinStrategyBuilderTest {

	@Test
	void test_1() {
		RoundRobinStrategyBuilder eb = new RoundRobinStrategyBuilder();
		
		String inputJSon = "{ \"type\" : \"round_robin_lss\", \"data\" : {\"timeslot\" : 5} }";
		LightSwitchingStrategy o = eb.createInstance(new JSONObject(inputJSon));
		assertTrue( o instanceof RoundRobinStrategy );
		
	}

	@Test
	void test_2() {
		RoundRobinStrategyBuilder eb = new RoundRobinStrategyBuilder();
		
		String inputJSon = "{ \"type\" : \"round_robin_lss\", \"data\" : {} }";
		LightSwitchingStrategy o = eb.createInstance(new JSONObject(inputJSon));
		assertTrue( o instanceof RoundRobinStrategy );
		
	}

	@Test
	void test_4() {
		RoundRobinStrategyBuilder eb = new RoundRobinStrategyBuilder();
		
		String inputJSon = "{ \"type\" : \"round_robin_lss\" }";
		LightSwitchingStrategy o = eb.createInstance(new JSONObject(inputJSon));
		assertTrue( o instanceof RoundRobinStrategy );
		
	}


}
