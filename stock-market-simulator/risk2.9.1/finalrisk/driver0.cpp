//======================================================================
//  FILE:               driver.cpp
//  PROGRAMMER:         John C. Wallace, James Ballantyne, Rick Decker
//  PURPOSE:            Artificial Stock-Bond Market Model
//  UPDATE HISTORY:
//   
//                      risk2.9.1 7/07/14  counting upward and downward bubbles separately 
//						risk2.9 7/05/14      forcasting levels (not deviations)
//						risk2.8.2 7/13  (CG) v2.8.1 with volatility output
//                      risk2.8.1 6/13  (CG) v2.8 with risk pref in input.txt     
//                      risk2.8 5/13	(JK) added 2.6 and 2.7 changes to rick's optimized code 		
//						risk2.8_proto	5/13	(RD) replaced linked_list with deque 
//												(RD) cosmetic changes; replaced at() with []
//										
//						risk2.7 5/13    (JK) risk 2.6 with loop for risk factor a separated out    
//                      risk2.6 5/13    (JK) risk 2.5 with cases for forecast rules
//                      risk2.5         (CG) (BH)
//                      risk2.4         (YD) adds risk presferences to staggered updating v2.4						
//
//						2.5		8/06	(CG) 2.4 with Specification testing 
//						2.4		8/06	(CG) Replace trading with rep agent eq in 2.2 (EL)
//						2.3		x/06	(CG) Add Specification testing
//						2.2		x/06	(CG) Add AR specifications
//						2.1		2/06	(CG) Fix bugs
//						2.0		7/05	(RD) Refactored, cleaned up
//						1.1		3/05	(JB) Replaced evolution with OLS (staggered updating)
//
//						1.0     10/04	(JCW)		
//======================================================================

#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <time.h>
#include <deque>		// replaced the old linked_list class 5/13
#include "agent.h"
#include "matrix.h"
#include <cstring>		// added for dev-c++ on gambs2 8/14

using namespace std;

//for Pompeii: 	remove .h for iostream iomani string and fstream
//				remove redundant string
//				add 'using namespace std;' after the #includes here and in agent.cpp

//----------------------- Type definitions for Linked Lists -----------------------

typedef deque<double> dlist;		// changed to deque 5/13
typedef deque<agent> agentList;
typedef deque< dlist > listList;

//----------------------------- Function Declarations -----------------------------

double		randNum				();

void		getInput			();

void 		calcAverageGenes	(const agentList &agents, 
								listList &averageGenes, 
								dlist &msvDist, 
								dlist &aveDist, 
								double p);

void 		calcAverageGenesAndPrice	(const agentList &agents, 
										dlist &price, 
										const dlist &rates, 
										const dlist &dividends, 
										listList &averageGenes, 
										dlist &msvDist, 
										dlist &aveDist, 
										double p, 
										int t, 
										double xstar);

// added by Yinghan Ding, 03/05/2012			
void 		calcAverageGenesAndPriceAndVolatility	(const agentList &agents, 
													dlist &price, 
													dlist &volatility, 
													dlist &exbar, 
													dlist &axstar, 
													dlist &pstar, 
													const dlist &rates, 
													const dlist &dividends, 
													listList &averageGenes, 
													dlist &msvDist, 
													dlist &aveDist, 
													double p, 
													int t, 
													double a);
					
void 		calcWealth			(agentList &agents, 
								const dlist &price, 
								const dlist &rates, 
								const dlist &dividends, 
								int t);
								
agentList	update				(const agentList & agentlist);

void 		doNewForcast		(agent & fRule, 
								int t, 
								const dlist & price,  
								const dlist & divs, 
								double xs);

void 		updateGeneHistory	(bool condition, 
								const agentList & agents, 
								listList* hist);

void 		doTrades			(agentList &agents, 
								dlist &price, 
								double &stocksTraded, 
								double &bondsTraded, 
								int t);

dlist 		getNumbers			(int howMany, 
								int badNum);

void 		orderContacts		(const agentList &agents, 
								dlist &contacts);

void 		writeToDisk			(const dlist &price, 
								const dlist &volatility, 
								const dlist &exbar, 
								const dlist &axstar, 
								const dlist &pstar, 
								const dlist &volume, 
								const dlist &rates, 
								const dlist &dividends, 
								const listList &wealthHistory, 
								const dlist &bondHistory, 
								const dlist &stockHistory, 
								const listList &averageGenes, 
								const listList* historyGene, 
								const listList &distanceHistory, 
								dlist &msvDist, 
								dlist &aveDist, 
								int sim);

void 		writeMatrixToDisk	(const Matrix & y, 
								const Matrix & x, 
								const Matrix & beta, 
								int count );

void 		incrementGlobals	();

//file for output in testing for explosive bubbles - cg 6/4/05
ofstream outfile( "explosive.txt", ios_base::app );
ofstream outfile1( "numExplosions.txt", ios_base::app ); //for counting explosions in 100 runs
ofstream outfile2( "volatility.txt" , ios_base::app ); //for recording volatility of each run //7/16/13

//ofstream outfile2("bubbles.txt", ios_base::app );

//------------------------------- Global Variables -------------------------------

int rounds[3]; 				// number of rounds in simulation
int popsize[3]; 			// population size
int leval[3]; 				// length of evaluation period
int linit[3];				// number of initial rounds
int traderLimit[3]; 		// how many traders trade per period
int fundTrader[3];			// number of fundamentalist traders
int numLook[3];				// number of other traders a trader can trade with
int trackAgent[3];			// inder of trader to track
int startDist[3];			// start point to keep track of distance
int endDist[3];				// end point to keep track of distance
int runs[3];				// number of rounds in a simulation. Only runs[0] has a value
int randSeed[3];			// seed for random number generator
int numSets[3];				// number of different sets of agents
int numa[3];                // number of risk factors to loop over. Only numa[0] has a value         //05/20/2013 Jim
double a[3];                // risk factor  //6/6/12
double bubbleThreshold[3];  // upward bubble threshold //6/6/12
double g[3];				// exponent to discount past rounds
double sigmaRange[3];		// range of sigma
double noiserange[3];		// range of noise
double pupdate[3];		// probability of reproduction
double pcompare[3];			// probablity to compare itself to another agent
double pcross[3];			// probablity to cross breed with another agent
double pmutate[3];			// probability an agent mutates
double mfrangeHigh[3];		// high range of mutation
double mfrangeLow[3];		// low range of mutation
double cfrange[3];			// cross breed range
double pbuy[3];				// percent of wealth used to buy
double psell[3];			// percent of wealth to sell
double minTrade[3];			// minimum number of trades that occur at average market price during P(t)
double bidAskSpread[3];		// spread to put around P(E)
double interest[3];			// starting interest rate
double dividend[3];			// starting dividend
double pshock[3];			// probablilty of shocking dividend
double alphaDiv[3];			// alpha value for dividend manipulation
double betaDiv[3];			// beta value for dividend manipulation
double shockRange[3];		// range to shock the dividend
double startPrice[3];		// starting price of simulation
double startShares[3];		// number of shares traders start with
double startBonds[3];		// number of bonds traders start
double geneA[3];			// pre-defined gene a
double geneB[3];			// pre-defined gene b
double geneC[3];			// pre-defined gene c
double geneD[3];			// pre-defined gene d
double geneE[3];			// pre-defined gene e
double geneF[3];			// pre-defined gene f
double geneG[3];			// pre-defined gene g

agent forcastRule;			// This agent will always hold the newest forcast rule. 3/05
int forecast_rule;          // functional form of forecast rule
int frule[3];               // functional form of forecast rule

//================================ main routine ================================

