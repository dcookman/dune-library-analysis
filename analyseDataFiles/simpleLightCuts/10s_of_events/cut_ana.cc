#include <vector>
#include "unistd.h"
#include <stdio.h>

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"
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

//#include "utility_functions.h"

using namespace std;

///-------------------------------------
///Custom Sorting Function
///-------------------------------------
bool sort_function(std::pair<double, int> pair1, std::pair<double, int> pair2)
{
	return (pair1.first < pair2.first);
}
///-------------------------------------

double cut_time = 0.1;


int main(int argc, char* argv[])
{

	///Supernova timing analysis
	bool supernova = false;
	bool argon = false;
	bool radon = false;

	std::string libraryfile1 = argv[1];
	string type = argv[2];
	if(type == "sn" || type == "Sn") {supernova = true;}
	if(type == "rn" || type == "Rn") {radon = true;}
	if(type == "ar" || type == "Ar") {argon = true;}
	
	if(supernova == false && argon == false && radon == false)
	  {cout << "Nothing to analyze..." << endl; exit(0); }
	if(supernova == true) {cout << "Running over supernova events..." << endl; }
	if(argon == true){cout << "Running over argon39 events..." << endl; }
	if(radon == true){cout << "Running over radon-222 events..." << endl; }

	cout << "Reading photon library from input file: " << libraryfile1.c_str()<<endl;

	TFile *f1 = nullptr;
	f1  =  TFile::Open(libraryfile1.c_str());
	TTree *data_tree1 = nullptr;
	data_tree1 =  (TTree*)f1->Get("data_tree");
	
	
	double data_time1;
	int data_pmt1;
	int data_event1;
	double data_x_pos1;
	double data_y_pos1;
	double data_z_pos1;

	data_tree1->SetBranchAddress("data_time", &data_time1);
	data_tree1->SetBranchAddress("data_pmt", &data_pmt1);
	data_tree1->SetBranchAddress("data_x_pos", &data_x_pos1);
	data_tree1->SetBranchAddress("data_y_pos", &data_y_pos1);
	data_tree1->SetBranchAddress("data_z_pos", &data_z_pos1);


	// TFile *f2 = nullptr;
	// f2  =  TFile::Open(libraryfile1.c_str());
	TTree *event_tree1 = nullptr;
	event_tree1 = (TTree*)f1->Get("event_tree");

	double event_E;
	double event_xpos;
	double event_ypos;
	double event_zpos;
	event_tree1->SetBranchAddress("event_E", &event_E);
	event_tree1->SetBranchAddress("event_x_pos", &event_xpos);
	event_tree1->SetBranchAddress("event_y_pos", &event_ypos);
	event_tree1->SetBranchAddress("event_z_pos", &event_zpos);

        int entries1 = 0;
	if(supernova == true || radon == true)
	{
		entries1 = data_tree1->GetEntries();
 		data_tree1->SetBranchAddress("data_event", &data_event1);
		cout << "Data file has: " << entries1 << " entries" << endl;
		
	}

	if(argon == true)
	{
		entries1 = data_tree1->GetEntries();
		cout << "Data file has: " << entries1 << " entries" << endl;
	}


	
	int realisticPMT_IDs[60] = {0, 4, 8, 12, 16, 20, 24, 32, 40, 44, 48, 52, 56, 60, 64, 88, 92, 96, 100, 104, 108, 112, 120, 128, 132, 136, 140, 144, 148, 152, 154, 158, 162, 166, 170, 174, 178, 186, 194, 198, 202, 206, 210, 214, 218, 242, 246, 250, 254, 258, 262, 266, 274, 282, 286, 290, 294, 298, 302, 306};




	////////////////////////////////////////////////////////////////////
	///////////////IF SUPERNOVA == TRUE ////////////////////////////////
	////////////////////////////////////////////////////////////////////
      
	if(supernova == true){	 

	//////////DECALRE HISTOGRAMS THAT NEED FILLING //////////
	TH1F *E_cut0sn = new TH1F("E_cut0sn","SN energy spectrum - No cuts",50,0,50);

	TH1F *cut10sn = new TH1F("cut10sn","PMTs with more than 10 fast photons",60,0,60);
	  TH1F *E_cut10sn_8pmts = new TH1F("E_cut10sn_8pmts","Supernova energy spectrum - 8 PMTs & 10 fast photon cut",50,0,50);
	  

	TH1F *cut8sn = new TH1F("cut8sn","PMTs with more than 8 fast photons",60,0,60);
	  TH1F *E_cut8sn_15pmts = new TH1F("E_cut8sn_15pmts","Supernova energy spectrum - 15 PMTs & 8 fast photon cut",50,0,50);
	  TH1F *E_cut8sn_10pmts = new TH1F("E_cut8sn_10pmts","Supernova energy spectrum - 10 PMTs & 8 fast photon cut",50,0,50);


	TH1F *cut6sn = new TH1F("cut6sn","PMTs with more than 6 fast photons",60,0,60);
	  TH1F *E_cut6sn_11pmts = new TH1F("E_cut6sn_11pmts","Supernova energy spectrum - 11 PMTs & 6 fast photon cut",50,0,50);

	TH1F *cut4sn = new TH1F("cut4sn","PMTs with more than 4 fast photons",60,0,60);
          TH1F *E_cut4sn_20pmts = new TH1F("E_cut4sn_20pmts","Supernova energy spectrum - 20 PMTs & 4 fast photon cut",50,0,50);

 
	  int no_of_evts = event_tree1->GetEntries(); //total number of events will be equal to the entires in the event tree 
	  cout << endl << "TEST - # of events: " << no_of_evts << endl;

	  double detected_photons = entries1; // total number of DETECTED photons from ALL events
	  double created_photons;
	  if(supernova == true){created_photons = no_of_evts * 24000;} //24000 is the scint yield of an electron in LAr @ 500 V/cm
	  if(radon == true){created_photons = no_of_evts * 16800;} // 16800 = SY of Alpha in LAr @ 500 V/cm
	  double percent_detected = (detected_photons/created_photons)*100;

	  cout << endl << "For the whole simulation - " << detected_photons << " of " << created_photons << " photons were detected." << endl;
	  cout << "This corresponds to: " << percent_detected << "% of photon detected." << endl << endl;;

	  //create vector of energies
	  vector<double> event_Es;
	  vector<double> evt_x;
	  vector<double> evt_y;
	  vector<double> evt_z;
	  for(int evt = 0; evt < no_of_evts; evt++){
	    event_tree1->GetEntry(evt);
	    event_Es.push_back(event_E);
	    evt_x.push_back(event_xpos);
	    evt_y.push_back(event_ypos);
	    evt_z.push_back(event_zpos);

	    //cout << "Energy of event " << evt+1 << " is: " << event_E << " MeV.";
	    //cout << "\t At position: (" << event_xpos << "," << event_ypos << "," << event_zpos << ")" << endl;
	  }

	  cout << endl << "Energy vector filled..." << endl;
	 


	  ///////////////////////////////////////////////////////////////////////////////////////
	  /////////PHOTON LOOP TO CREATE THE VECTOR OF VECTORS WITH ALL//////////////////////////
	  /////////////PHOTON TIMES ON EACH PMT FOR CURRENT EVENT////////////////////////////////
	  ///////////////////////////////////////////////////////////////////////////////////////
	  cout << endl << "Beginning main loop..." << endl;
	  vector< vector<double> > pmt_times; // Vector of vectors storing the times in each PMT
	  vector<double> hit_times;
	  int current_entry = 0;
	  for(int evt = 0; evt < no_of_evts; evt++){

	  int current_pmt_entry  = 0;
	    for(int pmt_no  = 0; pmt_no < 60; pmt_no++){
	   

	      for(int i = current_entry; i < entries1; i++){	      
		data_tree1->GetEntry(i);
	      
		//fill a normal vector	    
		if(data_pmt1 == realisticPMT_IDs[pmt_no] && data_event1 == evt ) //the pmt the photon hit is the pmt we're on in the current iteration
		  {
		    hit_times.push_back(data_time1); //fill a vector with all the photon times from event "evt" which hit pmt "pmt_no" 		  
		  }
	      
		if(data_event1 > evt) {
		  current_pmt_entry = i;
		  		  
		  break;
		}
		
	      
	      } // end of entry (photon) loop
	     

	      pmt_times.push_back(hit_times); //fill the pmts vector with the times from that event hitting that pmt
	      hit_times.clear();  // clear the vector      
	    
	    } // end of pmt loop
	    current_entry = current_pmt_entry;

	    ////////////////////////////////////////////////////////////////////////////////////
	    /////////////////TESTING THE OUTPUT OF THE VECTOR OF VECTORS////////////////////////
	    ////////////////////////////////////////////////////////////////////////////////////

	    /*
	      cout << "Event " << evt + 1 << "\tEnergy: " << event_Es[evt];
	      cout << " MeV \tPosition: (" << evt_x[evt] << "," << evt_y[evt] << "," << evt_z[evt] <<")";
	    */


	    /*
	    // CHECK HOW MANY PHOTONS IN AN EVENT (need to modify the evt loop to one iteration)
	    int evt_photons = 0;
	    for(int i = 0; i < 60; i++){
	    evt_photons += pmt_times[i].size();
	    }
	    */
    
	    //cout << endl << endl << "Total no of photons from evt: " << evt_photons << endl;


	    ////////////////////////////////////////////////////////////////////////////////////
	    //NB the end of the event loop is far below. Cuts are immediately below
	    ////////////////////////////////////////////////////////////////////////////////////

	    ////////Now check how many fast photons hit each PMT /////

	    //cout << endl << "Analysing event " << evt+1 << "..." << endl;
	    int pmts_with_10fast = 0;
	    int pmts_with_8fast = 0;
	    int pmts_with_6fast = 0;
	    int pmts_with_4fast = 0;

	    for ( int i = 0; i < pmt_times.size(); i++ )
	      {
		
		int sub100ns_photons = 0;
		for ( int j = 0; j < pmt_times[i].size(); j++ )
		  {
		    if(pmt_times[i][j] < cut_time){sub100ns_photons++;}// count how many photons arrive before 100ns on that PMT	  
		  } // end of photon cut loop

		if(sub100ns_photons > 9){pmts_with_10fast++;}
		if(sub100ns_photons > 7){pmts_with_8fast++;}
		if(sub100ns_photons > 5){pmts_with_6fast++;}
		if(sub100ns_photons > 3){pmts_with_4fast++;}

		//cout << "PMT " << i+1 << ":  Total photons " << pmt_times[i].size();
		//cout << "  Sub 100ns photons: " <<  sub100ns_photons <<endl;
		

	      } // end of pmt cut loop

	    //Fill the histograms
	    cut10sn->Fill(pmts_with_10fast);
	    cut8sn->Fill(pmts_with_8fast);
	    cut6sn->Fill(pmts_with_6fast);
	    cut4sn->Fill(pmts_with_4fast);
	    




	    /////////////////////////////////////////////////////////////////////////////////////
	    ///////////////////// CHOOSE BEST CUT AND PLOT THE ENERGY SPECTRUM //////////////////
	    /////////////////////////////////////////////////////////////////////////////////////
	    /////////
	    ///No cut
	    ////////
	    E_cut0sn->Fill(event_Es.at(evt));

	    /////////
	    ///for 10 fast
	    ////////
	    if(pmts_with_10fast >= 8) { E_cut10sn_8pmts->Fill(event_Es.at(evt)); }

	    /////////
	    ///for 8 fast
	    ////////
	    if(pmts_with_8fast >= 15) { E_cut8sn_15pmts->Fill(event_Es.at(evt)); }
	    if(pmts_with_8fast >= 10) { E_cut8sn_10pmts->Fill(event_Es.at(evt)); }      

	    /////////
	    ///for 6 fast
	    ////////
	    if(pmts_with_6fast >= 11) { E_cut6sn_11pmts->Fill(event_Es.at(evt)); }


	    /////////
	    ///for 4 fast
	    ////////
	    if(pmts_with_4fast >= 20) { E_cut4sn_20pmts->Fill(event_Es.at(evt)); }


	    pmt_times.clear();
	  
	    if((evt + 1) % 100 == 0) {cout << "Analysis of event " << evt + 1 << " complete." << endl;} //every 50 events


	  } //end of evt loop


	TFile *output=new TFile("output.root","RECREATE");
   
	output->cd();
	E_cut0sn->Write();

	cut10sn->Write();
	  E_cut10sn_8pmts->Write();


	cut8sn->Write();
	  E_cut8sn_15pmts->Write();
	  E_cut8sn_10pmts->Write();


	cut6sn->Write();
	  E_cut6sn_11pmts->Write();

	
	cut4sn->Write();
      	  E_cut4sn_20pmts->Write();

	output->Close();

	}//end of if SN  == true





	///////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////
	////////////////////////////END OF IF SUPERNOVA////////////////////////
	///////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////




	//NB The loops do the exact same thing, the only difference is that if radon == true it creates 
	//histograms with a rn label as opposed to a sn label, this makes reading in the graphs easier





	if(radon == true){	 

	//////////DECALRE HISTOGRAMS THAT NEED FILLING //////////

	TH1F *E_cut0rn = new TH1F("E_cut0rn","Radon energy spectrum - No cuts",50,5.3,5.8);
	
	TH1F *cut10rn = new TH1F("cut10rn","PMTs with more than 10 fast photons",60,0,60);
	  TH1F *E_cut10rn_8pmts = new TH1F("E_cut10rn_8pmts","Radon energy spectrum - 30 PMTs & 8 fast photon cut",50,5.3,5.8);;

	TH1F *cut8rn = new TH1F("cut8rn","PMTs with more than 8 fast photons",60,0,60);
	  TH1F *E_cut8rn_15pmts = new TH1F("E_cut8rn_15pmts","Radon energy spectrum - 30 PMTs & 15 fast photon cut",50,5.3,5.8);
	  TH1F *E_cut8rn_10pmts = new TH1F("E_cut8rn_10pmts","Radon energy spectrum - 20 PMTs & 10 fast photon cut",50,5.3,5.8);


	TH1F *cut6rn = new TH1F("cut6rn","PMTs with more than 6 fast photons",60,0,60);
	  TH1F *E_cut6rn_11pmts = new TH1F("E_cut6rn_11pmts","Radon energy spectrum - 11 PMTs & 6 fast photon cut",50,5.3,5.8);

	TH1F *cut4rn = new TH1F("cut4rn","PMTs with more than 4 fast photons",60,0,60);
	  TH1F *E_cut4rn_20pmts = new TH1F("E_cut4rn_20pmts","Radon energy spectrum - 20 PMTs & 4 fast photon cut",50,5.3,5.8);       
 
	  int no_of_evts = event_tree1->GetEntries(); //total number of events will be equal to the entires in the event tree 
	  cout << endl << "TEST - # of events: " << no_of_evts << endl;

	  double detected_photons = entries1; // total number of DETECTED photons from ALL events
	  double created_photons;
	  if(supernova == true){created_photons = no_of_evts * 24000;} //24000 is the scint yield of an electron in LAr @ 500 V/cm
	  if(radon == true){created_photons = no_of_evts * 16800;} // 16800 = SY of Alpha in LAr @ 500 V/cm
	  double percent_detected = (detected_photons/created_photons)*100;

	  cout << endl << "For the whole simulation - " << detected_photons << " of " << created_photons << " photons were detected." << endl;
	  cout << "This corresponds to: " << percent_detected << "% of photon detected." << endl << endl;;

	  //create vector of energies
	  vector<double> event_Es;
	  vector<double> evt_x;
	  vector<double> evt_y;
	  vector<double> evt_z;
	  for(int evt = 0; evt < no_of_evts; evt++){
	    event_tree1->GetEntry(evt);
	    event_Es.push_back(event_E);
	    evt_x.push_back(event_xpos);
	    evt_y.push_back(event_ypos);
	    evt_z.push_back(event_zpos);

	    //cout << "Energy of event " << evt+1 << " is: " << event_E << " MeV.";
	    //cout << "\t At position: (" << event_xpos << "," << event_ypos << "," << event_zpos << ")" << endl;
	  }

	  cout << endl << "Energy vector filled..." << endl;
	 


	  ///////////////////////////////////////////////////////////////////////////////////////
	  /////////PHOTON LOOP TO CREATE THE VECTOR OF VECTORS WITH ALL//////////////////////////
	  /////////////PHOTON TIMES ON EACH PMT FOR CURRENT EVENT////////////////////////////////
	  ///////////////////////////////////////////////////////////////////////////////////////
	  cout << endl << "Beginning main loop..." << endl;
	  vector< vector<double> > pmt_times; // Vector of vectors storing the times in each PMT
	  vector<double> hit_times;
	  int current_entry = 0;
	  for(int evt = 0; evt < no_of_evts; evt++){

	  int current_pmt_entry  = 0;
	    for(int pmt_no  = 0; pmt_no < 60; pmt_no++){
	   

	      for(int i = current_entry; i < entries1; i++){	      
		data_tree1->GetEntry(i);
	      
		//fill a normal vector	    
		if(data_pmt1 == realisticPMT_IDs[pmt_no] && data_event1 == evt ) //the pmt the photon hit is the pmt we're on in the current iteration
		  {
		    hit_times.push_back(data_time1); //fill a vector with all the photon times from event "evt" which hit pmt "pmt_no" 		  
		  }
	      
		if(data_event1 > evt) {
		  current_pmt_entry = i;
		  		  
		  break;
		}
		
	      
	      } // end of entry (photon) loop
	     

	      pmt_times.push_back(hit_times); //fill the pmts vector with the times from that event hitting that pmt
	      hit_times.clear();  // clear the vector      
	    
	    } // end of pmt loop
	    current_entry = current_pmt_entry;

	    ////////////////////////////////////////////////////////////////////////////////////
	    /////////////////TESTING THE OUTPUT OF THE VECTOR OF VECTORS////////////////////////
	    ////////////////////////////////////////////////////////////////////////////////////

	    /*
	      cout << "Event " << evt + 1 << "\tEnergy: " << event_Es[evt];
	      cout << " MeV \tPosition: (" << evt_x[evt] << "," << evt_y[evt] << "," << evt_z[evt] <<")";
	    */


	    /*
	    // CHECK HOW MANY PHOTONS IN AN EVENT (need to modify the evt loop to one iteration)
	    int evt_photons = 0;
	    for(int i = 0; i < 60; i++){
	    evt_photons += pmt_times[i].size();
	    }
	    */
    
	    //cout << endl << endl << "Total no of photons from evt: " << evt_photons << endl;


	    ////////////////////////////////////////////////////////////////////////////////////
	    //NB the end of the event loop is far below. Cuts are immediately below
	    ////////////////////////////////////////////////////////////////////////////////////

	    ////////Now check how many fast photons hit each PMT /////

	    //cout << endl << "Analysing event " << evt+1 << "..." << endl;
	    int pmts_with_10fast = 0;
	    int pmts_with_8fast = 0;
	    int pmts_with_6fast = 0;
	    int pmts_with_4fast = 0;

	    

	    for ( int i = 0; i < pmt_times.size(); i++ )
	      {
		
		int sub100ns_photons = 0;
		for ( int j = 0; j < pmt_times[i].size(); j++ )
		  {
		    if(pmt_times[i][j] < cut_time){sub100ns_photons++;}// count how many photons arrive before 100ns on that PMT	  
		  } // end of photon cut loop

		if(sub100ns_photons > 9){pmts_with_10fast++;}
		if(sub100ns_photons > 7){pmts_with_8fast++;}
		if(sub100ns_photons > 5){pmts_with_6fast++;}
		if(sub100ns_photons > 3){pmts_with_4fast++;}

		//cout << "PMT " << i+1 << ":  Total photons " << pmt_times[i].size();
		//cout << "  Sub 100ns photons: " <<  sub100ns_photons <<endl;
		

	      } // end of pmt cut loop

	    //Fill the histograms
	    cut10rn->Fill(pmts_with_10fast);
	    cut8rn->Fill(pmts_with_8fast);
	    cut6rn->Fill(pmts_with_6fast);
	    cut4rn->Fill(pmts_with_4fast);
	    

	     

	    /////////////////////////////////////////////////////////////////////////////////////
	    ///////////////////// CHOOSE BEST CUT AND FILL THE ENERGY HISTS // //////////////////
	    /////////////////////////////////////////////////////////////////////////////////////	    
	    /////////
	    ///No cut
	    ////////
	    E_cut0rn->Fill(event_Es.at(evt));


	    /////////
	    ///for 10 fast
	    ////////
	    if(pmts_with_10fast >= 8) { E_cut10rn_8pmts->Fill(event_Es.at(evt)); }

	    /////////
	    ///for 8 fast
	    ////////
	    if(pmts_with_8fast >= 15) { E_cut8rn_15pmts->Fill(event_Es.at(evt)); }
	    if(pmts_with_8fast >= 10) { E_cut8rn_10pmts->Fill(event_Es.at(evt)); }

	    /////////
	    ///for 6 fast
	    ////////
	    if(pmts_with_6fast >= 11) { E_cut6rn_11pmts->Fill(event_Es.at(evt)); }

	    /////////
	    ///for 4 fast
	    ////////
	    if(pmts_with_4fast >= 20) { E_cut4rn_20pmts->Fill(event_Es.at(evt)); }


	    //cout << "Size of pmt_times is: " << pmt_times.size() << endl;
	    pmt_times.clear();
	  
	    if((evt + 1) % 100 == 0) {cout << "Analysis of event " << evt + 1 << " complete." << endl;} //every 50 events


	  } //end of evt loop


	TFile *output=new TFile("output.root","RECREATE");
   
	output->cd();

	E_cut0rn->Write();

	cut10rn->Write();
	  E_cut10rn_8pmts->Write();

	cut8rn->Write();
	  E_cut8rn_15pmts->Write();
	  E_cut8rn_10pmts->Write();

	cut6rn->Write();
	  E_cut6rn_11pmts->Write();

	cut4rn->Write();
	  E_cut4rn_20pmts->Write();

	output->Close();

	}//end of if radon  == true












	return 0;

}//end main























