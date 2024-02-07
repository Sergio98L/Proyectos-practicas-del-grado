package es.ucm.tp1.supercars.control.commands;


import es.ucm.tp1.logic.Game;
import excepciones.CommandParseException;

public class SerializeCommand extends Command {

	private static final String NAME = "serialize";

	private static final String DETAILS = "seriali[z]e";

	private static final String SHORTCUT = "z";

	private static final String HELP = "Serializes the board";

	public SerializeCommand() {
		super(NAME, SHORTCUT, DETAILS, HELP);
	}

	@Override
	public boolean execute(Game game) {
		System.out.print(game.serialize());
		return false;
	}

	@Override
	protected Command parse(String[] commandWords) throws CommandParseException //Parsea el comando
	{ 
		SerializeCommand command = null;
		if ((commandWords[0].equals("serialize") || commandWords[0].equals("z")))
		{
			if(commandWords.length == 1)
			{
				command = new SerializeCommand();
			}
			else
			{
				throw new CommandParseException("[ERROR]: Update Command :" + INCORRECT_NUMBER_OF_ARGS_MSG);
			}
		}
		return command;
	}
}
