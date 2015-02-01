
#include <map>

void LoopThroughTrees(){
  
  gSystem->Load("../../HelperClass/HelperClass_cpp.so");
  gSystem->Load("../../MonteCarloBank/MonteCarloBank_cpp.so");
  
  
  int     Hmass                           = 125;
  string  category                        = "2jet";
  string  region                          = "all";//all now means MMC >80
  string  version                         = "v8";
  string  purpose                         = "MVA";
  string  treename                        = "mva";
  
  
  HelperClass hc;
  hc.SetTreeName(treename);
  hc.SetVersion(version);
  hc.SetPath("../../Ntuples/");

  MonteCarloBank mcb;
  
  //Get the Data trees:
  TTree *tdata = hc.GetTreeData();
  cout<<"\ndata events "<<tdata->GetEntries()<<endl;
  
  ///list of MC samples
  cout<<"\ncreating the MC list ..."<<endl;
  vector<int> RunsVector = hc.GetRunsVector(Hmass);
  
  std::map<std::string,int> Use;

  ///get MC trees
  map<int, TTree *> tmap;
  for(vector<int>::iterator it=RunsVector.begin(); it != RunsVector.end(); it++){
   if( *it >= 800000) continue;
    tmap.insert ( pair<int, TTree *>(*it,  hc.GetTreeMC(*it) ) );
//    cout<<"mc "<<*it<<" entries "<<tmap[*it]->GetEntries()<<endl;
  }

  TCut cutBackgroundTrain = hc.GetCut(category, "bkg",    purpose, region) ;
  TCut cutBackgroundTest  = hc.GetCut(category, "bkg",    purpose, region) ;
  
  
  
  ///Bkg    
  for(map<int, TTree *>::iterator itt = tmap.begin(); itt != tmap.end(); itt++){
    cout<<"BKG"<<endl;
  
      if( hc.Is("Ztautau", itt->first) ) {
	cout<<"Adding bkg "<<itt->first<<" in factory"<<endl;
	//	factory->AddTree (it->second, "Background", mcb.Get_Norm(it->first), cutBackgroundTrain, "train") ;
	//	factory->AddTree (it->second, "Background", mcb.Get_Norm(it->first), cutBackgroundTest, "test");
      }
  
      if( hc.Is("Electroweak", itt->first) ) {
	cout<<"Adding bkg "<<itt->first<<" in factory"<<endl;
	//	factory->AddTree (it->second, "Background", mcb.Get_Norm(it->first), cutBackgroundTrain, "train") ;
	//	factory->AddTree (it->second, "Background", mcb.Get_Norm(it->first), cutBackgroundTest, "test");
      }
  
    
  }
  
  
}
