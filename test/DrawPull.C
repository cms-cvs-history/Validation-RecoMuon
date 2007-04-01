TLegend* gLegend;

TString gSampleLoc;

void DrawPull(TString sampleLoc)
{
  gSampleLoc = sampleLoc;

  gStyle->SetPalette(1);
  gStyle->SetOptStat(0);
  gInterpreter->LoadMacro("libValidation.C");

  DrawPull2DHists("Pt10"  );
  DrawPull2DHists("Pt50"  );
  DrawPull2DHists("Pt100" );
  DrawPull2DHists("Pt500" );
  DrawPull2DHists("Pt1000");

  gChi2Max = 10;

  gMeanMax = 3; gWidthMin = 0; gWidthMax = 5;
  DrawFitHisto("Seed", "EtaVsPullPt", "+", "plots/PullPt");
  DrawFitHisto("Seed", "EtaVsPullPt", "-", "plots/PullPt");

  DrawFitHisto("Sta" , "EtaVsPullPt", "+", "plots/PullPt");
  DrawFitHisto("Sta" , "EtaVsPullPt", "-", "plots/PullPt");

  DrawFitHisto("Glb" , "EtaVsPullPt", "+", "plots/PullPt");
  DrawFitHisto("Glb" , "EtaVsPullPt", "-", "plots/PullPt");
}

void DrawFitHisto(TString muonType, TString histoName, TString charge, TString prefix)
{
  gLineColor = 1;
  TString name = muonType + (charge=="+"?"Plus":"Minus");
  TCanvas* cMean  = new TCanvas(name+"MeanCanvas", histoName+"Muon "+charge+" Mean Pull p_{T}", 1024, 768);
  TCanvas* cWidth = new TCanvas(name+"PullCanvas", histoName+"Muon "+charge+" Width Pull p_{T}", 1024, 768);
  TCanvas* cChi2  = new TCanvas(name+"Chi2Canvas", histoName+"Muon "+charge+" Pull Gaussian Fit Chi2", 1024, 768);

  cMean ->SetGridx(); cMean ->SetGridy(); 
  cWidth->SetGridx(); cWidth->SetGridy(); 
  cChi2 ->SetGridx(); cChi2 ->SetGridy(); 
//  cWidth->SetLogy();

  gLegend = new TLegend(.85, .85, 1.0, 1.0, "");

  DrawFitSlice(gSampleLoc+"Mu"+charge+"Pt10"  , muonType, histoName, cMean, cWidth, cChi2);
  DrawFitSlice(gSampleLoc+"Mu"+charge+"Pt50"  , muonType, histoName, cMean, cWidth, cChi2);
  DrawFitSlice(gSampleLoc+"Mu"+charge+"Pt100" , muonType, histoName, cMean, cWidth, cChi2);
  DrawFitSlice(gSampleLoc+"Mu"+charge+"Pt500" , muonType, histoName, cMean, cWidth, cChi2);
  DrawFitSlice(gSampleLoc+"Mu"+charge+"Pt1000", muonType, histoName, cMean, cWidth, cChi2);

  cMean ->cd(); gLegend->Draw("same");
  cWidth->cd(); gLegend->Draw("same");
  cChi2 ->cd(); gLegend->Draw("same");

  cMean ->Print(prefix+"Mean"+name+".gif");
  cWidth->Print(prefix+"Pull"+name+".gif");
  cChi2 ->Print(prefix+"Chi2"+name+".gif");
}

void DrawPull2DHists(TString sample)
{
  TCanvas* c = new TCanvas(sample+"Canvas", sample+" sigma(q/pT)", 1024, 768);
  c->Divide(2,3);

  DrawPullVsEta(gSampleLoc+TString("Mu+")+sample, "Seed", c->cd(1));
  DrawPullVsEta(gSampleLoc+TString("Mu-")+sample, "Seed", c->cd(2));
  DrawPullVsEta(gSampleLoc+TString("Mu+")+sample, "Sta" , c->cd(3));
  DrawPullVsEta(gSampleLoc+TString("Mu-")+sample, "Sta" , c->cd(4));
  DrawPullVsEta(gSampleLoc+TString("Mu+")+sample, "Glb" , c->cd(5));
  DrawPullVsEta(gSampleLoc+TString("Mu-")+sample, "Glb" , c->cd(6));

  c->Print(TString("plots/Pull2DMu")+sample+".gif");
}

void DrawPullVsEta(TString sampleName, TString muonType, TVirtualPad* pad)
{
  pad->SetGridx(); pad->SetGridy();
  TFile file(sampleName+".root"); file.cd();

  gROOT->cd();
  TH2F* his = (TH2F*)(file.Get(muonType+"EtaVsPullPt")->Clone());
  his->Rebin2D(1,2);

  his->SetTitle(sampleName+muonType+" Muon #eta vs Pull p_{T}");
  his->GetXaxis()->SetTitle("Psuedorapidity #eta");
  his->GetYaxis()->SetTitle("Pull");
  his->Draw("COLZ");

  file.Close();
}

