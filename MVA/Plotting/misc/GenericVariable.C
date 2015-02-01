// https://svnweb.cern.ch/trac/atlasphys/browser/Physics/Higgs/HSG4/software/hadhad/MultiVariateAnalysis
#include <iostream>
#include <vector>
#include <string>

#include "TROOT.h"
#include "TSystem.h"
#include "TH1D.h"
#include "TCut.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TLegend.h"
#include "TColor.h"
#include "TGaxis.h"
#include "TGraphAsymmErrors.h"

#include "TApplication.h"
#include "TRint.h"

#include "TMath.h"

#include "TBox.h"

#include "TLatex.h"

#include "HelperClass.h"
#include "MonteCarloBank.h"

using namespace std;


void GenericVariable();
bool Loop(const string &myCategory_s, const string &myVariable_s);
void CheckNegativeBinContent(TH1D *h, const string &s);

int main(/*int argc, char *argv[]*/)
{
		//TApplication *myapp=new TApplication("myapp",0,0);
	//myapp->Run();
	GenericVariable();
	
	return 0;
}

void GenericVariable(){
	///wish list:
	 
	vector<string> vCategory;
	//			vCategory.push_back("vbf");
			vCategory.push_back("NoJetReq");
			//	vCategory.push_back("boosted");
//	vCategory.push_back("1jet");
//	vCategory.push_back("0jet");
//	 	


	vector<string> vVariable;
	//______The VBF training variables:________
//	vVariable.push_back("ditau_dR");
//	vVariable.push_back("MMC_resonance_pt");
	vVariable.push_back("ditau_mass_mmc");
//	vVariable.push_back("tau_0_dijet_eta_centr");
//	vVariable.push_back("tau_1_dijet_eta_centr");
//	vVariable.push_back("dijet_mass");
//	vVariable.push_back("dijet_dEta");
//	vVariable.push_back("met_centrality");
//	vVariable.push_back("dijet_eta1_x_eta2");
	//	
	//______The Boosted training variables:________


	//vVariable.push_back("MMC_resonance_pt");
//	vVariable.push_back("ditau_dR");
//	vVariable.push_back("ditau_mass_mmc");
//	vVariable.push_back("met_centrality");
// 	vVariable.push_back("esv_all_objects_sphericity");
// 	vVariable.push_back("ditau_colapprox_x0");
// 	vVariable.push_back("ditau_colapprox_x1");
	//

//	//______The 1jet training variables:________                                                                                          
	//
//	vVariable.push_back("MMC_resonance_pt"); 
//	vVariable.push_back("ditau_dR"); 
//	vVariable.push_back("ditau_mass_mmc");
//	vVariable.push_back("met_centrality");
//	vVariable.push_back("esv_all_objects_sphericity");
//	vVariable.push_back("ditau_colapprox_x0"); 
//	vVariable.push_back("ditau_colapprox_x1");
	//	//



	//______Other Kinematic variables:________
//	vVariable.push_back("met_et");
//	//  vVariable.push_back("tau_0_BDT_score");
//	//  vVariable.push_back("tau_1_BDT_score");
//	vVariable.push_back("tau_0_pt");
//	vVariable.push_back("tau_1_pt");
//	//  vVariable.push_back("tau_0_tracks");
	//  vVariable.push_back("tau_1_tracks");

	//  vVariable.push_back("ditau_dEta");
	//
// 	vVariable.push_back("met_phi"); 
// 	vVariable.push_back("ditau_cosTheta");
// 	vVariable.push_back("ditau_mass_vis");
// 	vVariable.push_back("ditau_mass_col");

// 	vVariable.push_back("esv_all_objects_planarity");
// 	vVariable.push_back("esv_all_objects_aplanarity");
// 	vVariable.push_back("esv_all_objects_FoxWolfram_R1");
// 	vVariable.push_back("esv_all_objects_FoxWolfram_R2");
	// 	
	// 
//  	vVariable.push_back("MMC_resonance_jets_min_dR");	
// 	vVariable.push_back("MMC_resonance_jets_min_dEta");
// 	vVariable.push_back("MMC_resonance_dijet_DeltaPhi");
//  	vVariable.push_back("MMC_resonance_dijet_vecSumPt");
// 	vVariable.push_back("MMC_resonance_dijet_DeltaPt");
// 	vVariable.push_back("MMC_met_et");
// 	vVariable.push_back("MMC_resonance_x0");
// 	vVariable.push_back("MMC_resonance_x1");
	// 	

	// 	
//____ plot with jet requirements: 	
// 	vVariable.push_back("HT_jets");
//  	vVariable.push_back("HT_jets_taus_met");
	
// 	vVariable.push_back("jet_0_eta");
	// 	vVariable.push_back("jet_1_eta");
	// 	vVariable.push_back("jet_0_pt");
	// 	vVariable.push_back("jet_1_pt");
	
	///==== all variables in alphabetic order ==================================
// 	vVariable.push_back("dijet_dEta");
// 	vVariable.push_back("dijet_eta1_x_eta2");
// 	vVariable.push_back("dijet_mass");
// 	vVariable.push_back("ditau_colapprox_x0");
// 	vVariable.push_back("ditau_colapprox_x1");
// 	vVariable.push_back("ditau_cosTheta");
// 	vVariable.push_back("ditau_dEta");
// 	vVariable.push_back("ditau_dR");
// 	vVariable.push_back("ditau_mass_col");
// 	vVariable.push_back("ditau_mass_mmc");
//	vVariable.push_back("ditau_mass_vis");
// 	//vVariable.push_back("esv_all_objects_aplanarity");
// 	//vVariable.push_back("esv_all_objects_FoxWolfram_R1");
// 	//vVariable.push_back("esv_all_objects_FoxWolfram_R2");
// 	//vVariable.push_back("esv_all_objects_planarity");
// 	vVariable.push_back("esv_all_objects_sphericity");
// 	//vVariable.push_back("HT_jets");
// 	//vVariable.push_back("HT_jets_taus_met");
//	// 
// 	vVariable.push_back("jet_0_eta");
// 	// vVariable.push_back("jet_0_pt");
// 	vVariable.push_back("jet_1_eta");
// 	// vVariable.push_back("jet_1_pt");
//	// 	
// 	vVariable.push_back("met_centrality");
//        	vVariable.push_back("met_et");
//	// 	vVariable.push_back("met_phi");
//	// 	vVariable.push_back("MMC_met_et");
//// 	vVariable.push_back("MMC_resonance_dijet_DeltaPhi");
//// 	vVariable.push_back("MMC_resonance_dijet_DeltaPt");
//// 	vVariable.push_back("MMC_resonance_dijet_vecSumPt");
//// 	vVariable.push_back("MMC_resonance_jets_min_dEta");
//// 	vVariable.push_back("MMC_resonance_jets_min_dR");
//// 	vVariable.push_back("MMC_resonance_pt");
//// 	vVariable.push_back("MMC_resonance_x0");
//// 	vVariable.push_back("MMC_resonance_x1");
//	// 	
// 	vVariable.push_back("tau_0_BDT_score");
// 	vVariable.push_back("tau_0_dijet_eta_centr");
// 	vVariable.push_back("tau_0_pt");
// 	vVariable.push_back("tau_0_tracks");
// 	vVariable.push_back("tau_1_BDT_score");
// 	vVariable.push_back("tau_1_dijet_eta_centr");
// 	vVariable.push_back("tau_1_pt");
// 	vVariable.push_back("tau_1_tracks");
//	
//
//	


	typedef vector<string>::iterator ITS;
	
	for(ITS cat = vCategory.begin(); cat != vCategory.end(); cat++)
		for(ITS var = vVariable.begin(); var != vVariable.end(); var++)	
			if( Loop( *cat, *var) ) cout<<*cat << "  " << *var << " done "<<endl; else cout<<*cat << "  " << *var << " aborted "<<endl;

	cout<<"Done!"<<endl;
}

