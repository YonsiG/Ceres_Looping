void gen_cuttable()
{
 TFile *infile_sig = new TFile("../../../outfiles/4l1F/signal_selected.root","r");
 TFile *infile_sig_h = new TFile("../../../outfiles/4l1F/signal_h_selected.root","r");
 TFile *infile_ZZ = new TFile("../../../outfiles/4l1F/ZZ_selected.root","r");
 TFile *infile_WZ = new TFile("../../../outfiles/4l1F/WZ_selected.root","r");
 TFile *infile_tWZ = new TFile("../../../outfiles/4l1F/tWZ_selected.root","r");
 TFile *infile_h = new TFile("../../../outfiles/4l1F/h_selected.root","r");
 TFile *infile_ttZ = new TFile("../../../outfiles/4l1F/ttZ_selected.root","r");
 TFile *infile_stt = new TFile("../../../outfiles/4l1F/stt_selected.root","r");
 TFile *infile_others = new TFile("../../../outfiles/4l1F/others_selected.root","r");
 TH1D *cutflow_sig = (TH1D *)infile_sig->Get("cutflow");
 TH1D *cutflow_sig_h = (TH1D *)infile_sig_h->Get("cutflow");
 TH1D *cutflow_ZZ = (TH1D *)infile_ZZ->Get("cutflow");
 TH1D *cutflow_WZ = (TH1D *)infile_WZ->Get("cutflow");
 TH1D *cutflow_tWZ = (TH1D *)infile_tWZ->Get("cutflow");
 TH1D *cutflow_h = (TH1D *)infile_h->Get("cutflow");
 TH1D *cutflow_ttZ = (TH1D *)infile_ttZ->Get("cutflow");
 TH1D *cutflow_stt = (TH1D *)infile_stt->Get("cutflow");
 TH1D *cutflow_others = (TH1D *)infile_others->Get("cutflow");
 
 const char* cutName[50];
 cout.setf(ios::left);
 cout.width(30);
 cout<<"cut";
 cout.width(10);
 cout<<"signal";
 cout.width(10);
 cout<<"signal_h";
 cout.width(10);
 cout<<"ZZ";
 cout.width(10);
 cout<<"WZ";
 cout.width(10);
 cout<<"tWZ";
 cout.width(10);
 cout<<"h";
 cout.width(10);
 cout<<"ttZ";
 cout.width(10);
 cout<<"stt";
 cout.width(10);
 cout<<"others";
 cout.width(10);
 cout<<"s/sqrt(b)"<<endl;

 double signum=0, bkgnum=0;

 for (int ibin=0; ibin<cutflow_sig->GetXaxis()->GetNbins(); ibin++)
  {
   signum = cutflow_sig->GetBinContent(ibin+1) + cutflow_sig_h->GetBinContent(ibin+1);
   bkgnum = cutflow_ZZ->GetBinContent(ibin+1) + cutflow_WZ->GetBinContent(ibin+1) + cutflow_tWZ->GetBinContent(ibin+1) + cutflow_h->GetBinContent(ibin+1)
          + cutflow_ttZ->GetBinContent(ibin+1) + cutflow_stt->GetBinContent(ibin+1) + cutflow_others->GetBinContent(ibin+1);
   *cutName = cutflow_sig->GetXaxis()->GetBinLabel(ibin+1);
   cout.width(30);
   cout<<*cutName;
   cout.width(10);
   cout<<cutflow_sig->GetBinContent(ibin+1);
   cout.width(10);
   cout<<cutflow_sig_h->GetBinContent(ibin+1);
   cout.width(10);
   cout<<cutflow_ZZ->GetBinContent(ibin+1);
   cout.width(10);
   cout<<cutflow_WZ->GetBinContent(ibin+1);
   cout.width(10);
   cout<<cutflow_tWZ->GetBinContent(ibin+1);
   cout.width(10);
   cout<<cutflow_h->GetBinContent(ibin+1);
   cout.width(10);
   cout<<cutflow_ttZ->GetBinContent(ibin+1);
   cout.width(10);
   cout<<cutflow_stt->GetBinContent(ibin+1);
   cout.width(10);
   cout<<cutflow_others->GetBinContent(ibin+1);
   cout.width(10);
   cout<<signum/sqrt(bkgnum)<<endl;
  }
}
