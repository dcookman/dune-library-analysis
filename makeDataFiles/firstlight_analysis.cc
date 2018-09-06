#include<vector>
#include "utility_functions.h"

void firstlight_analysis(const char * infilename) {
    
    double max_x = 330.;
    
    // LOAD EVENT FILE AND ASSOCIATED BRANCHES
    TFile *fin = new TFile(infilename);
    TTree *dtree = (TTree*)fin->Get("data_tree");
    double data_time;      dtree->SetBranchAddress("data_time", &data_time);
    int data_pmt;       dtree->SetBranchAddress("data_pmt", &data_pmt);
    double data_x_pos;  dtree->SetBranchAddress("data_x_pos", &data_x_pos);
    double data_y_pos;  dtree->SetBranchAddress("data_y_pos", &data_y_pos);
    double data_z_pos;  dtree->SetBranchAddress("data_z_pos", &data_z_pos); 
    int data_event;     dtree->SetBranchAddress("data_event", &data_event);

    /////////////////////////
    // datatree for VUV light from ALL events generated
    ////////////////////////// 
    TTree *dtreevuv = (TTree*)fin->Get("data_tree_vuv");
    double data_time_vuv;      dtreevuv->SetBranchAddress("data_time_vuv", &data_time_vuv);
    int data_pmt_vuv;       dtreevuv->SetBranchAddress("data_pmt_vuv", &data_pmt_vuv);
    double data_x_pos_vuv;  dtreevuv->SetBranchAddress("data_x_pos_vuv", &data_x_pos_vuv); 
    double data_y_pos_vuv;  dtreevuv->SetBranchAddress("data_y_pos_vuv", &data_y_pos_vuv);
    double data_z_pos_vuv;  dtreevuv->SetBranchAddress("data_z_pos_vuv", &data_z_pos_vuv);
    int data_event_vuv;     dtreevuv->SetBranchAddress("data_event_vuv", &data_event_vuv);

    //////////////////////////////////
    // datatree for visible light from ALL events generated
    /////////////////////////////////
    TTree *dtreevis = (TTree*)fin->Get("data_tree_vis");
    double data_time_vis;      dtreevis->SetBranchAddress("data_time_vis", &data_time_vis);
    int data_pmt_vis;       dtreevis->SetBranchAddress("data_pmt_vis", &data_pmt_vis);
    double data_x_pos_vis;  dtreevis->SetBranchAddress("data_x_pos_vis", &data_x_pos_vis);
    double data_y_pos_vis;  dtreevis->SetBranchAddress("data_y_pos_vis", &data_y_pos_vis);
    double data_z_pos_vis;  dtreevis->SetBranchAddress("data_z_pos_vis", &data_z_pos_vis);
    int data_event_vis;     dtreevis->SetBranchAddress("data_event_vis", &data_event_vis);
    
    // Create histogram arrays
    const int numhists = 30;
    const double binlength = max_x/(double)numhists;
    vector<TH1F*> vuvhista;
    vector<TH1F*> vishista;
    for (int j=0; j<numhists; j++) {
        TH1F *vuvh = new TH1F(Form("vuvh%i",j), Form("Earliest Direct time for x-slice %i",j),  3000,0,1);
        TH1F *vish = new TH1F(Form("vish%i",j), Form("Earliest Reflected time for x-slice %i",j),3000,0,1);
        vuvhista.push_back(vuvh);
        vishista.push_back(vish);
    }
    TCanvas *c1 = new TCanvas("c1", "First-Light Times Plot",900,700);
    TH1F *vuvtimehist  = new TH1F("vuvtimehist" , "Earliest Direct-Light Photon Times", numhists,0,max_x);
    TH1F *vistimehist = new TH1F("vistimehist" , "Earliest Reflected Photon Times",    numhists,0,max_x);
    
    //Loop over entries in tree, and for each event find the shortest VUV arrival time
    //then fill the relevant histogram
    const int nentriesvuv = dtreevuv->GetEntries();
    int eventnum = 0;
    double earliesttime = 100000.;
    double last_x_pos;
    int slicenum;
    for(int i=0; i<nentriesvuv; i++) {
        dtreevuv->GetEntry(i);
        if(i!=0 && data_event_vuv != eventnum) {
            eventnum = data_event_vuv;
            slicenum = (last_x_pos/max_x)*numhists;
            //cout << Form("Filling hist with slicenum %i;\tpointer:\t",slicenum);
            //cout << vuvhista[slicenum] << endl;
            vuvhista[slicenum]->Fill(earliesttime);
            earliesttime = 100000.;
        }
        
        if(data_time_vuv < earliesttime) { earliesttime = data_time_vuv; }
        //cout << Form("Event#:\t%i\tOpC:\t%i\tTime:\t%g\tEarliest Time:\t%g\t\n",eventnum,data_pmt_vuv,data_time_vuv,earliesttime);
        
        last_x_pos = data_x_pos_vuv;
    }
    
    //Loop over entries in tree, and for each event find the shortest visible arrival time
    //then fill the relevant histogram
    const int nentriesvis = dtreevis->GetEntries();
    eventnum = 0;
    earliesttime = 100000.;
    for(int i=0; i<nentriesvis; i++) {
        dtreevis->GetEntry(i);
        if(i!=0 && data_event_vis != eventnum) {
            eventnum = data_event_vis;
            slicenum = (data_x_pos_vis/max_x)*numhists;
            vishista[slicenum]->Fill(earliesttime);
            earliesttime = 100000.;
        }
        
        if(data_time_vis < earliesttime) { earliesttime = data_time_vis; }
        //cout << Form("Event#:\t%i\tOpC:\t%i\tTime:\t%g\tEarliest Time:\t%g\t\n",eventnum,data_pmt_vis,data_time_vis,earliesttime);
        
        last_x_pos = data_x_pos_vuv;
    }
    
    //Plot data from histograms
    for(int k=0; k<numhists; k++) {
        vuvtimehist->Fill((k+0.5)*binlength, vuvhista[k]->GetMean());
        vistimehist->Fill((k+0.5)*binlength, vishista[k]->GetMean());
        
        vuvtimehist->SetBinError(k+1,vuvhista[k]->GetStdDev());
        vistimehist->SetBinError(k+1,vishista[k]->GetStdDev());
    }
    
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(0);
    gStyle->SetEndErrorSize(3);
    gStyle->SetErrorX(0);
    
    vuvtimehist->SetLineColor(kBlue);
    vistimehist->SetLineColor(kRed);
    
    vuvtimehist->SetMarkerColor(kBlue);
    vistimehist->SetMarkerColor(kRed);
    
    vuvtimehist->SetMarkerStyle(kFullCircle);
    vistimehist->SetMarkerStyle(kFullStar);
    
    vuvtimehist->GetXaxis()->SetTitle("Drift Distance (cm)");
    vuvtimehist->GetYaxis()->SetTitle("Time of First Photon's Arrival (ns)");
    
    vuvtimehist->Draw("E1");
    vistimehist->Draw("E1 same");
    
}
    