int main(int argc, char **argv) {
  
  int rank;
  int nprocs;
  char hostname[256];
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
  gethostname(hostname, 255);

 

	//forecast_rule = 4;	//functional form for forecast rule //relocated to input.txt 6/21/13
						    // case 1 : ar(3,3) all seven regressors
			                // case 2 : ar(0) msv
						    // case 3 : ar(1) linear
						    // case 4 : ar(2) linear
						    // case 5 : ar(2,1) nonlinear
						    // case 6 : ar(2,2) nonlinear
						    // case 7 : ar(3) linear
			                // case 8 : ar(3,1) nonlinear 


  getInput();				// Get input from file	
	forecast_rule = frule[0];  //6/21/13
		
	//--------------------------- Declarations ---------------------------
	
	int i;					// counter for for sundry loops
	int round; 				// counter for rounds in one simulation	
	int numExplosions = 0;	//counter for number of explosions in 100 runs
	int upExplosions = 0;  // counter for explosions upward
	int downExplosions = 0;   // counter for explosions downward
	double exsum = 0;
	double stocksTraded = 0;
	double bondsTraded = 0;
	double noise = 0;
    double dt = dividend[0];
    double shock = 0;
	double sumBid = 0;
	double sumAsk = 0;
	double avePrice = 0;
	double sigma = 0;
	//double bubbleThreshold = 2; //6//5/12

	time_t startSecond = time(NULL);
	time_t endSecond;
	time_t difference;
	
	outfile1 << "frule " << "leval " << "pupdate " << "a " << "numExplosions " << " upExplosions " << " downExplosions " << endl; //for counting explosions in 100 runs
	outfile2 << "Test number " << " a " << " Run number " << " random seed " << " volatility " << endl; //7/16/13
	
	
	 
	for (int acount = 0; acount < numa[0]; acount++) {	          //5/20/2013 Jim
	  if(acount % nprocs == rank){
   	cout << "Simulations for Risk Factor # " << acount + 1 << ": " << endl;
    cout << "forecast rule: " << forecast_rule << "; leval: " << leval[0] << "; pupdate: " << pupdate[0] << "; risk: " << a[0] << endl;
	cout << endl;
	//outfile1 << "leval " << "pupdate " << "a " << "numExplosions " << endl; //for counting explosions in 100 runs
    
	for (int sims = 0; sims < runs[0]; sims++) {
	  
		srand(randSeed[0]);	
		cout << "Test number: " << acount + 1 << " Run number: " << sims + 1 << " random seed: " << randSeed[0]  << endl;
		outfile << "Test number: " << acount + 1 << " Run number: " << sims + 1 << " random seed: " << randSeed[0]  << endl;
		
		

		//--------------------- Declaration of lists ---------------------
	
		agentList agents;		// stores all of the agents 
		
		dlist price;			// stores the price for every round
		dlist volatility;		// stores recent volatility for every round //6/5/12
		dlist exbar;			// stores the average ex (forecast of x = p + div) 
								// for every round
		dlist volume;			// stores the number of trades per round
		dlist rates;			// list of interest rates
		dlist dividends;		// list of dividend
		dlist tempDist;
		dlist msvDist;
		dlist aveDist;
		dlist currentWealth;	// All agents' wealth this period
		dlist bondHistory;		// Track one agents' Stock and Bond history
		dlist stockHistory;	
		
		dlist axstar;       // 04/26/2012, keep track of moving values of xstar
		dlist pstar;        //04/26/2012, keep track of moving values of pstar

		listList distanceHistory;     	
		listList wealthHistory;		// Keep track of all agents' wealth for all periods
		listList averageGenes;		// Keeps track of the average genes (6) total for 
									// every round
		listList historyGene[7];	// Keeps track of all genes for every agent   
	
		/***********************************************************************
						Initialize Agents
		***********************************************************************/
		double xstar = (alphaDiv[0] / (1 - betaDiv[0])) * 
						((1 + interest[0]) / interest[0]);
		//axstar.insert(xstar);
		double pstarvalue = (alphaDiv[0] / (1 - betaDiv[0])) / interest[0];
	
		for (i = 0; i < popsize[0]; i++) {
			agent newAgent(pupdate[0], pcompare[0], pcross[0], 
							pmutate[0], mfrangeHigh[0], mfrangeLow[0], 
							cfrange[0], pbuy[0], psell[0]);		
			newAgent.setSpread(bidAskSpread[0]);
		
			// Set the genes, the number of shares the agent has, the bidAsk spread
			// and set fundamentalist traders (if any)
				
			if (i < fundTrader[0]) {
				newAgent.setA(dt / interest[0]);
				newAgent.setB(0);
				newAgent.setC(0);
				newAgent.setD(0);
				newAgent.setE(0);
				newAgent.setF(0);
				newAgent.setG(0);
				newAgent.setFund(true);
				newAgent.setShares(100,0);
				newAgent.setShares(5,1);
			}
			else {		
                 geneA[0]=xstar;
				newAgent.setA(geneA[0] + (randNum() - 0.5) * 0); 	//0.1 - geneA[0]=xstar - REE point 
				newAgent.setB(geneB[0] + (randNum() - 0.5) * 0);	//1
				newAgent.setC(geneC[0] + (randNum() - 0.5) * 0);	//1	
				newAgent.setD(geneD[0] + (randNum() - 0.5) * 0);	//5
				newAgent.setE(geneE[0] + (randNum() - 0.5) * 0);	//1
				newAgent.setF(geneF[0] + (randNum() - 0.5) * 0);	//5
				newAgent.setG(geneG[0] + (randNum() - 0.5) * 0);	//5
				newAgent.setShares(startBonds[0], 0);
				newAgent.setShares(startShares[0], 1);
			}
			agents.push_back(newAgent);
			currentWealth.push_back(0);
		}
		
		/***********************************************************************
						Prime first 2 rounds
		***********************************************************************/
		for (round = 0; round < 3; round++) {
			price.push_back(startPrice[0]);
			volatility.push_back(0); //6/6/12
			exbar.push_back(0);
			//avbar.push_back(0);        // added by Yinghan Ding, 03/05/2012
			axstar.push_back(xstar);
			pstar.push_back(pstarvalue);
			volume.push_back(0);
			rates.push_back(interest[0]);
			dividends.push_back(dividend[0]);
			wealthHistory.push_back(currentWealth);
			bondHistory.push_back(agents[trackAgent[0]].getShares(0));
			stockHistory.push_back(agents[trackAgent[0]].getShares(1));
			calcAverageGenes(agents, averageGenes, msvDist, aveDist, 0);				
		} // END FOR (first chunk of rounds)
		
		/***********************************************************************
						Run without allowing the agents to change
						for linit rounds
		***********************************************************************/
		for (round = 3; round < linit[0] + 3; round++) {
			
			// No Trades. Price is equal to last period's price plus noise
			// Initialize values for this round
			// Insert interest rate, dividend, current price, expected price, 
			// and trade volume into lists
						 
			noise = noiserange[0] * (randNum() * 2 - 1);
			stocksTraded = 0;
			bondsTraded = 0;
			rates.push_back(interest[0]);
			
			// Dividend can be shocked
			if (randNum() < pshock[0])
				shock = shockRange[0] * (alphaDiv[0] / (1 - betaDiv[0])) * (randNum() - 0.5);
			else
				shock = 0;
						
			dt = alphaDiv[0] + betaDiv[0] * dividends[round - 1] + shock;
			dividends.push_back(dt);
						
			//don't shock price directly
			price.push_back(price[round - 1] + 0.0 * (randNum() - 0.5));
			volatility.push_back(volatility[round - 1]); //6/6/12
			axstar.push_back(xstar);
			pstar.push_back(pstarvalue);
			volume.push_back(bondsTraded);
			calcWealth(agents, price, rates, dividends, round);
			exsum = 0;
			currentWealth.clear();
						
			// Calculate average forecast price and wealth for all agents
			for (i = 0; i < popsize[0]; i++) {
				exsum = exsum + agents[i].calcForecast(price, dividends, 
															round, xstar);
				currentWealth.push_back(agents[i].getWealth());
			}
			exbar.push_back(exsum / popsize[0]);
			wealthHistory.push_back(currentWealth);
			bondHistory.push_back(agents[trackAgent[0]].getShares(0));
			stockHistory.push_back(agents[trackAgent[0]].getShares(1));
			calcAverageGenes(agents,averageGenes, msvDist, aveDist, 0);
		
			// Alternate conditions for updateGeneHistory:  (round%10 == 0), 
			// (round == 3), (0 <= round && round <= 200) (round == 1000000) 
			updateGeneHistory(422 - 1 <= round && round <= 442, 
								agents, historyGene);            
		} // END FOR (second chunk of rounds)

		xstar = (alphaDiv[0] / (1 - betaDiv[0])) * ((1 + interest[0]) / interest[0]);
					
		/***********************************************************************
						Do the rest of the rounds in a simulation run
		***********************************************************************/
		for (round = linit[0] + 3; round < rounds[0]; round++) {
		
		if((round + 1) % 100000 == 0) {
			cout << "round " << round + 1 << endl;
		}	//5/22/12
		
		if (price[round - 1] >= bubbleThreshold[0] || price[round - 1] <= 0) {	  					
		  //price.replace(price.elementAt(round - 1), round); 	
		  // price has exploded, don't process this round 	  					
		  price.push_back(price[round - 1]);
		  axstar.push_back(axstar[round - 1]);
		  pstar.push_back(pstar[round - 1]);
		} else { // process round if price has not exploded

				//We have replaced the GA-like evolve routine with staggered OLS 
				// updating - 3/05
				doNewForcast(forcastRule, round, price, dividends, xstar);
									   
				//Now determine if any agents will be able to use this update rule
				agents = update(agents);
				
				// Alternate conditions for updateGeneHistory: ((round+1)%100 == 0),
				// (0 < round && round <200)(15865 <= round && round <= 15964 && 
				// round % 1 == 0, agents, historyGene)
				// updateGeneHistory(14559 <= round && round < 14759,  agents, historyGene);
				
				updateGeneHistory(11000 - 1 <= round && round <= 11000 - 1 , 
								agents, historyGene);
						
				//----------------------- Start Trading Period -----------------------
									   
				// start of period's price is the closing price for last period. 			
				// kill 8/02/06
				//price.push_back(price[round - 1]);
						  
				// Insert period's interest rate and dividend
				// Dividend can be shocked
				if (randNum() < pshock[0])
					shock = shockRange[0] * (alphaDiv[0] / (1 - betaDiv[0])) *
							(randNum() - 0.5);				
				else
					shock = 0;
							
				dt = alphaDiv[0] + betaDiv[0] * dividends[round - 1] + shock;
				rates.push_back(interest[0]);
				dividends.push_back(dt);
				
				/*------------ Fundamentalists update their forecasts --------
				for (i = 0; i < fundTrader[0]; i++) {
					agent a = agents.elementAt(i);
					a.setA(dividends.elementAt(round) / rates.elementAt(round));
					agents[i] = a;
				}
				--------------------------------------------------------- */
				
				/*--------------- kill trading 8/02/06	-------------------   
				// Calculate all agents' orders
				for (i = 0; i < popsize[0]; i++) {
					agent trader = agents.elementAt(i);
					trader.calcOrderPrice(price, rates, dividends, round, xstar);
					trader.calcOrderAmount(price, rates, dividends, round, xstar);
					agents[i] = trader;
				}
											
				// Let Agents Trade Wealth
				// Initialize all trading variables
	
				sumBid = 0;
				sumAsk = 0;
				stocksTraded = 0;
				bondsTraded = 0;
				doTrades(agents, price, stocksTraded, bondsTraded, round); 
				//note that this is where price was updated 8/02/06
									
				// Calculate Average Bid and Ask Prices
				for (i = 0; i < popsize[0]; i++) {
					agent temp = agents.elementAt(i);
					sumBid += temp.getOrder().bid;
					sumAsk += temp.getOrder().ask;
				}
				// Calculate the minimum background trades and price
				bondsTraded += minTrade[0];
				avePrice = (sumBid + sumAsk) / (2 * popsize[0]);
				stocksTraded += minTrade[0] / avePrice;
				--------------------------------------------------------*/
	
				//-------------------- Done With Trades --------------------
				
				// Calculate the average forecasted market priceb for next period and 
				// the new price for next period 8/02/06
				// kill wealth recording 8/02/06
				exsum = 0;
				//currentWealth.clear();
				for (i = 0; i < popsize[0]; i++) {
					exsum = exsum + agents[i].calcForecast(price, dividends, 
															round, xstar);
					//currentWealth.push_back(agents[i].getWealth());
				}
				exbar.push_back(exsum / popsize[0]);
				//wealthHistory.insert(currentWealth);
				//bondHistory.insert(agents.elementAt(trackAgent[0]).getShares(0));
				//stockHistory.insert(agents.elementAt(trackAgent[0]).getShares(1));
				//calcAverageGenes(agents,averageGenes, msvDist, aveDist, 0);	
				//calcAverageGenesAndPrice(agents, price, rates, dividends, averageGenes, msvDist, aveDist, 0, round, xstar);		
				// by Yinghan Ding, 03/05/2012
				calcAverageGenesAndPriceAndVolatility(agents, price, volatility, 
													exbar, axstar, pstar, rates, 
													dividends, averageGenes, msvDist, 
													aveDist, 0, round,a[0]);
  
				// Calculate Distance from Locus of Expectations for every agent
				if (round > startDist[0] && round < endDist[0]) {
					tempDist.clear();
					for (i = 0; i < popsize[0]; i++) 
						tempDist.push_back(agents[i].calcDist(0));
					distanceHistory.push_back(tempDist);
				}
				
				noise = (noiserange[0] * (randNum() * 2 - 1));
				/* kill 8/02/06
				// Calculate new average price
				if (stocksTraded == 0 && price.elementAt(round - 1) > fabs(noise))
					price.replace(price.elementAt(round - 1) + noise, round);
				else if (stocksTraded > 0 && (bondsTraded / stocksTraded) >fabs( noise))
					price.replace((bondsTraded / stocksTraded) + noise, round);
				else
					price.replace(price.elementAt(round - 1), round);
				*/
					
				if ((price[round] > bubbleThreshold[0] && price[round - 1] < 
					bubbleThreshold[0]) ) {	
				  cout << "price has exploded upward in trading period " << round + 1 << endl;
				  outfile << "price has exploded upward in trading period " << round+1 << endl;
				  numExplosions++;
				  upExplosions++;
				  //outfile2 << round + 1 << endl;
				  //exploded = 1;
				  price[round] = bubbleThreshold[0]; //6/5/12
				  break;
				}
				if ((price[round] < 0 && price[round - 1] > 0)) {
					cout << "price has exploded downward in trading period " << round + 1 << endl;
				  outfile << "price has exploded downward in trading period " << round+1 << endl;
				  numExplosions++;
				  downExplosions++;
				  //outfile2 << round + 1 << endl;
				  //exploded = 1;
				  price[round] = 0; //6/5/12
				  break;
				}
				
				/*----------------- kill 8/02/06 ----------------------
				if (bondsTraded / stocksTraded > 1000) {
					price.replace(1000, round);
				}
							
				volume.insert(bondsTraded);
				
				// Calculate the new wealth of all agents
				calcWealth(agents,price,rates,dividends,round);
				----------------------------------------------------- */
			
				
			} // END IF (price hasn't exploded)
		} // END FOR (third chunk of rounds)
		cout << endl;

		// Done with simulation. Write data to disk -- can comment out if 
		// don't want the output
/*
					writeToDisk(price, volatility, exbar, axstar, pstar, 
					volume, rates, dividends, wealthHistory, 
					bondHistory, stockHistory, averageGenes, historyGene, 
					distanceHistory, msvDist, aveDist, sims);
*/
		// temp block wTD to text for explosion in 100 runs 5/26/05
		
		outfile2 << acount + 1 << ' ' << a[0] << ' ' << sims + 1 << ' ' << randSeed[0] << ' ' << volatility[round] << endl; //7/16/13
		
		// Increment All Global Variables for next Simulation
		incrementGlobals();
	} // END FOR (all simulations)
    cout << endl << "Done Running Simulations for Risk Factor #" << acount + 1 << endl;
    cout << "forecast rule: " << forecast_rule << " leval: " << leval[0] << "; pupdate: " << pupdate[0] << "; risk: " << a[0] << "; numExplosions: " << numExplosions << endl;
	//outfile1 << "leval " << "pupdate " << "numExplosions " << endl; //for counting explosions in 100 runs
    outfile1 << forecast_rule << ' ' << leval[0] << ' ' << pupdate[0] << ' ' << a[0] << ' ' << numExplosions << ' '<< upExplosions << ' ' << downExplosions << endl; //wTD number of explosions in 100 runs
    //cout << leval[0] << ' ' << pupdate[0] << ' ' << numExplosions << endl; 
    cout << endl << endl;
    if(numa[0] > 1) {a[0] += (a[2] - a[1]) / (numa[0]-1);}      //05/20/2013 Jim //moved here by cg 5/25/13
    numExplosions = 0; //cg 5/25/13
    upExplosions = 0;
    downExplosions = 0;
    randSeed[0] = randSeed[1]; //cg 5/25/13

      
    }   

    }

    endSecond = time(NULL);
	difference = endSecond - startSecond;
	cout << "This simulation took " << difference << " seconds to complete." << endl;
	
	MPI_Finalize();
	//	system("PAUSE"); //only for windows
    return 0;
	
}


