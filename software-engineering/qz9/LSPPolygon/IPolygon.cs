using System;
namespace LSPPolygon
{
	public interface IPolygon
	{
		int Radius { get; set; } 	// bounding circumradius
		int Sides { get; set; }
 		double Area();
		double Perimeter();
		void Draw();
	}
}
