package es.ucm.tp1.supercars.control.commands;


import es.ucm.tp1.logic.Game;
import excepciones.CommandParseException;

public class UpdateCommand extends Command {

	private static final String NAME = "update";

	private static final String DETAILS = "[n]one | []";

	private static final String SHORTCUT = "n";

	private static final String HELP = "update";

	public UpdateCommand() {
		super(NAME, SHORTCUT, DETAILS, HELP);
	}

	@Override
	public boolean execute(Game game) {
		game.comprobarColision();
		game.addColJugador();
		game.comprobarColision();
		game.updateGame();	
		return true;
	}

	@Override
	protected Command parse(String[] commandWords) throws CommandParseException //Parsea el comando
	{ 
		UpdateCommand command = null;
		if ((commandWords[0].equals("none") || commandWords[0].equals("") || commandWords[0].equals("n")))
		{
			if(commandWords.length == 1)
			{
				command = new UpdateCommand();
			}
			else
			{
				throw new CommandParseException("[ERROR]: Update Command :" + INCORRECT_NUMBER_OF_ARGS_MSG);
			}
		}
		return command;
	}
}
