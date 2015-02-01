

void RunTMVAOptimizationHadHad(TString classifier,  TString ntree1,  TString intree2, TString ileaf1, TString ileaf2){

	TString s = gSystem->pwd();
 
	string path = s + "/";
	
	
 	//gSystem->Exec( ("cd "+path+"../../HelperClass/; root -q -b -l CompileHelperClass.C; ls; cd -").c_str() );
	gSystem->AddIncludePath( (" -I"+path+"../../HelperClass/").c_str() );
	gSystem->Load( (path+"../../HelperClass/HelperClass_cpp.so").c_str() );
	
	//gSystem->Exec(("cd "+path+"../../MonteCarloBank/; root -q -b -l CompileMonteCarloBank.C; ls; cd -").c_str());
	gSystem->AddIncludePath( (" -I"+path+"../../MonteCarloBank/").c_str() );
	gSystem->Load( (path+"../../MonteCarloBank/MonteCarloBank_cpp.so").c_str() );
	


	//gSystem->CompileMacro( "TMVAOptimizationHadHad.C","gk" );
	gSystem->Load( "TMVAOptimizationHadHad_C.so" );
	
	TMVAOptimizationHadHad(classifier, ntree1, intree2, ileaf1, ileaf2);

 	gROOT->ProcessLine(".q");

}