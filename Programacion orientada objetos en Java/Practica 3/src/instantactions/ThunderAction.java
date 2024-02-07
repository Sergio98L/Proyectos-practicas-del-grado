package instantactions;


import es.ucm.tp1.logic.Collider;
import es.ucm.tp1.logic.Game;
import es.ucm.tp1.logic.InstantAction;

public class ThunderAction implements InstantAction{

	@Override
	public void execute(Game game) {
			int x= game.getRandomCol();
			int y= game.getRandomLane();
			String simbolo =game.positionToString(x, y);//no se suma la col del player porque se suma dentro del metodo
								
			boolean impacto = false;
			
				Collider objeto = game.getObjectInPosition(game.getColJugador()+x, y);
				if(objeto != null) {
					impacto = objeto.receiveThunder();
				}
				if(impacto) {
					System.out.println("Thunder hit position: " +"("+(x+1)+" , "+y+")" + "-> "+ simbolo +" hit");
				}else {
					System.out.println("Thunder hit position: " +"("+(x+1)+" , "+y+")");
				}
		}
}
