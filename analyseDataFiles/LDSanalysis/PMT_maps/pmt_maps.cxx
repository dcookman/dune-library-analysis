#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TKey.h"
#include "TH1D.h"
#include "TH2.h"
#include "TH3D.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TMath.h"
#include "TVector3.h"
#include "TRandom3.h"
#include "TGraph.h"
#include "THStack.h"
#include "TColor.h"
#include "TLegend.h"
#include "TMarker.h"

//using namespace std;

//int main()
void pmt_maps()
{

	TH2D * h_pmt_plane0 = new TH2D("h_pmt_plane0", " ", 14,0, 500, 11, -200, 200);
	TH2D * h_pmt_plane02 = new TH2D("h_pmt_plane0", " ", 14,0, 500, 11, -200, 200);
	TH2D * h_pmt_plane_ar0 = new TH2D("h_pmt_plane0", " ", 14,0, 500, 11, -200, 200);

	// Reading out positions of PMTs from txt file *****
	vector<vector<double> > myfile_data;
	ifstream myfile;
	myfile.open("../posPMTs_setup1.txt");
	if(myfile.is_open()) {cout << "File opened successfully" << endl; }
	while(!myfile.eof())
	{
		double num_pmt, x_pmt, y_pmt, z_pmt;
		if(myfile >> num_pmt >> x_pmt >> y_pmt >> z_pmt)
		{
			vector<double> line_data({num_pmt, x_pmt, y_pmt, z_pmt});
			myfile_data.push_back(line_data);
		}
		else{break; }
	}
	myfile.close();

	string datafile1 = "1_15MeVSn_middle_100nsCut.root"; // this is c1_n3
	string datafile2 = "1_QRn_middle_100nsCut.root"; // this is c1
	string datafile3 = "1_5MeVSn_middle_100nsCut.root"; // this is c1_n2

	TFile *f1 = nullptr;
	TFile *f2 = nullptr;
	TFile *f3 = nullptr;

	f1 = TFile::Open(datafile1.c_str());
	f2 = TFile::Open(datafile2.c_str());
	f3 = TFile::Open(datafile3.c_str());
	TTree *data_tree1 = nullptr;
	data_tree1 =  (TTree*)f1->Get("data_tree");
	int c3photons = data_tree1->GetEntries();
	TTree *data_tree2 = nullptr;
	data_tree2 = (TTree*)f2->Get("data_tree");
	int c1photons = data_tree2->GetEntries();
	TTree *data_tree3 = nullptr;
	data_tree3 = (TTree*)f3->Get("data_tree");
	int c2photons = data_tree3->GetEntries();


	//      double pmt_hits1;
	//      double pmt_hits2;
	//      double pmt_hits3;

	int pmt_hits1;
	int pmt_hits2;
	int pmt_hits3;

	data_tree1->SetBranchAddress("data_pmt", &pmt_hits1);
	data_tree2->SetBranchAddress("data_pmt", &pmt_hits2);
	data_tree3->SetBranchAddress("data_pmt", &pmt_hits3);

	int entries1 = 0;
	int entries2 = 0;
	int entries3 = 0;
	entries1 = data_tree1->GetEntries();
	entries2 = data_tree2->GetEntries();
	entries3 = data_tree3->GetEntries();

	for(int i = 0; i < entries1; i++)
	{
		data_tree1->GetEntry(i);
		h_pmt_plane_ar0->Fill(myfile_data.at(pmt_hits1).at(3), myfile_data.at(pmt_hits1).at(2));
	}
	for(int i = 0; i < entries2; i++)
	{
		data_tree2->GetEntry(i);
		h_pmt_plane0->Fill(myfile_data.at(pmt_hits2).at(3), myfile_data.at(pmt_hits2).at(2));
	}
	for(int i = 0; i < entries3; i++)
	{
		data_tree3->GetEntry(i);
		h_pmt_plane02->Fill(myfile_data.at(pmt_hits3).at(3), myfile_data.at(pmt_hits3).at(2));
	}

	double min_x = 0;
	double max_x = 0;

	//------Modifying colour scale ---------------------------
	double temp6 = h_pmt_plane0->GetBinContent(h_pmt_plane0->GetMaximumBin());
	double temp7 = h_pmt_plane_ar0->GetBinContent(h_pmt_plane_ar0->GetMaximumBin());
	double temp8 = h_pmt_plane02->GetBinContent(h_pmt_plane02->GetMaximumBin());
	double max2;
	if(temp6 > temp7 && temp6 > temp8) {max2 = temp6; }
	if(temp7 > temp6 && temp7 > temp8) {max2 = temp7; }
	if(temp8 > temp6 && temp8 > temp7) {max2 = temp8; }

	temp6 = 0; temp7 = 0; temp8 = 0;

	temp6 = h_pmt_plane0->GetBinContent(h_pmt_plane0->GetMinimumBin());
	temp7 = h_pmt_plane_ar0->GetBinContent(h_pmt_plane_ar0->GetMinimumBin());
	temp8 = h_pmt_plane02->GetBinContent(h_pmt_plane02->GetMinimumBin());
	double min2;
	if(temp6 < temp7 && temp6 < temp8) {min2 = temp6; }
	if(temp7 < temp6 && temp7 < temp8) {min2 = temp7; }
	if(temp8 < temp6 && temp8 < temp7) {min2 = temp8; }

	min_x = 0.95*min2;
	max_x = 1.15*max2;

	const Int_t pLevels = 99;
	Double_t __levels[pLevels];

	for(Int_t i = 1; i < pLevels; i++)
	{
		__levels[i] = min_x + (max_x-min_x)/(pLevels-1)*(i);
	}

	__levels[0]=0.0001;
	h_pmt_plane0->SetContour((sizeof(__levels)/sizeof(Double_t)),__levels);
	h_pmt_plane_ar0->SetContour((sizeof(__levels)/sizeof(Double_t)),__levels);
	h_pmt_plane02->SetContour((sizeof(__levels)/sizeof(Double_t)),__levels);

	gStyle->SetPalette(kBird);
	//--------------------------------------------------------

	TCanvas *can01 = new TCanvas();
	can01->cd();

	Int_t cj; //for color index setting
	TColor *colorz;//for color definition with alpha
	cj = TColor::GetColor("#000099");
	h_pmt_plane0->SetLineColor(cj);
	h_pmt_plane0->GetZaxis()->SetRangeUser(min_x,max_x);
	h_pmt_plane0->GetXaxis()->SetTitleSize(0.045);
	h_pmt_plane0->GetYaxis()->SetTitleSize(0.045);
	h_pmt_plane0->GetXaxis()->SetTitle("z [cm]");
	h_pmt_plane0->GetYaxis()->SetTitle("y [cm]");
	h_pmt_plane0->SetTitle("PMT Signal Map - 5.590 MeV Radon decay - 100ns cut");
	h_pmt_plane0->SetStats(kFALSE);
	h_pmt_plane0->Draw("colz");

	TCanvas *can02 = new TCanvas();
	can02->cd();

	h_pmt_plane02->SetLineColor(cj);
	h_pmt_plane02->GetZaxis()->SetRangeUser(min_x,max_x);
	h_pmt_plane02->GetXaxis()->SetTitleSize(0.045);
	h_pmt_plane02->GetYaxis()->SetTitleSize(0.045);
	h_pmt_plane02->GetXaxis()->SetTitle("z [cm]");
	h_pmt_plane02->GetYaxis()->SetTitle("y [cm]");
	h_pmt_plane02->SetTitle("PMT Signal Map - 5 MeV Supernova - 100ns cut");
	h_pmt_plane02->SetStats(kFALSE);
	h_pmt_plane02->Draw("colz");

	TCanvas *can03 = new TCanvas();
	can03->cd();

	h_pmt_plane_ar0->SetLineColor(cj);
	h_pmt_plane_ar0->GetZaxis()->SetRangeUser(min_x,max_x);
	h_pmt_plane_ar0->GetXaxis()->SetTitleSize(0.045);
	h_pmt_plane_ar0->GetYaxis()->SetTitleSize(0.045);
	h_pmt_plane_ar0->GetXaxis()->SetTitle("z [cm]");
	h_pmt_plane_ar0->GetYaxis()->SetTitle("y [cm]");
	h_pmt_plane_ar0->SetTitle("PMT Signal Map - 15 MeV Supernova - 100ns cut");
	h_pmt_plane_ar0->SetStats(kFALSE);
	h_pmt_plane_ar0->Draw("colz");

	//return 0;

}//end main
