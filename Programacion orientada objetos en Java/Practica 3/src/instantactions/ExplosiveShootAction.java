package instantactions;


import es.ucm.tp1.logic.Collider;
import es.ucm.tp1.logic.Game;
import es.ucm.tp1.logic.InstantAction;

public class ExplosiveShootAction implements InstantAction{

	private static final int Coste = 10;
	@Override
	public void execute(Game game) {

			//while para recorrer la linea actual del player
			int i=0;
			boolean disparoAcertado = false;
					
			while(i<game.getVisibility() && !disparoAcertado){
				Collider objeto = game.getObjectInPosition(game.getColJugador()+i, game.getPlayerY());
				if(objeto != null) {
					disparoAcertado = objeto.receiveShoot();
					for(int z= 0 ;z<3 ;z++) {
						for(int j=0;j<3;j++) {							
							objeto = game.getObjectInPosition(game.getColJugador()+i-1+z,  game.getPlayerY()-1+j);						
							if(objeto != null) {
								objeto.receiveExplosion();
							}	
							
						}
					}
					
				}	
				i++;
			}	
		}
	public static int getCoste() {
		return Coste;
	}

}
