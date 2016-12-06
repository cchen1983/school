using System;

namespace DIP
{
	class MainClass
	{
		public static void Main(string[] args)
		{
			
			try
			{
				bool IsHilaryWin = true;
				String Message;
				IMsg ScrMsg = new ScreenMsg();
				IMsg EMsg = new EmailMsg();

				BroadcastResult result = new BroadcastResult();

				if (IsHilaryWin)
				{
					Message = "Hilary Won.";
					result.Broadcast(EMsg, Message);
				}
				else {
					Message = "Trump Won.";
					result.Broadcast(ScrMsg, Message);
				}

				Console.WriteLine("\nPress any key to Exit.");
				Console.ReadLine();
			}
			catch (Exception e)
			{
				Console.WriteLine("Runtime Error: " + e.Message);
			}
		}
	}
}
