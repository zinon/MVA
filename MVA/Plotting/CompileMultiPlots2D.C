{

 	gSystem->Exec("rm MultiPlots2D_C.so");


	gSystem->AddIncludePath( " -I../../HelperClass/" );
	gSystem->Load( "../../HelperClass/HelperClass_cpp.so");

	gSystem->AddIncludePath( " -I../../MonteCarloBank/" );
	gSystem->Load( "../../MonteCarloBank/MonteCarloBank_cpp.so");
	
	cout<<"Compile includes : "<<gSystem->GetIncludePath()<<endl;
	gSystem->CompileMacro( "MultiPlots2D.C","gk" );
  
	gROOT->ProcessLine(".q");
  
	cout<<"Compile done!"<<endl;


}