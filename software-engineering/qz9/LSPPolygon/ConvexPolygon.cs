using System;
using System.Collections.Generic;

namespace LSPPolygon
{
	public class ConvexPolygon : IPolygon
	{
		private int sides = 4;
		private int radius;
		private List<int> xs = new List<int>();
		private List<int> ys = new List<int>();

		//private static readonly Random random = new Random();

		private static double RandAngle(double residual, int s)
		{
			//return random.NextDouble() * residual;
			return (2 * Math.PI / s) * 0.85;
		}

		private void VertexGen()
		{
			xs.Clear();
			ys.Clear();

			int cx = radius;
			int cy = radius;
			double res = 2 * Math.PI;
			double ang = 0.0;
			//double thr = 1.5 * (res / sides);

			for (int i = 0; i < sides; i++)
			{
				double rd = res;
				if (i < sides - 1)
				{
					rd = RandAngle(res, sides);
				}
				ang = ang + rd;
				res = res - rd;
				//Console.WriteLine("ang, res = " + ang + ", " + res);
				int x = cx + (int)(radius * Math.Sin(ang));
				int y = cy - (int)(radius * Math.Cos(ang));

				xs.Add(x);
				ys.Add(y);
			}

		}

		public int Sides
		{
			get
			{
				return sides;
			}

			set
			{
				int tmp = value;
				if (value < 4)
				{
					Console.WriteLine("The minimal number of sides of convex polygon must be 4.");
					tmp = 4;
				}
				sides = tmp;
				VertexGen();
			}
		}

		public int Radius
		{
			get
			{
				return radius;
			}

			set
			{
				int tmp = value;
				if (value < 10)
				{
					Console.WriteLine("The minimal circumradius must be 10.");
					tmp = 10;
				}
				radius = tmp;
				VertexGen();
			}
		}

		public void Draw()
		{
			Console.WriteLine("Convex Polygon");
			Console.WriteLine("Number of sides: " + sides);
			Console.WriteLine("Radius: " + radius);
			for (int i = 0; i < sides; i++)
			{
				int from = i;
				int to = (i + 1) % sides;

				int dx = xs[to] - xs[from];
				int dy = ys[to] - ys[from];
				double dis = Math.Round(Math.Sqrt(dx * dx + dy * dy), 2);

				Console.WriteLine("Draw line from " + xs[from] + ", " + ys[from] + " to "
								  + xs[to] + ", " + ys[to] + " length = " + dis);

			}
		}

		public double Area() {
			int sum = 0;
			for (int i = 0; i < sides; i++)
			{
				int from = i;
				int to = (i + 1) % sides;

				//(xs[from] * ys[to]) - (ys[from] * xs[to])
				sum = sum + ((xs[to] - xs[from]) * (ys[to] + ys[from]));
			}
			
			return Math.Abs((double)sum / 2.0);

			//return Math.Abs(vertices.Take(vertices.Count - 1).Select((p, i) => (p.X * vertices[i + 1].Y) - (p.Y * vertices[i + 1].X)).Sum() / 2);
		}

		public double Perimeter() {
			double res = 0.0;
			for (int i = 0; i < sides; i++)
			{
				int from = i;
				int to = (i + 1) % sides;

				int dx = xs[to] - xs[from];
				int dy = ys[to] - ys[from];
				double dis = Math.Round(Math.Sqrt(dx * dx + dy * dy), 2);
				res = res + dis;
			}
			return Math.Abs(res);
		}

	}
}
