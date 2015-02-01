#include <iostream>
#include <TROOT.h>
#include <TSystem.h>
#include <TIterator.h>
#include <TKey.h>
#include <TString.h>
#include <TFile.h>
#include <TH1.h>

using namespace std;

TFile* m_inFile;
bool m_firstRegion;

// get a vector of bins where to rebin to get an uncertainty <= 5% per bin.
// starting from highest bin!
// the numbers give the lowest bin included in the new bin
// overflowbin+1 and underflow bins are returned as the first and last element in the vector, respectively.

vector<int> getRebinBins(TH1* histoBkg, double maxUnc = 0.05) {

  vector<int> bins;
  bins.clear();

  int nBins = histoBkg -> GetNbinsX();
  cout<<"Org Org bins: "<<histoBkg -> GetNbinsX()<<endl;
  int iBin = nBins + 1; // start with overflow bin
  bins.push_back(nBins + 2);

  while (iBin > 0) {

    double sumBkg = 0;
    double err2Bkg = 0;
    bool pass = false;

    while (!pass && iBin >= 0) {
      sumBkg += histoBkg -> GetBinContent(iBin);
      err2Bkg += pow(histoBkg -> GetBinError(iBin), 2);
      cout<<"SumBkg: "<<sumBkg<<" err2Bkg"<<err2Bkg<<endl;
      double err2RelBkg = 1;
      if (sumBkg != 0) {
        err2RelBkg = err2Bkg / pow(sumBkg, 2);
      }
      cout<<"err2RelBkg: "<<err2RelBkg<<" iBin "<<iBin<<endl;
      pass = sqrt(err2RelBkg) < maxUnc;
      iBin--;
    }
    cout<<"PASS!"<<endl;
    // remove last bin
    if (iBin + 1 == 0 && bins.size() > 1)
      bins.pop_back();
    bins.push_back(iBin + 1);
  }

  return bins;
}

// rebin histogram with provided vector of bins

void rebinHisto(TH1* histo, vector<int>* bins) {
  cout<<"Org bins: "<<bins -> size()<<endl;
  TH1* histoOld = (TH1*) histo -> Clone();
  histo -> Reset();
  int newNBins = bins -> size() - 1;
  histo -> SetBins(newNBins, -1, 1);

  for (int iBinNew = 1; iBinNew <= newNBins; iBinNew++) {
    int iBinLow = bins -> at(newNBins - iBinNew + 1); // vector is reverse-ordered
    int iBinHigh = bins -> at(newNBins - iBinNew) - 1;

    double err = 0;
    double sum = histoOld -> IntegralAndError(iBinLow, iBinHigh, err);
    histo -> SetBinContent(iBinNew, sum);
    histo -> SetBinError(iBinNew, err);
  }
  delete histoOld;
}

// go recursively through directories in source.
// rebin all histos found on the way and save same to gDirectory.

//void rebinAllHistos(TDirectory* source, vector<int>* bins, string* region) {
void rebinAllHistos(TDirectory* source, vector<int>* bins) {
  cout<<"Bins size in rebinAllHistos: "<<bins->size()<<endl;
  TDirectory* savdir = gDirectory;
  TDirectory* adir = savdir;
  //if (source != m_inFile) {
  //  if (m_firstRegion) {
  //    adir = savdir -> mkdir(source -> GetName());
  //  } else {
  //    savdir -> cd(source -> GetName());
  //    adir = gDirectory;
  //  }
  //}
  adir -> cd();
 

//loop on all entries of this directory
  TKey* key;
  TIter nextkey(source -> GetListOfKeys());
  while ((key = (TKey*) nextkey())) {
    TClass* cl = gROOT -> GetClass(key -> GetClassName());
    if (!cl) continue;
    if (cl -> InheritsFrom(TDirectory::Class())) {
           cout << "-> going into folder '" << key -> GetName() << "'" << endl;
      source -> cd(key -> GetName());
      TDirectory* subdir = gDirectory;
      adir -> cd();
      //      rebinAllHistos(subdir, bins, region);
      rebinAllHistos(subdir, bins);
      adir -> cd();
    } else if (cl -> InheritsFrom(TH1::Class())) {
      TString name = key -> GetName();
      TH1* histo = (TH1*) source -> Get(name);
      adir -> cd();
      //      if (name.Contains(region -> c_str())) {
      cout<<"Histo names "<<histo->GetName()<<" title: "<<histo->GetTitle()<<endl;
        rebinHisto(histo, bins);
        histo -> Write();
	//      }
    }
  }
  adir -> SaveSelf(kTRUE);
  savdir -> cd();
}

