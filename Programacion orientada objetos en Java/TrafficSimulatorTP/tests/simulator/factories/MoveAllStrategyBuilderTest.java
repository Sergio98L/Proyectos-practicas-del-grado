package simulator.factories;

import static org.junit.jupiter.api.Assertions.*;

import org.json.JSONObject;
import org.junit.jupiter.api.Test;

import simulator.factories.MoveAllStrategyBuilder;
import simulator.model.DequeuingStrategy;
import simulator.model.MoveAllStrategy;

class MoveAllStrategyBuilderTest {

	@Test
	void test_1() {
		MoveAllStrategyBuilder eb = new MoveAllStrategyBuilder();
		
		String inputJSon = " { \"type\" : \"move_all_dqs\",  \"data\" : {} }";
		DequeuingStrategy o = eb.createInstance(new JSONObject(inputJSon));
		assertTrue( o instanceof MoveAllStrategy );
		
	}

	@Test
	void test_2() {
		MoveAllStrategyBuilder eb = new MoveAllStrategyBuilder();
		
		String inputJSon = " { \"type\" : \"move_all_dqs\" }";
		DequeuingStrategy o = eb.createInstance(new JSONObject(inputJSon));
		assertTrue( o instanceof MoveAllStrategy );
		
	}

}
