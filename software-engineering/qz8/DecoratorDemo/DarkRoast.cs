using System;
namespace DecoratorDemo
{
	public class DarkRoast : IBeverage
	{
		private string description = "Dark Roast";
		private double cost = 3.49;
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
				double price = cost;
				if (size == "Medium")
				{
					price = cost + 1.00;
				}
				else if (size == "Large")
				{
					price = cost + 2.00;
				}
				return price;
			}
		}
	}
}
