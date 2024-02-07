package es.ucm.tp1.supercars.control.commands;

import es.ucm.tp1.logic.Buyable;
import es.ucm.tp1.logic.Game;
import excepciones.CommandExecuteException;
import excepciones.NotEnoughCoinsException;
import instantactions.ShootAction;
import instantactions.ShootRayAction;


public class ShootRayCommand extends Command implements Buyable{

	private static final String NAME = "shoot";

	private static final String DETAILS = "[ra]hoot";

	private static final String SHORTCUT = "ra";

	private static final String HELP = "shoot bullet";

	public ShootRayCommand() {
		super(NAME, SHORTCUT, DETAILS, HELP);
	}

	@Override
	public boolean execute(Game game) throws CommandExecuteException {
		Buyable compra= new ShootRayCommand();
		try {
			compra.buy(game);
			game.execute(new ShootRayAction());
			game.updateGame();
		}catch (NotEnoughCoinsException x) {
			System.out.println(x.getMessage());
			throw new CommandExecuteException ("[ERROR]: Failed to shoot", x);		
		}
		return true;
	}

	@Override
	public int cost() {
		return ShootAction.getCoste();
	}

}
