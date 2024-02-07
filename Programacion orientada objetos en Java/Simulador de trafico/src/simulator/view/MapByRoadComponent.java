package simulator.view;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Image;
import java.awt.RenderingHints;
import java.io.File;
import java.io.IOException;
import java.util.List;

import javax.imageio.ImageIO;
import javax.swing.JPanel;
import javax.swing.SwingUtilities;

import simulator.control.Controller;
import simulator.model.Event;
import simulator.model.Road;
import simulator.model.RoadMap;
import simulator.model.TrafficSimObserver;
import simulator.model.Vehicle;
import simulator.model.VehicleStatus;

public class MapByRoadComponent extends JPanel  implements TrafficSimObserver{
	
	
	private static final long serialVersionUID = 1L;
	private static final Color _BG_COLOR = Color.WHITE;
	private static final Color _NEGRO = Color.BLACK;
	private static final Color _JUNCTION_COLOR = Color.BLUE;
	private static final Color _GREEN_LIGHT_COLOR = Color.GREEN;
	private static final Color _RED_LIGHT_COLOR = Color.RED;
	private static final Color _JUNCTION_LABEL_COLOR = new Color(200, 100, 0);

	private RoadMap _map;
	private Image[] _cont;
	private Image _car;
	
		public MapByRoadComponent(Controller ctrl) {
			
			ctrl.addObserver(this);
			initGUI();
		}
		private void initGUI() {
			_car = loadImage("car.png");
			_cont = new Image[6];
					
			for (int i=0;i<6;i++)
			_cont[i] = loadImage("cont_"+ i +".png");
			
			setPreferredSize(new Dimension(300, 200));
		}
		
		public void paintComponent(Graphics graphics) {
			super.paintComponent(graphics);
			Graphics2D g = (Graphics2D) graphics;
			g.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
			g.setRenderingHint(RenderingHints.KEY_TEXT_ANTIALIASING, RenderingHints.VALUE_TEXT_ANTIALIAS_ON);

			// clear with a background color
			g.setColor(_BG_COLOR);
			g.clearRect(0, 0, getWidth(), getHeight());

			if (_map == null || _map.getJunctions().size() == 0) {
				g.setColor(Color.red);
				g.drawString("No map yet!", getWidth() / 2 - 50, getHeight() / 2);
			} else {
				drawMap(g);
			}
		}
		
		private void drawMap(Graphics2D g) {
			int i =0;
			int y =0;
			int x1 = 50;
			int x2 = getWidth() - 100;
			
			for(Road r: _map.getRoads()) {
				
				y =(i+1)*50;
				
				Color colorEtiqueta = _NEGRO;
				g.setColor(colorEtiqueta);			
				g.drawLine(x1, y, x2, y);
	
				Color colorCruceOrigen = _JUNCTION_COLOR;					
				Color colorCruceDestino = _RED_LIGHT_COLOR;		
				int idx = r.getDest().getGreenLightIndex();
				if (idx != -1 && r.equals(r.getDest().getInRoads().get(idx))) {
					colorCruceDestino = _GREEN_LIGHT_COLOR;
				}
				
				g.setColor(colorCruceOrigen);
				g.fillOval(x1 - 1, y - 6, 14, 14);
				g.setColor(colorCruceDestino);
				g.fillOval(x2 - 1, y - 6, 14, 14);
				
				
				g.setColor(_JUNCTION_LABEL_COLOR);
				g.drawString(r.getSrc().getId(), x1, y - 6);
				g.drawString(r.getDest().getId(), x2, y - 6);
				
				
				drawVehicles(g,r,y,x1,x2);
				
				g.setColor(_NEGRO);
				g.drawString(r.getId(), x1-25, y+3);
				
				
				
				Image weather = loadImage("sun.png");
				
				switch(r.getWeather()){
				
				case SUNNY:
					weather = loadImage("sun.png");
					break;
				case CLOUDY:
					weather = loadImage("cloud.png");
					break;
				case RAINY:
					weather = loadImage("rain.png");
					break;
				case WINDY:
					weather = loadImage("wind.png");
					break;
				case STORM:
					weather = loadImage("storm.png");
					break;
					
					default:
					break;
					
				}
				g.drawImage(weather, x2+15, y-15, 32, 32, this);
				
				
				int C = (int) Math.floor(Math.min((double) r.getTotalCO2()/(1.0 + (double) r.getContLimit()),1.0)/0.19);
				Image cont = loadImage("cont_"+C+".png");
				g.drawImage(cont, x2+50, y -15, 32, 32, this);
				
				
				i++;
				
			}
			
		}
		private void drawVehicles(Graphics g, Road r, int y,int x1,int x2) {
					
			for (Vehicle v : r.getVehicles()) {
				if (v.getStatus() != VehicleStatus.ARRIVED) {

										
					// The calculation below compute the coordinate (vX,vY) of the vehicle on the
					// corresponding road. It is calculated relatively to the length of the road, and
					// the location on the vehicle.
									
								
					int x = x1 + (int) ((x2 - x1) * ((double) v.getLocation() / (double) r.getLength()));
					
					
					// Choose a color for the vehcile's label and background, depending on its
					// contamination class
					int vLabelColor = (int) (25.0 * (10.0 - (double) v.getContClass()));
					g.setColor(new Color(0, vLabelColor, 0));
					
					g.drawImage(_car, x, y - 6, 16, 16, this);
					g.drawString(v.getId(), x, y - 6);				
					
				}
			}
		}
		private Image loadImage(String img) {
			Image i = null;
			try {
				return ImageIO.read(new File("resources/icons/" + img));
			} catch (IOException e) {
			}
			return i;
		}
		
		
		public void update(RoadMap map) {
			SwingUtilities.invokeLater(() -> {
				_map = map;
				repaint();
			});
		}

		@Override
		public void onAdvanceStart(RoadMap map, List<Event> events, int time) {
		}

		@Override
		public void onAdvanceEnd(RoadMap map, List<Event> events, int time) {
			update(map);
		}

		@Override
		public void onEventAdded(RoadMap map, List<Event> events, Event e, int time) {
			update(map);
		}

		@Override
		public void onReset(RoadMap map, List<Event> events, int time) {
			update(map);
		}

		@Override
		public void onRegister(RoadMap map, List<Event> events, int time) {
			update(map);
		}

		@Override
		public void onError(String err) {
		}
}
