#ifndef AGENT_H
#define AGENT_H

#include <deque>
#include "order.h"
#include "matrix.h"

const int numCurrency = 2;
const int lchrom = 7;

typedef deque<double> dlist;

class agent {
public:
	// Constructors
	agent();
	agent(double vpupdate, double vpcompare, double vpcross,
		double vpmutate, double vmfrangeHigh, double vmfrangeLow, 
		double vcfrange, double vpbuy, double vpsell);
	
	// Accessors
	double calcForecast(const dlist &price, const dlist &dividends, int t, double xstar);
	double calcForecastNoIteration(const dlist &price, const dlist &dividends, 
									int t, double xstar);
	//double calcAntiFit(const dlist &price, const dlist &dividends, int t, int leval, int g);
	double calcAntiFit(const dlist &price, const dlist &dividends, 
						int t, int leval, double g, double xstar); //cg 8/19/04 (see also agent.cpp)
	
	//Update forcast rule
	void updateRule(const Matrix & rule );
	
	double getA() const {return chrom[0];}
	double getB() const {return chrom[1];}
	double getC() const {return chrom[2];}
	double getD() const {return chrom[3];}
	double getE() const {return chrom[4];}
	double getF() const {return chrom[5];}
	double getG() const {return chrom[6];}//cg 11/10/04 add cross product in forecast function
	
	double getpupdate() const {return pupdate;}
	double getpcompare() const {return pcompare;}
	double getpcross() const {return pcross;}
	double getpmutate() const {return pmutate;}
	double getmfrangeHigh() const {return mfrangeHigh;}
	double getmfrangeLow() const {return mfrangeLow;}
	double getcfrange() const {return cfrange;}
	double getpbuy() const {return pbuy;}
	double getpsell() const {return psell;}
	double getSpread() const {return bidAskSpread;}
	double getDist() const {return dist;}
	
	double getWealth() const {return wealth;}
	double getShares(int currency) const {return shares[currency];}
	order getOrder() const {return agentOrder;}
	
	bool getFund() const {return fund;}
	
	// Probability functions
	int mdist();
	int cdist();
	int rdist();
	int compdist();
	double cfdist();
	double mfdist();

	
	// Modifiers
	void setA(double a) {chrom[0] = a;}
	void setB(double b) {chrom[1] = b;}
	void setC(double c) {chrom[2] = c;}
	void setD(double d) {chrom[3] = d;}
	void setE(double e) {chrom[4] = e;}
	void setF(double f) {chrom[5] = f;}
	void setG(double g) {chrom[6] = g;}//cg 11/10/04 add cross product in forecast function
	
	void setpupdate(double n){pupdate=n;}
	void setpcompare(double n){pcompare=n;}
	void setpcross(double n){pcross=n;}
	void setpmutate(double n){pmutate=n;}
	void setmfrangeHigh(double n){mfrangeHigh=n;}
	void setmfrangeLow(double n){mfrangeLow=n;}
	void setcfrange(double n){cfrange=n;}
	void setpbuy(double n) {pbuy = n;}
	void setpsell(double n) {psell = n;}
	void setSpread(double s) {bidAskSpread = s;}
	void setDist(double d) {dist = d;}
	
	void setWealth(double w) {wealth = w;}
	void setShares(double s, int currency) {shares[currency] = s;}
	void setOrder(order o) {agentOrder = o;}
	
	void setFund(bool f) {fund = f;}
	
	void calcOrderPrice(const dlist &price, const dlist &rates, const dlist &dividends, int t, double xbar);
	void calcOrderAmount(const dlist &price, const dlist &rates, const dlist &dividends, int t, double xbar);
	double calcDist(const double &p);
		
	void operator= (const agent &a);

private:
	// Probability varaibles
	double pupdate;
	double pcompare;
	double pcross;
	double pmutate;
	double mfrangeHigh;
	double mfrangeLow;
	double cfrange;
	double pbuy;
	double psell;
	double bidAskSpread;
	double dist;
	
	// Agent prediction chromosomes
	double chrom[lchrom];
	
	// Agent's order for trading
	order agentOrder;
	
	// Agent's currency holdings
	// only 2 currencies
	double shares[2];
	
	// Agent's wealth in currency 0
	double wealth;
	
	// whether agent if a fundamentalist trader
	bool fund;
	
	// random number generator
	double randNum();
};

//==========================================================================
//
//              AGENT MEMBER FUNCTION DEFINITIONS
//
//==========================================================================

