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
void ZZZAna::Loop(const char* typeName, char* yearName)
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
 vector<double>*   trueFatJetEta = new std::vector<double>();
 vector<double>*   trueFatJetTau21 = new std::vector<double>();
 vector<double>*   trueFatJetMass = new std::vector<double>();
 vector<double>*   trueLeptonrel03 = new std::vector<double>();
 vector<double>*   trueLeptonrel04 = new std::vector<double>();
 vector<double>*   trueLepton_isMediumPOG = new std::vector<double>();
 ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float>>                ZZZ;
 ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float>>                firstZ, secondZ;

/*************setting cutflow*************/
 myHists->cutflow->GetXaxis()->SetBinLabel(1,"pre-selection");
 myHists->cutflow->GetXaxis()->SetBinLabel(2,"four good leptons");
 myHists->cutflow->GetXaxis()->SetBinLabel(3,"reconstruct 2 Z");
 myHists->cutflow->GetXaxis()->SetBinLabel(4,"71GeV<lep Z Mass<111GeV");
 myHists->cutflow->GetXaxis()->SetBinLabel(5,"requiring >=1 fatjet");
 myHists->cutflow->GetXaxis()->SetBinLabel(6,"Mass[70,110],fatjet>=1");
 myHists->cutflow->GetXaxis()->SetBinLabel(7,"Mass[70,110],fatjet=1");
 myHists->cutflow->GetXaxis()->SetBinLabel(8,"FatJetTau21_lead<0.7");
 myHists->cutflow->GetXaxis()->SetBinLabel(9,"300GeV<FatJetPt_lead<800GeV");
 myHists->cutflow->GetXaxis()->SetBinLabel(10,"FatJetPt_lead<500GeV");
// myHists->cutflow->GetXaxis()->SetBinLabel(10,"70GeV<DileptonMass<110GeV");

 myHists->cutflow_raw->GetXaxis()->SetBinLabel(1,"pre-selection");
 myHists->cutflow_raw->GetXaxis()->SetBinLabel(2,"four good leptons");
 myHists->cutflow_raw->GetXaxis()->SetBinLabel(3,"reconstruct 2 Z");
 myHists->cutflow_raw->GetXaxis()->SetBinLabel(4,"71GeV<lep Z Mass<111GeV");
 myHists->cutflow_raw->GetXaxis()->SetBinLabel(5,"requiring 1 fatjet");
 myHists->cutflow_raw->GetXaxis()->SetBinLabel(6,"Mass[70,110],fatjet>=1");
 myHists->cutflow_raw->GetXaxis()->SetBinLabel(7,"Mass[70,110],fatjet=1");
 myHists->cutflow_raw->GetXaxis()->SetBinLabel(8,"FatJetTau21_lead<0.7");
 myHists->cutflow_raw->GetXaxis()->SetBinLabel(9,"300GeV<FatJetPt_lead<800GeV");
 myHists->cutflow_raw->GetXaxis()->SetBinLabel(10,"FatJetPt_lead<500GeV");
// myHists->cutflow_raw->GetXaxis()->SetBinLabel(10,"70GeV<DileptonMass<110GeV");

