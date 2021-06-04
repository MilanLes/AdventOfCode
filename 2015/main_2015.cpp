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

	cout << "Floor: " << floor << endl;
	// Part two
	cout << "Basement position: " << basement_position << endl;

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
}

void day_5()
{
	ifstream input_file;
	input_file.open("2015_day5_input");
	string line;
	int niceStrings = 0;

	// read file line by line
	while(getline(input_file, line))
		if(IsNewNiceString(line)) niceStrings++;

	cout << "Nice strings: " << niceStrings << endl;
	input_file.close();
}

void day_6()
{
	
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
		case 6: day_6(); break;
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
	
	day_6();

	return 0;
}
