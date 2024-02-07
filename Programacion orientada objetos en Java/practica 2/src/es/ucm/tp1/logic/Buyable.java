package es.ucm.tp1.logic;

public interface Buyable {
	
	public int cost();
	
	public default boolean buy(Game game){	
		return game.restarMonedasPlayer(this.cost());
	// TODO add your code
	};
	
}
