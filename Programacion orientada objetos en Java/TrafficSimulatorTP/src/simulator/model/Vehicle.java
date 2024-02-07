package simulator.model;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

import org.json.JSONObject;

public class Vehicle extends SimulatedObject {
	
	private int speed;
	
	private int maxSpeed;
	
	private List<Junction> itinerary;
	
	private List<Junction> copiaItinerary;
	
	private VehicleStatus status;
	
	private Road road;
	
	private int location;
	
	private int distance;
	
	private int contClass;
	
	private int totalCO2;
	
	private int indiceItinerary;
	
	Vehicle(String id, int maxSpeed, int contClass, List<Junction> itinerary) throws IllegalArgumentException{
		super(id);
		this.maxSpeed = maxSpeed;
		this.contClass = contClass;
		this.itinerary = itinerary;
		indiceItinerary = 0;
		speed = 0;
		status = VehicleStatus.PENDING;
		this.contClass = contClass;
		location = 0;
		totalCO2 = 0;
		distance = 0;
		
		
		if(maxSpeed <= 0) {
			throw new IllegalArgumentException("maxSpeed es menor que 0");
		}
		else if(contClass < 0 || contClass > 10){
			throw new IllegalArgumentException("contClass mayor que 0 o menor que 10");
		}
		else if(itinerary.size() < 2) {
			throw new IllegalArgumentException("itinerary array size menor que 2");
		}

		
		copiaItinerary = Collections.unmodifiableList(new ArrayList<>(itinerary));
	}

	void setSpeed(int s) throws IllegalArgumentException{
		if(status == VehicleStatus.TRAVELING) {
			if(s < 0) {
				throw new IllegalArgumentException("setSpeed menor que 0");
			}
			else if(s > maxSpeed) {
				this.speed = maxSpeed;
			}
			else {
				this.speed = s;
			}
		}
		else {
			speed = 0;
		}
	}
	
	void setGradoContaminacion(int c) {
	if(c < 0 || c > 10){
		throw new IllegalArgumentException("c mayor que 0 o menor que 10");
	}
	else {
		contClass = c;
	}
}
	
	@Override
	void advance(int time) {

		if(status == VehicleStatus.TRAVELING) {
			
			int localizacionNueva = location + speed;
			
			if(localizacionNueva > road.getLength()) {
				localizacionNueva = road.getLength();
			}
			int c= contClass*(localizacionNueva -location);
			distance += (localizacionNueva - location);
			totalCO2 += c;
			road.addContamination(c);
			location = localizacionNueva;
			
			if(location >=road.getLength()) {
				status = VehicleStatus.WAITING;
				speed=0;
				indiceItinerary++;
				road.getDest().enter(this);
			}
		}else {
			speed = 0;
		}
	}
	
	
	void moveToNextRoad() {
		
		if(status == VehicleStatus.TRAVELING || status == VehicleStatus.ARRIVED) {
			throw new IllegalArgumentException("the status of the vehicle is invalid");
		}
		if(status == VehicleStatus.WAITING || status == VehicleStatus.ARRIVED) {
			road.exit(this);
		}
		if(indiceItinerary == itinerary.size() - 1){
			status = VehicleStatus.ARRIVED;
		}else{	
			road = itinerary.get(indiceItinerary).roadTo(itinerary.get(indiceItinerary+1));
			location = 0;
			road.enter(this);
			status = VehicleStatus.TRAVELING;	
			

		}
		
	}

	@Override
	public JSONObject report() {
				
		JSONObject jo1 = new JSONObject();
		
		jo1.put("distance", distance);
		jo1.put("co2", totalCO2);
		jo1.put("id", getId());
		jo1.put("class", contClass);
		jo1.put("speed", speed);
		jo1.put("status", status.toString());
		if(status == VehicleStatus.TRAVELING || status == VehicleStatus.WAITING) {
			jo1.put("road", road.getId());
			jo1.put("location", location);
		}
		
		return jo1;
	}	
	

	public int getLocation() {
		return location;
	}
	
	public int getSpeed() {
		return speed;
	} 
	
	public int getMaxSpeed() {
		return maxSpeed;
	}
	
	public int getContClass() {
		return contClass;
	}

	public VehicleStatus getStatus() {
		return status;
	}
	public int getDistance() {
		return distance;
	}
	
	public int getTotalCO2() {
		return totalCO2;
	}
	
	public List<Junction> getItinerary(){
		return copiaItinerary;
	}
	
	public Road getRoad() {
		return road;
	}


}
