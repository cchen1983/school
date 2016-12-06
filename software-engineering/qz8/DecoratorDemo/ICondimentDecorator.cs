using System;
namespace DecoratorDemo
{
	public interface ICondimentDecorator: IBeverage
	{
		string Description { get; }
	}
}
