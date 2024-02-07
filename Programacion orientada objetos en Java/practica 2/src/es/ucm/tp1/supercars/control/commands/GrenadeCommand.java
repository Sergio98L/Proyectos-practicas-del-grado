package es.ucm.tp1.supercars.control.commands;


import es.ucm.tp1.logic.Buyable;
import es.ucm.tp1.logic.Game;
import es.ucm.tp1.logic.gameobjects.Grenade;



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
	public boolean execute(Game game) {
		Buyable compra= new GrenadeCommand();

		if(compra.buy(game)) {
			game.addGrenade(new Grenade(game,game.getmovJugador()+x,y));
			game.updateGame();
			return true;
		}else {
			System.out.println("No se pudo usar Grenade, monedas insuficientes");
			return false;
		}
	}
	protected Command parse(String[] commandWords) {
		Command comando=null;
		int x,y = 0;

		if ("g".equalsIgnoreCase(commandWords[0]) || "grenade".equalsIgnoreCase(commandWords[0])) {			
			if (commandWords.length != 3) {
				System.out.format("[ERROR]: Command %s: %s%n%n", NAME, INCORRECT_NUMBER_OF_ARGS_MSG);
			}else {
				commandWords[0] = SHORTCUT;
				x= Integer.parseInt(commandWords[1]);
				y= Integer.parseInt(commandWords[2]);
				comando = new GrenadeCommand(x,y);
			}
		}			
			
		return comando;
	}
	@Override
	public int cost() {
		
		return Grenade.getCoste();
	}
	
}
