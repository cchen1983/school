using System;
namespace DecoratorDemo
{
	public class Soy : ICondimentDecorator
	{
		private IBeverage beverage;
		private string description = "Soy";
		private double cost = 0.39;

		public Soy(IBeverage Beverage)
		{
			beverage = Beverage;
		}

		public string Description
		{
			get
			{
				if (beverage.Description != "")
				{
					return beverage.Description + ", " + description;
				}
				else {
					return description;
				}
			}
		}

		public string Size
		{
			get
			{
				return beverage.Size;
			}
			set
			{

			}
		}

		public double Cost
		{
			get
			{
				double price = cost;
				string size = beverage.Size;

				if (size == "Medium")
				{
					price = cost + 0.20;
				}
				else if (size == "Large")
				{
					price = cost + 0.40;
				}
				return beverage.Cost + price;
			}
		}
	}
}
