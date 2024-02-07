package es.ucm.tp1.supercars.control.commands;

import es.ucm.tp1.logic.Game;
import excepciones.CommandExecuteException;
import excepciones.CommandParseException;
import excepciones.InputOutputRecordException;
import excepciones.InvalidLevelException;

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

	public ResetCommand(String dificultad, int seed) {
		super(NAME, SHORTCUT, DETAILS, HELP);
		this.nuevaDificultad = dificultad;
		this.nuevaSeed = seed;
	}

	@Override
	public boolean execute(Game game) throws CommandExecuteException {
			
		try{
			game.setLevel(this.nuevaDificultad);
			game.setSeed(this.nuevaSeed);
			game.init();
			game.cargarRecord();
		}catch(InputOutputRecordException x){
			System.out.println(x.getMessage());
			throw new CommandExecuteException ("[ERROR]: Failed to reset game", x);	
		} catch (InvalidLevelException e) {
			System.out.println(e.getMessage());
			throw new CommandExecuteException ("[ERROR]: Failed to reset game", e);	
		}

		return true;
	}

	protected Command parse(String[] commandWords) throws CommandParseException {
		Command comando = null;
		String dificultad = "";
		int seed = 0;
		if ("r".equalsIgnoreCase(commandWords[0]) || "reset".equalsIgnoreCase(commandWords[0])) {
			if (commandWords.length == 3) {
				commandWords[0] = SHORTCUT;		
				try{
					dificultad = commandWords[1];
					seed = Integer.parseInt(commandWords[2]);
				}catch(NumberFormatException x) {
					throw new CommandParseException("[ERROR]: Reset Command : Seed must be a number");
				}
				comando = new ResetCommand(dificultad, seed);
				} else {
					throw new CommandParseException("[ERROR]: Reset Command :" + INCORRECT_NUMBER_OF_ARGS_MSG);
			}
		}
		return comando;
	}
}
