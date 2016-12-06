using System;
namespace ShapeFactorySRP
{
	public interface IShape
	{
		double Area();
		double Circumference();

		string Name { get; set; }

		Int32 Height { get; set; }  // Height of bounding box of shape
		Int32 Width { get; set; }   // Width of bounding box of shape
		Int32 PivotX { get; set; }  // X coordinate of top‐left point
		Int32 PivotY { get; set; }  // Y coordinate of top‐left point
	}
}
