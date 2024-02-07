package simulator.model;

public class InterCityRoad extends Road{
	
	InterCityRoad(String id, Junction srcJunc, Junction destJunc, int maxSpeed, int contLimit, int length,Weather weather) {
		super(id, srcJunc, destJunc, maxSpeed, contLimit, length, weather);
	}

	@Override
	void reduceTotalContamination() {
		int x;
		int tc = totalCO2;
		switch (weather) {
		case SUNNY:
			x= 2;
			break;
		case CLOUDY:
			x= 3;
			break;
		case RAINY:
			x= 10;
			break;
		case WINDY:
			x= 15;
			break;
		case STORM:
			x= 20;
			break; 
		default:
			x = 0;
			break;
		}
		
		totalCO2 = ((100-x)*tc)/100; 
		
		
	}

	@Override
	void updateSpeedLimit() {
		if(totalCO2 > this.contLimit) {
			speedLimit = maxSpeed/2;
		}
		else {
			speedLimit = this.maxSpeed;
		}	
	}

	@Override
	int calculateVehicleSpeed(Vehicle v) {
		int ret;
		if(weather == Weather.STORM) {
			ret = speedLimit*8/10;
		}else {
			 ret = speedLimit;
		}
		
		return ret;
	}

}
