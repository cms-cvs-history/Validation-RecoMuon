TF1* gaus;
int gNHist;
int gRebinX = 1, gRebinY = 1;
double gMeanMin, gMeanMax, gResoMin, gResoMax;
TLegend* gLegend;

void DrawRes()
{
  gStyle->SetOptStat(0);
  gInterpreter->LoadMacro("libValidation.C");

  TF1* fGauss = new TF1("gaus", "gaus", -10, 10);
  gaus = fGauss;

  gRebinY = 1;
  gMeanMin = -2.0; gMeanMax = 2.0; 
  gResoMin = 0.05; gResoMax = 20.0;
  DrawFitHisto("Sta", "+");
  DrawFitHisto("Sta", "-");

  gRebinY = 1;
  gMeanMin = -0.2; gMeanMax = 0.2; 
  gResoMin = 0.005; gResoMax = 2.0;
  DrawFitHisto("Glb", "+");
  DrawFitHisto("Glb", "-");

  fGauss->Delete();
}

void DrawFitHisto(TString type, TString charge)
{
  gNHist = 1;
  TString name = type+(charge=="+"?"Plus":"Minus");
  TCanvas* cMean = new TCanvas(name+"MeanCanvas", type+"Muon "+charge+" Mean sigma(q/pT)", 1024, 768);
  TCanvas* cReso = new TCanvas(name+"ResoCanvas", type+"Muon "+charge+" Resolution sigma(q/pT)", 1024, 768);
  TCanvas* cChi2 = new TCanvas(name+"Chi2Canvas", type+"Muon "+charge+" sigma(q/pT) Fit Chi2", 1024, 768);

  cMean->SetGridx(); cMean->SetGridy(); 
  cReso->SetGridx(); cReso->SetGridy(); 
  cChi2->SetGridx(); cChi2->SetGridy(); 
  cReso->SetLogy();

  gLegend = new TLegend(.85, .85, 1.0, 1.0, "");

  DrawFitSlice("Mu"+charge+"Pt10"  , type, cMean, cReso, cChi2);
  DrawFitSlice("Mu"+charge+"Pt50"  , type, cMean, cReso, cChi2);
  DrawFitSlice("Mu"+charge+"Pt100" , type, cMean, cReso, cChi2);
  DrawFitSlice("Mu"+charge+"Pt500" , type, cMean, cReso, cChi2);
  DrawFitSlice("Mu"+charge+"Pt1000", type, cMean, cReso, cChi2);

  cMean->cd(); gLegend->Draw("same");
  cReso->cd(); gLegend->Draw("same");
  cChi2->cd(); gLegend->Draw("same");

  cMean->Print(TString("plots/QPtMean")+name+".gif");
  cReso->Print(TString("plots/QPtReso")+name+".gif");
  cChi2->Print(TString("plots/QPtChi2")+name+".gif");

  //gLegend->Delete();
  //cMean->Delete();
  //cReso->Delete();
  //cChi2->Delete();
}

void DrawFitSlice(TString dataName, TString muonType, 
                  TCanvas* cMean, TCanvas* cReso, TCanvas* cChi2)
{
  TString drawOpt(TString("E1X0") + (gNHist==1 ? "":"same"));

  TFile file(dataName+".root"); file.cd();
  TH2F* resHist = (TH2F*)file.Get(muonType+"EtaVsErrQPt"); 
  resHist->Rebin2D(gRebinX, gRebinY);
  const int nBinsX = resHist->GetNbinsX();
  const double xMin = resHist->GetBinCenter(0);
  const double xMax = resHist->GetBinCenter(nBinsX);

  if ( gaus ) gaus->SetParameters(1.0, 0.0, resHist->GetYaxis()->GetXmin(), resHist->GetYaxis()->GetXmax());
  if ( gaus ) gaus->SetRange(xMin, xMax); 

  gROOT->cd(); TDirectory dir("dir", "dir"); dir.cd();
  resHist->FitSlicesY(gaus);

  gROOT->cd();
  TH1F* fitMean = (TH1F*)dir.Get(muonType+"EtaVsErrQPt_1")->Clone();
  TH1F* fitReso = (TH1F*)dir.Get(muonType+"EtaVsErrQPt_2")->Clone();
  TH1F* fitChi2 = (TH1F*)dir.Get(muonType+"EtaVsErrQPt_chi2")->Clone();

  fitMean->SetTitle(muonType+"Muon #sigma(q/p_{T}) mean");
  fitReso->SetTitle(muonType+"Muon Resolution #sigma(q/p_{T})");

  fitMean->GetXaxis()->SetTitle("Psuedorapidity #eta"); fitMean->GetYaxis()->SetTitle("Mean #sigma(q/p_{T})");
  fitReso->GetXaxis()->SetTitle("Psuedorapidity #eta"); fitReso->GetYaxis()->SetTitle("Mean #sigma(q/p_{T})");

  cMean->cd(); 
  fitMean->SetMinimum(gMeanMin); fitMean->SetMaximum(gMeanMax); 
  fitMean->SetLineColor(gNHist); 
  fitMean->Draw(drawOpt);

  cReso->cd(); 
  fitReso->SetMinimum(gResoMin); fitReso->SetMaximum(gResoMax); 
  fitReso->SetLineColor(gNHist); 
  fitReso->Draw(drawOpt);
  ConnectLines(fitReso, dataName+muonType);

  cChi2->cd();
  fitChi2->SetLineColor(gNHist);
  fitChi2->Draw(drawOpt);
//  TCanvas* c = new TCanvas(muonType+muonType+"FitChi2Canvas");
//  c->cd(); fitChi2->Draw(); c->Print(TString("plots/QPtChi2")+dataName+muonType+".gif");

  if ( ++gNHist==kYellow ) gNHist++;

  file.Close();
}

