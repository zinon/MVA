#include <HistoTransform.h>

// PRIVATE

// get a vector of bins where to rebin to get an uncertainty <= 5% per bin.
// starting from highest bin!
// the numbers give the lowest bin included in the new bin
// overflowbin+1 and underflow bins are returned as the first and last element in the vector, respectively.

vector<int> HistoTransform::getRebinBins(TH1* histoBkg, double maxUnc) {

  vector<int> bins;
  bins.clear();

  int nBins = histoBkg -> GetNbinsX();
  int iBin = nBins + 1; // start with overflow bin
  bins.push_back(nBins + 2);

  while (iBin > 0) {

    double sumBkg = 0;
    double err2Bkg = 0;
    bool pass = false;

    while (!pass && iBin >= 0) {
      sumBkg += histoBkg -> GetBinContent(iBin);
      err2Bkg += pow(histoBkg -> GetBinError(iBin), 2);

      double err2RelBkg = 1;
      if (sumBkg != 0) {
        err2RelBkg = err2Bkg / pow(sumBkg, 2);
      }

      pass = sqrt(err2RelBkg) < maxUnc;
      iBin--;
    }
    // remove last bin
    if (iBin + 1 == 0 && bins.size() > 1)
      bins.pop_back();
    bins.push_back(iBin + 1);
  }

  return bins;
}

// rebin histogram with provided vector of bins

void HistoTransform::rebinHisto(TH1* histo, vector<int>* bins) {

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
  double diff = 1 - histo -> GetSumOfWeights() / histoOld -> GetSumOfWeights();
  if (TMath::Abs(diff) > 1e-10) {
    cout << "WARNING: sizeable difference in tranformation of '" << histo -> GetName() << "' found. Sum of weights: (old-new)/old = " << diff << endl;
  }
  delete histoOld;
}

void HistoTransform::readRebinBins(SubDirectory* subDir) {
  for (unsigned int iKFold = 0; iKFold < subDir -> kFolds.size(); iKFold++) {
    KFold* kFold = subDir -> kFolds[iKFold];
    for (unsigned int iRegion = 0; iRegion < kFold -> regions.size(); iRegion++) {
      Region* region = kFold -> regions[iRegion];
      cout << "INFO: building transformation for region '" << region -> name << "':";
      region -> bins = getRebinBins(region -> bkg, region -> maxUnc);
      cout << " Nbins = " << region -> bins.size() - 1 << endl;
    }
  }
}

HistoTransform::KFold* HistoTransform::getKFold(SubDirectory* subDir, string histName) {
  for (unsigned int iKFold = 0; iKFold < subDir -> kFolds.size(); iKFold++) {
    KFold* kFold = subDir -> kFolds[iKFold];
    TString name = histName;
    if (name.Contains(kFold -> name.c_str()))
      return kFold;
  }
  //  cout << "WARNING: kFold for histo '" << histName << "' not found!" << endl;
  return 0;
}

HistoTransform::Region* HistoTransform::getRegion(SubDirectory* subDir, string histName) {
  KFold* kFold = getKFold(subDir, histName);
  if (!kFold)
    return 0;
  if (kFold -> regions.size() == 1)
    return kFold -> regions[0];
  TString name = histName;
  for (unsigned int iRegion = 0; iRegion < kFold -> regions.size(); iRegion++) {
    TString stringIofK = TString::Format("_%iof%i", iRegion, (int) kFold -> regions.size());
    if (name.Contains(stringIofK))
      return kFold -> regions[iRegion];
  }
  //  cout << "WARNING: region for histo '" << histName << "' not found!" << endl;
  return 0;
}

bool HistoTransform::isFirstOfKFold(KFold* kFold, string histName) {
  if (!kFold)
    return false;
  TString string0ofK = TString::Format("_0of%i", (int) kFold -> regions.size());
  TString name = histName.c_str();
  if (name.Contains(string0ofK))
    return true;
  return false;
}

// go recursively through directories in source.
// rebin all histos found on the way and save same to gDirectory.

void HistoTransform::rebinAllHistos(TDirectory* source, SubDirectory* subDir) {
  TDirectory* savdir = gDirectory;
  TDirectory* adir = savdir;
  if (source != m_inFile) {
    adir = savdir -> mkdir(source -> GetName());
  }
  adir -> cd();
  //loop on all entries of this directory
  TKey* key;
  TIter nextkey(source -> GetListOfKeys());
  while ((key = (TKey*) nextkey())) {
    TClass* cl = gROOT -> GetClass(key -> GetClassName());
    if (!cl) continue;
    if (cl -> InheritsFrom(TDirectory::Class())) {
      cout << "INFO: going into directory '" << key -> GetName() << "'" << endl;
      source -> cd(key -> GetName());
      TDirectory* subdir = gDirectory;
      adir -> cd();
      rebinAllHistos(subdir, subDir);
      adir -> cd();
    } else if (cl -> InheritsFrom(TH1::Class())) {
      TString name = key -> GetName();
      TH1* histo = (TH1*) source -> Get(name);
      adir -> cd();
      Region* region = getRegion(subDir, name.Data());
      if (region) {
        //cout << "INFO: applying transformation for region '" << region -> name << "' to histogram '" << name.Data() << "'" << endl;
        rebinHisto(histo, &region -> bins);
        histo -> Write();
      }
    }
  }
  adir -> SaveSelf(kTRUE);
  savdir -> cd();
}