agent::agent() {
	int i;
	for (i=0; i<lchrom; i++)
		chrom[i] = 0;
		
	for (i=0; i<numCurrency; i++)
		shares[i] = 0;
	
	pupdate = 0;
	pcompare = 0;
	pcross = 0;
	pmutate = 0;
	mfrangeHigh = 0;
	mfrangeLow = 0;
	cfrange = 0;
	pbuy = 0;
	psell = 0;
	bidAskSpread = 0;
	dist = 0;
	fund = false;
	
	wealth = 0;
}

agent::agent(double vpupdate, double vpcompare, double vpcross,
		double vpmutate, double vmfrangeHigh, double vmfrangeLow, 
		double vcfrange, double vpbuy, double vpsell) {
	int i;
	
	for (i=0; i<lchrom; i++)
		chrom[i] = 0;
		
	for (i=0; i<numCurrency; i++)
		shares[i] = 0;
	
	pupdate = vpupdate;
	pcompare = vpcompare;
	pcross = vpcross;
	pmutate = vpmutate;
	mfrangeHigh = vmfrangeHigh;
	mfrangeLow = vmfrangeLow;
	cfrange = vcfrange;	
	pbuy = vpbuy;
	psell = vpsell;
	bidAskSpread = 0;
	dist = 0;
	fund=false;
	
	wealth = 0;
}

void agent::updateRule(const Matrix & rule ) 
{
	for (int i = 0; i < lchrom; i++ )
		chrom[i] = rule.getElement(i);
}

double agent::calcForecast(const dlist &price, const dlist &dividends, int t, double xstar){
	double forecastPriceDivT;  //cg 8/3/04
	double forecastPriceDivT1; //cg 8/3/04
	//double xstar = (alphaDiv[0]/(1-betaDiv[0]))*((1+interest[0])/interest[0]); //cg 10/06/04
	//double xstar = 21;
	
	if (t<1)
		return 0;
	else if (t < 3)
		return price[t-1] + dividends[t-1]; //cg 8/4/04
	forecastPriceDivT = getA() + getB()*(price[t-1] + dividends[t-1]) + getC()*(price[t-2] + dividends[t-2]) + getD()* (pow(price[t-2] + dividends[t-2],2)) + getE()*(price[t-3] + dividends[t-3]) + getF()*(pow(price[t-3] + dividends[t-3],2)) + getG()*((price[t-2] + dividends[t-2])*(price[t-3] + dividends[t-3]));	 ///cg 07/05/14
	forecastPriceDivT1 = getA() + getB() * (forecastPriceDivT ) + getC()*(price[t-1] + dividends[t-1]) + getD()*(pow(price[t-1] + dividends[t-1],2)) +	getE()*(price[t-2] + dividends[t-2]) + getF()*(pow(price[t-2] + dividends[t-2],2)) + getG()*((price[t-1] + dividends[t-1])*(price[t-2] + dividends[t-2]));	 //cg 07/05/14
	//added cross product G*(x(t-1)-x^*)*(x(t-2)-x^*) on 11/10/04 to allow for implicit belief in harmonic oscilator
		
	//if (forecastPriceDivT1 < 0)	//removed these two lines temp on 9/11/04 as if only individual learning (only mutation, no compare), some individuals can get stuck here and drift further and further out 
	//	return 0;					// "
		
	return forecastPriceDivT1;
}

//calcForecastNoIteration added in v8.31 to do noniterated expecatations for fitness evaluation. cg 10/06/04 
//now in v8.32 we change forecast rules to operate on deviations from xstar. cg 10/06/04
double agent::calcForecastNoIteration(const dlist &price, const dlist &dividends, int t, double xstar){
	double forecastPriceDivT;  //cg 8/3/04
	//double xstar = (alphaDiv[0]/(1-betaDiv[0]))*((1+interest[0])/interest[0]); //cg 10/06/04
	//double xstar = 21;
		
	if (t<1)
		return 0;
	else if (t < 3)
		return price[t-1] + dividends[t-1]; //cg 8/4/04
	forecastPriceDivT = getA() + getB()*(price[t-1] + dividends[t-1]) + getC()*(price[t-2] + dividends[t-2]) + getD()* (pow(price[t-2] + dividends[t-2],2)) + getE()*(price[t-3] + dividends[t-3] ) + getF()*(pow(price[t-3] + dividends[t-3],2)) + getG()*((price[t-2] + dividends[t-2])*(price[t-3] + dividends[t-3])) ;	 ///cg 10/06/04
			
	//if (forecastPriceDivT1 < 0)	//removed these two lines temp on 9/11/04 as if only individual learning (only mutation, no compare), some individuals can get stuck here and drift further and further out 
	//	return 0;					// "
		
	return forecastPriceDivT;
}

