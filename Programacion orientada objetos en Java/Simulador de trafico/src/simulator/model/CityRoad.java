package simulator.model;

public class CityRoad extends Road{

	
	CityRoad(String id, Junction srcJunc, Junction destJunc, int maxSpeed, int contLimit, int length, Weather weather) {
		super(id, srcJunc, destJunc, maxSpeed, contLimit, length, weather);

	}

	@Override
	void reduceTotalContamination() {
		int x;
		switch (weather) {
		case SUNNY:
			x= 2;
			break;
		case CLOUDY:
			x= 2;
			break;
		case RAINY:
			x= 2;
			break;
		case WINDY:
			x= 10;
			break;
		case STORM:
			x= 10;
			break; 
		default:
			x = 0;
			break;
		}
		if(totalCO2 > 0) {
			totalCO2 -= x;
		}
		
	}

	@Override
	void updateSpeedLimit() {
		speedLimit = maxSpeed;
	}

	@Override
	int calculateVehicleSpeed(Vehicle v) {
		
		return (((11-v.getContClass())*speedLimit)/11);
	}


}
