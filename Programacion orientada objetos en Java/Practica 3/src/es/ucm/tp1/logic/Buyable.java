package es.ucm.tp1.logic;

import excepciones.NotEnoughCoinsException;

public interface Buyable {
	
	public int cost();
	
	public default boolean buy(Game game) throws NotEnoughCoinsException{	
		return game.restarMonedasPlayer(this.cost());
	};
	
}
