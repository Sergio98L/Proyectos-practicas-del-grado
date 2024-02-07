package simulator.view;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.Frame;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.FileInputStream;

import java.util.ArrayList;
import java.util.List;


import javax.swing.Box;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFileChooser;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JSeparator;
import javax.swing.JSpinner;
import javax.swing.JTable;
import javax.swing.JToolBar;
import javax.swing.SpinnerNumberModel;

import javax.swing.SwingUtilities;


import simulator.control.Controller;
import simulator.misc.Pair;
import simulator.model.Event;
import simulator.model.NewSetContClassEvent;
import simulator.model.RoadMap;
import simulator.model.SetWeatherEvent;
import simulator.model.TrafficSimObserver;

import simulator.model.Weather;

public class ControlPanel extends JPanel implements TrafficSimObserver{
	
	private static final long serialVersionUID = 1L;
	private Controller _ctrl;
	private RoadMap roadMap;
	private int time;
	private JFileChooser JFileChooser;
	private boolean _stopped;
	
	private JToolBar toolBar;
	private JButton botonElegirFichero;
	private JButton botonCambiarC02;
	private JButton botonCambiarClima;
	private JButton botonWeatherHistory;
	private JButton botonContHistory;
	private JButton botonVehiclesSpeedHistory;
	private JButton botonRun;
	private JButton botonStop;
	private JSpinner jsTiks;
	private JButton botonExit;
	
	private ChangeWeatherDialog weatherDialog;
	private ChangeCO2ClassDialog C02Dialog;
	private WeatherHistoryDialog weatherHistoryDialog;
	private RoadContaminationHistoryDialog roadContaminationHistory;
	private VehicleHistoryDialog vHistoryDialog;
	
	private WeatherHistoryTableModel weatherHistoryTableModel;
	private ContHistoryTableModel contHistoryTableModel;
	private VehicleHistoryTableModel vehicleHistoryTableModel;
	
