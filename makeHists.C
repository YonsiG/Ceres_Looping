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

 cutflow = new TH1D("cutflow","cutflow",10,0,10);
 cutflow_ee = new TH1D("cutflow_ee","cutflow_ee",10,0,10);
 cutflow_em = new TH1D("cutflow_em","cutflow_em",10,0,10);
 cutflow_mm = new TH1D("cutflow_mm","cutflow_mm",10,0,10); 

 cutflow_raw = new TH1D("cutflow_raw","cutflow_raw",10,0,10);
 cutflow_ee_raw = new TH1D("cutflow_ee_raw","cutflow_ee_raw",10,0,10);
 cutflow_em_raw = new TH1D("cutflow_em_raw","cutflow_em_raw",10,0,10);
 cutflow_mm_raw = new TH1D("cutflow_mm_raw","cutflow_mm_raw",10,0,10);

 dileptonMass = new TH1D("dileptonMass","dileptonMass",60,60,120);
 dileptonMass_ee = new TH1D("dileptonMass_ee","dileptonMass_ee",60,60,120);
 dileptonMass_mm = new TH1D("dileptonMass_mm","dileptonMass_mm",60,60,120);
 dileptonMass_em = new TH1D("dileptonMass_em","dileptonMass_em",60,0,180);
 dileptonMass->Sumw2();
 dileptonMass_ee->Sumw2();
 dileptonMass_mm->Sumw2();
 dileptonMass_em->Sumw2();

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

 leptonPhi = new TH1D("leptonPhi","leptonPhi",100,-4,4);
 leptonPhi_ee = new TH1D("leptonPhi_ee","leptonPhi_ee",100,-4,4);
 leptonPhi_mm = new TH1D("leptonPhi_mm","leptonPhi_mm",100,-4,4);
 leptonPhi_em = new TH1D("leptonPhi_em","leptonPhi_em",100,-4,4);
 leptonPhi->Sumw2();
 leptonPhi_ee->Sumw2();
 leptonPhi_mm->Sumw2();
 leptonPhi_em->Sumw2();

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

 fatjetNumbers = new TH1D("fatjetNumbers","fatjetNumbers",5,0,5);
 fatjetNumbers_ee = new TH1D("fatjetNumbers_ee","fatjetNumbers_ee",5,0,5);
 fatjetNumbers_mm = new TH1D("fatjetNumbers_mm","fatjetNumbers_mm",5,0,5);
 fatjetNumbers_em = new TH1D("fatjetNumbers_em","fatjetNumbers_em",5,0,5);
 fatjetNumbers->Sumw2();
 fatjetNumbers_ee->Sumw2();
 fatjetNumbers_mm->Sumw2();
 fatjetNumbers_em->Sumw2();

 fatjetMass_lead = new TH1D("fatjetMass_lead","fatjetMass_lead",80,0,160);
 fatjetMass_ee_lead = new TH1D("fatjetMass_ee_lead","fatjetMass_ee_lead",80,0,160);
 fatjetMass_mm_lead = new TH1D("fatjetMass_mm_lead","fatjetMass_mm_lead",80,0,160);
 fatjetMass_em_lead = new TH1D("fatjetMass_em_lead","fatjetMass_em_lead",80,0,160);
 fatjetMass_lead->Sumw2();
 fatjetMass_ee_lead->Sumw2();
 fatjetMass_mm_lead->Sumw2();
 fatjetMass_em_lead->Sumw2();

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

 trueZPt_lead = new TH1D("trueZPt_lead","trueZPt_lead",100,0,400);
 trueZPt_sub = new TH1D("trueZPt_sub","trueZPt_sub",100,0,400);
 trueZPt_third = new TH1D("trueZPt_third","trueZPt_third",100,0,400);
}

void makeHists::saveHists()
{
 hf->cd();
 hf->Write();
 hf->Close();
}
