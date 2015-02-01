{

 	gSystem->Exec("rm MultiPlots_C.so");


	gSystem->AddIncludePath( " -I../../HelperClass/" );
	gSystem->Load( "../../HelperClass/HelperClass_cpp.so");

	gSystem->AddIncludePath( " -I../../MonteCarloBank/" );
	gSystem->Load( "../../MonteCarloBank/MonteCarloBank_cpp.so");
	
	cout<<"Compile includes : "<<gSystem->GetIncludePath()<<endl;
	gSystem->CompileMacro( "MultiPlots.C","gk" );
  
	gROOT->ProcessLine(".q");
  
	cout<<"Compile done!"<<endl;


}