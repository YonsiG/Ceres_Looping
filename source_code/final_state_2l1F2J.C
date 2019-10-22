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
#include "Math/VectorUtil.h"
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
 vector<double>*   trueFatJetPt = new std::vector<double>();
 vector<double>*   trueFatJetTau21 = new std::vector<double>();
 vector<double>*   trueFatJetMass = new std::vector<double>();
 ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float>>                lepZ,jetZ1,jetZ2,ZZZ;

/*************setting cutflow*************/
 myHists->cutflow->GetXaxis()->SetBinLabel(1,"pre-selection");
 myHists->cutflow->GetXaxis()->SetBinLabel(2,"two good leptons");
 myHists->cutflow->GetXaxis()->SetBinLabel(3,"opposite charge leptons");
 myHists->cutflow->GetXaxis()->SetBinLabel(4,"requiring nfatjet=1 njet=2");
 myHists->cutflow->GetXaxis()->SetBinLabel(5,"ZZZ mass>1200GeV");
 myHists->cutflow->GetXaxis()->SetBinLabel(6,"70GeV<FatJetMass_lead<110GeV");
 myHists->cutflow->GetXaxis()->SetBinLabel(7,"60GeV<FatJetMass_sub<100GeV");
 myHists->cutflow->GetXaxis()->SetBinLabel(8,"FatJetTau21_lead<0.5");
 myHists->cutflow->GetXaxis()->SetBinLabel(9,"FatJetTau21_sub<0.5");
 myHists->cutflow->GetXaxis()->SetBinLabel(10,"300GeV<FatJetPt_lead<800GeV");
 myHists->cutflow->GetXaxis()->SetBinLabel(11,"FatJetPt_lead<500GeV");
// myHists->cutflow->GetXaxis()->SetBinLabel(10,"70GeV<DileptonMass<110GeV");

 myHists->cutflow_raw->GetXaxis()->SetBinLabel(1,"pre-selection");
 myHists->cutflow_raw->GetXaxis()->SetBinLabel(2,"two good leptons");
 myHists->cutflow_raw->GetXaxis()->SetBinLabel(3,"opposite charge leptons");
 myHists->cutflow_raw->GetXaxis()->SetBinLabel(4,"requiring nfatjet=1 njet=2");
 myHists->cutflow_raw->GetXaxis()->SetBinLabel(5,"ZZZ mass>1200GeV");
 myHists->cutflow_raw->GetXaxis()->SetBinLabel(6,"70GeV<FatJetMass_lead<110GeV");
 myHists->cutflow_raw->GetXaxis()->SetBinLabel(7,"60GeV<FatJetMass_sub<100GeV");
 myHists->cutflow_raw->GetXaxis()->SetBinLabel(8,"FatJetTau21_lead<0.5");
 myHists->cutflow_raw->GetXaxis()->SetBinLabel(9,"FatJetTau21_sub<0.5");
 myHists->cutflow_raw->GetXaxis()->SetBinLabel(10,"300GeV<FatJetPt_lead<800GeV");
 myHists->cutflow_raw->GetXaxis()->SetBinLabel(11,"FatJetPt_lead<500GeV");
// myHists->cutflow_raw->GetXaxis()->SetBinLabel(10,"70GeV<DileptonMass<110GeV");

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

/*****************fatjets*******************/
   for(int ivec=0; ivec<fatjets_p4->size(); ivec++)
    {
     int lepFatjetOverlap=0;
     for (int ilep=0; ilep<trueLeptons->size(); ilep++)
      {
       if (ROOT::Math::VectorUtil::DeltaR(fatjets_p4->at(ivec),trueLeptons->at(ilep))<0.8)
        {
         lepFatjetOverlap=1;
        }
      }
     if (!lepFatjetOverlap) 
      {
       trueFatJets->push_back(fatjets_p4->at(ivec)); 
       trueFatJetMass->push_back(J_SD_mass->at(ivec));
       trueFatJetPt->push_back(J_pt->at(ivec));
       trueFatJetTau21->push_back(J_tau21->at(ivec));
      }
    }

   vector<int>*  goodFatjet = new std::vector<int>();
   for(int ivec=0; ivec<trueFatJets->size(); ivec++)
    { 
     if (60<trueFatJetMass->at(ivec) && trueFatJetMass->at(ivec)<120 && trueFatJetTau21->at(ivec)<0.7) goodFatjet->push_back(1);
     else goodFatjet->push_back(0);
    }

