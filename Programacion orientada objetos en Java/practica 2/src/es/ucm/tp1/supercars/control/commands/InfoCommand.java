package es.ucm.tp1.supercars.control.commands;

import es.ucm.tp1.logic.Game;
import es.ucm.tp1.logic.gameobjects.*;


public class InfoCommand extends Command {

	private static final String NAME = "info";

	private static final String DETAILS = "[i]nfo";

	private static final String SHORTCUT = "i";

	private static final String HELP = "prints gameobject info";

	public InfoCommand() {
		super(NAME, SHORTCUT, DETAILS, HELP);
	}

	@Override
	public boolean execute(Game game) {
		System.out.println("Available objects:");
		System.out.println(Player.getInfo());
		System.out.println(Coin.getInfo());
		System.out.println(Obstacle.getInfo());
		System.out.println(Grenade.getInfo());
		System.out.println(Wall.getInfo());
		System.out.println(Turbo.getInfo());
		System.out.println(SuperCoin.getInfo());
		System.out.println(Truck.getInfo());
		System.out.println(Pedestrian.getInfo());
		return false;
	}

}