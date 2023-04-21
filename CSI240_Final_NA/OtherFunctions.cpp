#include "program.h"

std::ostream& operator<<(std::ostream& out, Elements*& el)
{
	string types[15] = { "toeloop", "salchow", "loop", "flip", "lutz", "axel",
"upright", "layback", "camel", "sit", "step", "upright special or combo", "layback special",
	"camel special, sit special", "combo special" };

	if (el->getType() == 0 ||
		el->getType() == 1 ||
		el->getType() == 2 ||
		el->getType() == 3 ||
		el->getType() == 4 ||
		el->getType() == 5)
	{
		Jumps* onlyJump = static_cast<Jumps*>(el);
		out << "Type: " << types[onlyJump->getType()] << "\n" <<
			"Rotations: " << onlyJump->getRotations() << "\n" <<
			"GOE: " << onlyJump->getGOE() << "\n" <<
			"Score: " << onlyJump->getBV() << "\n";
	}
	else
	{
		SpinsAndSequences* onlySpinOrSeq = static_cast<SpinsAndSequences*>(el);
		out << "Type" << onlySpinOrSeq->getType() << "\n" <<
			"level" << onlySpinOrSeq->getLevel();
	}
	
	return out;
}

void splitLine(string element, vector<string>& infoPieces)
{
	string s;
	stringstream sin(element);
	while (getline(sin, s, ' '))
	{

		infoPieces.push_back(s);
	}

	//test printing
	/*for (int i = 0; i < infoPieces.size(); i++)
	{
		cout << infoPieces[i] << endl;
	}
	*/
	
	

	if (infoPieces.size() < 3)
	{
		string ex = "Not a complete element!";

		throw ex;
	}
}

void assignType(string element, elTypes& type, vector<string>& infoPieces)
{

	if (element.find("Sp") != string::npos)
	{
		if (element.find("USp") != string::npos)
		{
			if (element.find("FUSp") != string::npos || element.find("CUSp") != string::npos || element.find("CoSp") != string::npos)
			{
				type = UPRIGHTSPECIALORCOMBO;
			}
			else
				type = UPRIGHT;
		}
		else if (element.find("LSp") != string::npos)
		{
			if (element.find("FLSp") != string::npos || element.find("CLSp") != string::npos)
			{
				type = LAYBACKSPECIAL;
			}
			else
				type = LAYBACK;
		}
		else if (element.find("CSp") != string::npos)
		{
			if (element.find("FCSp") != string::npos || element.find("CCSp") != string::npos)
			{
				type = CAMELSPECIAL;
			}
			else
				type = CAMEL;
		}
		else if (element.find("SSp") != string::npos)
		{
			if (element.find("FSSp") != string::npos || element.find("CSSp") != string::npos)
			{
				type = SITSPECIAL;
			}
			else
				type = SIT;
		}
		else if (element.find("StSq") != string::npos)
		{
			type = STEP;
		}
		else if (element.find("CCoSp") != string::npos)
		{
			type = COMBOSPECIAL;
		}
		else
		{
			string ex = "Nope! Not a real element.";
			throw ex;
		}
		cout << "Spin Type: " << type << endl;

	}
	else
	{
		string oneLetter = element.substr(1, 1);

		if (oneLetter == "T")
		{
			type = TOELOOP;
		}
		else if (oneLetter == "S")
		{
			type = SALCHOW;
		}
		else if (oneLetter == "L")
		{
			string twoLetters = element.substr(1, 2);
			if (twoLetters == "Lo")
			{
				type = LOOP;
			}
			else if (twoLetters == "Lz")
			{
				type = LUTZ;
			}
		}
		else if (oneLetter == "F")
		{
			type = FLIP;
		}
		else if (oneLetter == "A")
		{
			type = AXEL;
		}
		else //do error thingy?
		{
			string ex = "Nope! Not a real element.";
			throw ex;
			return;

		}
	}

	if (infoPieces[0].find("e") != string::npos && (type == TOELOOP || type == SALCHOW || type == LOOP || type == AXEL))
	{
		string ex = "Cannot compute! e is not valid for this type of jump.";

		throw ex;
		return;
	}
}

//Takes info from file and makes all necessary function calls to break up and initilize data

