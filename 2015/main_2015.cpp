#include "helpers_2015.h"

/*
 *	find tasks here: https://adventofcode.com/2015
 */

using namespace std;

void log_err(string err_message)
{
	cout << err_message << endl;
}

void SantaPosition::Move(char santaDir)
{
	switch(santaDir)
	{
		case '>': x++; break;
		case '<': x--; break;
		case '^': y++; break;
		case 'v': y--; break;
		default:
			cout << "Wrong direction for Santa!" << endl;
	}
}

bool IsOldNiceString(string line)
{
	vector<string> forbiddenCombination = {"ab", "cd", "pq", "xy"};
	int vows = 0;
	string vowels = "aeiou";
	bool bDoublet = false;
	for(size_t strIter = 0; strIter < line.length(); strIter++)
	{
		// check for vowels
		for(char v : vowels)
			if(line[strIter] == v) vows++;

		string doubleChar = line.substr(strIter, 2);
		
		// disqualify forbidden strings
		for(string forbid : forbiddenCombination)
			if(doubleChar == forbid) return false;

		if(doubleChar[0] == doubleChar[1])
			bDoublet = true;
	}
	
	if(bDoublet && vows > 2) return true;
	
	return false;
}

bool IsNewNiceString(string line)
{
	bool bHasThreesome = false;
	bool bHasDoubles = false;

	for(size_t strIter = 0; strIter < line.length() - 1; strIter++)
	{
		if(line[strIter] == line[strIter + 2])
			bHasThreesome = true;

		string doublet = line.substr(strIter, 2);

		if(line.find(doublet, strIter + 2) != string::npos)
			bHasDoubles = true;
	}

	return bHasThreesome && bHasDoubles;
}

void day_1()
{
	ifstream input_file;
	input_file.open("2015_day1_input");
	string input_string;
	getline(input_file, input_string);
	int string_iter = 0;
	int floor = 0;
	// Part two
	int basement_position = -1;
	while(string_iter < input_string.length())
	{
		if(input_string[string_iter] == '(')
			floor++;
		else if(input_string[string_iter] == ')')
			floor--;
		else 
			log_err("Wrong floor input!");

		// Part two
		if(floor == -1 && basement_position < 0)
			basement_position = string_iter + 1;

		string_iter++;
	}

	cout << "Floor (part one): " << floor << endl;
	// Part two
	cout << "Basement position (part two): " << basement_position << endl;

	input_file.close();
}

void day_2()
{
	ifstream input_file;
	input_file.open("2015_day2_input");
	string line;
	long packing_paper = 0;
	// Part two
	long ribbon_length = 0;
	while(getline(input_file, line))
	{
		stringstream stream(line);
		string num;
		int width = 0, length = 0, height = 0;
		getline(stream, num,'x');
		length = stoi(num);
		getline(stream, num,'x');
		width = stoi(num);
		getline(stream, num,'x');
		height = stoi(num);
		
		if(width == 0 || length == 0 || height == 0)
			log_err("Zero value input dimension!");
		
		int smallest_area = length < width
			? width < height ? length*width : length*height
			: length < height ? width*length : width*height;

		// Part two
		int smallest_length = length < width
			? width < height ? length+width : length+height
			: length < height ? width+length : width+height;

		packing_paper += 2*length*width + 2*width*height + 2*height*length + smallest_area;
		// Part two
		ribbon_length += 2 * smallest_length + width * length * height;
	}

	cout << "Packing paper (part 1): " << packing_paper << endl;
	// Part two
	cout << "Ribbon length (part 2): " << ribbon_length << endl;

	input_file.close();
}

void day_3()
{
	ifstream input_file;
	input_file.open("2015_day3_input");
	string line;
	getline(input_file, line);
	int string_iter = 0;
	SantaPosition santaPos(0,0);
	// Part two
	SantaPosition robosantaPos(0,0);
	vector<SantaPosition> santas;

	vector<SantaPosition> houses;
	houses.emplace_back(santaPos);
	
	// Part two
	santas.emplace_back(santaPos);
	santas.emplace_back(robosantaPos);

	while(string_iter < line.length())
	{	
		// Part two
		for(int iter = 0; iter < 2; iter++)
		{
			santas[iter].Move(line[string_iter]);
			bool santaVisited = false;
			for(SantaPosition dom : houses)
			{
				if(dom == santas[iter])
				{
					santaVisited = true;
					break;
				}
			}

			if(!santaVisited)
				houses.emplace_back(santas[iter]);
			string_iter++;
		}
	}

	cout << "Houses with gifts: " << houses.size() << endl;
}

