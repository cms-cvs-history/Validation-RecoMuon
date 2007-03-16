void DrawMisQ()
{
  gInterpreter->LoadMacro("libValidation.C");
  gStyle->SetOptStat(0);

  TCanvas* c;

  gLineColor = 1;
  gLegend = new TLegend(.85, .15, 1.0, .30, "");
  c = new TCanvas("cSeedMinusMisQ", "Seed Charge MisIdentification", 1024, 768);
  c->cd(); c->SetGridx(); c->SetGridy(); c->SetLogy();
  DrawMisQ("Mu-Pt10"  , "Seed");
  DrawMisQ("Mu-Pt50"  , "Seed");
  DrawMisQ("Mu-Pt100" , "Seed");
  DrawMisQ("Mu-Pt500" , "Seed");
  DrawMisQ("Mu-Pt1000", "Seed");
  gLegend->Draw("same");
  c->Print("plots/MisQSeedMinus.gif");

  gLineColor = 1;
  gLegend = new TLegend(.85, .15, 1.0, .30, "");
  c = new TCanvas("cSeedPlusMisQ", "Seed Charge MisIdentification", 1024, 768);
  c->cd(); c->SetGridx(); c->SetGridy(); c->SetLogy();
  DrawMisQ("Mu+Pt10"  , "Seed");
  DrawMisQ("Mu+Pt50"  , "Seed");
  DrawMisQ("Mu+Pt100" , "Seed");
  DrawMisQ("Mu+Pt500" , "Seed");
  DrawMisQ("Mu+Pt1000", "Seed");
  gLegend->Draw("same");
  c->Print("plots/MisQSeedPlus.gif");

  gLineColor = 1;
  gLegend = new TLegend(.85, .15, 1.0, .30, "");
  c = new TCanvas("cStaMinusMisQ", "StaMuon Charge MisIdentification", 1024, 768);
  c->cd(); c->SetGridx(); c->SetGridy(); c->SetLogy();
  DrawMisQ("Mu-Pt10"  , "Sta");
  DrawMisQ("Mu-Pt50"  , "Sta");
  DrawMisQ("Mu-Pt100" , "Sta");
  DrawMisQ("Mu-Pt500" , "Sta");
  DrawMisQ("Mu-Pt1000", "Sta");
  gLegend->Draw("same");
  c->Print("plots/MisQStaMinus.gif");
  
  gLineColor = 1;
  gLegend = new TLegend(.85, .15, 1.0, .30, "");
  c = new TCanvas("cStaPlusMisQ", "StaMuon Charge MisIdentification", 1024, 768);
  c->cd(); c->SetGridx(); c->SetGridy(); c->SetLogy();
  DrawMisQ("Mu+Pt10"  , "Sta");
  DrawMisQ("Mu+Pt50"  , "Sta");
  DrawMisQ("Mu+Pt100" , "Sta");
  DrawMisQ("Mu+Pt500" , "Sta");
  DrawMisQ("Mu+Pt1000", "Sta");
  gLegend->Draw("same");
  c->Print("plots/MisQStaPlus.gif");
  
  gLineColor = 1;
  gLegend = new TLegend(.85, .15, 1.0, .30, "");
  c = new TCanvas("cGlbMinusMisQ", "GlbMuon Charge MisIdentification", 1024, 768);
  c->cd(); c->SetGridx(); c->SetGridy(); c->SetLogy();
  DrawMisQ("Mu-Pt10"  , "Glb");
  DrawMisQ("Mu-Pt50"  , "Glb");
  DrawMisQ("Mu-Pt100" , "Glb");
  DrawMisQ("Mu-Pt500" , "Glb");
  DrawMisQ("Mu-Pt1000", "Glb");
  gLegend->Draw("same");
  c->Print("plots/MisQGlbMinus.gif");
  
  gLineColor = 1;
  gLegend = new TLegend(.85, .15, 1.0, .30, "");
  c = new TCanvas("cGlbPlusMisQ", "GlbMuon Charge MisIdentification", 1024, 768);
  c->cd(); c->SetGridx(); c->SetGridy(); c->SetLogy();
  DrawMisQ("Mu+Pt10"  , "Glb");
  DrawMisQ("Mu+Pt50"  , "Glb");
  DrawMisQ("Mu+Pt100" , "Glb");
  DrawMisQ("Mu+Pt500" , "Glb");
  DrawMisQ("Mu+Pt1000", "Glb");
  gLegend->Draw("same");
  c->Print("plots/MisQGlbPlus.gif");
}

void DrawMisQ(TString sampleName, TString muonType)
{
  TFile file(sampleName+".root"); file.cd();

  TH1F* hMisQ = (TH1F*)file.Get(muonType+"MisQAboutEta");
  TH1F* hRec  = (TH1F*)((TH2F*)file.Get(muonType+"EtaVsPhi"))->ProjectionX();

  hMisQ->Sumw2();
  hRec->Sumw2();

  gROOT->cd();
  TH1F* his  = new TH1F(sampleName+muonType+"MisQ", sampleName+muonType+"Muon Charge Misidentification",
                        hRec->GetNbinsX(), hRec->GetXaxis()->GetXmin(), hRec->GetXaxis()->GetXmax());

  his->Divide(hMisQ, hRec, 1, 1, "B");
  his->SetMinimum(1E-4); his->SetMaximum(1.0);

  his->SetTitle(muonType+" Charge MisID rate");
  his->GetXaxis()->SetTitle("Psuedorapidity #eta");
  his->GetYaxis()->SetTitle("Charge Misidentification rate");
  his->SetLineColor(gLineColor);
  his->Draw(TString("E1X0")+(gLineColor==1?"":"same"));
  ConnectLines(his, sampleName);

  if ( ++gLineColor==kYellow ) gLineColor++;
  file.Close();
}