/*****************************************/
/*********Main Looping Code Start*********/
/*****************************************/

 for(int iLoop=0; iLoop<Nentries; iLoop++)
  {
   fChain->GetEntry(iLoop);
   Sta_TotalNumber++;

/***************leptons*****************/
   int isGoodLep=0;

   for(int ivec=0; ivec<lep_p4->size(); ivec++)
    {
     if (fabs(lep_id->at(ivec))==11 && lep_relIso03EA->at(ivec)<0.25) isGoodLep=1;
     if (fabs(lep_id->at(ivec))==13 && lep_relIso04DB->at(ivec)<0.25 && trueLepton_isMediumPOG) isGoodLep=1;
     if(isGoodLep==1) 
      {
       trueLeptons->push_back(lep_p4->at(ivec));
       trueLeptonsID->push_back(lep_id->at(ivec));
       trueLeptonsPt->push_back(lep_pt->at(ivec));
       trueLeptonsEta->push_back(lep_eta->at(ivec));
       trueLeptonsPhi->push_back(lep_phi->at(ivec));
       trueLeptonrel03->push_back(lep_relIso03EA->at(ivec));
       trueLeptonrel04->push_back(lep_relIso04DB->at(ivec));
       trueLepton_isMediumPOG->push_back(lep_isMediumPOG->at(ivec));
      }
    }

/*****************fatjets*******************/
   for(int ivec=0; ivec<fatjets_p4->size(); ivec++)
    {
     int lepFatjetOverlap=0;
     int fatjetMassRange=1;
     for (int ilep=0; ilep<trueLeptons->size(); ilep++)
      {
       if (ROOT::Math::VectorUtil::DeltaR(fatjets_p4->at(ivec),trueLeptons->at(ilep))<0.8)
        {
         lepFatjetOverlap=1;
        }
      }
//     if (70<J_SD_mass->at(ivec) && J_SD_mass->at(ivec)<110) fatjetMassRange=1; 
     if (!lepFatjetOverlap && fatjetMassRange) 
      {
       trueFatJets->push_back(fatjets_p4->at(ivec)); 
       trueFatJetMass->push_back(J_SD_mass->at(ivec));
       trueFatJetPt->push_back(J_pt->at(ivec));
       trueFatJetEta->push_back(J_eta->at(ivec));
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
    if(strcmp(yearName,"2016")==0) weight = weight*35.9;
    if(strcmp(yearName,"2017")==0) weight = weight*41.3;
    if(strcmp(yearName,"2018")==0) weight = weight*59.74;
    if(strcmp(yearName,"9999")==0) weight = weight*137;
    double weight0 = 1; 

/********pre-select validated events******/
   myHists->cutflow->Fill(0.5,weight);
   myHists->cutflow_raw->Fill(0.5,weight0);

   if (trueLeptons->size()!=4) 
    {
     trueLeptons->clear();
     trueLeptonsID->clear();
     trueLeptonsPt->clear();
     trueLeptonsEta->clear();
     trueLeptonsPhi->clear();
     trueLeptonrel03->clear();
     trueLeptonrel04->clear();
     trueLepton_isMediumPOG->clear();
     trueJets->clear();
     trueFatJets->clear();
     trueFatJetMass->clear();
     trueFatJetPt->clear();
     trueFatJetEta->clear();
     trueFatJetTau21->clear();
     continue;
    }

   myHists->cutflow->Fill(1.5,weight);
   myHists->cutflow_raw->Fill(1.5,weight0);

/************reconstructions***************/
   int lep4ID = trueLeptonsID->at(0)*trueLeptonsID->at(1)*trueLeptonsID->at(2)*trueLeptonsID->at(3);
   
   if (lep4ID!=14641 && lep4ID!=20449 && lep4ID!=28561)
    {
     trueLeptons->clear();
     trueLeptonsID->clear();
     trueLeptonsPt->clear();
     trueLeptonsEta->clear();
     trueLeptonsPhi->clear();
     trueLeptonrel03->clear();
     trueLeptonrel04->clear();
     trueLepton_isMediumPOG->clear();
     trueJets->clear();
     trueFatJets->clear();
     trueFatJetMass->clear();
     trueFatJetPt->clear();
     trueFatJetEta->clear();
     trueFatJetTau21->clear();
     continue;
    }

   ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float>> tempZ,currentZ;
   int Z1_num1=6666, Z1_num2=6666, Z2_num1=6666, Z2_num2=6666;

   for (int ilep1=0; ilep1<3; ilep1++)
    { 
     for (int ilep2=ilep1+1; ilep2<4; ilep2++)
      {
       int lep2ID = trueLeptonsID->at(ilep1)*trueLeptonsID->at(ilep2);
       if (lep2ID!=-121 && lep2ID!=-169) continue;
       currentZ = trueLeptons->at(ilep1)+trueLeptons->at(ilep2); 
       if (fabs(tempZ.M()-91.1876)>fabs(currentZ.M()-91.1876))
        {
         Z1_num1=ilep1;
         Z1_num2=ilep2;
         tempZ = trueLeptons->at(Z1_num1)+trueLeptons->at(Z1_num2);
        }
      }
    }

   if (Z1_num1!=0 && Z1_num1!=1 && Z1_num1!=2 && Z1_num1!=3) continue;

   for (int inum=0; inum<3; inum++)
    {
     if (inum!=Z1_num1 && inum!=Z1_num2) 
      {
       Z2_num1 = inum;
       break;
      }
    }

   for (int inum=0; inum<4; inum++)
    {
     if (inum!=Z1_num1 && inum!=Z1_num2 && inum!=Z2_num1) Z2_num2 = inum;
    }
   firstZ = trueLeptons->at(Z1_num1)+trueLeptons->at(Z1_num2);
   secondZ = trueLeptons->at(Z2_num1)+trueLeptons->at(Z2_num2);
   
   myHists->cutflow->Fill(2.5,weight);
   myHists->cutflow_raw->Fill(2.5,weight0);

   double max1, max2;
   max1 = max(trueLeptonrel03->at(Z1_num1),trueLeptonrel03->at(Z1_num2));
   max2 = max(trueLeptonrel03->at(Z2_num1),trueLeptonrel03->at(Z2_num2));
   myHists->max_leprel1->Fill(max1,weight);
   myHists->max_leprel2->Fill(max2,weight);

   double min_mll=6666,temp_mll=6666;
   for (int ilep1=0; ilep1<3; ilep1++) 
    {
     for (int ilep2=ilep1+1; ilep2<4; ilep2++)
      {
       temp_mll=(trueLeptons->at(ilep1)+trueLeptons->at(ilep2)).M();
       if (temp_mll<min_mll) min_mll=temp_mll;
      }
    }
   if (min_mll!=6666) myHists->min_mll->Fill(min_mll,weight);

/*************event selections*************/
   if (firstZ.M()<71 || firstZ.M()>111 || secondZ.M()<71 || secondZ.M()>111)
    {
     trueLeptons->clear();
     trueLeptonsID->clear();
     trueLeptonsPt->clear();
     trueLeptonsEta->clear();
     trueLeptonsPhi->clear();
     trueLeptonrel03->clear();
     trueLeptonrel04->clear();
     trueLepton_isMediumPOG->clear();
     trueJets->clear();
     trueFatJets->clear();
     trueFatJetMass->clear();
     trueFatJetPt->clear();
     trueFatJetEta->clear();
     trueFatJetTau21->clear();
     continue;
    }
   myHists->cutflow->Fill(3.5,weight);
   myHists->cutflow_raw->Fill(3.5,weight0);

   if (trueFatJets->size()<1)
    {
     trueLeptons->clear();
     trueLeptonsID->clear();
     trueLeptonsPt->clear();
     trueLeptonsEta->clear();
     trueLeptonsPhi->clear();
     trueLeptonrel03->clear();
     trueLeptonrel04->clear();
     trueLepton_isMediumPOG->clear();
     trueJets->clear();
     trueFatJets->clear();
     trueFatJetMass->clear();
     trueFatJetPt->clear();
     trueFatJetEta->clear();
     trueFatJetTau21->clear();
     continue;
    }

   myHists->cutflow->Fill(4.5,weight);
   myHists->cutflow_raw->Fill(4.5,weight0);

   int fatjetMassRange=0;
   double maxMass=0;
   double nearestMass=0;
   for(int ivec=0; ivec<trueFatJets->size(); ivec++)
    {
     if (70<trueFatJetMass->at(ivec) && trueFatJetMass->at(ivec)<110) fatjetMassRange+=1;  
     if (fabs(trueFatJetMass->at(ivec)-85) < fabs(nearestMass-85)) nearestMass=trueFatJetMass->at(ivec);
     if (trueFatJetMass->at(ivec)>maxMass) maxMass=trueFatJetMass->at(ivec);
    }

   if (fatjetMassRange==0) 
    {
     trueLeptons->clear();
     trueLeptonsID->clear();
     trueLeptonsPt->clear();
     trueLeptonsEta->clear();
     trueLeptonsPhi->clear();
     trueLeptonrel03->clear();
     trueLeptonrel04->clear();
     trueLepton_isMediumPOG->clear();
     trueJets->clear();
     trueFatJets->clear();
     trueFatJetMass->clear();
     trueFatJetPt->clear();
     trueFatJetEta->clear();
     trueFatJetTau21->clear();
     continue;
    }

   myHists->cutflow->Fill(5.5,weight);
   myHists->cutflow_raw->Fill(5.5,weight0);

   if (fatjetMassRange!=1)
    {
     trueLeptons->clear();
     trueLeptonsID->clear();
     trueLeptonsPt->clear();
     trueLeptonsEta->clear();
     trueLeptonsPhi->clear();
     trueLeptonrel03->clear();
     trueLeptonrel04->clear();
     trueLepton_isMediumPOG->clear();
     trueJets->clear();
     trueFatJets->clear();
     trueFatJetMass->clear();
     trueFatJetPt->clear();
     trueFatJetEta->clear();
     trueFatJetTau21->clear();
     continue;
    }

   ZZZ = trueLeptons->at(0)+trueLeptons->at(1)+trueLeptons->at(2)+trueLeptons->at(3)+trueFatJets->at(0);
//   myHists->cutflow->Fill(6.5,weight);
//   myHists->cutflow_raw->Fill(6.5,weight0);
   myHists->fatjetMass_Pt_lead->Fill(trueFatJetMass->at(0),trueFatJetPt->at(0),weight);
   myHists->fatjetMass_tau21_lead->Fill(trueFatJetMass->at(0),trueFatJetTau21->at(0),weight);
   myHists->fatjettau21_Pt_lead->Fill(trueFatJetTau21->at(0),trueFatJetPt->at(0),weight);
   myHists->ZZZMass_fatjetMass_lead->Fill(ZZZ.M(),trueFatJetMass->at(0),weight);
   myHists->ZZZMass_fatjetPt_lead->Fill(ZZZ.M(),trueFatJetPt->at(0),weight);
   myHists->ZZZMass_fatjettau21_lead->Fill(ZZZ.M(),trueFatJetTau21->at(0),weight);
   
/*************event selections*************/
/*   if (ZZZ.M()<1000)
    {
     trueLeptons->clear();
     trueLeptonsID->clear();
     trueLeptonsPt->clear();
     trueLeptonsEta->clear();
     trueLeptonsPhi->clear();
     trueLeptonrel03->clear();
     trueLeptonrel04->clear();
     trueLepton_isMediumPOG->clear();
     trueJets->clear();
     trueFatJets->clear();
     trueFatJetMass->clear();
     trueFatJetPt->clear();
     trueFatJetEta->clear();
     trueFatJetTau21->clear();
     continue;
    }

   myHists->cutflow->Fill(3.5,weight);
   myHists->cutflow_raw->Fill(3.5,weight0);

   if (firstZ.M()<80 || firstZ.M()>100 || secondZ.M()<80 || secondZ.M()>100)
    {
     trueLeptons->clear();
     trueLeptonsID->clear();
     trueLeptonsPt->clear();
     trueLeptonsEta->clear();
     trueLeptonsPhi->clear();
     trueLeptonrel03->clear();
     trueLeptonrel04->clear();
     trueLepton_isMediumPOG->clear();
     trueJets->clear();
     trueFatJets->clear();
     trueFatJetMass->clear();
     trueFatJetPt->clear();
     trueFatJetEta->clear();
     trueFatJetTau21->clear();
     continue;
    }

   myHists->cutflow->Fill(4.5,weight);
   myHists->cutflow_raw->Fill(4.5,weight0);

   if (trueFatJetMass->at(0)<50 || trueFatJetMass->at(0)>130)
    {
     trueLeptons->clear();
     trueLeptonsID->clear();
     trueLeptonsPt->clear();
     trueLeptonsEta->clear();
     trueLeptonsPhi->clear();
     trueLeptonrel03->clear();
     trueLeptonrel04->clear();
     trueLepton_isMediumPOG->clear();
     trueJets->clear();
     trueFatJets->clear();
     trueFatJetMass->clear();
     trueFatJetPt->clear();
     trueFatJetEta->clear();
     trueFatJetTau21->clear();
     continue;
    }

   myHists->cutflow->Fill(5.5,weight);
   myHists->cutflow_raw->Fill(5.5,weight0);
*/
/*   if (trueLeptonsPt->at(0)<150)
    {
     trueLeptons->clear();
     trueLeptonsID->clear();
     trueLeptonsPt->clear();
     trueLeptonsEta->clear();
     trueLeptonsPhi->clear();
     trueLeptonrel03->clear();
     trueLeptonrel04->clear();
     trueLepton_isMediumPOG->clear();
     trueJets->clear();
     trueFatJets->clear();
     trueFatJetMass->clear();
     trueFatJetPt->clear();
     trueFatJetEta->clear();
     trueFatJetTau21->clear();
     continue;
    }

   myHists->cutflow->Fill(5.5,weight);
   myHists->cutflow_raw->Fill(5.5,weight0);

   if (trueFatJetTau21->at(0)>0.7)
    {
     trueLeptons->clear();
     trueLeptonsID->clear();
     trueLeptonsPt->clear();
     trueLeptonsEta->clear();
     trueLeptonsPhi->clear();
     trueLeptonrel03->clear();
     trueLeptonrel04->clear();
     trueLepton_isMediumPOG->clear();
     trueJets->clear();
     trueFatJets->clear();
     trueFatJetMass->clear();
     trueFatJetPt->clear();
     trueFatJetEta->clear();
     trueFatJetTau21->clear();
     continue;
    }

   myHists->cutflow->Fill(6.5,weight);
   myHists->cutflow_raw->Fill(6.5,weight0);
*/
/*
   if (trueFatJetTau21->at(1)>0.5)
    {
     trueLeptons->clear();
     trueLeptonsID->clear();
     trueLeptonsPt->clear();
     trueLeptonsEta->clear();
     trueLeptonsPhi->clear();
     trueLeptonrel03->clear();
     trueLeptonrel04->clear();
     trueLepton_isMediumPOG->clear();
     trueJets->clear();
     trueFatJets->clear();
     trueFatJetMass->clear();
     trueFatJetPt->clear();
     trueFatJetEta->clear();
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
     trueLeptonrel03->clear();
     trueLeptonrel04->clear();
     trueLepton_isMediumPOG->clear();
     trueJets->clear();
     trueFatJets->clear();
     trueFatJetMass->clear();
     trueFatJetPt->clear();
     trueFatJetEta->clear();
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
     trueLeptonrel03->clear();
     trueLeptonrel04->clear();
     trueLepton_isMediumPOG->clear();
     trueJets->clear();
     trueFatJets->clear();
     trueFatJetMass->clear();
     trueFatJetPt->clear();
     trueFatJetEta->clear();
     trueFatJetTau21->clear();
     continue;
    }

   myHists->cutflow->Fill(10.5,weight);
   myHists->cutflow_raw->Fill(10.5,weight0);
*/

/**************plot filling****************/
   myHists->nb->Fill(nb,weight);
   myHists->jetNumbers->Fill(trueJets->size(),weight);
   myHists->fatjetNumbers->Fill(trueFatJets->size(),weight);
   myHists->MissingET_pt->Fill(met_pt,weight);
   myHists->ScalarPt->Fill(trueLeptonsPt->at(0)+trueLeptonsPt->at(1)+trueLeptonsPt->at(2)+trueLeptonsPt->at(3)+trueFatJetPt->at(0),weight);   

   myHists->fatjetMaxMass->Fill(maxMass,weight);
   myHists->fatjetNearestMass->Fill(nearestMass,weight);
   myHists->fatjetMass_lead->Fill(trueFatJetMass->at(0),weight);
   myHists->fatjet_tau21_lead->Fill(trueFatJetTau21->at(0),weight);
   myHists->fatjet_pt_lead->Fill(trueFatJetPt->at(0),weight);
   myHists->fatjet_eta->Fill(trueFatJetEta->at(0),weight);

   myHists->leptonPt_lead->Fill(trueLeptonsPt->at(0),weight);
   myHists->leptonEta_lead->Fill(trueLeptonsEta->at(0),weight);
   myHists->leptonPhi_lead->Fill(trueLeptonsPhi->at(0),weight);

   myHists->leptonPt_sub->Fill(trueLeptonsPt->at(1),weight);
   myHists->leptonEta_sub->Fill(trueLeptonsEta->at(1),weight);
   myHists->leptonPhi_sub->Fill(trueLeptonsPhi->at(1),weight);

   myHists->leptonPt_third->Fill(trueLeptonsPt->at(2),weight);
   myHists->leptonEta_third->Fill(trueLeptonsEta->at(2),weight);
   myHists->leptonPhi_third->Fill(trueLeptonsPhi->at(2),weight);

   myHists->leptonPt_fourth->Fill(trueLeptonsPt->at(3),weight);
   myHists->leptonEta_fourth->Fill(trueLeptonsEta->at(3),weight);
   myHists->leptonPhi_fourth->Fill(trueLeptonsPhi->at(3),weight);

   myHists->ZZZ_mass->Fill(ZZZ.M(),weight);

   myHists->firstZMass->Fill(firstZ.M(),weight);
   myHists->firstZPt->Fill(firstZ.Pt(),weight);
   myHists->secondZMass->Fill(secondZ.M(),weight);
   myHists->secondZPt->Fill(secondZ.Pt(),weight);
   myHists->deltaZPt->Fill(firstZ.Pt()-secondZ.Pt(),weight);

/************clearing variables************/
   trueLeptons->clear();
   trueLeptonsID->clear();
   trueLeptonsPt->clear();
   trueLeptonsEta->clear();
   trueLeptonsPhi->clear();
   trueLeptonrel03->clear();
   trueLeptonrel04->clear();
   trueLepton_isMediumPOG->clear();
   trueJets->clear();
   trueFatJets->clear();
   trueFatJetMass->clear();
   trueFatJetPt->clear();
   trueFatJetEta->clear();
   trueFatJetTau21->clear();

  }//main looping
}//ZZZAna::loop ends
