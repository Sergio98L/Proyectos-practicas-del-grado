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

public class RoadContaminationHistoryDialog extends JDialog{

	
	private static final long serialVersionUID = 1L;
	private JSpinner jsCont;
	private ContHistoryTableModel tableModel;
	private int estado;
	
	public RoadContaminationHistoryDialog(Frame parent,ContHistoryTableModel tableModel) {
		super(parent,true); //Para que sea modal y no se pueda clicar fuera del cuadrado
		this.tableModel = tableModel;
		initGUI();	
		
	}
	
	private void initGUI() {
		jsCont = new JSpinner();
		
		this.setTitle("RoadsContaminationHistory");
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
					
			JLabel txtTicks = new JLabel("Contamination Limit");
			jsCont = new JSpinner(new SpinnerNumberModel(1000, 0, Integer.MAX_VALUE, 1));
			jsCont.setPreferredSize(new Dimension(80, 25));
			
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
			botonUpdate.setToolTipText("Crea el nuevo evento");
			botonUpdate.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {				
				update();
			}});
			
			
		JPanel roadsView = createViewPanel(new JTable(tableModel));
		roadsView.setPreferredSize(new Dimension(500, 200));
			
			
		//Añadir al buttonPanel
		buttonPanel.add(botonCancel);
		buttonPanel.add(botonUpdate);
			
		//Añadir al secundaryPanel
		secondaryPanel.add(txtTicks);
		secondaryPanel.add(jsCont);
		
		//Añadir al mainPanel
		mainPanel.add(txtPanel);
		mainPanel.add(secondaryPanel);
		mainPanel.add(buttonPanel);
		mainPanel.add(roadsView);
		
		//Añadir al JDialog
		this.setDefaultCloseOperation(HIDE_ON_CLOSE);
		this.setContentPane(mainPanel);	
		this.setResizable(false);
		//this.setVisible(true);	 //No poner ser visible porque si no crea una ventana vacia extra
		this.pack();
		this.setLocationRelativeTo(null); //Para que aparezca siempre en medio de la pantalla
	}
	private void cancel() {
		this.setVisible(false);
		this.estado =0;
	}
	public void setVisible() {
		this.setVisible(true);
	}
	public void update() {
		this.tableModel.setmaxCont((int) jsCont.getValue());
		this.tableModel.fireTableDataChanged();
	}
	public Integer getTicks() {
		return (Integer) jsCont.getValue();
	}
	private JPanel createViewPanel(JComponent c) {
		JPanel p = new JPanel(new BorderLayout());	
		p.add(new JScrollPane(c));
		return p;
	}
}
