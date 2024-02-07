package es.ucm.tp1.control;

public enum Level {

	TEST(10, 3, 8, 0.5, 0, 0), EASY(30, 3, 8, 0.5, 0.5, 0), HARD(100, 5, 6, 0.7, 0.3, 0), ADVANCED(100, 3, 8, 0.3, 0.3, 0.1);

	private int length;

	private int width;
	
	private int visibility;

	private double advObjFreq;
	
	private double coinFrequency;

	private double obstacleFrequency;

	private Level(int length, int width, int visibility, double obstacleFrequency, double coinFrequency,double advObjFreq) {
		this.length = length;
		this.width = width;
		this.visibility = visibility;
		this.obstacleFrequency = obstacleFrequency;
		this.coinFrequency = coinFrequency;
		this.advObjFreq = advObjFreq;

	}

	// TODO fill your code

	public static Level valueOfIgnoreCase(String inputString) {
		
		for (Level level : Level.values()) {
			if (level.name().equalsIgnoreCase(inputString)) {
				return level;
			}
		}
		return null;
	}

	public static String all(String separator) {
		StringBuilder buffer = new StringBuilder();
		int levelCount = 0;
		for (Level level : Level.values()) {
			if (levelCount > 0) {
				buffer.append(separator);
			}
			buffer.append(level.name());
			levelCount++;
		}
		return buffer.toString();
	}

	public int getDimX() // Obtiene la dim_x
	{
		return this.length;
	}

	public int getDimY() // Obtiene la dim_y
	{
		return this.width;
	}

	public int getVisibility()
	{
		return this.visibility;
	}

	public double getCoinFrequency()
	{
		return this.coinFrequency;
	}

	public double getObstacleFrequency() 
	{
		return this.obstacleFrequency;
	}

	public boolean hasAdvancedObjects() {
		if(this.advObjFreq>0) {
			return true;
		}
		return false;
	}

	public double advancedObjectsFrequency() {
		
		return this.advObjFreq;
	}

}