bool Loop(const string &myCategory_s, const string &myVariable_s){

	///external classes
	gSystem->Load("../../HelperClass/HelperClass_cpp.so");
	gSystem->Load("../../MonteCarloBank/MonteCarloBank_cpp.so");

	HelperClass hc;
	MonteCarloBank mcbank;
	
	/// some variables
	string 	variable; double MinX, MaxX, MinY, MaxY;string 	category; double xlat, ylat;
	bool 	kLogY; string xTitle;int nbins; double firstbin, lastbin; bool kAdjustLeftBin, kAdjustRightBin;
	double 	QCD_TrackFitFactor, Z_TrackFitFactor; //take values from makeTrackFit.C output
	string fillcolor; int xNdivisions(0);
	
	string  category_file ;
	category = myCategory_s;
	if(category == "NoJetReq")	 	category_file = "vbf";
	else category_file = myCategory_s;

	cout<<"Category " <<	category <<endl;

	/// category settings

	if(category == "vbf"){
		//fillcolor = "green";
		fillcolor = "harmonized";
		
		//	     	QCD_TrackFitFactor = 0.33185; Z_TrackFitFactor = 0.228793; //v10. Before adding event weights

		QCD_TrackFitFactor = 0.348331;  Z_TrackFitFactor = 0.191327;// v10 after adding event weights

		/// All below are Before adding event weights
		//              QCD_TrackFitFactor = 0.432849;  Z_TrackFitFactor = 0.0771384;//updated MedMedCR 
		//				QCD_TrackFitFactor = 0.356847;  Z_TrackFitFactor = 0.232979;//just no jet req 
		//	QCD_TrackFitFactor = 0.530834;  Z_TrackFitFactor = 0.00270654;//reverse taudEta and no jet req
		//				QCD_TrackFitFactor = 0.503375;  Z_TrackFitFactor =0;//Updated Reverse taudEta CR  
		//		QCD_TrackFitFactor = 0.381789;  Z_TrackFitFactor = 0.158332;////with cut on BDT<0.5
		//		QCD_TrackFitFactor = 0.361301;  Z_TrackFitFactor = 0.22601;//with cut on BDT<0.5 NO JETS
	
	}else if(category == "NoJetReq"){
	  //QCD_TrackFitFactor = 0.530834;  Z_TrackFitFactor = 0.00270654;//reverse taudEta and no jet req Before adding event weights
	  	  QCD_TrackFitFactor = 0.510824;  Z_TrackFitFactor = 0.0386346;//reverse deta  no jet req
	  //	  QCD_TrackFitFactor = 0.401251;  Z_TrackFitFactor = 0.195582;//no dEta cut

	  //QCD_TrackFitFactor = 0.544138;  Z_TrackFitFactor = -0.00206106;//dEta>1.8 no jet req
	}else if(category == "boosted"){
		//fillcolor = "azure";
		fillcolor = "harmonized";
		
		//		QCD_TrackFitFactor = 0.175163;  Z_TrackFitFactor = 0.537113;//v10 
		QCD_TrackFitFactor = 0.194243;  Z_TrackFitFactor = 0.497483;
		//	QCD_TrackFitFactor = 0.418112;  Z_TrackFitFactor = 0.137653; //med med
		
	}else if( category == "1jet"){
		//fillcolor = "blue";
		fillcolor = "harmonized";
		
		QCD_TrackFitFactor = 0.328376;   Z_TrackFitFactor = 0.250448;//v10 
		// QCD_TrackFitFactor = 0.450998;   Z_TrackFitFactor = 0.0455698;// Medium Medium
		
	}else if( category == "0jet"){
		//fillcolor = "magenta";
		fillcolor = "harmonized";
		
		QCD_TrackFitFactor = 0.394051;   Z_TrackFitFactor = 0.180862;//v10	
		//	QCD_TrackFitFactor = 0.447054;		  Z_TrackFitFactor = 0.0776485;// Med Med CR

	}else{
		cout<<"\nplease, choose a category. Exiting ..."<<endl;
		exit(0);
	}
	
	///y-axis range
	bool kAutoMaxYaxis = true;
	double AutoOffsetTimes = 1.10;
	
	///variable settings
	if( myVariable_s == "met_et"){ 
		variable = myVariable_s; 
		MinX = 20.0; MaxX = 150.0; MinY = 1e-6; MaxY = 700.0;
		if(myCategory_s=="vbf"){  MinX = 20.0; MaxX = 150.0; MinY = 1e-6; MaxY = 700.0;}
		if(myCategory_s=="1jet"){  MinX = 20.0; MaxX = 150.0; MinY = 1e-6; MaxY = 700.0;}
		kLogY = false; xTitle = "#slash{E}_{T} [GeV]";
		firstbin = 0; lastbin = 150; nbins = 30; 
		kAdjustLeftBin = false; kAdjustRightBin = false;
		xlat = 25; ylat = MaxY*0.9;
		kAutoMaxYaxis = true; AutoOffsetTimes = 1.3;
		
	}else if( myVariable_s == "MMC_met_et"){ 
		variable = myVariable_s; 
		MinX = 20.0; MaxX = 150.0; MinY = 1e-6; MaxY = 700.0;
		if(myCategory_s=="vbf"){  MinX = 150.0; MaxX = 800.0; MinY = 1e-6; MaxY = 700.0;}
		if(myCategory_s=="boosted"){  MinX = 150.0; MaxX = 800.0; MinY = 1e-6; MaxY = 400.0;}
		if(myCategory_s=="1jet"){  MinX = 150.0; MaxX = 800.0; MinY = 1e-6; MaxY = 700.0;}
		if(myCategory_s=="0jet"){  MinX = 150.0; MaxX = 800.0; MinY = 1e-6; MaxY = 700.0;}
		kLogY = false; xTitle = "MMC #slash{E}_{T} [GeV]";
		firstbin = 0; lastbin = 150; nbins = 30; 
		kAdjustLeftBin = false; kAdjustRightBin = false;
		xlat = 20; ylat = MaxY*0.9;
		kAutoMaxYaxis = true; AutoOffsetTimes = 1.3;
		
	}else if( myVariable_s == "HT_jets_taus_met"){ 
		variable = myVariable_s; 
		MinX = 150.0; MaxX = 800.0; MinY = 1e-6; MaxY = 700.0;
		if(myCategory_s=="vbf"){  MinX = 150.0; MaxX = 800.0; MinY = 1e-6; MaxY = 220.0;}
		if(myCategory_s=="boosted"){  MinX = 150.0; MaxX = 800.0; MinY = 1e-6; MaxY = 2000.0;}
		if(myCategory_s=="1jet"){  MinX = 150.0; MaxX = 800.0; MinY = 1e-6; MaxY = 2000.0;}
		if(myCategory_s=="0jet"){  MinX = 150.0; MaxX = 800.0; MinY = 1e-6; MaxY = 2000.0;}
		kLogY = false; xTitle = "H_{T}(di-#tau, jets, #slash{E}_{T}) [GeV]";
		firstbin = 0; lastbin = 1000; nbins = 50; 
		kAdjustLeftBin = false; kAdjustRightBin = false;
		xlat = 160; ylat = MaxY*0.9;
		kAutoMaxYaxis = false; AutoOffsetTimes = 1.3;
		
	}else if( myVariable_s == "HT_jets"){ 
		variable = myVariable_s; 
		MinX = 80.0; MaxX = 500.0; MinY = 1e-6; MaxY = 700.0;
		if(myCategory_s=="vbf"){  MinX = 150.0; MaxX = 800.0; MinY = 1e-6; MaxY = 220.0;}
		if(myCategory_s=="boosted"){  MinX = 150.0; MaxX = 800.0; MinY = 1e-6; MaxY = 2000.0;}
		if(myCategory_s=="1jet"){  MinX = 150.0; MaxX = 800.0; MinY = 1e-6; MaxY = 2000.0;}
		if(myCategory_s=="0jet"){  MinX = 150.0; MaxX = 800.0; MinY = 1e-6; MaxY = 2000.0;}
		kLogY = false; xTitle = "H_{T}(jets) [GeV]";
		firstbin = 0; lastbin = 1000; nbins = 50; 
		kAdjustLeftBin = false; kAdjustRightBin = false;
		xlat = 160; ylat = MaxY*0.9;
		kAutoMaxYaxis = false; AutoOffsetTimes = 1.3;
		
	}else if(myVariable_s == "MMC_resonance_x0" || myVariable_s == "MMC_resonance_x1"){
		variable = myVariable_s;
		MinX = 0; MaxX = 1; MinY = -1e-6; MaxY = 200.0; 
		if(myCategory_s=="vbf"){ MinX = 0; MaxX = 1; MinY = -1e-6; MaxY = 200.0; }
		if(myCategory_s=="1jet"){ MinX = 0; MaxX = 1; MinY = -1e-6; MaxY = 200.0; }
		kLogY = false;  xTitle =  myVariable_s == "MMC_resonance_x0" ? "leading #tau MMC x" : "subleading #tau MMC x";
		firstbin = 0; lastbin = 1; nbins = 10;  kAdjustLeftBin = false; kAdjustRightBin = false;
		xlat = 0.01; ylat = MaxY*0.9;
		cout<<"Info: "<<xTitle<<" "<<firstbin<<" "<<lastbin<<endl;
		kAutoMaxYaxis = true; AutoOffsetTimes = 1.8;
	  
	}else if(myVariable_s == "ditau_colapprox_x0" || myVariable_s == "ditau_colapprox_x1"){
		variable = myVariable_s;
		MinX = 0; MaxX = 1; MinY = -1e-6; MaxY = 200.0; 
		if(myCategory_s=="vbf"){ MinX = 0.; MaxX = 1; MinY = -1e-6; MaxY = 200.0; }
		if(myCategory_s=="1jet"){ MinX = 0.; MaxX = 1; MinY = -1e-6; MaxY = 200.0; }
		kLogY = false;  xTitle =  myVariable_s == "ditau_colapprox_x0" ? "leading #tau Coll. Approx. x" : "subleading #tau Coll. Approx. x";
		firstbin = 0; lastbin = 1; nbins = 10;  kAdjustLeftBin = false; kAdjustRightBin = false;
		xlat = 0.05; ylat = MaxY*0.9;
		cout<<"Info: "<<xTitle<<" "<<firstbin<<" "<<lastbin<<endl;
		kAutoMaxYaxis = true; AutoOffsetTimes = 2;
	  
	}else if(myVariable_s == "MMC_resonance_jets_min_dEta"){
		variable = myVariable_s;
		MinX = 0; MaxX = 5; MinY = -1e-6; MaxY = 200.0;
		if(myCategory_s=="vbf"){ MinX = 0; MaxX = 5; MinY = -1e-6; MaxY = 200.0; }
		if(myCategory_s=="1jet"){ MinX = 0; MaxX = 5; MinY = -1e-6; MaxY = 200.0; }
		kLogY = false;  xTitle =  "min#Delta#eta(MMC, jet)";
		firstbin = 0; lastbin = 10; nbins = 50;  kAdjustLeftBin = false; kAdjustRightBin = false;
		xlat = 0.1; ylat = MaxY*0.9;
		cout<<"Info: "<<xTitle<<" "<<firstbin<<" "<<lastbin<<endl;
		kAutoMaxYaxis = true; AutoOffsetTimes = 1.5;
	  
	}else if(myVariable_s == "MMC_resonance_jets_min_dR"){
		variable = myVariable_s;
		MinX = 0; MaxX = 5; MinY = -1e-6; MaxY = 200.0;
		if(myCategory_s=="vbf"){ MinX = 0; MaxX = 5; MinY = -1e-6; MaxY = 200.0; }
		if(myCategory_s=="1jet"){ MinX = 0; MaxX = 5; MinY = -1e-6; MaxY = 200.0; }
		kLogY = false;  xTitle =  "min#DeltaR(MMC, jet)";
		firstbin = 0; lastbin = 10; nbins = 50;  kAdjustLeftBin = false; kAdjustRightBin = false;
		xlat = 0.1; ylat = MaxY*0.9;
		cout<<"Info: "<<xTitle<<" "<<firstbin<<" "<<lastbin<<endl;
		kAutoMaxYaxis = true; AutoOffsetTimes = 1.6;
	  
	}else if(myVariable_s == "MMC_resonance_dijet_DeltaPhi"){
		variable = myVariable_s;
		MinX = 0; MaxX = TMath::Pi(); MinY = -1e-6; MaxY = 200.0;
		if(myCategory_s=="vbf"){ MinX = 0; MaxX = TMath::Pi(); MinY = -1e-6; MaxY = 200.0; }
		if(myCategory_s=="1jet"){ return false; }
		kLogY = false;  xTitle =  "#Delta#phi(MMC, di-jet)";
		firstbin = 0; lastbin = TMath::Pi(); nbins = 16;  kAdjustLeftBin = false; kAdjustRightBin = false;
		xlat = 0.05; ylat = MaxY*0.9;
		cout<<"Info: "<<xTitle<<" "<<firstbin<<" "<<lastbin<<endl;
		kAutoMaxYaxis = true; AutoOffsetTimes = 1.3;
	  
	}else if(myVariable_s == "MMC_resonance_dijet_vecSumPt"){
		variable = myVariable_s;
		if(myCategory_s=="vbf"){ MinX = 0; MaxX = 150; MinY = -1e-6; MaxY = 200.0; }
		if(myCategory_s=="1jet"){ return false;}
		kLogY = false;  xTitle =  "#Sigma#vec{p}_{T}(MMC, di-jet)";
		firstbin = 0; lastbin = 500; nbins = 100;  kAdjustLeftBin = false; kAdjustRightBin = false;
		xlat = 2.5; ylat = MaxY*0.9;
		cout<<"Info: "<<xTitle<<" "<<firstbin<<" "<<lastbin<<endl;
		kAutoMaxYaxis = true; AutoOffsetTimes = 1.7;
	  
	}else if(myVariable_s == "MMC_resonance_dijet_DeltaPt"){
		variable = myVariable_s;
		MinX = 0; MaxX = 100; MinY = -1e-6; MaxY = 200.0;
		if(myCategory_s=="vbf"){ MinX = 0; MaxX = 100; MinY = -1e-6; MaxY = 200.0; }
		if(myCategory_s=="1jet"){ return false;}
		kLogY = false;  xTitle =  "#Deltap_{T}(MMC, di-jet)";
		firstbin = 0; lastbin = 500; nbins = 100;  kAdjustLeftBin = false; kAdjustRightBin = false;
		xlat = 2.5; ylat = MaxY*0.9;
		cout<<"Info: "<<xTitle<<" "<<firstbin<<" "<<lastbin<<endl;
		kAutoMaxYaxis = true; AutoOffsetTimes = 1.5;
	  
	}else if(myVariable_s == "MMC_resonance_pt"){ 
		variable = myVariable_s;
		MinX = 0.; MaxX = 250.; MinY = 1e-6; MaxY = 650.0; 
		if(myCategory_s=="vbf"){MinX = 100; MaxX = 300.; MinY = 1e-6; MaxY = 650.0; }
		if(myCategory_s=="boosted"){MinX = 100; MaxX = 300.; MinY = 1e-6; MaxY = 1000.0; }
		if(myCategory_s=="1jet"){MinX = 100; MaxX = 300.; MinY = 1e-6; MaxY = 650.0; }
		if(myCategory_s=="0jet"){MinX = 100; MaxX = 300.; MinY = 1e-6; MaxY = 650.0; }
		kLogY = false; xTitle = "MMC resonance p_{T} [GeV]";
		firstbin = 0; lastbin = 250; nbins = 25; kAdjustLeftBin = false; kAdjustRightBin = false;
		xlat = 105; ylat = MaxY*0.9;
		kAutoMaxYaxis = true; AutoOffsetTimes = 1.6;
		
	}else if(myVariable_s == "esv_all_objects_FoxWolfram_R1"){
		variable = myVariable_s;
		if(myCategory_s=="vbf"){ MinX = 0; MaxX = 1; MinY = -1e-6; MaxY = 200.0; }
		if(myCategory_s=="1jet"){ MinX = 0; MaxX = 1; MinY = -1e-6; MaxY = 200.0; }
		kLogY = false;  xTitle =  "Fox-Wolfram R_{1}";
		firstbin = 0; lastbin = 1; nbins = 20;  kAdjustLeftBin = false; kAdjustRightBin = false;
		xlat = 0.02; ylat = MaxY*0.9;
		cout<<"Info: "<<xTitle<<" "<<firstbin<<" "<<lastbin<<endl;
		kAutoMaxYaxis = true; AutoOffsetTimes = 1.7;
	  
	}else if(myVariable_s == "esv_all_objects_FoxWolfram_R2"){
		variable = myVariable_s;
		if(myCategory_s=="vbf"){ MinX = 0; MaxX = 1; MinY = -1e-6; MaxY = 200.0; }
		if(myCategory_s=="1jet"){ MinX = 0; MaxX = 1; MinY = -1e-6; MaxY = 200.0; }
		kLogY = false;  xTitle =  "Fox-Wolfram R_{2}";
		firstbin = 0; lastbin = 1; nbins = 20;  kAdjustLeftBin = false; kAdjustRightBin = false;
		xlat = 0.02; ylat = MaxY*0.9;
		cout<<"Info: "<<xTitle<<" "<<firstbin<<" "<<lastbin<<endl;
		kAutoMaxYaxis = true; AutoOffsetTimes = 1.7;
	  
	}else if(myVariable_s == "esv_all_objects_sphericity"){
		variable = myVariable_s;
		MinX = 0; MaxX = 1; MinY = -1e-6; MaxY = 200.0; 
		if(myCategory_s=="vbf"){ MinX = 0; MaxX = 1; MinY = -1e-6; MaxY = 200.0; }
		if(myCategory_s=="1jet"){ MinX = 0; MaxX = 1; MinY = -1e-6; MaxY = 200.0; }
		kLogY = false;  xTitle =  "Sphericity";
		firstbin = 0; lastbin = 1; nbins = 25;  kAdjustLeftBin = false; kAdjustRightBin = false;
		xlat = 0.02; ylat = MaxY*0.9;
		cout<<"Info: "<<xTitle<<" "<<firstbin<<" "<<lastbin<<endl;
		kAutoMaxYaxis = true; AutoOffsetTimes = 1.3;
	  
	}else if(myVariable_s == "esv_all_objects_planarity"){
		variable = myVariable_s;
		if(myCategory_s=="vbf"){ MinX = 0; MaxX = 0.5; MinY = -1e-6; MaxY = 1200.0; }
		if(myCategory_s=="boosted"){ MinX = 0; MaxX = 0.5; MinY = -1e-6; MaxY = 1200.0; }
		if(myCategory_s=="1jet"){ MinX = 0; MaxX = 0.5; MinY = -1e-6; MaxY = 1200.0; }
		if(myCategory_s=="0jet"){ MinX = 0; MaxX = 0.5; MinY = -1e-6; MaxY = 1200.0; }
		kLogY = false;  xTitle =  "Planarity";
		firstbin = 0; lastbin = 1; nbins = 25;  kAdjustLeftBin = false; kAdjustRightBin = false;
		xlat = 0.02; ylat = MaxY*0.9;
		cout<<"Info: "<<xTitle<<" "<<firstbin<<" "<<lastbin<<endl;
		kAutoMaxYaxis = true; AutoOffsetTimes = 1.3;
	  
	}else if(myVariable_s == "esv_all_objects_aplanarity"){
		variable = myVariable_s;
		if(myCategory_s=="vbf"){ MinX = 0; MaxX = 0.5; MinY = -1e-6; MaxY = 1200.0; }
		if(myCategory_s=="boosted"){ MinX = 0; MaxX = 0.5; MinY = -1e-6; MaxY = 1200.0; }
		if(myCategory_s=="1jet"){ MinX = 0; MaxX = 0.5; MinY = -1e-6; MaxY = 1200.0; }
		if(myCategory_s=="0jet"){ MinX = 0; MaxX = 0.5; MinY = -1e-6; MaxY = 1200.0; }
		kLogY = false;  xTitle =  "Aplanarity";
		firstbin = 0; lastbin = 1; nbins = 25;  kAdjustLeftBin = false; kAdjustRightBin = false;
		xlat = 0.02; ylat = MaxY*0.9;
		cout<<"Info: "<<xTitle<<" "<<firstbin<<" "<<lastbin<<endl;
		kAutoMaxYaxis = true; AutoOffsetTimes = 1.3;
	  
	}else if(myVariable_s == "ditau_dR"){ 
		variable = myVariable_s;
		MinX = 0.0; MaxX = 6.0; MinY = 1e-6; MaxY = 1200.0; 
		if(myCategory_s=="vbf"){  MinX = 0.0; MaxX = 6.0; MinY = 1e-6; MaxY = 1200.0; }
		if(myCategory_s=="1jet"){  MinX = 0.0; MaxX = 6.0; MinY = 1e-6; MaxY = 1600.0; }
		kLogY = false; xTitle = "#DeltaR_{#tau#tau}";
		firstbin = 0; lastbin = 10; nbins = 20; kAdjustLeftBin = false; kAdjustRightBin = false;
		xlat = 0.2; ylat = MaxY*0.9;
		kAutoMaxYaxis = true; AutoOffsetTimes = 1.5;
		
	}else if(myVariable_s == "ditau_dEta"){ 
		variable = myVariable_s;
		if(myCategory_s=="vbf"){  MinX = 0.0; MaxX = 3.4; MinY = 1e-6; MaxY = 1000.0; }
		if(myCategory_s=="1jet" || myCategory_s== "boosted" || myCategory_s == "NoJetReq"){  MinX = 0.0; MaxX = 3.4; MinY = 1e-6; MaxY = 800.0; }
		kLogY = false; xTitle = "#Delta#eta_{#tau#tau}";
		firstbin = 0; lastbin = 5; nbins = 25; kAdjustLeftBin = false; kAdjustRightBin = true;
		xlat = 0.2; ylat = MaxY*0.9;
		kAutoMaxYaxis = true; AutoOffsetTimes = 1.3;
		
	}else if( myVariable_s == "tau_0_dijet_eta_centr" || myVariable_s == "tau_1_dijet_eta_centr" ){ 
		variable = myVariable_s;
		MinX = 0.0; MaxX = 1.0; MinY = 1e-6; MaxY = 2000.0;
		if(myCategory_s=="vbf"){ MinX = 0.0; MaxX = 1.0; MinY = 1e-6; MaxY = 2000.0; } ///ok
		if(myCategory_s=="1jet"){ return false; } ///has no meaning
		kLogY = false; 
		xTitle =  myVariable_s == "tau_0_dijet_eta_centr" ? "leading #tau centrality" : "subleading #tau centrality";
		firstbin = 0; lastbin = 1; nbins = 20; kAdjustLeftBin = false; kAdjustRightBin = false;
		xlat = 0.02; ylat = MaxY*0.9;
		kAutoMaxYaxis = true; AutoOffsetTimes = 1.3;
		
	}else if( myVariable_s == "tau_0_BDT_score" || myVariable_s == "tau_1_BDT_score"){ 
		variable = myVariable_s;
		MinX = 0.5; MaxX = 1.0; MinY = 1e-6; MaxY = 700.0; 
		if(myCategory_s=="vbf"){ MinX = 0.5; MaxX = 1.0; MinY = 1e-6; MaxY = 700.0; }
		if(myCategory_s=="1jet"){ MinX = 0.5; MaxX = 1.0; MinY = 1e-6; MaxY = 700.0; }
		kLogY = false; 
		xTitle =  myVariable_s == "tau_0_BDT_score" ? "leading #tau ID BDT score" : "subleading #tau ID BDT score";
		firstbin = 0; lastbin = 1; nbins = 50; kAdjustLeftBin = false; kAdjustRightBin = false;
		xlat = 0.51; ylat = MaxY*0.9;
		kAutoMaxYaxis = true; AutoOffsetTimes = 2;
		
	}else if( myVariable_s == "tau_0_pt" || myVariable_s == "tau_1_pt"){ 
		variable = myVariable_s;
		MinX = 20; MaxX = 120.0; MinY = 1e-6; MaxY = 500.0; 
		if(myCategory_s=="vbf"){ MinX = 20; MaxX = 120.0; MinY = 1e-6; MaxY = 500.0; }
		if(myCategory_s=="boosted"){ MinX = 20; MaxX = 120.0; MinY = 1e-6; MaxY = 500.0; }
		if(myCategory_s=="1jet"){ MinX = 20; MaxX = 120.0; MinY = 1e-6; MaxY = 500.0; }
		if(myCategory_s=="0jet"){ MinX = 20; MaxX = 120.0; MinY = 1e-6; MaxY = 500.0; }
		kLogY = false; 
		xTitle =  myVariable_s == "tau_0_pt" ? "leading #tau p_{T} [GeV]" : "subleading #tau p_{T} [GeV]";
		firstbin = 0; lastbin = 200; nbins = 40; kAdjustLeftBin = false; kAdjustRightBin = false;
		xlat = 25; ylat = MaxY*0.9;
		kAutoMaxYaxis = true; AutoOffsetTimes = 1.5;
		
	}else if( myVariable_s == "tau_0_tracks" || myVariable_s == "tau_1_tracks"){ 
		variable = myVariable_s;
		MinX = -0.5; MaxX = 4.5; MinY = 1e-6; MaxY = 5000.0; 
		if(myCategory_s=="vbf"){ MinX = -0.5; MaxX = 4.5; MinY = 1e-6; MaxY = 5000.0; }
		if(myCategory_s=="1jet"){ MinX = -0.5; MaxX = 4.5; MinY = 1e-6; MaxY = 5000.0; }
		kLogY = false; 
		xTitle =  myVariable_s == "tau_0_tracks" ? "leading #tau N tracks" : "subleading #tau N tracks";
		firstbin = -0.5; lastbin = 4.5; nbins = 5; kAdjustLeftBin = false; kAdjustRightBin = false;
		xlat = -0.2; ylat = MaxY*0.9;
		xNdivisions=505;
		kAutoMaxYaxis = true; AutoOffsetTimes = 1.3;
		
	}else if(myVariable_s == "met_centrality" ){ 
		variable = myVariable_s;
		MinX = -1.5; MaxX = 1.5; MinY = 1e-6; MaxY = 900.0;
		if(myCategory_s=="vbf"){MinX = -1.5; MaxX = 1.5; MinY = 1e-6; MaxY = 900.0;}
		if(myCategory_s=="1jet"){MinX = -1.5; MaxX = 1.5; MinY = 1e-6; MaxY = 900.0;}
		kLogY = false; xTitle = "#slash{E}_{T} centrality";
		firstbin = -1.5; lastbin = 1.5; nbins = 20; kAdjustLeftBin = false; kAdjustRightBin = false;
		xlat = -1.4; ylat = MaxY*0.9;
		kAutoMaxYaxis = true; AutoOffsetTimes = 1.3;
		
	}else if(myVariable_s == "dijet_mass"  ){ 
		variable = myVariable_s;
		MinX = 20.; MaxX = 750; MinY = 1e-6; MaxY = 500.0; 
		if(myCategory_s=="vbf"){MinX = 25.; MaxX = 750; MinY = 1e-6; MaxY = 500.0; } ///ok
		if(myCategory_s=="boosted"){MinX = 25.; MaxX = 750; MinY = 1e-6; MaxY = 500.0; } ///ok
		if(myCategory_s=="1jet"){MinX = 25.; MaxX = 750; MinY = 1e-6; MaxY = 500.0; } ///ok
		if(myCategory_s=="0jet"){MinX = 25.; MaxX = 750; MinY = 1e-6; MaxY = 500.0; } ///ok
		kLogY = false; xTitle = "di-jet mass [GeV]";
		firstbin = 0; lastbin = 1000; nbins = 40; kAdjustLeftBin = false; kAdjustRightBin = false;
		xlat = 25; ylat = MaxY*0.9;
		kAutoMaxYaxis = true; AutoOffsetTimes = 1.4;
		
	}else if(myVariable_s == "dijet_dEta" ){ 
		variable = myVariable_s;
		MinX = 0.; MaxX = 8.0; MinY = 1e-6; MaxY = 400.0; 
		if(myCategory_s=="vbf"){MinX = 0.; MaxX = 8.0; MinY = 1e-6; MaxY = 400.0; } /// ok
		if(myCategory_s=="1jet"){MinX = 0.; MaxX = 8.0; MinY = 1e-6; MaxY = 400.0; } ///meaningless
		kLogY = false; xTitle = "Di-jet #Delta#eta";
		firstbin = 0; lastbin = 10; nbins = 40; kAdjustLeftBin = false; kAdjustRightBin = false;
		xlat = 0.1; ylat = MaxY*0.9;
		kAutoMaxYaxis = true; AutoOffsetTimes = 1.3;
		
	}else if(myVariable_s == "dijet_eta1_x_eta2" ){ 
		variable = myVariable_s;
		MinX = -15.; MaxX = 15.0; MinY = 1e-6; MaxY = 1500.0; 
		if(myCategory_s=="vbf"){MinX = -15.; MaxX = 15.0; MinY = 1e-6; MaxY = 1500.0; } ///ok
		if(myCategory_s=="1jet"){MinX = -15.; MaxX = 15.0; MinY = 1e-6; MaxY = 1000.0; } ///no sense
		kLogY = false; xTitle = "di-jet #eta_{1} #times #eta_{2}";
		firstbin = -15; lastbin = 15; nbins = 30; kAdjustLeftBin = false; kAdjustRightBin = false;
		xlat = -14; ylat = MaxY*0.9;
		kAutoMaxYaxis = true; AutoOffsetTimes = 2;
		
	}else if(myVariable_s == "met_phi"){ 
		variable = myVariable_s;
		MinX = -TMath::Pi(); MaxX = TMath::Pi();
		if(myCategory_s=="vbf"){ MinY = 1e-6; MaxY = 1000.0; }
		if(myCategory_s=="1jet"){ MinY = 1e-6; MaxY = 1000.0; }
		kLogY = false; xTitle = "E_{T}^{miss} #phi [rad]";
		firstbin = -TMath::Pi(); lastbin = TMath::Pi(); nbins = TMath::TwoPi()/0.4; kAdjustLeftBin = false; kAdjustRightBin = false;
		xlat = -3; ylat = MaxY*0.9;
		kAutoMaxYaxis = true; AutoOffsetTimes = 1.7;
		
	}else if(myVariable_s == "ditau_cosTheta" ){ 
		variable = myVariable_s;
		if(myCategory_s=="vbf"){ MinX = -1.05; MaxX = 1.05; MinY = 1e-6; MaxY = 1000.0; }
		if(myCategory_s=="1jet"){ MinX = -1.05; MaxX = 1.05; MinY = 1e-6; MaxY = 900.0; }
		kLogY = false; xTitle = "cos#alpha_{#tau#tau}";
		firstbin = -1.05; lastbin = 1.05; nbins = 11; /*zero right in the middle*/ kAdjustLeftBin = true; kAdjustRightBin = true;
		xlat = -1; ylat = MaxY*0.9;
		kAutoMaxYaxis = true; AutoOffsetTimes = 1.6;
		
	}else if(myVariable_s == "ditau_mass_vis"){ 
		variable = myVariable_s;
		if(myCategory_s=="vbf"){ MinX = 20; MaxX = 200; MinY = 1e-6; MaxY = 1000.0; }
		if(myCategory_s=="1jet"){ MinX = 20; MaxX = 200; MinY = 1e-6; MaxY = 800.0; }
		kLogY = false; xTitle = "m^{visible}_{#tau#tau} [GeV]";
		firstbin = 0; lastbin = 300; nbins = 60;  kAdjustLeftBin = false; kAdjustRightBin = false;
		xlat = 25; ylat = MaxY*0.9;
		kAutoMaxYaxis = true; AutoOffsetTimes = 1.3;
		
	}else if(myVariable_s == "ditau_mass_col"){ 
		variable = myVariable_s;
		if(myCategory_s=="vbf"){ MinX = 0; MaxX = 180; MinY = 1e-6; MaxY = 800.0; }
		if(myCategory_s=="boosted"){ MinX = 0; MaxX = 180; MinY = 1e-6; MaxY = 800.0; }
		if(myCategory_s=="1jet"){ MinX = 0; MaxX = 180; MinY = 1e-6; MaxY = 800.0; }
		if(myCategory_s=="0jet"){ MinX = 0; MaxX = 180; MinY = 1e-6; MaxY = 800.0; }
		kLogY = false; xTitle = "m^{collinear}_{#tau#tau} [GeV]";
		firstbin = 0; lastbin = 300; nbins = 60;  kAdjustLeftBin = false; kAdjustRightBin = false;
		xlat = 5; ylat = MaxY*0.9;
		kAutoMaxYaxis = true; AutoOffsetTimes = 1.5;
		
	}else if(myVariable_s == "ditau_mass_mmc"){ 
		variable = myVariable_s;
		MinX = 60; MaxX = 260; MinY = 1e-6; MaxY = 1000.0; 
		if(myCategory_s=="vbf"){ MinX = 50; MaxX = 250; MinY = 1e-6; MaxY = 1000.0; }
		if(myCategory_s=="1jet"){ MinX = 50; MaxX = 250; MinY = 1e-6; MaxY = 1000.0; }
		kLogY = false; xTitle = "m^{MMC}_{#tau#tau} [GeV]";
		firstbin = 0; lastbin = 250; nbins = 25;  kAdjustLeftBin = false; kAdjustRightBin = true;
		xlat = 65; ylat = MaxY*0.9;
		kAutoMaxYaxis = true; AutoOffsetTimes = 1.3;

	}else if(myVariable_s == "jet_0_eta" || "jet_1_eta"){ 
		variable = myVariable_s;
		MinX = -5; MaxX = 5; MinY = -1e-6; MaxY = 300.0; 
		if(myCategory_s=="vbf"){ MinX = -5; MaxX = 5; MinY = -1e-6; MaxY = 300.0; }
		if(myCategory_s=="boosted"){ MinX = -5; MaxX = 5; MinY = -1e-6; MaxY = 300.0; }
		if(myCategory_s=="1jet"){ MinX = -5; MaxX = 5; MinY = -1e-6; MaxY = 300.0; }
		if(myCategory_s=="0jet"){ MinX = -5; MaxX = 5; MinY = -1e-6; MaxY = 300.0; }
		kLogY = false;  xTitle =  myVariable_s == "jet_0_eta" ? "leading jet #eta" : "subleading jet #eta";
		firstbin = -5; lastbin = 5; nbins = 40;  kAdjustLeftBin = false; kAdjustRightBin = false;
		xlat = -4.5; ylat = MaxY*0.9;
		kAutoMaxYaxis = true; AutoOffsetTimes = 1.7;
		
	}else if(myVariable_s == "jet_0_pt" || "jet_1_pt"){
		variable = myVariable_s;
		if(myCategory_s=="vbf"){ MinX = 10.; MaxX = 300; MinY = -1e-6; MaxY = 300.0; }
		if(myCategory_s=="boosted"){ MinX = 10.; MaxX = 300; MinY = -1e-6; MaxY = 300.0; }
		if(myCategory_s=="1jet"){ MinX = 10.; MaxX = 300; MinY = -1e-6; MaxY = 300.0; }
		if(myCategory_s=="0jet"){ MinX = 10.; MaxX = 300; MinY = -1e-6; MaxY = 300.0; }
		kLogY = false;  xTitle =  myVariable_s == "jet_0_pt" ? "leading jet pT" : "subleading jet pT";
		firstbin = 10; lastbin = 300; nbins = 29;  kAdjustLeftBin = false; kAdjustRightBin = true;
		xlat = 15; ylat = MaxY*0.9;
		kAutoMaxYaxis = true; AutoOffsetTimes = 1.5;
		
	}else{
		cout<<"\nPlease, choose a good variable. Exiting ..."<<endl;
		return false;
	}
	
	///more specific drawing options

	bool	kEWK_subtraction 	= true;
	bool	kZtautau_subtraction= true;
	bool	kShow_StatErrorBands= true;
	bool	ApplyEventWeights	= true;

	int		SignalZoom 			=  10;
	string 	classifier 			= "BDT";
	string 	QCDmodel 			= "notOS";// notOS SS;
	string 	version 			= "v10";
	string	region 				= "CR_dEta";//CR SR CR_dEta
	string	purpose 			= "Plot";
	int 	Hmass 				= 125;
	string 	hmass 				= hc.GetStringFromInt(Hmass);
	string plots_subdir 		= "VBF_sidebandCR_SS";
	string  filenamecore		= "plots/"+plots_subdir+"/plot_"+variable+"_"+category+"_"+hmass+"_"+region+"_"+QCDmodel+"_"+version;
	string 	fn 					= filenamecore+".root";
	string 	fn_pdf 				= filenamecore+".pdf";
	bool 	kShowSignalAlone 	= true;
	bool 	kShowSpectrumWithSignal = false;
	bool	kProducePDF				= true;

	string  tag                             = "50Trees_500LeafEvts_NoHpT"; // vbf_boosted                                                                                           
	//      string  tag                             = "50Trees_500LeafEvts_NoHpT_QCDSS";//1jet 0 jet                         

	//	bool	kShowData = region == "CR"; /// overlay data only in Control Region - SR remains blind
	bool	kShowData = 1; /// overlay data only in Control Region - SR remains blind

	double RatioMinY= 0.55; 
	double RatioMaxY = 1.45; 
	
	///how to obtain ntuples
	hc.SetTreeName("mva"); 
	hc.SetVersion(version); 
	hc.SetPath("../../Ntuples/");

	///list of MC samples
	vector<int> RunsVector = hc.GetRunsVector(Hmass);
	
	///data tree
	cout<<"\ncreating tree map for data"<<endl;
	//	TTree *tData = hc.GetTreeData( );//get data from org ntuples
		TTree *tData = hc.GetTreeDataMVA( "*", classifier, category_file, hmass, tag);//katy get data from mva ntuples
	hc.SetLumiPerRunMap();
	
	int nDataEntries = tData->GetEntries();
	if(!nDataEntries) {cout<<"unable to get data tree entries. Exiting... "<<endl; return false;}
	
	///lumi
	double DataLumi = hc.GetRunsListTotalLumi("inb");
	cout<<"\nData lumi "<<DataLumi<<" nb-1"<<endl<<endl;
	double lumi_fb = DataLumi/1e6;
	char lumi_number[24];
	sprintf(lumi_number, "%.2f", lumi_fb);
	string lumi_str = lumi_number;
	
	/// mc tree map
	map<int, TTree *> tmap;
	cout<<"\ncreating tree map for mc ..."<<endl;
	for(vector<int>::iterator it=RunsVector.begin(); it != RunsVector.end(); it++){
		if( *it >= 800000) continue;
		//		tmap.insert ( pair<int, TTree *>(*it,  hc.GetTreeMC(hc.GetStringFromInt(*it)) ) );
				tmap.insert ( pair<int, TTree *>(*it,  hc.GetTreeMCMVA( hc.GetStringFromInt(*it), classifier, category_file, hmass, tag) ) );//katy
	}
	
	
	///histogramming
	cout<<"\nbooking histograms ..."<<endl;
	double BinW = (lastbin - firstbin)/nbins;
	cout<<"\nbin width : "<<BinW<<endl;
	
	TH1D *hist_Data = new TH1D("hist_Data",	"",	nbins, firstbin, lastbin);
	
	TH1D *hist_Data_TrackFit = new TH1D("hist_Data_TrackFit",	"",	nbins, firstbin, lastbin);
	
	TH1D *hist_QCD = new TH1D("hist_QCD",	"",	nbins, firstbin, lastbin);
	
	TH1D *hist_BKG = new TH1D("hist_BKG",	"",	nbins, firstbin, lastbin);
	
	TH1D *hSignal 		= new TH1D("hSignal","",	nbins, firstbin, lastbin);
	
	TH1D *hSpectrum0 	= new TH1D("hSpectrum0","",	nbins, firstbin, lastbin);
	
	TH1D *hSpectrum1 	= new TH1D("hSpectrum1","",	nbins, firstbin, lastbin);
	
	TH1D *hSpectrum2 	= new TH1D("hSpectrum2","",	nbins, firstbin, lastbin);
	
	TH1D *hSpectrum3 	= new TH1D("hSpectrum3","",	nbins, firstbin, lastbin);
	
	
	map<int, TH1D *> hmap_Sig;
	map<int, TH1D *> hmap_Bkg;
	for(vector<int>::iterator it=RunsVector.begin(); it != RunsVector.end(); it++){
		hmap_Sig.insert ( pair<int,TH1D *>(*it, new  TH1D("",	"",	nbins, firstbin, lastbin)) );
		hmap_Bkg.insert ( pair<int,TH1D *>(*it, new  TH1D("",	"",	nbins, firstbin, lastbin)) );
	}
	
	TCut hweight("");
	if (ApplyEventWeights){
	 hweight = "event_weight";
	 cout<<"\nincluding event weights : "<<hweight<<endl;
	}
	
	///give names
	cout<<"\nrenaming plots ..."<<endl;
	hc.SetHistoNames1D(hmap_Sig, "OS");
	hc.SetHistoNames1D(hmap_Bkg, QCDmodel);

	///plot making
	cout<<"\nCuts for search region : \n"<<hweight * hc.GetCut(category, "OS", purpose,region).GetTitle()<<endl;

	cout<<"\nfilling up histograms ..."<<endl;
	/// -- data
	hc.MakePlot( tData, hist_Data,  hc.GetCut(category, "OS", purpose,region), variable );
	/// -- data - Track Fit and QCD normalization
	hc.MakePlot( tData, hist_Data_TrackFit,  hc.GetCut(category, "OS", "TrackFit",region), variable );
	/// -- QCD from data
	hc.MakePlot( tData, hist_QCD,  hc.GetCut(category, QCDmodel, purpose, region), variable );
	/// -- MC search region
	for(map<int, TH1D *>::iterator it = hmap_Sig.begin(); it != hmap_Sig.end(); it++){
		if(it->first < 800000)
			hc.MakePlot(tmap[it->first], it->second, hweight * hc.GetCut(category, "OS", purpose, region), variable );	
	}
	/// -- MC bkg model - for bkg subtraction
	for(map<int, TH1D *>::iterator it = hmap_Bkg.begin(); it != hmap_Bkg.end(); it++){
		if(it->first < 800000)
			hc.MakePlot(tmap[it->first], it->second, hweight * hc.GetCut(category, QCDmodel, purpose, region), variable );
	}
	
	///normalize all MC to data lumi
	cout<<"\nhistograms normalization"<<endl;
	for(map<int, TH1D *>::iterator it = hmap_Sig.begin(); it != hmap_Sig.end(); it++){
		if(it->first < 800000){
			it->second->Scale( mcbank.Get_Norm(it->first, DataLumi) );
		}
	}
	for(map<int, TH1D *>::iterator it = hmap_Bkg.begin(); it != hmap_Bkg.end(); it++){
		if(it->first < 800000){
			it->second->Scale( mcbank.Get_Norm(it->first, DataLumi) );
		}
	}
	///fill inclusive MC plots
	cout<<"\nmaking inclusive histos ..."<<endl;
	for(vector<int>::iterator it=RunsVector.begin(); it != RunsVector.end(); it++){
		if( *it >= 800000) continue;
		
		if(! hmap_Sig[*it]->GetEntries() )  cout<<"empty signal histogram : "<<*it<<endl;
		if(! hmap_Bkg[*it]->GetEntries() )  cout<<"empty bkg histogram : "<<*it<<endl;
	
		if( hc.Is("Higgs", *it) ) {
			hmap_Sig[800000]->Add( hmap_Sig[*it]); 
			hmap_Bkg[800000]->Add( hmap_Bkg[*it]);
		}
		if( hc.Is("Ztautau", *it) ) {
			hmap_Sig[800001]->Add( hmap_Sig[*it]); 
			hmap_Bkg[800001]->Add( hmap_Bkg[*it]);
		}
		if( hc.Is("Wtaunu", *it) ) {
			hmap_Sig[800002]->Add( hmap_Sig[*it]); 
			hmap_Bkg[800002]->Add( hmap_Bkg[*it]);
		}
		if( hc.Is("Top", *it) ) {
			hmap_Sig[800003]->Add( hmap_Sig[*it]); 
			hmap_Bkg[800003]->Add( hmap_Bkg[*it]);
		}
		if( hc.Is("Dibosons", *it) ) {
			hmap_Sig[800004]->Add( hmap_Sig[*it]); 
			hmap_Bkg[800004]->Add( hmap_Bkg[*it]);
		}
		if( hc.Is("Electroweak", *it) ) {
			hmap_Sig[800005]->Add( hmap_Sig[*it]); 
			hmap_Bkg[800005]->Add( hmap_Bkg[*it]);
		}
	}

	///Perfrom EWK subtraction from QCD============================================================
	if(kEWK_subtraction){
		cout<<"\nSubtracting ewk bkg from QCD bkg"<<endl;
		cout<<"\tQCD integral before "<<hist_QCD->Integral()<<endl;
		hist_QCD->Add(hmap_Bkg[800005], -1);
		cout<<"\tQCD integral after "<<hist_QCD->Integral()<<endl<<endl;
		///check for negative bins here
		CheckNegativeBinContent(hist_QCD, "QCD - ewk bkg removal");
	}
	
	if(kZtautau_subtraction){
		cout<<"\nSubtracting Ztautau bkg from QCD bkg"<<endl;
		cout<<"\tQCD integral before "<<hist_QCD->Integral()<<endl;
		hist_QCD->Add(hmap_Bkg[800001], -1);
		cout<<"\tQCD integral after "<<hist_QCD->Integral()<<endl<<endl;
		///check for negative bins here
		CheckNegativeBinContent(hist_QCD, "QCD - Ztautau bkg removal");
	}

	///normalize QCD =============================================================================

	//new way without Noels SR and CR
	double QCDnorm =  QCD_TrackFitFactor * hist_Data_TrackFit->Integral(); 
	double QCD_integral(0); QCD_integral= hist_QCD->Integral();
	if(QCD_integral < 1e-8) {  cout<<"QCD Integral "<<QCD_integral<<endl; cout<<"Empty QCD histo. Bye bye ..."<<endl; exit(0); }
	double QCDweight_f = QCDnorm/QCD_integral;
	
	cout<<"\nNormalize QCD bkg to Track Fit"<<endl;
	cout<<"\tQCD target norm  "<<QCDnorm<<endl;
	cout<<"\tQCD final norm factor (using fQCD)  "<<QCDweight_f<<endl;
	
	//apply qcd weigth
	cout<<"\tQCD integral before "<<hist_QCD->Integral()<<endl;
	hist_QCD->Scale( QCDweight_f );
	cout<<"\tQCD integral after "<<hist_QCD->Integral()<<endl<<endl;
	
	
	///normalize Ztautau ==========================================================================
	
	//new way without Noels SR and CR
	double Znorm =  Z_TrackFitFactor * hist_Data_TrackFit->Integral(); 
	double Z_integral = hmap_Sig[800001]->Integral();
	if(Z_integral < 1e-6) { cout<<"Empty Ztautau histo. Bye bye ..."<<endl; exit(0); }
	double Zweight_f = Znorm / Z_integral;
	
	cout<<"\nNormalize Z bkg to Track Fit"<<endl;
	cout<<"\tZ target norm  "<<Znorm<<endl;
	cout<<"\tZ final norm factor (using fZ)  "<<Zweight_f<<endl;
	
		//apply qcd weigth
	cout<<"\tZ integral before "<<hmap_Sig[800001]->Integral()<<endl;
	hmap_Sig[800001]->Scale(Zweight_f);
	cout<<"\tZ integral after "<<hmap_Sig[800001]->Integral()<<endl<<endl;
	
		
	///output file (before canvas)
	TFile *f = new TFile( fn.c_str(), "recreate");
	

	cout<<"\nentries : integral"<<endl;
	cout<<"H    "<<hmap_Sig[800000]->GetEntries()<<" : "<<hmap_Sig[800000]->Integral()<<endl;
	cout<<"Z    "<<hmap_Sig[800001]->GetEntries()<<" : "<<hmap_Sig[800001]->Integral()<<endl;
	cout<<"EWK  "<<hmap_Sig[800005]->GetEntries()<<" : "<<hmap_Sig[800005]->Integral()<<endl;
	cout<<"QCD  "<<hist_QCD->GetEntries()<<" : "<<hist_QCD->Integral()<<endl;
	cout<<"Data  "<<hist_Data->GetEntries()<<" : "<<hist_Data->Integral()<<endl;
	

	
	///signal, individual plot
	hSignal->Add(hmap_Sig[800000], 1);
	
	///zoom signal
	if(SignalZoom > 0) hSignal->Scale( SignalZoom );
	
	//Katys rescaling________________________
	//double Rescaling[25] = { 1, 1, 1, 1, 1, 1,1.33168,1.19329, 1.14173, 1.08955, 1.10045, 1.08549, 1.0811, 1.01912, 1.04977, 0.998825, 0.934772, 0.970863, 0.981011, 1.04149, 0.980937, 0.97658, 1.48107, 0.914512, 1.};//from no jet reverse deta. before MC weight fix and changing of subtraction-norm order.  Norm factor = *0.9387
 
	double Rescaling[25] = { 1, 1, 1, 1, 1, 1,1.34455 ,1.20571, 1.12176, 1.07856, 1.08823, 1.06865, 1.06912, 1.00845, 1.0285, 0.98994, 0.93839, 0.96106, 0.98538, 1.01263, 0.99138, 0.93509, 1.54444, 0.781776, 1.}; //SS.  Data = 14760, Background = 14016.23  NormFactor = 0.9496

	//	double Rescaling[25] = { 1, 1, 1, 1, 1, 1,1.3222  ,1.03857, 1.09629, 1.08925, 1.07084, 1.09506, 1.04  , 1.00355, 0.99971, 0.98935, 0.98888, 0.98903, 1.06368, 1.05631, 1.16195, 1.07287, 1.50473, 0.77056, 1.};// notOS. 


	for(int i = 0 ; i<nbins; i++){
	  //	  cout<<"i: "<<i<<" Low bin edge: "<<hist_QCD->GetBinLowEdge(i+1)<<" BinContent: "<<hist_QCD->GetBinContent(i+1)<<" ScaleFactor: "<<Rescaling[i]<<" normalized scale factor: "<<Rescaling[i]*0.9387<<endl;
	  cout<<" Low bin edge: "<<hist_QCD->GetBinLowEdge(i+1)<<" BinContent: "<<hist_QCD->GetBinContent(i+1)<<" ScaleFactor: "<<Rescaling[i]<<" normalized scale factor: "<<Rescaling[i]*0.9496<<endl;
	  //	    hist_QCD->SetBinContent(i+1,hist_QCD->GetBinContent(i+1)*Rescaling[i]);
	  //    hist_QCD->SetBinContent(i+1,hist_QCD->GetBinContent(i+1)*Rescaling[i]*0.9387);//normalized
        }
	//End Katys rescaling________________________

	///spectra
	hSpectrum0->Add(hist_QCD, 1);			/// qcd
	
	hSpectrum1->Add(hSpectrum0, 1);		/// qcd + ewk
	hSpectrum1->Add(hmap_Sig[800005], 1); 
	
	hSpectrum2->Add(hSpectrum1, 1);		/// qcd + ewk + Z
	hSpectrum2->Add(hmap_Sig[800001], 1);
	
	hSpectrum3->Add(hSpectrum2, 1);		/// qcd + ewk + Z + signal
	hSpectrum3->Add(hmap_Sig[800000], SignalZoom);
	

	hist_BKG->Add(hSpectrum2, 1.0); ///higgs excluded of course
	
	///transform bkg to grap to obtain the stat error band
	TGraphAsymmErrors *gBkg = new TGraphAsymmErrors(hSpectrum2);
	
	///ratio 
	TH1D *h_Data_over_BKG = hc.GetHistoRatio(hist_Data, hist_BKG);

	///Canvas	
	TCanvas *c = new TCanvas("c","Stack Plots", 10, 10, 700, 700);
	c->SetFillColor(0);
	c->SetBorderMode(0);
	c->SetBorderSize(0);
	c->SetFrameBorderMode(0);
	gStyle->SetOptStat(0);
	gStyle->SetOptTitle(0);
	///
	TH1D *hEmpty1 = new TH1D("hEmpty1",	"",	nbins, firstbin, lastbin);
	TH1D *hEmpty2 = new TH1D("hEmpty2",	"",	nbins, firstbin, lastbin);
	int font = 82;
	///Up
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
		
	hEmpty1->Draw();
	

   
  	
	hc.SetStyle(hist_Data, "data", fillcolor);
	hc.SetStyle(hSpectrum0, "spectrum0", fillcolor);
	hc.SetStyle(hSpectrum1, "spectrum1", fillcolor);
	hc.SetStyle(hSpectrum2, "spectrum2", fillcolor);
	hc.SetStyle(hSpectrum3, "spectrum3", fillcolor);
	hc.SetStyle(hSignal, "signal");


	if(kShowSpectrumWithSignal) hSpectrum3->Draw("hist same");
	hSpectrum2->Draw("hist same");
	hSpectrum1->Draw("hist same");
	hSpectrum0->Draw("hist same");
	
	if(kShowSignalAlone) hSignal->Draw("hist same");
	
	if(kShow_StatErrorBands){
		gBkg->SetFillColor(kGray+2);
		gBkg->SetFillStyle(3004);
		gBkg->Draw("E2");
	}
	
	if(kShowData) hist_Data->Draw("ep same");
	
	
	
			
	if(kLogY) gPad->SetLogy();
	gPad->RedrawAxis();
	
// 	gPad->Modified(); 
// 	gPad->Update();

	TLegend *leg = new TLegend(0.4,0.6,0.92,0.92,NULL,"brNDC");
	leg->SetBorderSize(1);
	leg->SetLineColor(15);
	leg->SetLineStyle(1);
	leg->SetLineWidth(1);
	leg->SetFillColor(19);
	leg->SetFillStyle(3002);
	leg->SetTextFont(42); 
	leg->SetTextSize(0.03); 
	string legH = "Higgs m_{H} = " + hmass + " GeV (#sigma_{SM} #times "+ hc.GetStringFromInt(SignalZoom)+")";
		
	string luminosity = "#scale[0.75]{#int}dtL = "+lumi_str+" fb^{-1}";
	leg->AddEntry(hist_Data, ("2012 Data #sqrt{s} = 8 TeV, "+luminosity).c_str(),"lp");
	if(kShowSpectrumWithSignal) 
		leg->AddEntry(hSpectrum3, legH.c_str(),"lpf");
	else if(kShowSignalAlone)
		leg->AddEntry(hSignal, legH.c_str(),"l");
	else{
		//do nothing
	}
	leg->AddEntry(hSpectrum2,"Z/#gamma* #rightarrow #tau#tau","lpf");
	leg->AddEntry(hSpectrum1,"Electroweak","lpf");
	leg->AddEntry(hSpectrum0,"QCD multi-jets","lpf");
			
	
	leg->Draw();
   

	string lat_categ = 	
		category == "vbf" ? "VBF" :
		category == "boosted" ? "Boosted" :
	  	category == "1jet" ? "1-jet" :
	  	category == "0jet" ? "0-jet" : 
	        category == "NoJetReq" ? "No Jet Requirement" : 
			"Planet earth";

	if( kAutoMaxYaxis )  ylat = maxim_y_new*0.9;
	
	string thisregion = region == "CR" ? "Control Region" : region == "SR" ? "Signal Region" :region == "all" ? "No Mass Window" : region == "CR_dEta" ? "Reverse #tau#tau #Delta#eta CR": "which Region??";
	string category_region = "#splitline{#tau_{h} #tau_{h} : "+lat_categ+" category}{"+thisregion+"}";
	TLatex *tex = new TLatex( xlat, ylat, category_region.c_str() );
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
	
	///Down
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
				
	hEmpty2->GetYaxis()->SetTitle("#frac{Data}{Model}");			
	hEmpty2->GetYaxis()->SetTitleSize(0.17);
	hEmpty2->GetYaxis()->SetTitleOffset(0.34);	
	hEmpty2->GetYaxis()->SetTitleFont(font);
	hEmpty2->GetYaxis()->CenterTitle(1);
	hEmpty2->GetYaxis()->SetNdivisions(105);
	
	if(xNdivisions) hEmpty2->GetXaxis()->SetNdivisions( xNdivisions );
					
	hEmpty2->Draw();

// 	int ci5 = TColor::GetColor("#cfcc9f");
// 	int ci10 = TColor::GetColor("#e7e1bc");
// 	int ci20 = TColor::GetColor("#f1edda");
  
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
	box5->Draw("same");
	
	hc.SetStyle(h_Data_over_BKG, "ratio");
	if(kShowData) h_Data_over_BKG->Draw("ep same");

	//print ratio from NoJet-RevDeta CR to be used for katy's QCD scaling
	for(int i = 0 ; i<nbins; i++){
	  cout<<"Ratio BinContent: "<<i+1<<" "<< h_Data_over_BKG->GetBinContent(i) <<endl;

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

	
	cout<<fn<<endl;
	f->cd();
	c->Write();
	f->Close();
	
		
	
	
	cout<<"\nData tree entries : "<<tData->GetEntries()<<" <--- check if same with Make2DTrackHistos.C in TrackFit"<<endl;
	
	return true;
}


void CheckNegativeBinContent(TH1D *h, const string &s){
	cout<<"Checking "<<s<<" for bins with negative value"<<endl;
	bool found(false);
	int n = h->GetNbinsX();
	for(int i = 1; i <= n; i++){
		
		double bc = h->GetBinContent(i);
		
		if( bc < 0 ) {
			cout<<" negative bin content "<<bc<<" bin "<<i<<" "<<h->GetBinLowEdge(i)<<" - "<<h->GetBinLowEdge(i)+h->GetBinWidth(i)
					<<endl<<endl;
			
			found = true;
		}
	}
	
	if(!found) cout<<"\n"<<s<<" is OK"<<endl;
	cout<<endl;
}
