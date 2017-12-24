// Read in the .root event file, take the data and plot sensible histograms regarding the detected photons. 

{

  //////////////////////////////////////////
  /////// DEFINE FILES TO BE ANALYSED //////
  //////////////////////////////////////////
  const char* filename1 = "usefulDataFiles/10k_sn_randompos2.root";
  TFile * infile1=new TFile(filename1,"READ"); // define the input file
  TTree * data_tree1=(TTree *)infile1->Get("data_tree"); //directs towards root tree inside the input file

  const char* filename2 = "usefulDataFiles/10k_rn_randompos2.root";
  TFile * infile2=new TFile(filename2,"READ");
  TTree * data_tree2=(TTree *)infile2->Get("data_tree"); 
  

 //////////////////////////////////////////////////////////////////////////////////
 ///// **** Histograms of the photon arrival times from the input files **** //////   
 //////////////////////////////////////////////////////////////////////////////////

  //////////////////////
  ////Define Histograms
  //////////////////////
  TH1F *sn_times = new TH1F("sn_times","Photon arrival times 10k events",2500,0,5); // An example: TH1F(...,500,0,5) => 10ns bins between 0 and 5 microseconds
  TH1F *rn_times = new TH1F("rn_times","Photon arrival times 10k events",2500,0,5);

  //Draw on the histrogram using the data from the tree
  data_tree1->Draw("data_time >> sn_times");
  data_tree2->Draw("data_time >> rn_times");

  //////////////////////////
  //// Photon timing curves
  //////////////////////////

//Make a canvas
  TCanvas *c1 = new TCanvas("c1","c1");
  //Labelling
  rn_times->SetTitle("Photon arrival times - 10k events");
  rn_times->GetXaxis()->SetTitle("Arrival time [#mus]");
  rn_times->GetYaxis()->SetTitle("Fraction of detected photons");
  rn_times->SetMinimum(0);

  rn_times->GetXaxis()->SetTitleSize(0.05);
  rn_times->GetXaxis()->SetTitleOffset(0.85);
  rn_times->GetYaxis()->SetTitleSize(0.05);
  rn_times->GetYaxis()->SetTitleOffset(0.85);

  c1->SetLogy();

  //set line colors
  sn_times->SetLineColor(1);
  rn_times->SetLineColor(2);


  gStyle->SetOptStat(0);
  //Draw the histogram
  rn_times->Draw();
  sn_times->Draw("SAME"); //draws it onto the same canvas
 
  
  //add a legend
  TLegend* leg2 = new TLegend(0.2, 0.2, .8, .8);
  leg2->AddEntry("sn_times", "e^{-} induced scintillation");
  leg2->AddEntry("rn_times", "#alpha induced scintillation");
  leg2->Draw(); 
  
  
}

