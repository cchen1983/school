using System;
namespace DecoratorDemo
{
	public class HouseBlend: IBeverage
	{
		private string description = "House Blend";
		private double cost = 2.99;
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
