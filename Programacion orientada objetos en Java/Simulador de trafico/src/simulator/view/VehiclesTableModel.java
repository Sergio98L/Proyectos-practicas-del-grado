package simulator.view;

import java.util.ArrayList;
import java.util.List;

import javax.swing.table.AbstractTableModel;

import simulator.control.Controller;
import simulator.model.Event;
import simulator.model.RoadMap;
import simulator.model.TrafficSimObserver;
import simulator.model.Vehicle;

public class VehiclesTableModel extends AbstractTableModel implements TrafficSimObserver {
	
	
	private static final long serialVersionUID = 1L;
	private List<Vehicle> _listaVehiculos;
	private String _cols[] = { "Id", "Location","Itinerary","CO2 class","Max speed", "Speed","Total CO2","Distance" }; 
	
	
	public VehiclesTableModel(Controller ctrl) {		
		ctrl.addObserver(this);
		_listaVehiculos = new ArrayList<Vehicle>();
	}
	@Override
	public int getRowCount() {
		return _listaVehiculos.size();
	}
	@Override
	public int getColumnCount() {
		return _cols.length;
	}
	@Override
	public String getColumnName(int column) {
		return _cols[column];
	}
	@Override
	public Object getValueAt(int rowIndex, int columnIndex) {
		Object s = "";	
		Vehicle vehiculo =_listaVehiculos.get(rowIndex);
		
		switch (columnIndex) {
			case 0:
				s = vehiculo.getId();
				break;
			case 1:
				switch (vehiculo.getStatus()) {
					case PENDING:
						s = "Pending";
						break;
					case TRAVELING:
						s = vehiculo.getRoad().getId() + ":" +vehiculo.getLocation();
						break;
					case WAITING:
						s = "Waiting:"+vehiculo.getRoad().getDest().getId();
						break;
					case ARRIVED:
						s = "Arrived";
						break;
					}
				break;
			case 2:
				s=vehiculo.getItinerary();
				break;
			case 3:
				s=vehiculo.getContClass();
				break;
			case 4:
				s=vehiculo.getMaxSpeed();
				break;
			case 5:
				s=vehiculo.getSpeed();
				break;
			case 6:
				s=vehiculo.getTotalCO2();
				break;
			case 7:
				s=vehiculo.getDistance();
				break;
			default:
				break;
		}
		return s;
	}
	@Override
	public void onAdvanceStart(RoadMap map, List<Event> listaEventos, int time) {
		// TODO Auto-generated method stub
		
	}
	@Override
	public void onAdvanceEnd(RoadMap map, List<Event> listaEventos, int time) {
		_listaVehiculos =map.getVehicles();
		fireTableDataChanged();
		
	}
	@Override
	public void onEventAdded(RoadMap map, List<Event> listaEventos, Event e, int time) {
		_listaVehiculos =map.getVehicles();
		fireTableDataChanged();
		
	}
	@Override
	public void onReset(RoadMap map, List<Event> listaEventos, int time) {
		_listaVehiculos =map.getVehicles();
		fireTableDataChanged();
		
	}
	@Override
	public void onRegister(RoadMap map, List<Event> listaEventos, int time) {
		_listaVehiculos =map.getVehicles();
		fireTableDataChanged();
		
	}
	@Override
	public void onError(String msg) {
		// TODO Auto-generated method stub
		
	}
}
