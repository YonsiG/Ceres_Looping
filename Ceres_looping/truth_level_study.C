#define _ZZZANA_C_
#include "ZZZAna.h"
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "TMath.h"
#include "math.h"
#include "TH1D.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "TLorentzVector.h"
#include "Math/LorentzVector.h"
#include "Math/Point3D.h"
#include "TH3F.h"
#include <TRandom3.h>
#include "TMinuit.h"
#include <TApplication.h>
#include <TEnv.h>
#include <TComplex.h>
#include <TGraph.h>
#include <TProfile.h>
#include <TProfile2D.h>
#include <TTree.h>
#include "Math/VectorUtil.h"

using namespace std;
void ZZZAna::Loop(const char* typeName)
{
 if(isRead == false || fChain == 0)
 {
  cout<<"This file contains no events, skip to next file"<<endl;
  return;
 }

 bool isSignal = false;
 bool isBg = false;
 if(typeName == "signal") isSignal = true;
 if(typeName == "background") isBg = true;

 Int_t Nentries = fChain->GetEntries();

/**********variables for looping**********/
 vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float>>>*       trueLeptons = new std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float>>>();
 vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float>>>*       trueFatJets = new std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float>>>();
 vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float>>>*       trueJets = new std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float>>>();
 vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float>>>*       trueZbosons = new std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float>>>();
 vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float>>>*       Zrank = new std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float>>>();
 vector<int>*      trueLeptonsID = new std::vector<int>();
 vector<double>*   trueLeptonsPt = new std::vector<double>();
 vector<double>*   trueLeptonsEta = new std::vector<double>();
 vector<double>*   trueLeptonsPhi = new std::vector<double>();
 vector<double>*   trueZbosonsPt = new std::vector<double>();
 vector<double>*   ZrankPt = new std::vector<double>();
 ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float>>                lepZ,jetZ1,jetZ2,triZboson;

/*************setting cutflow*************/
 myHists->cutflow->GetXaxis()->SetBinLabel(1,"raw");
 myHists->cutflow->GetXaxis()->SetBinLabel(2,"ZZZ events");
 myHists->cutflow->GetXaxis()->SetBinLabel(3,"ZZZMass>500GeV");

 myHists->cutflow_raw->GetXaxis()->SetBinLabel(1,"raw");
 myHists->cutflow_raw->GetXaxis()->SetBinLabel(2,"ZZZ events");
 myHists->cutflow_raw->GetXaxis()->SetBinLabel(3,"ZZZMass>500GeV");

/*****************************************/
/*********Main Looping Code Start*********/
/*****************************************/

 for(int iLoop=0; iLoop<Nentries; iLoop++)
  {
   fChain->GetEntry(iLoop);
   Sta_TotalNumber++;
   myHists->cutflow->Fill(0.5,weight*137);
   myHists->cutflow_raw->Fill(0.5);

/******************Zboson*****************/
   for(int ivec=0; ivec<gen_part_p4->size(); ivec++)
    {
     if(gen_part_status->at(ivec)==22 || gen_part_id->at(ivec)==23)
      {
       trueZbosons->push_back(gen_part_p4->at(ivec));
       trueZbosonsPt->push_back(gen_part_pt->at(ivec));
      }
    }

   if (trueZbosons->size()!=3) continue;  
   triZboson = trueZbosons->at(0) + trueZbosons->at(1) +trueZbosons->at(2);
   myHists->cutflow->Fill(1.5,weight*137);
   myHists->cutflow_raw->Fill(1.5);

/**********ranking Z bosons by Pt*********/
   if (trueZbosonsPt->at(0)<trueZbosonsPt->at(1))
    {
     if (trueZbosonsPt->at(1)<trueZbosonsPt->at(2)) 
      {
       Zrank->push_back(trueZbosons->at(2));
       ZrankPt->push_back(trueZbosonsPt->at(2));
       Zrank->push_back(trueZbosons->at(1));
       ZrankPt->push_back(trueZbosonsPt->at(1));
       Zrank->push_back(trueZbosons->at(0));
       ZrankPt->push_back(trueZbosonsPt->at(0));
      }
     else
      {
       Zrank->push_back(trueZbosons->at(1));
       ZrankPt->push_back(trueZbosonsPt->at(1));
       if (trueZbosonsPt->at(0)<trueZbosonsPt->at(2))
        {
         Zrank->push_back(trueZbosons->at(2));
         ZrankPt->push_back(trueZbosonsPt->at(2));
         Zrank->push_back(trueZbosons->at(0));
         ZrankPt->push_back(trueZbosonsPt->at(0));
        }
       else 
        {
         Zrank->push_back(trueZbosons->at(2));
         ZrankPt->push_back(trueZbosonsPt->at(2));
         Zrank->push_back(trueZbosons->at(0));
         ZrankPt->push_back(trueZbosonsPt->at(0));
        }
      }
    }
   else
    {
     if (trueZbosonsPt->at(1)<trueZbosonsPt->at(2))
      {
       if (trueZbosonsPt->at(0)<trueZbosonsPt->at(2))
        {
         Zrank->push_back(trueZbosons->at(2));
         ZrankPt->push_back(trueZbosonsPt->at(2));
         Zrank->push_back(trueZbosons->at(0));
         ZrankPt->push_back(trueZbosonsPt->at(0));    
         Zrank->push_back(trueZbosons->at(1));
         ZrankPt->push_back(trueZbosonsPt->at(1));
        }
       else 
        {
         Zrank->push_back(trueZbosons->at(0));
         ZrankPt->push_back(trueZbosonsPt->at(0));
         Zrank->push_back(trueZbosons->at(2));
         ZrankPt->push_back(trueZbosonsPt->at(2));
         Zrank->push_back(trueZbosons->at(1));
         ZrankPt->push_back(trueZbosonsPt->at(1));
        }
      }
      else 
       {
        Zrank->push_back(trueZbosons->at(0));
        ZrankPt->push_back(trueZbosonsPt->at(0));
        Zrank->push_back(trueZbosons->at(1));
        ZrankPt->push_back(trueZbosonsPt->at(1));
        Zrank->push_back(trueZbosons->at(2));
        ZrankPt->push_back(trueZbosonsPt->at(2));
       }    
    }
 
/**********select validated events********/
   if (ZrankPt->at(0)<400 || ZrankPt->at(1)<400) 
    {
     myHists->cutflow->Fill(2.5,weight*137);
     myHists->cutflow_raw->Fill(2.5);
     trueLeptons->clear();
     trueLeptonsID->clear();
     trueLeptonsPt->clear();
     trueLeptonsEta->clear();
     trueLeptonsPhi->clear();
     trueJets->clear();
     trueFatJets->clear();
     trueZbosons->clear();
     trueZbosonsPt->clear();
     ZrankPt->clear();
     Zrank->clear();
     continue;
    }

/******************plotting****************/
   myHists->trueZPt_lead->Fill(ZrankPt->at(0),weight);
   myHists->trueZPt_sub->Fill(ZrankPt->at(1),weight);
   myHists->trueZPt_third->Fill(ZrankPt->at(2),weight);

   double angle1 = abs(ROOT::Math::VectorUtil::DeltaPhi(Zrank->at(0),Zrank->at(1)))*180/acos(-1);
   double angle2 = abs(ROOT::Math::VectorUtil::DeltaPhi(Zrank->at(1),Zrank->at(2)))*180/acos(-1);
   double angle3 = abs(ROOT::Math::VectorUtil::DeltaPhi(Zrank->at(0),Zrank->at(2)))*180/acos(-1);
   myHists->deltaPhi_ls->Fill(angle1,weight);
   myHists->deltaPhi_st->Fill(angle2,weight);
   myHists->deltaPhi_lt->Fill(angle3,weight);

/************clearing variables************/
   trueLeptons->clear();
   trueLeptonsID->clear();
   trueLeptonsPt->clear();
   trueLeptonsEta->clear();
   trueLeptonsPhi->clear();
   trueJets->clear();
   trueFatJets->clear();
   trueZbosons->clear();
   trueZbosonsPt->clear();
   ZrankPt->clear();
   Zrank->clear();

  }//main looping
}//ZZZAna::loop ends
