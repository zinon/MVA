//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Feb  4 14:31:37 2013 by ROOT version 5.34/00
// from TTree mva/A tree for the MVA had-had analysis
// found on file: ../../Ntuples/v8/data/data.200842.root
//////////////////////////////////////////////////////////

#ifndef ApplicationClass_h
#define ApplicationClass_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

#include "TMVA/Reader.h"


#include <iostream>

using namespace std;

class ApplicationClass {

	private:
	
		TFile *output_file;
		TMVA::Reader *reader;

	public :
		TTree          *fChain;   //!pointer to the analyzed TTree or TChain
		Int_t           fCurrent; //!current Tree number in a TChain

   		// Declaration of leaf types
		Double_t        rndm_gaussian;
		Double_t        ditau_dR;
		Double_t        tau_0_dijet_eta_centr;
		Double_t        tau_1_dijet_eta_centr;
		Double_t        met_centrality;
		Double_t        MMC_resonance_pt;
		Double_t        MMC_resonance_m;
		Double_t        dijet_mass;
		Double_t        dijet_dEta;
		Double_t        dijet_eta1_x_eta2;
		Double_t	ditau_mass_mmc;

		Double_t        esv_all_objects_sphericity;
		Double_t        ditau_colapprox_x0;
		Double_t	ditau_colapprox_x1;

		Double_t       ditau_dijet_met_VecSumPt;
		Double_t       ditau_pT_0_over_pT_1;
		Double_t       HT_jets_taus;

//		Double_t       tau_0_pt;
//		Double_t       tau_1_pt;
//		Double_t       tau_0_eta;
//		Double_t       tau_1_eta;
//		Double_t       tau_0_phi;
//		Double_t       tau_1_phi;
//
//		Double_t       met_phi;
//		Double_t       met_et;
//
   		// List of branches
		TBranch        *b_rndm_gaussian;   //!
		TBranch        *b_ditau_dR;   //!
		TBranch        *b_tau_0_dijet_eta_centr;   //!
		TBranch        *b_tau_1_dijet_eta_centr;   //!
		TBranch        *b_met_centrality;   //!
		TBranch        *b_MMC_resonance_pt;   //!
		TBranch        *b_MMC_resonance_m;   //!
		TBranch        *b_dijet_mass;   //!
		TBranch        *b_dijet_dEta;   //!
		TBranch        *b_dijet_eta1_x_eta2;   //!
		TBranch 	*b_ditau_mass_mmc;

		TBranch        *b_esv_all_objects_sphericity;
		TBranch        *b_ditau_colapprox_x0;
		TBranch	       *b_ditau_colapprox_x1;
		TBranch        *b_HT_jets_taus;
		TBranch        *b_ditau_pT_0_over_pT_1;
		TBranch        *b_ditau_dijet_met_VecSumPt;
//		TBranch       *b_tau_0_pt;
//		TBranch       *b_tau_1_pt;
//		TBranch       *b_tau_0_eta;
//		TBranch       *b_tau_1_eta;
//		TBranch       *b_tau_0_phi;
//		TBranch       *b_tau_1_phi;
//		TBranch       *b_met_phi;
//                TBranch       *b_met_et;
//
		
		ApplicationClass(TTree *tree=0);
		virtual ~ApplicationClass();
		virtual Int_t    Cut(Long64_t entry);
		virtual Int_t    GetEntry(Long64_t entry);
		virtual Long64_t LoadTree(Long64_t entry);
		virtual void     Init(TTree *tree);
		virtual void     Loop(const string &, const string &);
		virtual Bool_t   Notify();
		virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef ApplicationClass_cxx
ApplicationClass::ApplicationClass(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
	if (tree == 0) {
		TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("temp.root");
		if (!f || !f->IsOpen()) {
			f = new TFile("temp.root");
		}
		f->GetObject("mva",tree);

	}
	Init(tree);
}

ApplicationClass::~ApplicationClass()
{
	if (!fChain) return;
	delete fChain->GetCurrentFile();
}

Int_t ApplicationClass::GetEntry(Long64_t entry)
{
// Read contents of entry.
	if (!fChain) return 0;
	return fChain->GetEntry(entry);
}
Long64_t ApplicationClass::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
	if (!fChain) return -5;
	Long64_t centry = fChain->LoadTree(entry);
	if (centry < 0) return centry;
	if (fChain->GetTreeNumber() != fCurrent) {
		fCurrent = fChain->GetTreeNumber();
		Notify();
	}
	return centry;
}

