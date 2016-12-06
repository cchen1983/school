using System;
using System.Diagnostics;

namespace LSPPolygon
{
	public class PolygonFactory
	{

		public IPolygon GetPolygon(string type)
		{
			if (type == "Convex")
			{
				return new ConvexPolygon();
			}
			else {
				return null;
			}
		}
	}

	class MainClass
	{
		public static void Main(string[] args)
		{
			try
			{
				PolygonFactory factory = new PolygonFactory();

				while (true)
				{
					Console.WriteLine("\nPlease input the bounding radius: ");
					string radius = Console.ReadLine();
					Console.WriteLine("Please input the number of sides: ");
					string sides = Console.ReadLine();

					IPolygon poly = factory.GetPolygon("Convex");
					poly.Radius = int.Parse(radius);
					poly.Sides = int.Parse(sides);


					// data invariant
					Debug.Assert((poly.Radius >= 10), "Radius of bounding circle can't be 0 or less!");
					Debug.Assert((poly.Sides >= 4), "Convex Polygon sides can't be less than 4!");

					poly.Draw();
					Console.WriteLine("Area is: " + poly.Area());
					Console.WriteLine("Perimeter is: " + poly.Perimeter());
				}
			}
			catch (Exception ex)
			{
				Console.WriteLine("Runtime error: " + ex.Message);
			}
		}
	}
}
