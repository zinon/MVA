// @(#)root/tmva $Id: TMVAClassificationHadHad3.C 75129 2013-03-08 11:51:15Z zenon $
/**********************************************************************************
 *                                  *
 * The methods to be used can be switched on and off by means of booleans, or     *
 * via the prompt command, for example:                                           *
 *                                                                                *
 *    root -l ./TMVAClassificationHadHad.C\(\"Fisher,Likelihood\"\)                     *
 *                                                                                *
 * Launch the GUI via the command:                                                *
 *                                                                                *
 *    root -l ./TMVAGui.C                                                         *
 *                                                                                *
 **********************************************************************************/

#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <iterator>

#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TObjString.h"
#include "TSystem.h"
#include "TROOT.h"


#include "TMVAGui.C"

#if not defined(__CINT__) || defined(__MAKECINT__)
// needs to be included when makecint runs (ACLIC)
#include "TMVA/Factory.h"
#include "TMVA/Tools.h"
#endif


#include "HelperClass.h"
#include "MonteCarloBank.h"

using namespace std;

void TMVAClassificationHadHad3( TString myMethodList = "" )
{

//TO DO:
	//
// add ggF in testing when is not in training
	//

  
	///to define:
	string	PartUsedForTraining = "A"; // A, B, AB
	string 	treename			= "mva";
	string 	purpose				= "MVA";
	string 	category 			= "2jet";
	string	region 				= "all";//all now means MMC >80
	string 	version 			= "v8";
	int 	Hmass 				= 125;
	bool    kAllHiggsMasses		= false;//if true: (a) Hmass is ignored (b) will call HelperClass::GetRunsVector() with all mass points
	int		HmassMin 			= 100; // only if kAllHiggsMasses
	int		HmassMax 			= 150; // only if kAllHiggsMasses
	bool 	kVBF 				= true;
	bool 	kGGF 				= false;
	bool 	kWH			       	= false;
	bool 	kZH 				= false;
	bool 	kZtautau			= true;
	//bool 	kWtaunu				= true;
	bool 	kElwk				= true;
	bool 	kQCD				= true;
	//string QCDmodel = "notOS";
	 
	
	///Adaptive boost
	bool 	kBDT 				=  myMethodList.SubString("BDT").Length() > 0;
	//This is overwritten below!!!
	string  BDT_NTrees			= "47";
	string  BDT_nEventsMin		= "500";
	string  BDT_MaxDepth		= "100000";
	string 	BDT_BoostType		= "AdaBoost";
	string 	BDT_AdaBoostBeta 	= "0.5";
	string	BDT_UseYesNoLeaf	= "False";
	
	/// Gradient boost
	bool 	kBDTG				= myMethodList.SubString("BDTG").Length() > 0;
	
	///to define: This is a list of possible variables to use in the training.  Add the ones you wish to use
	vector<string> mVars; typedef vector<string>::iterator ITRS;


	///overwrite BDT parameters
	if(category == "2jet"){
		BDT_NTrees 			= "47";
		BDT_nEventsMin		= "500";
		BDT_MaxDepth 		= "100000";
		BDT_BoostType		= "AdaBoost";
		BDT_AdaBoostBeta 	= "0.5";
		BDT_UseYesNoLeaf	= "False";
		
	}else if (category == "1jet"){
		BDT_NTrees 			= "53";
		BDT_nEventsMin		= "440";
		BDT_MaxDepth 		= "100000";
		BDT_BoostType		= "AdaBoost";
		BDT_AdaBoostBeta 	= "0.5";
		BDT_UseYesNoLeaf	= "False";
		
	}else if (category == "0jet"){
		
	}else{
		
	}
	
	///variable lists
	if(category == "2jet"){
		mVars.push_back("ditau_dR");//
		mVars.push_back("tau_0_dijet_eta_centr");//
		mVars.push_back("tau_1_dijet_eta_centr");//
		mVars.push_back("met_centrality");//
		mVars.push_back("MMC_resonance_pt");//
		mVars.push_back("dijet_mass");//
		mVars.push_back("dijet_dEta");//
		mVars.push_back("dijet_eta1_x_eta2");//
		
				//other candidate variables:
		//mVars.push_back("dijet_dEta_x_sign1_x_sign2");//
				//mVars.push_back("met_et");
				//mVars.push_back("esv_all_objects_sphericity");
				//mVars.push_back("tau_0_BDT_score");
				//mVars.push_back("tau_1_BDT_score");
				//mVars.push_back("ditau_dEta");
				//mVars.push_back("tau_0_closest_jet_dR");
				//mVars.push_back("tau_1_closest_jet_dR");
				//mVars.push_back("ditau_VecSumPt");
				//mVars.push_back("ditau_dijet_met_VecSumPt");
				//mVars.push_back("ditau_met_dPhi");
				//mVars.push_back("esv_all_objects_FoxWolfram_R1");
				
	}else if (category == "1jet"){
		mVars.push_back("ditau_dR");
		mVars.push_back("MMC_resonance_pt");
		mVars.push_back("esv_all_objects_sphericity");
		mVars.push_back("met_centrality");
		mVars.push_back("ditau_colapprox_x0");
		mVars.push_back("ditau_colapprox_x1");
				
				//other candidate variables:
				//mVars.push_back("met_et");
		
	}else if (category == "0jet"){
		
	}else{
		
	}

	///Default MVA methods to be trained + tested
	std::map<std::string,int> Use;

   ///to define:  Boosted Decision Trees
	Use["BDT"]             = kBDT; // uses Adaptive Boost
	Use["BDTG"]            = kBDTG; // uses Gradient Boost
	Use["BDTB"]            = 0; // uses Bagging
	Use["BDTD"]            = 0; // decorrelation + Adaptive Boost
	Use["BDTF"]            = 0; // allow usage of fisher discriminant for node splitting 
	
	///external classes
	gSystem->Load("../../HelperClass/HelperClass_cpp.so");
	gSystem->Load("../../MonteCarloBank/MonteCarloBank_cpp.so");

	HelperClass hc;
	hc.SetTreeName(treename);
	hc.SetVersion(version);
	hc.SetPath("../../Ntuples/");
	
	MonteCarloBank mcb;

	///names
	string 	hmass = kAllHiggsMasses ? "allmasses" : hc.GetStringFromInt(Hmass);
	string	outPrefix = "TMVAClassificationHadHad";
	string	classi  = kBDT ? "BDT" : kBDTG ? "BDTG" : "none";
	string 	outCoreName = outPrefix + "_" + classi + "_PartTrained"+PartUsedForTraining+"_"+category+"_"+hmass+"_"+version;
	string 	outRootFileName = outCoreName+".root";
	string	outputWeightFileName = outCoreName;
			
	///list of MC samples
	cout<<"\ncreating the MC list ..."<<endl;
	vector<int> RunsVector = kAllHiggsMasses ? hc.GetRunsVector() : hc.GetRunsVector(Hmass);

	///get MC trees
	map<int, TTree *> tmap;
	for(vector<int>::iterator it=RunsVector.begin(); it != RunsVector.end(); it++){
		if( *it >= 800000) continue;
		tmap.insert ( pair<int, TTree *>(*it,  hc.GetTreeMC(*it) ) );
		cout<<"MC "<<*it<<" entries "<<tmap[*it]->GetEntries()<<endl;
	}
	
	///get data tree
	TTree *tdata = hc.GetTreeData();
	cout<<"\nData events "<<tdata->GetEntries()<<endl;


   /// This loads the library
	TMVA::Tools::Instance();

	std::cout << std::endl;
	std::cout << "==> Start TMVAClassificationHadHad" << std::endl;

   /// Select methods (don't look at this code - not of interest)
	if (myMethodList != "") {
		for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) it->second = 0;

		std::vector<TString> mlist = TMVA::gTools().SplitString( myMethodList, ',' );
		for (UInt_t i=0; i<mlist.size(); i++) {
			std::string regMethod(mlist[i]);

			if (Use.find(regMethod) == Use.end()) {
				std::cout << "Method \"" << regMethod << "\" not known in TMVA under this name. Choose among the following:" << std::endl;
				for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) std::cout << it->first << " ";
				std::cout << std::endl;
				return;
			}
			Use[regMethod] = 1;
		}
	}


   /// Create a ROOT output file where TMVA will store ntuples, histograms, etc.
	TFile* outputRootFile = TFile::Open( outRootFileName.c_str(), "RECREATE" );

	/// The first argument is the base of the name of all the weightfiles in the directory weight/
   /// The second argument is the output file for the training results
	///more options here http://tmva.sourceforge.net/optionRef.html#Factory
	TMVA::Factory *factory = new TMVA::Factory( outputWeightFileName, outputRootFile,
			"!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification" );

   ///Adding training variables - loop
	for(ITRS it = mVars.begin(); it != mVars.end(); it++){
		factory->AddVariable( (*it).c_str(), (*it).c_str(), "",'F');
	}
	


   ///  Register the training and test trees with factory
   	///Cuts
	
	TCut cTrain	= 	PartUsedForTraining == "A" 	? "rndm_gaussian < 0" : 
					PartUsedForTraining == "B" 	? "rndm_gaussian > 0" : 
					PartUsedForTraining == "AB" ? "" :  
			"unknown";
	
	TCut cTest	= 	PartUsedForTraining == "A" 	? "rndm_gaussian > 0" : 
					PartUsedForTraining == "B" 	? "rndm_gaussian < 0" : 
					PartUsedForTraining == "AB" ? "" : 
			"unknown";
	
	TCut mycutS = "";//hc.GetCut(category, "OS", 	purpose, region) + cTrain;
	TCut mycutB = "";//hc.GetCut(category, "bkg", 	purpose, region) + cTrain;

	TCut cutSignalTrain = hc.GetCut(category, "OS", 	purpose, region) + cTrain;
	TCut cutSignalTest  = hc.GetCut(category, "OS", 	purpose, region) + cTest;
  
	TCut cutBackgroundTrain = hc.GetCut(category, "bkg", 	purpose, region) + cTrain;
	TCut cutBackgroundTest  = hc.GetCut(category, "bkg", 	purpose, region) + cTest;
   


	///Signal
	if(kVBF){
		string HiggsProc = "vbf";
		if(kAllHiggsMasses){ ///all mass points
			for(int imass = HmassMin; imass<=HmassMax; imass+=5 ){
				cout<<"Adding "+HiggsProc+" signal "<<imass<<" in factory ..."<<endl;
				factory->AddTree(tmap[hc.GetHiggsMCnumber(Hmass, HiggsProc)], 
								 "Signal", mcb.Get_Norm(hc.GetHiggsMCnumber(imass, HiggsProc)), cutSignalTrain, "train"); 
		
				factory->AddTree(tmap[hc.GetHiggsMCnumber(Hmass, HiggsProc)], 
								 "Signal", mcb.Get_Norm(hc.GetHiggsMCnumber(imass, HiggsProc)) , cutSignalTest, "test"); 
			}
		}else{///single mass point
			cout<<"Adding "+HiggsProc+" signal "<<Hmass<<" in factory ..."<<endl;
			factory->AddTree(tmap[hc.GetHiggsMCnumber(Hmass, HiggsProc)], 
							 "Signal", mcb.Get_Norm(hc.GetHiggsMCnumber(Hmass, HiggsProc)), cutSignalTrain, "train"); 
		
			factory->AddTree(tmap[hc.GetHiggsMCnumber(Hmass, HiggsProc)], 
							 "Signal", mcb.Get_Norm(hc.GetHiggsMCnumber(Hmass, HiggsProc)) , cutSignalTest, "test"); 
		}

	}
	
	if(kGGF){
		string HiggsProc = "ggf";
		if(kAllHiggsMasses){ ///all mass points
			for(int imass = HmassMin; imass<=HmassMax; imass+=5 ){
				cout<<"Adding "+HiggsProc+" signal "<<imass<<" in factory ..."<<endl;
				factory->AddTree(tmap[hc.GetHiggsMCnumber(Hmass, HiggsProc)], 
								 "Signal", mcb.Get_Norm(hc.GetHiggsMCnumber(imass, HiggsProc)), cutSignalTrain, "train"); 
		
				factory->AddTree(tmap[hc.GetHiggsMCnumber(Hmass, HiggsProc)], 
								 "Signal", mcb.Get_Norm(hc.GetHiggsMCnumber(imass, HiggsProc)) , cutSignalTest, "test"); 
			}
		}else{///single mass point
			cout<<"Adding "+HiggsProc+" signal "<<Hmass<<" in factory ..."<<endl;
			factory->AddTree(tmap[hc.GetHiggsMCnumber(Hmass, HiggsProc)], 
							 "Signal", mcb.Get_Norm(hc.GetHiggsMCnumber(Hmass, HiggsProc)), cutSignalTrain, "train"); 
		
			factory->AddTree(tmap[hc.GetHiggsMCnumber(Hmass, HiggsProc)], 
							 "Signal", mcb.Get_Norm(hc.GetHiggsMCnumber(Hmass, HiggsProc)) , cutSignalTest, "test"); 
		}

	}
	
	if(kWH){
		string HiggsProc = "WH";
		if(kAllHiggsMasses){ ///all mass points
			for(int imass = HmassMin; imass<=HmassMax; imass+=5 ){
				cout<<"Adding "+HiggsProc+" signal "<<imass<<" in factory ..."<<endl;
				factory->AddTree(tmap[hc.GetHiggsMCnumber(Hmass, HiggsProc)], 
								 "Signal", mcb.Get_Norm(hc.GetHiggsMCnumber(imass, HiggsProc)), cutSignalTrain, "train"); 
		
				factory->AddTree(tmap[hc.GetHiggsMCnumber(Hmass, HiggsProc)], 
								 "Signal", mcb.Get_Norm(hc.GetHiggsMCnumber(imass, HiggsProc)) , cutSignalTest, "test"); 
			}
		}else{///single mass point
			cout<<"Adding "+HiggsProc+" signal "<<Hmass<<" in factory ..."<<endl;
			factory->AddTree(tmap[hc.GetHiggsMCnumber(Hmass, HiggsProc)], 
							 "Signal", mcb.Get_Norm(hc.GetHiggsMCnumber(Hmass, HiggsProc)), cutSignalTrain, "train"); 
		
			factory->AddTree(tmap[hc.GetHiggsMCnumber(Hmass, HiggsProc)], 
							 "Signal", mcb.Get_Norm(hc.GetHiggsMCnumber(Hmass, HiggsProc)) , cutSignalTest, "test"); 
		}

	}

	if(kZH){
		string HiggsProc = "ZH";
		if(kAllHiggsMasses){ ///all mass points
			for(int imass = HmassMin; imass<=HmassMax; imass+=5 ){
				cout<<"Adding "+HiggsProc+" signal "<<imass<<" in factory ..."<<endl;
				factory->AddTree(tmap[hc.GetHiggsMCnumber(Hmass, HiggsProc)], 
								 "Signal", mcb.Get_Norm(hc.GetHiggsMCnumber(imass, HiggsProc)), cutSignalTrain, "train"); 
		
				factory->AddTree(tmap[hc.GetHiggsMCnumber(Hmass, HiggsProc)], 
								 "Signal", mcb.Get_Norm(hc.GetHiggsMCnumber(imass, HiggsProc)) , cutSignalTest, "test"); 
			}
		}else{///single mass point
			cout<<"Adding "+HiggsProc+" signal "<<Hmass<<" in factory ..."<<endl;
			factory->AddTree(tmap[hc.GetHiggsMCnumber(Hmass, HiggsProc)], 
							 "Signal", mcb.Get_Norm(hc.GetHiggsMCnumber(Hmass, HiggsProc)), cutSignalTrain, "train"); 
		
			factory->AddTree(tmap[hc.GetHiggsMCnumber(Hmass, HiggsProc)], 
							 "Signal", mcb.Get_Norm(hc.GetHiggsMCnumber(Hmass, HiggsProc)) , cutSignalTest, "test"); 
		}

	}
	



	///Bkg
	for(map<int, TTree *>::iterator it = tmap.begin(); it != tmap.end(); it++){
		if(kZtautau){
			if( hc.Is("Ztautau", it->first) ) {
				cout<<"Adding Ztautau bkg "<<it->first<<" in factory"<<endl; 
				factory->AddTree (it->second, "Background", mcb.Get_Norm(it->first), cutBackgroundTrain, "train"); 
				factory->AddTree (it->second, "Background", mcb.Get_Norm(it->first), cutBackgroundTest, "test");
			}
		}
		
		if(kElwk){
			if( hc.Is("Electroweak", it->first) ) {
				cout<<"Adding Ewk bkg "<<it->first<<" in factory"<<endl; 
				factory->AddTree (it->second, "Background", mcb.Get_Norm(it->first), cutBackgroundTrain, "train"); 
				factory->AddTree (it->second, "Background", mcb.Get_Norm(it->first), cutBackgroundTest, "test");
			}
		}

	}
	if(kQCD){
		cout<<"Adding QCD bkg in factory"<<endl;
		factory->AddTree (tdata, "Background", 1, cutBackgroundTrain, "train"); 
		factory->AddTree (tdata, "Background", 1, cutBackgroundTest, "test");
	}
	
	///Weights 
	factory->SetWeightExpression("event_weight");

	/// DataSetFactory more options here  http://tmva.sourceforge.net/optionRef.html#DataSetFactory
	factory->PrepareTrainingAndTestTree( mycutS, mycutB, "NormMode=EqualNumEvents:!V" );
	//NormMode=None  or NormMode=EqualNumEvents
	//nTrain_Signal=0:nTrain_Background=0    Number of training events of class Signal/Bkg (default: 0 = all)


   /// - Book MVA method
	///BDT: more options here http://tmva.sourceforge.net/optionRef.html#MVA::BDT
	string BDTsettings = "!H:!V:NTrees="+BDT_NTrees+":nEventsMin="+BDT_nEventsMin+":MaxDepth="+BDT_MaxDepth+":BoostType="+BDT_BoostType+":AdaBoostBeta="+BDT_AdaBoostBeta+":SeparationType=GiniIndex:nCuts=20:PruneMethod=NoPruning:UseYesNoLeaf="+BDT_UseYesNoLeaf;
	if ( Use["BDT"] )  // Adaptive Boost
		factory->BookMethod( TMVA::Types::kBDT, "BDT", BDTsettings.c_str() );

	
	string BDTGsettings ="!H:!V:NTrees=500:BoostType=Grad:Shrinkage=0.10:UseBaggedGrad:GradBaggingFraction=0.5:nCuts=20:NNodesMax=5";
	if (Use["BDTG"]) // Gradient Boost
		factory->BookMethod( TMVA::Types::kBDT, "BDTG",  BDTGsettings.c_str());

	
   /// - Now you can tell the factory to train, test, and evaluate the MVAs

   /// Train MVAs using the set of training events
	factory->TrainAllMethods();

   /// - Evaluate all MVAs using the set of test events
	factory->TestAllMethods();

   /// -- Evaluate and compare performance of all configured MVAs
	factory->EvaluateAllMethods();

 
   /// Save the output
	outputRootFile->Close();

	std::cout << "==> Wrote root file: " << outputRootFile << std::endl;
	std::cout << "==> TMVAClassificationHadHad is done!" << std::endl;

	delete factory;

   /// Launch the GUI for the root macros
	if (!gROOT->IsBatch()) TMVAGui( outRootFileName.c_str() );
}
