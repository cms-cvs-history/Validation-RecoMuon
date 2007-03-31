bool gDoFolding = false;

void DrawEff(bool doFolding = false)
{
  gInterpreter->LoadMacro("libValidation.C");
  gStyle->SetOptStat(0);
  gDoFolding = doFolding;
   
  TCanvas* c1 = new TCanvas("StaSeedEff", 
			   "Sta and Seed Efficiencies", 1024, 768);
  c1->Divide(3,1);
  
  DrawEff("Seed","Sim",c1->cd(1));
  DrawEff("Sta","Sim",c1->cd(2));
  DrawEff("Sta","Seed",c1->cd(3));

  TCanvas* c2 = new TCanvas("GlbEff", 
			    "Glb Efficiencies", 1024, 768);
  c2->Divide(4,1);

  DrawEff("Glb","Sim",c2->cd(1));
  DrawEff("Glb","Tk",c2->cd(2));
  DrawEff("Glb","Sta",c2->cd(3));
  DrawEff("Glb","Seed",c2->cd(4));
}

void DrawEff(TString sampleName, TString muonType1, TString muonType2)
{

  TFile file("../data/RootHisto_200703301524/"+sampleName+".root"); file.cd();

  if(!file.IsOpen()) return;
  
  TH1F* hRec = (TH1F*)((TH2F*)file.Get(muonType1+"EtaVsPhi"))->ProjectionX();
  TH1F* hSim = (TH1F*)((TH2F*)file.Get(muonType2+"EtaVsPhi"))->ProjectionX();

  if ( gDoFolding ) {
    hRec = FoldH1(hRec);
    hSim = FoldH1(hSim);
  }
 
  hRec->Sumw2();
  hSim->Sumw2();

  gROOT->cd();
  TH1F* his  = new TH1F(sampleName+muonType1+muonType2+"his", sampleName+muonType1+muonType2, 
                        hRec->GetNbinsX(), hRec->GetXaxis()->GetXmin(), hRec->GetXaxis()->GetXmax()); 

  his->Divide(hRec, hSim, 1, 1, "B");
  his->SetMinimum(0.8); his->SetMaximum(1.0);

  his->SetTitle(muonType1+muonType2+" Muon Efficiency");
  his->GetXaxis()->SetTitle("Psuedorapidity #eta");
  his->GetYaxis()->SetTitle("Efficiency"); 
  his->SetLineColor(gLineColor);
  his->Draw(TString("E1X0")+(gLineColor==1?"":"same"));
  ConnectLines(his, sampleName);

  if ( ++gLineColor==kYellow ) gLineColor++;
  file.Close();
}


void DrawEff(TString muonStep2, TString muonStep1,TVirtualPad* pad){
  pad->Divide(1,2);
  pad->cd(1);
  pad->SetGridx(); pad->SetGridy();

  //   TCanvas* c;
  //   c = new TCanvas(muonStep2+muonStep1+"Eff_MuPlus", 
  // 		  muonStep2+"-"+muonStep1+" Efficiency for #mu^{+}", 1024, 768);
  //   c->cd(); c->SetGridx(); c->SetGridy();
  
  gLineColor = 1;
  gLegend = new TLegend(.85, .15, 1.0, .30, "");

  DrawEff("Mu+Pt10"  , muonStep2, muonStep1);
  DrawEff("Mu+Pt50"  , muonStep2, muonStep1);
  DrawEff("Mu+Pt100" , muonStep2, muonStep1);
  DrawEff("Mu+Pt500" , muonStep2, muonStep1);
  DrawEff("Mu+Pt1000", muonStep2, muonStep1);
  gLegend->Draw("same");
  pad->Print("plots/Eff_"+muonStep2+"_"+muonStep1+"_MuPlus.gif");


  gLineColor = 1;
  gLegend = new TLegend(.85, .15, 1.0, .30, "");
  //   c = new TCanvas(muonStep2+muonStep1+"Eff_MuMinus", 
  // 		  muonStep2+"-"+muonStep1+" Efficiency for #mu^{-}", 1024, 768);
  //   c->cd(); c->SetGridx(); c->SetGridy();
  
  pad->cd(2);
  DrawEff("Mu-Pt10"  , muonStep2, muonStep1);
  DrawEff("Mu-Pt50"  , muonStep2, muonStep1);
  DrawEff("Mu-Pt100" , muonStep2, muonStep1);
  DrawEff("Mu-Pt500" , muonStep2, muonStep1);
  DrawEff("Mu-Pt1000", muonStep2, muonStep1);
  gLegend->Draw("same");
  pad->Print("plots/Eff_"+muonStep2+"_"+muonStep1+"_MuMinus.gif");
}
