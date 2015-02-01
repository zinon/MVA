
void RunMultiPlots(TString category, TString variable){

 	gSystem->AddIncludePath( " -I../../HelperClass/" );
    gSystem->Load( "../../HelperClass/HelperClass_cpp.so");

 	gSystem->AddIncludePath( " -I../../MonteCarloBank/" );
    gSystem->Load( "../../MonteCarloBank/MonteCarloBank_cpp.so");
	
	gSystem->Load( "MultiPlots_C.so" );
	MultiPlots(category, variable);
	gROOT->ProcessLine(".q");

}

