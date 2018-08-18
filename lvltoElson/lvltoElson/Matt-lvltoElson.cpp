#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
struct groups
{
	int x = 0;
	int y = 0;
	int height = 0;
	int width = 1;
};
//MAIN FUNCTION
void main()
{
	std::vector<std::string> map;
	std::string readfromfile;
	std::string totallength;
	//+++++++
	std::vector<groups> grps;
	std::vector<groups> result;
	//+++++++
	std::ifstream loadlevel;
	loadlevel.open("test.txt");
	while (std::getline(loadlevel, readfromfile))
	{
		totallength += readfromfile;
		map.push_back(readfromfile);
	}

	std::cout << totallength << std::endl;
	int startPosX = 0;
	int startPosY = 0;
	int width = 1;
	int height = 0;
	bool walls = false;
	int buffer = 0;
	//Open Output file
	std::ofstream outputfile;
	outputfile.open("leevl.txt");
	std::cout << totallength.length() << std::endl;
	for (int x = 0; x <= map[0].length(); x++)
	{
		startPosX = x;
		startPosY = 0;
		walls = false;
		height = 0;
		for (int y = 0; y < map.size(); y++)
		{
			if (map[y][x] == '#')
			{
				if (!walls)
				{
					startPosY = y;
				}
				walls = true;	
				height++;
				
			}
			else if (map[y][x] == '0' && walls)
			{
				groups d;
				grps.push_back(d);
				grps[buffer].x = startPosX;
				grps[buffer].y = startPosY;
				grps[buffer].height = height;
				buffer++;
				walls = false;
				height = 0;
				width = 1;
			}
		}
		if (walls)
		{
			groups d;
			grps.push_back(d);
			grps[buffer].x = startPosX;
			grps[buffer].y = startPosY;
			grps[buffer].height = height;
			buffer++;
			walls = false;
			height = 0;
			width = 1;
		}
		
	}
	buffer = 0;
	for (int i = 0; i < grps.size(); i++)
	{
		bool adjacent = false;
		for (int f = 0; f < result.size(); f++)
		{
			if (result[f].x == (grps[i].x-result[f].width) && result[f].y == grps[i].y && result[f].height == grps[i].height)
			{				
				result[f].width++;
				adjacent = true;
			}
		}
		if (!adjacent)
		{
			groups n;
			result.push_back(n);
			result[buffer].x = grps[i].x;
			result[buffer].y = grps[i].y;
			result[buffer].height = grps[i].height;
			buffer++;
		}
	}
	for (int i = 0; i < result.size(); i++)
	{
		std::cout << "GameObject=Wall," << result[i].x << "-" << result[i].y << "," << result[i].width << "," << result[i].height << std::endl;
		outputfile << "GameObject=Wall," << result[i].x << "-" << result[i].y << "," << result[i].width << "," << result[i].height << std::endl;
	}
		std::cin >> totallength;

	loadlevel.close();
	outputfile.close();
	
}