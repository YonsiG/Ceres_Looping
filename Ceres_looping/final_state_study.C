#define _ZZZANA_C_
#include "ZZZAna.h"
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "TMath.h"
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
 vector<int>*      trueLeptonsID = new std::vector<int>();
 vector<double>*   trueLeptonsPt = new std::vector<double>();
 vector<double>*   trueLeptonsEta = new std::vector<double>();
 vector<double>*   trueLeptonsPhi = new std::vector<double>();
 ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float>>                lepZ,jetZ1,jetZ2;

/*************setting cutflow*************/
 myHists->cutflow->GetXaxis()->SetBinLabel(1,"raw");
 myHists->cutflow->GetXaxis()->SetBinLabel(2,"two good leptons");
 myHists->cutflow->GetXaxis()->SetBinLabel(3,"opposite charge leptons");
 myHists->cutflow->GetXaxis()->SetBinLabel(4,"requiring nfatjet>=2");

 myHists->cutflow_ee->GetXaxis()->SetBinLabel(1,"raw");
 myHists->cutflow_ee->GetXaxis()->SetBinLabel(2,"two good leptons");
 myHists->cutflow_ee->GetXaxis()->SetBinLabel(3,"opposite charge leptons");
 myHists->cutflow_ee->GetXaxis()->SetBinLabel(4,"requiring nfatjet>=2");

 myHists->cutflow_em->GetXaxis()->SetBinLabel(1,"raw");
 myHists->cutflow_em->GetXaxis()->SetBinLabel(2,"two good leptons");
 myHists->cutflow_em->GetXaxis()->SetBinLabel(3,"opposite charge leptons");
 myHists->cutflow_em->GetXaxis()->SetBinLabel(4,"requiring nfatjet>=2");

 myHists->cutflow_mm->GetXaxis()->SetBinLabel(1,"raw");
 myHists->cutflow_mm->GetXaxis()->SetBinLabel(2,"two good leptons");
 myHists->cutflow_mm->GetXaxis()->SetBinLabel(3,"opposite charge leptons");
 myHists->cutflow_mm->GetXaxis()->SetBinLabel(4,"requiring nfatjet>=2");

 myHists->cutflow_raw->GetXaxis()->SetBinLabel(1,"raw");
 myHists->cutflow_raw->GetXaxis()->SetBinLabel(2,"two good leptons");
 myHists->cutflow_raw->GetXaxis()->SetBinLabel(3,"opposite charge leptons");
 myHists->cutflow_raw->GetXaxis()->SetBinLabel(4,"requiring nfatjet>=2");

 myHists->cutflow_ee_raw->GetXaxis()->SetBinLabel(1,"raw");
 myHists->cutflow_ee_raw->GetXaxis()->SetBinLabel(2,"two good leptons");
 myHists->cutflow_ee_raw->GetXaxis()->SetBinLabel(3,"opposite charge leptons");
 myHists->cutflow_ee_raw->GetXaxis()->SetBinLabel(4,"requiring nfatjet>=2");

 myHists->cutflow_em_raw->GetXaxis()->SetBinLabel(1,"raw");
 myHists->cutflow_em_raw->GetXaxis()->SetBinLabel(2,"two good leptons");
 myHists->cutflow_em_raw->GetXaxis()->SetBinLabel(3,"opposite charge leptons");
 myHists->cutflow_em_raw->GetXaxis()->SetBinLabel(4,"requiring nfatjet>=2");

 myHists->cutflow_mm_raw->GetXaxis()->SetBinLabel(1,"raw");
 myHists->cutflow_mm_raw->GetXaxis()->SetBinLabel(2,"two good leptons");
 myHists->cutflow_mm_raw->GetXaxis()->SetBinLabel(3,"opposite charge leptons");
 myHists->cutflow_mm_raw->GetXaxis()->SetBinLabel(4,"requiring nfatjet>=2");