//============================== FUNCTION DEFINITIONS ==============================

// function: randNum() returns a random number between 0-1
double randNum() {
	return (double) rand() / RAND_MAX;
}

//	function: getInput() reads in input.txt and sets all of the global variables
void getInput() {
	// Strings to store line by line, variable name, start, and final value
	char line[256];
	char* variable;
	char* start;
	char* last;

	// Uses the file "input.txt"
	fstream input;
	input.open("input1.txt", fstream::in);

	// Go through the input file line by line, tokenize the line into three strings
	input.getline(line,256);
	while (strcmp(line, "") != 0) {
		
		variable = strtok(line, " ");
		start = strtok(NULL, " ");
		last = strtok(NULL, " ");

		// cout << variable << " " << start << " " << last << endl;
		// outfile <<  variable << " " << start << " " << last << endl;
		
		// Find and set the given variable
		if (strcmp(variable, "leval") == 0) {
			leval[0] = leval[1] = atoi(start);
			leval[2] = atoi(last);
		}
		else if (strcmp(variable, "rounds") == 0) {
			rounds[0] = rounds[1] = atoi(start);
			rounds[2] = atoi(last);
		}
		else if (strcmp(variable, "popsize") == 0) {
			popsize[0] = popsize[1] = atoi(start);
			popsize[2] = atoi(last);
		}
		else if (strcmp(variable, "a") == 0) { //6/6/12
			a[0] = a[1] = atof(start);
			a[2] = atof(last);
		}
		else if (strcmp(variable, "bubbleThreshold") == 0) {  //6/6/12
			bubbleThreshold[0] = bubbleThreshold[1] = atof(start);
			bubbleThreshold[2] = atof(last);
		}
		else if (strcmp(variable, "g") == 0) {
			g[0] = g[1] = atoi(start);
			g[2] = atoi(last);
		}
		else if (strcmp(variable, "linit") == 0) {
			linit[0] = linit[1] = atoi(start);
			linit[2] = atoi(last);
		}
		else if (strcmp(variable, "traderLimit") == 0) {
			traderLimit[0] = traderLimit[1] = atoi(start);
			traderLimit[2] = atoi(last);
		}
		else if (strcmp(variable, "fundTrader") == 0) {
			fundTrader[0] = fundTrader[1] = atoi(start);
			fundTrader[2] = atoi(last);
		}
		else if (strcmp(variable, "numLook") == 0) {
			numLook[0] = numLook[1] = atoi(start);
			numLook[2] = atoi(last);
		}
		else if (strcmp(variable, "trackAgent") == 0) {
			trackAgent[0] = trackAgent[1] = atoi(start);
			trackAgent[2] = atoi(last);
		}
		else if (strcmp(variable, "startDist") == 0) {
			startDist[0] = startDist[1] = atoi(start);
			startDist[2] = atoi(last);
		}
		else if (strcmp(variable, "endDist") == 0) {
			endDist[0] = endDist[1] = atoi(start);
			endDist[2] = atoi(last);
		}
		else if (strcmp(variable, "runs") == 0) {
			runs[0] = runs[1] = atoi(start);
			runs[2] = atoi(last);
		}
		else if (strcmp(variable, "numSets") == 0) {
			numSets[0] = numSets[1] = atoi(start);
			numSets[2] = atoi(last);
		}
		else if (strcmp(variable, "noiserange") == 0) {
			noiserange[0] = noiserange[1] = atof(start);
			noiserange[2] = atof(last);
		}
		else if (strcmp(variable, "pupdate") == 0) {
			pupdate[0] = pupdate[1] = atof(start);
			pupdate[2] = atof(last);
		}
		else if (strcmp(variable, "pcompare") == 0) {
			pcompare[0] = pcompare[1] = atof(start);
			pcompare[2] = atof(last);
		}
		else if (strcmp(variable, "pcross") == 0) {
			pcross[0] = pcross[1] = atof(start);
			pcross[2] = atof(last);
		}
		else if (strcmp(variable, "pmutate") == 0) {
			pmutate[0] = pmutate[1] = atof(start);
			pmutate[2] = atof(last);
		}
		else if (strcmp(variable, "pshock") == 0) {
			pshock[0] = pshock[1] = atof(start);
			pshock[2] = atof(last);
		}
		else if (strcmp(variable, "mfrangeHigh") == 0) {
			mfrangeHigh[0] = mfrangeHigh[1] = atof(start);
			mfrangeHigh[2] = atof(last);
		}
		else if (strcmp(variable, "mfrangeLow") == 0) {
			mfrangeLow[0] = mfrangeLow[1] = atof(start);
			mfrangeLow[2] = atof(last);
		}
		else if (strcmp(variable, "cfrange") == 0) {
			cfrange[0] = cfrange[1] = atof(start);
			cfrange[2] = atof(last);
		}
		else if (strcmp(variable, "pbuy") == 0) {
			pbuy[0] = pbuy[1] = atof(start);
			pbuy[2] = atof(last);
		}
		else if (strcmp(variable, "psell") == 0) {
			psell[0] = psell[1] = atof(start);
			psell[2] = atof(last);
		}
		else if (strcmp(variable, "minTrade") == 0) {
			minTrade[0] = minTrade[1] = atof(start);
			minTrade[2] = atof(last);
		}
		else if (strcmp(variable, "bidAskSpread") == 0) {
			bidAskSpread[0] = bidAskSpread[1] = atof(start);
			bidAskSpread[2] = atof(last);
		}
		else if (strcmp(variable, "interest") == 0) {
			interest[0] = interest[1] = atof(start);
			interest[2] = atof(last);
		}	
		else if (strcmp(variable, "dividend") == 0) {
			dividend[0] = dividend[1] = atof(start);
			dividend[2] = atof(last);
		}	
		else if (strcmp(variable, "startPrice") == 0) {
			startPrice[0] = startPrice[1] = atof(start);
			startPrice[2] = atof(last);
		}
		else if (strcmp(variable, "startShares") == 0) {
			startShares[0] = startShares[1] = atof(start);
			startShares[2] = atof(last);
		}
		else if (strcmp(variable, "startBonds") == 0) {
			startBonds[0] = startBonds[1] = atof(start);
			startBonds[2] = atof(last);
		}
		else if (strcmp(variable,"sigmaRange") == 0) {
			sigmaRange[0] = sigmaRange[1] = atof(start);
			sigmaRange[2] = atof(last);
		}
        else if (strcmp(variable, "alphaDiv") == 0) {
			alphaDiv[0] = alphaDiv[1] = atof(start);
			alphaDiv[2] = atof(last);
		}
        else if (strcmp(variable, "betaDiv") == 0) {
			betaDiv[0] = betaDiv[1] = atof(start);
			betaDiv[2] = atof(last);
		}
            else if (strcmp(variable, "shockRange") == 0) {
			shockRange[0] = shockRange[1] = atof(start);
			shockRange[2] = atof(last);
		}
		else if (strcmp(variable, "geneA") == 0) {
			geneA[0] = geneA[1] = atof(start);
			geneA[2] = atof(last);
		}
		else if (strcmp(variable, "geneB") == 0) {
			geneB[0] = geneB[1] = atof(start);
			geneB[2] = atof(last);
		}
		else if (strcmp(variable, "geneC") == 0) {
			geneC[0] = geneC[1] = atof(start);
			geneC[2] = atof(last);
		}
		else if (strcmp(variable, "geneD") == 0) {
			geneD[0] = geneD[1] = atof(start);
			geneD[2] = atof(last);
		}
		else if (strcmp(variable, "geneE") == 0) {
			geneE[0] = geneE[1] = atof(start);
			geneE[2] = atof(last);
		}
		else if (strcmp(variable, "geneF") == 0) {
			geneF[0] = geneF[1] = atof(start);
			geneF[2] = atof(last);
		}
		else if (strcmp(variable, "geneG") == 0) {
			geneG[0] = geneG[1] = atof(start);
			geneG[2] = atof(last);
		}
		else if (strcmp(variable, "randSeed") == 0) {
			randSeed[0] = randSeed[1] = atoi(start);
			randSeed[2] = atoi(last);
		}
		else if (strcmp(variable, "numa") == 0) {               //05/20/2013   Jim
			numa[0] = numa[1] = atoi(start);
			numa[2] = atoi(last);
		}
		else if (strcmp(variable, "frule") == 0) {               //06/21/2013   CG
			frule[0] = frule[1] = atoi(start);
			frule[2] = atoi(last);
		}
		else {
			cout << "Variable name: " << variable << " not recognized. No value set." << endl;
		}  		
		input.getline(line, 256);
	}
	input.close();
}

