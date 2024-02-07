package excepciones;

public class CommandParseException extends GameException
{

	private static final long serialVersionUID = 8781839658776020193L;
	
	public CommandParseException()
	{ 
		super(); 
	}
	public CommandParseException(String message)
	{
		super(message); 
	}
	public CommandParseException(String message, Throwable cause)
	{
		super(message, cause);
	}
	public CommandParseException(Throwable cause)
	{ 
		super(cause); 
	}
	CommandParseException(String message, Throwable cause, boolean enableSuppression, boolean writeableStackTrace)
	{
		super(message, cause, enableSuppression, writeableStackTrace);
	}
}
