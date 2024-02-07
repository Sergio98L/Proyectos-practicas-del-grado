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
	import simulator.model.Weather;
	
	public class WeatherHistoryTableModel extends AbstractTableModel implements TrafficSimObserver{
	
	private List<List<Pair<String,Weather>>> miLista;
	String[] _col = {"Ticks","Roads"};
	private Weather _w;
	private Controller c;
	
	public WeatherHistoryTableModel(Controller c) {
		this.c = c;
		this.c.addObserver(this);
		// TODO Auto-generated constructor stub
		miLista = new ArrayList<>();
	}
	
	@Override
	public int getRowCount() {
		return miLista.size();
	}
	
	@Override
	public int getColumnCount() {
	// TODO Auto-generated method stub
		return _col.length;
	}
	
	@Override
	public String getValueAt(int rowIndex, int columnIndex) {
	
		List<Pair<String, Weather>> elem = this.miLista.get(rowIndex);
		String s = "";
		
		switch (columnIndex) {
			case 0:
			s = ""+(rowIndex+1);
			break;
			case 1:
			List<String> mostrar = new ArrayList<String>();
			for(Pair<String,Weather> p: elem) {
				if(p.getSecond().equals(_w)) {
				mostrar.add( p.getFirst());
				}
			}
			s = mostrar.toString();
			break;
			default:
			assert (false);
			}
		return s;
	}
	
	public void setWeather(Weather w) {
	this._w = w;
	}
	
	@Override
	public void onAdvanceStart(RoadMap map, List<Event> events, int time) {
	// TODO Auto-generated method stub
	
	}
	
	@Override
	public void onAdvanceEnd(RoadMap map, List<Event> events, int time) {
	List<Pair<String, Weather>> l = new ArrayList<Pair<String,Weather>>();
		for(Road r: map.getRoads()) {
		Pair<String,Weather> aux = new Pair<String, Weather>(r.getId(), r.getWeather());
		l.add(aux);
		}
	this.miLista.add(l);
	
	}
	
	@Override
	public void onEventAdded(RoadMap map, List<Event> events, Event e, int time) {
	// TODO Auto-generated method stub
	
	}
	
	@Override
	public void onReset(RoadMap map, List<Event> events, int time) {
	this.miLista = new ArrayList<List<Pair<String,Weather>>>();
	
	}
	
	@Override
	public void onRegister(RoadMap map, List<Event> events, int time) {
	// TODO Auto-generated method stub
	
	}
	
	@Override
	public void onError(String err) {
	// TODO Auto-generated method stub
	
	}
	
	public void update() {
	fireTableDataChanged();
	
	}
	
	}