void day_4()
{
	// use some language with native MD5
	/* somehing like php
	<?php
	$str = "bgvyzdsv";
	$str_iter = 0;
	$res_string = '';
	$str_to_encode = '';
	while(strcmp(substr($res_string, 0, 6), "000000") != 0)
	{
		$str_iter++;
		$str_to_encode = $str.strval($str_iter);
		$res_string = md5($str_to_encode);
	};

	echo $res_string."\t".$str_to_encode."\t".$str_iter."\n";
	// 000000b1b64bf5eb55aad89986126953        bgvyzdsv1038736     1038736
	?>
	*/
	cout << "Solve this day in another lagnuage which has MD5 already implemented!" << endl;
}

void day_5()
{
	ifstream input_file;
	input_file.open("2015_day5_input");
	string line;
	int niceStrings = 0;

	while(getline(input_file, line))
		if(IsOldNiceString(line)) niceStrings++;
	cout << "Nice strings (part one): " << niceStrings << endl;

	niceStrings = 0;

	// read file line by line
	while(getline(input_file, line))
		if(IsNewNiceString(line)) niceStrings++;

	cout << "Nice strings (part two): " << niceStrings << endl;
	input_file.close();
}

void day_6_1()
{
	const int grid_size = 1000;
	bool grid[grid_size][grid_size] = { false };
	
	ifstream input_file;
	input_file.open("2015_day6_input");
	string line;

	while(getline(input_file, line))
	{
		stringstream lineToParse(line);
		// turn on 943,30 through 990,907
		// turn off 674,321 through 793,388
		// toggle 749,672 through 973,965
		string tempStr;
		getline(lineToParse, tempStr, ' ');

		LightOperation lightOp = LightOperation::eUnknown;
		int startX = -1, startY = -1, endX = -1, endY = -1;

		if(tempStr == "toggle")
		{
			lightOp = eToggle;
		}
		else if(tempStr == "turn")
		{
			getline(lineToParse, tempStr, ' ');
			if(tempStr == "on")
			{
				lightOp = eTurnOn;
			}
			else if(tempStr == "off")
			{
				lightOp = eTurnOff;
			}
			else
			{
				log_err("Undefined turn operation detected");
			}
		}
		else
		{
			log_err("Undefined light action detected!");
		}
		
		if(lightOp == LightOperation::eUnknown)
			log_err("Error reading light operation");
		
		getline(lineToParse, tempStr, ',');
		startX = stoi(tempStr);
		getline(lineToParse, tempStr, ' ');
		startY = stoi(tempStr);

		getline(lineToParse, tempStr, ' ');
		if(tempStr != "through")
			log_err("Through issue!");

		getline(lineToParse, tempStr, ',');
		endX = stoi(tempStr);
		getline(lineToParse, tempStr);
		endY = stoi(tempStr);

		if(startX < 0 || startY < 0 || endX < 0 || endY < 0)
			log_err("Coordinates error!");

		for(int xIter = startX; xIter <= endX; xIter++)
			for(int yIter = startY; yIter <= endY; yIter++)
				if(lightOp == LightOperation::eTurnOn)
					grid[xIter][yIter] = true;
				else if(lightOp == LightOperation::eTurnOff)
					grid[xIter][yIter] = false;
				else if(lightOp == LightOperation::eToggle)
					grid[xIter][yIter] = !grid[xIter][yIter];
				else log_err("wrong stuff going on with grid!");
	}

	input_file.close();

	// count the lights
	int lightsOn = 0;
	for(int x = 0; x < grid_size; x++)
		for(int y = 0; y < grid_size; y++)
			if(grid[x][y] == true) lightsOn++;

	cout << "total lights on: " << lightsOn << endl;
}

