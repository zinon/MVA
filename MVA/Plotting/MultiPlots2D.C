

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

#include "TROOT.h"
#include "TString.h"
#include "TSystem.h"
#include "TStyle.h"
#include "TH2D.h"
#include "TCut.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TLegend.h"
#include "TColor.h"
#include "TGaxis.h"
#include "TGraphAsymmErrors.h"
#include "TMath.h"
#include "TBox.h"
#include "TLatex.h"
#include "TProfile.h"
#include "TColor.h"

#include "HelperClass.h"
#include "MonteCarloBank.h"


void MultiPlots2D(TString category, TString variable1, TString variable2, TString counter);
void CheckNegativeBinContent(TH2D *h, const string &s);

void MultiPlots2D(TString category_tstr, TString variable1_tstr, TString variable2_tstr, TString counter_tstr){
  
  /// To do :
  /// update track fit norms with weights
  /// plot BDT
  
  const char *category_c 	= category_tstr.Data();
  const char *variable1_c = variable1_tstr.Data();
  const char *variable2_c = variable2_tstr.Data();
  const char *counter_c	= counter_tstr.Data();
  
  string category(category_c);
  string variable1(variable1_c);
  string variable2(variable2_c);
  string counter(counter_c);
  cout<<"Plotting variables '"<<variable1<<" Vs "<<variable2<<"' in category '"<<category<<"' ("<<counter<<")"<<endl;
  bool PlotTrackFit = true;
  string  category_file ; ///for reading from the BDT files
  if(category == "Preselection")
    category_file = "vbf";
  else
    category_file = category_c;
  
  ///external classes
  gSystem->Load("../../HelperClass/HelperClass_cpp.so");
  gSystem->Load("../../MonteCarloBank/MonteCarloBank_cpp.so");
  
  HelperClass hc;
  MonteCarloBank mcbank;
  
  
  /// some variables
  bool 	kLogZ; 
  string xTitle; string yTitle;
  int nbins1; double firstbin1, lastbin1; 
  int nbins2; double firstbin2, lastbin2; 
  double 	QCD_TrackFitFactor_nominal, Z_TrackFitFactor_nominal; 
  
  string 	fillcolor; int xNdivisions(0);
  string NormMethod("");
  
  double TrackFit_f_QCD, TrackFit_sf_QCD , TrackFit_sf13_QCD;
  double TrackFit_f_TAU, TrackFit_sf_TAU , TrackFit_sf13_TAU;
  
  /// category settings
  if(category == "vbf"){
	
	//v12 production
	//QCD_TrackFitFactor_nominal = 0.262317;  Z_TrackFitFactor_nominal = 0.261899; NormMethod="TrkFit"; ///normal (CR_UpperMassCut)
	//QCD_TrackFitFactor_nominal = 0.462345;  Z_TrackFitFactor_nominal = 0.036822; NormMethod="TrkFit"; // QCD-rich
	
	///v13
	//QCD_TrackFitFactor_nominal = 0.253793;  Z_TrackFitFactor_nominal = 0.291376;NormMethod="TrkFitNoMassCut";
	QCD_TrackFitFactor_nominal = 0.261082;  Z_TrackFitFactor_nominal = 0.284419; NormMethod="TrkFitUpperMassCut";
	
  }else if(category == "boosted"){
	
	//v12 production
	//QCD_TrackFitFactor_nominal = 0.262069;  Z_TrackFitFactor_nominal = 0.332742; NormMethod="TrkFit"; //normal (CR_UpperMassCut)
	//	  QCD_TrackFitFactor_nominal = 0.256712;  Z_TrackFitFactor_nominal = 0.324542;// no mass cut
	//	  QCD_TrackFitFactor_nominal = 0.470762;  Z_TrackFitFactor_nominal = 0.017898; NormMethod="TrkFit"; // QCD-rich
	
	///v13
	//QCD_TrackFitFactor_nominal = 0.188677;  Z_TrackFitFactor_nominal = 0.497606; NormMethod="TrkFitNoMassCut";
	QCD_TrackFitFactor_nominal = 0.19705;  Z_TrackFitFactor_nominal = 0.521256; NormMethod="TrkFitUpperMassCut";
	
  }else if( category == "1jet"){
	
	//v12 production
	//QCD_TrackFitFactor_nominal = 0.286683;  Z_TrackFitFactor_nominal = 0.287435; NormMethod="TrkFit";  //normal (CR_UpperMassCut)	
	//QCD_TrackFitFactor_nominal = 0.477353;  Z_TrackFitFactor_nominal = 0.0472635; NormMethod="TrkFit"; // QCD-rich
	
	///v13
	//QCD_TrackFitFactor_nominal = 0.288988;  Z_TrackFitFactor_nominal = 0.301052; NormMethod="TrkFitNoMassCut";
	QCD_TrackFitFactor_nominal = 0.289277;  Z_TrackFitFactor_nominal = 0.29546; NormMethod="TrkFitUpperMassCut";
	
  }else if( category == "0jet"){
	
	//v12 production
	//QCD_TrackFitFactor_nominal = 0.351096;  Z_TrackFitFactor_nominal = 0.200306; NormMethod="TrkFit";  //normal (CR_UpperMassCut)
	//QCD_TrackFitFactor_nominal = 0.453864;  Z_TrackFitFactor_nominal = 0.0974771; NormMethod="TrkFit"; // QCD-rich
	
	///v13
	//QCD_TrackFitFactor_nominal = 0.41449;  Z_TrackFitFactor_nominal = 0.13964; NormMethod="TrkFitNoMassCut";
	QCD_TrackFitFactor_nominal = 0.373924;  Z_TrackFitFactor_nominal = 0.161097; NormMethod="TrkFitUpperMassCut";
	
  }else if( category == "preselection"){
	
	///v12 
	//QCD_TrackFitFactor_nominal = 0.242913;  Z_TrackFitFactor_nominal = 0.352185;  NormMethod="TrkFit";  // MassSideBands
	//QCD_TrackFitFactor_nominal = 0.254399;  Z_TrackFitFactor_nominal = 0.331562;  NormMethod="TrkFit";  // mmc<100	
	///v12 - QCD-rich : reverted dEta
	//QCD_TrackFitFactor_nominal = 0.483114;  Z_TrackFitFactor_nominal = 0.0763533; NormMethod="TrkFit"; // met>0, no MET_bisect
	//QCD_TrackFitFactor_nominal = 0.455173;  Z_TrackFitFactor_nominal = 0.106133;  NormMethod="TrkFit";//met >20, no MET_bisect
	//QCD_TrackFitFactor_nominal = 0.447674;  Z_TrackFitFactor_nominal = 0.0621809;  NormMethod="TrkFit";//met >20,  MET_bisect
	//QCD_TrackFitFactor_nominal = 0.434523;  Z_TrackFitFactor_nominal = 0.041682;NormMethod="TrkFit";  //met >20,  MET_bisect, anti-id, no Wqq
	//QCD_TrackFitFactor_nominal = 0.478832;  Z_TrackFitFactor_nominal = 0.04491; NormMethod="TrkFit";//met >20,  MET_bisect, no Wqq
	
	///v13
	//QCD_TrackFitFactor_nominal = 0.272113;  Z_TrackFitFactor_nominal = 0.332463; NormMethod="TrkFitNoMassCut";
	QCD_TrackFitFactor_nominal = 0.261859;  Z_TrackFitFactor_nominal = 0.347731; NormMethod="TrkFitUpperMassCut";
	
  }else{
	cout<<"\nMultiPlots - Choose a proper category. Exiting ..."<<endl;
	exit(0);
  }
  
  
  ///y-axis range
  bool kAutoMaxYaxis = true;
  double AutoOffsetTimes = 1.10;
  
  ///profile variable bins
  bool kBin1 = false; 
  vector<double> v1;
  
  ///variables and histo setup ====================================================================
  
  ///MMC mass
  if(variable1 == "ditau_mass_mmc"){ xTitle = "m^{MMC}_{#tau#tau} [GeV]";	firstbin1 = 20; lastbin1 = 220; nbins1 = 25; }
  if(variable2 == "ditau_mass_mmc"){ yTitle = "m^{MMC}_{#tau#tau} [GeV]"; firstbin2 = 20; lastbin2 = 220; nbins2 = 25; }
  if(variable1 == "ditau_mass_mmc"){
	double tmpArr[] = {20, 28, 36, 44, 52, 60, 68, 76, 84, 92, 100, 108, 116, 124, 132, 140, 148, 156, 164, 172, 190, 220}; 
	vector<double> tmpVec (tmpArr, tmpArr + sizeof(tmpArr) / sizeof(double) ); v1 = tmpVec; kBin1 = true;
  }
  
  ///ditau dR
  if(variable1 == "ditau_dR"){ xTitle = "#DeltaR_{#tau#tau}"; firstbin1 = 0.; lastbin1 = 3.2; nbins1 = 32; }
  if(variable2 == "ditau_dR"){ yTitle = "#DeltaR_{#tau#tau}"; firstbin2 = 0.; lastbin2 = 3.2; nbins2 = 32; }
  if(variable1 == "ditau_dR"){
	double tmpArr[] = {0, 0.8, 1, 1.2, 1.4, 1.6, 2, 2.5, 3.2}; 
	vector<double> tmpVec (tmpArr, tmpArr + sizeof(tmpArr) / sizeof(double) ); v1 = tmpVec; kBin1 = true;
}

  ///met_centrality
  if(variable1 == "met_centrality"){ xTitle = "MET Centrality"; firstbin1 = -1.5; lastbin1 = 1.5; nbins1 = 30; }
  if(variable2 == "met_centrality"){ yTitle = "MET Centrality"; firstbin2 = -1.5; lastbin2 = 1.5; nbins2 = 30; }
  if(variable1 == "met_centrality"){
	double tmpArr[] = {-1.5, -1, -0.5, 0.5, 0.75, 1, 1.2, 1.3, 1.4, 1.5}; 
	vector<double> tmpVec (tmpArr, tmpArr + sizeof(tmpArr) / sizeof(double) ); v1 = tmpVec; kBin1 = true;
  }
  
  ///dijet eta
 if(variable1 == "dijet_dEta"){ xTitle = "di-jet #Delta#eta"; firstbin1 = 2; lastbin1 = 9; nbins1 = 35; }
 if(variable2 == "dijet_dEta"){ yTitle = "di-jet #Delta#eta"; firstbin2 = 2; lastbin2 = 9; nbins2 = 35; }
 if(variable1 == "dijet_dEta"){
   double tmpArr[] = {2,2.2,2.4,2.6,2.8,3,3.2,3.4,3.6,3.8,4,4.2,4.5, 5, 6, 9}; 
   vector<double> tmpVec (tmpArr, tmpArr + sizeof(tmpArr) / sizeof(double) ); v1 = tmpVec; kBin1 = true;
 }
 
 /// pt1/pt2
 if(variable1 == "ditau_pT_0_over_pT_1"){ xTitle = "pT^{1st}_{#tau}/pT^{2nd}_{#tau}"; firstbin1 = 1; lastbin1 = 5; nbins1 = 20; }
 if(variable2 == "ditau_pT_0_over_pT_1"){ yTitle = "pT^{1st}_{#tau}/pT^{2nd}_{#tau}"; firstbin2 = 1; lastbin2 = 5; nbins2 = 20; }
 if(variable1 == "ditau_pT_0_over_pT_1"){
   double tmpArr[] = {1, 1.1, 1.2, 1.4, 1.6, 1.8, 2, 2.2, 2.4, 2.6, 2.8, 3, 3.5, 4., 5.}; 
   vector<double> tmpVec (tmpArr, tmpArr + sizeof(tmpArr) / sizeof(double) ); v1 = tmpVec; kBin1 = true;
 }
 
 /// ht taus + jets
 if(variable1 == "HT_jets_taus"){ xTitle = "H_{T}(di-#tau, jets, #slash{E}_{T}) [GeV]"; firstbin1 = 80; lastbin1 = 560; nbins1 = 24; }
 if(variable2 == "HT_jets_taus"){ yTitle = "H_{T}(di-#tau, jets, #slash{E}_{T}) [GeV]"; firstbin2 = 80; lastbin2 = 560; nbins2 = 24; }
 if(variable1 == "HT_jets_taus"){
   double tmpArr[] = {80,100,120,140,160,180,200,220,240,260,280,300,320,340,360,400,460,560}; 
   vector<double> tmpVec (tmpArr, tmpArr + sizeof(tmpArr) / sizeof(double) ); v1 = tmpVec; kBin1 = true;
 }
 
 /// mmc x0
 if(variable1 == "MMC_resonance_x0"){ xTitle = "MMC #tau^{1st} visible fraction x"; firstbin1 = 0.; lastbin1 = 1.; nbins1 = 20; }
 if(variable2 == "MMC_resonance_x0"){ yTitle = "MMC #tau^{1st} visible fraction x"; firstbin2 = 0.; lastbin2 = 1.; nbins2 = 20; }
 
 /// mmc x1
 if(variable1 == "MMC_resonance_x1"){ xTitle = "MMC #tau^{2nd} visible fraction x"; firstbin1 = 0.; lastbin1 = 1.; nbins1 = 20; }
 if(variable2 == "MMC_resonance_x1"){ yTitle = "MMC #tau^{2nd} visible fraction x"; firstbin2 = 0.; lastbin2 = 1.; nbins2 = 20; }
 if(variable1 == "MMC_resonance_x0" || variable1 == "MMC_resonance_x1" ){
   double tmpArr[] = {0,0.2,0.25,0.3,0.35,0.4,0.45,0.5,0.55,0.6,0.65,0.7,0.75,0.8,0.9,1}; 
   vector<double> tmpVec (tmpArr, tmpArr + sizeof(tmpArr) / sizeof(double) ); v1 = tmpVec; kBin1 = true;
 }
 
 ///dijet mass
 if(variable1 == "dijet_mass"){ xTitle = "di-jet mass [GeV]"; firstbin1 = 20; lastbin1 = 860; nbins1 = 42; }
 if(variable2 == "dijet_mass"){ yTitle = "di-jet mass [GeV]"; firstbin2 = 20; lastbin2 = 860; nbins2 = 42; }
 if(variable1 == "dijet_mass"){
   double tmpArr[] = {20,40,60,80,100,120,140,160,180,200,220,240,260,280,300,320,340,360,380,400,450,500,600,700,860}; 
   vector<double> tmpVec (tmpArr, tmpArr + sizeof(tmpArr) / sizeof(double) ); v1 = tmpVec; kBin1 = true;
 }
 
 ///dijet eta1 x eta2
 if(variable1 == "dijet_eta1_x_eta2"){ xTitle = "di-jet #eta_{1} #times #eta_{2}"; firstbin1 = -10; lastbin1 = 10; nbins1 = 40; }
 if(variable2 == "dijet_eta1_x_eta2"){ yTitle = "di-jet #eta_{1} #times #eta_{2}"; firstbin2 = -10; lastbin2 = 10; nbins2 = 40; }
 if(variable1 == "dijet_eta1_x_eta2"){
   double tmpArr[] = {-10,-8,-7,-6,-5.5,-5,-4.5,-4,-3.5,-3,-2.5,-2,-1.5,-1,-0.5,0,0.5,1,1.5,2,2.5,3,3.5,4,4.5,5,5.5,6,7,8,10}; 
   vector<double> tmpVec (tmpArr, tmpArr + sizeof(tmpArr) / sizeof(double) ); v1 = tmpVec; kBin1 = true;
 }
 
 /// tau 0 centrality
 if(variable1 == "tau_0_dijet_eta_centr"){ xTitle = "leading #tau centrality"; firstbin1 = 0; lastbin1 = 1; nbins1 = 20; }
 if(variable2 == "tau_0_dijet_eta_centr"){ yTitle = "leading #tau centrality"; firstbin2 = 0; lastbin2 = 1; nbins2 = 20; }
 
 /// tau 0 centrality
 if(variable1 == "tau_1_dijet_eta_centr"){ xTitle = "subleading #tau centrality"; firstbin1 = 0; lastbin1 = 1; nbins1 = 20; }
 if(variable2 == "tau_1_dijet_eta_centr"){ yTitle = "subleading #tau centrality"; firstbin2 = 0; lastbin2 = 1; nbins2 = 20; }
 

 /// tau tracks
 if(variable1 == "tau_0_tracks_recounted"){ xTitle = "leading #tau recounted tracks"; firstbin1 = 0; lastbin1 = 20; nbins1 = 20; }
 if(variable2 == "tau_0_tracks_recounted"){ yTitle = "leading #tau recounted tracks"; firstbin2 = 0; lastbin2 = 20; nbins2 = 20; }

 if(variable1 == "tau_1_tracks_recounted"){ xTitle = "subleading #tau recounted tracks"; firstbin1 = 0; lastbin1 = 20; nbins1 = 20; }
 if(variable2 == "tau_1_tracks_recounted"){ yTitle = "subleading #tau recounted tracks"; firstbin2 = 0; lastbin2 = 20; nbins2 = 20; }

 ///BDT_Weight
 if(variable1 == "BDT_Weight"){ xTitle = "BDT_Weight"; firstbin1 = 0; lastbin1 = 100; nbins1 = 100; }
 if(variable2 == "BDT_Weight"){ yTitle = "BDT_Weight"; firstbin2 = 0; lastbin2 = 100; nbins2 = 100; }
 //   double tmpArr[] = {-10,-8,-7,-6,-5.5,-5,-4.5,-4,-3.5,-3,-2.5,-2,-1.5,-1,-0.5,0,0.5,1,1.5,2,2.5,3,3.5,4,4.5,5,5.5,6,7,8,10}; 
 //   vector<double> tmpVec (tmpArr, tmpArr + sizeof(tmpArr) / sizeof(double) ); v1 = tmpVec; kBin1 = true;


 ///
 
 //	if(variable1 == "ditau_dijet_met_VecSumPt"){ xTitle = "#left|#bf{p}_{T}(ditau, dijet, MET)#right|[GeV]"; firstbin1 = 0; lastbin1 = 200; nbins1 = 20; }
 //	if(variable2 == "ditau_dijet_met_VecSumPt"){ yTitle = "#left|#bf{p}_{T}(ditau, dijet, MET)#right|[GeV]"; firstbin2 = 0; lastbin2 = 200; nbins2 = 20; }
 //	if(variable1 == "ditau_dijet_met_VecSumPt"){
 //	  double tmpArr[] = {0,10,20,30,40,50,60,70,80,100,125,150,200}; 
 //		vector<double> tmpVec (tmpArr, tmpArr + sizeof(tmpArr) / sizeof(double) ); v1 = tmpVec; kBin1 = true;
 //	}
 ///
 if(variable1 == "ditau_dijet_met_VecSumPt"){ xTitle = "#left|#bf{p}_{T}(ditau, dijet, MET)#right|[GeV]"; firstbin1 = 0; lastbin1 = 150; nbins1 = 15; }
 if(variable2 == "ditau_dijet_met_VecSumPt"){ yTitle = "#left|#bf{p}_{T}(ditau, dijet, MET)#right|[GeV]"; firstbin2 = 0; lastbin2 = 150; nbins2 = 15; }
 if(variable1 == "ditau_dijet_met_VecSumPt"){
   double tmpArr[] = {0,10,20,30,40,50,60,70,80,100,125,150}; 
   vector<double> tmpVec (tmpArr, tmpArr + sizeof(tmpArr) / sizeof(double) ); v1 = tmpVec; kBin1 = true;
 }
 
 if(variable1 == "ditau_met_VecSumPt"){ xTitle = "#left|#bf{p}_{T}(ditau, MET)#right|[GeV]"; firstbin1 = 0; lastbin1 = 200; nbins1 = 20; }
 if(variable2 == "ditau_met_VecSumPt"){ yTitle = "#left|#bf{p}_{T}(ditau, MET)#right|[GeV]"; firstbin2 = 0; lastbin2 = 200; nbins2 = 20; }
 if(variable1 == "ditau_met_VecSumPt"){
   double tmpArr[] = {0,10,20,30,40,50,60,70,80,100,125,150,200}; 
   vector<double> tmpVec (tmpArr, tmpArr + sizeof(tmpArr) / sizeof(double) ); v1 = tmpVec; kBin1 = true;
 }
 
 
 ///
 if(variable1 == "ditau_dEta"){ xTitle = "#Delta#eta_{#tau#tau}"; firstbin1 = 0; lastbin1 = 1.5; nbins1 = 15; }
 if(variable2 == "ditau_dEta"){ yTitle = "#Delta#eta_{#tau#tau}"; firstbin2 = 0; lastbin2 = 1.5; nbins2 = 15; }
 
 ///
 if(variable1 == "met_et"){ xTitle = "#slash{E}_{T} [GeV]"; firstbin1 = 20; lastbin1 = 150; nbins1 = 26; }
 if(variable2 == "met_et"){ yTitle = "#slash{E}_{T} [GeV]"; firstbin2 = 20; lastbin2 = 150; nbins2 = 26; }
 
 ///
 if(variable1 == "MMC_met_et"){ xTitle = "MMC #slash{E}_{T} [GeV]"; firstbin1 = 20; lastbin1 = 150; nbins1 = 26; }
 if(variable2 == "MMC_met_et"){ yTitle = "MMC #slash{E}_{T} [GeV]"; firstbin2 = 20; lastbin2 = 150; nbins2 = 26; }
 
 if(variable1 == "met_et" || variable1 == "MMC_met_et" ){
   double tmpArr[] = {20,25,30,35,40,45,50,55,60,65,70,75,80,90,100,125,150,200}; 
   vector<double> tmpVec (tmpArr, tmpArr + sizeof(tmpArr) / sizeof(double) ); v1 = tmpVec; kBin1 = true;
 }
 
 ///
 if(variable1 == "tau_0_BDT_score"){ xTitle = "leading #tau ID BDT score"; firstbin1 = 0; lastbin1 = 1; nbins1 = 25; }
 if(variable2 == "tau_0_BDT_score"){ yTitle = "leading #tau ID BDT score"; firstbin2 = 0; lastbin2 = 1; nbins2 = 25; }
 
 ///
 if(variable1 == "tau_1_BDT_score"){ xTitle = "subleading #tau ID BDT score"; firstbin1 = 0; lastbin1 = 1; nbins1 = 25; }
 if(variable2 == "tau_1_BDT_score"){ yTitle = "subleading #tau ID BDT score"; firstbin2 = 0; lastbin2 = 1; nbins2 = 25; }
 
 ///
 if(variable1 == "ditau_cosTheta"){ xTitle = "cos#alpha_{#tau#tau}"; firstbin1 = -1.05; lastbin1 = 1.05; nbins1 = 11; }
 if(variable2 == "ditau_cosTheta"){ yTitle = "cos#alpha_{#tau#tau}"; firstbin2 = -1.05; lastbin2 = 1.05; nbins2 = 11; }
 
 
 ///ditau_colapprox_x0
 if(variable1 == "ditau_colapprox_x0"){ xTitle = "Collinear Approx x_{0}"; firstbin1 = -5.; lastbin1 = 5.; nbins1 = 25; }
 if(variable2 == "ditau_colapprox_x0"){ yTitle = "Collinear Approx x_{0}"; firstbin2 = -5.; lastbin2 = 5.; nbins2 = 25; }
 
 ///ditau_colapprox_x1
 if(variable1 == "ditau_colapprox_x1"){ xTitle = "Collinear Approx x_{1}"; firstbin1 = -5.; lastbin1 = 5.; nbins1 = 25; }
 if(variable2 == "ditau_colapprox_x1"){ yTitle = "Collinear Approx x_{1}"; firstbin2 = -5.; lastbin2 = 5.; nbins2 = 25; }
 
 
 ///
 if(variable1 == "esv_all_objects_sphericity"){ xTitle = "Event Shape Sphericity"; firstbin1 = 0; lastbin1 = 1; nbins1 = 20; }
 if(variable2 == "esv_all_objects_sphericity"){ yTitle = "Event Shape Sphericity"; firstbin2 = 0; lastbin2 = 1; nbins2 = 20; }
 if(variable1 == "esv_all_objects_sphericity"){
   double tmpArr[] = {0,0.05,0.1,0.15,0.2,0.25,0.3,0.35,0.4,0.45,0.5,0.55,0.6,0.65,0.7,0.8,1}; 
   vector<double> tmpVec (tmpArr, tmpArr + sizeof(tmpArr) / sizeof(double) ); v1 = tmpVec; kBin1 = true;
 }
 
 ///
 if(variable1 == "MMC_resonance_pt"){ xTitle = "MMC resonance p_{T} [GeV]"; firstbin1 = 0; lastbin1 = 350; nbins1 = 35; }
 if(variable2 == "MMC_resonance_pt"){ yTitle = "MMC resonance p_{T} [GeV]"; firstbin2 = 0; lastbin2 = 350; nbins2 = 35; }
 if(variable1 == "MMC_resonance_pt"){
   double tmpArr[] = {0,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200,250,350}; 
   vector<double> tmpVec (tmpArr, tmpArr + sizeof(tmpArr) / sizeof(double) ); v1 = tmpVec; kBin1 = true;
 }
 
 ///
 //if(variable1 == ""){ xTitle = ""; firstbin1 = ; lastbin1 = ; nbins1 = ; }
 //if(variable2 == ""){ yTitle = ""; firstbin2 = ; lastbin2 = ; nbins2 = ; }
 
 
 const int n1 = v1.size();
 double *Array1 = &v1[0];
 
 ///more specific drawing options - configuration ==============================================
 
 bool 	kWqq_special_treatment = true;
 bool	kEWK_subtraction 	= true;
 bool	kZtautau_subtraction= true;
 bool	kShow_StatSystBandsCombined = true;
 bool	kShowDataMCRatio_StatSystBandsCombined = false;
 bool	kShowDataMCRatio_StatSystBandsDecoupled = true;
 bool	kShow_RatioLines	= false;
 bool	ApplyEventWeights	= true;
 int		SignalZoom 			=  10;
 string 	classifier 			= "BDT";
 string 	QCDmodel 			= "SS";// notOS SS;
 string 	version 			= "v16";
 string		region 				= "CR_NoMassCut";// CR_dEta CR_QCDrich  CR_preselection  CR_MassSideBands
 string 	Zmodel				= "MC";
 // string		purpose 			= "Plot";
 string		purpose 			= "TrackFit";
 int 		Hmass 				= 125;
 string 	plots_subdir 		= "July18";
 bool 	kShowSignalAlone 	= true;
 bool 	kShowSpectrumWithist_Signal = false;
 bool kUseMergedData = false; // true: use one merged root file and save memory.  This is not supported for plotting BDT_Weight yet   

string  tag                                     = "test"; // vbf_boosted MMCOver60_QCDnotOS     

 bool	kProducePDF					= false;
 bool	kProducePNG					= true;
 bool	kProduceEPS					= false;
 bool	kProducePS					= false;
 
 double 	RatioMinY			= 0.55; 
 double 	RatioMaxY 			= 1.45; 
 bool 	ShowHorizontalErrorBarsInRatioPlot = false;	
 string HistoFitMethod 		= "TrackFit"; // TrackFit  dEtaFit
 
 bool kPrintEmptyHistos = false;
 
 bool kEmbedding = false; // if false then Z is from alpgen mc
 string Zsample = kEmbedding ? "Embedding" : "MC";
 
 string QCD_model_legend = QCDmodel;
 string Z_model_legend = Zmodel;
 
 ///propagating decisions 
 bool	kShowData = (region == "SR_MassWindow" && (variable1 == "ditau_mass_mmc" || variable2 == "ditau_mass_mmc") ) ? false : true; 
 string 	hmass 				= hc.GetStringFromInt(Hmass);
 string  filenamecore		= "plots/"+plots_subdir+"/plot_"+counter+"_"+variable1+"_Vs_"+variable2+"_"+category+"_H_"+hmass+"_Z_"+Zsample+"_"+region+"_QCD_"+QCDmodel+"_"+NormMethod+"_"+version;
 string 	fn 					= filenamecore+".root";
 string 	fn_pdf 				= filenamecore+".pdf";
 string 	fn_png 				= filenamecore+".png";
 string 	fn_eps 				= filenamecore+".eps";
 string 	fn_ps 				= filenamecore+".ps";
 
 ///how to obtain ntuples
 hc.SetTreeName("mva"); 
 hc.SetVersion(version); 
 // hc.SetPath("../../TreeMaker");//Z
 hc.SetPath("../../Ntuples");//K
 
 ///list of MC samples
 vector<int> RunsVector = hc.GetRunsVector(Hmass);
 
 ///data tree
 cout<<"\ncreating tree map for data"<<endl;
 // TTree *tData = hc.GetTreeData( );
 
 
 double DataLumi (0);
 TTree *tData;
 
 if(variable1 == "BDT_Weight" || variable2 == "BDT_Weight"){
   //  TTree *tData = hc.GetTreeDataMVA( "*", classifier, category_file, hmass, tag);//katy get data from mva ntuples
   tData = hc.GetTreeDataMVA( "*", classifier, category_file, hmass, tag);//katy get data from mva ntuples 
 }else{
   if(kUseMergedData){
     tData = hc.GetTreeDataMerged( );
     DataLumi = 2.01113e7;//nb-1
   }else{
     tData = hc.GetTreeData( );
     DataLumi = hc.GetRunsListTotalLumi("inb");
   }
 }
 
 hc.SetLumiPerRunMap();
 
 int nDataEntries = tData->GetEntries();
 if(!nDataEntries) {cout<<"unable to get data tree entries. Exiting... "<<endl; }
 
 ///lumi calculation run-per-run ==============================================================================
 // double DataLumi = hc.GetRunsListTotalLumi("inb");
 cout<<"\nData lumi "<<DataLumi<<" nb-1"<<endl<<endl;
 double lumi_fb = DataLumi/1e6;
 char lumi_number[24];
 sprintf(lumi_number, "%.2f", lumi_fb);
 string lumi_str = lumi_number;
 
 ///embedding Z tau tau sample =================================================================================
 TTree *tEmbedding;
// if(kEmbedding){
//   cout<<"\ncreating tree map for embedding"<<endl;
//   tEmbedding = hc.GetTreeEmbedding( );
//   cout<<"embedding entries  "<<tEmbedding->GetEntries()<<endl;
// }
 
 /// mc tree map ==============================================================================================
 map<int, TTree *> tmap;
 cout<<"\ncreating tree map for mc ..."<<endl;
 //for(vector<int>::iterator it=RunsVector.begin(); it != RunsVector.end(); it++){
 //  if( *it >= 800000) continue;
 //  tmap.insert ( pair<int, TTree *>(*it,  hc.GetTreeMC(hc.GetStringFromInt(*it)) ) );
 //  
 //}
 
 for(vector<int>::iterator it=RunsVector.begin(); it != RunsVector.end(); it++){
   if( *it >= 800000) continue;
   
   if(variable1 == "BDT_Weight" || variable2 == "BDT_Weight"){
     tmap.insert ( pair<int, TTree *>(*it,  hc.GetTreeMCMVA( hc.GetStringFromInt(*it), classifier, category_file, hmass, tag) ) );//katy     
   }else{
     tmap.insert ( pair<int, TTree *>(*it,  hc.GetTreeMC(hc.GetStringFromInt(*it)) ) );
     
//     if(kSyst_JESup)       tmap_JESup.insert (     pair<int, TTree *>(*it,  hc.GetTreeMC(hc.GetStringFromInt(*it), "JESup") ) );
//     if(kSyst_JESdown) tmap_JESdown.insert (       pair<int, TTree *>(*it,  hc.GetTreeMC(hc.GetStringFromInt(*it), "JESdown") ) );
//     if(kSyst_TESup)       tmap_TESup.insert (     pair<int, TTree *>(*it,  hc.GetTreeMC(hc.GetStringFromInt(*it), "TESup") ) );
//     if(kSyst_TESdown) tmap_TESdown.insert (       pair<int, TTree *>(*it,  hc.GetTreeMC(hc.GetStringFromInt(*it), "TESdown") ) );
   }
   
 }
 cout<<"  MC trees "<<tmap.size()<<endl;
// if(kSyst_JESup)         cout<<"  MC tree size JEsup "<<tmap_JESup.size()<<endl;
// if(kSyst_JESdown)       cout<<"  MC tree size JESdown "<<tmap_JESdown.size()<<endl;
// if(kSyst_TESup)         cout<<"  MC tree sise TESup "<<tmap_TESup.size()<<endl;
// if(kSyst_TESdown)       cout<<"  MC tree size TESdown "<<tmap_TESdown.size()<<endl;
 
 
 ///histogramming ===========================================================================================
 cout<<"\nbooking histograms ..."<<endl;
 double BinW1 = (lastbin1 - firstbin1)/nbins1;
 double BinW2 = (lastbin2 - firstbin2)/nbins2;
 
 cout<<"Variable 1 = "<<variable1<<endl;
 cout<<"  bin width : "<<BinW1<<endl;
 cout<<"  limits  : "<<firstbin1<<"  "<<lastbin1<<endl;
 
 cout<<"Variable 2 = "<<variable2<<endl;
 cout<<"  bin width : "<<BinW2<<endl;
 cout<<"  limits  : "<<firstbin2<<"  "<<lastbin2<<endl;
 
 //data - systematics-independent 
 TH2D *hist_Data 		= new TH2D("hist_Data",	"",			nbins1, firstbin1, lastbin1, nbins2, firstbin2, lastbin2);
 TH2D *hist_Data_HistoFit= new TH2D("hist_Data_HistoFit","",	nbins1, firstbin1, lastbin1, nbins2, firstbin2, lastbin2);
 
 //nominal
 TH2D *hist_QCD			= new TH2D("hist_QCD",	"",			nbins1, firstbin1, lastbin1, nbins2, firstbin2, lastbin2);
 TH2D *hist_Signal 		= new TH2D("hist_Signal","",		nbins1, firstbin1, lastbin1, nbins2, firstbin2, lastbin2);
 TH2D *hist_Spectrum0 	= new TH2D("hist_Spectrum0","",		nbins1, firstbin1, lastbin1, nbins2, firstbin2, lastbin2);
 TH2D *hist_Spectrum1 	= new TH2D("hist_Spectrum1","",		nbins1, firstbin1, lastbin1, nbins2, firstbin2, lastbin2);
 TH2D *hist_Spectrum2 	= new TH2D("hist_Spectrum2","",		nbins1, firstbin1, lastbin1, nbins2, firstbin2, lastbin2);
 TH2D *hist_Spectrum3 	= new TH2D("hist_Spectrum3","",		nbins1, firstbin1, lastbin1, nbins2, firstbin2, lastbin2);
 TH2D *hist_BKG 		= new TH2D("hist_BKG",	"",			nbins1, firstbin1, lastbin1, nbins2, firstbin2, lastbin2);
 TH2D *hist_Z_Emb		= new TH2D("hist_Z_Emb",	"",		nbins1, firstbin1, lastbin1, nbins2, firstbin2, lastbin2);
 TH2D *hist_Z_Emb_subtr = new TH2D("hist_Z_Emb_subtr",	"",	nbins1, firstbin1, lastbin1, nbins2, firstbin2, lastbin2);
 TH2D *hist_Z 			= new TH2D("hist_Z",	"",			nbins1, firstbin1, lastbin1, nbins2, firstbin2, lastbin2);
 TH2D *hist_Z_subtr 	= new TH2D("hist_Z_subtr",	"",		nbins1, firstbin1, lastbin1, nbins2, firstbin2, lastbin2);
 
 //histo maps
 map<int, TH2D *> hmap_Sig;
 map<int, TH2D *> hmap_Bkg;
 
 //fill maps with empty histograms for each sample
 for(vector<int>::iterator it=RunsVector.begin(); it != RunsVector.end(); it++){
   hmap_Sig.insert ( pair<int,TH2D *>(*it, new  TH2D("",	"",	nbins1, firstbin1, lastbin1, nbins2, firstbin2, lastbin2)) );
   hmap_Bkg.insert ( pair<int,TH2D *>(*it, new  TH2D("",	"",	nbins1, firstbin1, lastbin1, nbins2, firstbin2, lastbin2)) );
   
 }
 
 
 /// name histos===========================================================================================
 TCut hweight("");
 if (ApplyEventWeights){
   hweight = "event_weight";
   cout<<"\nincluding event weights : "<<hweight<<endl;
 }
 
 cout<<"\nrenaming plots ..."<<endl;
 hc.SetHistoNames2D(hmap_Sig, "OS");
 hc.SetHistoNames2D(hmap_Bkg, QCDmodel);
 
 
 ///plot making=============================================================================================
 cout<<"\nCuts for search region : \n"<< hweight * hc.GetCut(category, "OS", purpose,region).GetTitle()<<endl;
 cout<<"\nCuts for QCD bkg : \n"<< hc.GetCut(category, QCDmodel, purpose,region).GetTitle()<<endl;
 
 cout<<"\nfilling histograms ..."<<endl;
 /// -- data
 cout<<"  -->data (takes some time) ..."<<endl;
 hc.MakePlot( tData, hist_Data,  hc.GetCut(category, "OS", purpose, region), variable1, variable2 );
 
 /// -- data - Histo Fit and QCD normalization
 cout<<"  -->data histo-fit"<<endl;
 hc.MakePlot( tData, hist_Data_HistoFit,  hc.GetCut(category, "OS", HistoFitMethod, region), variable1, variable2 );
 
 /// -- QCD from data
 cout<<"  -->QCD"<<endl;
 hc.MakePlot( tData, hist_QCD,  hc.GetCut(category, QCDmodel, purpose, region), variable1, variable2 );
 
 /// -- MC search region - nominal
 
 cout<<"  -->MC SR"<<endl;
 for(map<int, TH2D *>::iterator it = hmap_Sig.begin(); it != hmap_Sig.end(); it++){
   if(it->first < 800000){
	 TCut c = "";
	 if(kWqq_special_treatment) if( it->first >= 169547 && it->first <= 169549 ) {c += "ditau_at_least_one_truth"; cout<<"Wqq "<<it->first<<endl;}
	 hc.MakePlot(tmap[it->first], it->second, hweight * hc.GetCut(category, "OS", purpose, region) * c, variable1, variable2 );	
   }
 }
 
 /// -- MC bkg model for bkg subtraction - nominal
 for(map<int, TH2D *>::iterator it = hmap_Bkg.begin(); it != hmap_Bkg.end(); it++){
   if(it->first < 800000)
	 hc.MakePlot(tmap[it->first], it->second, hweight * hc.GetCut(category, QCDmodel, purpose, region), variable1, variable2 );
 }
 
 /// -- embedding
 if(kEmbedding){
   cout<<"-->embedding"<<endl;
   ///search region
   hc.MakePlot( tEmbedding, hist_Z_Emb, hweight * hc.GetCut(category, "OS", purpose, region), variable1, variable2 );
   cout<<"\temb area: "<< hist_Z_Emb->Integral()<<endl;
   ///for subtractuion
   hc.MakePlot( tEmbedding, hist_Z_Emb_subtr, hweight * hc.GetCut(category, QCDmodel, purpose, region), variable1, variable2 );
   cout<<"\temb for subtr area: "<< hist_Z_Emb_subtr->Integral()<<endl;
 }
 
 ///normalize all MC to data lumi ==========================================================================================
 cout<<"\nhistograms normalization"<<endl;
 
 ///normalize signal
 cout<<"  signal"<<endl;
 for(map<int, TH2D *>::iterator it = hmap_Sig.begin(); it != hmap_Sig.end(); it++){
   if(it->first < 800000){
	 it->second->Scale( mcbank.Get_Norm(it->first, DataLumi) );
   }
 }
 
 ///normalize bkg
 cout<<"  bkg"<<endl;
 for(map<int, TH2D *>::iterator it = hmap_Bkg.begin(); it != hmap_Bkg.end(); it++){
   if(it->first < 800000){
	 it->second->Scale( mcbank.Get_Norm(it->first, DataLumi) );
   }
 }
 
 
 ///fill inclusive MC plots==========================================================================================
 cout<<"\nmaking inclusive histos ..."<<endl;
 for(vector<int>::iterator it=RunsVector.begin(); it != RunsVector.end(); it++){
   if( *it >= 800000) continue;
   
   ///check entries
   if(kPrintEmptyHistos){
	 //nominal
	 if(! hmap_Sig[*it]->GetEntries() )  cout<<"empty signal histogram : "<<*it<<endl;
	 if(! hmap_Bkg[*it]->GetEntries() )  cout<<"empty bkg histogram : "<<*it<<endl;
	 
   }
   
   int mcn(0);
   
   if( hc.Is("Higgs", *it)  ) { mcn = 800000;
   
   hmap_Sig[mcn]->Add( hmap_Sig[*it]); 
   hmap_Bkg[mcn]->Add( hmap_Bkg[*it]);
   
   }
   
   if( hc.Is("Ztautau", *it)  ) { mcn = 800001;
   
   hmap_Sig[mcn]->Add( hmap_Sig[*it]); 
   hmap_Bkg[mcn]->Add( hmap_Bkg[*it]);
   
   }
   
   if( hc.Is("Electroweak", *it)  ) { mcn = 800005;
   
   hmap_Sig[mcn]->Add( hmap_Sig[*it]); 
   hmap_Bkg[mcn]->Add( hmap_Bkg[*it]);
   
   }
   
   
   
 }//loop over mc samples
 
 
 ///Decide which will be the Z sample =================================================================================
 if(kEmbedding){
   cout<<"Z is from Embedding"<<endl;
   
   hist_Z->Add( hist_Z_Emb, 1 );
   hist_Z_subtr->Add(hist_Z_Emb_subtr , 1 );
   
   
 }else {
   cout<<"Z is from MC"<<endl;
   
   hist_Z->Add( hmap_Sig[800001], 1 );
   hist_Z_subtr->Add(hmap_Bkg[800001], 1 );
   
 }
 cout<<"\tZ entries, area "<<hist_Z->GetEntries()<<", "<<hist_Z->Integral()<<endl;
 
 ///Perform EWK + Z subtraction from QCD==============================================================================
 // ewk subtraction
 if(kEWK_subtraction){
   
   ///nominal
   cout<<"\nSubtracting ewk bkg from QCD bkg"<<endl;
   cout<<"\t  QCD integral before subtraction "<<hist_QCD->Integral(-1,-1,-1,-1)<<endl;
   hist_QCD->Add(hmap_Bkg[800005], -1);
   cout<<"\t  QCD integral after subtraction "<<hist_QCD->Integral(-1,-1,-1,-1)<<endl<<endl;
   //check for negative bins here
   //CheckNegativeBinContent(hist_QCD, "QCD - ewk bkg removal");
   
 }
 
 // Z subtraction
 if(kZtautau_subtraction){
   
   ///nominal
   cout<<"\nSubtracting Ztautau bkg from QCD bkg"<<endl;
   cout<<"\tQCD integral before "<<hist_QCD->Integral(-1,-1,-1,-1)<<endl;
   hist_QCD->Add(hist_Z_subtr, -1);
   cout<<"\tQCD integral after "<<hist_QCD->Integral(-1,-1,-1,-1)<<endl<<endl;
   //check for negative bins here
   //CheckNegativeBinContent(hist_QCD, "QCD - Ztautau bkg removal");
   
   
 }
 
 ///normalize QCD ======================================================================================================
 
 ///nominal 
 
 
 double data_trackfit_area = hist_Data_HistoFit->Integral(-1,-1,-1,-1);
 cout<<"\ntrack fit area "<<data_trackfit_area<<endl;
 //nominal
 cout<<"\nNormalize QCD bkg to Track Fit using factor "<<QCD_TrackFitFactor_nominal<<"  - NOMINAL"<<endl;
 double QCDnorm_nominal =  QCD_TrackFitFactor_nominal * data_trackfit_area;
 cout<<"\tQCD target norm  "<<QCDnorm_nominal<<endl;
 double QCD_integral_nominal(0); QCD_integral_nominal = hist_QCD->Integral(-1,-1,-1,-1);
 if(QCD_integral_nominal < 1e-8) {  
   cout<<"QCD Integral "<<QCD_integral_nominal<<endl; 
   cout<<"Empty QCD histo. Bye bye ..."<<endl; exit(0); 
 }
 double QCDweight_f_nominal = QCDnorm_nominal/QCD_integral_nominal;
 cout<<"\tQCD final norm factor (using fQCD)  "<<QCDweight_f_nominal<<endl;
 cout<<"\tQCD integral before scaling "<<hist_QCD->Integral(-1,-1,-1,-1)<<endl;
 hist_QCD->Scale( QCDweight_f_nominal );// normal
 ////double temp_scale_daniele_qcd = 0.606 * hist_Data->Integral(-1,-1,-1,-1)/hist_QCD->Integral(-1,-1,-1,-1);
 ////hist_QCD->Scale( temp_scale_daniele_qcd );// Trial
 cout<<"\tQCD integral after scaling "<<hist_QCD->Integral(-1,-1,-1,-1)<<" <<== final QCD bkg before subtraction"<<endl<<endl;
 
 
 
 // 		if( HistoFitMethod == "TrackFit" ) NormalizeQCD_TrackFit(hist_QCD, hist_Data_HistoFit, fQCD_HistoFit);
 // 	else if( HistoFitMethod == "dEtaFit" ) NormalizeQCD_dEtaFit(hist_QCD, hist_Data_HistoFit, fQCD_HistoFit);
 // 	else { cout<<"Normalization method for QCD - unknown : Exiting ... "<<endl; exit(0);}
 
 // 	double dEtaFit_fQCD = 0.5617;
 //  	double 	area_QCD =  hist_QCD->Integral(-1,-1,-1,-1);
 //  	double	area_data = hist_Data->Integral(-1,-1,-1,-1);
 // 	double 	dEtaFit_QCD_w = area_data/area_QCD*dEtaFit_fQCD;
 // 	cout<<"QCD Normalization: using f_QCD="<< dEtaFit_fQCD <<endl;
 // 	cout<<"QCD Normalization: total data events "<< area_data <<endl;
 // 	cout<<"QCD Normalization: total QCD events "<< area_QCD <<endl;
 // 	hist_QCD->Scale( dEtaFit_QCD_w);
 //  	cout<<"QCD Normalization: total normalized QCD events "<<  hist_QCD->Integral(-1,-1,-1,-1) <<endl;
 
 
 
 ///normalize Ztautau ==========================================================================
 
 // 	double 	area_TAU =  hmap_Sig[800001]->Integral(-1,-1,-1,-1);
 // 	cout<<"TAU Normalization: using f_TAU="<< TrackFit_f_TAU <<", sf_TAU=" << TrackFit_sf_TAU<<", sf13_TAU="<< TrackFit_sf13_TAU<<endl;
 // 	cout<<"TAU Normalization: total data events "<< area_data <<endl;
 // 	cout<<"TAU Normalization: total TAU events "<< area_TAU <<endl;
 // 	hmap_Sig[800001]->Scale(  0.8 );
 // 	cout<<"TAU Normalization: total normalized TAU events "<<  hmap_Sig[800001]->Integral(-1,-1,-1,-1) <<endl;
 // 	
 
 
 // 	double 	dEtaFit_fTAU = 0.3752;
 // 	double 	area_TAU =  hmap_Sig[800001]->Integral(-1,-1,-1,-1);
 // 	double 	dEtaFit_TAU_w = area_data/area_TAU*dEtaFit_fTAU;
 // 	cout<<"Z Normalization: using f_TAU="<< dEtaFit_fTAU <<endl;
 // 	cout<<"Z Normalization: total data events "<< area_data <<endl;
 // 	cout<<"Z Normalization: total TAU events "<< area_TAU <<endl;
 // 	hmap_Sig[800001]->Scale( dEtaFit_TAU_w);
 //  	cout<<"Z Normalization: total normalized TAU events "<<  hmap_Sig[800001]->Integral(-1,-1,-1,-1) <<endl;
 
 
 ///nominal - TrackFit KZ
 double Znorm_nominal =  Z_TrackFitFactor_nominal * data_trackfit_area; 
 double Z_integral_nominal = hist_Z->Integral();
 if(Z_integral_nominal < 1e-6) { cout<<"Empty Ztautau histo. Bye bye ..."<<endl; exit(0); }
 double Zweight_f_nominal = Znorm_nominal / Z_integral_nominal;	
 cout<<"\nNormalize Z bkg to Track Fit"<<endl;
 cout<<"\tZ target norm  N = "<<Znorm_nominal<<endl;
 cout<<"\tZ final norm factor (using fZ)  "<<Zweight_f_nominal<<endl;	
 //apply z weigth
 cout<<"\tZ integral before "<<hist_Z->Integral()<<endl;
 hist_Z->Scale(Zweight_f_nominal);//normal
 cout<<"\tZ integral after "<<hist_Z->Integral()<<endl<<endl;	
 

 ///stats =================================================================================================
 cout<<"\nentries : integral - nominal"<<endl;
 cout<<left<<"H    "<<setw(10)<<hmap_Sig[800000]->GetEntries()	<<" : "<<setw(10)<<hmap_Sig[800000]->Integral()<<endl;
 cout<<left<<"Z    "<<setw(10)<<hist_Z->GetEntries()				<<" : "<<setw(10)<<hist_Z->Integral()<<endl;
 cout<<left<<"EWK  "<<setw(10)<<hmap_Sig[800005]->GetEntries()	<<" : "<<setw(10)<<hmap_Sig[800005]->Integral()<<endl;
 cout<<left<<"QCD  "<<setw(10)<<hist_QCD->GetEntries()			<<" : "<<setw(10)<<hist_QCD->Integral()<<endl;
 cout<<left<<"Data "<<setw(10)<<hist_Data->GetEntries()			<<" : "<<setw(10)<<hist_Data->Integral()<<endl;
 cout<<"Data - [QCD + EWK + Z] = "<<
 hist_Data->Integral() - (hist_QCD->Integral() + hmap_Sig[800005]->Integral() + hist_Z->Integral() )<<endl;
 
 cout<<endl;
 
 ///signal, individual plot ======================================================================================
 hist_Signal->Add(hmap_Sig[800000], 1);
 
 
 ///zoom signal ===================================================================================================
 if(SignalZoom > 0){
   hist_Signal->Scale( SignalZoom );
 }
 
 ///spectra  and bkg curves ==========================================================================================
 
 ///spectra
 hist_Spectrum0->Add(hist_QCD, 1);			/// qcd
 
 hist_Spectrum1->Add(hist_Spectrum0, 1);		/// qcd + ewk
 hist_Spectrum1->Add(hmap_Sig[800005], 1); 
 
 hist_Spectrum2->Add(hist_Spectrum1, 1);		/// qcd + ewk + Z
 hist_Spectrum2->Add(hist_Z, 1);
 
 hist_Spectrum3->Add(hist_Spectrum2, 1);		/// qcd + ewk + Z + signal
 hist_Spectrum3->Add(hmap_Sig[800000], SignalZoom);
 
 ///Background - nominal
 hist_BKG->Add(hist_QCD, 1.0); 
 hist_BKG->Add(hmap_Sig[800005], 1.0); 
 hist_BKG->Add(hist_Z, 1.0); 	
 
 cout<<"\nBkg area "<<hist_BKG->Integral(-1,-1,-1,-1)<<endl;
 cout<<"\nData area "<<hist_Data->Integral(-1,-1,-1,-1)<<endl;
 
 
 ///output file (before canvas)
 TFile *f = new TFile( fn.c_str(), "recreate");
 
 cout<<" Setting Canvas"<<endl;
 ///Set canvas and create 2 empty histos for up and down  =========================================================
 TCanvas *c = new TCanvas("c","Stack Plots", 10, 10, 400, 400);
 gStyle->SetOptStat(0);
 gStyle->SetOptTitle(0);
 gStyle->SetObjectStat(0);
 c->SetFillColor(0);
 c->SetBorderMode(0);
 c->SetBorderSize(0);
 c->SetGridx();
 c->SetGridy();
 c->SetTickx(1);
 c->SetTicky(1);
 c->SetRightMargin( c->GetRightMargin()*0.3 );
 c->SetLeftMargin( c->GetLeftMargin()*1.4 );
 c->SetFrameBorderMode(0);
 gStyle->SetGridColor(kGray);
 
 
 int font = 82;
 
 hist_Data->SetStats(0);
 hist_Data->GetYaxis()->SetLabelSize(0.05);
 hist_Data->GetYaxis()->SetLabelFont(font);
 hist_Data->GetYaxis()->SetTitleSize(0.05);
 hist_Data->GetYaxis()->SetTitleOffset(1.3);	
 hist_Data->GetYaxis()->SetTitleFont(font);
 hist_Data->GetYaxis()->SetTitle(yTitle.c_str());
 
 hist_Data->GetXaxis()->SetLabelSize(0.04);
 hist_Data->GetXaxis()->SetLabelFont(font);
 hist_Data->GetXaxis()->SetTitleSize(0.05);
 hist_Data->GetXaxis()->SetTitleOffset(0.95);	
 hist_Data->GetXaxis()->SetTitleFont(font);
 hist_Data->GetXaxis()->SetTitle(xTitle.c_str());
 
 ///draw empty histo 
 
 
 hist_Data->SetMinimum(0);
 hist_BKG->SetMinimum(0);
 
 
 hist_Data->SetMarkerColor(kGray+2);	//TColor *col = gROOT->GetColor(kGray+1); cout<<col->GetNumber()<<endl;
 hist_BKG->SetMarkerColor(kRed); 
 
 // hist_Data->Draw("");
 // hist_BKG->Draw("same"); 
 
 TProfile *pData = hist_Data->ProfileX("pData");
 TProfile *pBkg = hist_BKG->ProfileX("pBkg");
 
 pData->SetLineColor(kGreen);	pData->SetLineWidth(3);
 pBkg->SetLineColor(kAzure+1);	pBkg->SetLineWidth(3);
 
 TH1 *pData_new;
 TH1 *pBkg_new;
 
 if(kBin1){
   pData_new 	= pData->Rebin(n1-1,"pData_new", Array1); 
   pBkg_new 	= pBkg->Rebin(n1-1,"Bkg_new", Array1); 
   //turn off for track fit
   pData_new->Draw("same");
   pBkg_new->Draw("same");
 }else{
   
   pData_new = pData;
   pBkg_new = pBkg;
   pData_new->Draw("same"); //To draw a profile histogram and not show the error bars use the “HIST” option
   pBkg_new->Draw("same");
 }
 
 TLatex *Chi2texHeader = new TLatex( 0.17, 0.82, "Chi2/NDF from:" );
 Chi2texHeader->SetNDC();//(Normalized Device Coordinates) [0,1]
 Chi2texHeader->SetTextFont(60);
 Chi2texHeader->SetTextSize(0.05);
 Chi2texHeader->SetLineWidth(2);
 Chi2texHeader->Draw();
 
 //http://root.cern.ch/root/html/TH1.html#TH1:Chi2Test
 double Chi2 = 	pData_new->Chi2Test(pBkg_new,"CHI2/NDF");
 double Chi2_2D = 	hist_Data->Chi2Test(hist_BKG,"CHI2/NDF");
 char cChi2[500];  	char cChi2_2D[500];  
 sprintf(cChi2,		" Profile: %f",Chi2);
 sprintf(cChi2_2D, 	" 2D Plot: %f",Chi2_2D);
 cout<<"Chi2/NDF: from profile "<<pData_new->Chi2Test(pBkg_new,"CHI2/NDF")<<endl;
 TLatex *Chi2tex = new TLatex( 0.17, 0.76, cChi2 );
 Chi2tex->SetNDC();//(Normalized Device Coordinates) [0,1]
 Chi2tex->SetTextFont(60);
 Chi2tex->SetTextSize(0.05);
 Chi2tex->SetLineWidth(2);
 Chi2tex->Draw();
 
 cout<<"Chi2/NDF: from 2D plot "<<hist_Data->Chi2Test(hist_BKG,"CHI2/NDF")<<endl;
 TLatex *Chi2tex_2D = new TLatex( 0.17, 0.70, cChi2_2D );
 Chi2tex_2D->SetNDC();//(Normalized Device Coordinates) [0,1]
 Chi2tex_2D->SetTextFont(60);
 Chi2tex_2D->SetTextSize(0.05);
 Chi2tex_2D->SetLineWidth(2);
 Chi2tex_2D->Draw();
 
 ofstream Chi2Record;
 Chi2Record.open("Chi2Values.txt",std::fstream::app);
 string PlottedVariables = variable1+" Vs "+variable2;
 Chi2Record<<PlottedVariables<<" Profile "<<cChi2<<endl;
 Chi2Record<<PlottedVariables<<" 2D "<<cChi2_2D<<endl;
 
 double cFactor_data = hist_Data->GetCorrelationFactor();
 double cFactor_bkg 	= hist_BKG->GetCorrelationFactor();
 
 char cFactor_data_buf[24];
 sprintf(cFactor_data_buf, "%.2f", cFactor_data);
 string  cFactor_data_str = cFactor_data_buf;
 
 char cFactor_bkg_buf[24];
 sprintf(cFactor_bkg_buf, "%.2f", cFactor_bkg);
 string  cFactor_bkg_str = cFactor_bkg_buf;
 
 
 string lat_str = "Data(#color[922]{#bullet} #color[416]{#topbar}, "+cFactor_data_str+")  Model(#color[632]{#bullet} #color[861]{#topbar}, "+cFactor_bkg_str+")";
 
 
 TLatex *tex = new TLatex(0.12, 0.93, lat_str.c_str());
 tex->SetTextFont(42);
 tex->SetTextSize(0.06);
 tex->SetNDC();
 tex->Draw();
 
 if(kLogZ) gPad->SetLogz();
 gPad->RedrawAxis();	
 
 c->Modified();
 c->cd();
 c->SetSelected(c);
 
 // 	cout<<" Setting Pad 1"<<endl;
 // 	///Top pad=======================================================================================================
 // 	c->cd();
 // 	TPad *pad1 = new TPad("pad1","pad1", 0, 0.2, 1, 1);
 // 	hc.SetPad(pad1);
 // 	pad1->SetTopMargin(c->GetTopMargin()*0.4 );
 // 	pad1->SetBottomMargin(0 );
 // 	pad1->Draw();
 // 	pad1->cd();
 // 	hEmpty1->GetXaxis()->SetRangeUser(MinX, MaxX); 
 // 
 // 	double maxim_y = hist_Data->GetBinContent(hist_Data->GetMaximumBin());
 // 	double maxim_y_new = maxim_y*AutoOffsetTimes;
 // 	if(kAutoMaxYaxis){
 // 		hEmpty1->SetMaximum(maxim_y_new);
 // 		cout<<"maxY "<<MaxY<<" -> "<<maxim_y_new<<endl;
 // 	}else{
   // 		if(MaxY>0) hEmpty1->SetMaximum(MaxY); 	
   // 		
   // 	}
   // 	if(MinY>0) hEmpty1->SetMinimum(MinY); 
   
   
   
   // 	if(xNdivisions) hEmpty1->GetXaxis()->SetNdivisions( xNdivisions );
   
   
   
   
   //if(kShowSignalAlone) hist_Signal->Draw("hist same");
   
   
   
   ///type category
   // 	string lat_categ = 	
   // 		category == "vbf" ? "VBF" :
   // 		category == "boosted" ? "Boosted" :
   // 	  	category == "1jet" ? "1-jet" :
   // 	  	category == "0jet" ? "0-jet" : 
   // 	  	category =="preselection"  ? "Preselection" :  
   // 			"unknown category";
   // 
   // 	string thisregion = 
   // 		region == "CR_MassSideBands" ? "Mass Side Bands CR" : 
   // 		region == "SR_MassWindow" ? "Signal Region" : 
   // 		region == "CR_LowMassCut" ? "Low Mass Cut CR" : 
   // 		region == "CR_UpperMassCut" ? "Upper Mass Cut CR" : 
   // 		region == "CR_NoMassCut" ? "No Mass Cut CR" : 
   // 		region == "CR_QCDrich" ? "QCD-rich CR" : 
   // 		region == "CR_preselection" ? "" : 
   // 		region == "CR_dEta" ? "#Delta#eta_{#tau#tau} CR" : 
   // 			"Unknown Region";
   // 		
   // 
   // 	string category_region = "#splitline{#tau_{h} #tau_{h} : "+lat_categ+"}{"+thisregion+"}";
   // 	
   // 	double xlat = 0.155;
   // 	double ylat= 0.625;
   // 
   // 	TLatex *tex = new TLatex( xlat, ylat, category_region.c_str() );
   // 	tex->SetNDC();//(Normalized Device Coordinates) [0,1]
   // 
   // 	tex->SetTextFont(42);
   // 	tex->SetTextSize(0.035);
   // 	tex->SetLineWidth(2);
   // 	tex->Draw();
   
   // 	cout<<" Setting Pad 2"<<endl;
   // 	///Bottom pad ===============================================================================================================
   // 	c->cd();
   // 	TPad *pad2 = new TPad("pad2","pad2", 0, 0, 1, 0.2);
   // 	hc.SetPad(pad2);
   // 	pad2->SetTopMargin(0);
   // 	pad2->SetBottomMargin(c->GetBottomMargin()*3.5 );
   // 	pad2->SetFillStyle(4000); //transparent
   // 	pad2->Draw();
   // 	pad2->cd();
   // 	hEmpty2->SetMaximum(RatioMaxY); 
   // 	hEmpty2->SetMinimum(RatioMinY); 
   // 	hEmpty2->GetXaxis()->SetLabelSize(0.14);
   // 	hEmpty2->GetYaxis()->SetLabelSize(0.14);
   // 	hEmpty2->GetXaxis()->SetLabelFont(font);
   // 	hEmpty2->GetYaxis()->SetLabelFont(font);
   // 	hEmpty2->GetXaxis()->SetTitle(xTitle.c_str());
   // 	hEmpty2->GetXaxis()->SetTitleOffset(0.9);	
   // 	hEmpty2->GetXaxis()->SetTitleFont(font);
   // 	hEmpty2->GetXaxis()->SetTitleSize(0.17);
   // 				
   // 	hEmpty2->GetYaxis()->SetTitle("title");			
   // 	hEmpty2->GetYaxis()->SetTitleSize(0.17);
   // 	hEmpty2->GetYaxis()->SetTitleOffset(0.34);	
   // 	hEmpty2->GetYaxis()->SetTitleFont(font);
   // 	hEmpty2->GetYaxis()->CenterTitle(1);
   // 	hEmpty2->GetYaxis()->SetNdivisions(105);
   // 
   // 					
   // 	hEmpty2->Draw();
   // 	
   // 
   // 	gPad->RedrawAxis();
   
   
   /// Store results =================================================================================
   
   if(kProducePDF){
	 c->SaveAs(fn_pdf.c_str());
	 cout<<fn_pdf<<endl;
   }
   
   if(kProducePNG){
	 c->SaveAs(fn_png.c_str());
	 cout<<fn_png<<endl;
   }
   
   if(kProduceEPS){
	 c->SaveAs(fn_eps.c_str());
	 cout<<fn_eps<<endl;
   }
   
   if(kProducePS){
	 c->SaveAs(fn_ps.c_str());
	 cout<<fn_ps<<endl;
   }
   
   cout<<fn<<endl;
   f->cd();
   c->Write();
   
   hist_Data_HistoFit->Write("hFitData");
   hist_Data->Write("hData");
   hist_BKG->Write("hBkg");
   hist_QCD->Write("hQCD");
   hmap_Sig[800005]->Write("hEwk");
   hist_Z->Write("hZtautau");
   hist_Signal->Write("hSignal");

   
   if(PlotTrackFit){
     hist_Z_Emb->Write("hist_800001");
     hist_QCD  ->Write("hist_900003");
     hist_QCD  ->Write("hist_900002");
     hist_Data ->Write("hist_900001");
     hist_Signal->Write("hist_800000");
     hmap_Sig[800005]->Write("hist_800005");
     //     hist_Z_subtr->Add(hist_Z_Emb_subtr , 1 );
   }
   f->Close();
   cout<<"\nData tree entries : "<<tData->GetEntries()<<" <--- "<<endl;
   
   }
   
   ///************************************************************************
   ///************************************************************************
   void CheckNegativeBinContent(TH2D *h, const string &s){
	 cout<<"Checking "<<s<<" for bins with negative value"<<endl;
	 bool found(false);
	 int n = h->GetNbinsX();
	 for(int i = 1; i <= n; i++){
	   
	   double bc = h->GetBinContent(i);
	   
	   if( bc < 0 ) {
		 cout<<" negative bin content "<<bc<<" bin "<<i<<" "<<h->GetBinLowEdge(i)<<" - "<<h->GetBinLowEdge(i)+h->GetBinWidth(i)
		 <<endl;
		 
		 found = true;
	   }
	 }
	 
	 if(!found) cout<<"\n"<<s<<" is OK"<<endl;
	 cout<<endl;
   }
   
   ///************************************************************************
   ///************************************************************************
   // void NormalizeQCD_TrackFit(TH2D *h, TH2D *hHistoFit, double f_QCD, ){
 // 	
 // 
 // 	
 // 	
 // 	
 // 
 // }
 // 	
 // void NormalizeQCD_dEtaFit(TH2D *h, TH2D *hHistoFit, TH2D *f){
 // 
 // }
 
 
 