// function: calcAverageGenes calculates the average genes for the population of agents
// Also calculates the distance from the Minimal State Value Equilibrium
void calcAverageGenes(const agentList &agents, listList &averageGenes, 
					dlist &msvDist, dlist &aveDist, double p) {
	dlist period;
	double dist;
	double asum, bsum, csum, dsum, esum, fsum, gsum;
	asum = bsum = csum = dsum = esum = fsum = gsum = 0;
	
	for (int i = 0; i < popsize[0]; i++) {
		asum += agents[i].getA();
		bsum += agents[i].getB();
		csum += agents[i].getC();
		dsum += agents[i].getD();
		esum += agents[i].getE();
		fsum += agents[i].getF();
		gsum += agents[i].getG();
	}
	period.push_back(asum / popsize[0]);
	period.push_back(bsum / popsize[0]);
	period.push_back(csum / popsize[0]);
	period.push_back(dsum / popsize[0]);
	period.push_back(esum / popsize[0]);
	period.push_back(fsum / popsize[0]);
	period.push_back(gsum / popsize[0]);
	
	dist = pow((double)	pow(period[0], 2) + pow(period[1], 2) + pow(period[2], 2) + 
						pow(period[3], 2) + pow(period[4], 2) + pow(period[5], 2) + 
						pow(period[6], 2), (double) 0.5);
        
	msvDist.push_back(dist);
    
	dist = asum / popsize[0];
    aveDist.push_back(dist);
        
	averageGenes.push_back(period);
}

// function: calcAverageGenesAndPrice calculates the average genes for the population of agents
// Also calculates the distance from the Minimal State Value Equilibrium
// Also calculates the price that would make the representative agent indifferent between stocks and bonds //8/2/06
// note 
void calcAverageGenesAndPrice(const agentList &agents, dlist &price,  
							const dlist &rates, const dlist &dividends, 
							listList &averageGenes, dlist &msvDist, dlist &aveDist, 
							double p, int t, double xstar) {
	dlist period;
	double dist;
	double tempprice;
	double asum, bsum, csum, dsum, esum, fsum, gsum;
	asum = bsum = csum = dsum = esum = fsum = gsum = 0;
	agent repagent;
	double repforecast;
	
	
	for (int i = 0; i < popsize[0]; i++) {
		asum += agents[i].getA();
		bsum += agents[i].getB();
		csum += agents[i].getC();
		dsum += agents[i].getD();
		esum += agents[i].getE();
		fsum += agents[i].getF();
		gsum += agents[i].getG();
	}
	period.push_back(asum / popsize[0]);
	period.push_back(bsum / popsize[0]);
	period.push_back(csum / popsize[0]);
	period.push_back(dsum / popsize[0]);
	period.push_back(esum / popsize[0]);
	period.push_back(fsum / popsize[0]);
	period.push_back(gsum / popsize[0]);
	
	// 8/2/06
	repagent.setA(period[0]);
	repagent.setB(period[1]);
	repagent.setC(period[2]);
	repagent.setD(period[3]);
	repagent.setE(period[4]);
	repagent.setF(period[5]);			
	repagent.setG(period[6]);
	
	dist = pow((double)	pow(period[0], 2) + pow(period[1], 2) + pow(period[2], 2) + 
						pow(period[3], 2) + pow(period[4], 2) + pow(period[5], 2) + 
						pow(period[6], 2), (double) 0.5);
    
    repforecast = repagent.calcForecast(price,dividends,t,xstar);
    //tempprice = 10; //***
    tempprice = (repforecast / (1+rates[t]));
    price.push_back(tempprice); //***
        
	msvDist.push_back(dist);
    
	dist = asum / popsize[0];
    aveDist.push_back(dist);
        
	averageGenes.push_back(period);
}

