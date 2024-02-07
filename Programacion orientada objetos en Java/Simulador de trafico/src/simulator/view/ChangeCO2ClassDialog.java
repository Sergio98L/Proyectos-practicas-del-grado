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
import simulator.model.RoadMap;
import simulator.model.Vehicle;

public class ChangeCO2ClassDialog extends JDialog{

	
	private static final long serialVersionUID = 1L;
	private JComboBox<Vehicle> cbVehiculos;
	private JComboBox<Integer> cbContaminacion;
	private JSpinner jsTiks;
	private int estado;
	
	public ChangeCO2ClassDialog(Frame parent) {
		super(parent,true); //Para que sea modal y no se pueda clicar fuera del cuadrado
				
		initGUI();	
		
	}
	
	private void initGUI() {
		cbVehiculos = new JComboBox<Vehicle>();
		cbContaminacion = new JComboBox<Integer>();
		jsTiks = new JSpinner();
		
		this.setTitle("Change C02 Class");
		//main Panel
		JPanel mainPanel = new JPanel();
		mainPanel.setLayout(new BoxLayout(mainPanel, BoxLayout.Y_AXIS));
		
		
			//Label
			JPanel txtPanel = new JPanel();
			txtPanel.setLayout(new FlowLayout());
			JLabel txtVentana = new JLabel("<html>Schedule an event to change the C02 class of a vehicle after a given number of simulation ticks from now.</html>");
			txtVentana.setAlignmentX(CENTER_ALIGNMENT);
			txtPanel.add(txtVentana);
			
		//secondary Panel
		JPanel secondaryPanel = new JPanel();
		secondaryPanel.setLayout(new FlowLayout());
		
			//CbmBox JSpinner
			JLabel txtVehicle = new JLabel("Vehicle");
			cbVehiculos.setModel(new DefaultComboBoxModel<Vehicle>());
			cbVehiculos.setPreferredSize(new Dimension(80, 25));
			
			JLabel txtC02 = new JLabel("CO2 Class");
			cbContaminacion.setModel(new DefaultComboBoxModel<Integer>());
			cbContaminacion.setPreferredSize(new Dimension(80, 25));
			
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
		secondaryPanel.add(cbVehiculos);
		secondaryPanel.add(txtC02);
		secondaryPanel.add(cbContaminacion);
		secondaryPanel.add(txtTicks);
		secondaryPanel.add(jsTiks);
		
		//Añadir al mainPanel
		mainPanel.add(txtPanel);
		mainPanel.add(secondaryPanel);
		mainPanel.add(buttonPanel);
		
		//Inicizalizar C02 CB
		
		for(int i=0;i<10;i++) {
			cbContaminacion.addItem(i);
		}
		
		//Añadir al JDialog
		this.setDefaultCloseOperation(HIDE_ON_CLOSE);
		this.setContentPane(mainPanel);	
		this.setResizable(false);
		//this.setVisible(true); //No poner ser visible porque si no crea una ventana vacia extra
		this.pack();
		this.setLocationRelativeTo(null); //Para que aparezca siempre en medio de la pantalla
	}
	private void cancel() {
		this.setVisible(false);
		this.estado =0;
	}
	private void ok() {
		if(this.cbVehiculos.getSelectedItem() !=null) {
			this.setVisible(false);
			this.estado =1;
		}
		
	}
	public int open(RoadMap roadMap) {
		
		if(roadMap !=null) {			
			for(Vehicle vehiculo : roadMap.getVehicles()) {
				cbVehiculos.addItem(vehiculo);
			}	
		}
		this.setVisible(true);
		return this.estado;
		
	}

	public Vehicle getVehicle() {
		return (Vehicle) cbVehiculos.getSelectedItem();
	}
	public Integer getCO2Class() {
		return (Integer) cbContaminacion.getSelectedItem();
	}
	public Integer getTicks() {
		return (Integer) jsTiks.getValue();
	}
}
