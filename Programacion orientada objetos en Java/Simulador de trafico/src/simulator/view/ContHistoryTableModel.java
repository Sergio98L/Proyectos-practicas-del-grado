package simulator.view;

import java.util.ArrayList;
import java.util.List;

import javax.swing.table.AbstractTableModel;

import simulator.control.Controller;
import simulator.misc.Pair;
import simulator.model.Event;
import simulator.model.Road;
import simulator.model.RoadMap;
import simulator.model.TrafficSimObserver;
import simulator.model.Vehicle;

public class ContHistoryTableModel extends AbstractTableModel implements TrafficSimObserver {
	
	
	private static final long serialVersionUID = 1L;
	private List<List<Pair<Integer,String>>> miLista;
	private int maxCont;
	private String _cols[] = { "Tick", "Roads" }; 
	
	
	public ContHistoryTableModel(Controller ctrl) {		
		ctrl.addObserver(this);
		miLista = new ArrayList<>();
	}
	@Override
	public int getRowCount() {
		return miLista.size();
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
		List<Pair<Integer,String>> roads = this.miLista.get(rowIndex);
		
		switch (columnIndex) {
			case 0:
				s = ""+(rowIndex+1);
				break;
			case 1:
				List<String> stringAMostar = new ArrayList<>();
				for(Pair<Integer,String> r: roads) {
					if(r.getFirst()> maxCont) {
						stringAMostar.add(r.getSecond());
					}
				}
				s = stringAMostar.toString();
				break;
			default:
				break;
		}
		return s;
	}
	public void setmaxCont(int i) {
		this.maxCont = i;
	}
	@Override
	public void onAdvanceStart(RoadMap map, List<Event> listaEventos, int time) {
		// TODO Auto-generated method stub
		
	}
	@Override
	public void onAdvanceEnd(RoadMap map, List<Event> listaEventos, int time) {
		List<Pair<Integer,String>> aux = new ArrayList<Pair<Integer,String>>();
		
		for(Road r : map.getRoads()) {
			Pair<Integer,String> aux2 = new Pair<Integer,String>(r.getTotalCO2(),r.getId());
			aux.add(aux2);
		}
		
		miLista.add(aux);
		fireTableDataChanged();
		
	}
	@Override
	public void onEventAdded(RoadMap map, List<Event> listaEventos, Event e, int time) {
		
	}
	@Override
	public void onReset(RoadMap map, List<Event> listaEventos, int time) {
		miLista = new ArrayList<>();
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