void HistoTransform::mergeKFolds(TDirectory* source, SubDirectory* subDir) {
  TDirectory* savdir = gDirectory;
  TDirectory* adir = source;
  //    if (source != m_inFile) {
  //      adir = savdir -> mkdir(source -> GetName());
  //    }
  adir -> cd();
  //loop on all entries of this directory
  TKey* key;
  TIter nextkey(source -> GetListOfKeys());
  while ((key = (TKey*) nextkey())) {
    TClass* cl = gROOT -> GetClass(key -> GetClassName());
    if (!cl) continue;
    if (cl -> InheritsFrom(TDirectory::Class())) {
      cout << "INFO: going into directory '" << key -> GetName() << "'" << endl;
      source -> cd(key -> GetName());
      TDirectory* subdir = gDirectory;
      adir -> cd();
      mergeKFolds(subdir, subDir);
      adir -> cd();
    } else if (cl -> InheritsFrom(TH1::Class())) {
      TString name = key -> GetName();
      TH1* histo = (TH1*) source -> Get(name);
      adir -> cd();
      KFold* kFold = getKFold(subDir, name.Data());
      if (isFirstOfKFold(kFold, name.Data())) {
        TString string0ofK = TString::Format("_0of%i", (int) kFold -> regions.size());
        TString nameMerged = name;
        nameMerged.ReplaceAll(string0ofK, "");
        TH1* histoMerged = (TH1*) histo -> Clone(nameMerged);
        for (unsigned int iRegion = 1; iRegion < kFold -> regions.size(); iRegion++) {
          //region = kFold -> regions[iRegion];
          TString foldName = name;
          //foldName.ReplaceAll(nameFirstRegion, region -> name.c_str());
          TString stringIofK = TString::Format("_%iof%i", iRegion, (int) kFold -> regions.size());
          foldName.ReplaceAll(string0ofK, stringIofK);
          histo = (TH1*) source -> Get(foldName);
          histoMerged -> Add(histo);
          //cout << "added " << iRegion << endl;
        }
        histoMerged -> Write();
      }
    }
  }
  adir -> SaveSelf(kTRUE);
  savdir -> cd();
}

void HistoTransform::readTotalBkg(SubDirectory* subDir) {

  for (unsigned int iKFold = 0; iKFold < subDir -> kFolds.size(); iKFold++) {
    KFold* kFold = subDir -> kFolds[iKFold];
    TH1* kFoldBkg = 0;
    for (unsigned int iRegion = 0; iRegion < kFold -> regions.size(); iRegion++) {
      Region* region = kFold -> regions[iRegion];
      cout << "INFO: reading total background for region '" << region -> name << "'" << endl;
      TH1* histoBkg = 0;
      for (unsigned int iBkg = 0; iBkg < subDir -> backgrounds.size(); iBkg++) {

        string histoName = subDir -> backgrounds[iBkg] + region -> name;
        TObject* objHisto = subDir -> dir -> Get(histoName.c_str());
        if (objHisto == 0) {
          cout << "ERROR: background '" << subDir -> backgrounds[iBkg] << "' not found!" << endl;
          gSystem -> Exit(1);
        }
        if (!histoBkg) {
          histoBkg = (TH1*) objHisto -> Clone("totalBkg");
          histoBkg -> SetDirectory(0);
        } else {
          histoBkg -> Add((TH1*) objHisto);
        }
        if (!kFoldBkg) {
          kFoldBkg = (TH1*) objHisto -> Clone("kFoldBkg");
          kFoldBkg -> SetDirectory(0);
        } else {
          kFoldBkg -> Add((TH1*) objHisto);
        }
      }

      //  histoBkg -> Draw();
      if (!histoBkg) {
        cout << "ERROR: total background not found!" << endl;
        gSystem -> Exit(1);
      }
      region -> bkg = histoBkg;
    }
    if (doMergeKFolds && !doTransformBeforeMerging) {
      for (unsigned int iRegion = 0; iRegion < kFold -> regions.size(); iRegion++) {
        Region* region = kFold -> regions[iRegion];
        region -> bkg = kFoldBkg;
      }
    }
  }
}

void HistoTransform::findRegions(SubDirectory* subDir, string anyHistoName) {

  cout << "INFO: looking for regions in directory '" << subDir -> dir -> GetName() << "'" << endl;
  TKey* key;
  TIter nextkey(subDir -> dir -> GetListOfKeys());
  while ((key = (TKey*) nextkey())) {
    TClass* cl = gROOT -> GetClass(key -> GetClassName());
    if (!cl) continue;
    if (cl -> InheritsFrom(TH1::Class())) {
      TString name = key -> GetName();
      if (name.Contains(anyHistoName.c_str())) {
        //          Region* region = new Region();
        //          region -> name = name.ReplaceAll(anyHistoName.c_str(), "").Data();
        //          region -> maxUnc = 0.05;
        //          //        cout << "-> found region '" << region << "'" << endl;
        //          subDir -> regions.push_back(region);
        TString regionName = name;
        regionName.ReplaceAll(anyHistoName.c_str(), "").Data();
        addRegion(subDir, regionName.Data(), 0.05, 1);
      }
    }
  }

  if (subDir -> kFolds.size() == 0) {
    cout << "ERROR: no histogram found! maybe there is no histgram named '" << anyHistoName << "'" << endl;
    gSystem -> Exit(1);
  }
}

