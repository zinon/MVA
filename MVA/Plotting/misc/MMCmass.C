// https://svnweb.cern.ch/trac/atlasphys/browser/Physics/Higgs/HSG4/software/hadhad/MultiVariateAnalysis
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

#include "TApplication.h"
#include "TRint.h"



#include "HelperClass.h"
#include "MonteCarloBank.h"

using namespace std;


void MMCmass();


int main(int argc, char *argv[])
{
	//TApplication *myapp=new TApplication("myapp",0,0);
	MMCmass();
	//myapp->Run();
	return 0;
}

void MMCmass(){

	///external classes
	gSystem->Load("../../HelperClass/HelperClass_cpp.so");
	gSystem->Load("../../MonteCarloBank/MonteCarloBank_cpp.so");

	MonteCarloBank mcbank;
	HelperClass hc;
	
	///settings - to edit :
	string variable = "ditau_mass_mmc";
	double 	QCDTrackFitFactor = 0.2685;
	double	ZtautauNormFactor = 1.0;
	int		SignalZoom = 50;
	string 	QCDmodel = "notOS";
	double 	QCDnorm = 1;
	string 	version = "v6";
	string 	category = "vbf";
	int 	Hmass = 125;
	string 	hmass = hc.GetStringFromInt(Hmass);
	string 	fn = "plot_MMCmass_"+category+"_"+hmass+"_"+version+".root";
	double 	MinX = 50.0;
	double 	MaxX = 180.0;
	double 	MinY = 1e-6;
	double 	MaxY = 350.0;
	bool 	kLogY = false;
	bool 	kAdjustLeftBin = false;
	//bool kAdjustRightBin = false;
	string xTitle = "MMC ditau mass [GeV]";
	int nbins = 40;
	double firstbin = 0;
	double lastbin = 200;	

	hc.SetTreeName("mva");
	hc.SetVersion(version);
	hc.SetPath("../../Ntuples/");

	///list of MC samples
	vector<int> RunsVector = hc.GetRunsVector(Hmass);
	
	///data tree
	TTree *tData = hc.GetTreeDataMVA();
	cout<<"\nData tree entries : "<<tData->GetEntries()<<endl;
	hc.SetLumiPerRunMap();
	
	///lumi
	double DataLumi = hc.GetRunsListTotalLumi("inb");
	cout<<"\nData lumi "<<DataLumi<<" nb-1"<<endl<<endl;
	
	/// mc tree map
	map<int, TTree *> tmap;
	//MC first
	for(vector<int>::iterator it=RunsVector.begin(); it != RunsVector.end(); it++){
		if( *it >= 800000) continue;
		tmap.insert ( pair<int, TTree *>(*it,  hc.GetTreeMCMVA(*it) ) );
	}
	
	///histogramming
	cout<<"\nbooking histograms"<<endl;
	double BinW = (lastbin - firstbin)/nbins;
	cout<<"\nbin width : "<<BinW<<endl;
	
	TH1D *hist_Data = new TH1D("hist_Data",	"",	nbins, firstbin, lastbin);
	
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
	
	///give names
	cout<<"renaming plots"<<endl;
	hc.SetHistoNames1D(hmap_Sig, "OS");
	hc.SetHistoNames1D(hmap_Bkg, QCDmodel);
	
	///plot making
	cout<<"Cuts for search region : \n"<<hc.GetCut(category, "OS", "MVA","SR").GetTitle()<<endl;
	
	cout<<"filling up histograms"<<endl;
	/// -- data
	hc.MakePlot( tData, hist_Data,  hc.GetCut(category, "OS", "MVA","SR"), variable );
	/// -- QCD from data
	hc.MakePlot( tData, hist_QCD,  hc.GetCut(category, QCDmodel, "MVA","SR"), variable );
	/// -- MC search region
	for(map<int, TH1D *>::iterator it = hmap_Sig.begin(); it != hmap_Sig.end(); it++){
		if(it->first < 800000)
		  hc.MakePlot(tmap[it->first], it->second, hc.GetCut(category, "OS", "MVA","SR"), variable );	
	}
	/// -- MC bkg model - for bkg subtraction
	for(map<int, TH1D *>::iterator it = hmap_Bkg.begin(); it != hmap_Bkg.end(); it++){
		if(it->first < 800000)
		  hc.MakePlot(tmap[it->first], it->second, hc.GetCut(category, QCDmodel, "MVA","SR"), variable );	
	}
	
	///normalize all MC to data lumi
	cout<<"histograms normalization"<<endl;
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
	cout<<"making inclusive histos"<<endl;
	for(vector<int>::iterator it=RunsVector.begin(); it != RunsVector.end(); it++){
		if( *it >= 800000) continue;
		if( hc.Is("Higgs", *it) ) 			{hmap_Sig[800000]->Add( hmap_Sig[*it]); hmap_Bkg[800000]->Add( hmap_Bkg[*it]); }
		if( hc.Is("Ztautau", *it) ) 		{hmap_Sig[800001]->Add( hmap_Sig[*it]); hmap_Bkg[800001]->Add( hmap_Bkg[*it]);}
		if( hc.Is("Wtaunu", *it) ) 			{hmap_Sig[800002]->Add( hmap_Sig[*it]); hmap_Bkg[800002]->Add( hmap_Bkg[*it]);}
		if( hc.Is("Top", *it) ) 			{hmap_Sig[800003]->Add( hmap_Sig[*it]); hmap_Bkg[800003]->Add( hmap_Bkg[*it]);}
		if( hc.Is("Dibosons", *it) ) 		{hmap_Sig[800004]->Add( hmap_Sig[*it]); hmap_Bkg[800004]->Add( hmap_Bkg[*it]);}
		if( hc.Is("Electroweak", *it) ) 	{hmap_Sig[800005]->Add( hmap_Sig[*it]); hmap_Bkg[800005]->Add( hmap_Bkg[*it]);}
		

	}

	
	///EWK subtraction from QCD
	cout<<"\nSubtracting ewk bkg from QCD bkg"<<endl;
	cout<<"QCD integral before "<<hist_QCD->Integral()<<endl;
	hist_QCD->Add(hmap_Bkg[800005], -1);
	cout<<"QCD integral after "<<hist_QCD->Integral()<<endl<<endl;
			
	///normalize QCD
	cout<<"\nNormalize QCD bkg to Track Fit"<<endl;
	cout<<"QCD integral before "<<hist_QCD->Integral()<<endl;
 	QCDnorm =  QCDTrackFitFactor* hist_Data->Integral(); 
	cout<<"QCD overall norm factor : "<<QCDnorm<<endl;
 	hist_QCD->Scale( QCDnorm/ (hist_QCD->Integral()) );
	cout<<"QCD integral after "<<hist_QCD->Integral()<<endl<<endl;
	
	///normalize Ztautau
	cout<<"\nNormalize Z tau tau"<<endl;
	cout<<"Z tau tau integral before "<<hmap_Sig[800001]->Integral()<<endl;
 	hmap_Sig[800001]->Scale(ZtautauNormFactor);
	cout<<"Z tau tau  integral after "<<hmap_Sig[800001]->Integral()<<endl<<endl;

	
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
	
	///spectra
	hSpectrum0->Add(hist_QCD, 1);			/// qcd
	
	hSpectrum1->Add(hSpectrum0, 1);		/// qcd + ewk
	hSpectrum1->Add(hmap_Sig[800005], 1); 
	
	hSpectrum2->Add(hSpectrum1, 1);		/// qcd + ewk + Z
	hSpectrum2->Add(hmap_Sig[800001], 1);
	
	hSpectrum3->Add(hSpectrum2, 1);		/// qcd + ewk + Z + signal
	hSpectrum3->Add(hmap_Sig[800000], SignalZoom);
	
	hist_BKG->Add(hSpectrum2, 1.0);
	
	///ratio 
	TH1D *h_Data_over_BKG = hc.GetHistoRatio(hist_Data, hist_BKG);
	

// 	
	///Canvas	
	TCanvas *c = new TCanvas("c","Stack Plots", 1290, 65, 700, 900);
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
 	if(MinY>0) hEmpty1->SetMinimum(MinY); 
 	if(MaxY>0) hEmpty1->SetMaximum(MaxY); 
	hEmpty1->GetXaxis()->SetLabelSize(0.0);
	hEmpty1->GetYaxis()->SetLabelSize(0.04);
	hEmpty1->GetYaxis()->SetLabelFont(font);
	hEmpty1->Draw();
   
  
	hc.SetStyle(hist_Data, "data");
	hc.SetStyle(hSpectrum0, "spectrum0");
	hc.SetStyle(hSpectrum1, "spectrum1");
	hc.SetStyle(hSpectrum2, "spectrum2");
	hc.SetStyle(hSpectrum3, "spectrum3");
	hc.SetStyle(hSignal, "signal");
	//hc.SetStyle(, "");
	
// 	hSignal->Draw("hist same");
	hSpectrum3->Draw("hist same");
	hSpectrum2->Draw("hist same");
	hSpectrum1->Draw("hist same");
	hSpectrum0->Draw("hist same");
	hist_Data->Draw("ep same");
			
	if(kLogY) gPad->SetLogy();
	gPad->RedrawAxis();
// 	gPad->Modified(); 
// 	gPad->Update();

	TLegend *leg = new TLegend(0.42,0.70,0.92,0.92,NULL,"brNDC");
	leg->SetBorderSize(1);
	leg->SetLineColor(15);
	leg->SetLineStyle(1);
	leg->SetLineWidth(1);
	leg->SetFillColor(19);
	leg->SetFillStyle(3002);
	leg->SetTextFont(42); 
	leg->SetTextSize(0.03); 
	string legH = "Higgs m_{H}=" + hmass + " GeV (#times "+ hc.GetStringFromInt(SignalZoom)+")";
	leg->AddEntry(hist_Data,"2012 data","lp");
	leg->AddEntry(hSpectrum3, legH.c_str(),"lpf");
	leg->AddEntry(hSpectrum2,"Z#tau#tau","lpf");
	leg->AddEntry(hSpectrum1,"Electroweak","lpf");
	leg->AddEntry(hSpectrum0,"QCD multi-jets","lpf");
	
	leg->Draw();
   
// 	double shift = 0.9;
// 	if(kLogY) shift = 0.4;
//    
// 	double xL_neg = 0.8;
// 	double xL_pos = 1.2;
//    
// 	if( fabs(xLat) < 5 ){xL_neg = 0.95; xL_pos = 1.3; }
// 	if( fabs(xLat) < 1 ){xL_neg = 0.8; xL_pos = 1.2; }
// 	if( fabs(xLat) > 10 ){xL_neg = 0.95; xL_pos = 1.05; }
//     
// 	TLatex *   tex0 = new TLatex( xLat, yLat, "#int");
// 	tex0->SetTextFont(42);
// 	tex0->SetTextSize(0.025);
// 	tex0->SetLineWidth(2);
// 	tex0->Draw();
   
// 	double new_xLat = (xLat>0 ? xLat*xL_pos : xLat*xL_neg);
// 
// 	TLatex *   tex = new TLatex( new_xLat, yLat, "dt L = 4.7 fb^{-1}");
// 	tex->SetTextFont(42);
// 	tex->SetTextSize(0.035);
// 	tex->SetLineWidth(2);
// 	tex->Draw();
// 
// 	TLatex *   tex1 = new TLatex( xLat, yLat*shift, "#sqrt{s} = 7 TeV");
// 	tex1->SetTextFont(42);
// 	tex1->SetTextSize(0.035);
// 	tex1->SetLineWidth(2);
// 	tex1->Draw();

	///Down
	c->cd();
	TPad *pad2 = new TPad("pad2","pad2", 0, 0, 1, 0.2);
	hc.SetPad(pad2);
	pad2->SetTopMargin(0);
	pad2->SetBottomMargin(c->GetBottomMargin()*3.5 );
	pad2->Draw();
	pad2->cd();
	hEmpty2->GetXaxis()->SetRangeUser(MinX, MaxX); 
	hEmpty2->SetMaximum(1.55);
	hEmpty2->SetMinimum(0.45);
	hEmpty2->GetXaxis()->SetLabelSize(0.14);
	hEmpty2->GetYaxis()->SetLabelSize(0.14);
	hEmpty2->GetXaxis()->SetLabelFont(font);
	hEmpty2->GetYaxis()->SetLabelFont(font);
	hEmpty2->GetXaxis()->SetTitle(xTitle.c_str());
	hEmpty2->GetXaxis()->SetTitleFont(font);
	hEmpty2->GetXaxis()->SetTitleSize(0.14);
	hEmpty2->Draw();

	int ci5 = TColor::GetColor("#cfcc9f");
	int ci10 = TColor::GetColor("#e7e1bc");
	int ci20 = TColor::GetColor("#f1edda");
  
	MinX -=  kAdjustLeftBin 	? BinW : 0;
// 	MaxX -=  kAdjustRightBin 	? BinW : 0;
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
	h_Data_over_BKG->Draw("ep same");

	gPad->RedrawAxis();
// 	gPad->Modified(); 
// 	gPad->Update();

	
	f->cd();
	
	c->Write();

	hist_Data->Write("hist_massSR_data");
	hist_QCD->Write("hist_QCD");

	hmap_Sig[800000]->Write("hist_Signal");
	hmap_Sig[800001]->Write("hist_massSR_ztautaunj");
	hmap_Sig[800005]->Write("hist_massSR_ewbkg");

	//See https://svnweb.cern.ch/trac/atlasphys/browser/Physics/Higgs/HSG4/software/hadhad/MultiVariateAnalysis/TreeMaker/eos.mc.txt
	//Or use hc.GetHiggsMCnumber(125, "vbf")
	hmap_Sig[hc.GetHiggsMCnumber(125,"vbf")]->Write("test");
	hmap_Sig[161617]->Write("hist_massSR_VBFH125");
	hmap_Sig[161577]->Write("hist_massSR_ggH125");

	hmap_Sig[161657]->Write("hist_massSR_ZH125");
	hmap_Sig[161697]->Write("hist_massSR_WH125");

	hmap_Sig[161657]->Add(hmap_Sig[161697],1.);  //shouldnt do it like this
	hmap_Sig[161657]->Write("hist_massSR_VH125");



	//temporarily filling syst histos with nominal:
	hmap_Sig[800001]->Write("syst_TESdown_massSR_ztautaunj");
	hmap_Sig[800001]->Write("syst_TESup_massSR_ztautaunj");
//
//	hmap_Sig[161617]->Write("syst_METdown_massSR_VBFH125");
//	hmap_Sig[161617]->Write("syst_METup_massSR_VBFH125");
//	hmap_Sig[161617]->Write("syst_TESdown_massSR_VBFH125");
//	hmap_Sig[161617]->Write("syst_TESup_massSR_VBFH125");
//
//	hmap_Sig[161517]->Write("syst_METdown_massSR_ggH125");
//	hmap_Sig[161517]->Write("syst_METup_massSR_ggH125");
//	hmap_Sig[161517]->Write("syst_TESdown_massSR_ggH125");
//	hmap_Sig[161517]->Write("syst_TESup_massSR_ggH125");
//
//	hmap_Sig[161657]->Write("syst_METdown_massSR_VH125");
//	hmap_Sig[161657]->Write("syst_METup_massSR_VH125");
//	hmap_Sig[161657]->Write("syst_TESdown_massSR_VH125");
//	hmap_Sig[161657]->Write("syst_TESup_massSR_VH125");

	f->Close();
	
	cout<<fn<<endl;
}
