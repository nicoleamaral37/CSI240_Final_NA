#include "Program.h"


int Elements::deduction;

const string Elements::OUTPUT_FILE = "ShortProgramDecoded.txt";
ofstream Elements::fout;
//fout.open(OUTPUT_FILE, ofstream::trunc);


string Elements::types[15] = {"toeloop", "salchow", "loop", "flip", "lutz", "axel",
"upright", "layback", "camel", "sit", "step", "upright special or combo", "layback special",
	"camel special, sit special", "combo special" };



Elements::Elements()
{
	type = AXEL;
	GOE = 0;
	//deduction = 0;
	totalGOE = 0;
	marking = "";
	
}

Elements::Elements(elTypes type, double GOE, int deduction, double bv = 0, string marking)
{
	this->type = type;
	//this->deduction = deduction;
	this->GOE = GOE;
	this->marking = marking;
	this->bv = bv;

}

double Elements::findTotalGOE()
{
	cout << "Total GOE: " << (GOE * .1) * bv << endl << "\n";
	return  (GOE*.1) * bv;
}

int Elements::getDeductions()
{
	return deduction;
}

double Elements::getGOE()
{
	return GOE;
}

elTypes Elements::getType()
	{
		return type;
	}


//SPINS AND SEQUENCES

const double SpinsAndSequences::upright[5] = { 1.0,1.2,1.5,1.9,2.4 };
const double SpinsAndSequences::layback[5] = { 1.2,1.5,1.9,2.4,2.7 };
const double SpinsAndSequences::camel[5] = { 1.1,1.4,1.8,2.3,2.6 };
const double SpinsAndSequences::sit[5] = { 1.1,1.3,1.6,2.1,2.5 };
const double SpinsAndSequences::step[5] = { 1.5,1.8,2.6,3.3,3.9 };

const double SpinsAndSequences::uprightSpecialOrCombo[5] = { 1.5,1.7,2.0,2.4,2.9 };
const double SpinsAndSequences::laybackSpecial[5] = { 1.7,2.0,2.4,2.9,3.2 };
const double SpinsAndSequences::camelSpecial[5] = { 1.6,1.9,2.3,2.8,3.2 };
const double SpinsAndSequences::sitSpecial[5] = { 1.7,2.0,2.3,2.6,3.0 };
const double SpinsAndSequences::comboSpecial[5] = { 1.7,2.0,2.5,3.0,3.5 };

//SpinsAndSequences constructors
SpinsAndSequences::SpinsAndSequences() : Elements(type, GOE, deduction,bv, marking)
{
	level = 0;
}

SpinsAndSequences::SpinsAndSequences(elTypes type, int level, double GOE, int deduction, double bv, string marking) : Elements(type, GOE, deduction, bv, marking)
{
	this->type = type;
	this->level = level;
	this->GOE = GOE;
	this->deduction += deduction;
	this->marking = marking;
}

void SpinsAndSequences::getDescription()
{	

	cout << "type: " << types[type] << endl
		<< "level: " << level << endl
		<< "GOE: " << GOE << endl
		<< "Total deductions: " << deduction << endl;

	fout << "type: " << types[type] << endl
		<< "level: " << level << endl
		<< "GOE: " << GOE << endl
		<< "Total deductions: " << deduction << endl;


}

int SpinsAndSequences::getLevel()
{
	return level;
}

//SpinsAndSequences calc member functions


double SpinsAndSequences::getBV()
{
	switch (type)
	{
	case 6: //upright

		bv = upright[level];
		bv += findTotalGOE();
		break;

	case 7: //layback
		bv = layback[level];
		bv += findTotalGOE();
		break;

	case 8: //camel

		bv = camel[level];
		bv += findTotalGOE();
		break;

	case 9: //sit
		bv = sit[level];
		bv += findTotalGOE();
		break;

	case 10: //step
		bv = step[level];
		bv += findTotalGOE();
		break;

	case 11: //upright or combo
		bv = uprightSpecialOrCombo[level];
		bv += findTotalGOE();
		break;


		//Flying or change of foot entries

	case 12: //Layback
		bv = laybackSpecial[level];
		bv += findTotalGOE();
		break;

	case 13: //camel
		bv = camelSpecial[level];
		bv += findTotalGOE();
		break;

	case 14: //sit
		bv = sitSpecial[level];
		bv += findTotalGOE();
		break;

	case 15: //combo
		bv = comboSpecial[level];
		bv += findTotalGOE();
		break;
	}
	return bv;
}


//JUMPS
const double Jumps::toeLoop[4] = { .40, 1.3, 4.2, 9.5 };
const double Jumps::salchow[4] = { .40, 1.3, 4.3, 9.7 };
const double Jumps::loop[4] = { .50, 1.7, 4.9, 10.5 };
const double Jumps::flip[4] = { .50, 1.8, 5.3, 11.0 };
const double Jumps::lutz[4] = { .60, 2.1, 5.9, 11.5 };
const double Jumps::axel[4] = { 1.0, 3.3, 8.0, 12.5 };

