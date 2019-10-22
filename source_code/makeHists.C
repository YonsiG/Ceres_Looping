#include "makeHists.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TH3F.h"
#include "TFile.h"
#include "TProfile.h"
#include "TProfile2D.h"
#include "TMath.h"
#include "TTree.h"

using namespace std;
void makeHists::createHists(const char* fileName)
{
 hf = new TFile(fileName,"RECREATE");

 cutflow = new TH1D("cutflow","cutflow",12,0,12);
 cutflow_ee = new TH1D("cutflow_ee","cutflow_ee",12,0,12);
 cutflow_em = new TH1D("cutflow_em","cutflow_em",12,0,12);
 cutflow_mm = new TH1D("cutflow_mm","cutflow_mm",12,0,12); 

 cutflow_raw = new TH1D("cutflow_raw","cutflow_raw",12,0,12);
 cutflow_ee_raw = new TH1D("cutflow_ee_raw","cutflow_ee_raw",12,0,12);
 cutflow_em_raw = new TH1D("cutflow_em_raw","cutflow_em_raw",12,0,12);
 cutflow_mm_raw = new TH1D("cutflow_mm_raw","cutflow_mm_raw",12,0,12);

 dileptonMass = new TH1D("dileptonMass","dileptonMass",60,60,120);
 dileptonMass_ee = new TH1D("dileptonMass_ee","dileptonMass_ee",60,60,120);
 dileptonMass_mm = new TH1D("dileptonMass_mm","dileptonMass_mm",60,60,120);
 dileptonMass_em = new TH1D("dileptonMass_em","dileptonMass_em",60,0,180);
 dileptonMass->Sumw2();
 dileptonMass_ee->Sumw2();
 dileptonMass_mm->Sumw2();
 dileptonMass_em->Sumw2();

 max_leprel1 = new TH1D("max_leprel1","max_leprel1",50,0,0.4);
 max_leprel2 = new TH1D("max_leprel2","max_leprel2",50,0,0.4);
 min_mll = new TH1D("min_mll","min_mll",50,0,200);
 max_leprel1->Sumw2();
 max_leprel2->Sumw2();
 min_mll->Sumw2();

 leptonPt_lead = new TH1D("leptonPt_lead","leptonPt_lead",100,0,400);
 leptonPt_ee_lead = new TH1D("leptonPt_ee_lead","leptonPt_ee_lead",100,0,400);
 leptonPt_mm_lead = new TH1D("leptonPt_mm_lead","leptonPt_mm_lead",100,0,400);
 leptonPt_em_lead = new TH1D("leptonPt_em_lead","leptonPt_em_lead",100,0,400);
 leptonPt_lead->Sumw2();
 leptonPt_ee_lead->Sumw2();
 leptonPt_mm_lead->Sumw2();
 leptonPt_em_lead->Sumw2();

 leptonPt_sub = new TH1D("leptonPt_sub","leptonPt_sub",100,0,400);
 leptonPt_ee_sub = new TH1D("leptonPt_ee_sub","leptonPt_ee_sub",100,0,400);
 leptonPt_mm_sub = new TH1D("leptonPt_mm_sub","leptonPt_mm_sub",100,0,400);
 leptonPt_em_sub = new TH1D("leptonPt_em_sub","leptonPt_em_sub",100,0,400);
 leptonPt_sub->Sumw2();
 leptonPt_ee_sub->Sumw2();
 leptonPt_mm_sub->Sumw2();
 leptonPt_em_sub->Sumw2();

 leptonEta_lead = new TH1D("leptonEta_lead","leptonEta_lead",60,-3,3);
 leptonEta_ee_lead = new TH1D("leptonEta_ee_lead","leptonEta_ee_lead",60,-3,3);
 leptonEta_mm_lead = new TH1D("leptonEta_mm_lead","leptonEta_mm_lead",60,-3,3);
 leptonEta_em_lead = new TH1D("leptonEta_em_lead","leptonEta_em_lead",60,-3,3);
 leptonEta_lead->Sumw2();
 leptonEta_ee_lead->Sumw2();
 leptonEta_mm_lead->Sumw2();
 leptonEta_em_lead->Sumw2();

 leptonEta_sub = new TH1D("leptonEta_sub","leptonEta_sub",60,-3,3);
 leptonEta_ee_sub = new TH1D("leptonEta_ee_sub","leptonEta_ee_sub",60,-3,3);
 leptonEta_mm_sub = new TH1D("leptonEta_mm_sub","leptonEta_mm_sub",60,-3,3);
 leptonEta_em_sub = new TH1D("leptonEta_em_sub","leptonEta_em_sub",60,-3,3);
 leptonEta_sub->Sumw2();
 leptonEta_ee_sub->Sumw2();
 leptonEta_mm_sub->Sumw2();
 leptonEta_em_sub->Sumw2();

 leptonPhi_lead = new TH1D("leptonPhi_lead","leptonPhi_lead",100,-4,4);
 leptonPhi_ee_lead = new TH1D("leptonPhi_ee_lead","leptonPhi_ee_lead",100,-4,4);
 leptonPhi_mm_lead = new TH1D("leptonPhi_mm_lead","leptonPhi_mm_lead",100,-4,4);
 leptonPhi_em_lead = new TH1D("leptonPhi_em_lead","leptonPhi_em_lead",100,-4,4);
 leptonPhi_lead->Sumw2();
 leptonPhi_ee_lead->Sumw2();
 leptonPhi_mm_lead->Sumw2();
 leptonPhi_em_lead->Sumw2();

 leptonPhi_sub = new TH1D("leptonPhi_sub","leptonPhi_sub",100,-4,4);
 leptonPhi_ee_sub = new TH1D("leptonPhi_ee_sub","leptonPhi_ee_sub",100,-4,4);
 leptonPhi_mm_sub = new TH1D("leptonPhi_mm_sub","leptonPhi_mm_sub",100,-4,4);
 leptonPhi_em_sub = new TH1D("leptonPhi_em_sub","leptonPhi_em_sub",100,-4,4);
 leptonPhi_sub->Sumw2();
 leptonPhi_ee_sub->Sumw2();
 leptonPhi_mm_sub->Sumw2();
 leptonPhi_em_sub->Sumw2();

 leptonPt_third = new TH1D("leptonPt_third","lepton_third",100,0,400);
 leptonPt_fourth = new TH1D("leptonPt_fourth","leptonPt_fourth",100,0,400);
 leptonEta_third = new TH1D("leptonEta_third","leptonEta_third",60,-3,3);
 leptonEta_fourth = new TH1D("leptonEta_fourth","leptonEta_fourth",60,-3,3);
 leptonPhi_third = new TH1D("leptonPhi_third","leptonPhi_third",100,-4,4);
 leptonPhi_fourth = new TH1D("leptonPhi_fourth","leptonPhi_fourth",100,-4,4);

 dileptonPt = new TH1D("dileptonPt","dileptonPt",100,0,400);
 dileptonPt_ee = new TH1D("dileptonPt_ee","dileptonPt_ee",100,0,400);
 dileptonPt_mm = new TH1D("dileptonPt_mm","dileptonPt_mm",100,0,400);
 dileptonPt_em = new TH1D("dileptonPt_em","dileptonPt_em",100,0,400);
 dileptonPt->Sumw2();
 dileptonPt_ee->Sumw2();
 dileptonPt_mm->Sumw2();
 dileptonPt_em->Sumw2();

 jetNumbers = new TH1D("jetNumbers","jetNumbers",10,0,10);
 jetNumbers_ee = new TH1D("jetNumbers_ee","jetNumbers_ee",10,0,10);
 jetNumbers_mm = new TH1D("jetNumbers_mm","jetNumbers_mm",10,0,10);
 jetNumbers_em = new TH1D("jetNumbers_em","jetNumbers_em",10,0,10);
 jetNumbers->Sumw2();
 jetNumbers_ee->Sumw2();
 jetNumbers_mm->Sumw2();
 jetNumbers_em->Sumw2();

 nb = new TH1D("nb","nb",10,0,10);
 fatjetNumbers = new TH1D("fatjetNumbers","fatjetNumbers",5,0,5);
 fatjetNumbers_ee = new TH1D("fatjetNumbers_ee","fatjetNumbers_ee",5,0,5);
 fatjetNumbers_mm = new TH1D("fatjetNumbers_mm","fatjetNumbers_mm",5,0,5);
 fatjetNumbers_em = new TH1D("fatjetNumbers_em","fatjetNumbers_em",5,0,5);
 fatjetNumbers->Sumw2();
 fatjetNumbers_ee->Sumw2();
 fatjetNumbers_mm->Sumw2();
 fatjetNumbers_em->Sumw2();
 nb->Sumw2();

 fatjetMaxMass = new TH1D("fatjetMaxMass","fatjetMaxMass",80,40,160);
 fatjetNearestMass = new TH1D("fatjetNearestMass","fatjetNearestMass",80,40,160);
 fatjetMass_lead = new TH1D("fatjetMass_lead","fatjetMass_lead",80,0,160);
 fatjetMass_ee_lead = new TH1D("fatjetMass_ee_lead","fatjetMass_ee_lead",80,0,160);
 fatjetMass_mm_lead = new TH1D("fatjetMass_mm_lead","fatjetMass_mm_lead",80,0,160);
 fatjetMass_em_lead = new TH1D("fatjetMass_em_lead","fatjetMass_em_lead",80,0,160);
 fatjetMass_lead->Sumw2();
 fatjetMass_ee_lead->Sumw2();
 fatjetMass_mm_lead->Sumw2();
 fatjetMass_em_lead->Sumw2();
 fatjetMaxMass->Sumw2();
 fatjetNearestMass->Sumw2();

 fatjet_tau21_lead = new TH1D("fatjet_tau21_lead","fatjet_tau21_lead",50,0,1);
 fatjet_tau21_ee_lead = new TH1D("fatjet_tau21_ee_lead","fatjet_tau21_ee_lead",50,0,1);
 fatjet_tau21_mm_lead = new TH1D("fatjet_tau21_mm_lead","fatjet_tau21_mm_lead",50,0,1);
 fatjet_tau21_em_lead = new TH1D("fatjet_tau21_em_lead","fatjet_tau21_em_lead",50,0,1);
 fatjet_tau21_lead->Sumw2();
 fatjet_tau21_ee_lead->Sumw2();
 fatjet_tau21_mm_lead->Sumw2();
 fatjet_tau21_em_lead->Sumw2();

 fatjet_pt_lead = new TH1D("fatjet_pt_lead","fatjet_pt_lead",120,0,1200);
 fatjet_pt_ee_lead = new TH1D("fatjet_pt_ee_lead","fatjet_pt_ee_lead",120,0,1200);
 fatjet_pt_mm_lead = new TH1D("fatjet_pt_mm_lead","fatjet_pt_mm_lead",120,0,1200);
 fatjet_pt_em_lead = new TH1D("fatjet_pt_em_lead","fatjet_pt_em_lead",120,0,1200);
 fatjet_pt_lead->Sumw2();
 fatjet_pt_ee_lead->Sumw2();
 fatjet_pt_mm_lead->Sumw2();
 fatjet_pt_em_lead->Sumw2();

 fatjet_eta = new TH1D("fatjet_eta","fatjet_eta",60,-3,3);
 fatjet_eta->Sumw2();

 fatjetMass_sub = new TH1D("fatjetMass_sub","fatjetMass_sub",80,0,160);
 fatjetMass_ee_sub = new TH1D("fatjetMass_ee_sub","fatjetMass_ee_sub",80,0,160);
 fatjetMass_mm_sub = new TH1D("fatjetMass_mm_sub","fatjetMass_mm_sub",80,0,160);
 fatjetMass_em_sub = new TH1D("fatjetMass_em_sub","fatjetMass_em_sub",80,0,160);
 fatjetMass_sub->Sumw2();
 fatjetMass_ee_sub->Sumw2();
 fatjetMass_mm_sub->Sumw2();
 fatjetMass_em_sub->Sumw2();

 fatjet_tau21_sub = new TH1D("fatjet_tau21_sub","fatjet_tau21_sub",50,0,1);
 fatjet_tau21_ee_sub = new TH1D("fatjet_tau21_ee_sub","fatjet_tau21_ee_sub",50,0,1);
 fatjet_tau21_mm_sub = new TH1D("fatjet_tau21_mm_sub","fatjet_tau21_mm_sub",50,0,1);
 fatjet_tau21_em_sub = new TH1D("fatjet_tau21_em_sub","fatjet_tau21_em_sub",50,0,1);
 fatjet_tau21_sub->Sumw2();
 fatjet_tau21_ee_sub->Sumw2();
 fatjet_tau21_mm_sub->Sumw2();
 fatjet_tau21_em_sub->Sumw2();

 fatjet_pt_sub = new TH1D("fatjet_pt_sub","fatjet_pt_sub",120,0,1200);
 fatjet_pt_ee_sub = new TH1D("fatjet_pt_ee_sub","fatjet_pt_ee_sub",120,0,1200);
 fatjet_pt_mm_sub = new TH1D("fatjet_pt_mm_sub","fatjet_pt_mm_sub",120,0,1200);
 fatjet_pt_em_sub = new TH1D("fatjet_pt_em_sub","fatjet_pt_em_sub",120,0,1200);
 fatjet_pt_sub->Sumw2();
 fatjet_pt_ee_sub->Sumw2();
 fatjet_pt_mm_sub->Sumw2();
 fatjet_pt_em_sub->Sumw2();

 trueZPt_lead = new TH1D("trueZPt_lead","trueZPt_lead",100,0,1000);
 trueZPt_sub = new TH1D("trueZPt_sub","trueZPt_sub",100,0,1000);
 trueZPt_third = new TH1D("trueZPt_third","trueZPt_third",100,0,1000);
 trueZPt_lead->Sumw2();
 trueZPt_sub->Sumw2();
 trueZPt_third->Sumw2();

 deltaPhi_ls = new TH1D("deltaPhi_ls","deltaPhi_ls",180,0,180);
 deltaPhi_st = new TH1D("deltaPhi_st","deltaPhi_st",180,0,180);
 deltaPhi_lt = new TH1D("deltaPhi_lt","deltaPhi_lt",180,0,180);
 deltaPhi_ls->Sumw2();
 deltaPhi_st->Sumw2();
 deltaPhi_lt->Sumw2();

 ZZZ_mass = new TH1D("ZZZ_mass","ZZZ_mass",1500,0,3000);
 ZZZ_mass->Sumw2();

 ScalarPt = new TH1D("ScalarPt","ScalarPt",20,0,2000);

 MissingET_pt = new TH1D("MissingET_pt","MissingET_pt",24,0,600);
 MissingET_pt->Sumw2();

 firstZMass = new TH1D("firstZMass","firstZMass",60,60,120);
 firstZPt = new TH1D("firstZPt","firstZPt",100,0,400);
 secondZMass = new TH1D("secondZMass","secondZMass",60,60,120);
 secondZPt = new TH1D("secondZPt","secondZPt",100,0,400);
 deltaZPt = new TH1D("deltaZPt","deltaZPt",50,-500,500);
 firstZMass->Sumw2();
 firstZPt->Sumw2();
 secondZMass->Sumw2();
 secondZPt->Sumw2();
 deltaZPt->Sumw2();

 fatjetMass_Pt_lead = new TH2D("fatjetMass_Pt_lead","fatjetMass_Pt_lead",20,0,160,24,0,1200);
 fatjetMass_Pt_sub = new TH2D("fatjetMass_Pt_sub","fatjetMass_Pt_sub",20,0,160,24,0,1200);
 fatjetMass_tau21_lead = new TH2D("fatjetMass_tau21_lead","fatjetMass_tau21_lead",20,0,160,10,0,1);
 fatjetMass_tau21_sub = new TH2D("fatjetMass_tau21_sub","fatjetMass_tau21_sub",20,0,160,10,0,1);
 fatjettau21_Pt_lead = new TH2D("fatjettau21_Pt_lead","fatjettau21_Pt_lead",10,0,1,24,0,1200);
 fatjettau21_Pt_sub = new TH2D("fatjettau21_Pt_sub","fatjettau21_Pt_sub",10,0,1,15,0,1200);
 fatjetMass_Pt_lead->Sumw2();
 fatjetMass_Pt_sub->Sumw2();
 fatjetMass_tau21_lead->Sumw2();
 fatjetMass_tau21_sub->Sumw2();
 fatjettau21_Pt_lead->Sumw2();
 fatjettau21_Pt_sub->Sumw2();

 ZZZMass_fatjetMass_lead = new TH2D("ZZZMass_fatjetMass_lead","ZZZMass_fatjetMass_lead",30,0,3000,20,0,160);
 ZZZMass_fatjetPt_lead = new TH2D("ZZZMass_fatjetPt_lead","ZZZMass_fatjetPt_lead",30,0,3000,24,0,1200);
 ZZZMass_fatjettau21_lead = new TH2D("ZZZMass_fatjettau21_lead","ZZZMass_fatjettau21_lead",30,0,3000,10,0,1);
 ZZZMass_fatjetMass_sub = new TH2D("ZZZMass_fatjetMass_sub","ZZZMass_fatjetMass_sub",30,0,3000,20,0,160);
 ZZZMass_fatjetPt_sub = new TH2D("ZZZMass_fatjetPt_sub","ZZZMass_fatjetPt_sub",30,0,3000,15,0,1200);
 ZZZMass_fatjettau21_sub = new TH2D("ZZZMass_fatjettau21_sub","ZZZMass_fatjettau21_sub",30,0,3000,10,0,1);
 ZZZMass_fatjetMass_sub->Sumw2();
 ZZZMass_fatjetPt_sub->Sumw2();
 ZZZMass_fatjettau21_sub->Sumw2();
 ZZZMass_fatjetMass_lead->Sumw2();
 ZZZMass_fatjetPt_lead->Sumw2();
 ZZZMass_fatjettau21_lead->Sumw2();
}

void makeHists::saveHists()
{
 hf->cd();
 hf->Write();
 hf->Close();
}
