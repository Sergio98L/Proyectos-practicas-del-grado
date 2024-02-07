package simulator.view;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.util.List;

import javax.swing.BorderFactory;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JSeparator;

import simulator.control.Controller;
import simulator.model.Event;
import simulator.model.RoadMap;
import simulator.model.TrafficSimObserver;

public class StatusBar extends JPanel implements TrafficSimObserver{
	
	
	private static final long serialVersionUID = 1L;
	private Controller _ctrl;
	private JLabel tiempo = new JLabel();
	private JLabel mensaje = new JLabel();
	
	
	public StatusBar(Controller ctrl) {
		
		_ctrl = ctrl;
		_ctrl.addObserver(this);
		initGUI();
	}
	private void initGUI() {
		this.setLayout(new FlowLayout(FlowLayout.LEFT));
		this.setBorder(BorderFactory.createLineBorder(Color.black));
		tiempo= new JLabel("Tiempo:");		
		mensaje= new JLabel("");
		
		
		JSeparator sep = new JSeparator(JSeparator.VERTICAL);
		sep.setPreferredSize(new Dimension(10,10));
		
		this.add(tiempo);
		this.add(sep);
		this.add(mensaje);
		
		
		
	}
	@Override
	public void onAdvanceStart(RoadMap map, List<Event> listaEventos, int time) {
		tiempo.setText("Tiempo: " + Integer.toString(time));
		mensaje.setText("");
		
	}
	@Override
	public void onAdvanceEnd(RoadMap map, List<Event> listaEventos, int time) {
		tiempo.setText("Tiempo: " + Integer.toString(time));
		mensaje.setText("");
		
	}
	@Override
	public void onEventAdded(RoadMap map, List<Event> listaEventos, Event e, int time) {
		tiempo.setText("Tiempo: " + Integer.toString(time));
		mensaje.setText("Event added: " + e.toString());
		
	}
	@Override
	public void onReset(RoadMap map, List<Event> listaEventos, int time) {
		tiempo.setText("Tiempo: " + Integer.toString(time));
		mensaje.setText("Simulacion reseteada");
		
	}
	@Override
	public void onRegister(RoadMap map, List<Event> listaEventos, int time) {
		mensaje.setText("Event added");
	}
	@Override
	public void onError(String msg) {
		mensaje.setText(msg);
		
	}
}
