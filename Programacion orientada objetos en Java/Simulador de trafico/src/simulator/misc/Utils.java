package simulator.misc;

import java.util.ArrayList;
import java.util.List;

public class Utils {
	static public <T> List<T> arrayToList(T a[]) {
		List<T> c = new ArrayList<>();
		for (T x : a) {
			c.add(x);
		}
		return c;
	}

}