Elements* findInfo(string element, double &total)
{
	string types[15] = {"toeloop", "salchow", "loop", "flip", "lutz", "axel",
"upright", "layback", "camel", "sit", "step", "upright special or combo", "layback special",
	"camel special, sit special", "combo special"}; 

	 elTypes type;
	 double GOE;
	 int deduction;
	 int rotations;
	 int level;
	 string marking;
	 double bv = 0;
	

	 

	// Finds rotations, GOE, deductions and throws an expection if missing necessary details
	vector<string> infoPieces;
	try
	{
		splitLine(element, infoPieces);
		string lastChar = infoPieces[0].substr(infoPieces[0].length() - 1, 1);
		//cout << "bro what: " << infoPieces[0].substr(infoPieces[0].length() -1, 1) << endl;
		GOE = stoi(infoPieces[1]);
		deduction = stoi(infoPieces[2]);

		for (int i = 0; i < 5; i++)
		{
			if (element.substr(0, 1) == to_string(i))
			{
				if (stoi(element.substr(0, 1)) <= 0 || stoi(element.substr(0, 1)) >= 5)
				{

					cout << "NOOOO" << endl;
					type = AXEL;
					GOE = 0;
					deduction = 0;
					rotations = 0;
					level = 0;
					marking = "";
					//return;

				}
				else if (stoi(element.substr(0, 1)) == i)
				{
					rotations = stoi(element.substr(0, 1));
				}
			}
			else if (lastChar == to_string(i))
			{
				level = stoi(lastChar);
				//cout << "yay!" << endl;
			}
		}
	}
	catch (string ex)
	{
		cout << endl << ex << endl << "\n";

		//reset and exit function
		type = AXEL;
		GOE = 0;
		deduction = 0;
		rotations = 0;
		level = 0;
		marking = "";
		//return;
	}

	// looks for special markings
	if (infoPieces[0].find("e") != string::npos)
	{
		marking += "e";
	}
	if (infoPieces[0].find("<") != string::npos)
	{
		marking += "<";
	}
	if (infoPieces[0].find("X") != string::npos)
	{
		marking += "X";
	}

	//Assigns jump/spin/sequence type and throws exception if element contains incorrect marking
	try
	{
		assignType(element, type, infoPieces);
	}
	catch (string ex)
	{
		cout << endl << ex << endl << "\n";

		//reset and exit function
		type = AXEL;
		GOE = 0;
		deduction = 0;
		rotations = 0;
		level = 0;
		marking = "";
		
		
	}



	if (type == 0 ||
		type == 1 ||
		type == 2 ||
		type == 3 ||
		type == 4 ||
		type == 5 &&
		rotations != 0)
	{
		
		Elements* anElement = new Jumps(type, rotations, GOE, deduction, bv, marking);
		anElement->getDescription();
		//shortProgram.push_back(aJump);
	
		//Jumps* onlyJump = static_cast<Jumps*>(anElement);
		total += anElement->getBV();
		//cout << types[type] << " " << onlyJump->getBV() << endl;
	
		return anElement;
	}
	else if (type == 6 ||
		type == 7 ||
		type == 8 ||
		type == 9 ||
		type == 10 ||
		type == 11 ||
		type == 12 ||
		type == 13 ||
		type == 14 ||
		type == 15 &&
		level != 0)
	{
		
		Elements* anElement = new SpinsAndSequences(type, level, GOE, deduction, bv, marking);
		//shortProgram.push_back(anElement);
		anElement->getDescription();
		//SpinsAndSequences* onlySpinOrSeq = static_cast<SpinsAndSequences*>(anElement);
		total += anElement->getBV();
		//cout << anElement;
	
		return anElement;
		//cout << types[type] << " " << onlySpinOrSeq->getBV() << endl;
	}
	
}

/*ostream& operator>>(ostream& out, Jumps& jump)
{
	out << jump.rotations;
	return out;
}
*/

/*istream& operator>>(istream& in, SpinsAndSequences& SpinOrSeq)
{
	cout << "Enter hours: ";
	//in >> clock.hour;
	cout << "Enter minutes: ";
	//in >> clock.minute;
	return in;
}
*/