	public ControlPanel(Controller ctrl) {
		
		_ctrl = ctrl;		
		_stopped = true;
		initGUI();
		_ctrl.addObserver(this);
	}
	private void initGUI() {
		this.setLayout(new BorderLayout());
		toolBar = new JToolBar();
		
		
		
		//Crear tabla del modelo para WeatherHistory
		weatherHistoryTableModel = new WeatherHistoryTableModel(_ctrl);
		contHistoryTableModel = new ContHistoryTableModel(_ctrl);
		vehicleHistoryTableModel = new VehicleHistoryTableModel(_ctrl);
		
		
		//Boton abrir fichero
		JFileChooser = new JFileChooser();
		
		File workingDirectory = new File("resources/examples/"); //Para que abra la carpeta del proyecto	
		JFileChooser.setCurrentDirectory(workingDirectory);
		
		
		botonElegirFichero = new JButton();
		
		botonElegirFichero.setToolTipText("Abrir un fichero del sistema");	
		botonElegirFichero.setIcon(new ImageIcon("resources/icons/open.png"));		
		botonElegirFichero.addActionListener(new ActionListener() {

		@Override
			public void actionPerformed(ActionEvent e) {
				loadFile();
			}});
		
		//Boton Cambiar Contaminacion
		botonCambiarC02 = new JButton();
		botonCambiarC02.setToolTipText("Cambiar la contaminacion de un vehiculo");
		botonCambiarC02.setIcon(new ImageIcon("resources/icons/co2class.png"));	
		botonCambiarC02.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				changeCO2Class();
			}});
		
		//Boton Cambiar Clima
		botonCambiarClima = new JButton();
		botonCambiarClima.setToolTipText("Cambiar el clima de una carretera");
		botonCambiarClima.setIcon(new ImageIcon("resources/icons/weather.png"));	
		botonCambiarClima.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				changeWeather();
			}});
		
		//Boton WeatherHistory
		botonWeatherHistory = new JButton();
		botonWeatherHistory.setToolTipText("Cambiar el clima de una carretera");
		botonWeatherHistory.setIcon(new ImageIcon("resources/icons/weather.png"));	
		botonWeatherHistory.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				weatherHistory();
			}});
		//Boton ContHistory
		botonContHistory = new JButton();
		botonContHistory.setToolTipText("prueba");
		botonContHistory.setIcon(new ImageIcon("resources/icons/co2class.png"));	
		botonContHistory.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				contHistory();
			}});
		//Boton botonVehiclesSpeedHistory
		botonVehiclesSpeedHistory = new JButton();
		botonVehiclesSpeedHistory.setToolTipText("prueba");
		botonVehiclesSpeedHistory.setIcon(new ImageIcon("resources/icons/weather.png"));	
		botonVehiclesSpeedHistory.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				vehicleHistory();
			}});
				
		//Boton Run
		botonRun = new JButton();
		botonRun.setToolTipText("Ejecuta la simulacion");
		botonRun.setIcon(new ImageIcon("resources/icons/run.png"));	
		botonRun.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				start();
			}});
	
		
		//Boton Stop
		botonStop = new JButton();
		botonStop.setToolTipText("Para la simulacion");
		botonStop.setIcon(new ImageIcon("resources/icons/stop.png"));	
		botonStop.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				 stop_sim();
			}});
		//JLabel Ticks
		
		JLabel ticks = new JLabel(" Ticks: ");
		
		//Crear JSpinner
		jsTiks = new JSpinner(new SpinnerNumberModel(10, 1, 99999, 1));
		jsTiks.setMaximumSize(new Dimension(80, 40));
		jsTiks.setMinimumSize(new Dimension(80, 40));
		jsTiks.setPreferredSize(new Dimension(80, 40));
		
		//Boton Exit
		botonExit = new JButton();
		botonExit.setToolTipText("Para la simulacion");
		botonExit.setIcon(new ImageIcon("resources/icons/exit.png"));	
		botonExit.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				exit();
				
			}});
		
		
		JSeparator sep = new JSeparator(JSeparator.VERTICAL);
		sep.setPreferredSize(new Dimension(10,10));
		sep.setMaximumSize(new Dimension(50,50));
		JSeparator sep2 =new JSeparator(JSeparator.VERTICAL);;
		sep2.setPreferredSize(new Dimension(10,10));
		sep2.setMaximumSize(new Dimension(50,50));
		JSeparator sep3 = new JSeparator(JSeparator.VERTICAL);
		sep3.setPreferredSize(new Dimension(10,10));
		sep3.setMaximumSize(new Dimension(50,50));
		
		
		//A�adir los componentes a la toolBar
		toolBar.add(botonElegirFichero);
		
		toolBar.addSeparator(); //Para que se cree la linea del separador y no sea un hueco vacio, si no se pone el addSeparator se crea pegado al boton de la izquierda 
		toolBar.add(sep);
		
		toolBar.add(botonCambiarC02);
		toolBar.add(botonCambiarClima);
		toolBar.add(botonWeatherHistory);
		toolBar.add(botonContHistory);
		toolBar.add(botonVehiclesSpeedHistory);
		
		toolBar.addSeparator(); //Para que se cree la linea del separador y no sea un hueco vacio, si no se pone el addSeparator se crea pegado al boton de la izquierda 
		toolBar.add(sep2);
		
		toolBar.add(botonRun);
		toolBar.add(botonStop);
		toolBar.add(ticks);
		toolBar.add(jsTiks);
		toolBar.add(Box.createHorizontalGlue());
		
		toolBar.addSeparator();//Para que se cree la linea del separador y no sea un hueco vacio, si no se pone el addSeparator se crea pegado al boton de la izquierda 	
		toolBar.add(sep3);
		
		toolBar.add(botonExit);
		
		
		toolBar.addSeparator();

		//A�adir los componentes al ControlPanel
		this.add(toolBar,BorderLayout.CENTER);
		
	}
	private void exit() {
		if(JOptionPane.showConfirmDialog((Frame) SwingUtilities.getWindowAncestor(this), "¿Salir del programa?", "Salir", JOptionPane.YES_NO_OPTION) == 0) {
			System.exit(0);
		}
	}
	private void start() {
		_stopped = false;
		enableToolBar(false);
		run_sim((Integer) jsTiks.getValue());
	}
	
	private void stop_sim() {
		_stopped = true;
	}
	
	private void run_sim(int n) {
		if (n > 0 && !_stopped) {
			try {
				_ctrl.run(1,null);
			} catch (Exception e) {
			 e.printStackTrace();
			 enableToolBar(true);
			 _stopped = true;
			 return;
			}
			SwingUtilities.invokeLater(new Runnable() {
				@Override
				public void run() {
					run_sim(n - 1);
				}
			});
			} 
		else {
			enableToolBar(true);
			_stopped = true;
			}		
	}
	private void enableToolBar(boolean enable) {
			botonElegirFichero.setEnabled(enable);
			botonCambiarC02.setEnabled(enable);
			botonCambiarClima.setEnabled(enable);
			botonRun.setEnabled(enable);
			botonWeatherHistory.setEnabled(enable);
			botonContHistory.setEnabled(enable);
			botonVehiclesSpeedHistory.setEnabled(enable);
	}
	private void changeWeather() {
		int estado =0;//
		weatherDialog = new ChangeWeatherDialog((Frame) SwingUtilities.getWindowAncestor(this));
		
		estado = weatherDialog.open(roadMap);//
		
		if(estado !=0) {
			List<Pair<String, Weather>> valoresJDialog = new ArrayList<>();
			valoresJDialog.add(new Pair<String, Weather>(weatherDialog.getRoad().getId(), weatherDialog.getWeather()));			
			int ticks =weatherDialog.getTicks();
			
			try {
				_ctrl.addEvent(new SetWeatherEvent (time+ticks, valoresJDialog));
			}catch(IllegalArgumentException e){
				JOptionPane.showMessageDialog((Frame) SwingUtilities.getWindowAncestor(this), "Se ha producido un error, no se puedo cambiar el Weather (" + e + ")");
			}
		}
		
	}
	private void changeCO2Class() {
		int estado = 0;
		C02Dialog = new ChangeCO2ClassDialog((Frame) SwingUtilities.getWindowAncestor(this));
		
		
		estado =C02Dialog.open(roadMap);
		//if(C02Dialog.open(_ctrl.getTrafficSM().getRoadMap()) == 1){	
		if(estado !=0) {
			List<Pair<String, Integer>> valoresJDialog = new ArrayList<>();
			valoresJDialog.add(new Pair<String, Integer>(C02Dialog.getVehicle().getId(), C02Dialog.getCO2Class()));			
			int ticks =C02Dialog.getTicks();
			
			try {
				_ctrl.addEvent(new NewSetContClassEvent (time+ticks, valoresJDialog));
			}catch(IllegalArgumentException e){
				JOptionPane.showMessageDialog((Frame) SwingUtilities.getWindowAncestor(this), "Se ha producido un error, no se puedo cambiar la CO2Class (" + e + ")");
			}
		}
		
	}
	private void weatherHistory() {
		
		weatherHistoryDialog = new WeatherHistoryDialog((Frame) SwingUtilities.getWindowAncestor(this),weatherHistoryTableModel);	
		
		weatherHistoryDialog.open(roadMap);
		//if(C02Dialog.open(_ctrl.getTrafficSM().getRoadMap()) == 1){	
		
	}
	private void contHistory() {
		
		roadContaminationHistory = new RoadContaminationHistoryDialog((Frame) SwingUtilities.getWindowAncestor(this),contHistoryTableModel);	
		roadContaminationHistory.setVisible();
		
		//if(C02Dialog.open(_ctrl.getTrafficSM().getRoadMap()) == 1){	
		
	}
	private void vehicleHistory() {
		
		vHistoryDialog = new VehicleHistoryDialog((Frame) SwingUtilities.getWindowAncestor(this),vehicleHistoryTableModel);	
		vHistoryDialog.open(roadMap);
		
		//if(C02Dialog.open(_ctrl.getTrafficSM().getRoadMap()) == 1){	
		
	}
	private void loadFile() {
		if(JFileChooser.showOpenDialog(this) == javax.swing.JFileChooser.APPROVE_OPTION) {
			File in = JFileChooser.getSelectedFile();
			try {
				
				_ctrl.reset();
				_ctrl.loadEvents(new FileInputStream(in));
				
			} catch (Exception e1) {
				JOptionPane.showMessageDialog((Frame) SwingUtilities.getWindowAncestor(this), "Error al cargar el fichero");		
			}			
		}
		
	}
	@Override
	public void onAdvanceStart(RoadMap map, List<Event> listaEventos, int time) {
		// TODO Auto-generated method stub
		
	}
	@Override
	public void onAdvanceEnd(RoadMap map, List<Event> listaEventos, int time) {
		roadMap = map;	
		this.time = time;
	}
	@Override
	public void onEventAdded(RoadMap map, List<Event> listaEventos, Event e, int time) {
		// TODO Auto-generated method stub
		
	}
	@Override
	public void onReset(RoadMap map, List<Event> listaEventos, int time) {
		
		
	}
	@Override
	public void onRegister(RoadMap map, List<Event> listaEventos, int time) {
		
	
	}
	@Override
	public void onError(String msg) {
		// TODO Auto-generated method stub
		
	}
	
}
