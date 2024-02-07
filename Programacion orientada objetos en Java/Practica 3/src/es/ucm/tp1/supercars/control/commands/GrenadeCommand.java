package es.ucm.tp1.supercars.control.commands;


import es.ucm.tp1.logic.Buyable;
import es.ucm.tp1.logic.Game;
import es.ucm.tp1.logic.gameobjects.Grenade;
import excepciones.CommandExecuteException;
import excepciones.CommandParseException;
import excepciones.NotEnoughCoinsException;
import excepciones.InvalidPositionException;



public class GrenadeCommand extends Command implements Buyable{

	private static final String NAME = "grenade";

	private static final String DETAILS = "[g]renade <x> <y>";

	private static final String SHORTCUT = "g";

	private static final String HELP = "add a grenade in position x, y";
	
	private int x,y;
	

	public GrenadeCommand() {
		super(NAME, SHORTCUT, DETAILS, HELP);
		
	}
	public GrenadeCommand(int x, int y) {
		super(NAME, SHORTCUT, DETAILS, HELP);
		this.x = x;
		this.y = y;
	}

	@Override
	public boolean execute(Game game) throws CommandExecuteException {
		
		Buyable compra= new GrenadeCommand();	
		try {
			compra.buy(game);
			game.addGrenade(new Grenade(game,game.getColJugador()+x,y));
			game.updateGame();
		}catch (NotEnoughCoinsException x) {
			System.out.println(x.getMessage());
			throw new CommandExecuteException ("[ERROR]: Failed to add grenade", x);
		
		}catch (InvalidPositionException x) {
			System.out.println(x.getMessage());
			throw new CommandExecuteException ("[ERROR]: Failed to add grenade", x);
		
		}
		return true;

	}
	protected Command parse(String[] commandWords) throws CommandParseException {
		Command comando=null;
		int x,y = 0;

		if ("g".equalsIgnoreCase(commandWords[0]) || "grenade".equalsIgnoreCase(commandWords[0])) {			
			if (commandWords.length == 3) {
				
				try {
					commandWords[0] = SHORTCUT;
					x= Integer.parseInt(commandWords[1]);
					y= Integer.parseInt(commandWords[2]);
					comando = new GrenadeCommand(x,y);
				}catch(NumberFormatException error) {
					throw new CommandParseException("[ERROR]: Invalid coordinates, expects a number: [g]renade <x> <y>");
					
				}

			}else {
				throw new CommandParseException("[ERROR]: " + INCORRECT_NUMBER_OF_ARGS_MSG + " for grenade: [g]renade <x> <y>");
			}
		}			
			
		return comando;
	}
	@Override
	public int cost() {
		
		return Grenade.getCoste();
	}
	
}
