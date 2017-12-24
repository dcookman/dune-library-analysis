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
  rn_times->SetTitle("Integrated light curves - normalised for 10k events");
  rn_times->GetXaxis()->SetTitle("Arrival time [#mus]");
  rn_times->GetYaxis()->SetTitle("Fraction of detected photons");
  rn_times->SetMinimum(0);

  rn_times->GetXaxis()->SetTitleSize(0.05);
  rn_times->GetXaxis()->SetTitleOffset(0.85);
  rn_times->GetYaxis()->SetTitleSize(0.05);
  rn_times->GetYaxis()->SetTitleOffset(0.85);

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



  // ---------------- SCALING THE HISTOGRAMS--------------------- //
  //NB the integral will just give the number of photons from that tree
  double sn_integral = sn_times->Integral();
  double rn_integral = rn_times->Integral();

  //scale the histograms to 1
  // => 1 is now the maximum thus each bin now represents the fraction of total light within that time-frame
  rn_times->Scale(1./rn_integral);
  sn_times->Scale(1./sn_integral);
  
  double sn_entries_new = sn_times->GetEntries();
  double rn_entries_new = rn_times->GetEntries();

  double sn_integral_new = sn_times->Integral();
  double rn_integral_new = rn_times->Integral();
  
  cout << "SN integral new: " << sn_integral_new << "\t";
  cout << "SN entries new: " << sn_entries_new << "\n";
  cout << "Rn integral new: " << rn_integral_new << "\t";
  cout << "Rn entries new: " << rn_entries_new << "\n";

  

  ////--------------------- PSD Analysis -----------------------------
  
  int rn_bins = rn_times->GetSize() - 2; // -2 two as it includes "undeflow" and "overflow" - Ask Andrzej if you're unsure about this
  int sn_bins = sn_times->GetSize() - 2;

  cout << "rn_bins: " << rn_bins << endl;
  cout << "sn_bins: " << sn_bins << endl;

  int bins;
  if(rn_bins == sn_bins){ bins = rn_bins; }
  else { cerr << "ERROR: Histograms do not have the same number of bins" << endl; }

  // We want to do a cumulative sum over all of the bins in order to see what fraction of light arrives at each time interval (bin)
  double sum_rn = 0;
  double sum_sn = 0;
  int count = 0;
  double temp_sn, temp_rn;
  for(int i = 0; i < bins; i++) {
    temp_sn = sn_times->GetBinContent(i); // Will return the fraction of light arriving within that time interval (bin)
    temp_rn = rn_times->GetBinContent(i);

    sum_sn += temp_sn;
    sum_rn += temp_rn;

    sn_times->SetBinContent(i,sum_sn); // now set the bin content to be the cumulative sum AT THAT POINT
    rn_times->SetBinContent(i,sum_rn);
    count++;
  }

  

  // FINDING THE POINT AT WHICH THE INTEGRATED TIMING CURVES ARE MOST DIFFERENT
  //The code below basically runs through each bin an finds the difference between the cumulative sums. It will find at which bin (i.e. time interval) the curves are most different from one another - this is a good place to define the cut off time.
  double current_diff =0;
  double max_diff = 0;
  int max_diff_bin = 0;
  for(int i = 0; i < bins; i++) {
    current_diff = rn_times->GetBinContent(i) - sn_times->GetBinContent(i);
    if(current_diff <  max_diff){ continue; } 
    else {
      max_diff = current_diff;
      max_diff_bin = i;
    }  
  }

  double max_diff_time = rn_times->GetBinCenter(max_diff_bin);
  cout << "Value of t where difference is biggest = " << max_diff_time << " mu_s." << endl;
  cout << "This is equivalent to: " << max_diff_time * 1000 << " ns." << endl;
  
  
  
}

