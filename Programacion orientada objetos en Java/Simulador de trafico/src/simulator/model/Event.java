package simulator.model;

public abstract class Event implements Comparable<Event> {

	protected int _time;

	Event(int time) {
		if (time < 1)
			throw new IllegalArgumentException("Time must be positive (" + time + ")");
		else
			_time = time;
	}

	public int getTime() {
		return _time;
	}

	@Override
	public int compareTo(Event o) {
		int ret;
		if(this.getTime() < o.getTime()) {
			ret = -1;
		}else if(this.getTime() > o.getTime()) {
			ret = 1;
		}else{
			ret = 0;
		}
		return ret;
	}

	abstract void execute(RoadMap map);
}
