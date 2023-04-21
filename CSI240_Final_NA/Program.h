#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>


using namespace std;



enum elTypes
{
	TOELOOP = 0,
	SALCHOW,
	LOOP,
	FLIP,
	LUTZ,
	AXEL,
	UPRIGHT,
	LAYBACK,
	CAMEL,
	SIT,
	STEP,
	UPRIGHTSPECIALORCOMBO,
	LAYBACKSPECIAL,
	CAMELSPECIAL,
	SITSPECIAL,
	COMBOSPECIAL
};




void splitLine(string element, vector<string>& infoPieces);


void assignType(string element, elTypes& tempType, vector<string>& infoPieces);

class Elements 
{
public:
	Elements();
	Elements(elTypes type, double GOE, int deduction, double bv, string marking="");
	double findTotalGOE();
	int getDeductions();

	elTypes getType();
	double getGOE();

	
	virtual void getDescription () = 0;
	virtual double getBV() = 0;
	friend std::ostream& operator<<(ostream& out, Elements*& el);
protected:
	double totalGOE;
	double bv;
	double GOE;
	elTypes type;
	string marking;
	static int deduction;
	static string types[15];
	static const string OUTPUT_FILE;
	static ofstream fout;

	
};


//SPINS
class SpinsAndSequences : public Elements
{
public:
	SpinsAndSequences();
	SpinsAndSequences(elTypes type, int level, double GOE, int deduction, double bv, string marking);
	void getDescription();
	double getBV();
	//friend istream& operator>>(istream& in, SpinsAndSequences& SpinOrSeq);
	
	int getLevel();
	
protected:
	int level;

	static const double upright[5];
	static const double layback[5];
	static const double camel[5];
	static const double sit[5];
	static const double step[5];

	static const double uprightSpecialOrCombo[5];
	static const double laybackSpecial[5];
	static const double camelSpecial[5];
	static const double sitSpecial[5];
	static const double comboSpecial[5];

};




//JUMPS

class Jumps : public Elements
{
public:

	Jumps();
	Jumps(elTypes type, int rotations, double GOE, int deduction, double bv, string marking);
	void getDescription();
	double calcE(double bv);
	double calcUnderRotated(double bv);
	double calcUnderRotatedAndE(double bv);
	double calcSecondHalf(double bv);
	void decipherMarkings();
	double getBV();

	int getRotations();

	friend ostream& operator>>(ostream& out, Jumps& jump);

	
	
protected:
	double euler = .50;
	int rotations;

	static const double toeLoop[4];
	static const double salchow[4];
	static const double loop[4];
	static const double flip[4];
	static const double lutz[4];
	static const double axel[4];

};

istream& operator>>(istream& in, SpinsAndSequences& SpinOrSeq);
istream& operator>>(istream& in, Jumps& jump);

Elements* findInfo(string element, double &total); 



