package simulator.model;

import java.util.ArrayList;
import java.util.List;

import org.json.JSONObject;

import simulator.misc.SortedArrayList;

public class TrafficSimulator implements Observable <TrafficSimObserver>{
	
	//TODO: A�adir onError cuando se metan las excepciones
	
	private RoadMap map;
	
	private List<Event> listaEventos;
	
	private int time;
	
	private List<TrafficSimObserver> listaObservadores;
	
	public TrafficSimulator() {
		
		map = new RoadMap();
		listaEventos = new SortedArrayList<Event>(); 
		listaObservadores = new ArrayList<TrafficSimObserver>();
		time = 0;
	}
	
	public void addEvent(Event e) {
		listaEventos.add(e);
		for(TrafficSimObserver o:listaObservadores) {
			o.onEventAdded(map, listaEventos, e, time);
		}
	}
	
	public void advance() {
		time++;
		
		for(TrafficSimObserver o:listaObservadores) {
			o.onAdvanceStart(map, listaEventos, time);
		}
		
		try {
			List<Event> aux = new ArrayList<Event>();
			
			for(Event e : listaEventos) {
				if(e.getTime() == time) {
					e.execute(map);
					aux.add(e);			
				}
			}	
			listaEventos.removeAll(aux);
			
			for(Junction j : map.getJunctions()) {
				j.advance(time);
			}
			for(Road r : map.getRoads()) {
				r.advance(time);
			}
		}catch(Exception e) {
			for (TrafficSimObserver o : listaObservadores)
			{
				o.onError(e.getMessage());
			}
			
		}			
		for(TrafficSimObserver o:listaObservadores) {
			o.onAdvanceEnd(map, listaEventos, time);
		}		
	}
	
	public void reset() {
		map.reset();
		listaEventos.clear();
		time = 0;
		for(TrafficSimObserver o:listaObservadores) {
			o.onReset(map, listaEventos, time);
		}
	}
	
	public JSONObject report() {
		
		JSONObject jo = new JSONObject();
		
		jo.put("time", time);
		jo.put("state", map.report());
		return jo;
		
	}

	@Override
	public void addObserver(TrafficSimObserver o) {
		if(!listaObservadores.contains(o)) {
			this.listaObservadores.add(o);
		}
		o.onRegister(map, listaEventos, time);
		
	}

	@Override
	public void removeObserver(TrafficSimObserver o) {	
		if(listaObservadores.contains(o)) {
			this.listaObservadores.remove(o);
		}
	}
	public RoadMap getRoadMap() {
		return this.map;
	}
}
