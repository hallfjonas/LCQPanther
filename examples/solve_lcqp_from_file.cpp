// Copyright 2020 Jonas Hall

#include <iostream>
#include <fstream>
#include <qpOASES.hpp>
#include <unistd.h>

int main() {
    auto inputdir = "examples/LCQP/example_data/";

    // Required files
    auto H_file = inputdir + "H.txt";
    auto g_file = inputdir + "g.txt";
    auto lb_file = inputdir + "lb.txt";
    auto ub_file = inputdir + "ub.txt";
    auto C_file = inputdir + "C.txt";

    // Contraints (optional files, but if A exists then all are required)
    auto A_file = inputdir + "A.txt";
    auto lbA_file = inputdir + "lbA.txt";
    auto ubA_file = inputdir + "ubA.txt";

    // Initial primal and dual guess (optional)
    auto x0_file = inputdir + "x0.txt";
    auto y0_file = inputdir + "y0.txt";

    int nV = 0;
    int nC = 0;

    auto line;

    std::ifstream lbfile(lb_file);
    while (std::getline(lbfile, line))
        nV++;

    std::ifstream lbAfile(lbA_file);
    while (std::getline(lbAfile, line))
        nC++;

    // Read x0 value
    double* x0 = new double[nV];
    if (access( x0_file.c_str(), F_OK ) != -1 ) {
        readFromFile( x0, nV, &x0_file[0] );
    } else {
        for (int i = 0; i < nV; i++)
            x0[i] = 0;
    }

    // Read y0 value
    double* y0 = new double[nV + nC];
    if (access( y0_file.c_str(), F_OK ) != -1 ) {
        readFromFile( y0, nV + nC, &y0_file[0] );
    } else {
        for (int i = 0; i < nV + nC; i++)
            y0[i] = 0;
    }

    Options options;
    options.setToDefault();
    options.initialComplementarityPenalty = 1.0;
    options.complementarityPenaltyUpdate = 2.0;

    int nWSR = 10000000;
    double* cputime = 0;

    if (nC == 0) {
        LCQProblemB lcqp( nV );
	    lcqp.setOptions( options );
        lcqp.init( &H_file[0], &g_file[0], &lb_file[0], &ub_file[0], &C_file[0], nWSR, cputime, x0, y0 );

        double* xOpt = new double[nV];
        double* yOpt = new double[nV];
        lcqp.getPrimalSolution( xOpt );
        lcqp.getDualSolution( yOpt );
    } else {
        LCQProblem lcqp( nV, nC );
	    lcqp.setOptions( options );
        lcqp.init( &H_file[0], &g_file[0], &A_file[0], &lb_file[0], &ub_file[0], &lbA_file[0], &ubA_file[0], &C_file[0], nWSR, cputime, x0, y0 );

        double* xOpt = new double[nV];
        double* yOpt = new double[nV];
        lcqp.getPrimalSolution( xOpt );
        lcqp.getDualSolution( yOpt );
    }
}
