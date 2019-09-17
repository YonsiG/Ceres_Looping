#ifndef _MAKEHIST_H_
#define _MAKEHIST_H_

#include <iostream>
#include "TTree.h"
#include "TH1D.h"

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

  TH1D *leptonPhi;
  TH1D *leptonPhi_ee;
  TH1D *leptonPhi_mm;
  TH1D *leptonPhi_em;

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

  TH1D *trueZPt_lead;
  TH1D *trueZPt_sub;
  TH1D *trueZPt_third;

  void createHists(const char* fileName); 
  void saveHists();
};
#endif