/*****************************************/
/*********Main Looping Code Start*********/
/*****************************************/

 for(int iLoop=0; iLoop<Nentries; iLoop++)
  {
   fChain->GetEntry(iLoop);
   Sta_TotalNumber++;

/***************leptons*****************/
   for(int ivec=0; ivec<lep_p4->size(); ivec++)
    {
     if(lep_isWVZVeto->at(ivec)==1) 
      {
       trueLeptons->push_back(lep_p4->at(ivec));
       trueLeptonsID->push_back(lep_id->at(ivec));
       trueLeptonsPt->push_back(lep_pt->at(ivec));
       trueLeptonsEta->push_back(lep_eta->at(ivec));
       trueLeptonsPhi->push_back(lep_phi->at(ivec));
      }
    }

/*******************jets********************/
   for(int ivec=0; ivec<jets_p4->size(); ivec++)
    {
       trueJets->push_back(jets_p4->at(ivec));
    }

/*****************fatjets*******************/
   for(int ivec=0; ivec<fatjets_p4->size(); ivec++)
    {
     trueFatJets->push_back(fatjets_p4->at(ivec));
    }

/**********select validated events********/
   myHists->cutflow->Fill(0.5,weight*137);
   myHists->cutflow_raw->Fill(0.5);

   if (trueLeptons->size()!=2) 
    {
     trueLeptons->clear();
     trueLeptonsID->clear();
     trueLeptonsPt->clear();
     trueLeptonsEta->clear();
     trueLeptonsPhi->clear();
     trueJets->clear();
     trueFatJets->clear();
     continue;
    }
   myHists->cutflow->Fill(1.5,weight*137);
   myHists->cutflow_raw->Fill(1.5);
   if (fabs(trueLeptonsID->at(0)*trueLeptonsID->at(1))==121)
    {
     myHists->cutflow_ee->Fill(1.5,weight*137);
     myHists->cutflow_ee_raw->Fill(1.5);
    }
   if (fabs(trueLeptonsID->at(0)*trueLeptonsID->at(1))==143)
    {
     myHists->cutflow_em->Fill(1.5,weight*137);
     myHists->cutflow_em_raw->Fill(1.5);
    }
   if (fabs(trueLeptonsID->at(0)*trueLeptonsID->at(1))==169)
    {
     myHists->cutflow_mm->Fill(1.5,weight*137);
     myHists->cutflow_mm_raw->Fill(1.5);
    }

   if (trueLeptonsID->at(0)*trueLeptonsID->at(1)>0)
    {
     trueLeptons->clear();
     trueLeptonsID->clear();
     trueLeptonsPt->clear();
     trueLeptonsEta->clear();
     trueLeptonsPhi->clear();
     trueJets->clear();
     trueFatJets->clear();
     continue;
    }
   myHists->cutflow->Fill(2.5,weight*137);
   myHists->cutflow_raw->Fill(2.5);
   if (fabs(trueLeptonsID->at(0)*trueLeptonsID->at(1))==121)
    {
     myHists->cutflow_ee->Fill(2.5,weight*137);
     myHists->cutflow_ee_raw->Fill(2.5);
    }
   if (fabs(trueLeptonsID->at(0)*trueLeptonsID->at(1))==143)
    {
     myHists->cutflow_em->Fill(2.5,weight*137);
     myHists->cutflow_em_raw->Fill(2.5);
    }
   if (fabs(trueLeptonsID->at(0)*trueLeptonsID->at(1))==169)
    {
     myHists->cutflow_mm->Fill(2.5,weight*137);
     myHists->cutflow_mm_raw->Fill(2.5);
    }

   if (trueFatJets->size()<2)
    {
     trueLeptons->clear();
     trueLeptonsID->clear();
     trueLeptonsPt->clear();
     trueLeptonsEta->clear();
     trueLeptonsPhi->clear();
     trueJets->clear();
     trueFatJets->clear();
     continue;
    }
   myHists->cutflow->Fill(3.5,weight*137);
   myHists->cutflow_raw->Fill(3.5);
   if (fabs(trueLeptonsID->at(0)*trueLeptonsID->at(1))==121)
    {
     myHists->cutflow_ee->Fill(3.5,weight*137);
     myHists->cutflow_ee_raw->Fill(3.5);
    }
   if (fabs(trueLeptonsID->at(0)*trueLeptonsID->at(1))==143)
    {
     myHists->cutflow_em->Fill(3.5,weight*137);
     myHists->cutflow_em_raw->Fill(3.5);
    }
   if (fabs(trueLeptonsID->at(0)*trueLeptonsID->at(1))==169)
    {
     myHists->cutflow_mm->Fill(3.5,weight*137);
     myHists->cutflow_mm_raw->Fill(3.5);
    }

/************reconstructions***************/
   lepZ = trueLeptons->at(0)+trueLeptons->at(1);

/**************plot fitting****************/
   myHists->dileptonMass->Fill(lepZ.M(),weight);
   myHists->dileptonPt->Fill(lepZ.Pt(),weight);
   myHists->jetNumbers->Fill(trueJets->size(),weight);
   myHists->fatjetNumbers->Fill(trueFatJets->size(),weight);

   myHists->fatjetMass_lead->Fill(J_SD_mass->at(0),weight);
   myHists->fatjet_tau21_lead->Fill(J_tau21->at(0),weight);
   myHists->fatjet_pt_lead->Fill(J_pt->at(0),weight);
   myHists->fatjetMass_sub->Fill(J_SD_mass->at(1),weight);
   myHists->fatjet_tau21_sub->Fill(J_tau21->at(1),weight);
   myHists->fatjet_pt_sub->Fill(J_pt->at(1),weight);

   myHists->leptonPt_lead->Fill(trueLeptonsPt->at(0),weight);
   myHists->leptonEta_lead->Fill(trueLeptonsEta->at(0),weight);
   myHists->leptonPhi->Fill(trueLeptonsPhi->at(0),weight);
   myHists->leptonPt_sub->Fill(trueLeptonsPt->at(1),weight);
   myHists->leptonEta_sub->Fill(trueLeptonsEta->at(1),weight);
   myHists->leptonPhi->Fill(trueLeptonsPhi->at(1),weight);

   if ((trueLeptonsID->at(0)*trueLeptonsID->at(1))==-121)
    {
     myHists->dileptonMass_ee->Fill(lepZ.M(),weight);
     myHists->dileptonPt_ee->Fill(lepZ.Pt(),weight);
     myHists->jetNumbers_ee->Fill(trueJets->size(),weight);
     myHists->fatjetNumbers_ee->Fill(trueFatJets->size(),weight);

     myHists->fatjetMass_ee_lead->Fill(J_SD_mass->at(0),weight);
     myHists->fatjet_tau21_ee_lead->Fill(J_tau21->at(0),weight);
     myHists->fatjet_pt_ee_lead->Fill(J_pt->at(0),weight);
     myHists->fatjetMass_ee_sub->Fill(J_SD_mass->at(1),weight);
     myHists->fatjet_tau21_ee_sub->Fill(J_tau21->at(1),weight);
     myHists->fatjet_pt_ee_sub->Fill(J_pt->at(1),weight);

     myHists->leptonPt_ee_lead->Fill(trueLeptonsPt->at(0),weight);
     myHists->leptonEta_ee_lead->Fill(trueLeptonsEta->at(0),weight);
     myHists->leptonPhi_ee->Fill(trueLeptonsPhi->at(0),weight);
     myHists->leptonPt_ee_sub->Fill(trueLeptonsPt->at(1),weight);
     myHists->leptonEta_ee_sub->Fill(trueLeptonsEta->at(1),weight);
     myHists->leptonPhi_ee->Fill(trueLeptonsPhi->at(1),weight);
    }

   if ((trueLeptonsID->at(0)*trueLeptonsID->at(1))==-169)
    {
     myHists->dileptonMass_mm->Fill(lepZ.M(),weight);
     myHists->dileptonPt_mm->Fill(lepZ.Pt(),weight);
     myHists->jetNumbers_mm->Fill(trueJets->size(),weight);
     myHists->fatjetNumbers_mm->Fill(trueFatJets->size(),weight);

     myHists->fatjetMass_mm_lead->Fill(J_SD_mass->at(0),weight);
     myHists->fatjet_tau21_mm_lead->Fill(J_tau21->at(0),weight);
     myHists->fatjet_pt_mm_lead->Fill(J_pt->at(0),weight);
     myHists->fatjetMass_mm_sub->Fill(J_SD_mass->at(1),weight);
     myHists->fatjet_tau21_mm_sub->Fill(J_tau21->at(1),weight);
     myHists->fatjet_pt_mm_sub->Fill(J_pt->at(1),weight);

     myHists->leptonPt_mm_lead->Fill(trueLeptonsPt->at(0),weight);
     myHists->leptonEta_mm_lead->Fill(trueLeptonsEta->at(0),weight);
     myHists->leptonPhi_mm->Fill(trueLeptonsPhi->at(0),weight);
     myHists->leptonPt_mm_sub->Fill(trueLeptonsPt->at(1),weight);
     myHists->leptonEta_mm_sub->Fill(trueLeptonsEta->at(1),weight);
     myHists->leptonPhi_mm->Fill(trueLeptonsPhi->at(1),weight);
    }

   if ((trueLeptonsID->at(0)*trueLeptonsID->at(1))==-143)
    {
     myHists->dileptonMass_em->Fill(lepZ.M(),weight);
     myHists->dileptonPt_em->Fill(lepZ.Pt(),weight);
     myHists->jetNumbers_em->Fill(trueJets->size(),weight);
     myHists->fatjetNumbers_em->Fill(trueFatJets->size(),weight);

     myHists->fatjetMass_em_lead->Fill(J_SD_mass->at(0),weight);
     myHists->fatjet_tau21_em_lead->Fill(J_tau21->at(0),weight);
     myHists->fatjet_pt_em_lead->Fill(J_pt->at(0),weight);
     myHists->fatjetMass_em_sub->Fill(J_SD_mass->at(1),weight);
     myHists->fatjet_tau21_em_sub->Fill(J_tau21->at(1),weight);
     myHists->fatjet_pt_em_sub->Fill(J_pt->at(1),weight);

     myHists->leptonPt_em_lead->Fill(trueLeptonsPt->at(0),weight);
     myHists->leptonEta_em_lead->Fill(trueLeptonsEta->at(0),weight);
     myHists->leptonPhi_em->Fill(trueLeptonsPhi->at(0),weight);
     myHists->leptonPt_em_sub->Fill(trueLeptonsPt->at(1),weight);
     myHists->leptonEta_em_sub->Fill(trueLeptonsEta->at(1),weight);
     myHists->leptonPhi_em->Fill(trueLeptonsPhi->at(1),weight);
    }

/************clearing variables************/
   trueLeptons->clear();
   trueLeptonsID->clear();
   trueLeptonsPt->clear();
   trueLeptonsEta->clear();
   trueLeptonsPhi->clear();
   trueJets->clear();
   trueFatJets->clear();

  }//main looping
}//ZZZAna::loop ends
