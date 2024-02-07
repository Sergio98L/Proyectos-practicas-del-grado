package simulator.view;

import java.util.ArrayList;
import java.util.List;

import javax.swing.table.AbstractTableModel;

import simulator.control.Controller;
import simulator.model.Event;
import simulator.model.Road;
import simulator.model.RoadMap;
import simulator.model.TrafficSimObserver;


public class RoadsTableModel extends AbstractTableModel implements TrafficSimObserver {
	
	private static final long serialVersionUID = 1L;
	private List<Road> _listaCarreteras;
	private String _cols[] = { "Id", "Length","Weather","Max speed", "Speed limit","Total CO2","C02 Limit"}; 
	
	public RoadsTableModel(Controller ctrl) {	
		_listaCarreteras = new ArrayList<Road>();
		ctrl.addObserver(this);
	}
	@Override
	public int getRowCount() {
		// TODO Auto-generated method stub
		return _listaCarreteras.size();
	}
	@Override
	public int getColumnCount() {
		// TODO Auto-generated method stub
		return _cols.length;
	}
	@Override
	public String getColumnName(int column) {
		return _cols[column];
	}
	@Override
	public Object getValueAt(int rowIndex, int columnIndex) {
		Object s = "";	
		Road road =_listaCarreteras.get(rowIndex);
		
		switch (columnIndex) {
			case 0:
				s = road.getId();
				break;
			case 1:
				s = road.getLength();
				break;
			case 2:
				s= road.getWeather();
				break;
			case 3:
				s=road.getMaxSpeed();
				break;
			case 4:
				s=road.getSpeedLimit();
				break;
			case 5:
				s=road.getTotalCO2();
				break;
			case 6:
				s=road.getContLimit();
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
		_listaCarreteras =map.getRoads();
		fireTableDataChanged();
		
	}
	@Override
	public void onEventAdded(RoadMap map, List<Event> listaEventos, Event e, int time) {
		_listaCarreteras =map.getRoads();
		fireTableDataChanged();
		
	}
	@Override
	public void onReset(RoadMap map, List<Event> listaEventos, int time) {
		_listaCarreteras =map.getRoads();
		fireTableDataChanged();
		
	}
	@Override
	public void onRegister(RoadMap map, List<Event> listaEventos, int time) {
		_listaCarreteras =map.getRoads();
		fireTableDataChanged();
		
	}
	@Override
	public void onError(String msg) {
		// TODO Auto-generated method stub
		
	}
}
