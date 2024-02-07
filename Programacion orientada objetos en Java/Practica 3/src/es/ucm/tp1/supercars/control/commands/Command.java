package es.ucm.tp1.supercars.control.commands;

import es.ucm.tp1.logic.Game;
import excepciones.CommandExecuteException;
import excepciones.CommandParseException;

public abstract class Command {

	private static final String UNKNOWN_COMMAND_MSG = "Unknown command";

	protected static final String INCORRECT_NUMBER_OF_ARGS_MSG = "Incorrect number of arguments";

	private final String name;

	private final String shortcut;

	private final String details;

	private final String help;
	

	public Command(String name, String shortcut, String details, String help) {
		this.name = name;
		this.shortcut = shortcut;
		this.details = details;
		this.help = help;
	}

	public abstract boolean execute(Game game) throws CommandExecuteException;

	protected static final Command[] AVAILABLE_COMMANDS = { new HelpCommand(), new InfoCommand(), new UpdateCommand(),
			new MoveUpCommand(), new MoveDownCommand(), new ExitCommand(), new ResetCommand(), new TestCommand(),new ShootCommand(),new GrenadeCommand(),new WaveCommand()
			,new SerializeCommand(),new SaveCommand(),new DumpCommand(),new ShowRecordCommand(),new ShootRayCommand(),new ClearCommand(),new ExplosiveShootCommand(),new CheatCommand()};

	public static Command getCommand(String[] commandWords) throws CommandParseException {
		Command command = null;
		int i = 0;
		boolean encontrado = false;
		while (i < AVAILABLE_COMMANDS.length && !encontrado)
		{
			command = AVAILABLE_COMMANDS[i].parse(commandWords);
			if (command != null) {
				encontrado = true;
			}
			i++;
		}
		if (!encontrado) {
			throw new CommandParseException(String.format("[ERROR]: %s", UNKNOWN_COMMAND_MSG));
		}

		return command;
	}

	protected boolean matchCommandName(String name) {
		return this.shortcut.equalsIgnoreCase(name) || this.name.equalsIgnoreCase(name);
	}

	protected Command parse(String[] words)throws CommandParseException {

		if (matchCommandName(words[0])) {
			
			  if (words.length != 1) {
				  throw new CommandParseException(String.format("[ERROR]:Command %s: %s", name,INCORRECT_NUMBER_OF_ARGS_MSG));
			  }
			  else {
				  return this;
			  }
		  }
		  return null;
		}
	

	protected String getNombre() {
		return this.details;
	}

	protected String gethelp() {
		return this.help;
	}


}
