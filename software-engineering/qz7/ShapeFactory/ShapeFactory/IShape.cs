using System;
namespace ShapeFactory
{
	public interface IShape
	{
		void Draw();

		double Area();
		double Circumference();

		string Name { get; set; }
	}
}
