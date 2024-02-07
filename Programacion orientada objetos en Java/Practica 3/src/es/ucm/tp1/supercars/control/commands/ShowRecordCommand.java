package es.ucm.tp1.supercars.control.commands;

import es.ucm.tp1.logic.Game;
import excepciones.CommandExecuteException;
import excepciones.CommandParseException;
import excepciones.ShowRecordException;

public class ShowRecordCommand extends Command {

	private static final String NAME = "record";

	private static final String DETAILS = "rec[o]rd";

	private static final String SHORTCUT = "o";

	private static final String HELP = "show level record";

	public ShowRecordCommand() {
		super(NAME, SHORTCUT, DETAILS, HELP);
	}

	@Override
	public boolean execute(Game game) throws CommandExecuteException {

		try{
			game.showRecord();
		}catch(ShowRecordException x){
			System.out.println(x.getMessage());
			throw new CommandExecuteException ("[ERROR]: Failed to show record", x);
		}
		
		return false;
	}
	protected Command parse(String[] commandWords) throws CommandParseException //Parsea el comando
	{ 
		ShowRecordCommand command = null;
		if ((commandWords[0].equals("record") || commandWords[0].equals("o")))
		{
			if(commandWords.length == 1)
			{
				command = new ShowRecordCommand();
			}
			else
			{
				throw new CommandParseException("[ERROR]: Show Record Command :" + INCORRECT_NUMBER_OF_ARGS_MSG);
			}
		}
		return command;
	}

}
