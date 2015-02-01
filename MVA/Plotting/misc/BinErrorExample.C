// Kyle Cranmer
// An explicit example for prescription to fill empty bins
// This example acts as a toy MC that fills histograms
// one can either calculate the required information from the MC samples
// or from the resulting histogram.  Both approaches are presented.

// The recommendation is an extension of section 3 from
// http://www.pp.rhul.ac.uk/~cowan/stat/notes/weights.pdf
// the key idea is we use the MC samples we have to calculate
// the quantity (\sigma^2 + \omega^2) in Eq. 15., where
// \sigma^2 is the variance of the weights and 
// \omega is the average weight.
// for empty bins, we make the conservative assumption that there
// could have been one MC event... so \nu/\omega = 1.
// And then (\sigma^2 + \omega^2) gives the variance for
// the background estimte (the weighted events in the bin).
// In the code below, avW2=(\sigma^2+\omega^2)~Variance, so 
// for the bin error we want sqrt(avW2).

void BinErrorExample(){

  TH1F* hist = new TH1F("hist","",10,0,1);
  hist->Sumw2();

  TFile *_file1 = TFile::Open("plot_BDTscore_2jet_125_SR_v8_30bins.root");
  TH1D* hist_bdtVBF_data_k;
  TH1D* hist_QCD_k;
  TH1D* hist_bdtVBF_ztautaunj_k;
  TH1D* hist_bdtVBF_ewbkg_k;
  TH1D* hist_bdtVBF_VBFH125_k;
  TH1D* hist_bdtVBF_ggH125_k;
  TH1D* hist_bdtVBF_ZH125_k;
  TH1D* hist_bdtVBF_WH125_k;
  TH1D* hist_bdtVBF_VH125_k;

 hist_bdtVBF_data_k     = (TH1D*)_file1->Get("hist_bdtVBF_data");
 hist_QCD_k             = (TH1D*)_file1->Get("hist_QCD");
 hist_bdtVBF_ztautaunj_k= (TH1D*)_file1->Get("hist_bdtVBF_ztautaunj");
 hist_bdtVBF_ewbkg_k=     (TH1D*)_file1->Get("hist_bdtVBF_ewbkg");
 hist_bdtVBF_VBFH125_k=   (TH1D*)_file1->Get("hist_bdtVBF_VBFH125");
 hist_bdtVBF_ggH125_k=    (TH1D*)_file1->Get("hist_bdtVBF_ggH125");
 hist_bdtVBF_VH125_k=     (TH1D*)_file1->Get("hist_bdtVBF_VH125");

 hist_bdtVBF_data_k->Sumw2();  
 hist_QCD_k->Sumw2();             
 hist_bdtVBF_ztautaunj_k->Sumw2();
 hist_bdtVBF_ewbkg_k->Sumw2();
 hist_bdtVBF_VBFH125_k->Sumw2();
 hist_bdtVBF_ggH125_k->Sumw2();
 hist_bdtVBF_VH125_k->Sumw2();   

  // Calculate samething from bins of histogram instead
  double sumW2TotBin_Z=0, avWeightBin_Z=0, avW2Bin_Z=0;
  double sumW2TotBin_QCD=0, avWeightBin_QCD=0, avW2Bin_QCD=0;
  double sumW2TotBin_EW=0, avWeightBin_EW=0, avW2Bin_EW=0;

  for(int j=1; j<=hist_bdtVBF_ztautaunj_k->GetNbinsX(); ++j){
    sumW2TotBin_Z   += pow( hist_bdtVBF_ztautaunj_k->GetBinError(j) , 2); // DON't forget to square!
    sumW2TotBin_QCD += pow( hist_QCD_k->GetBinError(j) , 2); // DON't forget to square!
    sumW2TotBin_EW  += pow( hist_bdtVBF_ewbkg_k->GetBinError(j) , 2); // DON't forget to square!
  }
  avWeightBin_Z += hist_bdtVBF_ztautaunj_k->GetSumOfWeights() / hist_bdtVBF_ztautaunj_k->GetEntries();
  avW2Bin_Z = sumW2TotBin_Z/hist_bdtVBF_ztautaunj_k->GetEntries();

  avWeightBin_QCD += hist_bdtVBF_QCD_k->GetSumOfWeights() / hist_bdtVBF_QCD_k->GetEntries();
  avW2Bin_QCD = sumW2TotBin_QCD/hist_bdtVBF_QCD_k->GetEntries();

  avWeightBin_EW += hist_bdtVBF_ewbkg_k->GetSumOfWeights() / hist_bdtVBF_ewbkg_k->GetEntries();
  avW2Bin_EW = sumW2TotBin_EW/hist_bdtVBF_ewbkg_k->GetEntries();

  // cout << "truth: mean, sigma, (sig^2+mean^2) " << meanWeight << ", "<< sigmaWeight << ", " << (meanWeight*meanWeight+sigmaWeight*sigmaWeight) << endl;

  //  cout << "MC event sum: avW, stdev, avW2 " << avWeight << ", "<< sqrt(sumW2Tot) << ", " << avW2 << endl;

  cout<<"For Ztautau:" <<endl;
  cout << "hist bin sum: avW, stdev, avW2 " << avWeightBin_Z << ", "<< sqrt(sumW2TotBin_Z) << ", " << avW2Bin_Z << endl;

  cout<<"For QCD:" <<endl;
  cout << "hist bin sum: avW, stdev, avW2 " << avWeightBin_QCD << ", "<< sqrt(sumW2TotBin_QCD) << ", " << avW2Bin_QCD << endl;

  cout<<"For EW:" <<endl;
  cout << "hist bin sum: avW, stdev, avW2 " << avWeightBin_EW << ", "<< sqrt(sumW2TotBin_EW) << ", " << avW2Bin_EW << endl;



  //Katy:  Check that the numbers make sense.  would I want to do this separately for each background? probably.

  // now fill empty bins with
  // binContent = avWeight     [or avWeightbin] 
  // binError = sqrt(avW2)     [or sqrt(avW2Bin)]
  

}
