#ifndef _ZZZANA_H_
#define _ZZZANA_H_

#include "makeHists.h"
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TMath.h>
#include <TH1F.h>
#include <TH1D.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLorentzVector.h>
#include <TH3F.h>
#include <TRandom3.h>
#include <TMinuit.h>
#include <TApplication.h>
#include <TEnv.h>
#include <TComplex.h>
#include <TH2D.h>
#include "Math/LorentzVector.h"

using namespace std;
class ZZZAna
{
 public:
 
 /***************test variables*****************/
 bool isRead;

 /*****************Tree input*******************/
 TTree *fChain;

 /***********Tree branch vairables**************/
 std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float>>>*       lep_p4=0;
 std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float>>>*       jets_p4=0;
 std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float>>>*       fatjets_p4=0;
 std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float>>>*       gen_part_p4=0;
 std::vector<double>*               J_SD_mass=0;
 std::vector<double>*               J_tau21=0;
 std::vector<double>*               J_pt=0;
 std::vector<double>*               lep_pt=0;
 std::vector<double>*               lep_eta=0;
 std::vector<double>*               lep_phi=0;
 std::vector<double>*               gen_part_pt=0;
 std::vector<int>*                  lep_isWVZVeto=0;
 std::vector<int>*                  lep_id=0;
 std::vector<int>*                  gen_part_id=0;
 std::vector<int>*                  gen_part_status=0;
 Float_t                            weight;
 
 /************tatistical variables**************/
 Int_t                             Sta_TotalNumber;

 /******************functions*******************/
 ZZZAna(const char* infileName, const char* typeName);
 virtual ~ZZZAna();
 virtual void Initial(const char* rootName, int rootNumber);
 virtual void Loop(const char* typeName);
 virtual void End(int rootNumber);
 virtual void Save(int rootNumber);

 /********************plots*********************/
 makeHists* myHists;

};//class ZZZAna definition ends

#endif //end define _ZZZANA_H_

#ifdef _ZZZANA_C_ //if already defined, then add functions
ZZZAna::ZZZAna(const char* infileName, const char* typeName)
{
 myHists = new makeHists();
 TString histName = (TString) typeName + "_selected.root";
 myHists->createHists(histName);
}

ZZZAna::~ZZZAna(){}

void ZZZAna::Initial(const char* rootName, int rootNumber)
{
 Sta_TotalNumber = 0;
 cout<<"**Running starting Rootfile: "<<rootNumber<<endl;

 TTree *tree;
 TFile *file = (TFile *)gROOT->GetListOfFiles()->FindObject(rootName);
 if(!file) file = new TFile(rootName);
 tree = (TTree *)gDirectory->Get("t");

 fChain = tree;
 isRead = true;

 double fileEntries = fChain->GetEntries();
 if(fileEntries == 0) isRead = false;

 /***************set branches**************/
 fChain->SetBranchAddress("lep_p4",&lep_p4);
 fChain->SetBranchAddress("lep_pt",&lep_pt);
 fChain->SetBranchAddress("lep_phi",&lep_phi);
 fChain->SetBranchAddress("lep_eta",&lep_eta);
 fChain->SetBranchAddress("jets_p4",&jets_p4);
 fChain->SetBranchAddress("evt_scale1fb",&weight);
 fChain->SetBranchAddress("lep_isWVZVeto",&lep_isWVZVeto);
 fChain->SetBranchAddress("lep_id",&lep_id);
 fChain->SetBranchAddress("jets_p4",&jets_p4);
 fChain->SetBranchAddress("J_p4",&fatjets_p4);
 fChain->SetBranchAddress("J_SD_mass",&J_SD_mass);
 fChain->SetBranchAddress("J_tau21",&J_tau21);
 fChain->SetBranchAddress("J_pt",&J_pt);
 fChain->SetBranchAddress("gen_part_p4",&gen_part_p4);
 fChain->SetBranchAddress("gen_part_pt",&gen_part_pt);
 fChain->SetBranchAddress("gen_part_id",&gen_part_id);
 fChain->SetBranchAddress("gen_part_status",&gen_part_status);
}

void ZZZAna::End(int rootNumber)
{
 cout<< "**Running: Free Rootfile: "<<rootNumber<<endl;
 cout<< "*************************"<<endl;
 cout<< "*********outputs*********"<<endl;
 cout<< "Total event number in this file:      "<<Sta_TotalNumber<<endl;
 delete fChain->GetCurrentFile();
}

void ZZZAna::Save(int rootNumber)
{
 cout<<"**Running: "<<rootNumber<<"  rootfiles finished"<<endl;
 cout<<"**The files contain "<<Sta_TotalNumber<<" events"<<endl;
 if(myHists)
 {
  myHists->saveHists();
  delete myHists;
 }
 cout<<"**Running histograms saved"<<endl;
}
#endif //end ifdef _ZZZANA_C_
