package simulator.view;

import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.Frame;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;



import javax.swing.BoxLayout;
import javax.swing.DefaultComboBoxModel;

import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JDialog;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JSpinner;
import javax.swing.SpinnerNumberModel;

import simulator.model.Road;
import simulator.model.RoadMap;

import simulator.model.Weather;

public class ChangeWeatherDialog extends JDialog{


	private static final long serialVersionUID = 1L;
	private JComboBox<Road> cbRoads;
	private JComboBox<Weather> cbWeather;
	private JSpinner jsTiks;
	private int estado;
	
	public ChangeWeatherDialog(Frame parent) {
		super(parent,true); //Para que sea modal y no se pueda clicar fuera del cuadrado
		initGUI();
		
		
	}
	
	private void initGUI() {
		cbRoads = new JComboBox<Road>();
		cbWeather = new JComboBox<Weather>();
		jsTiks = new JSpinner();
		
	
		
		this.setTitle("Change Road Weather");
		
		//main Panel
		JPanel mainPanel = new JPanel();
		mainPanel.setLayout(new BoxLayout(mainPanel, BoxLayout.Y_AXIS));
		
			//Label
			JPanel txtPanel = new JPanel();
			txtPanel.setLayout(new FlowLayout());
			JLabel txtVentana = new JLabel("Schedule an event to change the weather of a road after a given number of simulation ticks from now.");
			txtVentana.setAlignmentX(CENTER_ALIGNMENT);
			txtPanel.add(txtVentana);
			
		//secondary Panel
		JPanel secondaryPanel = new JPanel();
		secondaryPanel.setLayout(new FlowLayout());
		
			//CbmBox JSpinner
			JLabel txtVehicle = new JLabel("Road");
			cbRoads.setModel(new DefaultComboBoxModel<Road>());
			cbRoads.setPreferredSize(new Dimension(80, 25));
			
			JLabel txtC02 = new JLabel("Weather");
			cbWeather.setModel(new DefaultComboBoxModel<Weather>());
			cbWeather.setPreferredSize(new Dimension(80, 25));
			
			JLabel txtTicks = new JLabel("Ticks");
			jsTiks = new JSpinner(new SpinnerNumberModel(10, 1, 99999, 1));
			jsTiks.setPreferredSize(new Dimension(80, 25));
			
		//button Panel
		JPanel buttonPanel = new JPanel();
		buttonPanel.setLayout(new FlowLayout());	
		
			//botonCancelar
			JButton botonCancel = new JButton("Cancel");
			botonCancel.setToolTipText("Cancelar la creacion de un nuevo evento");
			botonCancel.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				cancel();
			}});
			//botonOk
			JButton botonOk = new JButton("Ok");
			botonOk.setToolTipText("Crea el nuevo evento");
			botonOk.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {				
				ok();
			}});
			
		//Añadir al buttonPanel
		buttonPanel.add(botonCancel);
		buttonPanel.add(botonOk);
			
		//Añadir al secundaryPanel
		secondaryPanel.add(txtVehicle);
		secondaryPanel.add(cbRoads);
		secondaryPanel.add(txtC02);
		secondaryPanel.add(cbWeather);
		secondaryPanel.add(txtTicks);
		secondaryPanel.add(jsTiks);
		
		//Añadir al mainPanel
		mainPanel.add(txtPanel);
		mainPanel.add(secondaryPanel);
		mainPanel.add(buttonPanel);
		
		
		//Inicializar Weather CB
		
		cbWeather.addItem(Weather.CLOUDY);
		cbWeather.addItem(Weather.RAINY);
		cbWeather.addItem(Weather.STORM);
		cbWeather.addItem(Weather.SUNNY);
		cbWeather.addItem(Weather.WINDY);
		
		//Añadir al JDialog
		this.setContentPane(mainPanel);
		this.pack();
		this.setResizable(false);
		//this.setVisible(true); No poner ser visible porque si no crea una ventana vacia extra
		this.setLocationRelativeTo(null); //Para que aparezca siempre en medio de la pantalla
	}
	private void cancel() {
		this.setVisible(false);
		this.estado =0;
	}
	private void ok() {
		if(this.cbRoads.getSelectedItem() !=null) {
			this.setVisible(false);
			this.estado =1;
		}		
	}
	public int open(RoadMap roadMap) {
				
		if(roadMap !=null) {
			for(Road road : roadMap.getRoads()) {
				cbRoads.addItem(road);
			}	
		}		
		this.setVisible(true);
		return this.estado;
		
	}

	public Road getRoad() {
		return (Road) cbRoads.getSelectedItem();
	}
	public Weather getWeather() {
		return (Weather) cbWeather.getSelectedItem();
	}
	public Integer getTicks() {
		return (Integer) jsTiks.getValue();
	}
}
