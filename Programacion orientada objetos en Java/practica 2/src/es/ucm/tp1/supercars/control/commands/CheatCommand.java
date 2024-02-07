package es.ucm.tp1.supercars.control.commands;


import es.ucm.tp1.logic.Game;

public class CheatCommand extends Command {

	private static final String NAME = "cheat";

	private static final String DETAILS = "Cheat [1..5]";

	private static final String SHORTCUT = "1 2 3 4 5";

	private static final String HELP = "Removes all elements of last visible column, and adds an Advanced Object";
	
	private static int CHEATNUMBER = 0;

	public CheatCommand() {
		super(NAME, SHORTCUT, DETAILS, HELP);
	}

	@Override
	public boolean execute(Game game) {
		game.borrarUltColumVisible();
		game.cheatGame(CHEATNUMBER);		
		return true;
	}
	protected Command parse(String[] commandWords) {
		if ("1".equalsIgnoreCase(commandWords[0])) {
			commandWords[0] = SHORTCUT;
			CHEATNUMBER = 1;
		}else if("2".equalsIgnoreCase(commandWords[0])) {
			commandWords[0] = SHORTCUT;
			CHEATNUMBER = 2;
		}else if("3".equalsIgnoreCase(commandWords[0])) {
			commandWords[0] = SHORTCUT;
			CHEATNUMBER = 3;
		}else if("4".equalsIgnoreCase(commandWords[0])) {
			commandWords[0] = SHORTCUT;
			CHEATNUMBER = 4;
		}else if("5".equalsIgnoreCase(commandWords[0])) {
			commandWords[0] = SHORTCUT;
			CHEATNUMBER = 5;
		}

		return super.parse(commandWords);
	}
}
