#include <iostream>
#include <TROOT.h>
#include <TSystem.h>
#include <TIterator.h>
#include <TKey.h>
#include <TString.h>
#include <TFile.h>
#include <TH1.h>
#include <vector>

using namespace std;

class HistoTransform {
private:

  TString m_inFileName;
  TString m_outFileName;
  TFile* m_inFile;
  TFile* m_outFile;

  typedef struct {
    string name;
    float maxUnc;
    TH1* bkg;
    vector<int> bins;
  } Region;

  typedef struct {
    string name;
    int nFold;
    vector<Region*> regions;
  } KFold;

  typedef struct {
    TDirectory* dir;
    vector<string> backgrounds;
    //vector<Region*> regions;
    vector<KFold*> kFolds;
  } SubDirectory;

  vector<SubDirectory*> m_subDirs;

  vector<int> getRebinBins(TH1* histoBkg, double maxUnc = 0.05);
  KFold* getKFold(SubDirectory* subDir, string histName);
  Region* getRegion(SubDirectory* subDir, string histName);
  bool isFirstOfKFold(KFold* kFold, string histName);
  void rebinHisto(TH1* histo, vector<int>* bins);
  void readRebinBins(SubDirectory* subDir);
  void rebinAllHistos(TDirectory* source, SubDirectory* subDir);
  void mergeKFolds(TDirectory* source, SubDirectory* subDir);
  void readTotalBkg(SubDirectory* source);
  void findRegions(SubDirectory* subDir, string anyHistoName);
  SubDirectory* findSubDirs(string subDirName, bool identical = false);
  void skimKFoldTrafos(SubDirectory * subDir);


public:

  bool doMergeKFolds;
  bool doTransformBeforeMerging;

  SubDirectory* addSubDirectory(string subDirName);
  void addBackground(SubDirectory* subDir, string bkgName);
  void addRegion(SubDirectory* subDir, string regionName, float maxUnc = 0.05, int nFold = 1);
  void run();

  HistoTransform(TString inFileName, TString outFileName = "") {

    m_inFileName = inFileName;
    m_outFileName = outFileName;

    cout << "INFO: reading from file '" << m_inFileName.Data() << "'" << endl;
    m_inFile = new TFile(m_inFileName, "read");
    if (!m_inFile -> IsOpen()) {
      gSystem -> Exit(1);
    }

    if (m_outFileName == "") {
      m_outFileName = m_inFileName;
      m_outFileName.ReplaceAll(".root", ".transformed.root");
    }
    cout << "INFO: writing to file '" << m_outFileName.Data() << "'" << endl;
    m_outFile = new TFile(m_outFileName, "recreate");

    doMergeKFolds = true;
    doTransformBeforeMerging = false;

  }

};


