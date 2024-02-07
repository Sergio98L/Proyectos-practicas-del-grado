package instantactions;


import es.ucm.tp1.logic.Game;
import es.ucm.tp1.logic.InstantAction;

public class ThunderAction implements InstantAction{


	@Override
	public void execute(Game game) {
			int x= game.getRandomCol();
			int y= game.getRandomLane();
			String simbolo =game.positionToString(x, y);
			
			if(game.impactoThunder(x+game.getmovJugador(), y)) {
				System.out.println("Thunder hit position: " +"("+(x+1)+" , "+y+")" + "-> "+ simbolo +" hit");
			}else {
				System.out.println("Thunder hit position: " +"("+(x+1)+" , "+y+")");
			}
		}
}