// Added by Yinghan Ding, 03/05/2012, and c.g. 6/12
void calcAverageGenesAndPriceAndVolatility(const agentList &agents, dlist &price,  
											dlist &volatility, dlist &exbar, 
											dlist &axstar, 
											dlist &pstar, const dlist &rates, 
											const dlist &dividends, 
											listList &averageGenes, 
											dlist &msvDist, dlist &aveDist, double p, 
											int t, double a) {
	dlist period;
	double dist;
	double tempprice;
	double asum, bsum, csum, dsum, esum, fsum, gsum;
	asum = bsum = csum = dsum = esum = fsum = gsum = 0;
	agent repagent;
	double repforecast;
	
	
	for (int i = 0; i < popsize[0]; i++) {
		asum += agents[i].getA();
		bsum += agents[i].getB();
		csum += agents[i].getC();
		dsum += agents[i].getD();
		esum += agents[i].getE();
		fsum += agents[i].getF();
		gsum += agents[i].getG();
	}
	period.push_back(asum / popsize[0]);
	period.push_back(bsum / popsize[0]);
	period.push_back(csum / popsize[0]);
	period.push_back(dsum / popsize[0]);
	period.push_back(esum / popsize[0]);
	period.push_back(fsum / popsize[0]);
	period.push_back(gsum / popsize[0]);
	
	// 8/2/06
	repagent.setA(period[0]);
	repagent.setB(period[1]);
	repagent.setC(period[2]);
	repagent.setD(period[3]);
	repagent.setE(period[4]);
	repagent.setF(period[5]);			
	repagent.setG(period[6]);
	
	dist = pow((double)	pow(period[0], 2) + pow(period[1], 2) + 
						pow(period[2], 2) + pow(period[3], 2) + 
						pow(period[4], 2) + pow(period[5], 2) + 
						pow(period[6], 2), (double) 0.5);
    // track pstar as well, output in the write to Matrix function.
    double xstar = axstar[t-1];
    repforecast = repagent.calcForecast(price,dividends,t,xstar);
    //tempprice = 10; //***

    // here we need to modify the arbitrage condition, Yinghan Ding 03/05/2012
    //double a = 2.0;          // 0.2 suggested in Branch and Evans? i see .75, higher elsewhere
    double supply = 1;       // for now

    //dlist avbar;
    double aveAx;
    double sumAx = 0;
    double sumVar = 0;
	double variance = 0;
	double sumVol = 0;
	double vol = 0;
	
	//alternate volatility measures
	
    // 1. true sample variance of recent excess returns
    /*-------------------------------------------------------------------------
    for (int i = leval[0]; i > 0; i--){
      sumAx = sumAx + price[t-i] + dividends[t-i] - (1+rates[t-i]) * price[t-i-1];
    }
    aveAx = sumAx / leval[0];
    for (int i = leval[0]; i > 0; i--){
      sumVol = sumVol + (price[t-i]+dividends[t-i] - (1+rates[t-i]) * price[t-i-1] - aveAx)
                          *(price[t-i]+dividends[t-i] - (1+rates[t-i]) * price[t-i-1] - aveAx);
    }
	vol = sumVol / leval[0];
	volatility.push_back(vol); //6/6/12
	------------------------------------------------------------------------ */
	//avbar.push_back(volatility);
	
	// 2. squared change in price plus dividend //6/8/12
    /*-------------------------------------------------------------------------
	double volScale = 25;
    for (int i = leval[0]; i > 0; i--){
      sumVol = sumVol + (price[t-i]+dividends[t-i] - price[t-i-1] - dividends[t-i-1])
                          *(price[t-i]+dividends[t-i] - price[t-i-1] - dividends[t-i-1])
                          *volScale;
    }
    vol = sumVol / leval[0];
	volatility.push_back(vol); //6/8/12
    ----------------------------------------------------------------------- */
    
    // 3. squared percentage change in price plus dividend //6/8/12
    /*-------------------------------------------------------------------------
    double volScale = 13.0; //13 near critical
    for (int i = leval[0]; i > 0; i--){
      sumVol = sumVol + ((price[t-i]+dividends[t-i] - price[t-i-1] - dividends[t-i-1])/(price[t-i-1] + dividends[t-i-1]))
                          *((price[t-i]+dividends[t-i] - price[t-i-1] - dividends[t-i-1])/(price[t-i-1] + dividends[t-i-1]))
                          *volScale;
    }
    vol = sumVol / leval[0];
	volatility.push_back(vol); //6/8/12
    ----------------------------------------------------------------------- */

    //4. forecast error of return //6/12/12
    double volScale = 1; //can vary this to scale up the volatility measure 
    for (int i = leval[0]; i > 0; i--){
      sumVol = sumVol + (price[t-i]+dividends[t-i] - exbar[t-i-1])
                          *(price[t-i]+dividends[t-i] - exbar[t-i-1])
                          *volScale;
    }
    vol = sumVol / leval[0];
	volatility.push_back(vol); //6/8/12
    
    //calculate price for round
    tempprice = repforecast / (1+rates[t]) - (a * vol * supply) / (1+rates[t]);
    price.push_back(tempprice); //***
    
    xstar = dividends[0] * (1+rates[t]) / rates[t] - a * variance * supply / 
    		rates[t]; //*** variance should be updated
    axstar.push_back(xstar);
    
    double pstarvalue = dividends[0] / rates[t] - a * variance * supply / 
    		rates[t]; //*** variance should be updated
    pstar.push_back(pstarvalue);
    
	msvDist.push_back(dist);
    
	dist = asum / popsize[0];
    aveDist.push_back(dist);
        
	averageGenes.push_back(period);
}

// function calcWealth calculates the wealth of the agent in terms of bonds (dollars)
// Can accumulate interest, but currently not included
void calcWealth(agentList &agents, const dlist &price, const dlist &rates, 
				const dlist &dividends, int t) {
	double wealth = 0;
	agent trader;
	
	// get rid of these when interest is calculated
	// dummy lines
	double r = rates[t];
	r = dividends[t];
	// end of dummy lines
	
	//double interest;
	for (int i = 0; i < popsize[0]; i++) {
		trader = agents[i];
		//interest = trader.getShares(0)*(1+(double)(1.0/365) * rates[t]);
		//trader.setShares(interest,0);
		//if (t%365 == 0)
		//wealth = trader.getShares(0) + (trader.getShares(1) * price[t]) +dividends[t] ;
		//else
		wealth = trader.getShares(0) + trader.getShares(1) * price[t];
		trader.setWealth(wealth);
		agents[i] = trader;	
	}
}

//Instead of using evolve we will randomly determine if the agent
//should update its forcast rule with the global updated forcast rule
agentList update( const agentList &agentlist ) { 
	agent parent;
	agentList newAgent;
	
	for (int i = 0; i < popsize[0]; i++) {
		parent = agentlist[i];
		
		// Update this agents rule
		if (parent.rdist() == 1) {
			parent.setA(forcastRule.getA());
			parent.setB(forcastRule.getB());
			parent.setC(forcastRule.getC());
			parent.setD(forcastRule.getD());
			parent.setE(forcastRule.getE());
			parent.setF(forcastRule.getF());			
			parent.setG(forcastRule.getG());
		}
		/*
		// for msv case
		if (parent.rdist() == 1) {
			parent.setA(forcastRule.getA());
			parent.setB(0.0);
			parent.setC(0.0);
			parent.setD(0.0);
			parent.setE(0.0);
			parent.setF(0.0);			
			parent.setG(0.0);
		}
		*/
		newAgent.push_back(parent);
	}
	return newAgent;
}
	
