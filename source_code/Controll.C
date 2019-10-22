#include "ZZZAna.h"
#include "makeHists.h"
#include <iostream>
#include <fstream>
#include "TH1D.h"

using namespace std;
int main(int argc, char ** argv)
{
 //usage output
 if(argc != 4)
// if(argc != 3)
 std::cout<<"usage : ./ZZZAna.exe filelist type year"<<std::endl;

 //read in filelist
 ifstream infile;
  infile.open(argv[1],ios::in);

 int count = 0;
 
 cout<<"**********************************"<<endl;
 cout<<"***********ZZZAna Begin***********"<<endl;
 cout<<"**********************************"<<endl;
 cout<<endl;
 
 ZZZAna Run(argv[1], argv[2]);
 
 TString inputRoot;
 while(infile>>inputRoot)
  {
   count++;
   Run.Initial(inputRoot, count);
   Run.Loop(argv[2],argv[3]);
//   Run.Loop(argv[2]);
   Run.End(count);
  }

 infile.close();
 Run.Save(count);
 cout<<endl;
 cout<<"**********************************"<<endl;
 cout<<"************ZZZAna End************"<<endl;
 cout<<"**********************************"<<endl;

 return 1;

}
