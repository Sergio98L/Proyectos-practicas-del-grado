package simulator.control;

import java.io.InputStream;
import java.io.OutputStream;
import java.io.PrintStream;

import org.json.JSONArray;
import org.json.JSONObject;
import org.json.JSONTokener;


import simulator.factories.Factory;
import simulator.model.Event;
import simulator.model.Observable;
import simulator.model.TrafficSimObserver;
import simulator.model.TrafficSimulator;

public class Controller implements Observable<TrafficSimObserver>{
	
	private TrafficSimulator traffic_sim;
	private Factory<Event> events_fact;
	
	public Controller(TrafficSimulator sim, Factory<Event> eventsFactory)	{
	
		if (sim == null) {
			throw new IllegalArgumentException("Traffic simulator no puede estar vacio.");
		}
		if (eventsFactory == null) {
			throw new IllegalArgumentException("EventsFactory no puede estar vacio.");
		}
	
		this.traffic_sim = sim;
		this.events_fact = eventsFactory;
	}
	
	public void loadEvents(InputStream in) {
		
		JSONObject jo1 = new JSONObject(new JSONTokener(in));
		JSONArray aux = jo1.getJSONArray("events");
		
		if (!jo1.has("events"))
		{
			throw new IllegalArgumentException("La entrada JSON no es correcta");
		}
		
		for (int i = 0; i < aux.length(); i++)
		{
			traffic_sim.addEvent(events_fact.createInstance(aux.getJSONObject(i)));
		}
	}
	
	public void run(int n, OutputStream out) throws InterruptedException{
		
		if(out != null)
		{
			JSONObject salida = new JSONObject();
			JSONArray array = new JSONArray();
			
			for (int i = 0; i < n; i++) 
			{
				traffic_sim.advance();
				array.put(traffic_sim.report());
			}
			
			salida.put("states", array);		
			PrintStream p = new PrintStream(out);
			p.println(salida.toString());
		}
		else
		{
			for (int i = 0; i < n; i++) 
			{
				traffic_sim.advance();
				Thread.sleep(30);
			}
		}
	}
	
	
	public void reset() {
		traffic_sim.reset();
	}
	public void addObserver(TrafficSimObserver o){
		this.traffic_sim.addObserver(o);
	}
	public void removeObserver(TrafficSimObserver o) {
		this.traffic_sim.removeObserver(o);
	}
	public void addEvent(Event e) {
		this.traffic_sim.addEvent(e);
	}
	//public TrafficSimulator getTrafficSM() {
	///	return this.traffic_sim;
	//}
}
