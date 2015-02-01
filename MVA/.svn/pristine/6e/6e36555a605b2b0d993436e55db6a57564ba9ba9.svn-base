
void RunMultiPlots2D(TString category, TString variable1, TString variable2, TString counter){

 	gSystem->AddIncludePath( " -I../../HelperClass/" );
    gSystem->Load( "../../HelperClass/HelperClass_cpp.so");

 	gSystem->AddIncludePath( " -I../../MonteCarloBank/" );
    gSystem->Load( "../../MonteCarloBank/MonteCarloBank_cpp.so");
	
	gSystem->Load( "MultiPlots2D_C.so" );
	MultiPlots2D(category, variable1, variable2, counter);
	gROOT->ProcessLine(".q");

}

