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
				if (IsHilaryWin)
				{
					Message = "Hilary Won.";
				}
				else {
					Message = "Trump Won.";
				}

				BroadcastResult result = new BroadcastResult();
				result.Broadcast(IsHilaryWin, Message);
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