// This is where we will set up the matrices and create our global OLS beta values - 3/05
// This is the only place where we use any Matrix operations
// To select a specification, uncomment it in "create the x matrix" and "make a new 
// forecast rule" sections below and change ncx in writeMatrixToDisk function to the 
// value of numcolsx for this specification. 
void doNewForcast(agent & fRule, int t, const dlist & price,  
					const dlist & divs, double xs) {
	dlist priceT;
	dlist divT;

	for (int i = t - 1; i >= t - 2 * leval[0]; i--) {
		priceT.push_back(price[i]);
		divT.push_back(divs[i]);
	}
	
	//-------------------------- Create the x matrix --------------------------

    int numcolsx;
    int loc;
    double* xa;
	switch (forecast_rule)
    {

    case 1:
    // original 7 parameter version:
    // three linear lags, two squared lags, one cross product
	numcolsx = 7; //4/9/06
	xa = new double[numcolsx * leval[0]];
	for (int i = 0; i < 7 * leval[0]; i += 7) {
		//Column 1
		xa[i] = 1.0;
		
		loc = i/7 + 1;
		//Column 2
		xa[i + 1] = priceT[loc] + divT[loc];
		
		//Column 3
		loc++;
		xa[i + 2] = priceT[loc] + divT[loc];
		
		//Column 4
		xa[i + 3] = xa[i + 2] * xa[i + 2];
		
		//Column 5
		loc++;
		xa[i + 4] = priceT[loc] + divT[loc];
		
		//Column 6
		xa[i + 5] = xa[i + 4] * xa[i + 4];
		
		//Column 7
		xa[i + 6] = xa[i + 2] * xa[i + 4];
    }
    break;
   
	case 2:
	// msv version: constant only //4/9/06
    numcolsx = 1; //4/9/06
	xa = new double[numcolsx * leval[0]];
	for (int i = 0; i < numcolsx * leval[0]; i += numcolsx) {
		//Column 1
		xa[i] = 1.0;
		
		loc = i/numcolsx + 1;
		//kill rest of columns 
    }
    break;
    
    
	case 3:
	// ar(1) version: one linear lag  //3/14/06 
	numcolsx = 2; //4/9/06
	xa = new double[numcolsx * leval[0]];
	for (int i = 0; i < numcolsx * leval[0]; i += numcolsx) {
		//Column 1
		xa[i] = 1.0;
		
		loc = i/numcolsx + 1;
		//Column 2
		xa[i + 1] = priceT[loc] + divT[loc];	
		//kill rest of columns
    }
    break;
    
    
    case 4:
	// ar(2) version: two linear lags //3/14/06
	numcolsx = 3; //4/9/06
	xa = new double[numcolsx * leval[0]]; //replace 7 with numcolsx 3/14/06
	for (int i = 0; i < numcolsx * leval[0]; i += numcolsx) {
		//Column 1
		xa[i] = 1.0;
		
		loc = i/numcolsx + 1;
		//Column 2
		xa[i + 1] = priceT[loc] + divT[loc];
		
		//Column 3
		loc++;
		xa[i + 2] = priceT[loc] + divT[loc];
		
		//kill rest of columns
    }
    break;
	
	
    case 5:	
	// ar(2,1) version //3/15/06 one linear lag, second lag squared
    numcolsx = 3; //4/9/06
	xa = new double[ numcolsx * leval[0]]; //replace 7 with 3 3/14/06
	for (int i = 0; i <  numcolsx * leval[0]; i +=  numcolsx) {
		//Column 1
		xa[i] = 1.0;
		
		loc = i/ numcolsx + 1;
		//Column 2
		xa[i + 1] = priceT[loc] + divT[loc] ;
		
		//Column 3
		loc++;
		//xa[i + 2] = priceT[loc] + divT[loc] ;
		xa[i + 2] = (priceT[loc] + divT[loc]) * (priceT[loc] + divT[loc]);				
		//kill rest of columns
    }
    break;
	
	
	case 6:
	// ar(2,2) version //3/14/06 two linear lags, plus second lag squared
	numcolsx = 4; //4/9/06
	xa = new double[numcolsx * leval[0]]; //replace 7 with 4 3/14/06
	for (int i = 0; i < numcolsx * leval[0]; i += numcolsx) {
		//Column 1
		xa[i] = 1.0;
		
		loc = i/numcolsx + 1;
		//Column 2
		xa[i + 1] = priceT[loc] + divT[loc] ;
		
		//Column 3
		loc++;
		xa[i + 2] = priceT[loc] + divT[loc] ;
		
		//Column 4
		xa[i + 3] = xa[i + 2] * xa[i + 2];
		
		//kill rest of columns
    }
    break;
	
	
	case 7:
	// ar(3) version //3/15/06 three linear lags 
	numcolsx = 4; //4/9/06
	xa = new double[numcolsx * leval[0]]; //replace 7 with number of cols of x 3/14/06
	for (int i = 0; i < numcolsx * leval[0]; i += numcolsx) {
		//Column 1
		xa[i] = 1.0;
		
		loc = i/numcolsx + 1;
		//Column 2
		xa[i + 1] = priceT[loc] + divT[loc] ;
		
		//Column 3
		loc++;
		xa[i + 2] = priceT[loc] + divT[loc] ;
				
		//Column 4
		//xa[i + 3] = xa[i + 2] * xa[i + 2];
		loc++;
		xa[i + 3] = priceT[loc] + divT[loc] ;
		
		//kill rest of columns		
    }
    break; 
	
	
	case 8:
	// ar(3,1) version //3/15/06 three linear lags and a cross product
	numcolsx = 5; //4/9/06
	xa = new double[numcolsx * leval[0]]; //replace 7 with number of cols of x 3/14/06
	for (int i = 0; i < numcolsx * leval[0]; i += numcolsx) {
		//Column 1
		xa[i] = 1.0;
		
		loc = i/numcolsx + 1;
		//Column 2
		xa[i + 1] = priceT[loc] + divT[loc] ;
		
		//Column 3
		loc++;
		xa[i + 2] = priceT[loc] + divT[loc] ;
				
		//Column 4
		//xa[i + 3] = xa[i + 2] * xa[i + 2];
		loc++;
		xa[i + 3] = priceT[loc] + divT[loc] ;
				
		//Column 5
		//loc++;
		//xa[i + 4] = priceT[loc] + divT[loc] - xs;
		xa[i + 4] = xa[i + 2] * xa[i + 3];
		
		//kill rest of columns
    }
    break;
    
    default:
            cout << "Invalid update rule";
    }//end of switch case

	
	//Matrix x(leval[0], 3, xa); //change 2nd arg to num columns of x
	Matrix x(leval[0], numcolsx, xa); //4/9/06
	delete[] xa;
	//-------------------------- Create the y matrix --------------------------
	
	double ya[leval[0]];
	
	for (int i = 0; i < leval[0]; i++) 
		ya[i] = priceT[i] + divT[i];
		
	Matrix y(leval[0], 1, ya);
	
	//-------------------- Make a new forecast rule (beta) --------------------
	
	//ar(x) version 3/14/06			
	Matrix transX = x.transpose();
	Matrix beta1 = (transX * x).invert() * (transX * y); //replace beta with bata1 which is just 2x1 rather than 7x1
			
	// new array to assemble beta components
    double bb[7];	
	switch (forecast_rule)
    {
           
    case 1:
	// original 7 parameter version
	bb[0] = beta1.getElement(0);
	bb[1] = beta1.getElement(1);
	bb[2] = beta1.getElement(2);
	bb[3] = beta1.getElement(3);
	bb[4] = beta1.getElement(4);
	bb[5] = beta1.getElement(5);
	bb[6] = beta1.getElement(6);
    break;
	
	case 2:
	// msv version: constant only
	bb[0] = beta1.getElement(0);
	bb[1] = 0;
	bb[2] = 0;
	bb[3] = 0;
	bb[4] = 0;
	bb[5] = 0;
	bb[6] = 0;
	break;
	
	case 3:
	// ar1 version: one linear lag
	bb[0] = beta1.getElement(0);
	bb[1] = beta1.getElement(1);
	bb[2] = 0;
	bb[3] = 0;
	bb[4] = 0;
	bb[5] = 0;
	bb[6] = 0;
	break;
	
	case 4:
	// ar(2) version: two linear lags
	bb[0] = beta1.getElement(0);
	bb[1] = beta1.getElement(1);
	bb[2] = beta1.getElement(2);
	bb[3] = 0;
	bb[4] = 0;
	bb[5] = 0;
	bb[6] = 0;
    break;
	
	case 5:
	// ar(2,1) version: one linear lag, plus second lag squared 
	bb[0] = beta1.getElement(0);
	bb[1] = beta1.getElement(1);
	bb[2] = 0;
	bb[3] = beta1.getElement(2);
	bb[4] = 0;
	bb[5] = 0;
	bb[6] = 0;
	break;
	
	case 6:
	// ar(2,2) version: two linear lags, plus second lag squared
	bb[0] = beta1.getElement(0);
	bb[1] = beta1.getElement(1);
	bb[2] = beta1.getElement(2);
	bb[3] = beta1.getElement(3);
	bb[4] = 0;
	bb[5] = 0;
	bb[6] = 0;
	break;
	
	case 7:
	// ar(3) version // three linear lags 
	bb[0] = beta1.getElement(0);
	bb[1] = beta1.getElement(1);
	bb[2] = beta1.getElement(2);
	bb[3] = 0;
	bb[4] = beta1.getElement(3);
	bb[5] = 0;
	bb[6] = 0;
	break;
	
	case 8:
	//ar(3,1) version: three linear lags, plus cross product of second and third
	bb[0] = beta1.getElement(0);
	bb[1] = beta1.getElement(1);
	bb[2] = beta1.getElement(2);
	bb[3] = 0;
	bb[4] = beta1.getElement(3);
	bb[5] = 0;
	bb[6] = beta1.getElement(4);
	break;
	
    default:
            cout << "Invalid update rule";
                
    }//end of switch case
    	
	//new create beta
	Matrix beta(7, 1, bb);
	
	//note: if use this, need to change numcolsx in writeMatrixToDisk below
	if (t == 50000) {						//2/07/06
		writeMatrixToDisk(y, x, beta, 0); 	//2/07/06
	}
	
	
	fRule.updateRule(beta);

}

// get genes for every Agent for certain rounds for geneHistory file output
void updateGeneHistory(bool condition, const agentList & agents, listList* hist) {
				
	if (condition) { 
		dlist temp0, temp1, temp2, temp3, temp4, temp5, temp6;
	
		for (int i = 0; i < popsize[0]; i++) {
			temp0.push_back(agents[i].getA());
			temp1.push_back(agents[i].getB());	
			temp2.push_back(agents[i].getC());
			temp3.push_back(agents[i].getD());	
			temp4.push_back(agents[i].getE());
			temp5.push_back(agents[i].getF());	
			temp6.push_back(agents[i].getG());
		}
		hist[0].push_back(temp0);
		hist[1].push_back(temp1);
		hist[2].push_back(temp2);
		hist[3].push_back(temp3);
		hist[4].push_back(temp4);
		hist[5].push_back(temp5);
		hist[6].push_back(temp6);
	}
}

