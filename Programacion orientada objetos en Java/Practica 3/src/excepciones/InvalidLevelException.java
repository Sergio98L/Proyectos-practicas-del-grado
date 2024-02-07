package excepciones;

public class InvalidLevelException extends CommandExecuteException
{
	
	private static final long serialVersionUID = -5828526463614667312L;

	public InvalidLevelException()
	{ 
		super(); 
	}
	public InvalidLevelException(String message)
	{
		super(message); 
	}
	public InvalidLevelException(String message, Throwable cause)
	{
		super(message, cause);
	}
	public InvalidLevelException(Throwable cause)
	{ 
		super(cause); 
	}
	InvalidLevelException(String message, Throwable cause, boolean enableSuppression, boolean writeableStackTrace)
	{
		super(message, cause, enableSuppression, writeableStackTrace);
	}
}
