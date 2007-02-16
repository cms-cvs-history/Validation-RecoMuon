bool gDoFolding = false;

void DrawEff(bool doFolding = false)
{
  gInterpreter->LoadMacro("libValidation.C");
  gStyle->SetOptStat(0);
  gDoFolding = doFolding;

  TCanvas* c;

  gNHist = 1;
  gLegend = new TLegend(.85, .15, 1.0, .30, "");
  c = new TCanvas("cStaMinusEff", "StaMuon Minus Efficiency", 1024, 768); 
  c->cd(); c->SetGridx(); c->SetGridy();
  DrawEff("Mu-Pt10"  , "Sta", "Sim");
  DrawEff("Mu-Pt50"  , "Sta", "Sim");
  DrawEff("Mu-Pt100" , "Sta", "Sim");
  DrawEff("Mu-Pt500" , "Sta", "Sim");
  DrawEff("Mu-Pt1000", "Sta", "Sim");
  gLegend->Draw("same");
  c->Print("plots/EffStaMinus.gif");

  gNHist = 1;
  gLegend = new TLegend(.85, .15, 1.0, .30, "");
  c = new TCanvas("cStaPlusEff", "StaMuon Plus Efficiency", 1024, 768); 
  c->cd(); c->SetGridx(); c->SetGridy();
  DrawEff("Mu+Pt10"  , "Sta", "Sim");
  DrawEff("Mu+Pt50"  , "Sta", "Sim");
  DrawEff("Mu+Pt100" , "Sta", "Sim");
  DrawEff("Mu+Pt500" , "Sta", "Sim");
  DrawEff("Mu+Pt1000", "Sta", "Sim");
  gLegend->Draw("same");
  c->Print("plots/EffStaPlus.gif");

  gNHist = 1;
  gLegend = new TLegend(.85, .15, 1.0, .30, "");
  c = new TCanvas("cGlbMinusEff", "GlbMuon Minus Efficiency", 1024, 768); 
  c->cd(); c->SetGridx(); c->SetGridy();
  DrawEff("Mu-Pt10"  , "Glb", "Sim");
  DrawEff("Mu-Pt50"  , "Glb", "Sim");
  DrawEff("Mu-Pt100" , "Glb", "Sim");
  DrawEff("Mu-Pt500" , "Glb", "Sim");
  DrawEff("Mu-Pt1000", "Glb", "Sim");
  gLegend->Draw("same");
  c->Print("plots/EffGlbMinus.gif");
 
  gNHist = 1;
  gLegend = new TLegend(.85, .15, 1.0, .30, "");
  c = new TCanvas("cGlbPlusEff", "GlbMuon Minus Efficiency", 1024, 768); 
  c->cd(); c->SetGridx(); c->SetGridy();
  DrawEff("Mu+Pt10"  , "Glb", "Sim");
  DrawEff("Mu+Pt50"  , "Glb", "Sim");
  DrawEff("Mu+Pt100" , "Glb", "Sim");
  DrawEff("Mu+Pt500" , "Glb", "Sim");
  DrawEff("Mu+Pt1000", "Glb", "Sim");
  gLegend->Draw("same");
  c->Print("plots/EffGlbPlus.gif");

  gNHist = 1;
  gLegend = new TLegend(.85, .15, 1.0, .30, "");
  c = new TCanvas("cGlbStaMinusEff", "GlbMuon/StaMuon Minus Efficiency", 1024, 768); 
  c->cd(); c->SetGridx(); c->SetGridy();
  DrawEff("Mu-Pt10"  , "Glb", "Sta");
  DrawEff("Mu-Pt50"  , "Glb", "Sta");
  DrawEff("Mu-Pt100" , "Glb", "Sta");
  DrawEff("Mu-Pt500" , "Glb", "Sta");
  DrawEff("Mu-Pt1000", "Glb", "Sta");
  gLegend->Draw("same");
  c->Print("plots/EffGlbStaMinus.gif");
                                   
  gNHist = 1;
  gLegend = new TLegend(.85, .15, 1.0, .30, "");
  c = new TCanvas("cGlbStaPlusEff", "GlbMuon/StaMuon Plus Efficiency", 1024, 768); 
  c->cd(); c->SetGridx(); c->SetGridy();
  DrawEff("Mu+Pt10"  , "Glb", "Sta");
  DrawEff("Mu+Pt50"  , "Glb", "Sta");
  DrawEff("Mu+Pt100" , "Glb", "Sta");
  DrawEff("Mu+Pt500" , "Glb", "Sta");
  DrawEff("Mu+Pt1000", "Glb", "Sta");
  gLegend->Draw("same");
  c->Print("plots/EffGlbStaPlus.gif");
  
}

void DrawEff(TString sampleName, TString muonType1, TString muonType2)
{

  TFile file(sampleName+".root"); file.cd();

  TH1F* hRec = (TH1F*)((TH2F*)file.Get(muonType1+"PhiVsEtaHist"))->ProjectionY();
  TH1F* hSim = (TH1F*)((TH2F*)file.Get(muonType2+"PhiVsEtaHist"))->ProjectionY();

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
  his->SetLineColor(gNHist);
  his->Draw(TString("E1X0")+(gNHist==1?"":"same"));
  ConnectLines(his, sampleName);

  if ( ++gNHist==kYellow ) gNHist++;
  file.Close();
}