void doTrades(agentList &agents, dlist &price, double &stocksTraded, double &bondsTraded, int t) { 
	int i;
	int j;
	
	// For every agent (trader1): Look at numLook other agents' bid and ask prices. 
	// Trade if both agents are willing.
    agent trader1;
	agent trader2;
	double buyPrice;
	double buyAmount;
    double buyAmountInShares;
	double sellPrice;
	double sellAmount;
    double sellAmountInDollars;
	
	// use a list of random numbers to pick which agents trade this period.
	dlist currentTraders(getNumbers(traderLimit[0], -1));
	
	for (i = 0; i < traderLimit[0]; i++) {
		trader1 = agents[(int)currentTraders[i]];
		// Pick a number (numLook) of agents to look at 
		// and order them from smallest ask price to largest
		dlist contacts(getNumbers(numLook[0], i));
		orderContacts(agents,contacts);
		// Buy Shares
		for (j = 0; j < numLook[0]; j++) {
			trader2 = agents[(int)contacts[j]];
			buyPrice = 0;
			buyAmount = 0;
			sellPrice = 0;
			sellAmount = 0;
			
			// Compare trader2's ask price to agent 1's bid pice. 
			// If the bid price of trader1 is less than or equal to the ask price of 
			// trader2, buy as much as trader1 can at trader2 ask price.
			
			if (trader1.getOrder().buyAmount > 0 && trader2.getOrder().sellAmount > 0) {
				if (trader1.getOrder().bid >= trader2.getOrder().ask && 
						trader2.getOrder().ask > 0) {
					buyPrice = trader2.getOrder().ask;
					if (trader1.getOrder().buyAmount < 
							trader2.getOrder().sellAmount * buyPrice)
						buyAmount = trader1.getOrder().buyAmount;
					else
						buyAmount = trader2.getOrder().sellAmount*buyPrice;	
						
				}
			}
			
			if (buyPrice == 0)
				buyAmountInShares = 0;
			else
				buyAmountInShares = buyAmount / buyPrice;
			
			// Trade Shares
			trader1.setShares(trader1.getShares(0) - buyAmount ,0);
			trader1.setShares(trader1.getShares(1) + buyAmountInShares,1);
			trader2.setShares(trader2.getShares(0) + buyAmount,0);
			trader2.setShares(trader2.getShares(1) - buyAmountInShares,1);
			
			// Adjust orders after trades
			order trader1Order = trader1.getOrder();
			order trader2Order = trader2.getOrder();
			trader1Order.buyAmount = trader1Order.buyAmount - buyAmount;
			trader2Order.sellAmount = trader2Order.sellAmount - buyAmountInShares;
						
			trader1.setOrder(trader1Order);
			trader2.setOrder(trader2Order);
				
			// update buyer and seller
			agents[(int)currentTraders[i]] = trader1;
			agents[(int)contacts[j]] = trader2;
			stocksTraded = stocksTraded +  buyAmountInShares;
			bondsTraded = bondsTraded + buyAmount;
			
			if 	(4415 - 1 <= t && t <= 4420 - 1 && buyPrice > 0) { //cg 11/15/04 track sales around an extreme event
				cout << "trading period " << t+1 << " agent " << currentTraders[i] << " buys from agent " 
				<< contacts[j] << " for price = " << buyPrice << endl;
				}			
				
		}
		// sell shares
		for (j = numLook[0] - 1; j >= 0; j--) {
			trader2 = agents[(int)contacts[j]];
			buyPrice = 0;
			buyAmount = 0;
			sellPrice = 0;
			sellAmount = 0;
			
			// Compare trader2's bid price to agent 1's ask.
			// If the ask price of trader1 is greater than or equal to the bid price of 
			// trader2, sell as much as possible at trader2 bid price.
			
			if (trader1.getOrder().sellAmount > 0 && trader2.getOrder().buyAmount > 0) {
				if (trader1.getOrder().ask <= trader2.getOrder().bid && 
						trader2.getOrder().bid > 0) {
					sellPrice = trader2.getOrder().bid;
					if (trader1.getOrder().sellAmount < trader2.getOrder().buyAmount/sellPrice)
						sellAmount = trader1.getOrder().sellAmount;
					else
						sellAmount = trader2.getOrder().buyAmount/sellPrice;
												
				}
			}
				
			// Trade Shares
			
            // sellAmount of currency 2 in terms of currency 1
			sellAmountInDollars = sellAmount * sellPrice;
				
			trader1.setShares(trader1.getShares(0) + sellAmountInDollars,0);
			trader1.setShares(trader1.getShares(1) - sellAmount,1);
			trader2.setShares(trader2.getShares(0) - sellAmountInDollars,0);
			trader2.setShares(trader2.getShares(1) + sellAmount,1);
			
			// Adjust orders after trades
			order trader1Order = trader1.getOrder();
			order trader2Order = trader2.getOrder();
			trader1Order.sellAmount = trader1Order.sellAmount - sellAmount;
			trader2Order.buyAmount = trader2Order.buyAmount - sellAmountInDollars;
						
			trader1.setOrder(trader1Order);
			trader2.setOrder(trader2Order);
				
			// update buyer and seller
			agents[(int)currentTraders[i]] = trader1;
			agents[(int)contacts[j]] = trader2;
			stocksTraded = stocksTraded + sellAmount;
			bondsTraded = bondsTraded + sellAmountInDollars;	
			
			if 	(4415 - 1 <= t && t <= 4420 - 1 && sellPrice > 0) {  //cg 11/15/04 track sales around an extreme event
				cout << " trading period " << t+1 << " agent " << currentTraders[i] << " sells to agent "	
				<< contacts[j] << " for price = " << sellPrice <<endl;
			}				
						
		}
		// Update Current Price P(t)
		if (stocksTraded > 0)
			price[t] = bondsTraded/stocksTraded; 
	}	
}

// RETURNS a list of size howMany, randomly chosen from {0, ... , popsize[0]} \ {badNum}
dlist getNumbers(int howMany, int badNum) {
	int i;
	dlist numbers;
	dlist randomList;
	
	// Create a dlist of Numbers between {0,n} excluding badNum
	for (i = 0; i < popsize[0]; i++) {
		if (i != badNum)
			numbers.push_back(i);
	}
	// Generate the selection, using the standard k-select algorithm
	// See Nijenhuis & Wulf, for example.
	for (i = 0; i < howMany; i++) {
		int pos = i + rand() % (numbers.size() - i);
		double save = numbers[pos];
		numbers[pos] = numbers[i];
		randomList.push_back(save);
	}
	return randomList;
}

// Orders the list of contacts from best to worst wrt the ask price of the agent at the specified locations. 
void orderContacts(const agentList &agents, dlist &contacts) {
	for (int i = 0; i < contacts.size() - 1; i++) {
		for (int j = i + 1; j < contacts.size(); j++) {
			if (agents[(int)contacts[i]].getOrder().ask > 
					agents[(int)contacts[j]].getOrder().ask) {
				int temp = (int)contacts[j];
				contacts[j] = (int)contacts[i];
				contacts[i] = temp;
			}
		}
	}
}

void writeMatrixToDisk(const Matrix & y, const Matrix & x, const Matrix & beta, int count ) {

	//We are going to write y and x to one file.  This file will be tab-delimited allowing for easy use in Stata
	//The other file will contain beta for comparison with Stata.
	fstream matrix;
	fstream answer;
	
	char dataFile1[50];
	char dataFile2[50];
	
	if (count == 0)
		strcpy(dataFile1, "Test1.txt");
	else if (count == 1)
		strcpy(dataFile1, "Test2.txt");
	else 
		strcpy(dataFile1, "Test3.txt" );
	
	matrix.open(dataFile1, ios::out);
	
	cout << "Writing Matrices to disk" << endl;
	
	int ncx; //need to change this to match numcolsx in doNewForcast above
	
	switch (forecast_rule)
    {

    case 1:
         ncx = 7;
    break;
      
    case 2: 
         ncx = 1;
    break;
    
	case 3:
         ncx = 2;
    break;
        
    case 4: 
         ncx = 3;
    break;
        
    case 5:
         ncx = 3;
    break;
        
    case 6: 
         ncx = 4;
    break;
        
    case 7:
         ncx = 4;
    break;
        
    case 8: 
         ncx = 5;
    break;
    
    default:
            cout << "Invalid update rule";
    }//end of switch case
    
    for (int i = 0; i < y.getRows() * y.getCols(); i++) {
		matrix << y.getElement(i) << '\t'; 
		
		for (int j = i * x.getCols(); j < i * x.getCols() + ncx ; j++) //ncx is numcolsx 
			matrix << x.getElement(j) << '\t';
		
		matrix << endl;
	}
	
	matrix.close();
	
	if (count == 0)
		strcpy(dataFile2, "Beta1.txt");
	else if (count == 1)
		strcpy(dataFile2, "Beta2.txt");
	else 
		strcpy(dataFile2, "Beta3.txt" );
	
	answer.open(dataFile2, ios::out);
	
	for (int i = 0; i < beta.getRows() * beta.getCols(); i++)
		answer << beta.getElement(i) << endl;	
		
	answer.close();
}

