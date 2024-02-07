package simulator.model;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;

import org.json.JSONArray;
import org.json.JSONObject;

public class Junction extends SimulatedObject {
	
	private List<Road> roads; //lista de carreteras que salen de un cruce (lista de carreteras entrantes)
	
	private Map<Junction,Road> juncConnection; //lista que dice a que cruce llegas por una carretera (map de carretras salientes)
	
	private List<List<Vehicle>> qs; //las clases entrantes se ponen en cola
	//pone que guardemos un road map para hacer la busqueda en la cola de manera eficiente
	
	private Map<Road,List<Vehicle>> mapCarreteraCola; //es el map que recomienda el enunciado 
													// que hagamos para buscar de forma eficiente
	
	private int currGreen; //indice de la carretera ENTRANTE que tiene el semaforo en verde
	
	private int lastSwitchingTime; //cambia el indice del semaforo en verde
	
	private LightSwitchingStrategy lsStrategy;
	
	private DequeuingStrategy dqStrategy; //elimina los vehiculos de la cola
	
	private int xCoor;
	
	private int yCoor;
	
	
	Junction(String id, LightSwitchingStrategy lsStrategy, DequeuingStrategy dqStrategy,
		int xCoor, int yCoor) {
		super(id);
		this.xCoor = xCoor;
		this.yCoor = yCoor;
		this.lsStrategy = lsStrategy;
		this.dqStrategy = dqStrategy;
		roads = new ArrayList<Road>();
		juncConnection = new HashMap<Junction, Road>();
		qs = new ArrayList<List<Vehicle>>();
		mapCarreteraCola = new HashMap<Road, List<Vehicle>>();
		currGreen = -1;
		
		if(lsStrategy == null) {
			throw new IllegalArgumentException("lsStrategy es null");
		}
		else if(dqStrategy == null) {
			throw new IllegalArgumentException("dqStrategy es null");
		}
		else if(xCoor < 0) {
			throw new IllegalArgumentException("xCoor mayor que 0");
		}
		else if(yCoor < 0) {
			throw new IllegalArgumentException("yCoor mayor que 0");
		}
	}

	void addIncommingRoad(Road r) {
		
		if(this != r.getDest()) {
			throw new IllegalArgumentException("este cruce no coincide con el cruce destino de la road add in");
		}
		else {
		
			roads.add(r);
			
			List<Vehicle> queue = new LinkedList<Vehicle>();
			
			qs.add(queue);
			
			mapCarreteraCola.put(r, queue);
		}
	}
	
	void addOutGoingRoad(Road r) {
		if(this.roadTo(r.getDest()) != null) {
			throw new IllegalArgumentException("hay mas carreteras que conectan este cruce con otro");
		}
		else if(this != r.getSrc()) { //comprueba que la carretera realmente es una carretera saliente
			throw new IllegalArgumentException("este cruce no coincide con el cruce destino de la road addout");
		}else {
			juncConnection.put(r.getDest(),r);
		}
	}
	
	void enter(Vehicle v) {
		qs.get(roads.indexOf(v.getRoad())).add(v);
	} 
	
	Road roadTo(Junction j) {
		return juncConnection.get(j);
	}
	
	@Override
	void advance(int time) {
				
		// 1) estrategia de dequeue
		if(currGreen != -1) {
			List<Vehicle> aux = new ArrayList<Vehicle>();
			aux = dqStrategy.dequeue(mapCarreteraCola.get(roads.get(currGreen)));	
			for(Vehicle v : aux) {
				v.moveToNextRoad();
			}
			mapCarreteraCola.get(roads.get(currGreen)).removeAll(aux);
		}

		// 2) estrategia de cambio de semaforo
		
		int oldGreen = 0;		

		oldGreen = currGreen;
		//cambia el semaforo
		currGreen = lsStrategy.chooseNextGreen(roads, qs, currGreen, lastSwitchingTime, time);
		
		if(currGreen != oldGreen) {
			lastSwitchingTime = time;
		}
	}



	@Override
	public JSONObject report() {

		JSONArray ja = new JSONArray();
		
		for(int i = 0; i < qs.size(); i++) {
			JSONArray jaVehicles = new JSONArray();
			for(Vehicle aux: qs.get(i)) {
				jaVehicles.put(aux.getId());
			}
			
			JSONObject jo2 = new JSONObject();
			
			jo2.put("road", roads.get(i).getId());
			jo2.put("vehicles", jaVehicles);
			
			ja.put(jo2);
		}

		JSONObject jo = new JSONObject();
		
		jo.put("id", getId());
		if(currGreen == -1) {
			jo.put("green", "none");			
		}
		else {
			jo.put("green", roads.get(currGreen).getId());
		}
		jo.put("queues", ja);
		
		
		return jo;
	}

	public int getX() {
		return xCoor;
	}

	public int getY() {
		return yCoor;
	}

	public int getGreenLightIndex() {
		return currGreen;
	}

	public List<Road> getInRoads() {
		// TODO Auto-generated method stub
		return roads;
	}
	public List<Vehicle> getQueue(Road r){
		return mapCarreteraCola.get(r);
		
	}
	
		
}
