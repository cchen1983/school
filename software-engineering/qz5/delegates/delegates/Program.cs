using System;
using System.IO;

namespace DelegatesExample
{
	class NumberChanging 
	{
		static int num;

		public NumberChanging(int n) 
		{
			num = n;	
		}

		public int AddNum(int p)
		{
			num += p;
			return num;
		}

		public int MultNum(int q)
		{
			num *= q;
			return num;
		}

		public int getNum()
		{
			return num;
		}
	}

	class PrintString { 
		static FileStream fs;
		static StreamWriter sw;

		public void WriteToScreen(string str)
		{
			Console.WriteLine("The String is: {0}", str);
		}

		public void WriteToFile(string s)
		{
			fs = new FileStream("test.txt",
			FileMode.Append, FileAccess.Write);
			sw = new StreamWriter(fs);
			sw.WriteLine(s);
			sw.Flush();
			sw.Close();
			fs.Close();
		}
	}

	class MainClass
	{
		delegate int NumberChanger(int n);
		public delegate void printString(string s);

		public static void Main(string[] args)
		{
			NumberChanging nm = new NumberChanging(10);

			NumberChanger nc1 = new NumberChanger(nm.AddNum);
			NumberChanger nc2 = new NumberChanger(nm.MultNum);

			nc1(25);
			Console.WriteLine("Value of Num: {0}", nm.getNum());
			nc2(5);
			Console.WriteLine("Value of Num: {0}", nm.getNum());

			NumberChanging nn = new NumberChanging(10);

			NumberChanger nc3 = new NumberChanger(nn.AddNum);
			NumberChanger nc4 = new NumberChanger(nn.MultNum);
			NumberChanger nc;

			nc = nc3;
			nc += nc4;

			nc(5);
			Console.WriteLine("Value of Num: {0}", nn.getNum());

			PrintString PS = new PrintString();
			printString ps1 = new printString(PS.WriteToScreen);
			printString ps2 = new printString(PS.WriteToFile);
			ps1("Hello world!");
			ps2("Hello world!");

			Console.ReadKey();
		}
	}
}
