package es.ucm.tp1.logic;

import java.util.Random;


import es.ucm.tp1.control.Level;
import es.ucm.tp1.logic.gameobjects.GameObject;
import es.ucm.tp1.logic.gameobjects.GameObjectContainer;
import es.ucm.tp1.logic.gameobjects.GameObjectGenerator;
import es.ucm.tp1.logic.gameobjects.Player;

public class Game {

	private int cycle;
	private int movJugador;
	private Level level;
	private Long seed;
	private Player player;
	private GameObjectContainer objectsContainer;
	private Random rand;
	private boolean endgame;
	private boolean testmode;
	private double tiempoInicial;
	private double tiempoTranscurrido;

	public Game(Long seed, Level level) {
		this.seed = seed;
		this.level = level;
		this.init();
	}

	public void init() {
		player = new Player(this);
		objectsContainer = new GameObjectContainer();
		rand = new Random(seed);
		GameObjectGenerator.generateGameObjects(this, level);
		this.cycle = 0;
		this.tiempoTranscurrido = 0;
		this.movJugador = 0;
	}

	public int getVisibility() {
		return this.level.getVisibility();
	}

	public int getRoadLength() {
		return this.level.getDimX();
	}

	public int getRandomLane() {
		return rand.nextInt(level.getDimY());
	}
	public int getRandomCol() {
		return rand.nextInt(level.getVisibility()-1);
	}

	public void setSeed(long numero) {
		this.seed = numero;
	}

	public void setLevel(String nivel) {
		this.level = Level.valueOfIgnoreCase(nivel);
	}

	public void tryToAddObject(GameObject objeto, double objectFrequency) {

		if (rand.nextDouble() < objectFrequency && objectsContainer.isPositionEmpty(objeto.getX(), objeto.getY())) {
			this.objectsContainer.add(objeto);
		}
	}

	public void toggleTest() {
		this.testmode = true;
	}

	public void checkEnd() // Comprueba si ha llegado al final
	{

		if (level.getDimX() - movJugador == 0) {
			this.endgame = true;
			System.out.print("\n[GAME OVER] Player wins\n");
			System.out.print("\nNew record!: " + Math.round((this.tiempoTranscurrido / 1000) * 100.0) / 100.0 + " s");

		} else if (!player.getAlive()) {

			this.endgame = true;
			System.out.print("\n[GAME OVER] Player crashed!\n");
		}

	}

	public boolean getEndGame() {
		return endgame;
	}

	public void exit() // Sale del juego
	{
		endgame = true;
		System.out.println("[GAME OVER] Player leaves the game");
	}

	public boolean movePlayerUp() {
		
		this.movJugador++;
		boolean puedeMover = false;
		
		if (player.getY() > 0) {
			player.movePlayerUp();
			puedeMover = true;
		}

		return puedeMover;
	}

	public boolean movePlayerDown() {

		this.movJugador++;
		boolean puedeMover = false;

		if (player.getY() < (level.getDimY() - 1)) {
			player.movePlayerDown();
			puedeMover = true;
		}

		return puedeMover;
	}

	public void updateGame() // Actualizar el juego

	{
		this.objectsContainer.updateObjects();
		GameObjectGenerator.generateRuntimeObjects(this);
		
		this.comprobarColision();
		
		this.cycle++;
		

		if (this.cycle == 1) {// cuando realiza un movimiento el jugador empieza el contador de tiempo
			this.tiempoInicial = System.currentTimeMillis();
		} else {
			this.tiempoTranscurrido = System.currentTimeMillis() - this.tiempoInicial;
		}
		
		
		this.checkDeadObjects();
		this.checkEnd();

	}

	public void comprobarColision() {
		player.doCollision();
	}
	
