package es.ucm.tp1.supercars.control.commands;

import es.ucm.tp1.logic.Game;
import es.ucm.tp1.logic.gameobjects.Grenade;

import java.util.Scanner;

public class ResetCommand extends Command {

	private static final String NAME = "reset";

	private static final String DETAILS = "[r]eset [<level> <seed>]";

	private static final String SHORTCUT = "r";

	private static final String HELP = "reset game";

	private int nuevaSeed;
	private String nuevaDificultad;
	
	public ResetCommand() {
		super(NAME, SHORTCUT, DETAILS, HELP);
	}
	
	public ResetCommand(String dificultad,int seed) {
		super(NAME, SHORTCUT, DETAILS, HELP);		
		this.nuevaDificultad = dificultad;
		this.nuevaSeed = seed;
	}

	@Override
	public boolean execute(Game game) {		
		game.setLevel(this.nuevaDificultad);
		game.setSeed(this.nuevaSeed);
		game.init();
		
		return true;
	}
	
	protected Command parse(String[] commandWords) {
		Command comando=null;
		String dificultad = "";
		int seed = 0;
			if ("r".equalsIgnoreCase(commandWords[0]) || "reset".equalsIgnoreCase(commandWords[0])) {
					if (commandWords.length != 3) {
						System.out.format("[ERROR]: Command %s: %s%n%n", NAME, INCORRECT_NUMBER_OF_ARGS_MSG);
					}
					else {
						commandWords[0] = SHORTCUT;
						dificultad = commandWords[1];
						seed = Integer.parseInt(commandWords[2]);
						comando = new ResetCommand(dificultad,seed);
					}
				}
		return comando;
	}
}
