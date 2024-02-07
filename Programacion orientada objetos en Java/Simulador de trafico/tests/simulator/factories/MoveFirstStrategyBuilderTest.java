package simulator.factories;

import static org.junit.jupiter.api.Assertions.*;

import org.json.JSONObject;
import org.junit.jupiter.api.Test;

import simulator.factories.MoveFirstStrategyBuilder;
import simulator.model.DequeuingStrategy;
import simulator.model.MoveFirstStrategy;

class MoveFirstStrategyBuilderTest {

	@Test
	void test_1() {
		MoveFirstStrategyBuilder eb = new MoveFirstStrategyBuilder();
		
		String inputJSon = " { \"type\" : \"move_first_dqs\",  \"data\" : {} }";
		DequeuingStrategy o = eb.createInstance(new JSONObject(inputJSon));
		assertTrue( o instanceof MoveFirstStrategy );
		
	}

	@Test
	void test_2() {
		MoveFirstStrategyBuilder eb = new MoveFirstStrategyBuilder();
		
		String inputJSon = " { \"type\" : \"move_first_dqs\" }";
		DequeuingStrategy o = eb.createInstance(new JSONObject(inputJSon));
		assertTrue( o instanceof MoveFirstStrategy );
		
	}

}
