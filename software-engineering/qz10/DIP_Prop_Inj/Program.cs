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
				BroadcastResult result = new BroadcastResult();
				IMsg ScrMsg = new ScreenMsg();
				IMsg EMsg = new EmailMsg();

				if (IsHilaryWin)
				{
					Message = "Hilary Won.";
					result.Msg = EMsg;
				}
				else {
					Message = "Trump Won.";
					result.Msg = ScrMsg;
				}

				result.Broadcast(Message);
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
