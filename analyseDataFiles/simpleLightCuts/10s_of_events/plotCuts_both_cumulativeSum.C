// Read in the .root event file, take the data and plot sensible histograms regarding the detected photons. 


// Important to note
  // coordinates of dimensions of SBND LAr tank (all in cm):
  // x = [ 0 -> 200 ] IN COLTONS CODE for 1 TPC. IRL active region x for 2 TPCs x_active = [-202.5 -> -2.5 ] & [2.5 -> 200] where cathode [-2.5 -> 2.5]
  // y = [ -200 -> 200 ] middle at 0
  // z = [ 0 -> 500 ]  where 0 = front.

{
  
  // read in the first file
  const char* filename1 = "rootFiles/output_10s_sn.root";
  
  TFile * infile1=new TFile(filename1,"READ"); // define the input file

  TH1F * cut10sn=(TH1F *)infile1->Get("cut10sn"); //directs towards the graph in the root file
  TH1F * cut8sn=(TH1F *)infile1->Get("cut8sn"); //directs towards the graph in the root file
  TH1F * cut6sn=(TH1F *)infile1->Get("cut6sn"); //directs towards the graph in the root file
  TH1F * cut4sn=(TH1F *)infile1->Get("cut4sn"); //directs towards the graph in the root file
  

  
  //read in the second file
  const char* filename2 = "rootFiles/output_10s_rn.root";
  
  TFile * infile2=new TFile(filename2,"READ"); // define the input file

  TH1F * cut10rn=(TH1F *)infile2->Get("cut10rn"); //directs towards the graph in the root file
  TH1F * cut8rn=(TH1F *)infile2->Get("cut8rn"); //directs towards the graph in the root file
  TH1F * cut6rn=(TH1F *)infile2->Get("cut6rn"); //directs towards the graph in the root file
  TH1F * cut4rn=(TH1F *)infile2->Get("cut4rn"); //directs towards the graph in the root file

  int bins = 60;
  double temp_sn, temp_rn;
  
  ///////////////
  // for cut10 //
  ///////////////
  double cut10rn_integral = cut10rn->GetEntries();
  double cut10sn_integral = cut10sn->GetEntries();
  cut10rn->Scale(100./cut10rn_integral);
  cut10sn->Scale(100./cut10sn_integral);

  double sum_cut10rn = 0;
  double sum_cut10sn = 0;
  for(int i = 0; i < bins; i++) {
    temp_rn = cut10rn->GetBinContent(i);
    temp_sn = cut10sn->GetBinContent(i);

    sum_cut10rn += temp_rn;
    sum_cut10sn += temp_sn;

    cut10rn->SetBinContent(i,sum_cut10rn);
    cut10sn->SetBinContent(i,sum_cut10sn);
  }


//Make a canvas
  TCanvas *c1 = new TCanvas("c1","c1");
  cut10rn->SetTitle("10 fast photons cut - 10s event run (x1000)");
  cut10rn->GetXaxis()->SetTitle("PMTs passing cut");
  cut10rn->GetYaxis()->SetTitle("% of events cut");

  cut10rn->GetMaximum(100);
  
  cut10rn->GetXaxis()->SetTitleSize(0.05);
  cut10rn->GetXaxis()->SetTitleOffset(0.85);
  cut10rn->GetYaxis()->SetTitleSize(0.05);
  cut10rn->GetYaxis()->SetTitleOffset(0.85);

  //set line colors
  cut10rn->SetLineColor(2);
  cut10sn->SetLineColor(1);

  //turn stats box off
  gStyle->SetOptStat(0);

  //Draw on the histrogram using the data from the tree
  cut10rn->Draw();
  cut10sn->Draw("SAME");


  TLegend* leg1 = new TLegend(0.1, 0.1, 0.5, 0.5);
  leg1->AddEntry("cut10rn", "Radon");
  leg1->AddEntry("cut10sn", "Supernova");
  leg1->Draw();

  
  ///////////////
  // for cut8 //
  ///////////////
  double cut8rn_integral = cut8rn->GetEntries();
  double cut8sn_integral = cut8sn->GetEntries();
  cut8rn->Scale(100./cut8rn_integral);
  cut8sn->Scale(100./cut8sn_integral);

  double sum_cut8rn = 0;
  double sum_cut8sn = 0;
  for(int i = 0; i < bins; i++) {
    temp_sn = cut8sn->GetBinContent(i);
    temp_rn = cut8rn->GetBinContent(i);

    sum_cut8sn += temp_sn;
    sum_cut8rn += temp_rn;

    cut8sn->SetBinContent(i,sum_cut8sn);
    cut8rn->SetBinContent(i,sum_cut8rn);
  }

//Make a canvas
  TCanvas *c2 = new TCanvas("c2","c2");
  //Labelling
  cut8rn->SetTitle("8 fast photons cut - 10s event run (x1000)");
  cut8rn->GetXaxis()->SetTitle("PMTs passing cut");
  cut8rn->GetYaxis()->SetTitle("% of events cut");

  cut8rn->SetMaximum(100);

  cut8rn->GetXaxis()->SetTitleSize(0.05);
  cut8rn->GetXaxis()->SetTitleOffset(0.85);
  cut8rn->GetYaxis()->SetTitleSize(0.05);
  cut8rn->GetYaxis()->SetTitleOffset(0.85);

  //set line colors
  cut8rn->SetLineColor(2);
  cut8sn->SetLineColor(1);

  //turn stats box off
  gStyle->SetOptStat(0);

  //Draw on the histrogram using the data from the tree
  cut8rn->Draw();
  cut8sn->Draw("SAME");

  TLegend* leg2 = new TLegend(0.1, 0.1, 0.5, 0.5);
  leg2->AddEntry("cut8rn", "Radon");
  leg2->AddEntry("cut8sn", "Supernova");
  leg2->Draw();


  ///////////////
  // for cut6 //
  ///////////////
  double cut6rn_integral = cut6rn->GetEntries();
  double cut6sn_integral = cut6sn->GetEntries();
  cut6rn->Scale(100./cut6rn_integral);
  cut6sn->Scale(100./cut6sn_integral);


  double sum_cut6rn = 0;
  double sum_cut6sn = 0;
  for(int i = 0; i < bins; i++) {
    temp_rn = cut6rn->GetBinContent(i);
    temp_sn = cut6sn->GetBinContent(i);

    sum_cut6sn += temp_sn;
    sum_cut6rn += temp_rn;

    cut6sn->SetBinContent(i,sum_cut6sn);
    cut6rn->SetBinContent(i,sum_cut6rn);
  }

//Make a canvas
  TCanvas *c3 = new TCanvas("c3","c3");
  //Labelling
  cut6rn->SetTitle("6 fast photons cut - 10s event run (x1000)");
  cut6rn->GetXaxis()->SetTitle("PMTs passing cut");
  cut6rn->GetYaxis()->SetTitle("% of events cut");

  cut6rn->SetMaximum(100);

  cut6rn->GetXaxis()->SetTitleSize(0.05);
  cut6rn->GetXaxis()->SetTitleOffset(0.85);
  cut6rn->GetYaxis()->SetTitleSize(0.05);
  cut6rn->GetYaxis()->SetTitleOffset(0.85);


  //set line colors
  cut6rn->SetLineColor(2);
  cut6sn->SetLineColor(1);

  //turn stats box off
  gStyle->SetOptStat(0);

  //Draw on the histrogram using the data from the tree
  cut6rn->Draw();
  cut6sn->Draw("SAME");


  TLegend* leg3 = new TLegend(0.1, 0.1, 0.5, 0.5);
  leg3->AddEntry("cut6rn", "Radon");
  leg3->AddEntry("cut6sn", "Supernova");
  leg3->Draw();



  ///////////////
  // for cut4 //
  ///////////////
  double cut4rn_integral = cut4rn->GetEntries();
  double cut4sn_integral = cut4sn->GetEntries();
  cut4rn->Scale(100./cut4rn_integral);
  cut4sn->Scale(100./cut4sn_integral);

  double sum_cut4rn = 0;
  double sum_cut4sn = 0;
  for(int i = 0; i < bins; i++) {
    temp_rn = cut4rn->GetBinContent(i);
    temp_sn = cut4sn->GetBinContent(i);

    sum_cut4sn += temp_sn;
    sum_cut4rn += temp_rn;

    cut4sn->SetBinContent(i,sum_cut4sn);
    cut4rn->SetBinContent(i,sum_cut4rn);
  }


  //Make a canvas
  TCanvas *c4 = new TCanvas("c4","c4");
  //Labelling
  cut4rn->SetTitle("4 fast photons cut - 10s event run (x1000)");
  cut4rn->GetXaxis()->SetTitle("PMTs passing cut");
  cut4rn->GetYaxis()->SetTitle("% of events cut");

  cut4rn->SetMaximum(100);

  cut4rn->GetXaxis()->SetTitleSize(0.05);
  cut4rn->GetXaxis()->SetTitleOffset(0.85);
  cut4rn->GetYaxis()->SetTitleSize(0.05);
  cut4rn->GetYaxis()->SetTitleOffset(0.85);


  //set line colors
  cut4rn->SetLineColor(2);
  cut4sn->SetLineColor(1);

  //turn stats box off
  gStyle->SetOptStat(0);

  //Draw on the histrogram using the data from the tree
  cut4rn->Draw();
  cut4sn->Draw("SAME");


  TLegend* leg4 = new TLegend(0.1, 0.1, 0.5, 0.5);
  leg4->AddEntry("cut4rn", "Radon");
  leg4->AddEntry("cut4sn", "Supernova");
  leg4->Draw();



}

