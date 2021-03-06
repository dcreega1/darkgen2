  
#include "tdrstyle.C"
#include "CMS_lumi.C"
#include "TH1.h"
#include "TH1F.h"

int dolog=0;
void species() 
{ 
  TFile *f1 = new TFile("res.root");
  TFile *f2 = new TFile("nonres.root");  

 
  gStyle->SetOptStat(0);
 
  TString canvName = "Fig_";
  canvName += "hptdp_A_B";
  
  if( writeExtraText ) canvName += "-prelim";
  //if( iPos%10==0 ) canvName += "-out";
  //else if( iPos%10==1 ) canvName += "-left";
  //else if( iPos%10==2 )  canvName += "-center";
  //else if( iPos%10==3 )  canvName += "-right";
  int W = 800;
  int H = 600;
  TCanvas* canv = new TCanvas(canvName,canvName,50,50,W,H);
  // references for T, B, L, R
  float T = 0.08*H;
  float B = 0.12*H; 
  float L = 0.12*W;
  float R = 0.04*W;
  
  //canv = new TCanvas(canvName,canvName,50,50,W,H);
  canv->SetFillColor(0);
  canv->SetBorderMode(0);
  canv->SetFrameFillStyle(0);
  canv->SetFrameBorderMode(0);
  canv->SetLeftMargin( L/W );
  canv->SetRightMargin( R/W );
  canv->SetTopMargin( T/H );
  canv->SetBottomMargin( B/H );
  canv->SetTickx(0);
  canv->SetTicky(0);
  
  if (dolog) canv->SetLogy();

  //TH1* h_pt = new TH1F("h_pt"," ",100,0,500);
  //h_pt->GetXaxis()->SetNdivisions(6,5,0);
  //h_pt->GetXaxis()->SetTitle("Dark Pion p_{T} (GeV)");  
  //h_pt->GetXaxis()->SetTitleSize(0.05);  
  //h_pt->GetYaxis()->SetNdivisions(6,5,0);
  //h_pt->GetYaxis()->SetTitleOffset(1);
  //h_pt->GetYaxis()->SetTitle("Events / 5 GeV");  
  //h_pt->GetYaxis()->SetTitleSize(0.05);  
  
  //int max=  test->GetMaximum() + test->GetMaximum()*0.2; 
  //int max=  2000.;
  //h_pt->SetMaximum(max);
  //cout << max << endl;
 
  //h_pt->Draw();
  
  // int histLineColor = kOrange+7;
  //int histFillColor = kOrange-2;
  //float markerSize  = 1.0;

  TLatex latex;
  
  int n_ = 2;
  
  float x1_l = 0.75;
  float y1_l = 0.90;
  
  float dx_l = 0.60;
  float dy_l = 0.1;
  float x0_l = x1_l-dx_l;
  float y0_l = y1_l-dy_l;
  
 TLegend *lgd = new TLegend(x0_l,y0_l,x1_l, y1_l); 
  lgd->SetBorderSize(0); lgd->SetTextSize(0.04); lgd->SetTextFont(62); lgd->SetFillColor(0);


  
  TH1F *A_cnt = static_cast<TH1F*>(f1->Get("hmapt")->Clone());
  A_cnt->SetDirectory(0);
  float aaA = A_cnt->GetEntries();
  cout<<" number of dark pions for A is "<<aaA<<endl;
  TH1F *A_pt = static_cast<TH1F*>(f1->Get("hdecays2")->Clone());
  A_pt->SetDirectory(0);
  A_pt->Scale(1./aaA);

  TH1F *B_cnt = static_cast<TH1F*>(f2->Get("hmapt")->Clone());
  B_cnt->SetDirectory(0);
  float aaB = B_cnt->GetEntries();
  cout<<" number of dark pions for B is "<<aaB<<endl;
  TH1F *B_pt = static_cast<TH1F*>(f2->Get("hdecays2")->Clone());
  B_pt->SetDirectory(0);
  B_pt->Scale(1./aaB);

  float max = std::max(A_pt->GetMaximum(),B_pt->GetMaximum());
    A_pt->SetMaximum(max*1.3);

  A_pt->GetYaxis()->SetTitle("mean per decay");  
  A_pt->GetYaxis()->SetTitleSize(0.05);  



  A_pt->SetLineColor(3);
  A_pt->SetLineWidth(3);
  A_pt->SetStats(0);
  A_pt->Draw("");


  

  B_pt->SetLineColor(2);
  B_pt->SetLineWidth(3);
  B_pt->SetStats(0);
  
  B_pt->Draw("same");




 
 lgd->AddEntry(A_pt, "dark pion 5 GeV, resonant decay", "l");
 lgd->AddEntry(B_pt, "non resonant decay", "l");
 lgd->Draw();
    // Writing the lumi information and the CMS "logo"
   // second parameter in example_plot is iPos, which drives the position of the CMS logo in the plot
  // iPos=11 : top-left, left-aligned
  // iPos=33 : top-right, right-aligned
  // iPos=22 : center, centered
  // mode generally : 
  //   iPos = 10*(alignement 1/2/3) + position (1/2/3 = left/center/right)
   
  writeExtraText = true;       // if extra text
  //  extraText  = "Preliminary";  // default extra text is "Preliminary"

  int iPeriod = 0;    // 1=7TeV, 2=8TeV, 3=7+8TeV, 7=7+8+13TeV, 0=free form (uses lumi_sqrtS)
   int iPos  = 11;
   //  CMS_lumi( canv, iPeriod, iPos );
  
  canv->Update();
  canv->RedrawAxis();
  canv->GetFrame()->Draw();
  lgd->Draw();

 
  if (dolog) {
    canv->Print(canvName+"_log.pdf",".pdf");
    canv->Print(canvName+"_log.png",".png");}
  else{ 
    canv->Print(canvName+".pdf",".pdf");
    canv->Print(canvName+".png",".png");}
  return;
}


