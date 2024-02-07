package simulator.view;

import java.util.ArrayList;
import java.util.List;

import javax.swing.table.AbstractTableModel;

import simulator.control.Controller;
import simulator.model.Event;
import simulator.model.Junction;
import simulator.model.Road;
import simulator.model.RoadMap;
import simulator.model.TrafficSimObserver;

public class JunctionsTableModel extends AbstractTableModel implements TrafficSimObserver {
	
	
	private static final long serialVersionUID = 1L;
	private List<Junction> _listaCruces;
	private String _cols[] = { "Id", "Green","Queues"}; 
	
	public JunctionsTableModel(Controller ctrl) {
		
		ctrl.addObserver(this);
		_listaCruces = new ArrayList<Junction>();
	}
	public int getRowCount() {
		// TODO Auto-generated method stub
		return _listaCruces.size();
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
		Junction j =_listaCruces.get(rowIndex);
		
		switch (columnIndex) {
			case 0:
				s = j.getId();
				break;
			case 1:
				if(j.getGreenLightIndex() ==-1) {
					s = "NONE";
				}else {
					s = j.getGreenLightIndex();
					s = j.getInRoads().get(j.getGreenLightIndex());
				}
				break;
			case 2:
				for (Road r : j.getInRoads()) {
				s = s + " " + r.getId() + ":" + j.getQueue(r);
				}
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
		_listaCruces =map.getJunctions();
		fireTableDataChanged();
		
	}
	@Override
	public void onEventAdded(RoadMap map, List<Event> listaEventos, Event e, int time) {
		_listaCruces =map.getJunctions();
		fireTableDataChanged();
		
	}
	@Override
	public void onReset(RoadMap map, List<Event> listaEventos, int time) {
		_listaCruces =map.getJunctions();
		fireTableDataChanged();
		
	}
	@Override
	public void onRegister(RoadMap map, List<Event> listaEventos, int time) {
		_listaCruces =map.getJunctions();
		fireTableDataChanged();
		
	}
	@Override
	public void onError(String msg) {
		// TODO Auto-generated method stub
		
	}
}