//TH1* readTotalBkg(TDirectory* source, string* region) {
TH1* readTotalBkg(TDirectory* source) {

  // define background histogram names

  vector<string> backgrounds;
  //  backgrounds.push_back("Diboson");
  //  //  backgrounds.push_back("WW");
  //  //  backgrounds.push_back("WZ");
  //  //  backgrounds.push_back("ZZ");
  //  backgrounds.push_back("Wb");
  //  backgrounds.push_back("Wc");
  //  backgrounds.push_back("Wcc");
  //  backgrounds.push_back("Wl");
  //  backgrounds.push_back("Zb");
  //  backgrounds.push_back("Zc");
  //  backgrounds.push_back("Zl");
  //  backgrounds.push_back("Top");
  //  //  backgrounds.push_back("ttbar");
  //  //  backgrounds.push_back("stop");
  //  backgrounds.push_back("multijet");
  //  backgrounds.push_back("bkg");

    backgrounds.push_back("hist_QCD");
    backgrounds.push_back("hist_bdtVBF_ztautaunj");
    backgrounds.push_back("hist_bdtVBF_ewbkg");



  TH1* histoBkg = 0;
  for (unsigned int iBkg = 0; iBkg < backgrounds.size(); iBkg++) {

    //    string histoName = backgrounds[iBkg] + *region;
    string histoName = backgrounds[iBkg];
    TObject* objHisto = source -> Get(histoName.c_str());
    if (objHisto == 0) {
      cout << "ERROR: background '" << backgrounds[iBkg] << "' not found!" << endl;
      gSystem -> Exit(1);
    }
    if (!histoBkg) {
      histoBkg = (TH1*) objHisto -> Clone("totalBkg");
      histoBkg -> SetDirectory(0);
    } else {
      histoBkg -> Add((TH1*) objHisto);
    }
  }

  //  histoBkg -> Draw();
  if (!histoBkg) {
    cout << "ERROR: total background not found!" << endl;
    gSystem -> Exit(1);
  }

  return histoBkg;

}

vector<string> findRegions(TDirectory* source, string dataName) {

  vector<string> regions;

  TKey* key;
  TIter nextkey(source -> GetListOfKeys());
  while ((key = (TKey*) nextkey())) {
    TClass* cl = gROOT -> GetClass(key -> GetClassName());
    if (!cl) continue;
    if (cl -> InheritsFrom(TH1::Class())) {
      TString name = key -> GetName();
      if (name.Contains(dataName.c_str())) {
        string region = name.ReplaceAll(dataName.c_str(), "").Data();
        //        cout << "-> found region '" << region << "'" << endl;
        regions.push_back(region);
      }
    }
  }

  if (regions.size() == 0) {
    cout << "ERROR: no data histogram found! maybe data name is not '" << dataName << "'" << endl;
    gSystem -> Exit(1);
  }
  return regions;
}

vector<string> findSubDirs(TDirectory* source, string subDirName) {

  vector<string> subDirs;

  TKey* key;
  TIter nextkey(source -> GetListOfKeys());
  while ((key = (TKey*) nextkey())) {
    TClass* cl = gROOT -> GetClass(key -> GetClassName());
    if (!cl) continue;
    if (cl -> InheritsFrom(TDirectory::Class())) {
      TString name = key -> GetName();
      if (name.Contains(subDirName)) {
        cout << "INFO: found subdirectory '" << name.Data() << "'" << endl;
        subDirs.push_back(name.Data());
      }
    }
  }

  if (subDirs.size() == 0) {
    cout << "INFO: no subdirectory found, using root directory" << endl;
    subDirs.push_back("");
  }
  return subDirs;
}

void transform(TString inFileName, double maxUnc = 0.05, TString outFileName = "") {

  string dataName = "data";
  //  string subDirName = "Lepton";
  string subDirName = "Lepton";

  m_inFile = new TFile(inFileName, "read");
  if (!m_inFile -> IsOpen()) {
    gSystem -> Exit(1);
  }

  if (outFileName == "") {
    outFileName = inFileName;
    outFileName.ReplaceAll(".root", ".transformed.root");
  }
  cout << "INFO: writing output to file '" << outFileName.Data() << "'" << endl;
  TFile* outFile = new TFile(outFileName, "recreate");

  cout << "INFO: looking for subdirectories containing '" << subDirName << "'" << endl;
  vector<string> subDirs = findSubDirs(m_inFile, subDirName);
  for (unsigned int iSubDir = 0; iSubDir < subDirs.size(); iSubDir++) {
    m_inFile -> cd(subDirs[iSubDir].c_str());
    TDirectory* sourceDir = gDirectory;
    cout << "INFO: looking for regions" << endl;
    vector<string> regions = findRegions(sourceDir, dataName);

    m_firstRegion = true;
    //    for (unsigned int iRegion = 0; iRegion < regions.size(); iRegion++) {
    //      cout << "INFO: reading total background for region '" << regions[iRegion] << "'" << endl;
      TH1* histoBkg = readTotalBkg(sourceDir);
      cout << "INFO: building transformation" << endl;
      vector<int> bins = getRebinBins(histoBkg, maxUnc);
      cout << "INFO: applying transformation" << endl;
      outFile -> cd();
      //      rebinAllHistos(sourceDir, &bins, &regions[iRegion]);
      rebinAllHistos(sourceDir, &bins);
      m_firstRegion = false;
      // }
  }

  cout << "Done!" << endl;
  gSystem -> Exit(0);

}
