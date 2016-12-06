using System;

namespace LSP
{
	class MainClass
	{
		public static void Main(string[] args)
		{
			try
			{
				Console.WriteLine("Hello World!");
			}
			catch (Exception ex) {
				Console.WriteLine("Runtime error: " + ex.Message);
			}

			Console.WriteLine("Press any key to terminate this program.");
			Console.ReadLine();
		}
	}
}
