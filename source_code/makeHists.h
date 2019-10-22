#ifndef _MAKEHIST_H_
#define _MAKEHIST_H_

#include <iostream>
#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"

class makeHists
{
  public:

  TFile *hf;

  TH1D *cutflow;
  TH1D *cutflow_ee;
  TH1D *cutflow_em;
  TH1D *cutflow_mm;

  TH1D *cutflow_raw;
  TH1D *cutflow_ee_raw;
  TH1D *cutflow_em_raw;
  TH1D *cutflow_mm_raw;

  TH1D *dileptonMass;
  TH1D *dileptonMass_ee;
  TH1D *dileptonMass_mm;
  TH1D *dileptonMass_em;
  
  TH1D *max_leprel1;
  TH1D *max_leprel2;
  TH1D *min_mll;

  TH1D *leptonPt_lead;
  TH1D *leptonPt_ee_lead;
  TH1D *leptonPt_mm_lead;
  TH1D *leptonPt_em_lead;
  
  TH1D *leptonEta_lead;
  TH1D *leptonEta_ee_lead;
  TH1D *leptonEta_mm_lead;
  TH1D *leptonEta_em_lead;
  
  TH1D *leptonPt_sub;
  TH1D *leptonPt_ee_sub;
  TH1D *leptonPt_mm_sub;
  TH1D *leptonPt_em_sub;

  TH1D *leptonEta_sub;
  TH1D *leptonEta_ee_sub;
  TH1D *leptonEta_mm_sub;
  TH1D *leptonEta_em_sub;

  TH1D *leptonPhi_lead;
  TH1D *leptonPhi_ee_lead;
  TH1D *leptonPhi_mm_lead;
  TH1D *leptonPhi_em_lead;

  TH1D *leptonPhi_sub;
  TH1D *leptonPhi_ee_sub;
  TH1D *leptonPhi_mm_sub;
  TH1D *leptonPhi_em_sub;

  TH1D *leptonPt_third;
  TH1D *leptonPt_fourth;
  TH1D *leptonEta_third;
  TH1D *leptonEta_fourth;
  TH1D *leptonPhi_third;
  TH1D *leptonPhi_fourth;

  TH1D *dileptonPt;
  TH1D *dileptonPt_ee;
  TH1D *dileptonPt_mm;  
  TH1D *dileptonPt_em;

  TH1D *jetNumbers;
  TH1D *jetNumbers_ee;
  TH1D *jetNumbers_mm;
  TH1D *jetNumbers_em;

  TH1D *fatjetNumbers;
  TH1D *fatjetNumbers_ee;
  TH1D *fatjetNumbers_mm;
  TH1D *fatjetNumbers_em;

  TH1D *fatjetMass_lead;
  TH1D *fatjetMass_ee_lead;
  TH1D *fatjetMass_mm_lead;
  TH1D *fatjetMass_em_lead;

  TH1D *fatjetMass_sub;
  TH1D *fatjetMass_ee_sub;
  TH1D *fatjetMass_mm_sub;
  TH1D *fatjetMass_em_sub;
 
  TH1D *fatjetMaxMass;
  TH1D *fatjetNearestMass; 

  TH1D *fatjet_tau21_lead;
  TH1D *fatjet_tau21_ee_lead;
  TH1D *fatjet_tau21_mm_lead;
  TH1D *fatjet_tau21_em_lead;

  TH1D *fatjet_tau21_sub;
  TH1D *fatjet_tau21_ee_sub;
  TH1D *fatjet_tau21_mm_sub;
  TH1D *fatjet_tau21_em_sub;

  TH1D *fatjet_pt_lead;
  TH1D *fatjet_pt_ee_lead;
  TH1D *fatjet_pt_mm_lead;
  TH1D *fatjet_pt_em_lead;

  TH1D *fatjet_pt_sub;
  TH1D *fatjet_pt_ee_sub;
  TH1D *fatjet_pt_mm_sub;
  TH1D *fatjet_pt_em_sub;

  TH1D *fatjet_eta;
  TH1D *MissingET_pt;
  TH1D *trueZPt_lead;
  TH1D *trueZPt_sub;
  TH1D *trueZPt_third;
  TH1D *deltaPhi_ls;
  TH1D *deltaPhi_st;
  TH1D *deltaPhi_lt;

  TH1D *ScalarPt;
  TH1D *ZZZ_mass;
  TH1D *firstZMass;
  TH1D *firstZPt;
  TH1D *secondZMass;
  TH1D *secondZPt;
  TH1D *deltaZPt;
  TH1D *nb;

  TH2D *fatjetMass_Pt_lead;
  TH2D *fatjetMass_Pt_sub;
  TH2D *fatjetMass_tau21_lead;
  TH2D *fatjetMass_tau21_sub;
  TH2D *fatjettau21_Pt_lead;
  TH2D *fatjettau21_Pt_sub;

  TH2D *ZZZMass_fatjetMass_lead;
  TH2D *ZZZMass_fatjettau21_lead;
  TH2D *ZZZMass_fatjetPt_lead;
  TH2D *ZZZMass_fatjetMass_sub;
  TH2D *ZZZMass_fatjettau21_sub;
  TH2D *ZZZMass_fatjetPt_sub;

  void createHists(const char* fileName); 
  void saveHists();
};
#endif