//still use calcAntiFit with iterated expectations for calculation of agent orders (bid and ask prices) 10/06/04
double agent::calcAntiFit(const dlist &price, const dlist &dividends, int t, int leval, double g, double xstar) { //cg 8/19/04 (see also agent.h)
	double sum = 0;
	double antifit = 0;

	//for (int k = t-leval; k<t; k++) {
		//antifit = fabs(calcForecast(price,dividends,k-1)-(price[k]+dividends[k])) * pow(1/(t-k),g);
		//sum = sum + antifit; //cg 8/18/04 replace i with k to avoid conflict with agent index ? 	
		
	for (int k = t-leval; k<t; k++) {
		antifit = fabs(calcForecastNoIteration(price,dividends,k,xstar)-(price[k]+dividends[k]));
		sum = sum + antifit; //cg 8/24/04 remove g as quick fix to problem!!!	
	}

	return sum;
}

void agent::calcOrderPrice(const dlist &price, const dlist &rates, const dlist &dividends, int t, double xstar) {
	order newOrder = agentOrder;
	double forecast = calcForecast(price,dividends,t,xstar);

	//original bid and ask without restrictions
	newOrder.bid = (forecast / (1+rates[t])) - (bidAskSpread/2);
	newOrder.ask = (forecast / (1+rates[t])) + (bidAskSpread/2);
	
	
	/* //alt: limit variability of bids and asks to +/- 0.1 on last period's price 2/21/06
	if ((forecast / (1+rates[t])) - (bidAskSpread/2) > price[t-1]+ 0.1) {
		newOrder.bid = price[t] + 0.1;
		}
		else {
		newOrder.bid = (forecast / (1+rates[t])) - (bidAskSpread/2);
		}
	if ((forecast / (1+rates[t])) - (bidAskSpread/2) < price[t-1] - 0.1) {
		newOrder.ask = price[t-1] - 0.1;
		}
		else {
		newOrder.ask = (forecast / (1+rates[t])) + (bidAskSpread/2);
		}
	*/
	agentOrder = newOrder;
}

void agent::calcOrderAmount(const dlist &price, const dlist &rates, const dlist &dividends, int t, double xstar) {
	order newOrder = agentOrder;	
	double forecast = calcForecast(price,dividends,t,xstar);
	double bonds = getShares(0);
	double stocks = getShares(1);
	
	if (((-1 * dividends[t]) + (1+rates[t]) * price[t-1]) < forecast) {
		newOrder.buyAmount = bonds * pbuy;
		newOrder.sellAmount = stocks * psell;
	}
	else {
		newOrder.buyAmount = bonds * psell;
		newOrder.sellAmount = stocks * pbuy;
	}
	agentOrder = newOrder;
}

void agent::operator =(const agent &a) {
	int i;
	for (i=0; i<lchrom; i++)
		chrom[i] = a.chrom[i];
	
	for (i=0; i<numCurrency; i++)
		shares[i] = a.shares[i];
	
	wealth = a.wealth;
	agentOrder = a.agentOrder;
	
	
	pupdate = a.pupdate;
	pcompare = a.pcompare;
	pcross = a.pcross;
	pmutate = a.pmutate;
	mfrangeHigh = a.mfrangeHigh;
	mfrangeLow = a.mfrangeLow;
	cfrange = a.cfrange;
	pbuy = a.pbuy;
	psell = a.psell;
	bidAskSpread = a.bidAskSpread;
	dist = a.dist;
	fund = a.fund;
}

//distance from wcc
double agent::calcDist(const double &p) {
	dist = getA() - (1 -  getB() - getC() - getE()) * p + (getD() + getF() + getG()) * pow(p,2);
	return dist;
}

int agent::mdist() {
	if (pmutate != 0)
		if (randNum() / pmutate < 1)
			return 1;
	return 0;		
}


int agent::cdist() {
	if (pcross != 0)
		if (randNum() / pcross < 1)
			return 1;
	return 0;		
}

int agent::rdist() {
	if (pupdate != 0)
		if (randNum() / pupdate < 1)
			return 1;
	return 0;		
}

int agent::compdist() {
	if (pcompare != 0)
		if (randNum() / pcompare < 1)
			return 1;
	return 0;		
}

/*
double agent::mfdist() {
	if (rand() % 2 == 1)
	return (randNum() - 0.5) * mfrangeHigh + 1; //cg 8/19/04
	return (randNum() - 0.5) * mfrangeLow + 1;  //cg 8/19/04
}
*/
//change mutation from multiplicative to addative. cg 10/07/04

double agent::mfdist() {
	if (rand() % 2 == 1)
	return (randNum() - 0.5) * mfrangeHigh;
	return (randNum() - 0.5) * mfrangeLow;
}

double agent::cfdist() {
	return (randNum() - 0.5) * cfrange + 0.5;
}

double agent::randNum() {
	return (double) rand() / RAND_MAX;
}

#endif

