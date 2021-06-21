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

#ifndef LCQPow_SUBSOLVER_HPP
#define LCQPow_SUBSOLVER_HPP

#include "SubsolverQPOASES.hpp"
#include "SubsolverOSQP.hpp"

namespace LCQPow {

    class Subsolver {
        public:
			/** Default constructor. */
			Subsolver( );

            /** Constructor for dense matrices (qpOASES).
             *
             * @param nV The number of optimization variables.
             * @param nC The number of linear constraints (should include the complementarity pairs).
             * @param H The Hessian matrix in dense format.
             * @param A The linear constraint matrix (should include the rows of the complementarity selector matrices).
            */
            Subsolver(  int nV,
                        int nC,
                        double* H,
                        double* A );

            /** Constructor for sparse matrices (qpOASES/OSQP).
             *
             * @param nV The number of optimization variables.
             * @param nC The number of linear constraints (should include the complementarity pairs).
             * @param H The Hessian matrix in sparse csc format.
             * @param A The linear constraint matrix in sparse csc format (should include the rows of the complementarity selector matrices).
             * @param qpSolver The QP subproblem solver to be used.
            */
            Subsolver(  int nV,
                        int nC,
                        csc* H,
                        csc* A,
                        QPSolver qpSolver);

            /** Copy constructor. */
            Subsolver(const Subsolver& rhs);

            /** Assignment operator (deep copy). */
            virtual Subsolver& operator=(const Subsolver& rhs);

            /** Write solution to x and y. */
            void getSolution( double* x, double* y );

            /** Options of subproblem solver. */
            void setPrintLevel( PrintLevel printLevel );

            /** Abstract method for solving the QP. */
            ReturnValue solve(  bool initialSolve, int& iterations,
                                const double* g,
                                const double* lbA, const double* ubA,
                                const double* x0 = 0, const double* y0 = 0,
                                const double* lb = 0, const double* ub = 0);

        protected:
            /** Copies all members from given rhs object. */
            void copy(const Subsolver& rhs);


        private:
            // The solver type
            QPSolver qpSolver;                      /**< Inidicating which qpSolver to use. */

            // The different solvers
        	SubsolverQPOASES solverQPOASES;         /**< When using qpOASES. */
			SubsolverOSQP solverOSQP;				/**< When using OSQP. */

            // Options and settings
            qpOASES::Options optionsQPOASES;        /**< Options for the qpOASES solver. */
    };
}

#endif  // LCQPow_SUBSOLVER_HPP