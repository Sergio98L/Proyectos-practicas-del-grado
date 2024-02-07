package es.ucm.tp1.supercars.control.commands;

import es.ucm.tp1.logic.Game;
import excepciones.CommandExecuteException;
import excepciones.CommandParseException;
import excepciones.UnvalidCheatNumberException;


public class CheatCommand extends Command {

	private static final String NAME = "cheat";

	private static final String DETAILS = "Cheat [1..5]";

	private static final String SHORTCUT = "1 2 3 4 5";

	private static final String HELP = "Removes all elements of last visible column, and adds an Advanced Object";

	private int x;

	public CheatCommand() {
		super(NAME, SHORTCUT, DETAILS, HELP);
	}
	public CheatCommand(int x) {
		super(NAME, SHORTCUT, DETAILS, HELP);
		this.x = x;
	}

	@Override
	public boolean execute(Game game)throws CommandExecuteException {
		try {
			game.borrarUltColumVisible();
			game.cheatGame(this.x);
		}
		catch(UnvalidCheatNumberException x){
			System.out.println(x.getMessage());
			throw new CommandExecuteException ("[ERROR]: Cheat Command : Failed to add cheat");
		}
		
		return true;
	}

	protected Command parse(String[] commandWords) throws CommandParseException {

		Command comando=null;
		int numero = 0;
		
		if (commandWords.length == 1){
			try {			
				numero = Integer.parseInt(commandWords[0]);
				comando = new CheatCommand(numero);
			}
			catch(NumberFormatException x){
				throw new CommandParseException("[ERROR]: Unknown command");		
			}
		}else {
			throw new CommandParseException("[ERROR]: Cheat Command :" + INCORRECT_NUMBER_OF_ARGS_MSG);						
		}

		return comando;
		
	}
}
