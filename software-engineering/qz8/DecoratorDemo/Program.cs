using System;

namespace DecoratorDemo
{
	public class PlaceHolder : IBeverage
	{
		private string description = "";
		private double cost = 0.00;
		private string size = "Small";

		public string Description
		{
			get
			{
				return description;
			}
		}

		public string Size
		{
			get
			{
				return size;
			}

			set
			{
				size = value;
			}
		}

		public double Cost
		{
			get
			{
				return cost;
			}
		}
	}

	class MainClass
	{
		public static void Main(string[] args)
		{
			try
			{
				IBeverage p = new PlaceHolder();
				IBeverage[] bevs = {new Espresso(), new HouseBlend(), new DarkRoast()};
				IBeverage[] extras = {new Mocha(p), new Soy(p), new Whip(p)};
				String[] sizes = { "Small", "Medium", "Large" };

				while (true) {
					Int32 bevId = 0;
					Int32 exId = 0;
					Int32 sizeId = 0;
					int ex_cnt = 0;
					String name = "Unknown";
					IBeverage bev, et;

					Console.WriteLine("Welcome to Starbuff Cafe");
					Console.WriteLine("Beverages prices:");
					Console.WriteLine("");
					Console.WriteLine("Name\t\tSmall\tMedium\tLarge");
					Console.WriteLine("------------------------------------------------------------------------");

					for (int i = 0; i < bevs.Length; i++) {
						bevs[i].Size = "Small";
						Console.WriteLine(bevs[i].Description + "\t$" + bevs[i].Cost + "\t$" + (bevs[i].Cost + 1.00) + "\t$" + (bevs[i].Cost + 2.00));
					}

					Console.WriteLine("");
					Console.WriteLine("Extras prices:");
					Console.WriteLine("");
					Console.WriteLine("Name\t\tSmall\tMedium\tLarge");
					Console.WriteLine("------------------------------------------------------------------------");
					for (int i = 0; i < extras.Length; i++)
					{
						Console.WriteLine(extras[i].Description + "\t\t$" + extras[i].Cost + "\t$" + (extras[i].Cost + 0.20) + "\t$" + (extras[i].Cost + 0.20));
					}

					Console.WriteLine("");
					Console.WriteLine("Enter Customer Name (Enter for Default, Q + Enter to Quit):");
					Console.WriteLine("");

					name = Console.ReadLine();
					if (name == "q" || name == "Q")
					{
						break;
					}
					else if (name == "") {
						name = "Unknown";
					}

					while (true) {
						bevId = 0;

						Console.WriteLine("Select Beverage:");
						for (int i = 0; i < bevs.Length; i++) {
							Console.WriteLine((i+1) + ". " + bevs[i].Description);
						}
						Console.WriteLine((bevs.Length + 1) + ". " + "Cancel");
						Console.WriteLine("");
						Console.WriteLine("Enter your choice: ");

						string choice = Console.ReadLine();
						try
						{
							bevId = Int32.Parse(choice);
						}
						catch (Exception ex) {	//Illegal Input
							bevId = 0;
						}

						if (bevId > 0 && bevId <= bevs.Length + 1) {	//Valid Input
							break;
						}
					}

					if (bevId == bevs.Length + 1) {
						Console.WriteLine("Purchasing has been canceled.");
						Console.WriteLine("");
						continue;
					}

					bev = bevs[bevId - 1];

					while (true)
					{
						sizeId = 0;

						Console.WriteLine("Select Size:");

						Console.WriteLine("1. " + "Small");
						Console.WriteLine("2. " + "Medium");
						Console.WriteLine("3. " + "Large");
						Console.WriteLine("4. " + "Cancel");
						Console.WriteLine("");
						Console.WriteLine("Enter your choice: ");

						string choice = Console.ReadLine();
						try
						{
							sizeId = Int32.Parse(choice);
						}
						catch (Exception ex)
						{   //Illegal Input
							sizeId = 0;
						}

						if (sizeId > 0 && sizeId <= 4)
						{   //Valid Input
							break;
						}
					}

					if (sizeId == 4)
					{
						Console.WriteLine("Purchasing has been canceled.");
						Console.WriteLine("");
						continue;
					}

					bev.Size = sizes[sizeId - 1];

					Console.WriteLine("Your order status:");
					Console.WriteLine("Customer Name: " + name);
					Console.WriteLine("Beverage: " + bevs[bevId - 1].Description);
					Console.WriteLine("Size: " + sizes[sizeId - 1]);
					Console.WriteLine("Extras: ");
					Console.WriteLine("Cost: " + bev.Cost);
					Console.WriteLine("");

					et = new Mocha(bev); //placeholder

					while (true)
					{
						exId = 0;

						Console.WriteLine("Select Extras:");
						for (int i = 0; i < extras.Length; i++)
						{
							Console.WriteLine((i + 1) + ". " + extras[i].Description);
						}
						Console.WriteLine((extras.Length + 1) + ". " + "Done");
						Console.WriteLine("");
						Console.WriteLine("Enter your choice: ");

						string choice = Console.ReadLine();
						try
						{
							exId = Int32.Parse(choice);
						}
						catch (Exception ex)
						{   //Illegal Input
							exId = 0;
						}

						if (exId > 0 && exId <= extras.Length)
						{
							if (exId == 1)
							{
								if (ex_cnt == 0)
								{
									et = new Mocha(bev);
								}
								else {
									et = new Mocha(et);
								}
							}
							else if (exId == 2)
							{
								if (ex_cnt == 0)
								{
									et = new Soy(bev);
								}
								else {
									et = new Soy(et);
								}
							}
							else {
								if (ex_cnt == 0)
								{
									et = new Whip(bev);
								}
								else {
									et = new Whip(et);
								}
							}
							ex_cnt += 1;
							continue;
						}
						else if (exId == extras.Length + 1)
						{   //Done
							break;
						}
					}

					Console.WriteLine("Your order status:");
					Console.WriteLine("Customer Name: " + name);
					Console.WriteLine("Beverage: " + bevs[bevId - 1].Description);
					Console.WriteLine("Size: " + sizes[sizeId - 1]);
					if (ex_cnt > 0)
					{
						Console.WriteLine("Extras: " + et.Description);
						Console.WriteLine("Cost: " + et.Cost);
					}
					else { 
						Console.WriteLine("Extras: ");
						Console.WriteLine("Cost: " + bev.Cost);
					}
					Console.WriteLine("");

				}

			}
			catch (Exception ex) {
				Console.WriteLine("Runtime Error: " + ex.Message);
			}

			//Console.ReadLine();
		}
	}
}
