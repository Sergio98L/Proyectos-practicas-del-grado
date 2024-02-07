package es.ucm.tp1.supercars.control.commands;

import es.ucm.tp1.logic.Buyable;
import es.ucm.tp1.logic.Game;
import instantactions.ShootAction;


public class ShootCommand extends Command implements Buyable{

	private static final String NAME = "shoot";

	private static final String DETAILS = "[s]hoot";

	private static final String SHORTCUT = "s";

	private static final String HELP = "shoot bullet";

	public ShootCommand() {
		super(NAME, SHORTCUT, DETAILS, HELP);
	}

	@Override
	public boolean execute(Game game) {
		Buyable compra= new ShootCommand();
		
		if(compra.buy(game)) {
			game.execute(new ShootAction());
			game.updateGame();
			return true;
		}else {
			System.out.println("No se pudo usar Shoot, monedas insuficientes");
			return false;
		}
	}

	@Override
	public int cost() {
		// TODO Auto-generated method stub
		return ShootAction.getCoste();
	}

}
