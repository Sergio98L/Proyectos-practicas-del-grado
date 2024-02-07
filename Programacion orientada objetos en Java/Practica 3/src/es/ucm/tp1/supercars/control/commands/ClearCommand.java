package es.ucm.tp1.supercars.control.commands;

import es.ucm.tp1.logic.Game;

public class ClearCommand extends Command {

	private static final String NAME = "clear";

	private static final String DETAILS = "Clear [0]";

	private static final String SHORTCUT = "0";

	private static final String HELP = "Clears the road";

	public ClearCommand() {
		super(NAME, SHORTCUT, DETAILS, HELP);
	}

	@Override
	public boolean execute(Game game) {
		game.clearCarretera();
		return true;
	}

}
