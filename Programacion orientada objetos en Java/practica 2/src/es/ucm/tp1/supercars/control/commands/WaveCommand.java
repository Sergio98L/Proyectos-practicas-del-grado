package es.ucm.tp1.supercars.control.commands;

import es.ucm.tp1.logic.Buyable;
import es.ucm.tp1.logic.Game;
import instantactions.WaveAction;


public class WaveCommand extends Command implements Buyable{

	private static final String NAME = "wave";

	private static final String DETAILS = "[w]ave";

	private static final String SHORTCUT = "w";

	private static final String HELP = "do wave";

	public WaveCommand() {
		super(NAME, SHORTCUT, DETAILS, HELP);
	}

	@Override
	public boolean execute(Game game) {
		Buyable compra= new WaveCommand();
		
		if(compra.buy(game)) {
			game.execute(new WaveAction());
			game.updateGame();
			return true;
		}else {
			System.out.println("No se pudo usar Wave, monedas insuficientes");
			return false;
		}
	
	}

	@Override
	public int cost() {
		// TODO Auto-generated method stub
		return WaveAction.getCoste();
	}

}
