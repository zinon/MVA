// gStyle->SetPalette(1, 0)
// int maxB = hSep->GetMaximumBin(); 
// int minB = hSep->GetMinimumBin();
// double zmin = hSep->GetBinContent(minB); double zmax =  hSep->GetBinContent(maxB);
// hSep->GetZaxis()->SetRangeUser(zmin, zmax);
// hSep->SetContour(2000);
// hSep->Draw("colz");

void GetMax(TH2D *h, double &xmax, int &imax, int &jmax);
double GetMinVal(TH2D *h);

void DrawOptimization()
{

	TFile *fout = new TFile ("scan_2jet_v8.root", "recreate");

	TH2D *hSig = new TH2D("hSig", "", 2000, 0, 2000, 2000, 0, 2000);
	TH2D *hSep = new TH2D("hSep", "", 2000, 0, 2000, 2000, 0, 2000); 
	TH2D *hRoc = new TH2D("hRoc", "", 2000, 0, 2000, 2000, 0, 2000);
	
	for(int i = 1; i <= 2000; i = i+2){
		for(int j = 5; j <= 2000; j = j+200){
			string x = GetStringFromInt(i);
			string y = GetStringFromInt(i+1);
			string z = GetStringFromInt(j);
			string w = GetStringFromInt(j+195);
			string s = "OptScan/TMVAClassificationHadHad_BDT_PartTrainedA_2jet_125_v8_opt_slice_"+x+"_"+y+"_"+z+"_"+w+".root";
			
	

			if (gSystem->AccessPathName(s.c_str(), kFileExists)) continue;
			
			Long_t id,size,flags,mt;
			gSystem->GetPathInfo(s.c_str() ,&id,&size,&flags,&mt);
			if( size < 100000 ) continue;
			
			TFile f( s.c_str() );
			if(f.IsZombie() ) continue;

			//cout<<"Got file : "<<s<<endl;
			TH2D *h1 = (TH2D *)f.Get("hSig");
			hSig->Add(h1, 1.0);
			
			TH2D *h2 = (TH2D *)f.Get("hSep");
			hSep->Add(h2, 1.0);
			
			TH2D *h3 = (TH2D *)f.Get("hRoc");
			hRoc->Add(h3, 1.0);
		}
	}
	
	
	double Sig; int iSig, jSig; GetMax(hSig, Sig, iSig, jSig);
	double Sep; int iSep, jSep; GetMax(hSep, Sep, iSep, jSep);
	double Roc; int iRoc, jRoc; GetMax(hRoc, Roc, iRoc, jRoc);
	
	

	TCanvas *c1 = new TCanvas ("cSig", "");
	c1->cd();
	hSig->Draw("colz");
	double x1 = hSig->GetXaxis()->GetBinLowEdge(iSig);
	double y1 = hSig->GetYaxis()->GetBinLowEdge(jSig);
	cout<<"Sig max "<<Sig<<" ("<<x1<<", "<<y1<<")"<<endl;
	cout<<"sig min val "<<GetMinVal(hSig)<<endl;
	TEllipse *el1 = new TEllipse (x1, y1, 25, 25);
	el1->SetLineWidth(2);
	el1->SetFillStyle(0);
	el1->Draw();

	TCanvas *c2 = new TCanvas ("cSep", "");
	c2->cd();
	hSep->Draw("colz");
	double x2 = hSep->GetXaxis()->GetBinLowEdge(iSep);
	double y2 = hSep->GetYaxis()->GetBinLowEdge(jSep);
	cout<<"Sep max "<<Sep<<" ("<<x2<<", "<<y2<<")"<<endl;
	cout<<"Sep min val "<<GetMinVal(hSep)<<endl;
	TEllipse *el2 = new TEllipse (x2, y2, 25, 25);
	el2->SetLineWidth(2);
	el2->SetFillStyle(0);
	el2->Draw();
	
	TCanvas *c3 = new TCanvas ("cRoc", "");
	c3->cd();
	hRoc->Draw("colz");
	double x3 = hRoc->GetXaxis()->GetBinLowEdge(iRoc);
	double y3 = hRoc->GetYaxis()->GetBinLowEdge(jRoc);
	cout<<"Roc max "<<Roc<<" ("<<x3<<", "<<y3<<")"<<endl;
	cout<<"Roc min val "<<GetMinVal(hRoc)<<endl;
	TEllipse *el3 = new TEllipse (x3, y3, 25, 25);
	el3->SetLineWidth(2);
	el3->SetFillStyle(0);
	el3->Draw();
	

	fout->cd();
	hSig->Write();
	hSep->Write();
	hRoc->Write();
	el1->Write();
	el2->Write();
 	el3->Write();
	c1->Write();
	c2->Write();
	c3->Write();
	fout->Close();
}

void GetMax(TH2D *h, double &xmax, int &imax, int &jmax){
	
	xmax = 0; imax = 0; jmax = 0;
	for(int i = 1; i <= h->GetNbinsX(); i++ ){
		for(int j = 1; j <= h->GetNbinsY(); j++ ){
			double bc = h->GetBinContent(i,j);
			if(bc > xmax) { xmax = bc; imax = i; jmax = j;}
		}
	}

	
}

double GetMinVal(TH2D *h){
	double minV = 1e6;
	
	for(int i = 1; i <= h->GetNbinsX(); i++ ){ for(int j = 1; j <= h->GetNbinsY(); j++ ){ double bc = h->GetBinContent(i,j);
			if(bc < minV && bc > 0.0) { minV = bc; }
		}
	}
	
	return minV;
}

string GetStringFromInt(int n){ std::ostringstream stm; stm << n; return stm.str(); }

