using System;
namespace DecoratorDemo
{
	public class Espresso: IBeverage
	{
		private string description = "Espresson";
		private double cost = 3.99;
		private string size = "Small";

		public string Description { 
			get {
				return description;
			}
		}

		public string Size
		{
			get
			{
				return size;
			}

			set {
				size = value;
			}
		}

		public double Cost { 
			get {
				double price = cost;
				if (size == "Medium")
				{
					price = cost + 1.00;
				}
				else if (size == "Large") {
					price = cost + 2.00;
				}
				return price;
			}
		}
	}
}
