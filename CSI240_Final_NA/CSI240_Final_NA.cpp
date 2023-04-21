

#include "Program.h"



int main()
{
    const string FILE_NAME = "ShortProgram.txt";
    ifstream fin;

     const string OUTPUT_FILE = "shortProgramDecoded.txt";
        ofstream fout;
        fout.open(OUTPUT_FILE, ofstream::trunc);



    vector<Elements*> shortProgram;
    string elementInfo;
    elTypes tempType;
    double total = 0;

    int tempIndex = 0;

    fin.open(FILE_NAME);

    if (fin.good())
    {
        while (!fin.eof())
        {
            getline(fin, elementInfo);
            shortProgram.push_back(findInfo(elementInfo, total));
           // shortProgram[shortProgram.size() - 1]->getDescription();
            // shortProgram[0]->getDescription();

            shortProgram[0]->getDescription();
            // total += shortProgram[0]->getBV();





         //  cout << shortProgram[tempIndex-1];


             //for (Elements* i : shortProgram)
               //  i->getDescription();

            /*for (int i = 0; i < shortProgram.size(); i++)
            {

                //cout << shortProgram.size() << endl;
                shortProgram[i]->getDescription();
            }
             */


        }
        cout << endl << total << " " << total - shortProgram[shortProgram.size()-1]->getDeductions() << endl;



        
    }

    for (int i = 0; i < shortProgram.size(); i++)
    {
        delete shortProgram[i];
        shortProgram[i] = nullptr;
    }
    shortProgram.clear();
    
}






   // shortProgram->findTotalGOE;

   /* for (int i = 0; i < shortProgram.size(); i++)
    {
        // if(shortProgram[i]->findTotalGOE)
        total += shortProgram[i]->getBV();
        cout << total << "total" << endl;
    }
    cout << total << "total" << endl;

    char ans;
    char ans2;
    do {
        cout << "Would you like to add another element? 'y' for yes, any other key to exit" << endl;
        cin >> ans;
        do {
            cout << "Would you like to add a Jump (j), Spin or Sequence (s)?" << endl;
            cin >> ans2;
        } while (ans2 != 'j' || ans2 != 's');

        if (ans2 == 'j')
        {

        }
        
    } while (ans == 'y');
    */



