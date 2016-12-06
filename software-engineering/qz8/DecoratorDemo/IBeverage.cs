using System;
namespace DecoratorDemo
{
	public interface IBeverage
	{
		string Description { get; }
		string Size { get; set; }
		double Cost { get; }
	}
}
