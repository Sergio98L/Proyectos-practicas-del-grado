package excepciones;

public class UnvalidCheatNumberException extends CommandExecuteException
{
	
	private static final long serialVersionUID = -5828526463614667312L;
	
	public UnvalidCheatNumberException()
	{ 
		super(); 
	}
	public UnvalidCheatNumberException(String message)
	{
		super(message); 
	}
	public UnvalidCheatNumberException(String message, Throwable cause)
	{
		super(message, cause);
	}
	public UnvalidCheatNumberException(Throwable cause)
	{ 
		super(cause); 
	}
	UnvalidCheatNumberException(String message, Throwable cause, boolean enableSuppression, boolean writeableStackTrace)
	{
		super(message, cause, enableSuppression, writeableStackTrace);
	}
}
