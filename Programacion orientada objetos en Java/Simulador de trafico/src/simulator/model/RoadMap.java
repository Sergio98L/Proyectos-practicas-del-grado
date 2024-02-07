package simulator.model;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.json.JSONArray;
import org.json.JSONObject;

public class RoadMap {
	
	private List<Junction> lJunctions;
	
	private List<Road> lRoads;
	
	private List<Vehicle> lVehicles;
	
	private Map<String, Junction> IdJunctionMap;

	private Map<String, Road> idRoadMap;
	
	private Map<String,Vehicle> idVehicleMap;
	
	public RoadMap() {
		lJunctions = new ArrayList<Junction>();
		lRoads = new ArrayList<Road>();
		lVehicles = new ArrayList<Vehicle>();
		IdJunctionMap = new HashMap<String, Junction>();
		idRoadMap = new HashMap<String, Road>();
		idVehicleMap = new HashMap<String, Vehicle>();
	}
	
	void addJunction(Junction j) {
		if(getJunction(j.getId()) == null) {
			lJunctions.add(j);
			IdJunctionMap.put(j.getId(), j);
		}else {
			throw new IllegalArgumentException("error al aniadir cruce ya que ya existe");
		}
	}
	
	void addRoad(Road r) {
		
		if(getRoad(r.getId()) == null) {
			if(IdJunctionMap.containsKey(r.getSrc().getId()) && IdJunctionMap.containsKey(r.getDest().getId())) {
				lRoads.add(r);
				idRoadMap.put(r.getId(), r);
			}
			else {
				throw new IllegalArgumentException("error al aniadir carretera");
			}
		}
		else {
			throw new IllegalArgumentException("error al aniadir carretera ya que ya existe");
		}
	}
	
	void addVehicle(Vehicle v) {
		Boolean a = false;
		for(int i = 1; i < v.getItinerary().size();i++) {
			for(int j = 0; j < lRoads.size();j++) {

				if(lRoads.get(j).getSrc() == v.getItinerary().get(i-1) && lRoads.get(j).getDest() == v.getItinerary().get(i)) {
					a = true;
				}
			}
		}
		if(getVehicle(v.getId()) == null) {
			if(a == true) {
				lVehicles.add(v);
				idVehicleMap.put(v.getId(), v);
			}else {
				throw new IllegalArgumentException("error al aniadir vehiculo");
			}
		}
		else {
			throw new IllegalArgumentException("error al aniadir vehiculo ya que ya existe");
		}
	}
	
	public Junction getJunction(String id) {
		return IdJunctionMap.get(id);
	}
	
	public Road getRoad(String id) {

		return idRoadMap.get(id);
	}
	
	public Vehicle getVehicle(String id) {

		return idVehicleMap.get(id);
	}
	public List<Junction> getJunctions(){
		return lJunctions;
	}
	public List<Road> getRoads(){
		return lRoads;
	}
	public List<Vehicle> getVehicles(){
		return lVehicles;
	}
	
	//limpia todas las listas y mapas.
	void reset() {		
		lJunctions.clear();
		lRoads.clear();
		lVehicles.clear();
		IdJunctionMap.clear();
		idRoadMap.clear();
		idVehicleMap.clear();
	}
	
	public JSONObject report() {
		JSONObject jo1 = new JSONObject();
		
		JSONArray joj = new JSONArray();
		

		for(int i = 0; i < lJunctions.size(); i++) {
			joj.put(lJunctions.get(i).report());
		}
		jo1.put("junctions", joj);
		
		JSONArray jor = new JSONArray();
		
		for(int i = 0; i < lRoads.size(); i++) {
			jor.put(lRoads.get(i).report());
		}
		jo1.put("roads", jor);
		
		JSONArray jov = new JSONArray();
	
		for(int i = 0; i < lVehicles.size(); i++) {
			jov.put(lVehicles.get(i).report());
		}
		jo1.put("vehicles", jov);
		return jo1;
	}


	
}
