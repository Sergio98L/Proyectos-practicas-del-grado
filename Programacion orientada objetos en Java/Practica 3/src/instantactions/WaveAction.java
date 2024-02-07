package instantactions;

import es.ucm.tp1.logic.Collider;
import es.ucm.tp1.logic.Game;
import es.ucm.tp1.logic.InstantAction;

public class WaveAction implements InstantAction{
	
	private static final int Coste = 5;
	
	@Override
	public void execute(Game game) {
									
				for(int x=(game.getVisibility()-1);x>=0;x--) {
					for(int y=0;y<game.getRoadWidth();y++) {																
						Collider objeto = game.getObjectInPosition(game.getColJugador()+x+1, y); //Mira si hay un objeto detras del objeto que vamos a empujar
						if(objeto ==null) {//si no hay objeto en la columna siguiente seguimos
						 objeto = game.getObjectInPosition(game.getColJugador()+x, y);//Cojemos el objeto que vamos a empujar
						 	if(objeto !=null) {
						 		objeto.receiveWave();
						 	}
						}
					}
				}	
		}
	
	public static int getCoste() {
		return Coste;
	}
}
