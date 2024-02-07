package simulator.view;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.Frame;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

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

import simulator.model.RoadMap;
import simulator.model.Vehicle;

public class VehicleHistoryDialog extends JDialog{

	
	private static final long serialVersionUID = 1L;
	private JSpinner jsTiks;
	private VehicleHistoryTableModel modeloTabla;
	
	public VehicleHistoryDialog(Frame parent,VehicleHistoryTableModel modeloTabla) {
		super(parent,true); //Para que sea modal y no se pueda clicar fuera del cuadrado
		this.modeloTabla = modeloTabla;	
		initGUI();	
		
	}
	
	private void initGUI() {
		jsTiks = new JSpinner();
		
		this.setTitle("Change C02 Class");
		//main Panel
		JPanel mainPanel = new JPanel();
		mainPanel.setLayout(new BoxLayout(mainPanel, BoxLayout.Y_AXIS));
		
		
			//Label
			JPanel txtPanel = new JPanel();
			txtPanel.setLayout(new FlowLayout());
			JLabel txtVentana = new JLabel("<html>Historial de vehiculos.</html>");
			txtVentana.setAlignmentX(CENTER_ALIGNMENT);
			txtPanel.add(txtVentana);
			
		//secondary Panel
		JPanel secondaryPanel = new JPanel();
		secondaryPanel.setLayout(new FlowLayout());
		
			//CbmBox JSpinner
	
		
			JLabel txtTicks = new JLabel("Speed Limit");
			jsTiks = new JSpinner(new SpinnerNumberModel(10, 1, Integer.MAX_VALUE, 1));
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
			JButton botonOk = new JButton("Update");
			botonOk.setToolTipText("Crea el nuevo evento");
			botonOk.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {				
				update();
			}});
			
			
		JPanel vehiculesView = createViewPanel(new JTable(this.modeloTabla));
		vehiculesView.setPreferredSize(new Dimension(500, 200));
		
		
		
		//Añadir al buttonPanel
		buttonPanel.add(botonCancel);
		buttonPanel.add(botonOk);
			
		//Añadir al secundaryPanel


		secondaryPanel.add(txtTicks);
		secondaryPanel.add(jsTiks);
		
		//Añadir al mainPanel
		mainPanel.add(txtPanel);
		mainPanel.add(secondaryPanel);
		mainPanel.add(buttonPanel);
		mainPanel.add(vehiculesView);
		
		
		
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

	}
	private void update() {
		this.modeloTabla.setSpeed(this.getTicks());
		this.modeloTabla.fireTableDataChanged();
	}
	public void open(RoadMap roadMap) {
		
		
		this.setVisible(true);
		
		
	}
	private JPanel createViewPanel(JComponent c) {
		JPanel p = new JPanel(new BorderLayout());		
		p.add(new JScrollPane(c));
		return p;
	}
	public Integer getTicks() {
		return (Integer) jsTiks.getValue();
	}
}
