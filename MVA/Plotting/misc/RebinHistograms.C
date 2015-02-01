/*_____________________________
Take the output from BDTscore.C and rebin the histograms such that there are no empty bins. 
Final histograms have equal bin widths from 0 to 1.  Currently I ask BDTscore.C to create histograms
with 1000 bins, to be rebinned here.
______________________________
*/

void RebinHistograms(){
  //	     TString Input = "plot_BDTscore_2jet_125_SR_v8.root"){
  TFile *_file1 = TFile::Open("plot_BDTscore_2jet_125_SR_v8.root");
  // TFile *_file1 = TFile::Open("plot_BDTscore_2jet_125_SR_v8_0-1_50bins.root");  
  //        TFile *_file1 = TFile::Open("plot_BDTscore_2jet_125_SR_v8_1000bins.root");
  //        TFile *_file1 = TFile::Open("plot_BDTscore_2jet_125_SR_v8_all125s_1000bins.root");
  //	TFile *_file1 = TFile::Open("plot_BDTscore_1jet_allmasses_SR_v8_1000bins.root");  
  //  TFile *_file1 = TFile::Open("plot_BDTscore_2jet_125_SR_v8_1000bins_saveVBF125trainOnly.root");
  //	TFile *_file1 = TFile::Open("plot_BDTscore_2jet_125_SR_v8_VBF125trainOnly_diJetdEtaCut.root");


      //________________________________________
      // Get the histograms from the input file
      //________________________________________

  TH1D* hist_bdtVBF_data_k;
  TH1D* hist_QCD_k;
  TH1D* hist_bdtVBF_ztautaunj_k;
  TH1D* hist_bdtVBF_ewbkg_k;
  TH1D* hist_bdtVBF_VBFH125_k;
  TH1D*	hist_bdtVBF_ggH125_k;	
  TH1D* hist_bdtVBF_ZH125_k;
  TH1D* hist_bdtVBF_WH125_k;	
  TH1D* hist_bdtVBF_VH125_k;     
  
 hist_bdtVBF_data_k     = (TH1D*)_file1->Get("hist_bdtVBF_data");
 hist_QCD_k             = (TH1D*)_file1->Get("hist_QCD");
 hist_bdtVBF_ztautaunj_k= (TH1D*)_file1->Get("hist_bdtVBF_ztautaunj");
 hist_bdtVBF_ewbkg_k=	  (TH1D*)_file1->Get("hist_bdtVBF_ewbkg");
 hist_bdtVBF_VBFH125_k=	  (TH1D*)_file1->Get("hist_bdtVBF_VBFH125");
 hist_bdtVBF_ggH125_k=	  (TH1D*)_file1->Get("hist_bdtVBF_ggH125");	
 hist_bdtVBF_VH125_k=     (TH1D*)_file1->Get("hist_bdtVBF_VH125");
 
 cout<<"Number of bins: "<< hist_bdtVBF_data->GetNbinsX()<<endl;
 double Content_Bkg[1000]=0;

 double Content_Ztt[1000]=0;
 double Content_Ztt_tmp =0;
 double BinError_Ztt_tmp=0;
 double NewBinError_Ztt[1000] =0.;

 double Content_Data[1000]=0;
 double Content_Data_tmp =0;
 double BinError_Data_tmp=0;
 double NewBinError_Data[1000] =0.;

 double Content_QCD[1000]=0;
 double Content_QCD_tmp =0;
 double BinError_QCD_tmp=0;
 double NewBinError_QCD[1000] =0.;

 double Content_ewbkg[1000]=0;
 double Content_ewbkg_tmp =0;
 double BinError_ewbkg_tmp=0;
 double NewBinError_ewbkg[1000] =0.;

 double Content_VBF[1000]=0;
 double Content_VBF_tmp =0;
 double BinError_VBF_tmp=0;
 double NewBinError_VBF[1000] =0.;

 double Content_ggH[1000]=0;
 double Content_ggH_tmp =0;
 double BinError_ggH_tmp=0;
 double NewBinError_ggH[1000] =0.;

 double Content_VH[1000]=0;
 double Content_VH_tmp =0;
 double BinError_VH_tmp=0;
 double NewBinError_VH[1000] =0.;

 int NewBin =0;


      //________________________________________
      // Loop through the finely-binned input histograms and add the bin content
      // until > 1. Then fill new histograms which will have no zero-content bins
      //________________________________________


 for(int i =1; i<=hist_QCD_k->GetNbinsX() ; i++){
   //   cout<<"Bin content: "<<i<<" "<< hist_bdtVBF_ztautaunj_k->GetBinContent(i)<<" error: "<<hist_bdtVBF_ztautaunj_k->GetBinError(i) <<endl;

   Content_Ztt_tmp  += hist_bdtVBF_ztautaunj_k->GetBinContent(i);
   BinError_Ztt_tmp += hist_bdtVBF_ztautaunj_k->GetBinError(i) * hist_bdtVBF_ztautaunj_k->GetBinError(i)  ;

   Content_Data_tmp  += hist_bdtVBF_data_k->GetBinContent(i);
   BinError_Data_tmp += hist_bdtVBF_data_k->GetBinError(i) * hist_bdtVBF_data_k->GetBinError(i)  ;

   Content_QCD_tmp  += hist_QCD_k->GetBinContent(i);
   BinError_QCD_tmp += hist_QCD_k->GetBinError(i) * hist_QCD_k->GetBinError(i)  ;

   Content_ewbkg_tmp  += hist_bdtVBF_ewbkg_k->GetBinContent(i);
   BinError_ewbkg_tmp += hist_bdtVBF_ewbkg_k->GetBinError(i) * hist_bdtVBF_ewbkg_k->GetBinError(i)  ;

   Content_VBF_tmp  += hist_bdtVBF_VBFH125_k->GetBinContent(i);
   BinError_VBF_tmp += hist_bdtVBF_VBFH125_k->GetBinError(i) * hist_bdtVBF_VBFH125_k->GetBinError(i)  ;

   Content_ggH_tmp  += hist_bdtVBF_ggH125_k->GetBinContent(i);
   BinError_ggH_tmp += hist_bdtVBF_ggH125_k->GetBinError(i) * hist_bdtVBF_ggH125_k->GetBinError(i)  ;

   Content_VH_tmp  += hist_bdtVBF_VH125_k->GetBinContent(i);
   BinError_VH_tmp += hist_bdtVBF_VH125_k->GetBinError(i) * hist_bdtVBF_VH125_k->GetBinError(i)  ;

   //___________Require that 1 or all or sum of backgrounds is < 1 per bin________
   //   if(Content_Ztt_tmp >0 ){
   //   if(Content_Ztt_tmp >= 1 && Content_QCD_tmp >= 1 && Content_ewbkg_tmp >= 1 ){
   //   if(Content_Ztt_tmp > 0 && Content_QCD_tmp > 0 && Content_ewbkg_tmp > 0 ){
   if((Content_Ztt_tmp + Content_QCD_tmp + Content_ewbkg_tmp) > 0 ){
     NewBin++;

     Content_Ztt[NewBin] = Content_Ztt_tmp;
     NewBinError_Ztt[NewBin] = sqrt(BinError_Ztt_tmp);
     Content_Ztt_tmp = 0;
     BinError_Ztt_tmp = 0;

     Content_Data[NewBin] = Content_Data_tmp;
     NewBinError_Data[NewBin] = sqrt(BinError_Data_tmp);
     Content_Data_tmp = 0;
     BinError_Data_tmp = 0;

     Content_QCD[NewBin] = Content_QCD_tmp;
     NewBinError_QCD[NewBin] = sqrt(BinError_QCD_tmp);
     Content_QCD_tmp = 0;
     BinError_QCD_tmp = 0;

     Content_ewbkg[NewBin] = Content_ewbkg_tmp;
     NewBinError_ewbkg[NewBin] = sqrt(BinError_ewbkg_tmp);
     Content_ewbkg_tmp = 0;
     BinError_ewbkg_tmp = 0;

     Content_VBF[NewBin] = Content_VBF_tmp;
     NewBinError_VBF[NewBin] = sqrt(BinError_VBF_tmp);
     Content_VBF_tmp = 0;
     BinError_VBF_tmp = 0;

     Content_ggH[NewBin] = Content_ggH_tmp;
     NewBinError_ggH[NewBin] = sqrt(BinError_ggH_tmp);
     Content_ggH_tmp = 0;
     BinError_ggH_tmp = 0;

     Content_VH[NewBin] = Content_VH_tmp;
     NewBinError_VH[NewBin] = sqrt(BinError_VH_tmp);
     Content_VH_tmp = 0;
     BinError_VH_tmp = 0;

   }
  
  

 }


 //________________________________________
 // Define new histograms
 // The number of bins is determined above 
 //________________________________________
 
 TH1D* NewZtautau = new TH1D("NewZtautau","NewZtautau",NewBin,0.,1.);
 TH1D* NewData = new TH1D("NewData","NewData",NewBin,0.,1.);
 TH1D* NewQCD = new TH1D("NewQCD","NewQCD",NewBin,0.,1.);
 TH1D* Newewbkg = new TH1D("Newewbkg","Newewbkg",NewBin,0.,1.);

 TH1D* NewAllbkg = new TH1D("NewAllbkg","NewAllbkg",NewBin,0.,1.);
 TH1D* NewEWQCDbkg = new TH1D("NewEWQCDbkg","NewEWQCDbkg",NewBin,0.,1.);

 TH1D* NewVBF = new TH1D("NewVBF","NewVBF",NewBin,0.,1.);
 TH1D* NewggH = new TH1D("NewggH","NewggH",NewBin,0.,1.);
 TH1D* NewVH = new TH1D("NewVH","NewVH",NewBin,0.,1.);


 //________________________________________
 // Fill new histograms
 //________________________________________
 

 for (int j=1; j<=NewBin; j++){
   cout<<"New Bins: "<<j<<" "<< Content_Ztt[j]<<" New error: "<< NewBinError_Ztt[j]<<endl;
   NewZtautau->SetBinContent(j, Content_Ztt[j]);
      NewZtautau->SetBinError(j, NewBinError_Ztt[j]);

   NewData->SetBinContent(j, Content_Data[j]);
      NewData->SetBinError(j, NewBinError_Data[j]);

   NewQCD->SetBinContent(j, Content_QCD[j]);
      NewQCD->SetBinError(j, NewBinError_QCD[j]);

   Newewbkg->SetBinContent(j, Content_ewbkg[j]);
      Newewbkg->SetBinError(j, NewBinError_ewbkg[j]);

   NewVBF->SetBinContent(j, Content_VBF[j]);
      NewVBF->SetBinError(j, NewBinError_VBF[j]);

   NewggH->SetBinContent(j, Content_ggH[j]);
      NewggH->SetBinError(j, NewBinError_ggH[j]);
   
   NewVH->SetBinContent(j, Content_VH[j]);
      NewVH->SetBinError(j, NewBinError_VH[j]);

 }

 //________________________________________
 //  Draw stack histograms
 //________________________________________
 
 
 TCanvas *c1 = new TCanvas("c1","c1");
 
 NewEWQCDbkg->Add(Newewbkg,1.);
 NewEWQCDbkg->Add(NewQCD,1.);
 NewEWQCDbkg->SetFillColor(38);
 
 NewAllbkg->Add(NewZtautau,1.);
 NewAllbkg->Add(NewEWQCDbkg,1.);
 NewAllbkg->SetFillColor(62);
 
 NewQCD->SetFillColor(9);
 NewAllbkg->Draw("hist");
 NewEWQCDbkg->Draw("hist");
 NewQCD->Draw("hist");
 
 NewAllbkg->Draw("hist");
 NewEWQCDbkg->Draw("histsame");
 NewQCD->Draw("histsame");
 
 NewData->SetMarkerStyle(8);
 NewData->SetMarkerSize(0.9);
 // NewData->Draw("same");  // 
 
 NewVBF->SetLineColor(2);
 NewggH->SetLineColor(6);
 NewVH->SetLineColor(3);
 
 NewVBF->SetLineWidth(3);
 NewggH->SetLineWidth(3);
 NewVH-> SetLineWidth(3);
 

  TLegend * leg = new TLegend(0.1,0.5,0.3,0.75);
  leg->AddEntry(NewVBF,"VBF 125");
  leg->AddEntry(NewggH,"GGF 125");
  leg->AddEntry(NewVH, "VH 125");

  leg->SetShadowColor(0);
  leg->SetLineColor(0);
  leg->SetFillColor(0);
  leg->Draw();


 /*
 //Check Histograms individually
// c1->Divide(2,1);
// c1->cd(1);
// hist_bdtVBF_ztautaunj_k->Draw();
// c1->cd(2);
// NewZtautau->Draw();

 TCanvas *c2 = new TCanvas("c2","c2");
 c2->Divide(2,1);
 c2->cd(1);
 hist_bdtVBF_data_k->Draw();
 c2->cd(2);
 NewData->Draw();

TCanvas *c3 = new TCanvas("c3","c3");
 c3->Divide(2,1);
 c3->cd(1);
 hist_QCD_k->Draw();
 c3->cd(2);
 NewQCD->Draw();

TCanvas *c4 = new TCanvas("c4","c4");
 c4->Divide(2,1);
 c4->cd(1);
 // hist_bdtVBF_ewbkg_k->Draw();
 hist_bdtVBF_VBFH125_k->Draw();
 c4->cd(2);
 // Newewbkg->Draw();
 NewVBF->Draw();
  */

//  NewData   ->Rebin(2);
//  NewQCD    ->Rebin(2);
//  NewAllbkg ->Rebin(2);
//  NewEWQCDbkg->Rebin(2);
//  NewZtautau->Rebin(2);
//  Newewbkg  ->Rebin(2);
// NewVBF    ->Rebin(2);
// NewggH    ->Rebin(2);
// NewVH     ->Rebin(2);

 f_out= TFile::Open("NewRebinnedHistograms.root","RECREATE");
 f_out->cd();
 c1->Write();// only backgrounds
 NewData->Write("hist_bdtVBF_data");
 NewQCD->Write("hist_QCD");
 NewZtautau->Write("hist_bdtVBF_ztautaunj");
 Newewbkg->Write("hist_bdtVBF_ewbkg");
 
 NewVBF->Write("hist_bdtVBF_VBFH125");
 NewggH->Write("hist_bdtVBF_ggH125");	
 NewVH->Write("hist_bdtVBF_VH125");
 
 f_out->Close(); 
 

 NewVBF->Scale(100.);
  NewggH->Scale(100.);
  NewVH->Scale(100.);

  NewData->Draw("same");
  NewVBF->Draw("histsame");
  NewggH->Draw("histsame");
  NewVH->Draw("histsame");
  

}
