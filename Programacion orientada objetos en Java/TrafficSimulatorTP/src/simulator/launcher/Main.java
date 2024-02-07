package simulator.launcher;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.ArrayList;
import java.util.List;

import javax.swing.SwingUtilities;

import org.apache.commons.cli.CommandLine;
import org.apache.commons.cli.CommandLineParser;
import org.apache.commons.cli.DefaultParser;
import org.apache.commons.cli.HelpFormatter;
import org.apache.commons.cli.Option;
import org.apache.commons.cli.Options;
import org.apache.commons.cli.ParseException;

import simulator.control.Controller;

import simulator.model.*;
import simulator.view.MainWindow;
import simulator.factories.*;

public class Main {
	
	private enum mode {
		GUI, CONSOLE;
	}
	//private final static Integer _timeLimitDefaultValue = 10;
	private static String _inFile = null;
	private static String _outFile = null;
	private static mode _modoActual = null;
	private static Factory<Event> _eventsFactory = null;
	private static Integer ticks = 300;

	private static void parseArgs(String[] args) {

		// define the valid command line options
		//
		Options cmdLineOptions = buildOptions();

		// parse the command line as provided in args
		//
		CommandLineParser parser = new DefaultParser();
		try {
			CommandLine line = parser.parse(cmdLineOptions, args);
			parseModeOption(line);
			parseHelpOption(line, cmdLineOptions);
			parseInFileOption(line);
			parseOutFileOption(line);
			parseTicks(line);

			// if there are some remaining arguments, then something wrong is
			// provided in the command line!
			//
			String[] remaining = line.getArgs();
			if (remaining.length > 0) {
				String error = "Illegal arguments:";
				for (String o : remaining)
					error += (" " + o);
				throw new ParseException(error);
			}

		} catch (ParseException e) {
			System.err.println(e.getLocalizedMessage());
			System.exit(1);
		}

	}

	private static Options buildOptions() {
		Options cmdLineOptions = new Options();

		cmdLineOptions.addOption(Option.builder("m").longOpt("mode").hasArg().desc("Select Mode").build());
		cmdLineOptions.addOption(Option.builder("i").longOpt("input").hasArg().desc("Events input file").build());
		cmdLineOptions.addOption(
				Option.builder("o").longOpt("output").hasArg().desc("Output file, where reports are written.").build());
		cmdLineOptions.addOption(Option.builder("h").longOpt("help").desc("Print this message").build());
		cmdLineOptions.addOption(Option.builder("t").hasArg().longOpt("ticks").desc("ticks of traffic simulator").build());
		
		return cmdLineOptions;
	}
	private static void parseModeOption(CommandLine line){
		String modo = line.getOptionValue("m");
		if (modo == null || modo.equalsIgnoreCase("gui")) {
			
				_modoActual = mode.GUI;
			
		}else {
			_modoActual = mode.CONSOLE;
		}
		
		
	}

	private static void parseHelpOption(CommandLine line, Options cmdLineOptions) {
		if (line.hasOption("h")) {
			HelpFormatter formatter = new HelpFormatter();
			formatter.printHelp(Main.class.getCanonicalName(), cmdLineOptions, true);
			System.exit(0);
		}
	}

	private static void parseInFileOption(CommandLine line) throws ParseException {
		_inFile = line.getOptionValue("i");
		if (_inFile == null && _modoActual == mode.CONSOLE) {
			throw new ParseException("An events file is missing");
		}
	}

	private static void parseOutFileOption(CommandLine line) throws ParseException {
		
		if(_modoActual == mode.CONSOLE)
		_outFile = line.getOptionValue("o");
	}
	
	private static void parseTicks(CommandLine line) {
		if(line.hasOption("t")) {
			ticks = Integer.parseInt(line.getOptionValue("t"));
		}
	}

	private static void initFactories() {

		// TODO complete this method to initialize _eventsFactory
		
		List<Builder<LightSwitchingStrategy>> lsbs = new ArrayList<>();
		lsbs.add( new RoundRobinStrategyBuilder() );
		lsbs.add( new MostCrowdedStrategyBuilder() );
		Factory<LightSwitchingStrategy> lssFactory = new BuilderBasedFactory<>(lsbs);

		
		List<Builder<DequeuingStrategy>> dqbs = new ArrayList<>();
		dqbs.add( new MoveFirstStrategyBuilder() );
		dqbs.add( new MoveAllStrategyBuilder() );
		Factory<DequeuingStrategy> dqsFactory = new BuilderBasedFactory<>(dqbs);

		
		List<Builder<Event>> ebs = new ArrayList<>();
		ebs.add( new NewJunctionEventBuilder(lssFactory,dqsFactory) );
		ebs.add( new NewCityRoadEventBuilder() );
		ebs.add( new NewInterCityRoadEventBuilder() );
		ebs.add( new NewVehicleEventBuilder() );
		ebs.add( new SetWeatherEventBuilder() );
		ebs.add( new SetContClassEventBuilder() );
		_eventsFactory = new BuilderBasedFactory<>(ebs);

	}

	private static void startBatchMode() throws IOException, InterruptedException {
		//generar un inputstream un outputstream el traffic simulator, el controller y llamar al run del controller
		OutputStream out;
		InputStream in = new FileInputStream(new File(_inFile));
		TrafficSimulator ts = new TrafficSimulator();
		Controller c = new Controller(ts, _eventsFactory);
		CarreterasConColas carr = new CarreterasConColas(c);
		
		if(_outFile == null) {
			out = System.out;
		}
		else {
			out = new FileOutputStream(new File(_outFile)); 
		}
		c.loadEvents(in);
		c.run(ticks, out);
		in.close();
		carr.mostrar();
		out.close();
		
	}

	private static void start(String[] args) throws IOException, InterruptedException {
		initFactories();
		parseArgs(args);
		if(_modoActual == mode.GUI) {
			startGUIMode();
		}else {
			startBatchMode();
		}
		
	}
	private static void startGUIMode() throws IOException {
		
		TrafficSimulator ts = new TrafficSimulator();
		Controller c = new Controller(ts, _eventsFactory);
		
		if(_inFile != null) {
			InputStream in = new FileInputStream(new File(_inFile));
			c.loadEvents(in);
			in.close();
		}
		
		SwingUtilities.invokeLater(new Runnable() {
			@Override
			public void run() {
				new MainWindow(c);
		}
		}); 

	}

	// example command lines:
	//
	// -i resources/examples/ex1.json
	// -i resources/examples/ex1.json -t 300
	// -i resources/examples/ex1.json -o resources/tmp/ex1.out.json
	// --help

	public static void main(String[] args) {
		try {
			start(args);
		} catch (Exception e) {
			e.printStackTrace();
		}

	}

}
