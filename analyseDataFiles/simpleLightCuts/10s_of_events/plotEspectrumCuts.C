// Read in the .root event file, take the data and plot sensible histograms regarding the detected photons. 

{
  
  // read in the first (supernova) file
  const char* filename1 = "rootFiles/output_10s_sn_Ecuts.root";
  
  TFile * infile1=new TFile(filename1,"READ"); // define the input file

  TH1F * E_cut0sn=(TH1F *)infile1->Get("E_cut0sn"); //directs towards the graph in the root file 
    TH1F * E_cut10sn_8pmts=(TH1F *)infile1->Get("E_cut10sn_8pmts"); 
 
    TH1F * E_cut8sn_10pmts=(TH1F *)infile1->Get("E_cut8sn_10pmts"); 
    TH1F * E_cut8sn_15pmts=(TH1F *)infile1->Get("E_cut8sn_15pmts"); 

    TH1F * E_cut6sn_11pmts=(TH1F *)infile1->Get("E_cut6sn_11pmts"); 
  
    TH1F * E_cut4sn_20pmts=(TH1F *)infile1->Get("E_cut4sn_20pmts"); 

  

  //read in the second (radon) file
  const char* filename2 = "rootFiles/output_10s_rn_Ecuts.root";
  
  TFile * infile2=new TFile(filename2,"READ"); // define the input file
  TH1F * E_cut0rn=(TH1F *)infile2->Get("E_cut0rn"); //directs towards the graph in the root file
  
    TH1F * E_cut10rn_8pmts=(TH1F *)infile2->Get("E_cut10rn_8pmts"); 
  
    TH1F * E_cut8rn_10pmts=(TH1F *)infile2->Get("E_cut8rn_10pmts"); 
    TH1F * E_cut8rn_15pmts=(TH1F *)infile2->Get("E_cut8rn_15pmts"); 

    TH1F * E_cut6rn_11pmts=(TH1F *)infile2->Get("E_cut6rn_11pmts"); 

    TH1F * E_cut4rn_20pmts=(TH1F *)infile2->Get("E_cut4rn_20pmts"); 

  

  ////////////////////////////////////
  //////////// Quick analysis ////////
  ////////////////////////////////////
  double_t max_sn = E_cut0sn->GetMaximum();
  double_t max_rn = E_cut0rn->GetMaximum();

  double photons_cut0sn = E_cut0sn->GetEntries();
  double photons_cut0rn = E_cut0rn->GetEntries();
  
  double photons_cut10sn_8pmts = E_cut10sn_8pmts->GetEntries();  double photons_cut10rn_8pmts = E_cut10rn_8pmts->GetEntries();

  double photons_cut8sn_10pmts = E_cut8sn_10pmts->GetEntries();  double photons_cut8rn_10pmts = E_cut8rn_10pmts->GetEntries();
  double photons_cut8sn_15pmts = E_cut8sn_15pmts->GetEntries();  double photons_cut8rn_15pmts = E_cut8rn_15pmts->GetEntries();

  double photons_cut6sn_11pmts = E_cut6sn_11pmts->GetEntries();  double photons_cut6rn_11pmts = E_cut6rn_11pmts->GetEntries();

  double photons_cut4sn_20pmts = E_cut4sn_20pmts->GetEntries();    double photons_cut4rn_20pmts = E_cut4rn_20pmts->GetEntries();


  cout << "Number of SN events: " << photons_cut0sn << endl;
  cout << "Number of Rn events: " << photons_cut0rn << endl;

  cout << endl << endl << "------10 fast photons-------" << endl;  
  cout << "On 8 PMTs:" << endl;   
  cout << "SN events: " << photons_cut10sn_8pmts << " => " << (photons_cut10sn_8pmts/photons_cut0sn) * 100 << "% of original SN events" << endl;
  cout << "Rn events: " << photons_cut10rn_8pmts << " => " << (photons_cut10rn_8pmts/photons_cut0rn) * 100 << "% of original Rn events" << endl;
  cout << "---------------------------" << endl;


  cout << endl << endl << "------8 fast photons-------" << endl;  
  cout << "On 10 PMTs:" << endl;   
  cout << "SN events: " << photons_cut8sn_10pmts << " => " << (photons_cut8sn_10pmts/photons_cut0sn) * 100 << "% of original SN events" << endl;
  cout << "Rn events: " << photons_cut8rn_10pmts << " => " << (photons_cut8rn_10pmts/photons_cut0rn) * 100 << "% of original Rn events" << endl;
  cout << endl;
  cout << "On 15 PMTs:" << endl;   
  cout << "SN events: " << photons_cut8sn_15pmts << " => " << (photons_cut8sn_15pmts/photons_cut0sn) * 100 << "% of original SN events" << endl;
  cout << "Rn events: " << photons_cut8rn_15pmts << " => " << (photons_cut8rn_15pmts/photons_cut0rn) * 100 << "% of original Rn events" << endl;
  cout << "---------------------------" << endl;


  cout << endl << endl << "------6 fast photons-------" << endl;  
  cout << "On 11 PMTs:" << endl;   
  cout << "SN events: " << photons_cut6sn_11pmts << " => " << (photons_cut6sn_11pmts/photons_cut0sn) * 100 << "% of original SN events" << endl;
  cout << "Rn events: " << photons_cut6rn_11pmts << " => " << (photons_cut6rn_11pmts/photons_cut0rn) * 100 << "% of original Rn events" << endl;
  cout << "---------------------------" << endl;

  cout << endl << endl << "------4 fast photons-------" << endl;  
  cout << "On 20 PMTs:" << endl;   
  cout << "SN events: " << photons_cut4sn_20pmts << " => " << (photons_cut4sn_20pmts/photons_cut0sn) * 100 << "% of original SN events" << endl;
  cout << "Rn events: " << photons_cut4rn_20pmts << " => " << (photons_cut4rn_20pmts/photons_cut0rn) * 100 << "% of original Rn events" << endl;
  cout << "---------------------------" << endl;


  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////// Drawing the histograms //////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Make a canvas
  TCanvas *c1 = new TCanvas("c1","cut 10 SN");
  //Labelling
  E_cut0sn->SetTitle("The effect of simple light cuts on the supernova energy spectrum");
  E_cut0sn->GetXaxis()->SetTitle("Energy [MeV]");
  E_cut0sn->GetYaxis()->SetTitle("Events");
  E_cut0sn->SetMaximum(max_sn+10);

  E_cut0sn ->GetXaxis()->SetTitleSize(0.05);
  E_cut0sn->GetXaxis()->SetTitleOffset(0.85);
  E_cut0sn->GetYaxis()->SetTitleSize(0.05);
  E_cut0sn->GetYaxis()->SetTitleOffset(0.85);

  //set line colors
  E_cut0sn->SetLineColor(1);
  E_cut4sn_20pmts->SetLineColor(2);
  E_cut6sn_11pmts->SetLineColor(7);
  E_cut8sn_15pmts->SetLineColor(8);
  E_cut10sn_8pmts->SetLineColor(6);

  //turn stats box off
  gStyle->SetOptStat(0);

  //Draw on the histrogram using the data from the tree
  E_cut0sn->Draw();
  E_cut4sn_20pmts->Draw("SAME");
  E_cut6sn_11pmts->Draw("SAME");
  E_cut8sn_15pmts->Draw("SAME");
  E_cut10sn_8pmts->Draw("SAME");
  
  

  TLegend* leg1 = new TLegend(0.1, 0.1, 0.5, 0.5);
  leg1->AddEntry("E_cut0sn", "No cuts");
  leg1->AddEntry("E_cut4sn_20pmts", "1: 4 fast photons, 20 pmts");
  leg1->AddEntry("E_cut6sn_11pmts", "2: 6 fast photons, 11 pmts");
  leg1->AddEntry("E_cut8sn_15pmts", "3: 8 fast photons, 15 pmts");
  leg1->AddEntry("E_cut10sn_8pmts", "4: 10 fast photons, 8 pmts");
  leg1->Draw();



  ///////////////
  // radon
  ///////////////
//Make a canvas
  TCanvas *c2 = new TCanvas("c2","cut 10 Rn");
  //Labelling
  E_cut0rn->SetTitle("The effect of simple light cuts on the radon energy spectrum");
  E_cut0rn->GetXaxis()->SetTitle("Energy [MeV]");
  E_cut0rn->GetYaxis()->SetTitle("Events");
  E_cut0rn->SetMaximum(max_rn+10);

  E_cut0rn ->GetXaxis()->SetTitleSize(0.05);
  E_cut0rn->GetXaxis()->SetTitleOffset(0.85);
  E_cut0rn->GetYaxis()->SetTitleSize(0.05);
  E_cut0rn->GetYaxis()->SetTitleOffset(0.85);

  //set line colors
  E_cut0rn->SetLineColor(1);
  E_cut4rn_20pmts->SetLineColor(2);
  E_cut6rn_11pmts->SetLineColor(7);
  E_cut8rn_15pmts->SetLineColor(8);
  E_cut10rn_8pmts->SetLineColor(6);

  //turn stats box off
  gStyle->SetOptStat(0);

  //Draw on the histrogram using the data from the tree
  E_cut0rn->Draw();
  E_cut4rn_20pmts->Draw("SAME");
  E_cut6rn_11pmts->Draw("SAME");
  E_cut8rn_15pmts->Draw("SAME");
  E_cut10rn_8pmts->Draw("SAME");
  
  TLegend* leg2 = new TLegend(0.1, 0.1, 0.5, 0.5);
  leg2->AddEntry("E_cut0rn", "No cuts");
  leg2->AddEntry("E_cut4rn_20pmts", "1: 4 fast photons, 20 pmts");
  leg2->AddEntry("E_cut6rn_11pmts", "2: 6 fast photons, 11 pmts");
  leg2->AddEntry("E_cut8rn_15pmts", "3: 8 fast photons, 15 pmts");
  leg2->AddEntry("E_cut10rn_8pmts", "4: 10 fast photons, 8 pmts");
  leg2->Draw();
  

}

