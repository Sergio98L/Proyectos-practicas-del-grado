package simulator.view;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.Frame;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.List;

import javax.swing.BorderFactory;
import javax.swing.BoxLayout;
import javax.swing.DefaultComboBoxModel;

import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JComponent;
import javax.swing.JDialog;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JSpinner;
import javax.swing.JTable;
import javax.swing.SpinnerNumberModel;
import javax.swing.border.TitledBorder;

import simulator.model.Road;
import simulator.model.RoadMap;

import simulator.model.Weather;

public class WeatherHistoryDialog extends JDialog{


	private static final long serialVersionUID = 1L;
	private JComboBox<Weather> cbWeather;
	private WeatherHistoryTableModel whTableM;
	
	
	public WeatherHistoryDialog(Frame parent,WeatherHistoryTableModel whTableM) {
		super(parent,true); //Para que sea modal y no se pueda clicar fuera del cuadrado
		this.whTableM = whTableM;
		initGUI();
	
	}
	
	private void initGUI() {
		
		cbWeather = new JComboBox<Weather>();
		
		
	
		
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
			
			
			
			JLabel txtWeather = new JLabel("Weather");
			cbWeather.setModel(new DefaultComboBoxModel<Weather>());
			cbWeather.setPreferredSize(new Dimension(80, 25));
			
			

			
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
			JButton botonUpdate = new JButton("Update");
			botonUpdate.setToolTipText("Cambia la tabla que muestra");
			botonUpdate.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {				
				update();
			}});
			
		//Añadir al buttonPanel
		buttonPanel.add(botonCancel);
		buttonPanel.add(botonUpdate);
			
		//Añadir al secundaryPanel

		
		secondaryPanel.add(txtWeather);
		secondaryPanel.add(cbWeather);

		
		
		//Añadir al mainPanel
		mainPanel.add(txtPanel);
		mainPanel.add(secondaryPanel);
		mainPanel.add(buttonPanel);
		
		JPanel junctionsView = createViewPanel(new JTable(whTableM));
		junctionsView.setPreferredSize(new Dimension(500, 200));
		mainPanel.add(junctionsView);
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
	}
	
	public void open(RoadMap roadMap) {
					
		this.setVisible(true);
	}
	public void update() {
		whTableM.setWeather((Weather) cbWeather.getSelectedItem());
		whTableM.update();
	}
	
	public Weather getWeather() {
		return (Weather) cbWeather.getSelectedItem();
	}
	private JPanel createViewPanel(JComponent c) {
		JPanel p = new JPanel(new BorderLayout());	
		p.add(new JScrollPane(c));
		return p;
	}

}
