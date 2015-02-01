#define ApplicationClass_cxx
#include "ApplicationClass.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void ApplicationClass::Loop(const string & TrainingHalf, const string &cat)
{

	///========================================

	string category = cat;
	
	if( cat == "vbf" || cat == "boosted" || cat == "1jet" || cat == "0jet" ){
		cout<<"ApplicationClass::Loop - Category chosen "<<category<<endl;
	}else{
		cerr<<"ApplicationClass::Loop - Unknown category "<<cat<<". Aborting program..."<<endl;
		return;
	}
	///========================================
	
	

	if (fChain == 0) return;

	Float_t t_BDT_Weight;
	
	TString method = "BDT method";
	
	reader = new TMVA::Reader("!Color:!Silent");
	
	Float_t var0,var1,var2,var3,var4,var5,var6,var7,var8,var9,var10;
	

	
	///copy and paste here  the output of the TMVAClassificationHadHad code
	if( category == "vbf" ){	
	  reader->AddVariable("MMC_resonance_m", &var0);
	  reader->AddVariable("ditau_dR", &var1);
	  reader->AddVariable("ditau_dijet_met_VecSumPt", &var2);
	  reader->AddVariable("dijet_mass", &var3);
	  reader->AddVariable("dijet_dEta", &var4);
	  reader->AddVariable("dijet_eta1_x_eta2", &var5);
	  reader->AddVariable("tau_0_dijet_eta_centr", &var6);
	  reader->AddVariable("tau_1_dijet_eta_centr", &var7);
	  reader->AddVariable("met_centrality", &var8);
	  
	}else if (category == "boosted" ){
	  reader->AddVariable("MMC_resonance_m", &var0);
	  reader->AddVariable("ditau_dR", &var1);
	  reader->AddVariable("ditau_pT_0_over_pT_1", &var2);
	  reader->AddVariable("ditau_colapprox_x0", &var3);
	  reader->AddVariable("ditau_colapprox_x1", &var4);
	  reader->AddVariable("met_centrality", &var5);
	  reader->AddVariable("HT_jets_taus", &var6);

	}else if (category == "1jet" ){
	  reader->AddVariable("MMC_resonance_m", &var0);
	  reader->AddVariable("met_centrality", &var1);
	  reader->AddVariable("ditau_dR", &var2);
	  reader->AddVariable("ditau_pT_0_over_pT_1", &var3);
	  reader->AddVariable("HT_jets_taus", &var4);
	  reader->AddVariable("ditau_colapprox_x0", &var5);
	  reader->AddVariable("ditau_colapprox_x1", &var6);

	}else if (category == "0jet"  ){
	  reader->AddVariable("MMC_resonance_m", &var0);
	  reader->AddVariable("met_centrality", &var1);
	  reader->AddVariable("ditau_dR", &var2);
	  reader->AddVariable("ditau_pT_0_over_pT_1", &var3);
	  reader->AddVariable("HT_jets_taus", &var4);
	  reader->AddVariable("ditau_colapprox_x0", &var5);
	  reader->AddVariable("ditau_colapprox_x1", &var6);
	  
	}else{
		cerr<<"Define your category first. Exiting ..."<<endl;
		exit(0);
	}
	
	///load the training xml
	reader->BookMVA(method, "weights/TMVAClassificationHadHad_BDT.weights.xml");
		
	///output root file
	output_file = new TFile("NEW_TREE.root","recreate");
	
	///copy the original tree and add the BDT branch
	TTree *FinalMVATree = fChain->CloneTree(0);
	FinalMVATree->Branch("BDT_Weight", &t_BDT_Weight, "BDT_Weight/F");

	///tree enetries
	Long64_t nentries = fChain->GetEntries();
	if(!nentries) cerr<<"Error. Got zero tree entries "<<nentries<<endl;
	cout<<"Tree entries retrieved "<<nentries<<endl;
			
	///event loop
	Long64_t nbytes = 0, nb = 0;
	for (Long64_t jentry=0; jentry<nentries;jentry++) {
		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) break;
		nb = fChain->GetEntry(jentry);   nbytes += nb;
		
		t_BDT_Weight = -12345;
		

		///copy and paste here  the output of the TMVAClassificationHadHad code
		if( category == "vbf" ){		  
		  var0 = MMC_resonance_m;
		  var1 = ditau_dR;
		  var2 = ditau_dijet_met_VecSumPt;
		  var3 = dijet_mass;
		  var4 = dijet_dEta;
		  var5 = dijet_eta1_x_eta2;
		  var6 = tau_0_dijet_eta_centr;
		  var7 = tau_1_dijet_eta_centr;
		  var8 = met_centrality;
		}else if (category == "boosted" ){	
		  var0 = MMC_resonance_m;
		  var1 = ditau_dR;
		  var2 = ditau_pT_0_over_pT_1;
		  var3 = ditau_colapprox_x0;
		  var4 = ditau_colapprox_x1;
		  var5 = met_centrality;
		  var6 = HT_jets_taus;
		}else if (category == "1jet" ){
		  var0 = MMC_resonance_m;
		  var1 = ditau_dR;
		  var2 = ditau_pT_0_over_pT_1;
		  var3 = ditau_colapprox_x0;
		  var4 = ditau_colapprox_x1;
		  var5 = met_centrality;
		  var6 = HT_jets_taus;		  
		}else if (category == "0jet" ){
		  var0 = MMC_resonance_m;
		  var1 = ditau_dR;
		  var2 = ditau_pT_0_over_pT_1;
		  var3 = ditau_colapprox_x0;
		  var4 = ditau_colapprox_x1;
		  var5 = met_centrality;
		  var6 = HT_jets_taus;	
		}else{
			cerr<<"Define your category first. Exiting ..."<<endl;
			exit(0);
		}
		
		///evaluate the event BDT

		t_BDT_Weight = reader->EvaluateMVA(method);
		
		//cout<<"Weight "<<t_BDT_Weight<<" for rndm = "<<rndm_gaussian<<", dR = "<<ditau_dR<<endl;
		
		 ///For weights trained on A events, apply to B events:
		if(TrainingHalf == "A"){
			if( rndm_gaussian > 0 ){ // rndm_gaussian > 0  = B
				FinalMVATree->Fill();
			}
		}
		
      	///For weights trained on B events, apply to A events:
		if(TrainingHalf == "B"){
			if( rndm_gaussian < 0 ){ // rndm_gaussian < 0  = A
				FinalMVATree->Fill();
			}
		}

		
	}//loop
	
	
	output_file->cd();
	FinalMVATree ->Write();
	output_file->Write();
	output_file->Close();

}
