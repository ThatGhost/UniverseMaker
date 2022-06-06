#pragma once

struct Planet
{
	double distance = 0.0;
	double radius = 0.0;
	double foliage = 0.0;
	double minerals = 0.0;
	double water = 0.0;
	double gases = 0.0;
	double temperature = 0.0;
	double population = 0.0;
	bool ring = false;
	std::vector<double> vMoons;
};


class StarSystem
{
public:
	StarSystem(uint32_t x, uint32_t y, bool bGenerateFullSystem = false)
	{
		nProcGen = (x & 0xFFFF) << 16 | (y & 0xFFFF);

		starExists = (rndInt(0, 20) == 1);
		if (!starExists) return;

		starDiameter = rndDouble(10.0, 24.0);
		c = g_starColours[rndInt(0,5)];

		if (!bGenerateFullSystem) return;

		double dDistanceFromStar = rndDouble(60.0, 200.0);
		int nPlanets = rndInt(0, 8);
		for (int i = 0; i < nPlanets; i++)
		{
			Planet p;
			p.distance = dDistanceFromStar;
			dDistanceFromStar += rndDouble(20.0, 200.0);
			p.radius = rndDouble(4.0, 12.0);

			p.temperature = rndDouble(-200.0, 300.0);

			/*p.foliage = rndDouble(0.0, 1.0);
			p.minerals = rndDouble(0.0, 1.0);
			p.gases = rndDouble(0.0, 1.0);
			p.water = rndDouble(0.0, 1.0);

			double dSum = 1.0 / (p.foliage + p.minerals + p.gases + p.water);
			p.foliage *= dSum;
			p.minerals *= dSum;
			p.gases *= dSum;
			p.water *= dSum;*/

			//p.population = std::max(rndInt(-5000000, 20000000), 0);

			p.ring = rndInt(0, 10) == 1;

			int nMoons = std::max(rndInt(-5, 5), 0);
			for (int n = 0; n < nMoons; n++)
			{
				p.vMoons.push_back(rndDouble(1.0, 5.0));
			}

			// Add planet to vector
			Planets.push_back(p);
		}
	}

	~StarSystem()
	{

	}

public:
	std::vector<Planet> Planets;
	bool starExists = false;
	double starDiameter = 10.0f;
	Color4f c{};
private:
	Color4f g_starColours[5] =
	{
		Color4f(235 / 255.0, 64 / 255.0, 52 / 255.0, 1.0f),
		Color4f(235 / 255.0, 125 / 255.0, 52 / 255.0, 1.0f),
		Color4f(235 / 255.0, 162 / 255.0, 52 / 255.0, 1.0f),
		Color4f(235 / 255.0, 198 / 255.0, 52 / 255.0, 1.0f),
		Color4f(208 / 255.0, 235 / 255.0, 52 / 255.0, 1.0f)
	};

	uint32_t nProcGen = 0;

	double rndDouble(double min, double max)
	{
		return ((double)rnd() / (double)(0x7FFFFFFF)) * (max - min) + min;
	}

	int rndInt(int min, int max)
	{
		return (rnd() % (max - min)) + min;
	}

	uint32_t rnd()
	{
		nProcGen += 0xe120fc15;
		uint64_t tmp;
		tmp = (uint64_t)nProcGen * 0x4a39b70d;
		uint32_t m1 = (tmp >> 32) ^ tmp;
		tmp = (uint64_t)m1 * 0x12fad5c9;
		uint32_t m2 = (tmp >> 32) ^ tmp;
		return m2;
	}
};