//Jumps Constructors
Jumps::Jumps() : Elements(type, GOE, deduction,bv, marking)
{
	rotations = 1;
}
Jumps::Jumps(elTypes type, int rotations, double GOE, int deduction, double bv, string marking) : Elements(type, GOE, deduction, bv, marking)
{
	this->type = type;
	this->rotations = rotations;
	this->GOE = GOE;
	this->deduction += deduction;
	this->marking = marking;
}

//get desc
void Jumps::getDescription()
{
	

	cout << "type: " << types[type] << endl
		<< "rotations: " << rotations << endl
		<< "GOE: " << GOE << endl
		<< "Total deductions: " << deduction << endl;

	fout << "type: " << types[type] << endl
		<< "level: " << rotations << endl
		<< "GOE: " << GOE << endl
		<< "Total deductions: " << deduction << endl;

	
}

int Jumps::getRotations()
{
	return rotations;
}
//Jumps calc member functions

void Jumps::decipherMarkings()
{
	if (type == LUTZ || type == FLIP)
	{
		if (marking.find("e<") != string::npos)
			bv = calcUnderRotatedAndE(bv);
			if (marking.find("X") != string::npos)
			{
				//cout << "BV: " << bv << endl;
				bv = calcSecondHalf(bv) + findTotalGOE();
			}
			else
				bv = calcUnderRotatedAndE(bv) + findTotalGOE();

		return;
	}

	if (marking.find("<") != string::npos || (type == LUTZ || type == FLIP && marking.find("e") != string::npos))
	{
		cout << "Marks: " << marking << endl;
		bv = calcUnderRotated(bv);
		if (marking.find("X") != string::npos)
		{
			//cout << "BV: " << bv << endl;
			bv = calcSecondHalf(bv) + findTotalGOE();
		}
		else
			bv = calcUnderRotated(bv) + findTotalGOE();
	}
	else
		bv += findTotalGOE();
}


double Jumps::getBV()
{

	switch (type)
	{
	case 0: //toeloop

		bv = toeLoop[rotations - 1];
		decipherMarkings();
		break;

	case 1: //salchow
		bv = salchow[rotations - 1];
		decipherMarkings();
		break;

	case 2: //loop

		bv = loop[rotations - 1];
		decipherMarkings();
		break;

	case 3: //flip both <e
		bv = flip[rotations - 1];
		decipherMarkings();
		break;

	case 4: //lutz both <e
		bv = lutz[rotations - 1];

		decipherMarkings();
		break;

	case 5: //axel
		bv = axel[rotations - 1];
		 decipherMarkings();
		break;
	}
	return bv;
}

double Jumps::calcE(double bv)
{
	return bv - (bv * .20);
}

double Jumps::calcUnderRotated(double bv)
{
	return bv - (bv * .20);
}

double Jumps::calcUnderRotatedAndE(double bv)
{
	return bv - (bv * .40);
}

double Jumps::calcSecondHalf(double bv)
{
	return bv * 1.1;
}




/*
if (marking == "<" || marking == "e")
{
	if (marking.find("X") != string::npos)
	{
		bv = calcSecondHalf(calcUnderRotated(lutz[rotations - 1]));
	}
	else
		bv = calcUnderRotated(lutz[rotations - 1]);

}
else if (marking.find("e<") != string::npos)

	if (marking.find("X") != string::npos)
	{
		bv = calcSecondHalf(calcUnderRotatedAndE(lutz[rotations - 1]));
	}
	else
		bv = calcUnderRotatedAndE(lutz[rotations - 1]);
else
	bv = lutz[rotations - 1];

	string oneLetter = element.substr(1, 1);

	if (oneLetter == "T")
	{
		tempType = TOELOOP;
	}
	else if (oneLetter == "S")
	{
		string twoLetters = element.substr(1, 2);
		if (element.substr(0, 2) == "Sp")
		{
			tempType = SIT;
		}
		else
		tempType = SALCHOW;
	}
	else if (oneLetter == "L")
	{
		string twoLetters = element.substr(1, 2);
		if (twoLetters == "Lo")
		{
			tempType = LOOP;
		}
		else if (twoLetters == "Lz")
		{
			tempType = LUTZ;
		}
		else if (element.substr(0, 2) == "LS")
		{
			tempType = LAYBACK;
		}
	}
	else if (oneLetter == "F")
	{
		tempType = FLIP;
	}
	else if (oneLetter == "A")
	{
		tempType = AXEL;
	}
	else if (oneLetter == "U")
	{
		tempType = UPRIGHT;
	}
	else if (oneLetter == "C")
	{
		tempType = CAMEL;
	}
	else //do error thingy?
	{
		cout << "Nope! Not a real element." << endl;
	}
	*/