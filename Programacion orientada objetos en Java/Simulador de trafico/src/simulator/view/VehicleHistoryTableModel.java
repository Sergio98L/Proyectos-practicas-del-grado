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


public class VehicleHistoryTableModel extends AbstractTableModel implements TrafficSimObserver {
	
	private static final long serialVersionUID = 1L;
	private List<List<Pair<String,Integer>>> miLista;
	private int SpeedLimit;
	private String _cols[] = { "Tick", "Vehicles"}; 
	
	public VehicleHistoryTableModel(Controller ctrl) {	
		miLista = new ArrayList<>();
		ctrl.addObserver(this);
	}
	@Override
	public int getRowCount() {
		// TODO Auto-generated method stub
		return miLista.size();
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
		String s = "";	
		List<Pair<String,Integer>> paresVehicle = miLista.get(rowIndex);
		
		switch (columnIndex) {
			case 0:
				s = ""+(rowIndex+1);
				break;
			case 1:
				List<String> datosAMostrar = new ArrayList<String>();
				for(Pair<String,Integer> parEn: paresVehicle) {
					
					if(parEn.getSecond() > SpeedLimit)
					datosAMostrar.add(parEn.getFirst());
				}			
				s = datosAMostrar.toString();
				break;
			
			default:
				break;
		}
		return s;
	}
	public void setSpeed(int i) {
		this.SpeedLimit = i;
	}
	@Override
	public void onAdvanceStart(RoadMap map, List<Event> listaEventos, int time) {
		// TODO Auto-generated method stub
		
	}
	@Override
	public void onAdvanceEnd(RoadMap map, List<Event> listaEventos, int time) {
		
		List<Pair<String,Integer>> aux1 = new ArrayList<Pair<String,Integer>>();
		
		for(Vehicle v: map.getVehicles()) {
			Pair<String,Integer> pairAux = new Pair<String,Integer>(v.getId(),v.getSpeed());		
			aux1.add(pairAux);
		}	
		miLista.add(aux1);
		
		fireTableDataChanged();
		
	}
	@Override
	public void onEventAdded(RoadMap map, List<Event> listaEventos, Event e, int time) {
		
	}
	@Override
	public void onReset(RoadMap map, List<Event> listaEventos, int time) {
		miLista = new ArrayList<List<Pair<String,Integer>>>();
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
