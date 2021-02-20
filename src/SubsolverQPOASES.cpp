/*
 *	This file is part of lcqpOASES.
 *
 *	lcqpOASES -- A Solver for Quadratic Programs with Commplementarity Constraints.
 *	Copyright (C) 2020 - 2021 by Jonas Hall et al.
 *
 *	lcqpOASES is free software; you can redistribute it and/or
 *	modify it under the terms of the GNU Lesser General Public
 *	License as published by the Free Software Foundation; either
 *	version 2.1 of the License, or (at your option) any later version.
 *
 *	lcqpOASES is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *	See the GNU Lesser General Public License for more details.
 *
 *	You should have received a copy of the GNU Lesser General Public
 *	License along with lcqpOASES; if not, write to the Free Software
 *	Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <SubsolverQPOASES.hpp>
#include <qpOASES.hpp>

namespace lcqpOASES {

    /*
     *   S u b s o l v e r O S Q P
     */
    SubsolverQPOASES::SubsolverQPOASES( ) { }


    /*
     *   S u b s o l v e r Q P O A S E S
     */
    SubsolverQPOASES::SubsolverQPOASES( int _nV, int _nC,
                                        double* _H, double* _A)
    {
        if (_nV <= 0  || _nC <= 0)
            throw( MessageHandler::PrintMessage( returnValue::INVALID_ARGUMENT) );

        nV = _nV;
        nC = _nC;

        qp = qpOASES::QProblem(nV, nC);

        H = new double[nV*nV];
        A = new double[nC*nV];

        memcpy(H, _H, (long unsigned int)(nV*nV)*sizeof(double));
        memcpy(A, _A, (long unsigned int)(nC*nV)*sizeof(double));
    }

    /*
     *   S u b s o l v e r O  S Q P
     */
    SubsolverQPOASES::SubsolverQPOASES(const SubsolverQPOASES& rhs)
    {
        copy( rhs );
    }

    /*
     *   ~ S u b s o l v e r Q P O A S E S
     */
    SubsolverQPOASES::~SubsolverQPOASES()
    {
        if (H != 0)
            delete[] H;

        if (A != 0)
            delete[] A;
    }

    /*
     *   o p e r a t o r =
     */
    SubsolverQPOASES& SubsolverQPOASES::operator=(const SubsolverQPOASES& rhs)
    {
        if (this != &rhs) {
            copy( rhs );
        }

        return *this;
    }


    /*
     *   s e t O p t i o n s
     */
    void SubsolverQPOASES::setOptions( qpOASES::Options options )
    {
        qp.setOptions( options );
    }


    /*
     *   s o l v e
     */
    returnValue SubsolverQPOASES::solve(    bool initialSolve, int& iterations,
                                            const double* const g,
                                            const double* const lb, const double* const ub,
                                            const double* const lbA, const double* const ubA,
                                            const double* const x0, const double* const y0 )
    {
        qpOASES::returnValue ret;

        qpOASES::int_t nwsr = 1000000;

        if (initialSolve) {
            ret = qp.init(H, g, A, lb, ub, lbA, ubA, nwsr, (double*)0, x0, y0);
        } else {
            ret = qp.hotstart(g, lb, ub, lbA, ubA, nwsr);
        }

        iterations = (int)(nwsr);

        if (ret != qpOASES::returnValue::SUCCESSFUL_RETURN)
            return returnValue::SUBPROBLEM_SOLVER_ERROR;

        return returnValue::SUCCESSFUL_RETURN;
    }


    /*
     *   g e t P r i m a l S o l u t i o n
     */
    void SubsolverQPOASES::getPrimalSolution( double* x )
    {
        qp.getPrimalSolution( x );
    }


    /*
     *   g e t D u a l S o l u t i o n
     */
    void SubsolverQPOASES::getDualSolution( double* y )
    {
        qp.getDualSolution( y );
    }


    /*
     *   c o p y
     */
    void SubsolverQPOASES::copy(const SubsolverQPOASES& rhs)
    {
        nV = rhs.nV;
        nC = rhs.nC;

        H = new double[nV*nV];
        A = new double[nC*nV];
        H = rhs.H;
        A = rhs.A;

        qp = rhs.qp;
    }
}