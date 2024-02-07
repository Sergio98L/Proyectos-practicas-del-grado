package es.ucm.tp1.logic.gameobjects;

import es.ucm.tp1.logic.Game;

public class Coin extends GameObject {

	private static final String Symbol = "¢";
	private static int monedasEnTablero;
	private static final String Info = "[Coin] gives 1 coin to the player";

	public Coin(Game g, int f, int c) {
		super(g, f, c);
		this.symbol = Symbol;

	}

	public static String getInfo() {
		return Info;
	}

	public static int getMonedasEnTablero() {
		return monedasEnTablero;
	}

	public static void reset() {
		monedasEnTablero = 0;
	}

	// La usa GamePrinter:
	public static String getCoinSymbol() {
		return Symbol;
	}

	@Override
	public boolean doCollision() {
		return false;
	}

	@Override
	public boolean receiveCollision(Player player) {
		player.addCoin();
		this.alive = false;
		return false;
	}

	@Override
	public void onEnter() {
		monedasEnTablero++;

	}

	@Override
	public void update() {
	}

	@Override
	public void onDelete() {
		monedasEnTablero--;

	}

	@Override
	public boolean receiveShoot() {
		return false;
	}

	@Override
	public boolean receiveExplosion() {
		return false;
	}

	@Override
	public boolean receiveThunder() {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public boolean receiveWave() {
		x++;
		return true;
	}

	@Override
	public boolean receiveRay() {
		// TODO Auto-generated method stub
		return false;
	}

}
