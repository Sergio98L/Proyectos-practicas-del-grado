package es.ucm.tp1.supercars.control.commands;


import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

import es.ucm.tp1.logic.Game;
import excepciones.CommandExecuteException;
import excepciones.CommandParseException;

public class SaveCommand extends Command {

	private static final String NAME = "save";

	private static final String DETAILS = "sa[v]e <filename>";

	private static final String SHORTCUT = "v";

	private static final String HELP = "save game";
	
	private String filename;
	
	public SaveCommand() {
		super(NAME, SHORTCUT, DETAILS, HELP);
	}
	
	public SaveCommand(String filename) {
		super(NAME, SHORTCUT, DETAILS, HELP);
		this.filename = filename;
	}

	@Override
	public boolean execute(Game game) throws CommandExecuteException {
		
		File name = new File(this.filename + ".txt");
		try (BufferedWriter buff = new BufferedWriter (new FileWriter(name)))
		{
			buff.write("Supercars 3.0 version");
			buff.newLine();
			buff.newLine();
			game.save(buff);
			System.out.format("%s %s.%n", "Game successfully saved in file", name);
			buff.close();
			
		}
		catch (IOException x)
		{
			throw new CommandExecuteException("Game was not able to store");
		}
		return false;
	}

	@Override
	protected Command parse(String[] commandWords) throws CommandParseException //Parsea el comando
	{ 
		SaveCommand command = null;
		if ((commandWords[0].equals("save") || commandWords[0].equals("v")))
		{
			if(commandWords.length == 2)
			{
				command = new SaveCommand(commandWords[1]);
			}
			else
			{
				throw new CommandParseException("[ERROR]: Save Command :" + INCORRECT_NUMBER_OF_ARGS_MSG);
			}
		}
		return command;
	}
}
