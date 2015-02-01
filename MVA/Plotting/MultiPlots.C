

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

#include "TROOT.h"
#include "TString.h"
#include "TSystem.h"
#include "TStyle.h"
#include "TH1D.h"
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

#include "HelperClass.h"
#include "MonteCarloBank.h"

void MultiPlots(TString category, TString variable);
void CheckNegativeBinContent(TH1D *h, const string &s);
void PrintErrors(TGraphAsymmErrors *g);
// void NormalizeQCD_TrackFit(TH1D *h, TH1D *hHistoFit, double f);
// void NormalizeQCD_dEtaFit(TH1D *h, TH1D *hHistoFit, double f);
void Normalize_QCD_Ztautau_TrkFit_ZinonKaty(const string &S, TH1D *h, double data_trackfit_area, double SF );
void QCD_subtraction(const string &S, TH1D *h, const TH1D *hs, bool k);
void TestVariations(const string &S, bool kUp, const TH1D *h0, const TH1D *h1);

void MultiPlots(TString category_tstr, TString variable_tstr){
  
	///form chars to strings
	const char *category_c = category_tstr.Data();
	const char *variable_c = variable_tstr.Data();
	
	string category(category_c);
	string variable(variable_c);
	cout<<"Plotting variable '"<<variable<<"' in category '"<<category<<"'"<<endl;

	string  category_file ; ///for reading from the BDT files
    if(category == "Preselection")  
	  category_file = "vbf";
    else 
	  category_file = category_c;

	///external classes
	gSystem->Load("../../HelperClass/HelperClass_cpp.so");
	gSystem->Load("../../MonteCarloBank/MonteCarloBank_cpp.so");

	HelperClass hc;
	hc.SetPrints(false);
	
	MonteCarloBank mcbank;
	mcbank.PrintWeights(false);
	
	/// some variables
	double MinX, MaxX, MinY, MaxY; 
	bool 	kLogY; string xTitle;int nbins; double firstbin, lastbin; bool kAdjustLeftBin, kAdjustRightBin;
	double 	QCD_TrackFitFactor_nominal, Z_TrackFitFactor_nominal; 
	double 	QCD_TrackFitFactor_JESup, QCD_TrackFitFactor_JESdown;
	double 	QCD_TrackFitFactor_TESup, QCD_TrackFitFactor_TESdown;
	double 	Z_TrackFitFactor_JESup, Z_TrackFitFactor_JESdown;
	double 	Z_TrackFitFactor_TESup, Z_TrackFitFactor_TESdown;
	string 	fillcolor; int xNdivisions(0);
	string NormMethod("");
	double f_QCD, f_TAU, f13_QCD, f13_TAU, sf_QCD, sf_TAU, sf13_QCD, sf13_TAU;

	/// category settings
	if(category == "vbf"){
		//fillcolor = "green";
		fillcolor = "harmonized";

		QCD_TrackFitFactor_nominal = 0.262317;  Z_TrackFitFactor_nominal = 0.261899; NormMethod="TrkFit"; // normal

	}else if(category == "boosted"){
		//fillcolor = "azure";
		fillcolor = "harmonized";
        QCD_TrackFitFactor_nominal = 0.254399;  Z_TrackFitFactor_nominal = 0.331562;  //Preselection mmc<100         

	}else if( category == "1jet"){
		//fillcolor = "blue";
		fillcolor = "harmonized";

		QCD_TrackFitFactor_nominal = 0.286683;  Z_TrackFitFactor_nominal = 0.287435;//normal (CR_UpperMassCut)   

	}else if( category == "0jet"){
		//fillcolor = "magenta";
		fillcolor = "harmonized";
        QCD_TrackFitFactor_nominal = 0.351096;  Z_TrackFitFactor_nominal = 0.200306;//normal (CR_UpperMassCut)                                                 

		
	}else if( category == "preselection"){

	  QCD_TrackFitFactor_nominal = 0.424183;  	Z_TrackFitFactor_nominal = 0.149615; 	  NormMethod="TrkFit0jet";  // from 0jet
	  QCD_TrackFitFactor_TESup = 0.426185;  	Z_TrackFitFactor_TESup = 0.14891;
	  QCD_TrackFitFactor_TESdown = 0.426215;  	Z_TrackFitFactor_TESdown = 0.151973;
	    
	  f_QCD           =        0.7745;// +-       0.0118
	  f_TAU           =        0.1872;// +-       0.0029
	  f13_QCD         =        0.0164;//
	  f13_TAU         =        0.0018;//
	  sf_QCD          =        1.3168;// +-       0.0201
	  sf_TAU          =        0.7124;// +-       0.0109
	  sf13_QCD        =        1.2994;// +-       0.0201
	  sf13_TAU        =        0.7124;// +-       0.0109
	  
	}else{
		cout<<"\nMultiPlots - Choose a proper category. Exiting ..."<<endl;NormMethod="TrkFit";
		exit(0);
	}
	
	
	///automate the y-axis range
	bool kAutoMaxYaxis = true;
	double AutoOffsetTimes = 1.10;
	
	///variable settings =============================================================================================
	if( variable == "BDT_Weight"){
	  	MinX = -1.0; MaxX = 1.0; MinY = 1e-6; MaxY = 700.0;
		kLogY = false; xTitle = "BDT score";
		firstbin = -1; lastbin = 1; nbins = 20; 
		kAdjustLeftBin = false; kAdjustRightBin = false;
		kAutoMaxYaxis = true; AutoOffsetTimes = 1.5;
		
	  
	}else if( variable == "met_et"){ 
	  
		MinX = 20.0; MaxX = 150.0; MinY = 1e-6; MaxY = 700.0;
		kLogY = false; xTitle = "#slash{E}_{T} [GeV]";
		firstbin = 0; lastbin = 300; nbins = 60; 
		kAdjustLeftBin = false; kAdjustRightBin = false;
		kAutoMaxYaxis = true; AutoOffsetTimes = 1.5;
		
	}else if( variable == "MMC_met_et"){ 
		
		MinX = 20.0; MaxX = 150.0; MinY = 1e-6; MaxY = 700.0;
		kLogY = false; xTitle = "MMC #slash{E}_{T} [GeV]";
		firstbin = 0; lastbin = 300; nbins = 60; 
		kAdjustLeftBin = false; kAdjustRightBin = false;
		kAutoMaxYaxis = true; AutoOffsetTimes = 1.5;
		
	}else if( variable == "ditau_met_out_min_dPhi"){

		MinX = 0.0; MaxX = 4.0; MinY = 1e-6; MaxY = 700.0;
		kLogY = false; xTitle = "ditau_met_out_min_dPhi";
		firstbin = 0; lastbin = 4; nbins = 20;
		kAdjustLeftBin = false; kAdjustRightBin = false;
		kAutoMaxYaxis = true; AutoOffsetTimes = 1.5;
		
	}else if( variable == "HT_jets_taus"){ 
		 
		MinX = 60.0; MaxX = 760.0; MinY = 1e-6; MaxY = 220.0; // taus: 35 + 25 = 60
		kLogY = false; xTitle = "H_{T}(di-#tau, jets) [GeV]";
		firstbin = 60; lastbin = 1060; nbins = 50; 
		kAdjustLeftBin = false; kAdjustRightBin = false;
		kAutoMaxYaxis = true; AutoOffsetTimes = 1.5;
		
	}else if( variable == "HT_jets_taus_met"){ 
		
		MinX = 80.0; MaxX = 780.0; MinY = 1e-6; MaxY = 220.0; // taus: 35 + 25 + met 20 = 80
		kLogY = false; xTitle = "H_{T}(di-#tau, jets, #slash{E}_{T}) [GeV]";
		firstbin = 80; lastbin = 1080; nbins = 50; 
		kAdjustLeftBin = false; kAdjustRightBin = false;
		kAutoMaxYaxis = true; AutoOffsetTimes = 1.5;
		
	}else if( variable == "HT_jets"){ 

		MinX = 0.0; MaxX = 700.0; MinY = 1e-6; MaxY = 220.0;
		kLogY = false; xTitle = "H_{T}(jets) [GeV]";
		firstbin = 0; lastbin = 1000; nbins = 50; 
		kAdjustLeftBin = false; kAdjustRightBin = false;
		kAutoMaxYaxis = true; AutoOffsetTimes = 1.5;
		
	}else if(variable == "MMC_resonance_x0" || variable == "MMC_resonance_x1"){
		
		MinX = 0; MaxX = 1; MinY = -1e-6; MaxY = 200.0; 

		kLogY = false;  xTitle =  variable == "MMC_resonance_x0" ? "MMC leading #tau visible fraction x" : "MMC subleading #tau visible fraction x";
		firstbin = 0; lastbin = 1; nbins = 10;  
		kAdjustLeftBin = false; kAdjustRightBin = false;
		kAutoMaxYaxis = true; AutoOffsetTimes = 1.5;
	  
	}else if(variable == "ditau_colapprox_x0" || variable == "ditau_colapprox_x1"){
		
		MinX = 0; MaxX = 1; MinY = -1e-6; MaxY = 200.0; 
		if(category=="vbf"){ MinX = 0.; MaxX = 1; MinY = -1e-6; MaxY = 200.0; }
		if(category=="1jet"){ MinX = 0.; MaxX = 1; MinY = -1e-6; MaxY = 200.0; }
		kLogY = false;  xTitle =  variable == "ditau_colapprox_x0" ? 
				"Collinear Approximation leading #tau x" : "Collinear Approximation  subleading #tau x";
		firstbin = 0; lastbin = 1; nbins = 10;  kAdjustLeftBin = false; kAdjustRightBin = false;
		kAutoMaxYaxis = true; AutoOffsetTimes = 2;
	  
	}else if(variable == "MMC_resonance_jets_min_dEta"){
		
		MinX = 0; MaxX = 5; MinY = -1e-6; MaxY = 200.0;
		kLogY = false;  xTitle =  "min#Delta#eta(MMC resonance, jet)";
		firstbin = 0; lastbin = 10; nbins = 25;  
		kAdjustLeftBin = false; kAdjustRightBin = false;
		kAutoMaxYaxis = true; AutoOffsetTimes = 1.7;
	  
	}else if(variable == "MMC_resonance_jets_min_dR"){
		
		MinX = 0; MaxX = 5; MinY = -1e-6; MaxY = 200.0;
		kLogY = false;  xTitle =  "min#DeltaR(MMC resonance, jet)";
		firstbin = 0; lastbin = 10; nbins = 25;  
		kAdjustLeftBin = false; kAdjustRightBin = false;
		kAutoMaxYaxis = true; AutoOffsetTimes = 1.7;
	  
	}else if(variable == "MMC_resonance_dijet_DeltaPhi"){
		
		MinX = 0; MaxX = TMath::Pi(); MinY = -1e-6; MaxY = 200.0;
		kLogY = false;  xTitle =  "#Delta#phi(MMC resonance, di-jet)";
		firstbin = 0; lastbin = TMath::Pi(); nbins = 16;  
		kAdjustLeftBin = false; kAdjustRightBin = false;
		kAutoMaxYaxis = true; AutoOffsetTimes = 1.6;
	  
	}else if(variable == "MMC_resonance_dijet_vecSumPt"){
		MinX = 0; MaxX = 150; MinY = -1e-6; MaxY = 200.0; 
	
		kLogY = false;  xTitle =  "#Sigma#vec{p}_{T}(MMC resonance, di-jet)";
		firstbin = 0; lastbin = 500; nbins = 50;  
		kAdjustLeftBin = false; kAdjustRightBin = false;
		kAutoMaxYaxis = true; AutoOffsetTimes = 1.8;
	  
	}else if(variable == "MMC_resonance_dijet_DeltaPt"){
		
		MinX = 0; MaxX = 100; MinY = -1e-6; MaxY = 200.0;
		kLogY = false;  xTitle =  "#Deltap_{T}(MMC resonance, di-jet)";
		firstbin = 0; lastbin = 500; nbins = 50;  
		kAdjustLeftBin = false; kAdjustRightBin = false;
		kAutoMaxYaxis = true; AutoOffsetTimes = 1.7;
	  
	}else if(variable == "MMC_resonance_pt"){ 
		
		MinX = 0; MaxX = 260.; MinY = 1e-6; MaxY = 650.0; 
		kLogY = false; xTitle = "MMC resonance p_{T} [GeV]";
		firstbin = 0; lastbin = 500; nbins = 50; 
		kAdjustLeftBin = false; kAdjustRightBin = false;
		kAutoMaxYaxis = true; AutoOffsetTimes = 1.7;
		
	}else if(variable == "esv_all_objects_FoxWolfram_R1"){
		
		MinX = 0; MaxX = 1; MinY = -1e-6; MaxY = 200.0; 
		kLogY = false;  xTitle =  "Event Shape Fox-Wolfram R_{1}";
		firstbin = 0; lastbin = 1; nbins = 20;  
		kAdjustLeftBin = false; kAdjustRightBin = false;
		kAutoMaxYaxis = true; AutoOffsetTimes = 1.7;
	  
	}else if(variable == "esv_all_objects_FoxWolfram_R2"){
		
		MinX = 0; MaxX = 1; MinY = -1e-6; MaxY = 200.0;
		kLogY = false;  xTitle =  "Event Shape Fox-Wolfram R_{2}";
		firstbin = 0; lastbin = 1; nbins = 20;  
		kAdjustLeftBin = false; kAdjustRightBin = false;
		kAutoMaxYaxis = true; AutoOffsetTimes = 1.8;
	  
	}else if(variable == "esv_all_objects_sphericity"){
		
		MinX = 0; MaxX = 1; MinY = -1e-6; MaxY = 200.0; 
		kLogY = false;  xTitle =  "Event Shape Sphericity";
		firstbin = 0; lastbin = 1; nbins = 20;  
		kAdjustLeftBin = false; kAdjustRightBin = false;
		kAutoMaxYaxis = true; AutoOffsetTimes = 1.5;
	  
	}else if(variable == "esv_all_objects_planarity"){
		
		MinX = 0; MaxX = 0.5; MinY = -1e-6; MaxY = 1200.0; 
		kLogY = false;  xTitle =  "Event Shape Planarity";
		firstbin = 0; lastbin = 1; nbins = 20;  
		kAdjustLeftBin = false; kAdjustRightBin = false;
		kAutoMaxYaxis = true; AutoOffsetTimes = 1.5;
	  
	}else if(variable == "esv_all_objects_aplanarity"){
		
		MinX = 0; MaxX = 0.5; MinY = -1e-6; MaxY = 1200.0;
		kLogY = false;  xTitle =  "Event Shape Aplanarity";
		firstbin = 0; lastbin = 1; nbins = 25;  
		kAdjustLeftBin = false; kAdjustRightBin = false;
		kAutoMaxYaxis = true; AutoOffsetTimes = 1.5;
	  
	}else if(variable == "ditau_dR"){ 
		
		MinX = 0.0; MaxX = 4.0; MinY = 1e-6; MaxY = 1200.0; 
		kLogY = false; xTitle = "#DeltaR_{#tau#tau}";
		firstbin = 0; lastbin = 10; nbins = 25; 
		kAdjustLeftBin = false; kAdjustRightBin = false;
		kAutoMaxYaxis = true; AutoOffsetTimes = 1.7;
		
	}else if(variable == "ditau_dEta"){ 
		MinX = 0.0; MaxX = 3.4; MinY = 1e-6; MaxY = 1000.0; 

		kLogY = false; xTitle = "#Delta#eta_{#tau#tau}";
		firstbin = 0; lastbin = 5; nbins = 25; //25 nominal
		kAdjustLeftBin = false; kAdjustRightBin = true;
		//xlat = 0.2; 
		kAutoMaxYaxis = true; AutoOffsetTimes = 1.5;
		
	}else if( variable == "tau_0_dijet_eta_centr" || variable == "tau_1_dijet_eta_centr" ){ 
		
		MinX = 0.0; MaxX = 1.0; MinY = 1e-6; MaxY = 2000.0;
		kLogY = false; 
		xTitle =  variable == "tau_0_dijet_eta_centr" ? "leading #tau centrality" : "subleading #tau centrality";
		firstbin = 0; lastbin = 1; nbins = 20; 
		kAdjustLeftBin = false; kAdjustRightBin = false;
		kAutoMaxYaxis = true; AutoOffsetTimes = 1.3;
		
	}else if( variable == "tau_0_BDT_score" || variable == "tau_1_BDT_score"){ 
		
		MinX = 0.5; MaxX = 1.0; MinY = 1e-6; MaxY = 700.0; 
		kLogY = false; 
		xTitle =  variable == "tau_0_BDT_score" ? "leading #tau ID BDT score" : "subleading #tau ID BDT score";
		firstbin = 0; lastbin = 1; nbins = 25; 
		kAdjustLeftBin = false; kAdjustRightBin = false;
		kAutoMaxYaxis = true; AutoOffsetTimes = 2;
		
	}else if( variable == "tau_0_pt" || variable == "tau_1_pt"){ 
		
		MinX = 20; MaxX = 180.0; MinY = 1e-6; MaxY = 500.0;
		if(variable == "tau_0_pt") MinX = 35;
		if(variable == "tau_1_pt") MinX = 25;
		kLogY = false; 
		xTitle =  variable == "tau_0_pt" ? "leading #tau p_{T} [GeV]" : "subleading #tau p_{T} [GeV]";
		firstbin = 0; lastbin = 200; nbins = 40; kAdjustLeftBin = false; kAdjustRightBin = false;
		kAutoMaxYaxis = true; AutoOffsetTimes = 1.7;

		
	}else if( variable == "tau_0_eta" || variable == "tau_1_eta"){ 
		
		MinX = -2.5; MaxX = 2.5; MinY = 1e-6; MaxY = 1000;
		kLogY = false; 
		xTitle =  variable == "tau_0_eta" ? "leading #tau #eta" : "subleading #tau #eta";
		firstbin = -2.5; lastbin = 2.5; nbins = 25; 
		kAdjustLeftBin = false; kAdjustRightBin = false;
		kAutoMaxYaxis = true; AutoOffsetTimes = 1.7;
		
	}else if( variable == "tau_0_phi" || variable == "tau_phi"){ 
		
		MinX = -TMath::Pi(); MaxX = TMath::Pi(); MinY = 1e-6; MaxY = 1000; 
		kLogY = false; 
		xTitle =  variable == "tau_0_phi" ? "leading #tau #phi [rad]" : "subleading #tau #phi [rad]";
		firstbin = -TMath::Pi(); lastbin = TMath::Pi(); nbins = 16; 
		kAdjustLeftBin = false; kAdjustRightBin = false;
		kAutoMaxYaxis = true; AutoOffsetTimes = 1.8;
		
	}else if( variable == "tau_0_tracks" || variable == "tau_1_tracks"){ 
		
		MinX = -0.5; MaxX = 4.5; MinY = 1e-6; MaxY = 5000.0; 
		kLogY = false; 
		xTitle =  variable == "tau_0_tracks" ? "leading #tau N tracks" : "subleading #tau N tracks";
		firstbin = -0.5; lastbin = 4.5; nbins = 5; 
		kAdjustLeftBin = false; kAdjustRightBin = false;
		//xlat = -0.2; 
		xNdivisions=505;
		kAutoMaxYaxis = true; AutoOffsetTimes = 1.5;
		
	}else if(variable == "met_centrality" ){ 
		
		MinX = -1.5; MaxX = 1.5; MinY = 1e-6; MaxY = 900.0;
		kLogY = false; xTitle = "#slash{E}_{T} centrality";
		firstbin = -1.5; lastbin = 1.5; nbins = 15; 
		kAdjustLeftBin = false; kAdjustRightBin = false;
		//xlat = -1.4; 
		kAutoMaxYaxis = true; AutoOffsetTimes = 1.5;
		
	}else if( variable == "dijet_mass"  ){ 
		
		MinX = 20.; MaxX = 750; MinY = 1e-6; MaxY = 500.0; 
		kLogY = false; xTitle = "di-jet mass [GeV]";
		firstbin = 0; lastbin = 1000; nbins = 40; 
		kAdjustLeftBin = false; kAdjustRightBin = false;
		kAutoMaxYaxis = true; AutoOffsetTimes = 1.5;
		
	}else if(variable == "dijet_dEta" ){ 
		
		MinX = 0.; MaxX = 8.0; MinY = 1e-6; MaxY = 400.0; 
		kLogY = false; xTitle = "di-jet #Delta#eta";
		firstbin = 0; lastbin = 10; nbins = 40; 
		kAdjustLeftBin = false; kAdjustRightBin = false;
		kAutoMaxYaxis = true; AutoOffsetTimes = 1.7;
		
	}else if(variable == "dijet_dPhi" ){ 
		
		MinX = 0.; MaxX = TMath::Pi(); MinY = 1e-6; MaxY = 1000.0; 
		kLogY = false; xTitle = "di-jet #Delta#phi";
		firstbin = 0; lastbin = TMath::Pi(); nbins = 16; 
		kAdjustLeftBin = false; kAdjustRightBin = false;
		kAutoMaxYaxis = true; AutoOffsetTimes = 1.9;
		
	}else if(variable == "dijet_eta1_x_eta2" ){ 
		
		MinX = -15.; MaxX = 15.0; MinY = 1e-6; MaxY = 1500.0; 
		kLogY = false; xTitle = "di-jet #eta_{1} #times #eta_{2}";
		firstbin = -15; lastbin = 15; nbins = 30; 
		kAdjustLeftBin = false; kAdjustRightBin = false;
		kAutoMaxYaxis = true; AutoOffsetTimes = 2;
		
	}else if(variable == "met_phi"){ 
		
		MinX = -TMath::Pi(); MaxX = TMath::Pi();
		kLogY = false; xTitle = "E_{T}^{miss} #phi [rad]";
		firstbin = -TMath::Pi(); lastbin = TMath::Pi(); nbins = TMath::TwoPi()/0.4; 
		kAdjustLeftBin = false; kAdjustRightBin = false;
		kAutoMaxYaxis = true; AutoOffsetTimes = 1.8;
		
	}else if(variable == "ditau_cosTheta" ){ 
		
		MinX = -1.05; MaxX = 1.05; MinY = 1e-6; MaxY = 1000.0; 
		kLogY = false; xTitle = "cos#alpha_{#tau#tau}";
		firstbin = -1.05; lastbin = 1.05; nbins = 11; //zero right in the middle
		kAdjustLeftBin = true; kAdjustRightBin = true;
		kAutoMaxYaxis = true; AutoOffsetTimes = 1.5;
		
	}else if(variable == "ditau_mass_vis"){ 
	
		MinX = 20; MaxX = 250; MinY = 1e-6; MaxY = 1000.0; 
		kLogY = false; xTitle = "m^{visible}_{#tau#tau} [GeV]";
		firstbin = 0; lastbin = 400; nbins = 50;  
		kAdjustLeftBin = false; kAdjustRightBin = false;
		kAutoMaxYaxis = true; AutoOffsetTimes = 1.5;
		
	}else if(variable == "ditau_mass_col"){ 
		
		MinX = 0; MaxX = 260; MinY = 1e-6; MaxY = 800.0;
		
		kLogY = false; xTitle = "m^{collinear}_{#tau#tau} [GeV]";
		firstbin = 0; lastbin = 400; nbins = 50;  
		kAdjustLeftBin = false; kAdjustRightBin = false;
		kAutoMaxYaxis = true; AutoOffsetTimes = 1.7;
		
	}else if(variable == "ditau_mass_mmc"){ 
		
		MinX = 0; MaxX = 260; MinY = 1e-6; MaxY = 1000.0; 
		kLogY = false; xTitle = "m^{MMC}_{#tau#tau} [GeV]";
		//firstbin = 0; lastbin = 400; nbins = 80;  //5 GeV
		firstbin = 0; lastbin = 400; nbins = 50;  //8 GeV
		kAdjustLeftBin = false; kAdjustRightBin = true;
		kAutoMaxYaxis = true; AutoOffsetTimes = 1.8;

	}else if(variable == "ditau_pT_0_over_pT_1"){ 
		
		MinX = 1; MaxX = 5; MinY = 1e-6; MaxY = 1000.0; 
		kLogY = false; xTitle = "pT^{1st}_{#tau}/pT^{2nd}_{#tau}";
		firstbin = 1; lastbin = 11; nbins = 25;  
		kAdjustLeftBin = false; kAdjustRightBin = true;
		kAutoMaxYaxis = true; AutoOffsetTimes = 1.5;

	}else if(variable == "jet_0_eta" || variable ==  "jet_1_eta"){ 
		
		MinX = -5; MaxX = 5; MinY = -1e-6; MaxY = 300.0; 
		kLogY = false;  xTitle =  variable == "jet_0_eta" ? "leading jet #eta" : "subleading jet #eta";
		firstbin = -5; lastbin = 5; nbins = 20;  
		kAdjustLeftBin = false; kAdjustRightBin = false;
		kAutoMaxYaxis = true; AutoOffsetTimes = 1.8;
		
	}else if(variable == "jet_0_pt" || variable ==  "jet_1_pt"){

		MinX = 30; MaxX = 310; MinY = -1e-6; MaxY = 1000.0; 
		kLogY = false;  xTitle =  variable == "jet_0_pt" ? "leading jet pT [GeV]" : "subleading jet pT [GeV]";
		firstbin = 10; lastbin = 510; nbins = 50;  
		kAdjustLeftBin = false; kAdjustRightBin = true;
		kAutoMaxYaxis = true; AutoOffsetTimes = 1.7;
		
	}else if(variable == "averageIntPerXing" ){
		MinX = 0; MaxX = 50; MinY = -1e-6; MaxY = 1000.0;
		kLogY = false;  xTitle =  "Mean number of interactions per bunch crossing <#mu>";
		firstbin = 0; lastbin = 100; nbins = 100;  
		kAdjustLeftBin = false; kAdjustRightBin = true;
		kAutoMaxYaxis = true; AutoOffsetTimes = 1.7;
		
	}else if(variable == "ditau_met_VecSumPt"){ 
		
		MinX = 0; MaxX = 200; MinY = 1e-6; MaxY = 1000.0; 
		kLogY = false; xTitle = "pT(#tau^{1st}, #tau^{2nd}, E_{T}^{miss}) [GeV]";
		firstbin = 0; lastbin = 500; nbins = 50;  
		kAdjustLeftBin = false; kAdjustRightBin = true;
		kAutoMaxYaxis = true; AutoOffsetTimes = 1.5;

	}else if(variable == "ditau_dijet_met_VecSumPt"){ 
		
		MinX = 0; MaxX = 150; MinY = 1e-6; MaxY = 1000.0; 
		kLogY = false; xTitle = "#left|#bf{p}_T(#tau^{1st})+#bf{p}_T(#tau^{2nd})+#bf{p}_T(jet^{1st})+#bf{p}_T(jet^{2nd})+#bf{E}_{T}^{miss}#right| [GeV]";
		firstbin = 0; lastbin = 200; nbins = 40;  
		kAdjustLeftBin = false; kAdjustRightBin = true;
		kAutoMaxYaxis = true; AutoOffsetTimes = 1.5;

	}else{
		cout<<"\nPlease, choose a good variable. Exiting ..."<<endl; exit(0);
		
	}
		
	///more specific drawing options - configuration ==============================================
	
	bool 	kWqq_special_treatment = true;
	bool	kQCD_EWK_subtraction 	= true;
	bool	kQCD_Ztautau_subtraction= true;
	bool	kShow_ModelStatSystBandsCombined = true;
	bool	kShow_DataMCRatio_StatSystBandsCombined = false;
	bool	kShow_DataMCRatio_StatSystBandsDecoupled = false;
	bool 	kShow_RelativeStatSystBandsCombined = true;
	bool 	kShow_HorizontalErrorBarsInRatioPlot = false;	
	bool	kShow_RatioLines	= false;
	bool 	kPrintErrors = false;
	bool	ApplyEventWeights	= true;
	int		SignalZoom 			=  10; // times cross-section
	string 	classifier 			= "BDT";
	string 	QCDmodel 			= "notOS";// notOS SS;
	string 	version 			= "v16";
	string	region 				= "CR_preselection";//"CR_preselection";// CR_dEta  CR_QCDrich  CR_Zrich CR_preselection  CR_NoMassCut
	string	purpose 			= "Plot";
	int 	Hmass 				= 125;
	string 	plots_subdir 		= "July8";
	bool 	kShowSignalAlone 	= false;
	bool 	kShowSpectrumWithist_Signal = false;
	bool	kProducePDF					= false;
	bool	kProducePNG					= false;
	bool	kProduceEPS					= false;
	bool	kProduceROOT				= true;	
	double 	RatioMinY			= 0.55; 
	double 	RatioMaxY 			= 1.45; 
	string  HistoFitMethod 		= "TrackFit"; // TrackFit  dEtaFit - in order to pick the right norm value - to set later	
	string  tag					= "test"; // vbf_boosted MMCOver60_QCDnotOS
	
	bool kEmbedding = false; // if false then Z is from alpgen mc

	bool kUseMergedData = true; // true: use one merged root file and save memory
	
	bool kUseMergedEmbedding = true;
	
	bool kUseCommonTrackFitCode = true; // not working at the moment true: use fQCD and fTAU of KG's code

	bool kSyst_JESup 	= false;
	bool kSyst_JESdown 	= false;
	bool kSyst_TESup 	= true;
	bool kSyst_TESdown 	= true;	
	
	bool kNoSystematics = false;
	
	bool kTestVariations = false;
	
	bool kCheckNegativeBinContentAfterSubtraction = false;

	bool kPrintEmptyHistos = false;
	
	string PadBelowXtitle = "#frac{Data}{Model}";
	
	///propagate options to other plotting variables
	

	
	if( kShow_RelativeStatSystBandsCombined){
	  RatioMinY = -0.5;
	  RatioMaxY = 0.5;
	  PadBelowXtitle = "#frac{Data-Model}{Model}";
	  
	}
	
	string Zsample = kEmbedding ? "Embedding" : "MC";
	
	if( variable == "tau_0_tracks" || variable == "tau_1_tracks") QCDmodel = "SS";
	
	string QCD_model_legend = QCDmodel;
	
	string Z_model_legend = Zsample;
	
	bool	kShowData = (region == "SR_MassWindow" && variable == "ditau_mass_mmc") ? false : true; 
	string 	hmass 				= hc.GetStringFromInt(Hmass);
	string  filenamecore		= "plots/"+plots_subdir+"/plot_"+variable+"_categ_"+category+"_H_"+hmass+"_Z_"+Zsample+"_"+region+"_QCD_"+QCDmodel+"_"+NormMethod+"_"+version;
	string 	fn 					= filenamecore+".root";
	string 	fn_pdf 				= filenamecore+".pdf";
	string 	fn_png 				= filenamecore+".png";
	string 	fn_eps 				= filenamecore+".eps";
	
	if(kNoSystematics){
		kSyst_JESup = false;
		kSyst_JESdown = false;
		kSyst_TESup = false;
		kSyst_TESdown = false;
	}
			
	///how to obtain ntuples=====================================================================================
	hc.SetTreeName("mva"); 
	hc.SetVersion(version); 
	hc.SetPath("../../TreeMaker");
	//hc.SetPath("../../Ntuples/");

	///list of MC samples=======================================================================================
	vector<int> RunsVector = hc.GetRunsVector(Hmass);
	
	///data tree==================================================================================================
	cout<<"\ncreating tree map for data ..."<<endl;
	double DataLumi (0);
	TTree *tData;
	
	if(variable == "BDT_Weight"){
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
	
	if(!tData) {cout<<"unable to get data tree"<<endl; exit(0); }
	
	hc.SetLumiPerRunMap();
	
	int nDataEntries = tData->GetEntries();
	if(!nDataEntries) {cout<<"unable to get data tree entries ("<<nDataEntries<<"). Exiting... "<<endl; exit(0); }
	
	///lumi calculation run-per-run ==============================================================================
	cout<<"\nActual data lumi "<<DataLumi<<" nb-1"<<endl<<endl;
	double lumi_fb = DataLumi/1e6;
	char lumi_number[24];
	sprintf(lumi_number, "%.2f", lumi_fb);
	string lumi_str = lumi_number;
	
	///embedding Z tau tau sample =================================================================================
	TTree *tEmbedding;
	TTree *tEmbedding_TESup;
	TTree *tEmbedding_TESdown;
	
	if(kEmbedding){

	  if(variable == "BDT_Weight") {
		cout<<"missing - exiting"<<endl; exit(0);
		
	  }else{
		
		cout<<"\ncreating tree map for Z embedding - NOMINAL"<<endl;
		if(kUseMergedEmbedding)
		  tEmbedding = hc.GetTreeEmbeddingMerged( "" );
		else
		  tEmbedding = hc.GetTreeEmbedding( "" );
		
		if(!tEmbedding){
		  cerr<<"\tNull tree... Exiting"<<endl; exit(0);
		}else{
		  cout<<"\tZ embedding tree entries - NOMINAL "<<tEmbedding->GetEntries()<<endl;
		}
		
		if(kSyst_TESup){
		  cout<<"\ncreating tree map for Z embedding - TESup"<<endl;
		  if(kUseMergedEmbedding)
			tEmbedding_TESup = hc.GetTreeEmbeddingMerged( "TESup" );
		  else
			tEmbedding_TESup = hc.GetTreeEmbedding( "TESup" );
		  
		  if(!tEmbedding_TESup){
			cerr<<"\tNull tree... Exiting"<<endl; exit(0);
		  }else{
			cout<<"\tZ embedding tree entries - TESup "<<tEmbedding_TESup->GetEntries()<<endl;
		  }
		}
		
		if(kSyst_TESdown){
		  cout<<"\ncreating tree map for Z embedding - TESdown"<<endl;
		  if(kUseMergedEmbedding)
			tEmbedding_TESdown = hc.GetTreeEmbeddingMerged( "TESdown" );
		  else
			tEmbedding_TESdown = hc.GetTreeEmbedding("TESdown" );
		  
		  if(!tEmbedding_TESdown){
			cerr<<"\tNull tree... Exiting"<<endl; exit(0);
		  }else{
			cout<<"\tZ embedding tree entries - TESdown "<<tEmbedding_TESdown->GetEntries()<<endl;
		  }
		}
		
	  }//plotting variable
	  
	  
	}//emb
	
	/// mc tree map ==============================================================================================
	map<int, TTree *> tmap;
	map<int, TTree *> tmap_JESup;
	map<int, TTree *> tmap_JESdown;
	map<int, TTree *> tmap_TESup;
	map<int, TTree *> tmap_TESdown;
	
	cout<<"\ncreating tree map for mc ..."<<endl;
	for(vector<int>::iterator it=RunsVector.begin(); it != RunsVector.end(); it++){
		if( *it >= 800000) continue;
		
		if(variable == "BDT_Weight"){
		  tmap.insert ( pair<int, TTree *>(*it,  hc.GetTreeMCMVA( hc.GetStringFromInt(*it), classifier, category_file, hmass, tag) ) );//katy
		  
		}else{
		  tmap.insert ( pair<int, TTree *>(*it,  hc.GetTreeMC(hc.GetStringFromInt(*it)) ) );
		  
		  if(kSyst_JESup) 	tmap_JESup.insert ( 	pair<int, TTree *>(*it,  hc.GetTreeMC(hc.GetStringFromInt(*it), "JESup") ) );		
		  if(kSyst_JESdown) tmap_JESdown.insert ( 	pair<int, TTree *>(*it,  hc.GetTreeMC(hc.GetStringFromInt(*it), "JESdown") ) );		
		  if(kSyst_TESup) 	tmap_TESup.insert ( 	pair<int, TTree *>(*it,  hc.GetTreeMC(hc.GetStringFromInt(*it), "TESup") ) );		
		  if(kSyst_TESdown) tmap_TESdown.insert ( 	pair<int, TTree *>(*it,  hc.GetTreeMC(hc.GetStringFromInt(*it), "TESdown") ) );
		}
		
	}
	cout<<"  MC trees "<<tmap.size()<<endl;
	if(kSyst_JESup) 	cout<<"  MC tree size JEsup "<<tmap_JESup.size()<<endl;
	if(kSyst_JESdown) 	cout<<"  MC tree size JESdown "<<tmap_JESdown.size()<<endl;
	if(kSyst_TESup) 	cout<<"  MC tree sise TESup "<<tmap_TESup.size()<<endl;
	if(kSyst_TESdown) 	cout<<"  MC tree size TESdown "<<tmap_TESdown.size()<<endl;
	
	///histogramming ===========================================================================================
	cout<<"\nbooking histograms ..."<<endl;
	double BinW = (lastbin - firstbin)/nbins;
	cout<<"\nbin width : "<<BinW<<endl;
	cout<<"\nlimits  : "<<firstbin<<"  "<<lastbin<<endl;
	
	//data - systematics-independent 
	TH1D *hist_Data = new TH1D("hist_Data",	"",	nbins, firstbin, lastbin);
	TH1D *hist_Data_HistoFit = new TH1D("hist_Data_HistoFit",	"",	nbins, firstbin, lastbin);
		
	//nominal
	TH1D *hist_QCD			= new TH1D("hist_QCD",	"",		nbins, firstbin, lastbin);
	TH1D *hist_Signal 		= new TH1D("hist_Signal","",	nbins, firstbin, lastbin);
	TH1D *hist_Z 			= new TH1D("hist_Z",	"",		nbins, firstbin, lastbin);
	TH1D *hist_Z_subtr 		= new TH1D("hist_Z_subtr",	"",	nbins, firstbin, lastbin);
	TH1D *hist_Z_Emb		= new TH1D("hist_Z_Emb",	"",		nbins, firstbin, lastbin);
	TH1D *hist_Z_Emb_subtr 	= new TH1D("hist_Z_Emb_subtr",	"",	nbins, firstbin, lastbin);
	TH1D *hist_Spectrum0 	= new TH1D("hist_Spectrum0","",	nbins, firstbin, lastbin);
	TH1D *hist_Spectrum1 	= new TH1D("hist_Spectrum1","",	nbins, firstbin, lastbin);
	TH1D *hist_Spectrum2 	= new TH1D("hist_Spectrum2","",	nbins, firstbin, lastbin);
	TH1D *hist_Spectrum3 	= new TH1D("hist_Spectrum3","",	nbins, firstbin, lastbin);
	TH1D *hist_BKG 			= new TH1D("hist_BKG",	"",		nbins, firstbin, lastbin);

	TH1D *hist_Z_norm_to_1 	= new TH1D("hist_Z_norm_to_1",	"",		nbins, firstbin, lastbin);
	
	//JES up
	TH1D *hist_JESup_QCD		= new TH1D("hist_JESup_QCD",	"",	nbins, firstbin, lastbin);
	TH1D *hist_JESup_Signal 	= new TH1D("hist_JESup_Signal","",	nbins, firstbin, lastbin);
	TH1D *hist_JESup_BKG 		= new TH1D("hist_JESup_BKG",	"",	nbins, firstbin, lastbin);
	
	//JES down
	TH1D *hist_JESdown_QCD		= new TH1D("hist_JESdown_QCD",	"",	nbins, firstbin, lastbin);
	TH1D *hist_JESdown_Signal 	= new TH1D("hist_JESdown_Signal","",	nbins, firstbin, lastbin);
	TH1D *hist_JESdown_BKG 		= new TH1D("hist_JESdown_BKG",	"",	nbins, firstbin, lastbin);
	
	//TES up
	TH1D *hist_TESup_QCD		= new TH1D("hist_TESup_QCD",	"",	nbins, firstbin, lastbin);
	TH1D *hist_TESup_Signal 	= new TH1D("hist_TESup_Signal","",	nbins, firstbin, lastbin);
	TH1D *hist_TESup_BKG 		= new TH1D("hist_TESup_BKG",	"",	nbins, firstbin, lastbin);
	TH1D *hist_TESup_Z	 		= new TH1D("hist_TESup_Z",	"",	nbins, firstbin, lastbin);
	TH1D *hist_TESup_Z_subtr	= new TH1D("hist_TESup_Z_subtr",	"",	nbins, firstbin, lastbin);
	TH1D *hist_TESup_Z_Emb		= new TH1D("hist_TESup_Z_Emb",	"",		nbins, firstbin, lastbin);
	TH1D *hist_TESup_Z_Emb_subtr = new TH1D("hist_TESup_Z_Emb_subtr",	"",		nbins, firstbin, lastbin);
	
	//TES down
	TH1D *hist_TESdown_QCD		= new TH1D("hist_TESdown_QCD",	"",	nbins, firstbin, lastbin);
	TH1D *hist_TESdown_Signal 	= new TH1D("hist_TESdown_Signal","",	nbins, firstbin, lastbin);
	TH1D *hist_TESdown_BKG 		= new TH1D("hist_TESdown_BKG",	"",	nbins, firstbin, lastbin);
	TH1D *hist_TESdown_Z 		= new TH1D("hist_TESdown_Z",	"",	nbins, firstbin, lastbin);
	TH1D *hist_TESdown_Z_subtr 	= new TH1D("hist_TESdown_Z_subtr",	"",	nbins, firstbin, lastbin);
	TH1D *hist_TESdown_Z_Emb 	= new TH1D("hist_TESdown_Z_Emb",	"",	nbins, firstbin, lastbin);
	TH1D *hist_TESdown_Z_Emb_subtr 	= new TH1D("hist_TESdown_Z_Emb_subtr",	"",	nbins, firstbin, lastbin);
	
	//histo maps for MC
	map<int, TH1D *> hmap_Sig;
	map<int, TH1D *> hmap_Bkg;
	
	map<int, TH1D *> hmap_JESup_Sig;
	map<int, TH1D *> hmap_JESup_Bkg;
	
	map<int, TH1D *> hmap_JESdown_Sig;
	map<int, TH1D *> hmap_JESdown_Bkg;
	
	map<int, TH1D *> hmap_TESup_Sig;
	map<int, TH1D *> hmap_TESup_Bkg;
	
	map<int, TH1D *> hmap_TESdown_Sig;
	map<int, TH1D *> hmap_TESdown_Bkg;
	
	//fill maps with empty histograms for each sample
	for(vector<int>::iterator it=RunsVector.begin(); it != RunsVector.end(); it++){
		hmap_Sig.insert ( pair<int,TH1D *>(*it, new  TH1D("",	"",	nbins, firstbin, lastbin)) );
		hmap_Bkg.insert ( pair<int,TH1D *>(*it, new  TH1D("",	"",	nbins, firstbin, lastbin)) );
		
		if(kSyst_JESup){
			hmap_JESup_Sig.insert ( pair<int,TH1D *>(*it, new  TH1D("",	"",	nbins, firstbin, lastbin)) );
			hmap_JESup_Bkg.insert ( pair<int,TH1D *>(*it, new  TH1D("",	"",	nbins, firstbin, lastbin)) );
		}
		
		if(kSyst_JESdown){
			hmap_JESdown_Sig.insert ( pair<int,TH1D *>(*it, new  TH1D("",	"",	nbins, firstbin, lastbin)) );
			hmap_JESdown_Bkg.insert ( pair<int,TH1D *>(*it, new  TH1D("",	"",	nbins, firstbin, lastbin)) );
		}
		
		if(kSyst_TESup){
			hmap_TESup_Sig.insert ( pair<int,TH1D *>(*it, new  TH1D("",	"",	nbins, firstbin, lastbin)) );
			hmap_TESup_Bkg.insert ( pair<int,TH1D *>(*it, new  TH1D("",	"",	nbins, firstbin, lastbin)) );
		}
		
		if(kSyst_TESdown){
			hmap_TESdown_Sig.insert ( pair<int,TH1D *>(*it, new  TH1D("",	"",	nbins, firstbin, lastbin)) );
			hmap_TESdown_Bkg.insert ( pair<int,TH1D *>(*it, new  TH1D("",	"",	nbins, firstbin, lastbin)) );
		}
	}
	
	/// name histos===========================================================================================
	TCut hweight("");
	if (ApplyEventWeights){
		hweight = "event_weight";
		cout<<"\nincluding event weights : "<<hweight<<endl;
	}
	
	cout<<"\nrenaming plots ..."<<endl;
	hc.SetHistoNames1D(hmap_Sig, "OS");
	hc.SetHistoNames1D(hmap_Bkg, QCDmodel);

// 	hc.SetHistoNames1D(hmap_JESup_Sig, "OS_JESup");
// 	hc.SetHistoNames1D(hmap_JESup_Bkg, QCDmodel+"_JESup");
// 	
// 	hc.SetHistoNames1D(hmap_JESdown_Sig, "OS_JESdown");
// 	hc.SetHistoNames1D(hmap_JESdown_Bkg, QCDmodel+"_JESdown");
// 	
	hc.SetHistoNames1D(hmap_TESup_Sig, "OS_TESup");
	hc.SetHistoNames1D(hmap_TESup_Bkg, QCDmodel+"_TESup");
	
	hc.SetHistoNames1D(hmap_TESdown_Sig, "OS_TESdown");
	hc.SetHistoNames1D(hmap_TESdown_Bkg, QCDmodel+"_TESdown");
	
	///plot making=============================================================================================
	cout<<"\nCuts for search region : \n"<<hweight * hc.GetCut(category, "OS", purpose,region).GetTitle()<<endl;
	
	cout<<"\nCuts for QCD bkg : \n"<<hc.GetCut(category, QCDmodel, purpose,region).GetTitle()<<endl;

	cout<<"\nfilling histograms ..."<<endl;
	
	/// -- data
	cout<<"->data (takes some time) ..."<<endl;
	hc.MakePlot( tData, hist_Data,  hc.GetCut(category, "OS", purpose, region), variable );
	cout<<"\thist_Data integral: "<<hist_Data->Integral()<<endl;
	
	/// -- data - Histo Fit and QCD normalization
	cout<<"-->data histo-fit"<<endl;
	hc.MakePlot( tData, hist_Data_HistoFit,  hc.GetCut(category, "OS", HistoFitMethod, region), variable );
	cout<<"\thisto fit area: "<<hist_Data_HistoFit->Integral()<<endl;
	
	/// -- QCD from data
	cout<<"-->QCD"<<endl;
	hc.MakePlot( tData, hist_QCD,  hc.GetCut(category, QCDmodel, purpose, region), variable );
	cout<<"\tQCD area: "<<hist_QCD->Integral()<<endl;
	if(kSyst_TESup) hist_TESup_QCD->Add(hist_QCD, 1);
	if(kSyst_TESdown) hist_TESdown_QCD->Add(hist_QCD, 1);
	
	/// -- embedding
	if(kEmbedding){
	  cout<<"-->embedding"<<endl;
	  
	  ///search region
	  hc.MakePlot( tEmbedding, hist_Z_Emb, hweight * hc.GetCut(category, "OS", purpose, region), variable );
	  cout<<"\temb area - NOMINAL: "<< hist_Z_Emb->Integral()<<endl;
	  ///for subtraction
	  hc.MakePlot( tEmbedding, hist_Z_Emb_subtr, hweight * hc.GetCut(category, QCDmodel, purpose, region), variable );
	  cout<<"\temb for subtr area - NOMINAL: "<< hist_Z_Emb_subtr->Integral()<<endl;
	  
	  if(kSyst_TESup){
		///search region
		hc.MakePlot( tEmbedding_TESup, hist_TESup_Z_Emb, hweight * hc.GetCut(category, "OS", purpose, region), variable );
		cout<<"\temb area - TESup: "<< hist_TESup_Z_Emb->Integral()<<endl;
		///for subtraction
		hc.MakePlot( tEmbedding_TESup, hist_TESup_Z_Emb_subtr, hweight * hc.GetCut(category, QCDmodel, purpose, region), variable );
		cout<<"\temb for subtr area - TESup: "<< hist_TESup_Z_Emb_subtr->Integral()<<endl;
	  }
	  
	  if(kSyst_TESdown){
		///search region
		hc.MakePlot( tEmbedding_TESdown, hist_TESdown_Z_Emb, hweight * hc.GetCut(category, "OS", purpose, region), variable );
		cout<<"\temb area - TESdown: "<< hist_TESdown_Z_Emb->Integral()<<endl;
		///for subtraction
		hc.MakePlot( tEmbedding_TESdown, hist_TESdown_Z_Emb_subtr, hweight * hc.GetCut(category, QCDmodel, purpose, region), variable );
		cout<<"\temb for subtr area - TESdown: "<< hist_TESdown_Z_Emb_subtr->Integral()<<endl;
	  }
// TCut tmp1 = "(event_weight)*((((((((((((((((((grl)&&(ditau_ok))&&(tau_0_pt > 35.))&&(tau_1_pt > 25.))&&(MMC_ok))&&(MMC_resonance_m > 0))&&(ditau_overlap_removal_ok))&&(ditau_same_vertex))&&(ditau_met_bisect==1 || ditau_met_out_min_dPhi<0.5*3.1415))&&(met_et > 20.0))&&(ditau_dR > 0.8 && ditau_dR < 2.8))&&(ditau_dEta < 1.5))&&(tau_0_BDT_medium))&&(tau_1_BDT_medium))&&(tau_0_BDT_tight || tau_1_BDT_tight))&&(ditau_OS))&&((((tau_0_tracks ==1 ||tau_0_tracks ==3)&&(tau_1_tracks ==1 ||tau_1_tracks ==3))&&(1))&&(1)))&&(ditau_mass_mmc > 0))";
// TCut tmp2 = "(event_weight)*((((((((((((((((((grl)&&(ditau_ok))&&(tau_0_pt > 35.))&&(tau_1_pt > 25.))&&(MMC_ok))&&(MMC_resonance_m > 0))&&(ditau_overlap_removal_ok))&&(ditau_same_vertex))&&(ditau_met_bisect==1 || ditau_met_out_min_dPhi<0.5*3.1415))&&(met_et > 20.0))&&(ditau_dR > 0.8 && ditau_dR < 2.8))&&(ditau_dEta < 1.5))&&(tau_0_BDT_medium))&&(tau_1_BDT_medium))&&(tau_0_BDT_tight || tau_1_BDT_tight))&&(ditau_notOS))&&((((1)&&(1))&&(1))&&(1)))&&(ditau_mass_mmc > 0))";
// hc.MakePlot( tEmbedding, hist_Z_Emb, tmp1, variable );
// 	  cout<<"\temb area: "<< hist_Z_Emb->Integral()<<endl;
// 	  ///for subtractuion
// 	  hc.MakePlot( tEmbedding, hist_Z_Emb_subtr, tmp2, variable );
// 	  cout<<"\temb for subtr area: "<< hist_Z_Emb_subtr->Integral()<<endl;
	  
	}
	
	
	/// -- MC search region - nominal
	cout<<"-->MC SR"<<endl;
	for(map<int, TH1D *>::iterator it = hmap_Sig.begin(); it != hmap_Sig.end(); it++){
		if(it->first < 800000){
			TCut c = "";
			if(kWqq_special_treatment) 
			  if( it->first >= 169547 && it->first <= 169549 ) {c += "ditau_at_least_one_truth"; cout<<"Wqq "<<it->first<<endl;}
			  
			hc.MakePlot(tmap[it->first], it->second, hweight * hc.GetCut(category, "OS", purpose, region) * c, variable );	
		}
	}

	/// -- MC search region  - JESup
	if(kSyst_JESup) {
		cout<<"  MC SR JESup"<<endl;
		for(map<int, TH1D *>::iterator it = hmap_JESup_Sig.begin(); it != hmap_JESup_Sig.end(); it++){
			if(it->first < 800000)
				hc.MakePlot(tmap_JESup[it->first], it->second, hweight * hc.GetCut(category, "OS", purpose, region), variable );	
		}
	}
	
	/// -- MC search region  - JESdown
	if(kSyst_JESdown) {
		cout<<"  MC SR JESdown"<<endl;
		for(map<int, TH1D *>::iterator it = hmap_JESdown_Sig.begin(); it != hmap_JESdown_Sig.end(); it++){
			if(it->first < 800000)
				hc.MakePlot(tmap_JESdown[it->first], it->second, hweight * hc.GetCut(category, "OS", purpose, region), variable );	
		}
	}
	
	/// -- MC search region  - TESup
	if(kSyst_TESup) {
		cout<<"  MC SR TESup"<<endl;
		for(map<int, TH1D *>::iterator it = hmap_TESup_Sig.begin(); it != hmap_TESup_Sig.end(); it++){
			if(it->first < 800000)
				hc.MakePlot(tmap_TESup[it->first], it->second, hweight * hc.GetCut(category, "OS", purpose, region), variable );	
		}
	}
	
	/// -- MC search region  - TESdown
	if(kSyst_TESdown) {
		cout<<"  MC SR TESdown"<<endl;
		for(map<int, TH1D *>::iterator it = hmap_TESdown_Sig.begin(); it != hmap_TESdown_Sig.end(); it++){
			if(it->first < 800000)
				hc.MakePlot(tmap_TESdown[it->first], it->second, hweight * hc.GetCut(category, "OS", purpose, region), variable );	
		}
	}
	
	
	/// -- MC bkg model for bkg subtraction - nominal
	for(map<int, TH1D *>::iterator it = hmap_Bkg.begin(); it != hmap_Bkg.end(); it++){
		if(it->first < 800000)
			hc.MakePlot(tmap[it->first], it->second, hweight * hc.GetCut(category, QCDmodel, purpose, region), variable );
	}
	
	/// -- MC bkg model for bkg subtraction  - JESup
	if(kSyst_JESup) {
		cout<<"  MC bkg JESup"<<endl;
		for(map<int, TH1D *>::iterator it = hmap_JESup_Bkg.begin(); it != hmap_JESup_Bkg.end(); it++){
			if(it->first < 800000)
				hc.MakePlot(tmap_JESup[it->first], it->second, hweight * hc.GetCut(category, QCDmodel, purpose, region), variable );
		}
	}
	
	/// -- MC bkg model for bkg subtraction  - JESdown
	if(kSyst_JESdown) {
		cout<<"  MC bkg JESdown"<<endl;
		for(map<int, TH1D *>::iterator it = hmap_JESdown_Bkg.begin(); it != hmap_JESdown_Bkg.end(); it++){
			if(it->first < 800000)
				hc.MakePlot(tmap_JESdown[it->first], it->second, hweight * hc.GetCut(category, QCDmodel, purpose, region), variable );
		}
	}
	
	/// -- MC bkg model for bkg subtraction  - TESup
	if(kSyst_TESup) {
		cout<<"  MC bkg TESup"<<endl;
		for(map<int, TH1D *>::iterator it = hmap_TESup_Bkg.begin(); it != hmap_TESup_Bkg.end(); it++){
			if(it->first < 800000)
				hc.MakePlot(tmap_TESup[it->first], it->second, hweight * hc.GetCut(category, QCDmodel, purpose, region), variable );
		}
	}
	
	/// -- MC bkg model for bkg subtraction  - TESdown
	if(kSyst_TESdown) {
		cout<<"  MC bkg TESdown"<<endl;
		for(map<int, TH1D *>::iterator it = hmap_TESdown_Bkg.begin(); it != hmap_TESdown_Bkg.end(); it++){
			if(it->first < 800000)
				hc.MakePlot(tmap_TESdown[it->first], it->second, hweight * hc.GetCut(category, QCDmodel, purpose, region), variable );
		}
	}
	
	/// special treatment: normalize mu data
	if(variable == "averageIntPerXing" ){
		hist_Data->Scale(1.0/1.1);
	}
	
	///normalize all MC to data lumi ==========================================================================================
	cout<<"\nhistograms normalization"<<endl;
	
	///normalize signal
	cout<<"  signal"<<endl;
	for(map<int, TH1D *>::iterator it = hmap_Sig.begin(); it != hmap_Sig.end(); it++){
		if(it->first < 800000){
			it->second->Scale( mcbank.Get_Norm(it->first, DataLumi) );
		}
	}
	
	///normalize signal  - JESup
	if(kSyst_JESup) {
		cout<<"  signal JESup"<<endl;
		for(map<int, TH1D *>::iterator it = hmap_JESup_Sig.begin(); it != hmap_JESup_Sig.end(); it++){
			if(it->first < 800000){
				it->second->Scale( mcbank.Get_Norm(it->first, DataLumi) );
			}
		}
	}
	
		///normalize signal  - JESdown
	if(kSyst_JESdown) {
		cout<<"  signal JESdown"<<endl;
		for(map<int, TH1D *>::iterator it = hmap_JESdown_Sig.begin(); it != hmap_JESdown_Sig.end(); it++){
			if(it->first < 800000){
				it->second->Scale( mcbank.Get_Norm(it->first, DataLumi) );
			}
		}
	}
	
	///normalize signal  - TESup
	if(kSyst_TESup) {
		cout<<"  signal TESup"<<endl;
		for(map<int, TH1D *>::iterator it = hmap_TESup_Sig.begin(); it != hmap_TESup_Sig.end(); it++){
			if(it->first < 800000){
				it->second->Scale( mcbank.Get_Norm(it->first, DataLumi) );
			}
		}
	}
	
	///normalize signal  - TESdown
	if(kSyst_TESdown) {
		cout<<"  signal TESdown"<<endl;
		for(map<int, TH1D *>::iterator it = hmap_TESdown_Sig.begin(); it != hmap_TESdown_Sig.end(); it++){
			if(it->first < 800000){
				it->second->Scale( mcbank.Get_Norm(it->first, DataLumi) );
			}
		}
	}
	
	///normalize bkg
	cout<<"  bkg"<<endl;
	for(map<int, TH1D *>::iterator it = hmap_Bkg.begin(); it != hmap_Bkg.end(); it++){
		if(it->first < 800000){
			it->second->Scale( mcbank.Get_Norm(it->first, DataLumi) );
		}
	}
	
	///normalize bkg JESup
	if(kSyst_JESup) {
		cout<<"  bkg JESup"<<endl;
		for(map<int, TH1D *>::iterator it = hmap_JESup_Bkg.begin(); it != hmap_JESup_Bkg.end(); it++){
			if(it->first < 800000){
				it->second->Scale( mcbank.Get_Norm(it->first, DataLumi) );
			}
		}
	}
	
	///normalize bkg JESdown
	if(kSyst_JESdown) {
		cout<<"  bkg JESdown"<<endl;
		for(map<int, TH1D *>::iterator it = hmap_JESdown_Bkg.begin(); it != hmap_JESdown_Bkg.end(); it++){
			if(it->first < 800000){
				it->second->Scale( mcbank.Get_Norm(it->first, DataLumi) );
			}
		}
	}
	
	///normalize bkg TESup
	if(kSyst_TESup) {
		cout<<"  bkg TESup"<<endl;
		for(map<int, TH1D *>::iterator it = hmap_TESup_Bkg.begin(); it != hmap_TESup_Bkg.end(); it++){
			if(it->first < 800000){
				it->second->Scale( mcbank.Get_Norm(it->first, DataLumi) );
			}
		}
	}
	
	///normalize bkg TESdown
	if(kSyst_TESdown) {
		cout<<"  bkg TESdown"<<endl;
		for(map<int, TH1D *>::iterator it = hmap_TESdown_Bkg.begin(); it != hmap_TESdown_Bkg.end(); it++){
			if(it->first < 800000){
				it->second->Scale( mcbank.Get_Norm(it->first, DataLumi) );
			}
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
		
			//JESup
			if(kSyst_JESup){
				if(! hmap_JESup_Sig[*it]->GetEntries() )  cout<<"empty signal histogram  - JESup: "<<*it<<endl;
				if(! hmap_JESup_Bkg[*it]->GetEntries() )  cout<<"empty bkg histogram  - JESup: "<<*it<<endl;
			}
			
			//JESdown
			if(kSyst_JESdown){
				if(! hmap_JESdown_Sig[*it]->GetEntries() )  cout<<"empty signal histogram  - JESdown: "<<*it<<endl;
				if(! hmap_JESdown_Bkg[*it]->GetEntries() )  cout<<"empty bkg histogram  - JESdown: "<<*it<<endl;
			}
			
			//TESup
			if(kSyst_TESup){
				if(! hmap_TESup_Sig[*it]->GetEntries() )  cout<<"empty signal histogram  - TESup: "<<*it<<endl;
				if(! hmap_TESup_Bkg[*it]->GetEntries() )  cout<<"empty bkg histogram  - TESup: "<<*it<<endl;
			}
			
			//TESdown
			if(kSyst_TESdown){
				if(! hmap_TESdown_Sig[*it]->GetEntries() )  cout<<"empty signal histogram  - TESdown: "<<*it<<endl;
				if(! hmap_TESdown_Bkg[*it]->GetEntries() )  cout<<"empty bkg histogram  - TESdown: "<<*it<<endl;
			}
		}
		
		int mcn(0);	
		if( hc.Is("Higgs", *it)  ) { mcn = 800000;

			hmap_Sig[mcn]->Add( hmap_Sig[*it]); 
			hmap_Bkg[mcn]->Add( hmap_Bkg[*it]);
			
			//JESup
			if(kSyst_JESup) {
				hmap_JESup_Sig[mcn]->Add( hmap_JESup_Sig[*it]); 
				hmap_JESup_Bkg[mcn]->Add( hmap_JESup_Bkg[*it]);
			}
			
			//JESdown
			if(kSyst_JESdown) {
				hmap_JESdown_Sig[mcn]->Add( hmap_JESdown_Sig[*it]); 
				hmap_JESdown_Bkg[mcn]->Add( hmap_JESdown_Bkg[*it]);
			}
			
			//TESup
			if(kSyst_TESup) {
				hmap_TESup_Sig[mcn]->Add( hmap_TESup_Sig[*it]); 
				hmap_TESup_Bkg[mcn]->Add( hmap_TESup_Bkg[*it]);
			}
			
			//TESdown
			if(kSyst_TESdown) {
				hmap_TESdown_Sig[mcn]->Add( hmap_TESdown_Sig[*it]); 
				hmap_TESdown_Bkg[mcn]->Add( hmap_TESdown_Bkg[*it]);
			}
		}
		
		if( hc.Is("Ztautau", *it)  ) { mcn = 800001;

			hmap_Sig[mcn]->Add( hmap_Sig[*it]); 
			hmap_Bkg[mcn]->Add( hmap_Bkg[*it]);
			
			//JESup
			if(kSyst_JESup) {
				hmap_JESup_Sig[mcn]->Add( hmap_JESup_Sig[*it]); 
				hmap_JESup_Bkg[mcn]->Add( hmap_JESup_Bkg[*it]);
			}
			
			//JESdown
			if(kSyst_JESdown) {
				hmap_JESdown_Sig[mcn]->Add( hmap_JESdown_Sig[*it]); 
				hmap_JESdown_Bkg[mcn]->Add( hmap_JESdown_Bkg[*it]);
			}
			
			//TESup
			if(kSyst_TESup) {
				hmap_TESup_Sig[mcn]->Add( hmap_TESup_Sig[*it]); 
				hmap_TESup_Bkg[mcn]->Add( hmap_TESup_Bkg[*it]);
			}
			
			//TESdown
			if(kSyst_TESdown) {
				hmap_TESdown_Sig[mcn]->Add( hmap_TESdown_Sig[*it]); 
				hmap_TESdown_Bkg[mcn]->Add( hmap_TESdown_Bkg[*it]);
			}
		}
		
		if( hc.Is("Electroweak", *it)  ) { mcn = 800005;

			hmap_Sig[mcn]->Add( hmap_Sig[*it]); 
			hmap_Bkg[mcn]->Add( hmap_Bkg[*it]);
			
			//JESup
			if(kSyst_JESup) {
				hmap_JESup_Sig[mcn]->Add( hmap_JESup_Sig[*it]); 
				hmap_JESup_Bkg[mcn]->Add( hmap_JESup_Bkg[*it]);
			}
			
			//JESdown
			if(kSyst_JESdown) {
				hmap_JESdown_Sig[mcn]->Add( hmap_JESdown_Sig[*it]); 
				hmap_JESdown_Bkg[mcn]->Add( hmap_JESdown_Bkg[*it]);
			}
			
			//TESup
			if(kSyst_TESup) {
				hmap_TESup_Sig[mcn]->Add( hmap_TESup_Sig[*it]); 
				hmap_TESup_Bkg[mcn]->Add( hmap_TESup_Bkg[*it]);
			}
			
			//TESdown
			if(kSyst_TESdown) {
				hmap_TESdown_Sig[mcn]->Add( hmap_TESdown_Sig[*it]); 
				hmap_TESdown_Bkg[mcn]->Add( hmap_TESdown_Bkg[*it]);
			}
		}
		
		
		
	}//loop over mc samples


	
	///Decide which is going to be the Z sample =================================================================================
	if(kEmbedding){
	  cout<<"\nZ is from Embedding"<<endl;
	  
	  cout<<"\ncreating Z NOMINAL histos ..."<<endl;
	  hist_Z->Add( hist_Z_Emb, 1 );
	  hist_Z_subtr->Add(hist_Z_Emb_subtr , 1 );
	  
	  if(kSyst_TESup){
		cout<<"\nsetting Z Embedding TES UP histos ..."<<endl;
		hist_TESup_Z->Add( hist_TESup_Z_Emb, 1);
		hist_TESup_Z_subtr->Add( hist_TESup_Z_Emb_subtr, 1);
	  }
	  
	  if(kSyst_TESdown){
		cout<<"\nsetting Z Embedding TES DOWN histos ..."<<endl;
		hist_TESup_Z->Add( hist_TESup_Z_Emb, 1);
		hist_TESup_Z_subtr->Add( hist_TESup_Z_Emb_subtr, 1);
	  }
	  
	  
	}else {
	  cout<<"\nZ is from MC"<<endl;
	  
	  cout<<"\ncreating Z NOMINAL histos ..."<<endl;
	  hist_Z->Add( hmap_Sig[800001], 1 );
	  hist_Z_subtr->Add(hmap_Bkg[800001], 1 );
	  
	  if(kSyst_TESup){
		cout<<"\nsetting Z TES UP histos ..."<<endl;
		hist_TESup_Z->Add( hmap_TESup_Sig[800001], 1);
		hist_TESup_Z_subtr->Add( hmap_TESup_Bkg[800001], 1);

	  }
	  
	  if(kSyst_TESdown){
		cout<<"\nsetting Z TES DOWN histos ..."<<endl;
		hist_TESdown_Z->Add( hmap_TESdown_Sig[800001], 1);
		hist_TESdown_Z_subtr->Add( hmap_TESdown_Bkg[800001], 1);
	  }
	  
	  
	}
	
	cout<<"Z histograms"<<endl;
	cout<<"\tZ : entries, area "<<hist_Z->GetEntries()<<", "<<hist_Z->Integral()<<endl;
	cout<<"\tZ subtr : entries, area "<<hist_Z_subtr->GetEntries()<<", "<<hist_Z_subtr->Integral()<<endl;
	
	if(kSyst_TESup){
	  cout<<"\tZ TES UP: entries, area "<<hist_TESup_Z->GetEntries()<<", "<<hist_TESup_Z->Integral()<<endl;
	  cout<<"\tZ TES UP subtr : entries, area "<<hist_TESup_Z_subtr->GetEntries()<<", "<<hist_TESup_Z_subtr->Integral()<<endl;
	}
	
	if(kSyst_TESdown){
	  cout<<"\tZ TES DOWN: entries, area "<<hist_TESdown_Z->GetEntries()<<", "<<hist_TESdown_Z->Integral()<<endl;
	  cout<<"\tZ TES DOWN subtr : entries, area "<<hist_TESdown_Z_subtr->GetEntries()<<", "<<hist_TESdown_Z_subtr->Integral()<<endl;
	}
	
	hist_Z_norm_to_1 ->Add(hist_Z, 1);
	hist_Z_norm_to_1->Scale( 1.0 / (hist_Z_norm_to_1->Integral()) );
	
	///test variations
	if( kTestVariations){
	  
	  if(kSyst_TESup) TestVariations("Ztautau UP", true, hist_Z, hist_TESup_Z);
	  if(kSyst_TESdown) TestVariations("Ztautau DOWN", true, hist_Z, hist_TESdown_Z);
	  
	}
 
	
	///Perform EWK + Z subtraction from QCD==============================================================================
	// ewk subtraction
	if(kQCD_EWK_subtraction){
	  
	  QCD_subtraction("EWK NOMINAL", 	hist_QCD, 		hmap_Bkg[800005], 		kCheckNegativeBinContentAfterSubtraction);
	  if(kSyst_TESup)  	QCD_subtraction("EWK JESup", 	hist_TESup_QCD, 	hmap_TESup_Bkg[800005], kCheckNegativeBinContentAfterSubtraction);
	  if(kSyst_TESdown) QCD_subtraction("EWK JESdown", 	hist_TESdown_QCD, 	hmap_TESdown_Bkg[800005], kCheckNegativeBinContentAfterSubtraction);
	  		
	}
	
	// Z subtraction
	if(kQCD_Ztautau_subtraction){
	  
	  QCD_subtraction("Ztautau NOMINAL", 	hist_QCD, 			hist_Z_subtr, 		kCheckNegativeBinContentAfterSubtraction);
	  if(kSyst_TESup)  	QCD_subtraction("Ztautau JESup", 		hist_TESup_QCD, 	hist_TESup_Z_subtr, kCheckNegativeBinContentAfterSubtraction);
	  if(kSyst_TESdown) 	QCD_subtraction("Ztautau JESdown", 	hist_TESdown_QCD, 	hist_TESup_Z_subtr, kCheckNegativeBinContentAfterSubtraction);
	
	}
	
	///normalize QCD ======================================================================================================
	

// 	double area_data = hist_Data->Integral();
// 	
// 	//TrackFit
// 	double 	area_QCD =  hist_QCD->Integral();
// 	cout<<"QCD Normalization: using "<<endl;
// 	cout
// 	<<"  f_QCD    "<<f_QCD<<endl
// 	<<"  f13_QCD  "<f13_QCD<<<endl
// 	<<"  sf_QCD   "<<sf_QCD<<endl
// 	<<"  sf13_QCD "<<sf13_QCD<<endl;
// 	
// 	cout<<"QCD Normalization: total data events "<< area_data <<endl;
// 	cout<<"QCD Normalization: total QCD events "<< area_QCD <<endl;
// 	double TrackFit_w_QCD = TrackFit_f_QCD*area_data/area_QCD;
// 	hist_QCD->Scale( TrackFit_w_QCD  );
// 	cout<<"QCD Normalization: total normalized QCD events "<<  hist_QCD->Integral() <<endl;
	
	
	double data_trackfit_area = hist_Data_HistoFit->Integral();
	cout<<"\ntrack fit area "<<data_trackfit_area<<endl;
	
	Normalize_QCD_Ztautau_TrkFit_ZinonKaty( "QCD - Nominal", hist_QCD, data_trackfit_area, QCD_TrackFitFactor_nominal);
	
	if(kSyst_TESup){
	  Normalize_QCD_Ztautau_TrkFit_ZinonKaty( "QCD - TES UP", hist_TESup_QCD, data_trackfit_area, QCD_TrackFitFactor_TESup);
	}
	
	if(kSyst_TESdown){
	  Normalize_QCD_Ztautau_TrkFit_ZinonKaty( "QCD - TES DOWN", hist_TESdown_QCD, data_trackfit_area, QCD_TrackFitFactor_TESdown);
	}
	
	
	
	///normalize Ztautau ==========================================================================
	
	//TrackFit
// 	double 	area_TAU =  hist_Z->Integral();
// 	cout<<"TAU Normalization: using f_TAU="<< TrackFit_f_TAU <<", sf_TAU=" << TrackFit_sf_TAU<<", sf13_TAU="<< TrackFit_sf13_TAU<<endl;
// 	cout<<"TAU Normalization: total data events "<< area_data <<endl;
// 	cout<<"TAU Normalization: total TAU events "<< area_TAU <<endl;
// 	double TrackFit_w_TAU = TrackFit_f_TAU*area_data/area_TAU;
// 	hist_Z->Scale( TrackFit_w_TAU  );
// 	cout<<"TAU Normalization: total normalized TAU events "<<  hist_Z->Integral() <<endl;

	Normalize_QCD_Ztautau_TrkFit_ZinonKaty( "Ztautau - Nominal", hist_Z, data_trackfit_area, Z_TrackFitFactor_nominal);

	if(kSyst_TESup){
	  Normalize_QCD_Ztautau_TrkFit_ZinonKaty( "Ztautau - TES UP", hist_TESup_Z, data_trackfit_area, Z_TrackFitFactor_TESup);
	}

	if(kSyst_TESdown){
	  Normalize_QCD_Ztautau_TrkFit_ZinonKaty( "Ztautau - TES DOWN", hist_TESdown_Z, data_trackfit_area, Z_TrackFitFactor_TESdown);
	}


	///stats =================================================================================================
	cout<<"\nentries : integral - nominal"<<endl;
	cout<<left<<"H    "<<setw(10)<<hmap_Sig[800000]->GetEntries()	<<" : "<<setw(10)<<hmap_Sig[800000]->Integral()<<endl;
	cout<<left<<"Z    "<<setw(10)<<hist_Z->GetEntries()				<<" : "<<setw(10)<<hist_Z->Integral()<<endl;
	cout<<left<<"EWK  "<<setw(10)<<hmap_Sig[800005]->GetEntries()	<<" : "<<setw(10)<<hmap_Sig[800005]->Integral()<<endl;
	cout<<left<<"QCD  "<<setw(10)<<hist_QCD->GetEntries()			<<" : "<<setw(10)<<hist_QCD->Integral()<<endl;
	cout<<left<<"Data "<<setw(10)<<hist_Data->GetEntries()			<<" : "<<setw(10)<<hist_Data->Integral()<<endl;
	cout<<"Data - [QCD + EWK + Z] = "<<
	hist_Data->Integral() - (hist_QCD->Integral() + hmap_Sig[800005]->Integral() + hist_Z->Integral() )<<endl;

	///signal, individual plot ======================================================================================
	hist_Signal->Add(hmap_Sig[800000], 1);
	
	if(kSyst_JESup){
		hist_JESup_Signal->Add(hmap_JESup_Sig[800000], 1);
	}
	
	if(kSyst_JESdown){
		hist_JESdown_Signal->Add(hmap_JESdown_Sig[800000], 1);
	}
	
	if(kSyst_TESup){
		hist_TESup_Signal->Add(hmap_TESup_Sig[800000], 1);
	}
	
	if(kSyst_TESdown){
		hist_TESdown_Signal->Add(hmap_TESdown_Sig[800000], 1);
	}
	
	///zoom signal ===================================================================================================
	if(SignalZoom > 0){
		hist_Signal->Scale( SignalZoom );
	
		if(kSyst_JESup) hist_JESup_Signal->Scale( SignalZoom );
		 
		if(kSyst_JESdown) hist_JESdown_Signal->Scale( SignalZoom );
		 
		if(kSyst_TESup) hist_TESup_Signal->Scale( SignalZoom );
		 
		if(kSyst_TESdown) hist_TESdown_Signal->Scale( SignalZoom );
	}
	
	///spectra  and bkg curves ==========================================================================================
	
	///spectra
	cout<<"\ncreating spectra - NOMINAL"<<endl;
	hist_Spectrum0->Add(hist_QCD, 1);			/// qcd
	
	hist_Spectrum1->Add(hist_Spectrum0, 1);		/// qcd + ewk
	hist_Spectrum1->Add(hmap_Sig[800005], 1); 
	
	hist_Spectrum2->Add(hist_Spectrum1, 1);		/// qcd + ewk + Z
	hist_Spectrum2->Add(hist_Z, 1);

	hist_Spectrum3->Add(hist_Spectrum2, 1);		/// qcd + ewk + Z + signal
	hist_Spectrum3->Add(hmap_Sig[800000], SignalZoom);
	
	///Background - nominal
	cout<<"\ncreating BKG - NOMINAL"<<endl;
	hist_BKG->Add(hist_QCD, 1.0); 
	hist_BKG->Add(hmap_Sig[800005], 1.0); 
	hist_BKG->Add(hist_Z, 1.0); 	
	cout<<"\tBkg area "<<hist_BKG->Integral()<<endl;
	cout<<"\t\tQCD "<<hist_QCD->Integral()<<endl;
	cout<<"\t\tEWK "<<hmap_Sig[800005]->Integral()<<endl;
	cout<<"\t\tZtt "<<hist_Z->Integral()<<endl;
	
//	///Background - JESup
// 	if(kSyst_JESup){
// 		hist_JESup_BKG->Add(hist_JESup_QCD, 1.0);
// 		hist_JESup_BKG->Add(hmap_JESup_Sig[800005], 1.0);
// 		hist_JESup_BKG->Add(hmap_JESup_Sig[800001], 1.0);
// 		
// 		cout<<"\nBkg area - JESup "<<hist_JESup_BKG->Integral()<<endl;
// 	}
// 	
// 	///Background - JESdown
// 	if(kSyst_JESdown){
// 		hist_JESdown_BKG->Add(hist_JESdown_QCD, 1.0);
// 		hist_JESdown_BKG->Add(hmap_JESdown_Sig[800005], 1.0);
// 		hist_JESdown_BKG->Add(hmap_JESdown_Sig[800001], 1.0);
// 		
// 		cout<<"\nBkg area - JESdown "<<hist_JESdown_BKG->Integral()<<endl;
// 	}
// 	
  ///Background - TESup
  if(kSyst_TESup){
	cout<<"\ncreating BKG -TESup "<<endl;
	hist_TESup_BKG->Add(hist_TESup_QCD, 1.0);
	hist_TESup_BKG->Add(hmap_TESup_Sig[800005], 1.0);
	hist_TESup_BKG->Add(hist_TESup_Z, 1.0);
	
	cout<<"\tBkg area - TESup "<<hist_TESup_BKG->Integral()<<endl;
	cout<<"\t\tQCD "<<hist_TESup_QCD->Integral()<<endl;
	cout<<"\t\tEWK "<<hmap_TESup_Sig[800005]->Integral()<<endl;
	cout<<"\t\tZtt "<<hist_TESup_Z->Integral()<<endl;
  }

  ///Background - TESdown
  if(kSyst_TESdown){
	cout<<"\ncreating BKG -TESdown "<<endl;
	hist_TESdown_BKG->Add(hist_TESdown_QCD, 1.0);
	hist_TESdown_BKG->Add(hmap_TESdown_Sig[800005], 1.0); 
	hist_TESdown_BKG->Add(hist_TESdown_Z, 1.0);
	
	cout<<"\tBkg area - TESdown "<<hist_TESdown_BKG->Integral()<<endl;
	cout<<"\t\tQCD "<<hist_TESdown_QCD->Integral()<<endl;
	cout<<"\t\tEWK "<<hmap_TESdown_Sig[800005]->Integral()<<endl;
	cout<<"\t\tZtt "<<hist_TESdown_Z->Integral()<<endl;
  }
  
  if( kTestVariations){
	
	if(kSyst_TESup) TestVariations("BKG UP", true, hist_BKG, hist_TESup_BKG);
	if(kSyst_TESdown) TestVariations("BKG DOWN", true, hist_BKG, hist_TESdown_BKG);
	
  }
/// make graphs ================================================================================================
	cout<<"\nMaking graphs ... "<<endl;
	
	///data : histo ---> graph
	TGraphAsymmErrors *gData = new TGraphAsymmErrors(hist_Data);
	cout<<"\tData, Nbins = "<<gData->GetN()<<endl;
	///transform bkg to grap to obtain the stat error + syst  band
// 	TH1D *hTMP0  = new TH1D("hTMP0","",	nbins, firstbin, lastbin);
// 	hTMP0->Add(hist_BKG, 1.0);
// 	
//  	TH1D *hTMP1  = new TH1D("hTMP1","",	nbins, firstbin, lastbin);
//  	hTMP1->Add(hist_BKG, 1.05);
// 	
// 	TH1D *hTMP2  = new TH1D("hTMP2","",	nbins, firstbin, lastbin);
// 	hTMP2->Add(hist_BKG, 0.9);
	
	//nominal Bkg
	TGraphAsymmErrors *gBkg = new TGraphAsymmErrors(hist_BKG);
	cout<<"\tBkg, Nbins = "<<gBkg->GetN()<<endl;
	
	//bkg + syst bands
	TGraphAsymmErrors *gBkgBands;
	 
	// only JES
	if(kSyst_JESup && kSyst_JESdown)
		gBkgBands = hc.GetCombinedSystematicsGraph(hist_BKG, hist_JESup_BKG, hist_JESdown_BKG);
	
	// only TES
	if(kSyst_TESup && kSyst_TESdown)
	  gBkgBands = hc.GetCombinedSystematicsGraph(hist_BKG, hist_TESup_BKG, hist_TESdown_BKG);
	  //hc.GetCombinedSystematicsGraph(hTMP0, hTMP1, hTMP2);
	
	// TES + JES
	if(kSyst_JESup && kSyst_JESdown && kSyst_TESup && kSyst_TESdown )
		gBkgBands = hc.GetCombinedSystematicsGraph(hist_BKG, 
			hist_JESup_BKG, hist_JESdown_BKG, 
			hist_TESup_BKG, hist_TESdown_BKG);
															//hTMP1, hTMP2 );
	// bkg without bands
	if(kNoSystematics){
		cout<<"\tNo systematics required -> Bkg+bands = Bkg"<<endl;
		gBkgBands = gBkg;
	}										
	cout<<"\tBkg combined/bands, Nbins = "<<gBkgBands->GetN()<<endl;
	
	//relative upper and down bands
	TGraphAsymmErrors *gBkgRelBandUp = hc.GetRelativeBand(gBkgBands, "up");
	TGraphAsymmErrors *gBkgRelBandDown = hc.GetRelativeBand(gBkgBands, "down");	
	
	///histo ratio - stats only
	TH1D *h_Data_over_BKG = hc.GetHistoRatio(hist_Data, hist_BKG);
	cout<<"\tData/Bkg ratio - stats only, Nbins = "<<h_Data_over_BKG->GetNbinsX()<<endl;
	
	///ratio with errors
	TGraphAsymmErrors *g_Data_over_MC_Stat_x_Syst = hc.DivideGraphAsymmErrors(gData, gBkgBands);
	//TGraphAsymmErrors *g_Data_over_MC_Stat_x_Syst = hc.GraphsOperation(gData, true, gBkgBands, true, "ratio", false);
	cout<<"\tData/Bkg ratio - with stats+systs combined Nbins= "<<g_Data_over_MC_Stat_x_Syst->GetN()<<endl;
		
	TGraphAsymmErrors *g_Data_Stat_Rel = hc.GetGraphRelativeRatio(gData);
	cout<<"\tData rel ratio - stats only  Nbins= "<<g_Data_Stat_Rel->GetN()<<endl;
	
	TGraphAsymmErrors *g_Data_over_MC_Syst = hc.GraphsOperation(gData, false, gBkgBands, true, "ratio", false);
	cout<<"\tData/Bkg ratio - with systs only Nbins= "<<g_Data_over_MC_Syst->GetN()<<endl;
	
	TGraphAsymmErrors *g_Data_minus_MC_over_MC_DataStat = hc.GraphsOperation(gData, true, gBkgBands, false, "rel_ratio", false);
	cout<<"\t {Data-Bkg}/Bkg ratio - with data stats only Nbins= "<<g_Data_minus_MC_over_MC_DataStat->GetN()<<endl;
	
	///print errors
	if(kPrintErrors) PrintErrors(gBkgBands);

	///output file (before canvas)
	TFile *f = new TFile( fn.c_str(), "recreate");

	///Set canvas and create 2 empty histos for up and down  =========================================================
	TCanvas *c = new TCanvas("c","Stack Plots", 10, 10, 700, 700);
	c->SetFillColor(0);
	c->SetBorderMode(0);
	c->SetBorderSize(0);
	c->SetFrameBorderMode(0);
	gStyle->SetOptStat(0);
	gStyle->SetOptTitle(0);
	
	///create 2 empty histos 
	TH1D *hEmpty1 = new TH1D("hEmpty1",	"",	nbins, firstbin, lastbin);
	TH1D *hEmpty2 = new TH1D("hEmpty2",	"",	nbins, firstbin, lastbin);
	int font = 82;
	
	///Top pad=======================================================================================================
	c->cd();
	TPad *pad1 = new TPad("pad1","pad1", 0, 0.2, 1, 1);
	hc.SetPad(pad1);
	pad1->SetTopMargin(c->GetTopMargin()*0.4 );
	pad1->SetBottomMargin(0 );
	pad1->Draw();
	pad1->cd();
	hEmpty1->GetXaxis()->SetRangeUser(MinX, MaxX); 

	double maxim_y = hist_Data->GetBinContent(hist_Data->GetMaximumBin());
	double maxim_y_new = maxim_y*AutoOffsetTimes;
	if(kAutoMaxYaxis){
		hEmpty1->SetMaximum(maxim_y_new);
		cout<<"maxY "<<MaxY<<" -> "<<maxim_y_new<<endl;
	}else{
		if(MaxY>0) hEmpty1->SetMaximum(MaxY); 	
		
	}
	if(MinY>0) hEmpty1->SetMinimum(MinY); 
	
	hEmpty1->GetXaxis()->SetLabelSize(0.0);
	hEmpty1->GetYaxis()->SetLabelSize(0.04);
	hEmpty1->GetYaxis()->SetLabelFont(font);
	
	hEmpty1->GetYaxis()->SetTitle("events");			
	hEmpty1->GetYaxis()->SetTitleSize(0.05);
	hEmpty1->GetYaxis()->SetTitleOffset(1.3);	
	hEmpty1->GetYaxis()->SetTitleFont(font);
	
	if(xNdivisions) hEmpty1->GetXaxis()->SetNdivisions( xNdivisions );
		
	///draw empty histo 
	hEmpty1->Draw();

	///set histo styles
	hc.SetStyle(hist_Data, "data", fillcolor);
	hc.SetStyle(hist_Spectrum0, "spectrum0", fillcolor);
	hc.SetStyle(hist_Spectrum1, "spectrum1", fillcolor);
	hc.SetStyle(hist_Spectrum2, "spectrum2", fillcolor);
	hc.SetStyle(hist_Spectrum3, "spectrum3", fillcolor);
	hc.SetStyle(hist_Signal, "signal");

	///draw 
	if(kShowSpectrumWithist_Signal) hist_Spectrum3->Draw("hist same");
	hist_Spectrum2->Draw("hist same");
	hist_Spectrum1->Draw("hist same");
	hist_Spectrum0->Draw("hist same");
	
	if(kShowSignalAlone) hist_Signal->Draw("hist same");
	
	if(kShow_ModelStatSystBandsCombined){
		gBkgBands->SetFillColor(kGray+2);
		gBkgBands->SetFillStyle(3004);
		gBkgBands->Draw("E2");
		
		hc.SetErrorBarsToZero(gBkg, 1, 0);
		gBkg->SetMarkerStyle(20);
		gBkg->SetLineWidth(2);
		gBkg->Draw("||");//http://root.cern.ch/root/html/TGraphPainter.html
	}
	
	if(kShowData){
		hc.SetErrorBarsToZero(gData, 1, 0);
		gData->SetMarkerStyle(20);
		gData->SetMarkerSize(1.5);
		gData->SetLineWidth(2);
		gData->SetLineColor(1);
		gData->Draw("PZ");
		//hist_Data->Draw("ep same");
	
	}

	if(kLogY) gPad->SetLogy();
	gPad->RedrawAxis();
	
// 	gPad->Modified(); 
// 	gPad->Update();

	///the legends
	string leg_Higgs = "Higgs m_{H} = " + hmass + " GeV (#sigma_{SM} #times "+ hc.GetStringFromInt(SignalZoom)+")";
		
	string leg_lumi = "#scale[0.75]{#int}dtL = "+lumi_str+" fb^{-1}";
		
	string leg_data_and_lumi = "2012 Data #sqrt{s} = 8 TeV  "+leg_lumi;
		
	string leg_Z = "Z #rightarrow #tau_{h} #tau_{h}  ("+Z_model_legend+")";
		
	string leg_QCD = "QCD multi-jets ("+QCD_model_legend+")";
		
	string leg_ewk = "Electroweak";
		
				
	TLegend *leg1 = new TLegend(0.155, 0.695, 0.42, 0.94,NULL,"brNDC");
	leg1->SetBorderSize(0);
	leg1->SetLineColor(15);
	leg1->SetLineStyle(1);
	leg1->SetLineWidth(0);
	leg1->SetFillColor(0);//19
	leg1->SetFillStyle(0);//3002
	leg1->SetTextFont(42); 
	leg1->SetTextSize(0.03); 

	leg1->AddEntry(hist_Spectrum2, leg_Z.c_str(),"lpf");
	leg1->AddEntry(hist_Spectrum1, leg_ewk.c_str(),"lpf");
	leg1->AddEntry(hist_Spectrum0, leg_QCD.c_str(),"lpf");
			
	leg1->Draw();

			
	TLegend *leg2 = new TLegend(0.44,0.695,0.94,0.94,NULL,"brNDC");
	leg2->SetBorderSize(0);
	leg2->SetLineColor(15);
	leg2->SetLineStyle(1);
	leg2->SetLineWidth(0);
	leg2->SetFillColor(0);
	leg2->SetFillStyle(0);
	leg2->SetTextFont(42); 
	leg2->SetTextSize(0.03); 
	
	leg2->AddEntry(hist_Data, leg_data_and_lumi.c_str(),"lp");
		
	if(kShowSpectrumWithist_Signal) 
		leg2->AddEntry(hist_Spectrum3, leg_Higgs.c_str(),"lpf");
	else if(kShowSignalAlone)
		leg2->AddEntry(hist_Signal, leg_Higgs.c_str(),"l");
	else{
		//do nothing
	}

	if(kShow_ModelStatSystBandsCombined){
		if(kNoSystematics) 
			leg2->AddEntry(gBkgBands,"#color[4]{Stat} error","f");
		else
			leg2->AddEntry(gBkgBands,"#color[4]{Stat} #otimes Syst uncertainties","f");
	}

	leg2->Draw();

			
	///type category
	string lat_categ = 	
		category == "vbf" ? "VBF" :
		category == "boosted" ? "Boosted" :
	  	category == "1jet" ? "1-jet" :
	  	category == "0jet" ? "0-jet" : 
	  	category =="preselection"  ? "Preselection" :  
			"unknown category";

	string thisregion = 
		region == "CR_MassSideBands" ? "Mass Side Bands CR" : 
		region == "SR_MassWindow" ? "Signal Region" : 
		region == "CR_LowMassCut" ? "Low Mass Cut CR" : 
		region == "CR_UpperMassCut" ? "Upper Mass Cut CR" : 
		region == "CR_NoMassCut" ? "No Mass Cut CR" : 
		region == "CR_QCDrich" ? "QCD-rich CR" : 
		region == "CR_preselection" ? "" : 
		region == "CR_dEta" ? "#Delta#eta_{#tau#tau} CR" : 
			"Unknown Region";
		

	string category_region = "#splitline{#tau_{h} #tau_{h} : "+lat_categ+"}{"+thisregion+"}";
	
	double xlat = 0.155;
	double ylat= 0.625;
	if(variable == "dijet_mass" || variable == "dijet_dEta" || variable == "averageIntPerXing" ||
		  variable == "tau_0_dijet_eta_centr" ||  variable == "tau_1_dijet_eta_centr" ||
		  variable == "tau_0_tracks" || variable == "tau_1_tracks" || variable == "MMC_resonance_dijet_vecSumPt" ||
		  variable == "MMC_resonance_dijet_vecSumPt" || variable == "MMC_resonance_jets_min_dEta" ||
		  variable == "MMC_resonance_pt" || variable == "jet_0_pt" || variable == "jet_1_pt" || variable == "met_et" ||
		  variable == "MMC_met_et" || variable == "esv_all_objects_sphericity" || variable == "HT_jets" || variable == "HT_jets_taus" || 
		  variable == "HT_jets_taus_met" || variable == "tau_0_pt" || variable == "tau_1_pt" || 
		  variable == "ditau_pT_0_over_pT_1" || variable == "esv_all_objects_aplanarity" ||  variable == "esv_all_objects_planarity" ||
		  variable == "dijet_dPhi" || variable == "ditau_dEta"

	  ){
		xlat = 0.6;
	}
	TLatex *tex = new TLatex( xlat, ylat, category_region.c_str() );
	tex->SetNDC();//(Normalized Device Coordinates) [0,1]

	tex->SetTextFont(42);
	tex->SetTextSize(0.035);
	tex->SetLineWidth(2);
	tex->Draw();

	//hide zero
// 	int xsign = MinX >= 0 ? 1 : -1;
// 	TBox *box = new TBox(MinX - xsign*MinX*0.2, 0, MinX- xsign*MinX*0.01, MaxY/5e-2);
// 	box->SetFillColor(kRed);
// 	box->SetLineColor(kBlue);
// 	box->Draw();
	
	///Bottom pad ===============================================================================================================
	c->cd();
	TPad *pad2 = new TPad("pad2","pad2", 0, 0, 1, 0.2);
	hc.SetPad(pad2);
	pad2->SetTopMargin(0);
	pad2->SetBottomMargin(c->GetBottomMargin()*3.5 );
	pad2->SetFillStyle(4000); //transparent
	pad2->Draw();
	pad2->cd();
	hEmpty2->GetXaxis()->SetRangeUser(MinX, MaxX); 
	hEmpty2->SetMaximum(RatioMaxY); 
	hEmpty2->SetMinimum(RatioMinY); 
	hEmpty2->GetXaxis()->SetLabelSize(0.14);
	hEmpty2->GetYaxis()->SetLabelSize(0.14);
	hEmpty2->GetXaxis()->SetLabelFont(font);
	hEmpty2->GetYaxis()->SetLabelFont(font);
	hEmpty2->GetXaxis()->SetTitle(xTitle.c_str());
	hEmpty2->GetXaxis()->SetTitleOffset(0.9);	
	hEmpty2->GetXaxis()->SetTitleFont(font);
	hEmpty2->GetXaxis()->SetTitleSize(0.17);
				
	hEmpty2->GetYaxis()->SetTitle(PadBelowXtitle.c_str());		
	hEmpty2->GetYaxis()->SetTitleSize(0.17);
	hEmpty2->GetYaxis()->SetTitleOffset(0.34);	
	hEmpty2->GetYaxis()->SetTitleFont(font);
	hEmpty2->GetYaxis()->CenterTitle(1);
	hEmpty2->GetYaxis()->SetNdivisions(105);
	
	if(xNdivisions) hEmpty2->GetXaxis()->SetNdivisions( xNdivisions );
					
	hEmpty2->Draw();
	
	if(kShow_HorizontalErrorBarsInRatioPlot){
  
		int ci5 = kCyan - 5;
		int ci10 = kCyan - 8;
		int ci20 = kCyan - 10;
								
		MinX -=  kAdjustLeftBin 	? BinW : 0;
		MaxX +=  kAdjustRightBin 	? BinW : 0;
		TBox *box5 = new TBox(MinX, 0.95, MaxX, 1.05);
		box5->SetFillColor(ci5);
	
		TBox *box10 = new TBox(MinX, 0.90, MaxX, 1.1);
		box10->SetFillColor(ci10);
	
		TBox *box20 = new TBox(MinX, 0.80, MaxX, 1.2);
		box20->SetFillColor(ci20);
	
		box20->Draw("same");
		box10->Draw("same");
		box5->Draw();
	}
	
	if( kShow_RatioLines ){
		
		TLine *line1 = new TLine( hEmpty2->GetXaxis()->GetXmin(), 1, hEmpty2->GetXaxis()->GetXmax(), 1);
		line1->SetLineStyle(7);
		line1->SetLineColor(1);
		line1->Draw("same");
	}
	
	hc.SetStyle(h_Data_over_BKG, "ratio");
	
	///stat and syst combined
	g_Data_over_MC_Stat_x_Syst->SetFillColor(kGray+2);
	g_Data_over_MC_Stat_x_Syst->SetFillStyle(3004);
	g_Data_over_MC_Stat_x_Syst->SetMarkerStyle(20);
	g_Data_over_MC_Stat_x_Syst->SetMarkerSize(0.5);
	//hc.SetErrorBarsToZero(g_Data_over_MC_Stat_x_Syst, 1, 0);
	
	/// only mc syst
	g_Data_over_MC_Syst->SetMarkerStyle(7);
	//g_Data_over_MC_Syst->SetMarkerSize(1);
	g_Data_over_MC_Syst->SetMarkerColor(kRed-3);
	g_Data_over_MC_Syst->SetFillColor(41);
	g_Data_over_MC_Syst->SetFillStyle(1001);
	
	///only data stat
	g_Data_Stat_Rel->SetMarkerStyle(7);
	//g_Data_Stat_Rel->SetMarkerSize(1);
	g_Data_Stat_Rel->SetMarkerColor(1);
	
	/// data-mc over mc
	g_Data_minus_MC_over_MC_DataStat->SetMarkerStyle(7);
	g_Data_minus_MC_over_MC_DataStat->SetMarkerColor(1);
	
	
	///relative bands up and down
	gBkgRelBandUp->SetLineColor(kGreen);
	gBkgRelBandDown->SetLineColor(kRed);
	hc.SetErrorBarsToZero(gBkgRelBandUp, 1, 0);
	hc.SetErrorBarsToZero(gBkgRelBandDown, 1, 0);
	
	///plot graphs
	if(kShow_DataMCRatio_StatSystBandsCombined){

		if(kShowData) g_Data_over_MC_Stat_x_Syst->Draw("P E2");
		
	}else if(kShow_DataMCRatio_StatSystBandsDecoupled) {
		
		if(kShowData){
			g_Data_over_MC_Syst->Draw("E2 P");
			g_Data_Stat_Rel->Draw("PZ S");
		}
			
	}else if(kShow_RelativeStatSystBandsCombined){

	  gBkgRelBandUp->Draw("L");
	  gBkgRelBandDown->Draw("L S");
	  g_Data_minus_MC_over_MC_DataStat->Draw("P Z S");
	  
	}else{
		
		if(kShowData) h_Data_over_BKG->Draw("ep same");
	}
	

	gPad->RedrawAxis();
// 	gPad->Modified(); 
// 	gPad->Update();

//	c->Draw();	

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
	
	
	if(kProduceROOT){
	  cout<<fn<<endl;
	  f->cd();
	  hist_Data->Write("hData");
	  hist_QCD->Write("hQCD");
	  hmap_Sig[hc.GetHiggsMCnumber(125, "vbf")]->Write("hVBF");
	  hmap_Sig[hc.GetHiggsMCnumber(125, "ggf")]->Write("hGGF");
	  hmap_Sig[hc.GetHiggsMCnumber(125, "WH")]->Add(hmap_Sig[hc.GetHiggsMCnumber(125, "ZH")]);
	  hmap_Sig[hc.GetHiggsMCnumber(125, "WH")]->Write("hVH");
	  hist_Z ->Write("hZ");
	  hmap_Sig[800005]->Write("hEwk");
	  
	  hist_Z_norm_to_1->Write();
	  c->Write(); 
	  
	  f->Close();
	}
	
	cout<<"\nData tree entries : "<<tData->GetEntries()<<""<<endl;
	

}
///************************************************************************
///************************************************************************
void PrintErrors(TGraphAsymmErrors *g){
	
	double* x 	= g->GetX();
	double* y 	= g->GetY();

	double* errYlow  = g->GetEYlow();
	double* errYhigh = g->GetEYhigh();
	
	const int nBin = g->GetN();
	
	for(int i=0; i<nBin; i++){
		
		cout<<left<<setw(8)<<x[i]<<" "<<setw(10)<<y[i]<<" -"<<setw(10)<<errYlow[i]<<" +"<<setw(10)<<errYhigh[i]<<endl;
	}
	
}
///************************************************************************
///************************************************************************
void CheckNegativeBinContent(TH1D *h, const string &s){
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
void Normalize_QCD_Ztautau_TrkFit_ZinonKaty(const string &S, TH1D *h, double data_trackfit_area, double SF ){
  
  cout<<"\nNormalizing "<<S<<"  SF = "<<SF<<endl;
  
  double TARGET_AREA =  SF * data_trackfit_area;
  
  cout<<"\tTarget area = "<<TARGET_AREA<<endl;
  
  double AREA(0);  AREA = h->Integral();
  
  if(AREA < 1e-8) {  
	cout<<"Integral "<<AREA<<" ==> Empty QCD histo. Exiting ..."<<endl; 
	exit(0); 
  }
  
  double WEIGHT = TARGET_AREA/AREA;
  cout<<"\tWeight "<<WEIGHT<<endl;
  cout<<"\tIntegral before scaling "<<h->Integral()<<endl;
  h->Scale( WEIGHT );
  cout<<"\tIntegral after scaling "<<h->Integral()<<" (before subtraction) "<<endl<<endl;
  
  
}
///************************************************************************
///************************************************************************
void QCD_subtraction(const string &S, TH1D *h, const TH1D *hs, bool k){
  cout<<"\nQCD: Subtracting "<<S<<endl;
  cout<<"\tQCD integral before "<<h->Integral()<<endl;
  h->Add(hs, -1); 
  cout<<"\tQCD integral after "<<h->Integral()<<endl;
  if(k) CheckNegativeBinContent(h, "QCD-"+S);
}
///************************************************************************
///************************************************************************
void TestVariations(const string &S, bool kUp, const TH1D *h0, const TH1D *h1){
  
  cout<<"\nTest variations "<<S<<endl;
  
  for(int i = 1; i <= h0->GetNbinsX(); i++){
	double y = h0->GetBinContent(i);
	double y1 = h1->GetBinContent(i);
	double dy = kUp ? y1 - y : y - y1;
	double x = h0->GetBinCenter(i);
	
	cout<<"x, y, abs err, rel err  "<<x<<" : "<<y<<" : "<<dy<<" : "<<dy/y<<endl;
  }
  
}

	

