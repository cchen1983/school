using System;

namespace DIP
{
	class MainClass
	{
		public static void Main(string[] args)
		{
			
			try
			{
				bool isHilaryWin = true;
				BroadcastResult result = new BroadcastResult();
				result.Broadcast(isHilaryWin);
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
