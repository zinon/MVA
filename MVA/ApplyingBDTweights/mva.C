#define mva_cxx
#include "mva.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void mva::Loop(int TrainingHalf)
{
  
	if (fChain == 0) return;
  
    
     //________________Declare variables used in the BDT________________
	Float_t _bdt_vbf;
	Float_t _tau_0_BDT_score ;             
	Float_t _tau_0_dijet_eta_centr ;       
	Float_t _tau_1_BDT_score ;         
	Float_t _tau_1_dijet_eta_centr ;       
	Float_t _ditau_dR        ;         
	Float_t _ditau_VecSumPt  ;         
	Float_t _ditau_met_dPhi  ;         
	Float_t _dijet_dEta_x_sign1_x_sign2 ; 
	Float_t _dijet_mass      ;         
	Float_t _dijet_eta1_x_eta2 ;       
  
    //________________Declare BDT(s)________________
    
	Float_t _BDT_VBF;
  
	output_hist = new TFile("NEW_TREE.root","recreate");
  
    //________________Declare the output tree________________
    
    // TTree* FinalMVATree = new TTree("FinalMVAtree", "Tree including BDTs");
    
	TTree *FinalMVATree = fChain->CloneTree(0);
  
    // FinalMVATree->Branch("hadhadMVA",&hadhadMVA.kz_tau_0_dijet_eta_centr, "kz_tau_0_dijet_eta_centr/F");
    //FinalMVATree->Branch("hadhadMVA",&hadhadMVA.category, "category/I");
    // FinalMVATree->Branch("BDT_VBF", &BDT_VBF, "BDT_VBF/F");
    // FinalMVATree->Branch("BDT_VBF", &BDT_VBF, "BDT_VBF/F");
	FinalMVATree->Branch("bdt_vbf", &_bdt_vbf, "bdt_vbf/F");
    
    
	Long64_t nentries = fChain->GetEntriesFast();
    
	Long64_t nbytes = 0, nb = 0;
	for (Long64_t jentry=0; jentry<nentries;jentry++) {
		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) break;
		nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      
      //_BDT_VBF = -99.;
      //      _BDT = -99.;
		_bdt_vbf = -99.;
      
		_tau_0_BDT_score =             tau_0_BDT_score ;     
		_tau_0_dijet_eta_centr =       tau_0_dijet_eta_centr       ;
		_tau_1_BDT_score =               tau_1_BDT_score       ;
		_tau_1_dijet_eta_centr =       tau_1_dijet_eta_centr ;
		_ditau_dR        =               ditau_dR                 ;     
		_ditau_VecSumPt  =               ditau_VecSumPt            ;     
		_ditau_met_dPhi  =               ditau_met_dPhi      ;
		_dijet_dEta_x_sign1_x_sign2 =  dijet_dEta_x_sign1_x_sign2 ;
		_dijet_mass      =               dijet_mass             ;
		_dijet_eta1_x_eta2 =             dijet_eta1_x_eta2        ;     
      // cout<<"tau0bdt "<<_tau_0_BDT_score<<endl;//works
      
      
		TTree* TempBDTtree = new TTree("TempBDTtree","Tree for the BDT");
		TempBDTtree->Branch("tau_0_BDT_score",       &_tau_0_BDT_score,            "tau_0_BDT_score/F"); 
		TempBDTtree->Branch("tau_0_dijet_eta_centr", &_tau_0_dijet_eta_centr,      "tau_0_dijet_eta_centr/F");
		TempBDTtree->Branch("tau_1_BDT_score",       &_tau_1_BDT_score,            "tau_1_BDT_score/F"); 
		TempBDTtree->Branch("tau_1_dijet_eta_centr", &_tau_1_dijet_eta_centr,      "tau_1_dijet_eta_centr/F"); 
		TempBDTtree->Branch("ditau_dR",              &_ditau_dR,                   "ditau_dR/F"); 
		TempBDTtree->Branch("ditau_VecSumPt",        &_ditau_VecSumPt,             "ditau_VecSumPt/F"); 
		TempBDTtree->Branch("ditau_met_dPhi",        &_ditau_met_dPhi,             "ditau_met_dPhi/F"); 
		TempBDTtree->Branch("dijet_dEta_x_sign1_x_sign2",  &_dijet_dEta_x_sign1_x_sign2, "dijet_dEta_x_sign1_x_sign2/F"); 
		TempBDTtree->Branch("dijet_mass",            &_dijet_mass,                 "dijet_mass/F"); 
		TempBDTtree->Branch("dijet_eta1_x_eta2",     &_dijet_eta1_x_eta2 ,         "dijet_eta1_x_eta2/F");         
      
      
		TempBDTtree->Fill();
      
		TempBDTtree->SetBranchAddress("tau_0_BDT_score",       &var1);
		TempBDTtree->SetBranchAddress("tau_0_dijet_eta_centr", &var2);
		TempBDTtree->SetBranchAddress("tau_1_BDT_score",       &var3);
		TempBDTtree->SetBranchAddress("tau_1_dijet_eta_centr", &var4);
		TempBDTtree->SetBranchAddress("ditau_dR",              &var5);
		TempBDTtree->SetBranchAddress("ditau_VecSumPt",        &var6);
		TempBDTtree->SetBranchAddress("ditau_met_dPhi",        &var7);
		TempBDTtree->SetBranchAddress("dijet_dEta_x_sign1_x_sign2",  &var8);
		TempBDTtree->SetBranchAddress("dijet_mass",            &var9);
		TempBDTtree->SetBranchAddress("dijet_eta1_x_eta2",     &var10);
      
      
		var1=_tau_0_BDT_score       ;       
		var2=_tau_0_dijet_eta_centr  ;       
		var3=_tau_1_BDT_score        ;       
		var4=_tau_1_dijet_eta_centr  ;       
		var5=_ditau_dR               ;       
		var6=_ditau_VecSumPt         ;       
		var7=_ditau_met_dPhi         ;       
		var8=_dijet_dEta_x_sign1_x_sign2  ; 
		var9=_dijet_mass;   
		var10=_dijet_eta1_x_eta2      ;       
      
      
		_bdt_vbf=reader[0]->EvaluateMVA("BDT method");     

      _bdt_vbf=(_bdt_vbf+1. /2.);
      
		delete TempBDTtree;
      
      //      hadhadMVA.kz_tau_0_dijet_eta_centr = tau_0_dijet_eta_centr;
      //hadhadMVA.category = category;
      
      //To ensure the same events are not used in the Training and the final result:



      //_______  For weights trained on ODD events, apply to EVEN events:__________
		if(TrainingHalf == 0){
			if( averageIntPerXing % 2 ==0 ){
				FinalMVATree->Fill();
			}
		}
      //_______For weights trained on EVEN events, apply to ODD events:_________
      
		if(TrainingHalf == 1){
			if( averageIntPerXing % 2 ==1 ){
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
