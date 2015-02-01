#define mva_cxx
#include "mva.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

//#define JETCAT 2 
#define JETCAT 1

void mva::Loop(const string & TrainingHalf)
{
  
	if (fChain == 0) return;
  
    
     ///________________Declare variables used in the BDT________________
	
	Float_t _ditau_dR;
	Float_t _tau_0_dijet_eta_centr;
	Float_t _tau_1_dijet_eta_centr;
	Float_t _met_centrality;
	Float_t _MMC_resonance_pt;
	Float_t _dijet_mass;
	Float_t _dijet_dEta;
       	Float_t _dijet_eta1_x_eta2;
	Float_t _dijet_dEta_x_sign1_x_sign2;
	//	Float_t _met_et;
  
    ///________________Declare BDT(s)________________
    
	Float_t _BDT_Weight;
  
	output_hist = new TFile("NEW_TREE.root","recreate");
  
    ///________________Declare the output tree________________

	TTree *FinalMVATree = fChain->CloneTree(0);

	
	FinalMVATree->Branch("BDT_Weight", &_BDT_Weight, "BDT_Weight/F");
    
    ///________________Loop _______________    
	Long64_t nentries = fChain->GetEntriesFast();
    
	Long64_t nbytes = 0, nb = 0;
	for (Long64_t jentry=0; jentry<nentries;jentry++) {
		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) break;
		nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      

		_BDT_Weight = -99.;
      

// 	_ditau_dR = ditau_dR;
// 	_tau_0_dijet_eta_centr = tau_0_dijet_eta_centr;
// 	_tau_1_dijet_eta_centr = tau_1_dijet_eta_centr;
// 	_met_centrality = met_centrality;
// 	_MMC_resonance_pt = MMC_resonance_pt;
// 	_dijet_mass = dijet_mass;
// 	_dijet_dEta = dijet_dEta;
// 	_dijet_eta1_x_eta2 = dijet_eta1_x_eta2;
//       
// 		TTree* TempBDTtree = new TTree("TempBDTtree","Tree for the BDT");
// 		if(JETCAT == 2 ){
// 			TempBDTtree->Branch("ditau_dR",       			&_ditau_dR,     				"ditau_dR/F"); 
// 			TempBDTtree->Branch("tau_0_dijet_eta_centr", 	&_tau_0_dijet_eta_centr,      	"tau_0_dijet_eta_centr/F");
// 			TempBDTtree->Branch("tau_1_dijet_eta_centr", 	&_tau_1_dijet_eta_centr,      	"tau_1_dijet_eta_centr/F"); 
// 			TempBDTtree->Branch("met_centrality", 			&_met_centrality,      			"met_centrality/F"); 
// 			TempBDTtree->Branch("MMC_resonance_pt", 		&_MMC_resonance_pt,      		"MMC_resonance_pt/F"); 
// 			TempBDTtree->Branch("dijet_mass",     			&_dijet_mass,   				"dijet_mass/F"); 
// 			TempBDTtree->Branch("dijet_dEta", 				&_dijet_dEta,      				"dijet_dEta/F"); 
// 			TempBDTtree->Branch("dijet_eta1_x_eta2",     	&_dijet_eta1_x_eta2 ,  			"dijet_eta1_x_eta2/F");
// 		}
// 		TempBDTtree->Fill();
//       
// 	  
// 	  
// 		if(JETCAT == 2 ){
// 			TempBDTtree->SetBranchAddress("ditau_dR", &var1);
// 			TempBDTtree->SetBranchAddress("tau_0_dijet_eta_centr", &var2);
// 			TempBDTtree->SetBranchAddress("tau_1_dijet_eta_centr", &var3);
// 			TempBDTtree->SetBranchAddress("met_centrality", &var4);
// 			TempBDTtree->SetBranchAddress("MMC_resonance_pt", &var5);
// 			TempBDTtree->SetBranchAddress("dijet_mass", &var6);
// 			TempBDTtree->SetBranchAddress("dijet_dEta", &var7);
// 			TempBDTtree->SetBranchAddress("dijet_eta1_x_eta2", &var8);
//       }
// 	  
// 	  
// 	  if(JETCAT == 2 ){
// 	 	 var1 = _ditau_dR;
// 		 var2 = _tau_0_dijet_eta_centr;
// 		 var3 = _tau_1_dijet_eta_centr;
// 		 var4 = _met_centrality;
// 		 var5 = _MMC_resonance_pt;
// 		 var6 = _dijet_mass;
// 		 var7 = _dijet_dEta;
// 		 var8 = _dijet_eta1_x_eta2;
// 	  }

		
	  if(JETCAT == 2 ){
	 	 var1 = ditau_dR;
		 var2 = tau_0_dijet_eta_centr;
		 var3 = tau_1_dijet_eta_centr;
		 var4 = met_centrality;
		 var5 = MMC_resonance_pt;
		 var6 = dijet_mass;
		 var7 = dijet_dEta;
		 var8 = dijet_eta1_x_eta2;
		 //		 var9 = met_et;
		 // var7 = dijet_dEta_x_sign1_x_sign2;
	  }
	  

	  if(JETCAT == 1 ){
	 	 var1 = ditau_dR;
		 var2 = MMC_resonance_pt;
		 var3 = esv_all_objects_sphericity;
		 var4 = met_centrality;
		 var5 = ditau_colapprox_x0;
		 var6 = ditau_colapprox_x1;

		 //		 var9 = met_et;
		 // var7 = dijet_dEta_x_sign1_x_sign2;
	  }
	  
      
		_BDT_Weight = reader[0]->EvaluateMVA("BDT method");

		//_BDT_Weight=(_BDT_Weight+1.) /2.;
		//	cout<<"The weight after trans: "<<_BDT_Weight<<endl;
		//delete TempBDTtree;

      ///To ensure the same events are not used in the Training and the final result:



      //_______  For weights trained on A events, apply to B events:__________
		if(TrainingHalf == "A"){
			if( rndm_gaussian > 0 ){ // rndm_gaussian > 0  = B
				FinalMVATree->Fill();
			}
		}
      //_______For weights trained on B events, apply to A events:_________
      
		if(TrainingHalf == "B"){
			if( rndm_gaussian < 0 ){ // rndm_gaussian < 0  = A
				FinalMVATree->Fill();
			}
		}
      //_________
      
	}
 
  

    
	output_hist->cd();
	FinalMVATree ->Write();
	output_hist->Write();
	output_hist->Close();
}
