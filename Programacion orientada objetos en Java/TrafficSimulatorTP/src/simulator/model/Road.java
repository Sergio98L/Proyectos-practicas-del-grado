package simulator.model;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;

import org.json.JSONArray;
import org.json.JSONObject;

public abstract class Road extends SimulatedObject {
	
	protected Junction srcJunc;
	
	protected Junction destJunc;
	
	protected int length;
	
	protected int maxSpeed;
	
	protected int speedLimit;

	protected int contLimit;
	
	protected int totalCO2;
	
	protected Weather weather;
	
	protected List<Vehicle> vehiculos;
	
	private MiComparador comparaVehiculos;
	
	Road(String id, Junction srcJunc, Junction destJunc, int maxSpeed,
			int contLimit, int length, Weather weather) throws IllegalArgumentException {
			super(id);
			this.srcJunc = srcJunc;
			this.destJunc = destJunc;
			this.length = length;
			this.maxSpeed = maxSpeed;
			this.weather = weather;
			this.contLimit = contLimit;
			speedLimit = maxSpeed;
			this.vehiculos = new ArrayList<Vehicle>();
			
			
			comparaVehiculos = new MiComparador();
			
			if(maxSpeed <= 0) {
				throw new IllegalArgumentException("maxSpeed mayor que 0");
			}
			else if(contLimit < 1) {
				throw new IllegalArgumentException("contLimit mayor que 0");
			}
			else if(length <= 0) {
				throw new IllegalArgumentException("length mayor que 0");
			}
			else if(srcJunc == null) {
				throw new NullPointerException("srcJunc is null");
			}
			else if(destJunc == null) {
				throw new NullPointerException("destJunc is null");
			}
			else if(weather == null) {
				throw new NullPointerException("weather is null");
			}
			this.destJunc.addIncommingRoad(this);
			this.srcJunc.addOutGoingRoad(this);
	}
	
	void enter(Vehicle v){
		
		if(v.getLocation() != 0) {
			throw new IllegalArgumentException("localizacion del vehiculo inicial no es 0");
		}
		else if (v.getSpeed() != 0) {
			throw new IllegalArgumentException("velocidad del vehiculo inicial no es 0");
		}
		else {vehiculos.add(v);}
	}
	
	void exit(Vehicle v) {
		vehiculos.remove(v);
	}
	
	void setWeather(Weather w) throws NullPointerException {
		weather = w;
		if(weather == null) {
			throw new NullPointerException("type Weather is null");
		}
	}
	
	void addContamination(int c) {
		if(c < 0) {
			throw new IllegalArgumentException("value of contamination to add is negative");
		}
		else {
			totalCO2 += c;
		}
	}
	
	abstract void reduceTotalContamination();
	
	abstract void updateSpeedLimit();
	
	abstract int calculateVehicleSpeed(Vehicle v);
	
	@Override
	void advance(int time) {

		reduceTotalContamination();
		updateSpeedLimit();
		
		for(Vehicle aux:vehiculos) {
			aux.setSpeed(calculateVehicleSpeed(aux));
			aux.advance(time);
		}
		vehiculos.sort(comparaVehiculos);

	}

	@Override
	public JSONObject report() {

		JSONObject jo1 = new JSONObject();
		
		JSONArray ja1 = new JSONArray();
		
		for(Vehicle aux: vehiculos) {
			ja1.put(aux.getId());
		}
		
		jo1.put("id", getId());
		jo1.put("speedlimit", speedLimit);
		jo1.put("weather", weather.toString());
		jo1.put("co2", totalCO2);
		jo1.put("vehicles", ja1);

		return jo1;
	}


	
	public int getLength() {
		return length;	
	}
	
	public Junction getDest() {
		return destJunc; 	
	}
	
	public Junction getSrc() {
		return srcJunc;
	}
	
	public Weather getWeather() {
		return weather;
	}
	
	public int getContLimit() {
		return contLimit;
	}
	
	public int getMaxSpeed() {
		return maxSpeed;
	}
	
	public int getTotalCO2() {
		return totalCO2;
	}
	
	public void setTotalCO2(int totalCO2) {
		this.totalCO2 = totalCO2;
	}

	public int getSpeedLimit() {
		return speedLimit;
	}
	
	public  List<Vehicle> getVehicles(){
		return Collections.unmodifiableList(vehiculos);
	}
	
	public static class MiComparador implements Comparator<Vehicle>{
		
		@Override
		public int compare(Vehicle o1, Vehicle o2) {
			int ret;
			if(o1.getLocation() > o2.getLocation()) {
				ret = -1;
			}else if(o1.getLocation() < o2.getLocation()){
				ret = 1;
			}else{
				ret = 0;
			}
			return ret;
		}
		
	}
}
