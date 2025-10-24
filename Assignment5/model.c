#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include <math.h>
#include "model.h"

void initializeNode(Node* ptrmysinglenode)
{
	ptrmysinglenode->v=-94.7;
	ptrmysinglenode->cai=0.0472;
	ptrmysinglenode->casr=320.0;
	ptrmysinglenode->f=1.0;
	ptrmysinglenode->d=0.0;
	ptrmysinglenode->m=0.0;
	ptrmysinglenode->h=1.0;
	ptrmysinglenode->j=1.0;
	ptrmysinglenode->fca=1.0;
	ptrmysinglenode->kr=0.0;
	ptrmysinglenode->ks=0.0;
	ptrmysinglenode->xto=0.0;
	ptrmysinglenode->yto=1.0;
}

void updateNode(Node* mynode, Node* mynodenew, double diffusionValue)
{
// parameter values
	double gna = 12.8;
	double gk1 = 2.8;
	double gkr = 0.0136;
	double gks = 0.0245;
	double gkp = 0.002216;
	double gto = 0.23815;
	double gnab = 0.0031;
	double gcab = 0.0003842;
	double pca = 0.0000226;
	double pcak = 5.79e-7;
	double prel = 6.0;
	double pleak = 0.000001;
	double inakbar = 0.693;
	double icahalfbar = -0.265;
	double ipcabar = 0.05;
	double rr = 8.314;
	double tt = 310.0;
	double ff = 96.5;
	double acap = 1.534e-4;
	double csc = 1.0;
	double eta = 0.35;
	double xksat = 0.2;
	double xknaca = 1500.0;
	double xkmfca = 0.18;
	double xkmk1 = 13.0;
	double xkmna = 87.5;
	double xkmca = 1380.0;
	double xkmnai = 10.0;
	double xkmko = 1.5;
	double xkmpca = 0.05;
	double xkmup = 0.32;
	double cmdntot = 10.0;
	double csqntot  =10000.0;
	double xkmcmdn = 2.0;
	double xkmcsqn = 600.0;
	double vup = 0.1;
	double vmyo = 25.84e-6;
	double vsr = 2e-6;
	double cnai = 10.0;
	double cki = 149.4;	
	double cnao = 138.0;
	double cko = 4.0;
	double ccao = 2000.0;

// useful quantities and constants
	double rtof = rr *tt / ff;
	double ena = rtof * log(cnao / cnai);
	double ek = rtof * log(cko / cki);
	double eks = rtof * log((cko + 0.01833 * cnao) / (cki + 0.01833 * cnai));
	double sigma = (exp(cnao / 67.3) - 1.) / 7.;
	double taufca = 30.;
	double caidtconst = acap * csc * 0.5 / (ff * vmyo);
	
	double dt = .02;
	double dx = .0125;
	double diff_coeff = 0.001;
	
	double am, bm, ah, bh, aj, bj, taum, tauh, tauj, minf, hinf, jinf;
	double rinf, taukr, ikrcoeff, sinf, tauks;
	double axto, bxto, ayto, byto, tauxto, xtoinf, tauyto, ytoinf;
	double inaca1, inaca2, ecat, icakcoeff;
	double finf, tauf, dinf, taud, xicabart1, xicabart2, xicabar, fcainf;
	double gamma, xjrelcoeff, xjrel, xjleak, xjup, bit, dcaidt, bsr, dcasrdt;
	double ina, ik1, ikr, iks, ito, ikp, inak, inaca, ipca, icab, inab, ica, icak;
	
// sodium current
    if(abs(mynode->v + 47.13) < 1e-6) 
		am = 3.2;
	else
		am = 0.32 * (mynode->v + 47.13) / (1.-exp(-0.1 * (mynode->v + 47.13)));
    bm = 0.08 * exp(-mynode->v / 11.);
    ah = 0.135 * exp(-(mynode->v + 80.) /6.8);
    bh = 7.5 / (1. + exp(-0.1 * (mynode->v + 11.)));
    aj = 0.175 * exp(-(mynode->v + 100.0) / 23.) / (1. + exp(0.15 * (mynode->v + 79.)));
    bj = 0.3 / (1. + exp(-0.1 * (mynode->v + 32.)));
    taum = 1. / (am+bm);
    minf = taum * am;
    tauh = 1. / (ah+bh);
    hinf = tauh * ah;
    tauj = 1. / (aj+bj);
    jinf=tauj * aj;

    mynodenew->m = minf + (mynode->m - minf) * exp(-dt / taum);
    mynodenew->h = hinf + (mynode->h - hinf) * exp(-dt / tauh);
    mynodenew->j = jinf + (mynode->j - jinf) * exp(-dt / tauj);
    ina = gna * mynodenew->m * mynodenew->m * mynodenew->m * mynodenew->h * mynodenew->j * (mynode->v - ena);

// inward rectifier k+ current
    ik1 = gk1 * cko / (cko + xkmk1) * (mynode->v - ek) / (2. + exp(1.62 / rtof * (mynode->v - ek)));

// rapid component of the delayed rectifier k+ current
    rinf = 1. / (1. + exp(-2.182 - 0.1819 * mynode->v));
    taukr = 43. + 1. / (exp(-5.495 + 0.1691 * mynode->v) + exp(-7.677 - 0.0128 * mynode->v));
    mynodenew->kr = rinf + (mynode->kr - rinf) * exp(-dt / taukr);
    ikrcoeff = gkr * sqrt(cko) * 0.5 * (mynode->v - ek) / (1. + 2.5 * exp(0.1 * (mynode->v + 28.0)));
    ikr = mynodenew->kr * ikrcoeff;

// slow component of the delayed rectifier k+ current
    sinf = 1. / (1. + exp(-(mynode->v - 16.0) / 13.6));
    if(abs(mynode->v - 10) < 1e-6) 
		tauks = 417.946;
	else
		tauks = 1. / ((0.0000719 * (mynode->v - 10.) / (1. - exp(-0.148 * (mynode->v - 10.)))) + (0.000131 * (mynode->v - 10.) / (exp(0.0687 * (mynode->v - 10.)) - 1.)));
    mynodenew->ks = sinf + (mynode->ks - sinf) * exp(-dt / tauks);
    iks = gks * mynodenew->ks * mynodenew->ks * (mynode->v - eks);

// transient outward k+ current
    axto = 0.04516 * exp(0.03577 * mynode->v);
    bxto = 0.0989 * exp(-0.06237 * mynode->v);
    ayto = 0.005415 * exp(-(mynode->v + 33.5) / 5.) / (1. + 0.051335 * exp(-(mynode->v  +33.5) / 5.));
    byto = 0.005415 * exp((mynode->v + 33.5) / 5.) / (1. + 0.051335 * exp((mynode->v + 33.5) / 5.));
    tauxto = 1. / (axto + bxto);
    xtoinf = axto * tauxto;
    tauyto = 1. / (ayto + byto);
    ytoinf = ayto * tauyto;

    mynodenew->xto = xtoinf + (mynode->xto - xtoinf) * exp(-dt / tauxto);
    mynodenew->yto = ytoinf + (mynode->yto - ytoinf) * exp(-dt / tauyto);
    ito = gto * mynodenew->xto * mynodenew->yto * (mynode->v - ek);

// plateau k+ current
    ikp = gkp * (mynode->v - ek) / (1. + exp((7.488 - mynode->v) / 5.98));
//    xikp=gkp*(v-ek)./(1.+exp((7.488-v)/5.98));

// na+-k+ pump current
    inak = inakbar * (cko / (cko + xkmko)) / (1. + pow((xkmnai/cnai),1.5)) / (1. + 0.1245 * exp(-0.1 * mynode->v / rtof) + 0.0365 * sigma * exp(-mynode->v / rtof));

// na+/ca2+ exchange current
    inaca1 = (xknaca/((xkmna*xkmna*xkmna)+(cnao*cnao*cnao)))/(xkmca+ccao)/(1.+xksat*exp(mynode->v*(eta-1.)/rtof))*(exp(mynode->v*eta/rtof)*(cnai*cnai*cnai)*ccao);
    inaca2 = (xknaca/((xkmna*xkmna*xkmna)+(cnao*cnao*cnao)))/(xkmca+ccao)/(1.+xksat*exp(mynode->v*(eta-1.)/rtof))*(exp(mynode->v*(eta-1.)/rtof)*(cnao*cnao*cnao));
    inaca = inaca1 - inaca2 * mynode->cai;

// sarcolemmal pump current
    ipca = ipcabar * mynode->cai / (xkmpca + mynode->cai);

// ca2+ background current
    ecat = 0.5 * rtof * log(ccao / mynode->cai);
    icab = gcab * (mynode->v - ecat);

// na+ background current
    inab = gnab * (mynode->v-ena);

// L-type ca2+ channel current
    finf = 1. / (1. + exp((mynode->v + 12.5) / 5.));
    tauf = 30. + 200. / (1.  +exp((mynode->v + 20.) / 9.5));
    dinf = 1. / (1. + exp(-(mynode->v + 10.) / 6.24));
    taud = 1. / ((0.25 * exp(-0.01 * mynode->v) / (1. + exp(-0.07 * mynode->v))) + (0.07 * exp(-0.05 * (mynode->v + 40.))) / (1. + exp(0.05 * (mynode->v + 40.))));

    if(abs(mynode->v) < 1e-6) 
    {
		xicabart1 = 0.00434168 * exp(2. * mynode->v / rtof);
        xicabart2 = 0.00434168 * 0.341 * ccao;
	}
	else
	{
		xicabart1 = pca / csc * 4.0 * mynode->v * ff / rtof / (exp(2 * mynode->v / rtof) - 1.) *exp(2. * mynode->v / rtof);
		xicabart2 = pca / csc * 4.0 * mynode->v * ff / rtof / (exp(2 * mynode->v / rtof) - 1.) * 0.341 * ccao;
	}
    xicabar = xicabart1 * mynode->cai - xicabart2;
    mynodenew->f = finf + (mynode->f - finf) * exp(-dt / tauf);
    mynodenew->d = dinf + (mynode->d - dinf) * exp(-dt / taud);
    fcainf = 1. / (1. + pow((mynode->cai / xkmfca),3));
    mynodenew->fca = fcainf + (mynode->fca - fcainf) * exp(-dt / taufca);
    ica = xicabar * mynodenew->f * mynodenew->d * mynodenew->fca;

// k+ current through the L-type Ca2+ channel
	if(abs(mynode->v) < 1e-6) 
		icakcoeff = 317.103;
	else
		icakcoeff=pcak/csc*(1000.*mynode->v*ff/rtof) * (cki*exp(mynode->v/rtof)-cko) / (exp(mynode->v/rtof)-1.);
    icak = icakcoeff * mynodenew->f * mynodenew->d * mynodenew->fca / (1. + xicabar / icahalfbar);

// calcium handling
    gamma = 1. / (1. + pow((2000.0 / mynode->casr),3));
    xjrelcoeff = prel / (1. + 1.65 * exp(mynode->v / 20.));
    xjrel = xjrelcoeff * mynode->f * mynode->d * mynode->fca * (gamma * mynode->casr - mynode->cai);
    xjleak = pleak * (mynode->casr - mynode->cai);
    xjup = vup / (1. + pow((xkmup / mynode->cai),2));
    bit = 1. / (1. + (cmdntot * xkmcmdn / (pow((xkmcmdn + mynode->cai),2))));
    dcaidt = bit * (xjrel + xjleak - xjup - caidtconst * (ica + icab + ipca - 2.0*inaca));
    mynodenew->cai = mynode->cai + dt * dcaidt;

    bsr = 1. / (1. + csqntot * xkmcsqn / (pow((xkmcsqn + mynode->casr),2)));
    dcasrdt = bsr * (xjup - xjleak - xjrel) * vmyo / vsr;
    mynodenew->casr = mynode->casr + dt * dcasrdt;

    mynodenew->v = mynode->v + dt*diff_coeff/(dx*dx)*diffusionValue - dt*(ina + ik1 + ito + ikp + inab + iks + ica + inaca + ipca + icab + icak + inak + ikr);

}
