package excepciones;

public class GameException extends Exception
{
	
	private static final long serialVersionUID = 6131026381934571270L;
	
	public GameException()
	{ 
		super(); 
	}
	public GameException(String message)
	{
		super(message); 
	}
	public GameException(String message, Throwable cause)
	{
		super(message, cause);
	}
	public GameException(Throwable cause)
	{ 
		super(cause); 
	}
	GameException(String message, Throwable cause, boolean enableSuppression, boolean writeableStackTrace)
	{
		super(message, cause, enableSuppression, writeableStackTrace);
	}
}
