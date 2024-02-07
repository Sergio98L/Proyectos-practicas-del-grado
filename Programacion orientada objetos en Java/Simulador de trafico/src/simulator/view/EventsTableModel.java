package simulator.view;

import java.util.ArrayList;
import java.util.List;
import javax.swing.table.AbstractTableModel;

import simulator.control.Controller;
import simulator.model.Event;
import simulator.model.RoadMap;
import simulator.model.TrafficSimObserver;

public class EventsTableModel extends AbstractTableModel implements TrafficSimObserver {
	
	private static final long serialVersionUID = 1L;
	private List<Event> _listaEventos;
	private String _cols[] = { "Time", "Desc." }; 
	
	public EventsTableModel(Controller ctrl) {
		
		ctrl.addObserver(this);
		_listaEventos= new ArrayList<Event>();
	}
	@Override
	public int getRowCount() {
		
	 return _listaEventos.size();
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
		String s = "";
		Event e = _listaEventos.get(rowIndex);
		switch ( columnIndex ) {
			case 0:
				s = Integer.toString(e.getTime());
				break;
			case 1:
				s = e.toString();
				break;
			default:
				assert(false);
		}
		return s;
		}
	@Override
	public void onAdvanceStart(RoadMap map, List<Event> listaEventos, int time) {
		// TODO Auto-generated method stub
		
	}
	@Override
	public void onAdvanceEnd(RoadMap map, List<Event> listaEventos, int time) {
		_listaEventos =listaEventos;
		fireTableDataChanged();
		
	}
	@Override
	public void onEventAdded(RoadMap map, List<Event> listaEventos, Event e, int time) {
		_listaEventos =listaEventos;
		fireTableDataChanged();
		
	}
	@Override
	public void onReset(RoadMap map, List<Event> listaEventos, int time) {
		_listaEventos =listaEventos;
		fireTableDataChanged();
		
	}
	@Override
	public void onRegister(RoadMap map, List<Event> listaEventos, int time) {
		
	}
	@Override
	public void onError(String msg) {
		// TODO Auto-generated method stub
		
	}
	
}