void ApplicationClass::Init(TTree *tree)
{

   // Set branch addresses and branch pointers
	if (!tree) return;
	fChain = tree;
	fCurrent = -1;
	fChain->SetMakeClass(1);


	fChain->SetBranchAddress("rndm_gaussian", &rndm_gaussian, &b_rndm_gaussian);
	fChain->SetBranchAddress("ditau_dR", &ditau_dR, &b_ditau_dR);
	fChain->SetBranchAddress("tau_0_dijet_eta_centr", &tau_0_dijet_eta_centr, &b_tau_0_dijet_eta_centr);
	fChain->SetBranchAddress("tau_1_dijet_eta_centr", &tau_1_dijet_eta_centr, &b_tau_1_dijet_eta_centr);
	fChain->SetBranchAddress("met_centrality", &met_centrality, &b_met_centrality);
        fChain->SetBranchAddress("MMC_resonance_pt", &MMC_resonance_pt, &b_MMC_resonance_pt);
	fChain->SetBranchAddress("MMC_resonance_m", &MMC_resonance_m, &b_MMC_resonance_m);
	fChain->SetBranchAddress("dijet_mass", &dijet_mass, &b_dijet_mass);
	fChain->SetBranchAddress("dijet_dEta", &dijet_dEta, &b_dijet_dEta);
	fChain->SetBranchAddress("dijet_eta1_x_eta2", &dijet_eta1_x_eta2, &b_dijet_eta1_x_eta2);
	fChain->SetBranchAddress("ditau_mass_mmc", &ditau_mass_mmc, &b_ditau_mass_mmc);

	fChain->SetBranchAddress("ditau_colapprox_x0", &ditau_colapprox_x0, &b_ditau_colapprox_x0);
	fChain->SetBranchAddress("ditau_colapprox_x1", &ditau_colapprox_x1, &b_ditau_colapprox_x1);
	fChain->SetBranchAddress("esv_all_objects_sphericity", &esv_all_objects_sphericity, &b_esv_all_objects_sphericity);

	fChain->SetBranchAddress("HT_jets_taus", &HT_jets_taus, &b_HT_jets_taus);
	fChain->SetBranchAddress("ditau_pT_0_over_pT_1", &ditau_pT_0_over_pT_1, &b_ditau_pT_0_over_pT_1);
	fChain->SetBranchAddress("ditau_dijet_met_VecSumPt", &ditau_dijet_met_VecSumPt, &b_ditau_dijet_met_VecSumPt);


//	fChain->SetBranchAddress("tau_0_pt", tau_0_pt,        &b_tau_0_pt);
//	fChain->SetBranchAddress("tau_1_pt", tau_1_pt,        &b_tau_1_pt);
//	fChain->SetBranchAddress("tau_0_eta",tau_0_eta,       &b_tau_0_eta);
//	fChain->SetBranchAddress("tau_1_eta",tau_1_eta,       &b_tau_1_eta);
//	fChain->SetBranchAddress("tau_0_phi",tau_0_phi,       &b_tau_0_phi);
//	fChain->SetBranchAddress("tau_1_phi",tau_1_phi,       &b_tau_1_phi);
//	fChain->SetBranchAddress("met_phi",  met_phi,         &b_met_phi);
//	fChain->SetBranchAddress("met_et",   met_et,          &b_met_et);   
//	
	Notify();
}

Bool_t ApplicationClass::Notify()
{
	return kTRUE;
}

void ApplicationClass::Show(Long64_t entry)
{
	if (!fChain) return;
	fChain->Show(entry);
}
Int_t ApplicationClass::Cut(Long64_t entry)
{

	return 1;
}
#endif // #ifdef ApplicationClass_cxx
