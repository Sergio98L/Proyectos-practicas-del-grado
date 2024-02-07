package es.ucm.tp1.supercars.control.commands;

import es.ucm.tp1.logic.Game;

public class HelpCommand extends Command {

	private static final String NAME = "help";

	private static final String DETAILS = "[h]elp";

	private static final String SHORTCUT = "h";

	private static final String HELP = "show this help";

	public HelpCommand() {
		super(NAME, SHORTCUT, DETAILS, HELP);
	}

	@Override
	public boolean execute(Game game) {

		String buffer = "Available commands:";
		System.out.println(buffer.toString());
		for (int i = 0; i < AVAILABLE_COMMANDS.length; i++) {
			buffer = AVAILABLE_COMMANDS[i].getNombre() + ": " + AVAILABLE_COMMANDS[i].gethelp();
			System.out.println(buffer);
		}

		return false;
	}

}
