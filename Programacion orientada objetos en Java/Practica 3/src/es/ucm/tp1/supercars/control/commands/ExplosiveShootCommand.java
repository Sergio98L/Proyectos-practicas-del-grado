package es.ucm.tp1.supercars.control.commands;

import es.ucm.tp1.logic.Buyable;
import es.ucm.tp1.logic.Game;
import excepciones.CommandExecuteException;
import excepciones.NotEnoughCoinsException;
import instantactions.ExplosiveShootAction;


public class ExplosiveShootCommand extends Command implements Buyable{

	private static final String NAME = "Explosive shoot";

	private static final String DETAILS = "[es]hoot";

	private static final String SHORTCUT = "es";

	private static final String HELP = "shoot explosive bullet";

	public ExplosiveShootCommand() {
		super(NAME, SHORTCUT, DETAILS, HELP);
	}

	@Override
	public boolean execute(Game game) throws CommandExecuteException {
		Buyable compra= new ExplosiveShootCommand();
		try {
			compra.buy(game);
			game.execute(new ExplosiveShootAction());
			game.updateGame();
		}catch (NotEnoughCoinsException x) {
			System.out.println(x.getMessage());
			throw new CommandExecuteException ("[ERROR]: Failed to shoot", x);		
		}
		return true;
	}

	@Override
	public int cost() {
		return ExplosiveShootAction.getCoste();
	}

}
