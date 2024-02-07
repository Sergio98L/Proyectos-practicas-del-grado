package instantactions;

import es.ucm.tp1.logic.Collider;
import es.ucm.tp1.logic.Game;
import es.ucm.tp1.logic.InstantAction;

public class ExplosionAction implements InstantAction{

	private int x,y;
	
	
	public ExplosionAction(int x, int y) {
		this.x = x;
		this.y = y;	
	}
	
	@Override
	public void execute(Game game) {
			
			//explotan todos los obstaculos adyacentes a la granada 3x3
		Collider objeto = null;
		
			for(int i= 0 ;i<3 ;i++) {
				for(int j=0;j<3;j++) {
					
					objeto = null;
					objeto = game.getObjectInPosition(this.x-1+i, this.y-1+j);
					
					if(objeto != null) {
						objeto.receiveExplosion();
					}	
				}
			}			
		}
}