/*******************jets********************/
   for(int ivec=0; ivec<jets_p4->size(); ivec++)
    {
     int jetFatOverlap=0;
     for (int ifat=0; ifat<trueFatJets->size(); ifat++)
      {
       if (ROOT::Math::VectorUtil::DeltaR(jets_p4->at(ivec),trueFatJets->at(ifat))<0.8 && goodFatjet->at(ifat))
        {
         jetFatOverlap=1;
        }
      }
     if (!jetFatOverlap)
      {
      trueJets->push_back(jets_p4->at(ivec));
      }
    }

/***********correction of weight**********/
    weight = 6020.9*1000*137/98984939;
//    weight = weight*137;
    double weight0 = 1; 

/********pre-select validated events******/
   myHists->cutflow->Fill(0.5,weight);
   myHists->cutflow_raw->Fill(0.5,weight0);

   if (trueLeptons->size()!=2) 
    {
     trueLeptons->clear();
     trueLeptonsID->clear();
     trueLeptonsPt->clear();
     trueLeptonsEta->clear();
     trueLeptonsPhi->clear();
     trueJets->clear();
     trueFatJets->clear();
     trueFatJetMass->clear();
     trueFatJetPt->clear();
     trueFatJetTau21->clear();
     continue;
    }

   myHists->cutflow->Fill(1.5,weight);
   myHists->cutflow_raw->Fill(1.5,weight0);

   if (trueLeptonsID->at(0)*trueLeptonsID->at(1)>0)
    {
     trueLeptons->clear();
     trueLeptonsID->clear();
     trueLeptonsPt->clear();
     trueLeptonsEta->clear();
     trueLeptonsPhi->clear();
     trueJets->clear();
     trueFatJets->clear();
     trueFatJetMass->clear();
     trueFatJetPt->clear();
     trueFatJetTau21->clear();
     continue;
    }

   myHists->cutflow->Fill(2.5,weight);
   myHists->cutflow_raw->Fill(2.5,weight0);

   if (trueFatJets->size()!=1 || trueJets->size()!=2)
    {
     trueLeptons->clear();
     trueLeptonsID->clear();
     trueLeptonsPt->clear();
     trueLeptonsEta->clear();
     trueLeptonsPhi->clear();
     trueJets->clear();
     trueFatJets->clear();
     trueFatJetMass->clear();
     trueFatJetPt->clear();
     trueFatJetTau21->clear();
     continue;
    }

/************reconstructions***************/
   lepZ = trueLeptons->at(0)+trueLeptons->at(1);
   ZZZ = lepZ+trueFatJets->at(0)+trueJets->at(0)+trueJets->at(1);

   myHists->cutflow->Fill(3.5,weight);
   myHists->cutflow_raw->Fill(3.5,weight0);
   myHists->fatjetMass_Pt_lead->Fill(trueFatJetMass->at(0),trueFatJetPt->at(0),weight);
   myHists->fatjetMass_tau21_lead->Fill(trueFatJetMass->at(0),trueFatJetTau21->at(0),weight);
   myHists->fatjettau21_Pt_lead->Fill(trueFatJetTau21->at(0),trueFatJetPt->at(0),weight);
   myHists->ZZZMass_fatjetMass_lead->Fill(ZZZ.M(),trueFatJetMass->at(0),weight);
   myHists->ZZZMass_fatjetPt_lead->Fill(ZZZ.M(),trueFatJetPt->at(0),weight);
   myHists->ZZZMass_fatjettau21_lead->Fill(ZZZ.M(),trueFatJetTau21->at(0),weight);
   myHists->ZZZ_mass->Fill(ZZZ.M(),weight);