void day_6_2()
{
	const int grid_size = 1000;
	int grid[grid_size][grid_size] = { 0 };

	ifstream input_file;
	input_file.open("2015_day6_input");
	string line;

	while(getline(input_file, line))
	{
		stringstream lineToParse(line);
		string tempStr;
		getline(lineToParse, tempStr, ' ');

		LightOperation lightOp = LightOperation::eUnknown;
		int startX = -1, startY = -1, endX = -1, endY = -1;

		if(tempStr == "toggle")
		{
			lightOp = eToggle;
		}
		else if(tempStr == "turn")
		{
			getline(lineToParse, tempStr, ' ');
			if(tempStr == "on")
				lightOp = eTurnOn;
			else if(tempStr == "off")
				lightOp = eTurnOff;
			else
				log_err("Undefined turn operation detected");
		}
		else
		{
			log_err("Undefined light action detected!");
		}
		
		if(lightOp == LightOperation::eUnknown)
			log_err("Error reading light operation");
		
		getline(lineToParse, tempStr, ',');
		startX = stoi(tempStr);
		getline(lineToParse, tempStr, ' ');
		startY = stoi(tempStr);

		getline(lineToParse, tempStr, ' ');
		if(tempStr != "through")
			log_err("Through issue!");

		getline(lineToParse, tempStr, ',');
		endX = stoi(tempStr);
		getline(lineToParse, tempStr);
		endY = stoi(tempStr);

		if(startX < 0 || startY < 0 || endX < 0 || endY < 0)
			log_err("Coordinates error!");

		for(int xIter = startX; xIter <= endX; xIter++)
			for(int yIter = startY; yIter <= endY; yIter++)
			{
				if(lightOp == LightOperation::eTurnOn)
				{	
					grid[xIter][yIter] += 1;
				}
				else if(lightOp == LightOperation::eTurnOff)
				{
					if(grid[xIter][yIter] > 0)
						grid[xIter][yIter] -= 1;
				}	
				else if(lightOp == LightOperation::eToggle)
				{
					grid[xIter][yIter] += 2;
				}
				else log_err("wrong stuff going on with grid!" + lightOp);
			}
	}

	input_file.close();

	// count the lights
	int totalBrightness = 0;
	for(int x = 0; x < grid_size; x++)
		for(int y = 0; y < grid_size; y++)
			totalBrightness += grid[x][y];

	cout << "total brightness: " << totalBrightness << endl;
}

void day_7()
{
	ifstream input_file;
	input_file.open("2015_day7_input");
	string line;
	vector<int> wires;
	vector<string> sample_input = 
	{
		"123 -> x",
		"456 -> y",
		"x AND y -> d",
		"x OR y -> e",
		"x LSHIFT 2 -> f",
		"y RSHIFT 2 -> g",
		"NOT x -> h",
		"NOT y -> i"
	};
	/*
	d: 72
	e: 507
	f: 492
	g: 114
	h: 65412
	i: 65079
	x: 123
	y: 456
	*/
	//while(getline(input_file, line))
	for(string line : sample_input)
	{
		cout << line << endl;
	}

	input_file.close();
}

int main()
{
	/*
	short day_choice = -1;
	cout << "Advent of Code 2015" << endl;
	do
	{
		cout << "Enter day to solve. Enter 0 to end.\nDay choice: ";
		cin >> day_choice;
		switch (day_choice)
		{
		case 1: day_1(); break;
		case 2: day_2(); break;
		case 3: day_3(); break;
		case 4: day_4(); break;
		case 5: day_5(); break;
		case 6: day_6_1(); day_6_2(); break;
		case 7: day_7(); break;
		case 8: day_8(); break;
		case 9: day_9(); break;
		case 10: day_10(); break;
		case 11: day_11(); break;
		case 12: day_12(); break;
		case 13: day_13(); break;
		case 14: day_14(); break;
		case 15: day_15(); break;
		case 16: day_16(); break;
		case 17: day_17(); break;
		case 18: day_18(); break;
		case 19: day_19(); break;
		case 20: day_20(); break;
		case 21: day_21(); break;
		case 22: day_22(); break;
		case 23: day_23(); break;
		case 24: day_24(); break;
		case 25: day_25(); break;
		default:
			break;
		}
	} while(day_choice != 0);*/
	
	day_7();

	return 0;
}