	public Collider getObjectInPosition(int x, int y) {
		
		Collider interfaz = null;
		
		interfaz = objectsContainer.getObjectInPosition(x, y, interfaz);
		
		return interfaz;
	}
	public void checkDeadObjects() // Eliminar objetos muertos el juego
	{
		objectsContainer.removeDead();
	}
	public int getPlayerCoins() {
		return player.getMonedas();
	}
	public boolean restarMonedasPlayer(int monedasPerdidas) {
		return player.restarMonedas(monedasPerdidas);
	}
	public void addWallCoins() {
		for(int i=0;i<5;i++) {
			player.addCoin();
		}		
	}
	public int getPlayerY() {
		return player.getY();
	}
	public int get() {
		return player.getY();
	}
	public void addGrenade(GameObject o) {
		
		
		int parteVisible = this.getVisibility()+this.movJugador;
		
		if(o.getX()>=0 && o.getX() < parteVisible && o.getY()<level.getDimY()) { //comprobar que este en la parte visible
			if(objectsContainer.isPositionEmpty(o.getX(), o.getY())) {
				this.forceAddObject(o);
			}else {
				System.out.println("No se puede colocar encima de un objeto");
			}
		}else {
			System.out.println("No se puede colocar fuera de la parte visible");
		}
	}
	
	public void resetMonedasPlayer(){
		
		this.player.setMonedasCero();
	}
	//Execute InstantAction:
	
	public void execute(InstantAction instantAction) {
		instantAction.execute(this);
	}
	
	public void empujarObjetos(int x, int y) {
		if(this.objectsContainer.isPositionEmpty(x+1, y)) {
			this.objectsContainer.empujarObjetos(x,y);
		}
	}
	
	public boolean impactoThunder(int x, int y) {
		return this.objectsContainer.impactoThunder(x, y);
	}
	
	//Metodos para cheat
	public void clearCarretera(){
		
		this.objectsContainer.clearObjects();
		//GameObjectGenerator.reset(this.level);
	}
	public void borrarUltColumVisible(){
		
		this.objectsContainer.borrarUltColumVisible((this.movJugador + (this.getVisibility()-1)));
	}
	
	public void cheatGame(int cheat) {
		GameObjectGenerator.forceAdvanceObject(this, cheat, (this.movJugador + (this.getVisibility()-1)));
	}
	public void forceAddObject(GameObject o) {
		this.objectsContainer.add(o);
		
	}
	
	// Metodos para el GamePrinter:

	public String positionToString(int x, int y) {
		String symbolo = "";

		if (player.isInThisPosition(x, y)) {
			symbolo = player.toString();
		}
			symbolo += objectsContainer.getPositionToString(x + movJugador, y);
		if(x + movJugador == level.getDimX()) {
			symbolo += "¦";
		}
		return symbolo;
	}

	public String distanceToGoal() {
		// TODO Auto-generated method stub
		return "" + (level.getDimX() - movJugador);
	}

	public int playerCoins() {
		// TODO Auto-generated method stub
		return player.getMonedas();
	}

	public int getCycle() {
		// TODO Auto-generated method stub
		return this.cycle;
	}

	public Level getLevel() {
		// TODO Auto-generated method stub
		return this.level;
	}

	public boolean isTestMode() {
		// TODO Auto-generated method stub
		return this.testmode;
	}

	public long elapsedTime() {
		// TODO Auto-generated method stub
		return (long) this.tiempoTranscurrido;
	}

	public int getRoadWidth() {
		// TODO Auto-generated method stub
		return this.level.getDimY();
	}

	public boolean isUserExit() {
		// TODO Auto-generated method stub
		return this.endgame;
	}

	public boolean hasArrived() {
		boolean hasArrived = false;

		if (level.getDimX() - movJugador == 0) {
			hasArrived = true;
		}

		return hasArrived;
	}

	public boolean isNewRecord() {
		// TODO Auto-generated method stub
		return false;
	}

	public long getRecord() {
		// TODO Auto-generated method stub
		return 0;
	}
	
	public int getmovJugador() {
		
		return this.movJugador;
	}
	public void addmovJugador() {
		
		this.movJugador++;
	}

	public void getTurbo() {
		this.movJugador +=3;
		
	}

}
