//how to use: time root RunTMVAClassificationHadHad4.C\(\"BDT\"\)

void RunTMVAClassificationHadHad5(TString classifier){

	TString s = gSystem->pwd();
 
	string path = s + "/";
	
	
 	//gSystem->Exec( ("cd "+path+"../../HelperClass/; root -q -b -l CompileHelperClass.C; ls; cd -").c_str() );
	gSystem->AddIncludePath( (" -I"+path+"../../HelperClass/").c_str() );
	gSystem->Load( (path+"../../HelperClass/HelperClass_cpp.so").c_str() );
	
	//gSystem->Exec(("cd "+path+"../../MonteCarloBank/; root -q -b -l CompileMonteCarloBank.C; ls; cd -").c_str());
	gSystem->AddIncludePath( (" -I"+path+"../../MonteCarloBank/").c_str() );
	gSystem->Load( (path+"../../MonteCarloBank/MonteCarloBank_cpp.so").c_str() );
	


	gSystem->CompileMacro( "TMVAClassificationHadHad5.C","gk" );
	
	TMVAClassificationHadHad5(classifier);

 	gROOT->ProcessLine(".q");

}