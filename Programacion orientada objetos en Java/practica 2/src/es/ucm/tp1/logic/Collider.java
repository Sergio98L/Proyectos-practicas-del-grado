package es.ucm.tp1.logic;

import es.ucm.tp1.logic.gameobjects.Player;

public interface Collider {


	boolean receiveCollision(Player player);
	
	boolean receiveShoot();
	boolean receiveExplosion();

	boolean doCollision();

}