HistoTransform::SubDirectory* HistoTransform::findSubDirs(string subDirName, bool identical) {

  if (identical && subDirName == "") {
    SubDirectory* subDir = new SubDirectory();
    subDir -> dir = m_inFile;
    m_subDirs.push_back(subDir);
    return subDir;
  }

  TKey* key;
  TIter nextkey(m_inFile -> GetListOfKeys());
  while ((key = (TKey*) nextkey())) {
    TClass* cl = gROOT -> GetClass(key -> GetClassName());
    if (!cl) continue;
    if (cl -> InheritsFrom(TDirectory::Class())) {
      TString name = key -> GetName();
      if ((name.Contains(subDirName) && !identical) || name.EqualTo(subDirName)) {
        cout << "INFO: found subdirectory '" << name.Data() << "'" << endl;
        SubDirectory* subDir = new SubDirectory();
        m_inFile -> cd(name);
        subDir -> dir = gDirectory;
        m_subDirs.push_back(subDir);
        if (identical)
          return subDir;
        else
          addBackground(subDir, "bkg");
      }
    }
  }

  if (m_subDirs.size() == 0 && !identical) {
    cout << "INFO: no subdirectory found, using root directory" << endl;
    SubDirectory* subDir = new SubDirectory();
    subDir -> dir = m_inFile;
    m_subDirs.push_back(subDir);
    addBackground(subDir, "bkg");
    return subDir;
  }
  if (identical) {
    cout << "WARNING: subdirectory '" << subDirName << "' not found!" << endl;
  }
  return 0;
}

void HistoTransform::skimKFoldTrafos(SubDirectory * subDir) {
  cout << "INFO: skimming kFold transformations (for same number of bins in each fold)" << endl;
  for (unsigned int iKFold = 0; iKFold < subDir -> kFolds.size(); iKFold++) {
    KFold* kFold = subDir -> kFolds[iKFold];
    int nFold = kFold -> regions.size();
    if (nFold <= 1)
      continue;
    int minBins = -1;
    for (int iFold = 0; iFold < nFold; iFold++) {
      int nBins = kFold -> regions[iFold] -> bins.size() - 1;
      if (minBins > nBins || minBins == -1)
        minBins = nBins;
    }
    cout << "INFO: minimum number of bins for kFold '" << kFold -> name << "':" << minBins << endl;
    for (int iFold = 0; iFold < nFold; iFold++) {
      vector<int>* bins = &kFold -> regions[iFold] -> bins;
      while ((int) bins -> size() - 1 > minBins) {
        bins -> pop_back();
        bins -> pop_back();
        bins -> push_back(0);
      }
    }
  }
}

// PUBLIC

HistoTransform::SubDirectory* HistoTransform::addSubDirectory(string subDirName) {
  return findSubDirs(subDirName, true);
}

void HistoTransform::addBackground(SubDirectory* subDir, string bkgName) {
  subDir -> backgrounds.push_back(bkgName);
}

void HistoTransform::addRegion(SubDirectory* subDir, string regionName, float maxUnc, int nFold) {
  KFold* kFold = new KFold();
  for (int iFold = 0; iFold < nFold; iFold++) {
    Region* region = new Region();
    region -> name = regionName;
    if (nFold > 1)
      region -> name += TString::Format("_%iof%i", iFold, nFold);
    region -> maxUnc = maxUnc;
    kFold -> regions.push_back(region);
    kFold -> name = regionName;
    //subDir -> regions.push_back(region);
  }
  //if (nFold > 1)
  subDir -> kFolds.push_back(kFold);
}

void HistoTransform::run() {

  if (m_subDirs.size() == 0) {
    string subDirName = "Lepton";
    cout << "INFO: no subdirectories defined, looking for those containing '" << subDirName << "'" << endl;
    findSubDirs(subDirName, false);
  }

  for (unsigned int iSubDir = 0; iSubDir < m_subDirs.size(); iSubDir++) {
    SubDirectory* subDir = m_subDirs[iSubDir];
    if (subDir -> kFolds.size() == 0)
      findRegions(subDir, "data");
    readTotalBkg(subDir);
    readRebinBins(subDir);
    skimKFoldTrafos(subDir);
    cout << "INFO: applying transformations" << endl;
    m_outFile -> cd();
    rebinAllHistos(subDir -> dir, subDir);
    if (doMergeKFolds) {
      cout << "INFO: merging KFolds" << endl;
      m_outFile -> cd();
      mergeKFolds(m_outFile, subDir);
    }
  }
}
