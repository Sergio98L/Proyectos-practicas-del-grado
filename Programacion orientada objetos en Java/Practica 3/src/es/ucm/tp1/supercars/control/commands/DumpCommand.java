
package es.ucm.tp1.supercars.control.commands;


import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import es.ucm.tp1.logic.Game;
import excepciones.CommandExecuteException;
import excepciones.CommandParseException;




public class DumpCommand extends Command{

	private static final String NAME = "dump";

	private static final String DETAILS = "[d]ump <filename>";

	private static final String SHORTCUT = "d";

	private static final String HELP = "Shows the content of a saved file";
	
	private String filename;
	

	public DumpCommand() {
		super(NAME, SHORTCUT, DETAILS, HELP);
		
	}
	public DumpCommand(String filename) {
		super(NAME, SHORTCUT, DETAILS, HELP);
		this.filename = filename;
	}

	@Override
	public boolean execute(Game game) throws CommandExecuteException {
		
		File name = new File(this.filename + ".txt");
		try (BufferedReader buff = new BufferedReader (new FileReader(name)))
		{
			
			String linea;
	         while((linea=buff.readLine())!=null)
	            System.out.println(linea);
	         
			System.out.format("%s %s.%n", "File successfully loaded", name);
			buff.close();
			
		}
		catch (IOException x)
		{
			throw new CommandExecuteException("File was not able to load");
		}
		return false;

	}
	protected Command parse(String[] commandWords) throws CommandParseException //Parsea el comando
	{ 
		DumpCommand command = null;
		if ((commandWords[0].equals("dump") || commandWords[0].equals("d")))
		{
			if(commandWords.length == 2)
			{
				command = new DumpCommand(commandWords[1]);
			}
			else
			{
				throw new CommandParseException("[ERROR]: Dump Command :" + INCORRECT_NUMBER_OF_ARGS_MSG);
			}
		}
		return command;
	}
}
