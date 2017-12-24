// Read in the .root event file, take the data and plot sensible histograms regarding the detected photons. 


// Important to note
  // coordinates of dimensions of SBND LAr tank (all in cm):
  // x = [ 0 -> 200 ] IN COLTONS CODE for 1 TPC. IRL active region x for 2 TPCs x_active = [-202.5 -> -2.5 ] & [2.5 -> 200] where cathode [-2.5 -> 2.5]
  // y = [ -200 -> 200 ] middle at 0
  // z = [ 0 -> 500 ]  where 0 = front.

{

  filename = "1mil_fixed1MeV_randompos.root";

  TFile * infile=new TFile(filename,"READ"); // define the input file

  TTree * data_tree=(TTree *)infile->Get("data_tree"); //directs towards to root tree inside the input file

  TTree * data_tree_vuv=(TTree *)infile->Get("data_tree_vuv");
  TTree * data_tree_vis=(TTree *)infile->Get("data_tree_vis");

  double bin_content;
  double new_bin_content;
  
  /*
 //////////////////////////////////////////////////////////////////////////////////
 ///////// ***** Histogram for z  position of each detected photon ***** //////////   
 //////////////////////////////////////////////////////////////////////////////////

//Make a canvas
  TCanvas *c1 = new TCanvas("c1","c1");
  TH1F *zpos = new TH1F("zpos","Detected light",100,0,500);
  TH1F *zpos_vuv = new TH1F("zpos_vuv","VUV light",100,0,500);
  TH1F *zpos_vis = new TH1F("zpos_vis","Visible light",100,0,500);
  gStyle->SetOptStat(0);

  //Labelling
  zpos->GetXaxis()->SetTitle("z position (down beam-line) [cm]");
  zpos->GetYaxis()->SetTitle("Detected photons / MeV deposited");
  zpos->SetMinimum(0);

  zpos->GetXaxis()->SetTitleSize(0.05);
  zpos->GetXaxis()->SetTitleOffset(0.85);
  zpos->GetYaxis()->SetTitleSize(0.05);
  zpos->GetYaxis()->SetTitleOffset(0.85);


  //set line colors
  zpos->SetLineColor(1);
  zpos_vuv->SetLineColor(4);
  zpos_vis->SetLineColor(2);



  //Draw on the histrogram using the data from the tree
  data_tree->Draw("data_z_pos >> zpos");
  data_tree_vuv->Draw("data_z_pos_vuv >> zpos_vuv");
  data_tree_vis->Draw("data_z_pos_vis >> zpos_vis");
  

  int zsize = zpos->GetSize() - 1;
  int zsize_vuv = zpos_vuv->GetSize() - 1;
  int zsize_vis = zpos_vis->GetSize() - 1;
  

  for(int i = 0; i < zsize; i++){
    bin_content = zpos->GetBinContent(i);
    new_bin_content = bin_content/(1000000/(zsize-1));
    zpos->SetBinContent(i,new_bin_content);
  }

  for(int i = 0; i < zsize_vuv; i++){
    bin_content = zpos_vuv->GetBinContent(i);
    new_bin_content = bin_content/(1000000/(zsize_vuv-1));
    zpos_vuv->SetBinContent(i,new_bin_content);
  }

  for(int i = 0; i < zsize_vis; i++){
    bin_content = zpos_vis->GetBinContent(i);
    new_bin_content = bin_content/(1000000/(zsize_vis-1));
    zpos_vis->SetBinContent(i,new_bin_content);
  }




 //Draw the histogram
  zpos->Draw();
  zpos_vuv->Draw("SAME");
  zpos_vis->Draw("SAME");
  
  TLegend* leg = new TLegend(0.2, 0.2, .8, .8);
  leg->AddEntry("zpos", "Total light");
  leg->AddEntry("zpos_vuv", "VUV light");
  leg->AddEntry("zpos_vis", "Visible light");
  leg->Draw();
  

  
 //////////////////////////////////////////////////////////////////////////////////
 ///////// ***** Histogram for y position of each detected photon ***** ///////////  
 //////////////////////////////////////////////////////////////////////////////////
  

//Make a canvas
  TCanvas *c2 = new TCanvas("c2","c2");
  TH1F *ypos = new TH1F("ypos","Detected light",80,-200,200);
  TH1F *ypos_vuv = new TH1F("ypos_vuv","VUV light",80,-200,200);
  TH1F *ypos_vis = new TH1F("ypos_vis","Visible light",80,-200,200);


  //Labelling
  ypos->GetXaxis()->SetTitle("y position (y=0 at TPC center) [cm]");
  ypos->GetYaxis()->SetTitle("Detected photons / MeV deposited");
  ypos->SetMinimum(0);

  ypos->GetXaxis()->SetTitleSize(0.05);
  ypos->GetXaxis()->SetTitleOffset(0.85);
  ypos->GetYaxis()->SetTitleSize(0.05);
  ypos->GetYaxis()->SetTitleOffset(0.85);


  //set line colors
  ypos->SetLineColor(1);
  ypos_vuv->SetLineColor(4);
  ypos_vis->SetLineColor(2);


  //Draw on the histrogram using the data from the tree
  data_tree->Draw("data_y_pos >> ypos");
  data_tree_vuv->Draw("data_y_pos_vuv >> ypos_vuv");
  data_tree_vis->Draw("data_y_pos_vis >> ypos_vis");

  int ysize = ypos->GetSize() - 1;
  int ysize_vuv = ypos_vuv->GetSize() - 1;
  int ysize_vis = ypos_vis->GetSize() - 1;
  
  for(int i = 0; i < ysize; i++){
    bin_content = ypos->GetBinContent(i);
    new_bin_content = bin_content/(1000000/(ysize-1));
    ypos->SetBinContent(i,new_bin_content);
  }

  for(int i = 0; i < ysize_vuv; i++){
    bin_content = ypos_vuv->GetBinContent(i);
    new_bin_content = bin_content/(1000000/(ysize_vuv-1));
    ypos_vuv->SetBinContent(i,new_bin_content);
  }

  for(int i = 0; i < ysize_vis; i++){
    bin_content = ypos_vis->GetBinContent(i);
    new_bin_content = bin_content/(1000000/(ysize_vis-1));
    ypos_vis->SetBinContent(i,new_bin_content);
  }


 

  //Draw the histogram
  ypos->Draw();
  ypos_vuv->Draw("SAME");
  ypos_vis->Draw("SAME");

  TLegend* leg2 = new TLegend(0.2, 0.2, .8, .8);
  leg2->AddEntry("ypos", "Total light");
  leg2->AddEntry("ypos_vuv", "VUV light");
  leg2->AddEntry("ypos_vis", "Visible light");
  leg2->Draw();


 //////////////////////////////////////////////////////////////////////////////////
 ///////// ***** Histogram for x position of each detected photon ***** ///////////  
 //////////////////////////////////////////////////////////////////////////////////

//Make a canvas
  TCanvas *c3 = new TCanvas("c3","c3");
  TH1F *xpos = new TH1F("xpos","Detected light",40,0,200);
  TH1F *xpos_vuv = new TH1F("xpos_vuv","VUV light",40,0,200);
  TH1F *xpos_vis = new TH1F("xpos_vis","Visible light",40,0,200);


  //Labelling
  xpos->GetXaxis()->SetTitle("x position (x=0 at Cathode) [cm]");
  xpos->GetYaxis()->SetTitle("Detected photons / MeV deposited");
  xpos->SetMinimum(0);

  xpos->GetXaxis()->SetTitleSize(0.05);
  xpos->GetXaxis()->SetTitleOffset(0.85);
  xpos->GetYaxis()->SetTitleSize(0.05);
  xpos->GetYaxis()->SetTitleOffset(0.85);

  //set line colors
  xpos->SetLineColor(1);
  xpos_vuv->SetLineColor(4);
  xpos_vis->SetLineColor(2);


  //Draw on the histrogram using the data from the tree
  data_tree->Draw("data_x_pos >> xpos");
  data_tree_vuv->Draw("data_x_pos_vuv >> xpos_vuv");
  data_tree_vis->Draw("data_x_pos_vis >> xpos_vis");


  int xsize = xpos->GetSize() - 1;
  int xsize_vuv = xpos_vuv->GetSize() - 1;
  int xsize_vis = xpos_vis->GetSize() - 1;
  
  for(int i = 0; i < xsize; i++){
    bin_content = xpos->GetBinContent(i);
    new_bin_content = bin_content/(1000000/(xsize-1));
    xpos->SetBinContent(i,new_bin_content);
  }

  for(int i = 0; i < xsize_vuv; i++){
    bin_content = xpos_vuv->GetBinContent(i);
    new_bin_content = bin_content/(1000000/(xsize_vuv-1));
    xpos_vuv->SetBinContent(i,new_bin_content);
  }

  for(int i = 0; i < xsize_vis; i++){
    bin_content = xpos_vis->GetBinContent(i);
    new_bin_content = bin_content/(1000000/(xsize_vis-1));
    xpos_vis->SetBinContent(i,new_bin_content);
  }


 

  //Draw the histogram
  xpos->Draw();
  xpos_vuv->Draw("SAME");
  xpos_vis->Draw("SAME");

  TLegend* leg3 = new TLegend(0.2, 0.2, .8, .8);
  leg3->AddEntry("xpos", "Total light");
  leg3->AddEntry("xpos_vuv", "VUV light");
  leg3->AddEntry("xpos_vis", "Visible light");
  leg3->Draw();


  */
  
  ////////// ***** Plot x-y plane ***** //////////

  TCanvas *c4 = new TCanvas("c4,c4");
  TH2F *xyplane = new TH2F("xyplane", "Detector response as viewed from x-y plane (all light)", 40, 0, 200, 80, -200, 200);  

  
  //Labelling
  xyplane->SetTitle("Detector response as viewed from x-y plane (all light)");
  xyplane->GetXaxis()->SetTitle("x position (Cathode at x = 0 cm) [cm]");
  xyplane->GetYaxis()->SetTitle("y position [cm]");

  xyplane->SetTitleSize(22);
  xyplane->GetXaxis()->SetTitleSize(0.05);
  xyplane->GetXaxis()->SetTitleOffset(0.85);
  xyplane->GetYaxis()->SetTitleSize(0.05);
  xyplane->GetYaxis()->SetTitleOffset(0.85);
  
  gStyle->SetOptStat(0);

  data_tree->Draw("data_y_pos:data_x_pos >> xyplane"); 

  int bins_x = xyplane->GetNbinsX();
  int bins_y = xyplane->GetNbinsY();
  double bins_tot = bins_x * bins_y;

  for(int i = 1; i <= bins_x; i++){
    for(int j = 1; j <= bins_y; j++){
      bin_content = xyplane->GetBinContent(i,j);
      new_bin_content = bin_content/(1000000/(bins_tot));
      xyplane->SetBinContent(i,j,new_bin_content);
    }  
  }
  
  xyplane->Draw("COLZ");
  
  
 ////////// ***** Plot x-y plane vuv only ***** //////////

  TCanvas *c5 = new TCanvas("c5,c5");
  TH2F *xyplane_vuv = new TH2F("xyplane_vuv", "Detector response as viewed from x-y plane (VUV only)", 40, 0, 200, 80, -200, 200);  
  

  //Labelling
  xyplane_vuv->SetTitle("Detector response as viewed from x-y plane (VUV light only)");
  xyplane_vuv->GetXaxis()->SetTitle("x position (Cathode at x = 0 cm) [cm]");
  xyplane_vuv->GetYaxis()->SetTitle("y position [cm]");

  xyplane_vuv->SetTitleSize(22);
  xyplane_vuv->GetXaxis()->SetTitleSize(0.05);
  xyplane_vuv->GetXaxis()->SetTitleOffset(0.85);
  xyplane_vuv->GetYaxis()->SetTitleSize(0.05);
  xyplane_vuv->GetYaxis()->SetTitleOffset(0.85);
  
  gStyle->SetOptStat(0);


  data_tree_vuv->Draw("data_y_pos_vuv:data_x_pos_vuv >> xyplane_vuv"); 

  int bins_x_vuv = xyplane_vuv->GetNbinsX();
  int bins_y_vuv = xyplane_vuv->GetNbinsY();
  double bins_tot_vuv = bins_x_vuv * bins_y_vuv;

  for(int i = 1; i <= bins_x_vuv; i++){
    for(int j = 1; j <= bins_y_vuv; j++){
      bin_content = xyplane_vuv->GetBinContent(i,j);
      new_bin_content = bin_content/(1000000/(bins_tot_vuv));
      xyplane_vuv->SetBinContent(i,j,new_bin_content);
    }  
  }

  xyplane_vuv->Draw("COLZ"); 


////////// ***** Plot x-y plane vis only ***** //////////

  TCanvas *c6 = new TCanvas("c6,c6");
  TH2F *xyplane_vis = new TH2F("xyplane_vis", "Detector response as viewed from x-y plane (Visible light only)", 40, 0, 200, 80, -200, 200);  


  //Labelling
  xyplane_vis->SetTitle("Detector response as viewed from x-y plane (Visible light only)");
  xyplane_vis->GetXaxis()->SetTitle("x position (Cathode at x = 0 cm) [cm]");
  xyplane_vis->GetYaxis()->SetTitle("y position [cm]");

  xyplane_vis->SetTitleSize(22);
  xyplane_vis->GetXaxis()->SetTitleSize(0.05);
  xyplane_vis->GetXaxis()->SetTitleOffset(0.85);
  xyplane_vis->GetYaxis()->SetTitleSize(0.05);
  xyplane_vis->GetYaxis()->SetTitleOffset(0.85);
  
  gStyle->SetOptStat(0);


  data_tree_vis->Draw("data_y_pos_vis:data_x_pos_vis >> xyplane_vis"); 

  int bins_x_vis = xyplane_vis->GetNbinsX();
  int bins_y_vis = xyplane_vis->GetNbinsY();
  double bins_tot_vis = bins_x_vis * bins_y_vis;

  for(int i = 1; i <= bins_x_vis; i++){
    for(int j = 1; j <= bins_y_vis; j++){
      bin_content = xyplane_vis->GetBinContent(i,j);
      new_bin_content = bin_content/(1000000/(bins_tot_vis));
      xyplane_vis->SetBinContent(i,j,new_bin_content);
    }  
  }


  xyplane_vis->Draw("COLZ"); 

  


  //infile->Close(); // close the input file

}