void deltafirstlight_analysis(const char * infilename) {
    
    double max_x = 330.;
    
    // LOAD EVENT FILE AND ASSOCIATED BRANCHES
    TFile *fin = new TFile(infilename);
    TTree *dtree = (TTree*)fin->Get("data_tree");
    double data_time;      dtree->SetBranchAddress("data_time", &data_time);
    int data_pmt;       dtree->SetBranchAddress("data_pmt", &data_pmt);
    double data_x_pos;  dtree->SetBranchAddress("data_x_pos", &data_x_pos);
    double data_y_pos;  dtree->SetBranchAddress("data_y_pos", &data_y_pos);
    double data_z_pos;  dtree->SetBranchAddress("data_z_pos", &data_z_pos); 
    int data_event;     dtree->SetBranchAddress("data_event", &data_event);

    /////////////////////////
    // datatree for VUV light from ALL events generated
    ////////////////////////// 
    TTree *dtreevuv = (TTree*)fin->Get("data_tree_vuv");
    double data_time_vuv;      dtreevuv->SetBranchAddress("data_time_vuv", &data_time_vuv);
    int data_pmt_vuv;       dtreevuv->SetBranchAddress("data_pmt_vuv", &data_pmt_vuv);
    double data_x_pos_vuv;  dtreevuv->SetBranchAddress("data_x_pos_vuv", &data_x_pos_vuv); 
    double data_y_pos_vuv;  dtreevuv->SetBranchAddress("data_y_pos_vuv", &data_y_pos_vuv);
    double data_z_pos_vuv;  dtreevuv->SetBranchAddress("data_z_pos_vuv", &data_z_pos_vuv);
    int data_event_vuv;     dtreevuv->SetBranchAddress("data_event_vuv", &data_event_vuv);

    //////////////////////////////////
    // datatree for visible light from ALL events generated
    /////////////////////////////////
    TTree *dtreevis = (TTree*)fin->Get("data_tree_vis");
    double data_time_vis;      dtreevis->SetBranchAddress("data_time_vis", &data_time_vis);
    int data_pmt_vis;       dtreevis->SetBranchAddress("data_pmt_vis", &data_pmt_vis);
    double data_x_pos_vis;  dtreevis->SetBranchAddress("data_x_pos_vis", &data_x_pos_vis);
    double data_y_pos_vis;  dtreevis->SetBranchAddress("data_y_pos_vis", &data_y_pos_vis);
    double data_z_pos_vis;  dtreevis->SetBranchAddress("data_z_pos_vis", &data_z_pos_vis);
    int data_event_vis;     dtreevis->SetBranchAddress("data_event_vis", &data_event_vis);
    
    // Create histogram arrays
    const int numhists = 30;
    const double binlength = max_x/(double)numhists;
    vector<TH1F*> hista;
    for (int j=0; j<numhists; j++) {
        TH1F *deltah = new TH1F(Form("deltah%i",j), Form("Difference in Earliest Direct times for x-slice %i",j),  30000,-3.,3.);
        hista.push_back(deltah);
    }
    TCanvas *c1 = new TCanvas("c1", "Difference in Earliest Times Plot",900,700);
    TH1F *deltatimehist  = new TH1F("deltatimehist" , "Difference in Earliest Photon Times", numhists,0,max_x);
    
    //Loop over entries in tree, and for each event find the shortest VUV arrival time
    //then fill the relevant histogram
    
    const int nentriesvuv = dtreevuv->GetEntries();
    int eventnum = 0;
    double earliesttimevuv = 100000.;
    double last_x_pos;
    int slicenum;
    int j = 0;
    double earliesttimevis = 100000.;
    for(int i=0; i<nentriesvuv; i++) {
        dtreevuv->GetEntry(i);
        if(i!=0 && data_event_vuv != eventnum) {
            
            dtreevis->GetEntry(j);
            while(data_event_vis == eventnum) {
                if(data_time_vis < earliesttimevis) { earliesttimevis = data_time_vis; }
                j++;
                dtreevis->GetEntry(j);
            }
            
            slicenum = (last_x_pos/max_x)*numhists;
            double deltat = earliesttimevis-earliesttimevuv;
            hista[slicenum]->Fill(deltat);
            
            earliesttimevuv = 100000.;
            earliesttimevis = 100000.;
            eventnum = data_event_vuv;
        }
        
        if(data_time_vuv < earliesttimevuv) { earliesttimevuv = data_time_vuv; }
        
        last_x_pos = data_x_pos_vuv;
    }
    
    //Plot data from histograms
    for(int k=0; k<numhists; k++) {
        deltatimehist->Fill((k+0.5)*binlength, hista[k]->GetMean());
        deltatimehist->SetBinError(k+1,hista[k]->GetStdDev());
    }
    
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(0);
    gStyle->SetEndErrorSize(3);
    gStyle->SetErrorX(0);
    
    deltatimehist->SetLineColor(kBlue);
    deltatimehist->SetMarkerColor(kBlue);
    deltatimehist->SetMarkerStyle(kFullCircle);
    deltatimehist->GetXaxis()->SetTitle("Drift Distance (cm)");
    deltatimehist->GetYaxis()->SetTitle("Difference in Time of First Photon's Arrival (ns)");
    
    deltatimehist->Draw("E1");
}


void testVUVTimes(double distance, int num_phot) {
    vector<double> VUVTimes = utility::GetVUVTime(distance, num_phot);
    TH1F *vuvtimehist  = new TH1F("vuvtimehist" , "Earliest Direct-Light Photon Times", 2000,0,400);
    
    for(auto& x: VUVTimes) {
        vuvtimehist->Fill(x);
    }
    vuvtimehist->Draw();
}
