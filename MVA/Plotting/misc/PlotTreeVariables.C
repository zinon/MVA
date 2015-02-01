//  to execute: 
// [] .L PlotTreeVariables.C+

#include <iostream>

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

#include "TApplication.h"
#include "TRint.h"



#include "HelperClass.h"
#include "MonteCarloBank.h"

void PlotTreeVariables();

int main(int argc, char *argv[])
{
PlotTreeVariables();
	return 0;
}

void PlotTreeVariables(){

	gSystem->Load("../../HelperClass/HelperClass_cpp.so");
	gSystem->Load("../../MonteCarloBank/MonteCarloBank_cpp.so");

	MonteCarloBank mcbank;
	HelperClass hc;
	
	///settings - to edit :
	string variable; int nbins;double firstbin; double lastbin; string xTitle; bool kQCD(true); double MaxY(1);
	//variable = "esv_all_objects_sphericity"; xTitle = "sphericity"; nbins = 50; firstbin = 0.0; lastbin = 1.0;
	//variable = "esv_all_objects_planarity"; xTitle = "planarity"; nbins = 25; firstbin = 0.0; lastbin = 0.5;
	//variable = "esv_all_objects_FoxWolfram_R1"; xTitle = "R1"; nbins = 25; firstbin = 0.0; lastbin = 1.0; MaxY = 0.2;
	//variable = "esv_all_objects_FoxWolfram_R2"; xTitle = "R2"; nbins = 25; firstbin = 0.0; lastbin = 1.0;MaxY = 0.2;
	//variable = "esv_all_objects_FoxWolfram_R3"; xTitle = "R3"; nbins = 25; firstbin = 0.0; lastbin = 1.0;MaxY = 0.2;
	//variable = "esv_all_objects_FoxWolfram_R4"; xTitle = "R4"; nbins = 25; firstbin = 0.0; lastbin = 1.0;MaxY = 0.2;

	//variable = "tau_0_mmcResonance_cosThetaStar"; xTitle = "cos#theta*"; nbins = 25; firstbin = -1.0; lastbin = 1.0;
	//variable = "tau_1_mmcResonance_cosThetaStar"; xTitle = "cos#theta*"; nbins = 25; firstbin = -1.0; lastbin = 1.0;
	//variable = "tau_0_visibleParent_cosThetaStar"; xTitle = "cos#theta*"; nbins = 25; firstbin = -1.0; lastbin = 1.0;
	variable = "tau_1_visibleParent_cosThetaStar"; xTitle = "cos#theta*"; nbins = 25; firstbin = -1.0; lastbin = 1.0;
	//variable = "ditau_Qplus_Qminus_deltaPt"; xTitle = "#Delta p_{T}"; nbins = 50; firstbin = -50; lastbin = 50; kQCD = false;
	
	//variable = "tau_0_closest_jet_dR"; xTitle = "min#DeltaR"; nbins = 35; firstbin = 0.0; lastbin = 3.5;
	//variable = "tau_1_closest_jet_dR"; xTitle = "min#DeltaR"; nbins = 35; firstbin = 0.0; lastbin = 3.5;
	
	string 	QCDmodel = "notOS";
	string	category = "2jet";
	string	version = "v7";
	int 	Hmass = 125;
	

	hc.SetTreeName("mva");
	hc.SetVersion(version);
	hc.SetPath("../../Ntuples/");

	///list of MC samples
	vector<int> RunsVector = hc.GetRunsVector(Hmass);
	
	///data tree
	cout<<"\ncreating tree map for data"<<endl;
	TTree *tData = hc.GetTreeData();
	hc.SetLumiPerRunMap();
	
	///lumi
	double DataLumi = hc.GetRunsListTotalLumi("inb");
	cout<<"\nData lumi "<<DataLumi<<" nb-1"<<endl<<endl;
	
	/// mc tree map
	cout<<"\ncreating tree map for mc"<<endl;
	map<int, TTree *> tmap;
	for(vector<int>::iterator it=RunsVector.begin(); it != RunsVector.end(); it++){
		if( *it >= 800000) continue;
		tmap.insert ( pair<int, TTree *>(*it,  hc.GetTreeMC(*it) ) );
	}
	
	///histogramming
	cout<<"\nbooking histograms"<<endl;
	double BinW = (lastbin - firstbin)/nbins;
	cout<<"\nbin width : "<<BinW<<endl;
	
	map<int, TH1D *> hmap_Sig;
	map<int, TH1D *> hmap_Bkg;
	for(vector<int>::iterator it=RunsVector.begin(); it != RunsVector.end(); it++){
		hmap_Sig.insert ( pair<int,TH1D *>(*it, new  TH1D("",	"",	nbins, firstbin, lastbin)) );
		hmap_Bkg.insert ( pair<int,TH1D *>(*it, new  TH1D("",	"",	nbins, firstbin, lastbin)) );
	}
	
	TH1D *hist_Data = new TH1D("hist_Data",	"",	nbins, firstbin, lastbin);
	
	TH1D *hist_QCD = new TH1D("hist_QCD",	"",	nbins, firstbin, lastbin);
		
	///give names
	cout<<"renaming plots"<<endl;
	hc.SetHistoNames1D(hmap_Sig, "OS");
	hc.SetHistoNames1D(hmap_Bkg, QCDmodel);
	
	///plot making
	cout<<"\nCuts  : \n"<<hc.GetCut(category, "OS", "MVA", "all").GetTitle()<<endl;
	
	cout<<"\nfilling up histograms ..."<<endl;
	/// -- data
	hc.MakePlot( tData, hist_Data,  hc.GetCut(category, "OS", "MVA", "all"), variable );
	/// -- QCD from data
	hc.MakePlot( tData, hist_QCD,  hc.GetCut(category, QCDmodel, "MVA", "all"), variable );
	/// -- MC search region
	for(map<int, TH1D *>::iterator it = hmap_Sig.begin(); it != hmap_Sig.end(); it++){
		if(it->first < 800000)
			hc.MakePlot(tmap[it->first], it->second, hc.GetCut(category, "OS", "MVA", "all"), variable );	
	}
	/// -- MC bkg model - for bkg subtraction
	for(map<int, TH1D *>::iterator it = hmap_Bkg.begin(); it != hmap_Bkg.end(); it++){
		if(it->first < 800000)
			hc.MakePlot(tmap[it->first], it->second, hc.GetCut(category, QCDmodel, "MVA", "all"), variable );
	}
	
	///normalize all MC to unity
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
	cout<<"\nmaking inclusive histos"<<endl;
	for(vector<int>::iterator it=RunsVector.begin(); it != RunsVector.end(); it++){
		if( *it >= 800000) continue;
		
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


	///normalize all  to unity
	cout<<"\nhistograms normalization"<<endl;
	for(map<int, TH1D *>::iterator it = hmap_Sig.begin(); it != hmap_Sig.end(); it++){
		it->second->Scale( 1.0/(it->second->Integral()) );
	}
	for(map<int, TH1D *>::iterator it = hmap_Bkg.begin(); it != hmap_Bkg.end(); it++){
		it->second->Scale( 1.0/(it->second->Integral()) );
	}

	hist_Data->Scale( 1.0/(hist_Data->Integral()) );
	hist_QCD->Scale( 1.0/(hist_QCD->Integral()) );
			
	///file
	TFile *f = new TFile( "treeplots.root", "recreate");
	
	///Canvas	
	TCanvas *c = new TCanvas("c","", 1290, 65, 700, 900);
	c->SetFillColor(0);
	c->SetBorderMode(0);
	c->SetBorderSize(0);
	c->SetFrameBorderMode(0);
	gStyle->SetOptStat(0);
	gStyle->SetOptTitle(0);
	gPad->SetTopMargin(c->GetTopMargin()*0.4 );
	gPad->SetTopMargin(c->GetLeftMargin()*1.1 );
	gPad->SetTopMargin(c->GetTopMargin()*0.2 );
		
	hmap_Sig[800000]->SetLineColor(kRed);
	hmap_Sig[800001]->SetLineColor(kAzure);
	hmap_Sig[800005]->SetLineColor(kOrange);
	hist_QCD->SetLineColor(1);
		
	hmap_Sig[800000]->Draw();
	if(kQCD) hist_QCD->Draw("same");
	hmap_Sig[800001]->Draw("same");
	hmap_Sig[800005]->Draw("same");
		
	hmap_Sig[800000]->GetXaxis()->SetTitle(xTitle.c_str());
	
	hmap_Sig[800000]->SetMaximum(MaxY);
		

	TLegend *leg = new TLegend(0.42,0.70,0.92,0.92,NULL,"brNDC");
	leg->SetBorderSize(1);
	leg->SetLineColor(15);
	leg->SetLineStyle(1);
	leg->SetLineWidth(1);
	leg->SetFillColor(19);
	leg->SetFillStyle(3002);
	leg->SetTextFont(42); 
	leg->SetTextSize(0.03); 
	string legH = "";
	leg->AddEntry(hmap_Sig[800000],"VBF Higgs","lp");
	leg->AddEntry(hmap_Sig[800001],"Z#tau#tau","lp");
	leg->AddEntry(hmap_Sig[800005],"EWK","lp");
	leg->AddEntry(hist_QCD,"QCD (notOS)","lp");		
	leg->Draw();
		
		
   
	f->cd();
	
	c->Write();

	f->Close();
}

