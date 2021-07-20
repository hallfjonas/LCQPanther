/*
 *	This file is part of LCQPow.
 *
 *	LCQPow -- A Solver for Quadratic Programs with Commplementarity Constraints.
 *	Copyright (C) 2020 - 2021 by Jonas Hall et al.
 *
 *	LCQPow is free software; you can redistribute it and/or
 *	modify it under the terms of the GNU Lesser General Public
 *	License as published by the Free Software Foundation; either
 *	version 2.1 of the License, or (at your option) any later version.
 *
 *	LCQPow is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *	See the GNU Lesser General Public License for more details.
 *
 *	You should have received a copy of the GNU Lesser General Public
 *	License along with LCQPow; if not, write to the Free Software
 *	Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */


#include "OutputStatistics.hpp"
#include <vector>

namespace LCQPow {

    OutputStatistics::OutputStatistics( ) { }


    OutputStatistics& OutputStatistics::operator=( const OutputStatistics& rhs )
    {
        iterTotal = rhs.iterTotal;
        iterOuter = rhs.iterOuter;
        subproblemIter = rhs.subproblemIter;
        rhoOpt = rhs.rhoOpt;
        status = rhs.status;

        innerIters = rhs.innerIters;
        subproblemIters = rhs.subproblemIters;
        accuSubproblemIters = rhs.accuSubproblemIters;
        stepLength = rhs.stepLength;
        stepSize = rhs.stepSize;
        statVals = rhs.statVals;
        objVals = rhs.objVals;
        phiVals = rhs.phiVals;
        meritVals = rhs.meritVals;

        return *this;
    }


    void OutputStatistics::reset( )
    {
        iterTotal = 0;
        iterOuter = 0;
        subproblemIter = 0;
        rhoOpt = 0.0;
        status = PROBLEM_NOT_SOLVED;

        innerIters.clear();
        subproblemIters.clear();
        accuSubproblemIters.clear();
        stepLength.clear();
        stepSize.clear();
        statVals.clear();
        objVals.clear();
        phiVals.clear();
        meritVals.clear();
    }


    ReturnValue OutputStatistics::updateIterTotal( int delta_iter )
    {
        if (delta_iter < 0) return INVALID_TOTAL_ITER_COUNT;

        iterTotal += delta_iter;
        return SUCCESSFUL_RETURN;
    }


    ReturnValue OutputStatistics::updateIterOuter( int delta_iter )
    {
        if (delta_iter < 0) return INVALID_TOTAL_OUTER_ITER;

        iterOuter += delta_iter;
        return SUCCESSFUL_RETURN;
    }


    ReturnValue OutputStatistics::updateSubproblemIter( int delta_iter )
    {
        if (delta_iter < 0) return IVALID_SUBPROBLEM_ITER;

        subproblemIter += delta_iter;
        return SUCCESSFUL_RETURN;
    }


    ReturnValue OutputStatistics::updateRhoOpt( double _rho )
    {
        if (_rho <= 0) return INVALID_RHO_OPT;

        rhoOpt = _rho;
        return SUCCESSFUL_RETURN;
    }


    ReturnValue OutputStatistics::updateSolutionStatus( AlgorithmStatus _status )
    {
        status = _status;
        return SUCCESSFUL_RETURN;
    }


    ReturnValue OutputStatistics::updateTrackingVectors(
                int thisInnerIter,
                int thisSubproblemIter,
                double thisStepLength,
                double thisStepSize,
                double statVal,
                double objVal,
                double phiVal,
                double meritVal
            )
    {
        innerIters.push_back(thisInnerIter);
        subproblemIters.push_back(thisSubproblemIter);
        if (accuSubproblemIters.size() == 0)
            accuSubproblemIters.push_back(thisSubproblemIter);
        else
            accuSubproblemIters.push_back(accuSubproblemIters.back() + thisSubproblemIter);

        stepLength.push_back(thisStepLength);
        stepSize.push_back(thisStepSize);
        statVals.push_back(statVal);
        objVals.push_back(objVal);
        phiVals.push_back(phiVal);
        meritVals.push_back(meritVal);

        return SUCCESSFUL_RETURN;
    }


    int OutputStatistics::getIterTotal( ) const
    {
        return iterTotal;
    }


    int OutputStatistics::getIterOuter( ) const
    {
        return iterOuter;
    }


    int OutputStatistics::getSubproblemIter( ) const
    {
        return subproblemIter;
    }


    double OutputStatistics::getRhoOpt( ) const
    {
        return rhoOpt;
    }


    AlgorithmStatus OutputStatistics::getSolutionStatus( ) const
    {
        return status;
    }


    int* OutputStatistics::getInnerIters( ) const
    {
        if(innerIters.size() == 0)
            return NULL;

        int* vals = new int[innerIters.size()];
        for (size_t i = 0; i < innerIters.size(); i++)
            vals[i] = innerIters[i];

        return vals;
    }


    int* OutputStatistics::getSubproblemIters( ) const
    {
        if(subproblemIters.size() == 0)
            return NULL;

        int* vals = new int[subproblemIters.size()];
        for (size_t i = 0; i < subproblemIters.size(); i++)
            vals[i] = subproblemIters[i];

        return vals;
    }


    int* OutputStatistics::getAccuSubproblemIters( ) const
    {
        if(accuSubproblemIters.size() == 0)
            return NULL;

        int* vals = new int[accuSubproblemIters.size()];
        for (size_t i = 0; i < accuSubproblemIters.size(); i++)
            vals[i] = accuSubproblemIters[i];

        return vals;
    }


    double* OutputStatistics::getStepLength( ) const
    {
        if(stepLength.size() == 0)
            return NULL;

        double* vals = new double[stepLength.size()];
        for (size_t i = 0; i < stepLength.size(); i++)
            vals[i] = stepLength[i];

        return vals;
    }


    double* OutputStatistics::getStepSize( ) const
    {
        if(stepSize.size() == 0)
            return NULL;

        double* vals = new double[stepSize.size()];
        for (size_t i = 0; i < stepSize.size(); i++)
            vals[i] = stepSize[i];

        return vals;
    }


    double* OutputStatistics::getStatVals( ) const
    {
        if(statVals.size() == 0)
            return NULL;

        double* vals = new double[statVals.size()];
        for (size_t i = 0; i < statVals.size(); i++)
            vals[i] = statVals[i];

        return vals;
    }


    double* OutputStatistics::getObjVals( ) const
    {
        if(objVals.size() == 0)
            return NULL;

        double* vals = new double[objVals.size()];
        for (size_t i = 0; i < objVals.size(); i++)
            vals[i] = objVals[i];

        return vals;
    }


    double* OutputStatistics::getPhiVals( ) const
    {
        if(phiVals.size() == 0)
            return NULL;

        double* vals = new double[phiVals.size()];
        for (size_t i = 0; i < phiVals.size(); i++)
            vals[i] = phiVals[i];

        return vals;
    }


    double* OutputStatistics::getMeritVals( ) const
    {
        if(meritVals.size() == 0)
            return NULL;

        double* vals = new double[meritVals.size()];
        for (size_t i = 0; i < meritVals.size(); i++)
            vals[i] = meritVals[i];

        return vals;
    }

}
