package instantactions;


import es.ucm.tp1.logic.Collider;
import es.ucm.tp1.logic.Game;
import es.ucm.tp1.logic.InstantAction;

public class ShootAction implements InstantAction{

	private static final int Coste = 1;
	@Override
	public void execute(Game game) {

			//while para recorrer la linea actual del player
			int i=0;
			boolean disparoAcertado = false;
					
			while(i<game.getVisibility() && !disparoAcertado){
				Collider objeto = game.getObjectInPosition(game.getColJugador()+i, game.getPlayerY());
				if(objeto != null) {
					disparoAcertado = objeto.receiveShoot();
				}	
				i++;
			}	
		}
	public static int getCoste() {
		return Coste;
	}

}
