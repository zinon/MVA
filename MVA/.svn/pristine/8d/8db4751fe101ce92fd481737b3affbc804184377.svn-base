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
#include "TGaxis.h"
#include "TGraphAsymmErrors.h"

#include "TApplication.h"
#include "TRint.h"

#include "TLatex.h"

#include "HelperClass.h"
#include "MonteCarloBank.h"

using namespace std;


void BDTscore();

void CheckEmptyBins(TH1D *h, const string &s);
void CheckNegativeBinContent(TH1D *h, const string &s);

int main(int argc, char *argv[])
{
	//TApplication *myapp=new TApplication("myapp",0,0);
	BDTscore();
	//myapp->Run();
	return 0;
}

void BDTscore(){

	///external classes
	gSystem->Load("../../HelperClass/HelperClass_cpp.so");
	gSystem->Load("../../MonteCarloBank/MonteCarloBank_cpp.so");

	MonteCarloBank mcbank;
	HelperClass hc;

	///analysis settings
	string variable 			= "BDT_Weight";//"bdt_vbf";
	bool	kEWK_subtraction 	= true;  
	bool	kZtautau_subtraction= true;
	bool	kShow_StatErrorBands= true;
	bool    kFill_Empty_Bins 	= true;//Kyle's fix
	bool 	kPlotSignificance 	= false;
	double 	MaxYsignificance 	= 1.5;
	int		SignalZoom 			= 10;
	string classifier 			= "BDT";
	string 	QCDmodel 			= "SS";// notOS SS
	string 	version 			= "v10";
	string 	category 			= "vbf"; // vbf boosted 1jet 0jet
	string	region 				= "all"; // SR  CR

	//	string 	tag			       	= "50Trees_500LeafEvts_wHpT_CorrectedCS_QCDSS"; // 50Trees_500LeafEvts_NoMMC //
	//	string 	tag			       	= "50Trees_500LeafEvts_NoHpT_CorrectedCS_QCDSS"; // :)
		string 	tag			       	= "50Trees_500LeafEvts_NoHpT"; // vbf_boosted
		//	string  tag                             = "50Trees_500LeafEvts_NoHpT_QCDSS";//1jet 0 jet
	//       	string  tag                             = "50Trees_500LeafEvts_wHpT_QCDSS";//

	//	string  tag                            = "50Trees_500LeafEvts_BoostedPlus1Jet_QCDSS";
	string	purpose 			= "Plot";
	int 	Hmass 				= 125;
	string 	hmass 				= hc.GetStringFromInt(Hmass); // "allmasses"

	///file name
	string 	fn 	 = "plots/plot_BDTscore_"+category+"_"+hmass+"_"+region+"_"+version+"_"+tag+".root";	
	
	///blind - unblind
	bool kShowData = region == "all";//used "CR" for blind. /// SR is blind for the moment, no data overlaid - use SR for limits

	///
	hc.SetTreeName("mva");
	hc.SetVersion(version);
	hc.SetProjectTag(tag); // tag used to distinguish studies - defined in ../Weighting/RunOverAllFiles.batch
	hc.SetPath("../../Ntuples");
	
	///plot settings
	bool	kShowSignal_Alone = true;
	bool	kShowQCD_Alone = false;
	bool 	kShowSpectrumWithSignal = false;
	
	bool 	kAutoMaxYaxis = true;
	double 	AutoOffsetTimes = 1.40; 

	int	xNdivisions = 0;
	
	double RatioMinY= 0.55; 
	double RatioMaxY = 1.45; 
	
	double 	MinY = 1e-6;
	double 	MaxY = 1000.0;
	bool 	kLogY = false;
	bool 	kAdjustLeftBin = false;
	bool 	kAdjustRightBin = false;
	
	string 	xTitle = "BDT score";

	/// category settings
	string fillcolor; 
	double	QCD_TrackFitFactor = 1;
	double	Z_TrackFitFactor = 1;	
	
	if(category == "vbf"){

      	//	fillcolor = "green";
		fillcolor = "harmonized";
			
		//QCD_TrackFitFactor = 0.33185; Z_TrackFitFactor = 0.228793; //v10
		//						QCD_TrackFitFactor = 0.432849;  Z_TrackFitFactor = 0.0771384;//updated MedMedCR
						QCD_TrackFitFactor = 0.503375;  Z_TrackFitFactor =0;//Reverse taudEta CR
	}else if(category == "boosted"){
			//fillcolor = "azure";
		fillcolor = "harmonized";
		
					QCD_TrackFitFactor = 0.175163;  Z_TrackFitFactor = 0.537113;//v10 
			//   QCD_TrackFitFactor = 0.418112;  Z_TrackFitFactor = 0.137653; //med med 
		   //QCD_TrackFitFactor = 0.606614l; Z_TrackFitFactor =0;//Reverse taudEta CR
		//	QCD_TrackFitFactor = 0.193098;  Z_TrackFitFactor = 0.453808; //Boosted+1Jet category
	}else if( category == "1jet"){
		//fillcolor = "blue";
		fillcolor = "harmonized";
		
	       	QCD_TrackFitFactor = 0.328376;   Z_TrackFitFactor = 0.250448;//v10 
		//	QCD_TrackFitFactor = 0.450998;   Z_TrackFitFactor = 0.0455698;// Medium Medium 
		//	  QCD_TrackFitFactor = 0.521353;  Z_TrackFitFactor = 0.0169697;// Reverse taudEta CR
	}else if( category == "0jet"){
		//fillcolor = "magenta";
		fillcolor = "harmonized";
		
			QCD_TrackFitFactor = 0.394051;   Z_TrackFitFactor = 0.180862;//v10
			//            QCD_TrackFitFactor = 0.447054;  Z_TrackFitFactor = 0.0776485;// Med Med CR  
			    //	  QCD_TrackFitFactor = 0.502023;  Z_TrackFitFactor = 0.0558228;// Reverse tauDeta CR
	}else{
		cout<<"\nplease, choose a category. Exiting ..."<<endl;
		exit(0);
	}



	///Binning =========================================================================================================
	bool kVariableBinning = false;	
	
	//range
	double 	firstbinX = 0.0;
	double 	lastbinX = 1.0;	
	
	//plotting limits
	double 	MinX = firstbinX; 
	double 	MaxX = lastbinX;
	
	///note: fixed and variable binning must be unrelated
	
	//fixed binning
	double 	BinWidth = 0.033;
	int 	NbinsFixedWidth = ceil( (lastbinX - firstbinX)/BinWidth );
	cout<<"Fixed width, N bins  "<<NbinsFixedWidth<<endl;

	//variable binning
	static const int NumVarBins = 16; //the histogram will have NumVarBins-1 bins

	Float_t Bins[NumVarBins];
	Float_t this_value=0;
		
	int nbins = NumVarBins - 1;
	Bins[0] = firstbinX;
	
	for(int i=1; i<NumVarBins; i++){
		if(i<=18) this_value += 0.033;//Set the width of the first set of bins

	    // else if(i<=6) this_value += 0.05;//When i = (NumVarBins-1) then you are setting the width of the last bin
		Bins[i] = firstbinX + this_value;
	}
 


	///latex
	double ylat(1);
	double xlat = MinX * 1.05;
	
	///list of MC samples
	vector<int> RunsVector = hc.GetRunsVector(Hmass);
	
	///data tree
	cout<<"\ncreating tree map for data ..."<<endl;
	TTree *tData = hc.GetTreeDataMVA( "*", classifier, category, hmass, tag);//must match root files
	hc.SetLumiPerRunMap();
	int NtreeEntries = tData->GetEntries();
	cout<<"\ntotal data entries : "<<NtreeEntries<<endl;
	
	///lumi
	double DataLumi = hc.GetRunsListTotalLumi("inb");
	cout<<"\nData lumi "<<DataLumi<<" nb-1"<<endl<<endl;
	double lumi_fb = DataLumi/1e6;
	char lumi_number[24];
	sprintf(lumi_number, "%.2f", lumi_fb);
	string lumi_str = lumi_number;
	
	/// mc tree map
	map<int, TTree *> tmap;
	cout<<"creating tree map for mc"<<endl;
	for(vector<int>::iterator it=RunsVector.begin(); it != RunsVector.end(); it++){
		if( *it >= 800000) continue;
		tmap.insert ( pair<int, TTree *>(*it,  hc.GetTreeMCMVA( hc.GetStringFromInt(*it), classifier, category, hmass, tag) ) );//needs to match root file names
	}
	
	
	map<int, TH1D *> hmap_Sig;
	map<int, TH1D *> hmap_Bkg;
		//map<int, TH1D *> hmap_Sig_MassWindow;
	for(vector<int>::iterator it=RunsVector.begin(); it != RunsVector.end(); it++){
		if( kVariableBinning ){
			hmap_Sig.insert ( pair<int,TH1D *>(*it, new  TH1D("",	"",	nbins, Bins)) );
			hmap_Bkg.insert ( pair<int,TH1D *>(*it, new  TH1D("",	"",	nbins, Bins)) );
		}else{
			hmap_Sig.insert ( pair<int,TH1D *>(*it, new  TH1D("",	"",	NbinsFixedWidth, firstbinX, lastbinX)) );
			hmap_Bkg.insert ( pair<int,TH1D *>(*it, new  TH1D("",	"",	NbinsFixedWidth, firstbinX, lastbinX)) );
		}
		//hmap_Sig_MassWindow.insert ( pair<int,TH1D *>(*it, new  TH1D("",	"",	nbins, Bins)) );
	}
	
	///give names
	cout<<"\nrenaming plots ..."<<endl;
	hc.SetHistoNames1D(hmap_Sig, "OS");
	hc.SetHistoNames1D(hmap_Bkg, QCDmodel);
	//hc.SetHistoNames1D(hmap_Sig_MassWindow, "OS_MassWindow");
	
	///plot making
	//for reference:TCut HelperClass::GetCut(const string &category, const string &qq, const string &purpose, const string &region){
	//the region can be "CR" or "SR" or "all"
	cout<<"\nCuts for search region : \n"<<hc.GetCut(category, "OS", purpose,region).GetTitle()<<"   for category "<<category<<endl;
	//	cout<<"\nCuts for search region + mass window : \n"<<hc.GetCut(category, "OS", "MVA","CR").GetTitle()<<endl;
	
	cout<<"\nbooking histograms ..."<<endl;	
	double BinW;
	TH1D* hist_Data;
	TH1D* hist_Data_TrackFit;
	TH1D* hist_QCD;
	TH1D* hist_BKG;
	TH1D* hTop;
	TH1D* hVH;
	TH1D* hSignal;
	TH1D* hSpectrum0;
	TH1D* hSpectrum1;
	TH1D* hSpectrum2;
	TH1D* hSpectrum3;
	TH1D* hist_BKG_empty_bin_fix;
	

		
	if( kVariableBinning ){
		cout<<"\nHistogram binning : variable"<<endl;
		hist_Data 			= new TH1D("hist_Data",	"",	nbins, Bins);
	
		hist_Data_TrackFit 	= new TH1D("hist_Data_TrackFit",	"",	nbins, Bins);
	
		hist_QCD 			= new TH1D("hist_QCD",	"",	nbins, Bins);
	
		hist_BKG			= new TH1D("hist_BKG",	"",	nbins, Bins);
	
		hTop 				= new TH1D("hTop","",	nbins, Bins);
	
		hVH 				= new TH1D("hVH","",	nbins, Bins);
			
		hSignal 			= new TH1D("hSignal","",	nbins, Bins);
	
		hSpectrum0 			= new TH1D("hSpectrum0","",	nbins, Bins);
	
		hSpectrum1 			= new TH1D("hSpectrum1","",	nbins, Bins);
	
		hSpectrum2 			= new TH1D("hSpectrum2","",	nbins, Bins);
	
		hSpectrum3 			= new TH1D("hSpectrum3","",	nbins, Bins);
		
		hist_BKG_empty_bin_fix	= new TH1D("hist_BKG_empty_bin_fix",	"", nbins, Bins);
		

		
	}else{
		cout<<"\nHistogram binning : fixed"<<endl;
		
		hist_Data 			= new TH1D("hist_Data",	"",	NbinsFixedWidth, firstbinX, lastbinX);
	
		hist_Data_TrackFit 	= new TH1D("hist_Data_TrackFit",	"",	NbinsFixedWidth, firstbinX, lastbinX);
	
		hist_QCD 			= new TH1D("hist_QCD",	"", NbinsFixedWidth, firstbinX, lastbinX);
	
		hist_BKG			= new TH1D("hist_BKG",	"", NbinsFixedWidth, firstbinX, lastbinX);
	
		hTop 				= new TH1D("hTop","",	NbinsFixedWidth, firstbinX, lastbinX);
	
		hVH 				= new TH1D("hVH","",	NbinsFixedWidth, firstbinX, lastbinX);
				
		hSignal 			= new TH1D("hSignal","", NbinsFixedWidth, firstbinX, lastbinX);	
	
		hSpectrum0 			= new TH1D("hSpectrum0","",	NbinsFixedWidth, firstbinX, lastbinX);
	
		hSpectrum1 			= new TH1D("hSpectrum1","",	NbinsFixedWidth, firstbinX, lastbinX);
	
		hSpectrum2 			= new TH1D("hSpectrum2","", NbinsFixedWidth, firstbinX, lastbinX);
	
		hSpectrum3 			= new TH1D("hSpectrum3","",	NbinsFixedWidth, firstbinX, lastbinX);

		hist_BKG_empty_bin_fix	= new TH1D("hist_BKG_empty_bin_fix",	"", NbinsFixedWidth, firstbinX, lastbinX);
		
		BinW = (lastbinX - firstbinX)/NbinsFixedWidth;
		cout<<"\nbin width (fixed) : "<<BinW<<endl;
	}
			
	cout<<"\nfilling up histograms ..."<<endl;
	/// -- data
	hc.MakePlot( tData, hist_Data,  hc.GetCut(category, "OS", purpose, region), variable );
		
	/// -- data - Track Fit and QCD normalization
	hc.MakePlot( tData, hist_Data_TrackFit,  hc.GetCut(category, "OS", "TrackFit",region), variable );
		
	/// -- QCD from data
	hc.MakePlot( tData, hist_QCD,  hc.GetCut(category, QCDmodel, purpose, region), variable );
		
	/// -- MC search region
	for(map<int, TH1D *>::iterator it = hmap_Sig.begin(); it != hmap_Sig.end(); it++){
		if(it->first < 800000)
			hc.MakePlot(tmap[it->first], it->second, hc.GetCut(category, "OS", purpose, region), variable );	
	}
		
	/// -- MC search region - Mass Window - for Z normalization
// 	for(map<int, TH1D *>::iterator it = hmap_Sig_MassWindow.begin(); it != hmap_Sig_MassWindow.end(); it++){
// 		if(it->first < 800000)
// 		  hc.MakePlot(tmap[it->first], it->second, hc.GetCut(category, "OS", purpose, region), variable ); //??
// 	}
		
	/// -- MC bkg model - for bkg subtraction
	for(map<int, TH1D *>::iterator it = hmap_Bkg.begin(); it != hmap_Bkg.end(); it++){
		if(it->first < 800000)
			hc.MakePlot(tmap[it->first], it->second, hc.GetCut(category, QCDmodel, purpose, region), variable );
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
// 	for(map<int, TH1D *>::iterator it = hmap_Sig_MassWindow.begin(); it != hmap_Sig_MassWindow.end(); it++){
// 		if(it->first < 800000){
// 			it->second->Scale( mcbank.Get_Norm(it->first, DataLumi) );
// 		}
// 	}
	///fill inclusive MC plots
	cout<<"\nmaking inclusive histos"<<endl;
	for(vector<int>::iterator it=RunsVector.begin(); it != RunsVector.end(); it++){
		if( *it >= 800000) continue;
		
		if( hc.Is("Higgs", *it) ) {
			//hmap_Sig[800000]->Sumw2(); 
			//hmap_Bkg[800000]->Sumw2();
		  
			hmap_Sig[800000]->Add( hmap_Sig[*it]); 
			hmap_Bkg[800000]->Add( hmap_Bkg[*it]);
		  //hmap_Sig_MassWindow[800000]->Add( hmap_Sig_MassWindow[*it]); 
		}
		if( hc.Is("Ztautau", *it) ) {
			//hmap_Sig[800001]->Sumw2(); 
			//hmap_Bkg[800001]->Sumw2();
		  
			hmap_Sig[800001]->Add( hmap_Sig[*it]); 
			hmap_Bkg[800001]->Add( hmap_Bkg[*it]);
		  //hmap_Sig_MassWindow[800001]->Add( hmap_Sig_MassWindow[*it]); 
		}
		if( hc.Is("Wtaunu", *it) ) {
			//hmap_Sig[800002]->Sumw2(); 
			//hmap_Bkg[800002]->Sumw2();
		  
			hmap_Sig[800002]->Add( hmap_Sig[*it]); 
			hmap_Bkg[800002]->Add( hmap_Bkg[*it]);
		  //hmap_Sig_MassWindow[800002]->Add( hmap_Sig_MassWindow[*it]);
		}
		if( hc.Is("Top", *it) ) {
			//hmap_Sig[800003]->Sumw2(); 
			//hmap_Bkg[800003]->Sumw2();
		  
			hmap_Sig[800003]->Add( hmap_Sig[*it]); 
			hmap_Bkg[800003]->Add( hmap_Bkg[*it]);
		  //hmap_Sig_MassWindow[800003]->Add( hmap_Sig_MassWindow[*it]);
		}
		if( hc.Is("Dibosons", *it) ) {
			//hmap_Sig[800004]->Sumw2(); 
			//hmap_Bkg[800004]->Sumw2();
		  
			hmap_Sig[800004]->Add( hmap_Sig[*it]); 
			hmap_Bkg[800004]->Add( hmap_Bkg[*it]);
			//hmap_Sig_MassWindow[800004]->Add( hmap_Sig_MassWindow[*it]); 
		}
		if( hc.Is("Electroweak", *it) ) {
			//hmap_Sig[800005]->Sumw2(); 
			//hmap_Bkg[800005]->Sumw2();
		  
			hmap_Sig[800005]->Add( hmap_Sig[*it]); 
			hmap_Bkg[800005]->Add( hmap_Bkg[*it]);
		  //hmap_Sig_MassWindow[800005]->Add( hmap_Sig_MassWindow[*it]); 
		}
		if( hc.Is("VH", *it) ) {
			//hmap_Sig[800006]->Sumw2(); 
			//hmap_Bkg[800006]->Sumw2();
		  
			hmap_Sig[800006]->Add( hmap_Sig[*it]); 
			hmap_Bkg[800006]->Add( hmap_Bkg[*it]);
		  //hmap_Sig_MassWindow[800005]->Add( hmap_Sig_MassWindow[*it]); 
		}
		if( hc.Is("Top", *it) ) {
		 // hmap_Sig[800005]->Sumw2(); 
		 // hmap_Bkg[800005]->Sumw2();
			// 
		 // hmap_Sig[800005]->Add( hmap_Sig[*it]); 
		 // hmap_Bkg[800005]->Add( hmap_Bkg[*it]);
		 // //hmap_Sig_MassWindow[800005]->Add( hmap_Sig_MassWindow[*it]); 
		}

	}

///normalize QCD =============================================================================

	//new way without Noels SR and CR
	double QCDnorm =  QCD_TrackFitFactor * hist_Data_TrackFit->Integral(); 
	double QCD_integral = hist_QCD->Integral();
	if(QCD_integral<1e-6) { cout<<"Empty QCD histo. Bye bye ..."<<endl; exit(0); }
	double QCDweight_f = QCDnorm/QCD_integral;
	
	cout<<"\nNormalize QCD bkg to Track Fit"<<endl;
	cout<<"\tQCD target norm  "<<QCDnorm<<endl;
	cout<<"\tQCD final norm factor (using fQCD)  "<<QCDweight_f<<endl;
	
	//apply qcd weigth
	cout<<"\tQCD integral before "<<hist_QCD->Integral()<<endl;
	hist_QCD->Scale( QCDweight_f );
	cout<<"\tQCD integral after "<<hist_QCD->Integral()<<endl<<endl;
	
	///Perfrom EWK / Ztautau subtraction from QCD============================================================
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
	
	
	///normalize Ztautau ==========================================================================
	
	//new way without Noels SR and CR
	double Znorm =  Z_TrackFitFactor * hist_Data_TrackFit->Integral(); 
	double Z_integral = hmap_Sig[800001]->Integral();
	if(Z_integral <1e-6) { cout<<"Empty Z histo. Bye bye ..."<<endl; exit(0); }
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
	cout<<"All Higgs    "<<hmap_Sig[800000]->GetEntries()<<" : "<<hmap_Sig[800000]->Integral()<<endl;
	cout<<"VBF 125    "<<	hmap_Sig[161617]->GetEntries()<<" : "<<hmap_Sig[161617]->Integral()<<endl;
	cout<<"GGF 125    "<<	hmap_Sig[161577]->GetEntries()<<" : "<<hmap_Sig[161577]->Integral()<<endl;
	cout<<"VH 125    "<<	hmap_Sig[800006]->GetEntries()<<" : "<<hmap_Sig[800006]->Integral()<<endl;
	cout<<"Z    "<<hmap_Sig[800001]->GetEntries()<<" : "<<hmap_Sig[800001]->Integral()<<endl;
	cout<<"EWK  "<<hmap_Sig[800005]->GetEntries()<<" : "<<hmap_Sig[800005]->Integral()<<endl;
	cout<<"VH   "<<hmap_Sig[800006]->GetEntries()<<" : "<<hmap_Sig[800006]->Integral()<<endl;
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
	TH1D *hEmpty1 = new TH1D("hEmpty1",	"",	nbins, firstbinX, lastbinX);
	TH1D *hEmpty2 = new TH1D("hEmpty2",	"",	nbins, firstbinX, lastbinX);
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
	hc.SetStyle(hist_QCD, "qcd");
	

//	hc.SetStyle(hist_Data, "data");
//	hc.SetStyle(hSpectrum0, "spectrum0");
//	hc.SetStyle(hSpectrum1, "spectrum1");
//	hc.SetStyle(hSpectrum2, "spectrum2");
//	hc.SetStyle(hSpectrum3, "spectrum3");
//	hc.SetStyle(hSignal, "signal");
	//
// 	hSignal->Draw("hist same");

	if(kShowSpectrumWithSignal) hSpectrum3->Draw("hist same");//Comment out stacked signal for now
	hSpectrum2->Draw("hist same");
	hSpectrum1->Draw("hist same");
	hSpectrum0->Draw("hist same");
	
	if(kShowSignal_Alone) hSignal->Draw("hist same");
	if(kShowQCD_Alone) hist_QCD->Draw("hist same");	
	
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
	else if(kShowSignal_Alone)
		leg->AddEntry(hSignal, legH.c_str(),"l");
	else{
		//do nothing
	}
	leg->AddEntry(hSpectrum2,"Z/#gamma* #rightarrow #tau#tau","lpf");
	leg->AddEntry(hSpectrum1,"Electroweak","lpf");
	leg->AddEntry(hSpectrum0,"QCD multi-jets","lpf");
			
	
	leg->Draw();
   

	string lat_categ = 	
			category == "boosted" ? "Boosted" :
		 	category == "vbf" ? "VBF":
		  	category == "1jet" ? "1-jet" :
			category == "0jet" ? "0-jet" : "Planet earth";

	if( kAutoMaxYaxis )  ylat = maxim_y_new*0.9;
			
	//       	string thisregion = region == "CR" ? "Control Region" : region == "SR" ? "Signal Region" : region == "all" ? "NoMassWindow" :"Which Region?";
	string thisregion = region == "CR" ? "Control Region" : region == "SR" ? "Signal Region" : region == "all" ? "MediumMedium Control Region" :"Which Region?";
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
       	if(kShowData) h_Data_over_BKG->Draw("ep same");//tmp for blind

	gPad->RedrawAxis();
// 	gPad->Modified(); 
// 	gPad->Update();




	/// empty bins check up  ================================================================================= 
	CheckEmptyBins(hmap_Sig[161617] , "VBFH125");	
	
	CheckEmptyBins(hmap_Sig[161577] , "ggH125");	
	
	CheckEmptyBins(hmap_Sig[800006] , "VH");
	
	CheckEmptyBins(hmap_Sig[800001] , "Ztautau");	
	
	CheckEmptyBins(hmap_Sig[800005] , "EWK");
	
	CheckEmptyBins(hist_QCD , "QCD");	
	
	CheckEmptyBins(hist_Data, "Data");
	
	CheckEmptyBins(hmap_Sig[800000] , "Signal");	
	

	//CheckEmptyBins( , "");			

	


// 	h_empty_bin_fix_Z;
// 	h_empty_bin_fix_QCD;
// 	h_empty_bin_fix_EW;
// 	h_empty_bin_fix_H;
				
	///___ Apply Kyle's Empty Bin Fix__________________________________________________________
		
	double sumW2TotBin_Z=0, avWeightBin_Z=0, avW2Bin_Z=0;
	double sumW2TotBin_QCD=0, avWeightBin_QCD=0, avW2Bin_QCD=0;
	double sumW2TotBin_EW=0, avWeightBin_EW=0, avW2Bin_EW=0;

	double sumW2TotBin_H=0, avWeightBin_H=0, avW2Bin_H=0;
	
	for(int j=1; j<=hmap_Sig[800001]->GetNbinsX(); ++j){
		sumW2TotBin_Z   += pow( hmap_Sig[800001]->GetBinError(j) , 2); // DON't forget to square!
		sumW2TotBin_QCD += pow( hist_QCD        ->GetBinError(j) , 2); 
		sumW2TotBin_EW  += pow( hmap_Sig[800005]->GetBinError(j) , 2); 
		sumW2TotBin_H   += pow( hmap_Sig[800000]->GetBinError(j) , 2); 
	}
	avWeightBin_Z += hmap_Sig[800001]->GetSumOfWeights() / hmap_Sig[800001]->GetEntries();
	avW2Bin_Z = sumW2TotBin_Z/hmap_Sig[800001]->GetEntries();
	
	avWeightBin_QCD += hist_QCD->GetSumOfWeights() / hist_QCD->GetEntries();
	avW2Bin_QCD = sumW2TotBin_QCD/hist_QCD->GetEntries();
	
	avWeightBin_EW += hmap_Sig[800005]->GetSumOfWeights() / hmap_Sig[800005]->GetEntries();
	avW2Bin_EW = sumW2TotBin_EW/hmap_Sig[800005]->GetEntries();

	avWeightBin_H += hmap_Sig[800000]->GetSumOfWeights() / hmap_Sig[800000]->GetEntries();
	avW2Bin_H = sumW2TotBin_H/hmap_Sig[800000]->GetEntries();
	
	cout<<"For Ztautau:" <<endl;
	cout<<"GetSumOfWeights: "<< hmap_Sig[800001]->GetSumOfWeights() <<" Num Entries "<<hmap_Sig[800001]->GetEntries()<<" counted error sum squared "<<sumW2TotBin_Z<<endl;
	cout << "hist bin sum: avW, stdev, avW2 " << avWeightBin_Z << ", "<< sqrt(sumW2TotBin_Z) << ", " << avW2Bin_Z << endl;
	
	cout<<"For QCD:" <<endl;
	cout << "hist bin sum: avW, stdev, avW2 " << avWeightBin_QCD << ", "<< sqrt(sumW2TotBin_QCD) << ", " << avW2Bin_QCD << endl;
	
	cout<<"For EW:" <<endl;
	cout << "hist bin sum: avW, stdev, avW2 " << avWeightBin_EW << ", "<< sqrt(sumW2TotBin_EW) << ", " << avW2Bin_EW << endl;
	
	double Z = 999.; double Q = 999.; double EW = 999.;  double H = 999.;

// now fill empty bins with
  // binContent = avWeight     [or avWeightbin]
  // binError = sqrt(avW2)     [or sqrt(avW2Bin)]
	

	if(kFill_Empty_Bins){
		for(int j=1; j<=hmap_Sig[800001]->GetNbinsX(); ++j){
			Z =  hmap_Sig[800001]->GetBinContent(j);
			if( Z  < 1e-6 )  { 
				cout<<"empty Z: "<<hmap_Sig[800001]->GetBinCenter(j)<<endl; 
				hmap_Sig[800001]->SetBinContent(j,avWeightBin_Z); 
				hmap_Sig[800001]->SetBinError(j,sqrt(avW2Bin_Z));
			}
			Q =  hist_QCD->GetBinContent(j);
			if( Q  < 1e-6 )  { 
				hist_QCD->SetBinContent(j,avWeightBin_QCD); 
				hist_QCD->SetBinError(j,sqrt(avW2Bin_QCD));
			}
			EW =  hmap_Sig[800005]->GetBinContent(j);
			if( EW  < 1e-6 )  { 
				hmap_Sig[800005]->SetBinContent(j,avWeightBin_EW); 
				hmap_Sig[800005]->SetBinError(j,sqrt(avW2Bin_EW));
			}  
			H =  hmap_Sig[800000]->GetBinContent(j);
			if( H  < 1e-6 )  { 
				hmap_Sig[800000]->SetBinContent(j,avWeightBin_H); 
				hmap_Sig[800000]->SetBinError(j,sqrt(avW2Bin_H));
			}  

		}
		
		hist_BKG_empty_bin_fix->Add( hist_QCD, 1.0); ///qcd
		hist_BKG_empty_bin_fix->Add( hmap_Sig[800005], 1.0);///ew
		hist_BKG_empty_bin_fix->Add( hmap_Sig[800001], 1.0); ///Z
	}



	
	//__ End Kyle's Empty Bin Fix______________________________________________________
	





	/// Store results ================================================================================= 
	f->cd();
	
	c->Write();
	
	hmap_Sig[800000]->Write("hist_Signal");
	
	hmap_Sig[161617]->Write("hist_bdtVBF_VBFH125");
	
	hmap_Sig[161577]->Write("hist_bdtVBF_ggH125");
	
	hmap_Sig[800006]->Write("hist_bdtVBF_VH125");
	
	hmap_Sig[800001]->Write("hist_bdtVBF_ztautaunj");
	
	hmap_Sig[800005]->Write("hist_bdtVBF_ewbkg");
	
	hist_QCD->Write("hist_QCD");
	
	hist_Data->Write("hist_bdtVBF_data");
	
	hist_BKG->Write("hist_bkg");
	
	if(kFill_Empty_Bins) hist_BKG_empty_bin_fix->Write("hist_bkg_empty_bin_fix");

    //See https://svnweb.cern.ch/trac/atlasphys/browser/Physics/Higgs/HSG4/software/hadhad/MultiVariateAnalysis/TreeMaker/eos.mc.txt                  
    //Or use hc.GetHiggsMCnumber(125, "vbf")                                                                                                          
	//hmap_Sig[hc.GetHiggsMCnumber(125,"vbf")]->Write("test");


	//hmap_Sig[161657]->Write("hist_bdtVBF_ZH125");
	//hmap_Sig[161697]->Write("hist_bdtVBF_WH125");
	//hmap_Sig[161657]->Sumw2();
	
// 	hmap_Sig[161657]->Add(hmap_Sig[161697],1.);  //shouldnt do it like this                                                                           
// 	hmap_Sig[161657]->Write("hist_bdtVBF_VH125");
	


        //temporarily filling syst histos with nominal:                                                      
	hmap_Sig[800001]->Write("syst_TESdown_bdtVBF_ztautaunj");
	hmap_Sig[800001]->Write("syst_TESup_bdtVBF_ztautaunj");

	f->Close();
	


	cout<<fn<<endl;
	
	cout<<"\nData tree entries : "<<tData->GetEntries()<<" <--- check if same with Make2DTrackHistos.C in TrackFit"<<endl;
	
	if(kVariableBinning){
	
		cout<<"\nHistogram: range = "<<firstbinX<<" - "<<lastbinX<<endl;
		for(int i=0; i<NumVarBins; i++){
			cout<<"Bin: "<<i<<" "<<Bins[i]<<endl;
		}
	}else{
		cout<<"\nHistogram: range = "<<firstbinX<<" - "<<lastbinX<<", "<<nbins<<"bins, bin width "<< BinW<<endl;
	}
	
	
	
}

void CheckEmptyBins(TH1D *h, const string &s){
	cout<<"Checking "<<s<<" for empty bins"<<endl;
	bool found(false);
	int n = h->GetNbinsX();
	for(int i = 1; i <= n; i++){
		
		double bc = h->GetBinContent(i);
		
		if( bc < 1e-6 ) {
			cout<<" empty bin "<<i<<" "<<h->GetBinLowEdge(i)<<" - "<<h->GetBinWidth(i)<<endl;
			found = true;
		}
	}
	
	if(!found) cout<<"\n"<<s<<" is OK"<<endl;
	cout<<endl;
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
