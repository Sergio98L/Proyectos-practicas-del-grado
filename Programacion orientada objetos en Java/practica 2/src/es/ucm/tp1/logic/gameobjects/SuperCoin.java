package es.ucm.tp1.logic.gameobjects;

import es.ucm.tp1.logic.Game;

public class SuperCoin extends GameObject {

	private static final String Symbol = "$";
	
	//private static int obstaculosEnTablero;
	private static final String Info = "[SUPERCOIN] gives 1000 coins";
	private static boolean hasSupercoin = false;
	
	public SuperCoin(Game g, int f, int c) {
		super(g, f, c);
		this.symbol = Symbol;
	}

	public static String getInfo() {
		return Info;
	}

	// La usa GamePrinter:
	public static String getObstacleSymbol() {
		return Symbol;
	}

	@Override
	public boolean doCollision() {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public boolean receiveCollision(Player player) {
		player.getSuperCoin();
		this.alive = false;
		return false;
	}

	@Override
	public void onEnter() {
		hasSupercoin = true;
	}

	@Override
	public void update() {
		// TODO Auto-generated method stub

	}

	@Override
	public void onDelete() {
		hasSupercoin = false;

	}
	public static boolean hasSuperCoin() {
		return hasSupercoin;
	}
	public static void reset() {
		 hasSupercoin = false;
	}
	@Override
	public boolean receiveShoot() {
		return false;
	}

	@Override
	public boolean receiveExplosion() {
		// TODO Auto-generated method stub
		return false;
	}
}