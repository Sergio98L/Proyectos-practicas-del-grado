package es.ucm.tp1.logic.gameobjects;

import es.ucm.tp1.logic.Collider;
import es.ucm.tp1.logic.Game;
import excepciones.NotEnoughCoinsException;

public class Player extends GameObject {
	private int monedas;

	private static final String Info = "[Car] the racing car";
	// X son las filas
	// Y son las columnas

	public Player(Game g) {
		super(g, 0, 1);
		this.monedas = 10;
	}

	public static String getInfo() {
		return Info;
	}
	public String getAllInfo() {
		String info =this.toString() +" ("+this.getX()+","+ this.getY()+ ")" +"\n";
		return info;
	}

	public String toString() {
		String simbolo;
		if (this.alive) {
			simbolo = ">";
		} else {
			simbolo = "@";
		}
		return simbolo;
	}

	public void setMonedasCero() {
		this.monedas = 0;
	}

	public boolean restarMonedas(int monedasPerdidas) throws NotEnoughCoinsException {				
		
		boolean suficiente = false;
			
			if (monedas >= monedasPerdidas)
			{		
				this.monedas -= monedasPerdidas;	
				suficiente = true;
			}
			else
			{
				throw new NotEnoughCoinsException("[ERROR]: Cost is: " + monedasPerdidas + ": Not enough coins");
			}
		
		return suficiente;
	}
	
	public void resetPlayerPos() {
		this.x = 0;
		this.y = 1;
	}

	public void setDeadPlayer() {
		alive = false;
	}

	public void getSuperCoin() {
		this.monedas += 1000;
	}

	public int getMonedas() {
		return this.monedas;
	}

	public void addCoin() {
		this.monedas++;
	}

	public void addCoin(int monedas) {
		this.monedas += monedas;
	}

	public void getTurbo(int posicionesAvanzadas) {
		game.getTurbo(posicionesAvanzadas);
	}

	@Override
	public boolean doCollision() {
		Collider other = game.getObjectInPosition(game.getColJugador(), y);
		if (other != null) {
			return other.receiveCollision(this);
		}
		return false;
	}

	@Override
	public boolean receiveCollision(Player player) {
		return false;
	}

	@Override
	public void onEnter() {
	}

	@Override
	public void update() {
	}

	@Override
	public void onDelete() {
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
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public boolean receiveRay() {
		// TODO Auto-generated method stub
		return false;
	}

}