void writeToDisk(const dlist &price, const dlist &volatility, const dlist &exbar, 
				const dlist &axstar, const dlist &pstar, const dlist &volume, 
				const dlist &rates, const dlist &dividends, 
				const listList &wealthHistory, const dlist &bondHistory, 
				const dlist &stockHistory, const listList &averageGenes, 
				const listList* historyGene, 
				const listList &distanceHistory, dlist &msvDist, 
				dlist &aveDist, int sim) {
	int i,j;
	
	cout << "Writing Data to Disk" << endl;
	sim++;
	char buffer[4];
	sprintf(buffer, "%d", sim); 

	fstream filestr;
	char dataFile[20];
	strcpy(dataFile, "Sim");
	strcat(dataFile,buffer);
	strcat(dataFile, "data.txt");
	filestr.open(dataFile,fstream::out);
	for (i = 0; i < rounds[0]; i++) {
  		filestr << setprecision(10) << price[i] << " " << volatility[i] << " " << exbar[i] << " " << axstar[i] << " " <<
    		pstar[i] << " " << volume[i] << " " << rates[i] << " " <<
    		dividends[i] <<'\n';
    	}
    	filestr.close();
    	
 	fstream wealthstr;
 	char wealthFile[20];
	strcpy(wealthFile, "Sim");
	strcat(wealthFile,buffer);
	strcat(wealthFile, "wealth.txt");
	wealthstr.open(wealthFile,fstream::out);
	for (i = 0; i < rounds[0]; i++) { 
		if (i % 1000 == 0) {  	/* if statement added cg 4/27/04 - only print every N rounds */
			wealthstr << setprecision(10) << wealthHistory[i][trackAgent[0]] << " " << bondHistory[i] << " " << stockHistory[i];
			wealthstr << '\n';
			}					/* close if statement */
		}						
	wealthstr.close();

	fstream wealthDist;
	char wealthDistFile[20];
	strcpy(wealthDistFile, "Sim");
	strcat(wealthDistFile,buffer);
	strcat(wealthDistFile, "wealthDist.txt");
	wealthDist.open(wealthDistFile, fstream::out);
	for (i=0; i<popsize[0]; i++) 
		wealthDist << setprecision(10) << "Agent #" << i << ": $" <<wealthHistory[rounds[0]-1][i] << endl;
	wealthDist.close();
	
	
	fstream genes;
	char genesFile[20];
	strcpy(genesFile, "Sim");
	strcat(genesFile,buffer);
	strcat(genesFile, "genes.txt");
	genes.open(genesFile,fstream::out);
	for (i = 0; i < rounds[0]; i++) {
		for (j = 0; j < 7; j++) {
				genes << setprecision(10) << averageGenes[i][j] << " ";
		}
		genes  << " " << msvDist[i] <<  " " << aveDist[i] << '\n';
	}
	genes.close();
	
	/*
	fstream geneHist;
	char genesHistFile[20];
	strcpy(genesHistFile, "Sim");
	strcat(genesHistFile,buffer);
	strcat(genesHistFile, "genesHist.txt");
	geneHist.open(genesHistFile,fstream::out);
	for (i=0; i<historyGene[1].size(); i++) {
		for (j=0; j<popsize[0]; j++) 
			geneHist << setprecision(10) << historyGene[1][i][j] << " ";
		geneHist << endl;
		for (j=0; j<popsize[0]; j++) 
			geneHist << setprecision(10) << historyGene[2][i][j] << " ";
		geneHist << endl;
		geneHist << endl;
	}
	geneHist.close();
	*/
	
	fstream geneHist0;
	char genesHistFile0[20];
	strcpy(genesHistFile0, "Sim");
	strcat(genesHistFile0,buffer);
	strcat(genesHistFile0, "genesHista0.txt");
	geneHist0.open(genesHistFile0,fstream::out);
	for (i = 0; i < historyGene[0].size(); i++) {
		for (j = 0; j < popsize[0]; j++) 
			geneHist0 << setprecision(10) << historyGene[0][i][j] << " ";
		//geneHist << endl;
		//for (j=0; j<popsize[0]; j++) 
		//	geneHist << setprecision(10) << historyGene[2][i][j] << " ";
		//geneHist << endl;
		geneHist0 << endl;
	}
	geneHist0.close();
	
	fstream geneHist1;
	char genesHistFile1[20];
	strcpy(genesHistFile1, "Sim");
	strcat(genesHistFile1,buffer);
	strcat(genesHistFile1, "genesHista1.txt");
	geneHist1.open(genesHistFile1,fstream::out);
	for (i = 0; i < historyGene[1].size(); i++) {
		for (j = 0; j < popsize[0]; j++) 
			geneHist1 << setprecision(10) << historyGene[1][i][j] << " ";
		//geneHist << endl;
		//for (j=0; j<popsize[0]; j++) 
		//	geneHist << setprecision(10) << historyGene[2][i][j] << " ";
		//geneHist << endl;
		geneHist1 << endl;
	}
	geneHist1.close();

	fstream geneHist2;
	char genesHistFile2[20];
	strcpy(genesHistFile2, "Sim");
	strcat(genesHistFile2,buffer);
	strcat(genesHistFile2, "genesHista2.txt");
	geneHist2.open(genesHistFile2,fstream::out);
	for (i = 0; i < historyGene[2].size(); i++) {
		//for (j=0; j<popsize[0]; j++) 
		//	geneHist << setprecision(10) << historyGene[1][i][j] << " ";
		//geneHist << endl;
		for (j=0; j<popsize[0]; j++) 
			geneHist2 << setprecision(10) << historyGene[2][i][j] << " ";
		//geneHist << endl;
		geneHist2 << endl;
	}
	geneHist2.close();
	
	fstream geneHist3;
	char genesHistFile3[20];
	strcpy(genesHistFile3, "Sim");
	strcat(genesHistFile3,buffer);
	strcat(genesHistFile3, "genesHista3.txt");
	geneHist3.open(genesHistFile3,fstream::out);
	for (i = 0; i < historyGene[3].size(); i++) {
		//for (j=0; j<popsize[0]; j++) 
		//	geneHist << setprecision(10) << historyGene[1][i][j] << " ";
		//geneHist << endl;
		for (j=0; j<popsize[0]; j++) 
			geneHist3 << setprecision(10) << historyGene[3][i][j] << " ";
		//geneHist << endl;
		geneHist3 << endl;
	}
	geneHist3.close();
	
	fstream geneHist4;
	char genesHistFile4[20];
	strcpy(genesHistFile4, "Sim");
	strcat(genesHistFile4,buffer);
	strcat(genesHistFile4, "genesHista4.txt");
	geneHist4.open(genesHistFile4,fstream::out);
	for (i = 0; i < historyGene[4].size(); i++) {
		//for (j=0; j<popsize[0]; j++) 
		//	geneHist << setprecision(10) << historyGene[1][i][j] << " ";
		//geneHist << endl;
		for (j=0; j<popsize[0]; j++) 
			geneHist4 << setprecision(10) << historyGene[4][i][j] << " ";
		//geneHist << endl;
		geneHist4 << endl;
	}
	geneHist4.close();
	
	fstream geneHist5;
	char genesHistFile5[20];
	strcpy(genesHistFile5, "Sim");
	strcat(genesHistFile5,buffer);
	strcat(genesHistFile5, "genesHista5.txt");
	geneHist5.open(genesHistFile5,fstream::out);
	for (i = 0; i < historyGene[5].size(); i++) {
		//for (j=0; j<popsize[0]; j++) 
		//	geneHist << setprecision(10) << historyGene[1][i][j] << " ";
		//geneHist << endl;
		for (j=0; j<popsize[0]; j++) 
			geneHist5 << setprecision(10) << historyGene[5][i][j] << " ";
		//geneHist << endl;
		geneHist5 << endl;
	}
	geneHist5.close();

	fstream geneHist6;
	char genesHistFile6[20];
	strcpy(genesHistFile6, "Sim");
	strcat(genesHistFile6,buffer);
	strcat(genesHistFile6, "genesHista6.txt");
	geneHist6.open(genesHistFile6,fstream::out);
	for (i = 0; i < historyGene[6].size(); i++) {
		//for (j=0; j<popsize[0]; j++) 
		//	geneHist << setprecision(10) << historyGene[1][i][j] << " ";
		//geneHist << endl;
		for (j=0; j<popsize[0]; j++) 
			geneHist6 << setprecision(10) << historyGene[6][i][j] << " ";
		//geneHist << endl;
		geneHist6 << endl;
	}
	geneHist6.close();


	fstream distHist;
	char distHistFile[20];
	strcpy(distHistFile, "Sim");
	strcat(distHistFile,buffer);
	strcat(distHistFile, "distHist.txt");
	distHist.open(distHistFile,fstream::out);
	for (i = 0; i < distanceHistory.size(); i++) {
		for (int j = 0; j < popsize[0]; j++) 
			distHist << setprecision(10) << distanceHistory[i][j] << " ";
		distHist << endl;
	}
	distHist.close();
	
}
			
void incrementGlobals() {
	if (runs[0] > 1) {
		int rm1 = runs[0] - 1;
		
		rounds[0] += (rounds[2] - rounds[1]) / rm1;
		popsize[0] += (popsize[2] - popsize[1]) / rm1;
		leval[0] += (leval[2] - leval[1]) / rm1;
		g[0] += (g[2] - g[1]) / rm1 ;
		linit[0] += (linit[2] - linit[1]) / rm1;
		//a[0] += (a[2] - a[1]) / rm1; //6/6/12
		bubbleThreshold[0] += (bubbleThreshold[2] - bubbleThreshold[1]) / rm1;  //6/6/12
		traderLimit[0] += (traderLimit[2] - traderLimit[1]) / rm1;
		fundTrader[0] += (fundTrader[2] - fundTrader[1]) / rm1;
		numLook[0] += (numLook[2] - numLook[1]) / rm1;
		trackAgent[0] += (trackAgent[2] - trackAgent[1]) / rm1;
		startDist[0] += (startDist[2] - startDist[1]) / rm1;
		endDist[0] += (endDist[2] - endDist[1]) / rm1;
		randSeed[0] += (randSeed[2] - randSeed[1]) / rm1;
		noiserange[0] += (noiserange[2] - noiserange[1]) / rm1;
		sigmaRange[0] += (sigmaRange[2] - sigmaRange[1]) / rm1;
		numSets[0] += (numSets[2] - numSets[1]) / rm1;
		pupdate[0] += (pupdate[2] - pupdate[1]) / rm1;
		pcompare[0] += (pcompare[2] - pcompare[1]) / rm1;
		pcross[0] += (pcross[2] - pcross[1]) / rm1;
		pmutate[0] += (pmutate[2] - pmutate[1]) / rm1;
		mfrangeHigh[0] += (mfrangeHigh[2] - mfrangeHigh[1]) / rm1;
		mfrangeLow[0] += (mfrangeLow[2] - mfrangeLow[1]) / rm1;
		cfrange[0] += (cfrange[2] - cfrange[1]) / rm1;
		pbuy[0] += (pbuy[2] - pbuy[1]) / rm1;
		psell[0] += (psell[2] - psell[1]) / rm1;
		minTrade[0] += (minTrade[2] - minTrade[1]) / rm1;
		bidAskSpread[0] += (bidAskSpread[2] - bidAskSpread[1]) / rm1;
		interest[0] += (interest[2] - interest[1]) / rm1;
		dividend[0] += (dividend[2] - dividend[1]) / rm1;
		pshock[0] += (pshock[2] - pshock[1]) / rm1;
		alphaDiv[0] += (alphaDiv[2] - alphaDiv[1]) / rm1;
		betaDiv[0] += (betaDiv[2] - betaDiv[1]) / rm1;
		shockRange[0] += (shockRange[2] - shockRange[1]) / rm1;
		startPrice[0] += (startPrice[2] - startPrice[1]) / rm1;
		startShares[0] += (startShares[2] - startShares[1]) / rm1;
		startBonds[0] += (startBonds[2] - startBonds[1]) / rm1;
		geneA[0] += (geneA[2] - geneA[1]) / rm1;
		geneB[0] += (geneB[2] - geneB[1]) / rm1;
		geneC[0] += (geneC[2] - geneC[1]) / rm1;
		geneD[0] += (geneD[2] - geneD[1]) / rm1;
		geneE[0] += (geneE[2] - geneE[1]) / rm1;
		geneF[0] += (geneF[2] - geneF[1]) / rm1;
		geneG[0] += (geneG[2] - geneG[1]) / rm1;
	}
}
