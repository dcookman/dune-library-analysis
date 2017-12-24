// Reads in the .root event file, and plots a timing curve with the photon arrival times (stored in data_time)
// Fits a double exponential function to the curve 


// Important to note
  // coordinates of dimensions of SBND LAr tank (all in cm):
  // x = [ 0 -> 200 ] IN COLTONS CODE for 1 TPC. IRL active region x for 2 TPCs x_active = [-202.5 -> -2.5 ] & [2.5 -> 200] where cathode [-2.5 -> 2.5]
  // y = [ -200 -> 200 ] middle at 0
  // z = [ 0 -> 500 ]  where 0 = front.

{

  filename = "usefulDataFiles/10k_rn_randompos2.root";

  TFile * infile=new TFile(filename,"READ"); // define the input file

  TTree * data_tree=(TTree *)infile->Get("data_tree"); //directs towards to root tree inside the input file

  //Using the TF1::Fit method:
  //"expo" is an exponential with 2 parameters - f(x) = exp(p0 + p1*x)
  
  TF1 *expfn = new TF1("expfn","expo(0)+expo(2)",0,5.5);
  //expfn->SetParameters(10,-25,3,-6.7);
  expfn->SetParameter(1,-160);
  expfn->SetParameter(3,-0.7);
  expfn->SetParLimits(1,-160,-10);
  expfn->SetParLimits(3,-10,0);


  //Set parameter names
  expfn->SetParName(0,"C_{1}");
  expfn->SetParName(1,"-1/#tau_{f}");
  expfn->SetParName(2,"C_{2}");
  expfn->SetParName(3,"-1/#tau_{s}");
  
 //////////////////////////////////////////////////////////////////////////////////
 //////////////// ***** Histogram for photon arrival times ***** //////////////////   
 //////////////////////////////////////////////////////////////////////////////////

//Make a canvas
  TCanvas *c1 = new TCanvas("c1","c1");
  TH1F *times = new TH1F("times","Photon arrival times",500,0,6);

  //Labelling
  times->GetXaxis()->SetTitle("Arrival time [#mus]");
  times->GetYaxis()->SetTitle("Number of photons");
  times->SetMinimum(0.1);

  times->GetXaxis()->SetTitleSize(0.05);
  times->GetXaxis()->SetTitleOffset(0.85);
  times->GetYaxis()->SetTitleSize(0.05);
  times->GetYaxis()->SetTitleOffset(0.85);

  //set line colors
  times->SetLineColor(1);

  //Draw on the histrogram using the data from the tree
  data_tree->Draw("data_time >> times");

  
  double maxBin = times->GetMaximumBin();
  double maxBinValue = times->GetBinCenter(maxBin);
  double minRange = maxBinValue + 0.001; //add a nanosecond to be safe
  times->Fit("expfn","BR+","",minRange,6); //fits the function to the histogram
  gStyle->SetOptFit(111);
  
  
  //Draw the histogram
  times->Draw();
  
  //gStyle->SetOptStats(11); // doesn't print the next canvas if this is used...

  
    TLegend* leg = new TLegend(0.2, 0.2, .8, .8);
  leg->AddEntry("times", "photon arrival times");
  leg->AddEntry(expfn, "exp[C_{1}-1/#tau_{f}*x]+exp[C_{2}-1/#tau_{s}*x]  ");
  leg->Draw();
  
  



  
  ////////////////////////////////////
  ///////PLOT ALL 3 COMPONENTS////////
  ////////////////////////////////////

//Make a canvas
  TCanvas *c2 = new TCanvas("c2","c2");
  TH1F *timing = new TH1F("timing","Photon arrival times",250,0,6);
  TH1F *timing_vuv = new TH1F("timing_vuv","VUV light",250,0,6);
  TH1F *timing_vis = new TH1F("timing_vis","Visible light",250,0,6);
  //gStyle->SetOptStat(0);

  //Labelling
  timing->GetXaxis()->SetTitle("Arrival time [#mus]");
  timing->GetYaxis()->SetTitle("Number of photons");
  timing->SetMinimum(0.1);

  timing->GetXaxis()->SetTitleSize(0.05);
  timing->GetXaxis()->SetTitleOffset(0.85);
  timing->GetYaxis()->SetTitleSize(0.05);
  timing->GetYaxis()->SetTitleOffset(0.85);

  //set line colors
  timing->SetLineColor(1);
  timing_vuv->SetLineColor(4);
  timing_vis->SetLineColor(2);

  //Draw on the histrogram using the data from the tree
  data_tree->Draw("data_time >> timing");
  data_tree_vuv->Draw("data_time_vuv >> timing_vuv");
  data_tree_vis->Draw("data_time_vis >> timing_vis");

  //Draw the histogram
  timing->Draw();
  timing_vuv->Draw("SAME");
  timing_vis->Draw("SAME");

  TLegend* leg2 = new TLegend(0.2, 0.2, .8, .8);
  leg2->AddEntry("timing", "Total light");
  leg2->AddEntry("timing_vuv", "VUV light");
  leg2->AddEntry("timing_vis", "Visible light");
  leg2->Draw();
  
}

