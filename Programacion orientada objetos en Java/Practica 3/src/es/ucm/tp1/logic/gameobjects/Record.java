package es.ucm.tp1.logic.gameobjects;


import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import es.ucm.tp1.logic.Game;
import excepciones.InputOutputRecordException;
import excepciones.ShowRecordException;


public class Record {
	private long test,easy,hard,advanced;
	private Game game;

	public Record(Game game) {
		this.game = game;
		//valores por defecto:
		this.test = 22340;
		this.easy = 1760;
		this.hard = 6057;
		this.advanced = 1030;
		
	}
//cargar y guardar
	public void guardarRecord() throws InputOutputRecordException {
		
		File name = new File("record.txt");
		try (BufferedWriter buff = new BufferedWriter (new FileWriter(name)))
		{							
			switch(game.getLevel()) {
				case TEST:
					this.test = game.elapsedTime();
					break;
				case EASY:
					this.easy = game.elapsedTime();
					break;
				case HARD:
					this.hard = game.elapsedTime();
					break;
				case ADVANCED:
					this.advanced = game.elapsedTime();
					break;
			}
			buff.write("HARD:" + this.hard);
			buff.newLine();
			buff.write("TEST:" + this.test);
			buff.newLine();
			buff.write("EASY:" + this.easy);
			buff.newLine();
			buff.write("ADVANCED:" + this.advanced);
			buff.newLine();
			
			System.out.format("%s %s.%n", "\nGame records successfully saved in file", name);
			buff.close();
			
		}
		catch (IOException x)
		{
			throw new InputOutputRecordException("Game records werent able to store ");
		}
	}
	
	public void cargarRecord() throws InputOutputRecordException {
		
		File name = new File("record.txt");
		try (BufferedReader buff = new BufferedReader (new FileReader(name)))
		{					
			String s;
			while((s=buff.readLine())!=null) {
				String[] parameters = s.toLowerCase().trim().split(":");
				try {
				switch(parameters[0]) {
				case "test":
					this.test = Integer.parseInt(parameters[1]);
					break;
				case "easy":
					this.easy = Integer.parseInt(parameters[1]);
					break;
				case "hard":
					this.hard = Integer.parseInt(parameters[1]);
					break;
				case "advanced":
					this.advanced = Integer.parseInt(parameters[1]);
					break;
				}
				}catch(NumberFormatException error) {
					throw new InputOutputRecordException("Game records are corrupted");
				}
			}
			System.out.format("%s %s.%n", "Game records successfully loaded", name);
			buff.close();
		}
		catch (IOException x)
		{
			throw new InputOutputRecordException("Game records werent able to load");
		}
	}
	
	public long getRecord() throws ShowRecordException {
		long recordActual=0;
		
		switch(game.getLevel()) {
		case TEST:
			recordActual= this.test;
			break;
		case EASY:
			recordActual= this.easy;
			break;
		case HARD:
			recordActual= this.hard;
			break;
		case ADVANCED:
			recordActual= this.advanced;
			break;
		default:
			throw new ShowRecordException("[ERROR]: Couldnt obtain current level record");
	}
		return recordActual;
	}
}