/*************event selections*************/
/*   if (ZZZ.M()<1200)
    {
     trueLeptons->clear();
     trueLeptonsID->clear();
     trueLeptonsPt->clear();
     trueLeptonsEta->clear();
     trueLeptonsPhi->clear();
     trueJets->clear();
     trueFatJets->clear();
     trueFatJetMass->clear();
     trueFatJetPt->clear();
     trueFatJetTau21->clear();
     continue;
    }
*/
/*   myHists->cutflow->Fill(4.5,weight);
   myHists->cutflow_raw->Fill(4.5,weight0);

   if (trueFatJetMass->at(0)<70 || trueFatJetMass->at(0)>110)
    {
     trueLeptons->clear();
     trueLeptonsID->clear();
     trueLeptonsPt->clear();
     trueLeptonsEta->clear();
     trueLeptonsPhi->clear();
     trueJets->clear();
     trueFatJets->clear();
     trueFatJetMass->clear();
     trueFatJetPt->clear();
     trueFatJetTau21->clear();
     continue;
    }

   myHists->cutflow->Fill(5.5,weight);
   myHists->cutflow_raw->Fill(5.5,weight0);

   if (trueFatJetMass->at(1)<60 || trueFatJetMass->at(1)>100)
    {
     trueLeptons->clear();
     trueLeptonsID->clear();
     trueLeptonsPt->clear();
     trueLeptonsEta->clear();
     trueLeptonsPhi->clear();
     trueJets->clear();
     trueFatJets->clear();
     trueFatJetMass->clear();
     trueFatJetPt->clear();
     trueFatJetTau21->clear();
     continue;
    }

   myHists->cutflow->Fill(6.5,weight);
   myHists->cutflow_raw->Fill(6.5,weight0);

   if (trueFatJetTau21->at(0)>0.5)
    {
     trueLeptons->clear();
     trueLeptonsID->clear();
     trueLeptonsPt->clear();
     trueLeptonsEta->clear();
     trueLeptonsPhi->clear();
     trueJets->clear();
     trueFatJets->clear();
     trueFatJetMass->clear();
     trueFatJetPt->clear();
     trueFatJetTau21->clear();
     continue;
    }

   myHists->cutflow->Fill(7.5,weight);
   myHists->cutflow_raw->Fill(7.5,weight0);

   if (trueFatJetTau21->at(1)>0.5)
    {
     trueLeptons->clear();
     trueLeptonsID->clear();
     trueLeptonsPt->clear();
     trueLeptonsEta->clear();
     trueLeptonsPhi->clear();
     trueJets->clear();
     trueFatJets->clear();
     trueFatJetMass->clear();
     trueFatJetPt->clear();
     trueFatJetTau21->clear();
     continue;
    }

   myHists->cutflow->Fill(8.5,weight);
   myHists->cutflow_raw->Fill(8.5,weight0);

   if (trueFatJetPt->at(0)<300 || trueFatJetPt->at(0)>800)
    {
     trueLeptons->clear();
     trueLeptonsID->clear();
     trueLeptonsPt->clear();
     trueLeptonsEta->clear();
     trueLeptonsPhi->clear();
     trueJets->clear();
     trueFatJets->clear();
     trueFatJetMass->clear();
     trueFatJetPt->clear();
     trueFatJetTau21->clear();
     continue;
    }

   myHists->cutflow->Fill(9.5,weight);
   myHists->cutflow_raw->Fill(9.5,weight0);

   if (trueFatJetPt->at(1)>500)
    {
     trueLeptons->clear();
     trueLeptonsID->clear();
     trueLeptonsPt->clear();
     trueLeptonsEta->clear();
     trueLeptonsPhi->clear();
     trueJets->clear();
     trueFatJets->clear();
     trueFatJetMass->clear();
     trueFatJetPt->clear();
     trueFatJetTau21->clear();
     continue;
    }

   myHists->cutflow->Fill(10.5,weight);
   myHists->cutflow_raw->Fill(10.5,weight0);
*/
/*   if (lepZ.M()<70 or lepZ.M()>110)
    {
     trueLeptons->clear();
     trueLeptonsID->clear();
     trueLeptonsPt->clear();
     trueLeptonsEta->clear();
     trueLeptonsPhi->clear();
     trueJets->clear();
     trueFatJets->clear();
     trueFatJetMass->clear();
     trueFatJetPt->clear();
     trueFatJetTau21->clear();
     continue;
    }

   myHists->cutflow->Fill(9.5,weight);
   myHists->cutflow_raw->Fill(9.5,weight0);
*/

