package instantactions;

import es.ucm.tp1.logic.Game;
import es.ucm.tp1.logic.InstantAction;

public class WaveAction implements InstantAction{
	
	private static final int Coste = 5;
	
	@Override
	public void execute(Game game) {
									
				for(int x=(game.getVisibility()-1);x>0;x--) {
					for(int y=0;y<game.getRoadWidth();y++) {						
						game.empujarObjetos(game.getmovJugador()+x, y);
					}
				}	
		}
	
	public static int getCoste() {
		return Coste;
	}
}
