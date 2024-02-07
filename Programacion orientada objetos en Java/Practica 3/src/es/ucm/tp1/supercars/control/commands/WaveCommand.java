package es.ucm.tp1.supercars.control.commands;

import es.ucm.tp1.logic.Buyable;
import es.ucm.tp1.logic.Game;
import excepciones.CommandExecuteException;
import excepciones.NotEnoughCoinsException;
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
	public boolean execute(Game game) throws CommandExecuteException {
		Buyable compra= new WaveCommand();
		
		try {
			compra.buy(game);
			game.execute(new WaveAction());
			game.updateGame();
		}catch (NotEnoughCoinsException x) {
			System.out.println(x.getMessage());
			throw new CommandExecuteException ("[ERROR]: Failed to use wave", x);		
		}
		return true;
	}

	@Override
	public int cost() {
		return WaveAction.getCoste();
	}

}
