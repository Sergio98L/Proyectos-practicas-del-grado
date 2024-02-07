package simulator.model;

import java.util.ArrayList;
import java.util.List;

import simulator.control.Controller;
import simulator.misc.Pair;

public class CarreterasConColas implements TrafficSimObserver{

	
	private List<Pair<Integer,List<Pair<String,Integer>>>> miLista;
	//Lista de pares  tiempo , carreteras + numero vehiculos en cola
	
	public CarreterasConColas(Controller ctrl) {
		ctrl.addObserver(this);
		miLista = new ArrayList<Pair<Integer,List<Pair<String,Integer>>>>();
	}
	
	public void onAdvanceStart(RoadMap map, List<Event> listaEventos, int time) {
		// TODO Auto-generated method stub
		
	}
	public void mostrar() {
		String salida = "";
		for(Pair<Integer,List<Pair<String,Integer>>> p: miLista) {		
			System.out.println("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
			salida = p.getFirst().toString() + ": [";
			
			for(Pair<String, Integer> a:p.getSecond()) {
				salida += a.getFirst() +" "+ a.getSecond().toString();
			}
			salida+="]";
			System.out.println(salida);
		}
	}
	@Override
	public void onAdvanceEnd(RoadMap map, List<Event> listaEventos, int time) {
		//Par derecho de carretera + tamano cola
		List<Pair<String,Integer>> aux = new ArrayList<Pair<String,Integer>>();
		
		int tamanoColaEnt = 0;
		int tamanoColaSalida = 0;
		int tamanoTotal = 0;
		
		for(Road r: map.getRoads()) {
			if(r.getSrc().getQueue(r) != null) {
				tamanoColaEnt =r.getSrc().getQueue(r).size();
			}
			if(r.getDest().getQueue(r) != null) {
				tamanoColaSalida =r.getDest().getQueue(r).size();
			}
			
			tamanoTotal = tamanoColaEnt + tamanoColaSalida;
			aux.add(new Pair<String, Integer>(r.getId(),tamanoTotal));
		
		}
		if(tamanoTotal >0) {
		Pair<Integer,List<Pair<String,Integer>>> aux2 = new Pair<Integer, List<Pair<String,Integer>>>(time, aux);
		miLista.add(aux2);
		}
	}

	@Override
	public void onEventAdded(RoadMap map, List<Event> listaEventos, Event e, int time) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void onReset(RoadMap map, List<Event> listaEventos, int time) {
		miLista = new ArrayList<Pair<Integer,List<Pair<String,Integer>>>>();
		
	}

	@Override
	public void onRegister(RoadMap map, List<Event> listaEventos, int time) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void onError(String msg) {
		// TODO Auto-generated method stub
		
	}

}
