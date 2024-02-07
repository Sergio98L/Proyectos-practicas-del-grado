package simulator.factories;

import static org.junit.jupiter.api.Assertions.*;

import org.json.JSONObject;
import org.junit.jupiter.api.Test;

import simulator.factories.MostCrowdedStrategyBuilder;
import simulator.model.LightSwitchingStrategy;
import simulator.model.MostCrowdedStrategy;

class MostCrowdedStrategyBuilderTest {

	@Test
	void test_1() {
		MostCrowdedStrategyBuilder eb = new MostCrowdedStrategyBuilder();
		
		String inputJSon = "{ \"type\" : \"most_crowded_lss\", \"data\" : {\"timeslot\" : 5} }";
		LightSwitchingStrategy o = eb.createInstance(new JSONObject(inputJSon));
		assertTrue( o instanceof MostCrowdedStrategy );
		
	}

	@Test
	void test_2() {
		MostCrowdedStrategyBuilder eb = new MostCrowdedStrategyBuilder();
		
		String inputJSon = "{ \"type\" : \"most_crowded_lss\", \"data\" : {} }";
		LightSwitchingStrategy o = eb.createInstance(new JSONObject(inputJSon));
		assertTrue( o instanceof MostCrowdedStrategy );
		
	}

	@Test
	void test_4() {
		MostCrowdedStrategyBuilder eb = new MostCrowdedStrategyBuilder();
		
		String inputJSon = "{ \"type\" : \"most_crowded_lss\" }";
		LightSwitchingStrategy o = eb.createInstance(new JSONObject(inputJSon));
		assertTrue( o instanceof MostCrowdedStrategy );
		
	}


}
