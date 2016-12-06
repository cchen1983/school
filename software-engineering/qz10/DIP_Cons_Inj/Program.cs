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
				BroadcastResult result;
				IMsg Msg;
				if (IsHilaryWin)
				{
					Message = "Hilary Won.";
					Msg = new EmailMsg();
				}
				else {
					Message = "Trump Won.";
					Msg = new ScreenMsg();
				}

				result = new BroadcastResult(Msg);
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