/**************plot filling****************/
//   myHists->ZZZ_mass->Fill(ZZZ.M(),weight);
   myHists->dileptonMass->Fill(lepZ.M(),weight);
   myHists->dileptonPt->Fill(lepZ.Pt(),weight);
   myHists->jetNumbers->Fill(trueJets->size(),weight);
   myHists->fatjetNumbers->Fill(trueFatJets->size(),weight);

   myHists->fatjetMass_lead->Fill(trueFatJetMass->at(0),weight);
   myHists->fatjet_tau21_lead->Fill(trueFatJetTau21->at(0),weight);
   myHists->fatjet_pt_lead->Fill(trueFatJetPt->at(0),weight);

   myHists->leptonPt_lead->Fill(trueLeptonsPt->at(0),weight);
   myHists->leptonEta_lead->Fill(trueLeptonsEta->at(0),weight);
   myHists->leptonPhi_lead->Fill(trueLeptonsPhi->at(0),weight);

   if ((trueLeptonsID->at(0)*trueLeptonsID->at(1))==-121)
    {
     myHists->dileptonMass_ee->Fill(lepZ.M(),weight);
     myHists->dileptonPt_ee->Fill(lepZ.Pt(),weight);
     myHists->jetNumbers_ee->Fill(trueJets->size(),weight);
     myHists->fatjetNumbers_ee->Fill(trueFatJets->size(),weight);

     myHists->fatjetMass_ee_lead->Fill(trueFatJetMass->at(0),weight);
     myHists->fatjet_tau21_ee_lead->Fill(trueFatJetTau21->at(0),weight);
     myHists->fatjet_pt_ee_lead->Fill(trueFatJetPt->at(0),weight);

     myHists->leptonPt_ee_lead->Fill(trueLeptonsPt->at(0),weight);
     myHists->leptonEta_ee_lead->Fill(trueLeptonsEta->at(0),weight);
    }

   if ((trueLeptonsID->at(0)*trueLeptonsID->at(1))==-169)
    {
     myHists->dileptonMass_mm->Fill(lepZ.M(),weight);
     myHists->dileptonPt_mm->Fill(lepZ.Pt(),weight);
     myHists->jetNumbers_mm->Fill(trueJets->size(),weight);
     myHists->fatjetNumbers_mm->Fill(trueFatJets->size(),weight);

     myHists->fatjetMass_mm_lead->Fill(trueFatJetMass->at(0),weight);
     myHists->fatjet_tau21_mm_lead->Fill(trueFatJetTau21->at(0),weight);
     myHists->fatjet_pt_mm_lead->Fill(trueFatJetPt->at(0),weight);

     myHists->leptonPt_mm_lead->Fill(trueLeptonsPt->at(0),weight);
     myHists->leptonEta_mm_lead->Fill(trueLeptonsEta->at(0),weight);
    }

   if ((trueLeptonsID->at(0)*trueLeptonsID->at(1))==-143)
    {
     myHists->dileptonMass_em->Fill(lepZ.M(),weight);
     myHists->dileptonPt_em->Fill(lepZ.Pt(),weight);
     myHists->jetNumbers_em->Fill(trueJets->size(),weight);
     myHists->fatjetNumbers_em->Fill(trueFatJets->size(),weight);

     myHists->fatjetMass_em_lead->Fill(trueFatJetMass->at(0),weight);
     myHists->fatjet_tau21_em_lead->Fill(trueFatJetTau21->at(0),weight);
     myHists->fatjet_pt_em_lead->Fill(trueFatJetPt->at(0),weight);

     myHists->leptonPt_em_lead->Fill(trueLeptonsPt->at(0),weight);
     myHists->leptonEta_em_lead->Fill(trueLeptonsEta->at(0),weight);
    }

/************clearing variables************/
   trueLeptons->clear();
   trueLeptonsID->clear();
   trueLeptonsPt->clear();
   trueLeptonsEta->clear();
   trueLeptonsPhi->clear();
   trueJets->clear();
   trueFatJets->clear();
   trueFatJetMass->clear();
   trueFatJetPt->clear();
   trueFatJetTau21->clear();

  }//main looping
}//ZZZAna::loop ends
