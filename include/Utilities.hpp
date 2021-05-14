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


#ifndef LCQPOASES_UTILITIES_HPP
#define LCQPOASES_UTILITIES_HPP

#include <osqp.h>

namespace lcqpOASES {

    enum ReturnValue {
        // Special values
        NOT_YET_IMPLEMENTED = -1,                       /**< Not yet implemented (internal use only). */
        SUCCESSFUL_RETURN = 0,						    /**< Successful return. */

        // Invalid arguments
        INVALID_ARGUMENT = 100,                         /**< Generic invalid argument. */
        INVALID_PENALTY_UPDATE_VALUE = 101,             /**< Invalid penalty update value. Must be > 1. */
        INVALID_COMPLEMENTARITY_TOLERANCE = 102,        /**< Invalid complementarity tolerance. Must be no smaller than machine precision. */
        INVALID_INITIAL_PENALTY_VALUE = 103,            /**< Invalid initial penalty parameter. Must be positive. */
        INVALID_MAX_ITERATIONS_VALUE = 104,             /**< Invalid number of maximal outer iterations. Must be a positive integer. */
        INVALID_STATIONARITY_TOLERANCE = 105,           /**< Invalid stationarity tolerance. Must be no smaller than machine precision. */
        INVALID_NUMBER_OF_OPTIM_VARS = 106,             /**< Invalid number of optimization variables. Must be a positive integer. */
        INVALID_NUMBER_OF_COMP_VARS = 107,              /**< Invalid number of complementarity constraints. Must be a positive integer. */
        INVALID_NUMBER_OF_CONSTRAINT_VARS = 108,        /**< Invalid number of linear constraints. Must be a non-negative integer. */
        INVALID_RELAX_OPTIONS_TOLERANCE = 109,          /**< Invalid number of active set changes to switch to precision mode. Must be a positive integer. */
        INVALID_OSQP_BOX_CONSTRAINTS = 110,             /**< Invalid constraints passed to OSQP solver: This solver does not handle box constraints, please pass them through linear constraints. */
        INVALID_TOTAL_ITER_COUNT = 111,                 /**< Invalid total number of iterations delta passed to output statistics (must be non-negative integer). */
        INVALID_TOTAL_OUTER_ITER = 112,                 /**< Invalid total number of outer iterations delta passed to output statistics (must be non-negative integer). */
        IVALID_SUBPROBLEM_ITER = 113,                   /**< Invalid total number of subproblem solver iterates delta passed to output statistics (must be non-negative integer). */
        INVALID_RHO_OPT = 114,                          /**< Invalid rho value at solution passed to output statistics. (must be positive double). */
        INVALID_PRINT_LEVEL_VALUE = 115,                /**< Invalid integer to be parsed to print level passed (must be in range of enum). */

        // Algorithmic errors
        MAX_ITERATIONS_REACHED = 200,                   /**< Maximum number of iterations reached. */
        INITIAL_SUBPROBLEM_FAILED = 202,                /**< Failed to solve the initial QP. */
        SUBPROBLEM_SOLVER_ERROR = 203,                  /**< An error occured in the subproblem solver. */

        // Generic errors
        LCQPOBJECT_NOT_SETUP = 300,                     /**< Constructor has not been called. */
        INDEX_OUT_OF_BOUNDS = 301,                      /**< Index out of bounds. */
        UNABLE_TO_READ_FILE = 302,                      /**< Unable to read a file. */

        // Sparse matrices
        INVALID_INDEX_POINTER = 400,                    /**< Invalid index pointer for a csc matrix. */
        INVALID_INDEX_ARRAY = 401                       /**< Invalid index array for a csc matrix. */
    };

    enum AlgorithmStatus {
        PROBLEM_NOT_SOLVED = 0,                         /**< The problem was not solved. */
        W_STATIONARY_SOLUTION = 1,                      /**< The solution corresponds to a weakly stationary point. */
        C_STATIONARY_SOLUTION = 2,                      /**< The solution corresponds to a Clarke stationary point. */
        M_STATIONARY_SOLUTION = 3,                      /**< The solution corresponds to a Mordukhovich stationary point. */
        S_STATIONARY_SOLUTION = 4                       /**< The solution corresponds to a strongly stationary point. */
    };

    enum PrintLevel {
        NONE = 0,                                       /**< No Output. */
        OUTER_LOOP_ITERATES = 1,                        /**< Print stats for each outer loop iterate. */
        INNER_LOOP_ITERATES = 2,                        /**< Print stats for each inner loop iterate. */
        SUBPROBLEM_SOLVER_ITERATES = 3                  /**< Print stats for each inner loop (and possibly output of subproblem solver). */
    };


    class Options {

        public:

            /** Default constructor. */
            Options( );


            /** Copy constructor (deep copy).
             *
             * @param rhs The object to be copied.
            */
            Options( const Options& rhs );


            /** Destructor. */
            ~Options( );


            /** Assignment operator.
             *
             * @param rhs The obejct from which to assign.
            */
            Options& operator=( const Options& rhs );


            /** Sets all options to default values. */
            void setToDefault( );

            /** Get stationarity tolerance. */
            double getStationarityTolerance( );

            /** Set stationarity tolerance. */
            void setStationarityTolerance( double val );

            /** Get complementarity tolerance. */
            double getComplementarityTolerance( );

            /** Set complementarity tolerance. */
            void setComplementarityTolerance( double val );

            /** Get initial penalty parameter. */
            double getInitialPenaltyParameter( );

            /** Set complementarity tolerance. */
            void setInitialPenaltyParameter( double val );

            /** Get penalty parameter update factor. */
            double getPenaltyUpdateFactor( );

            /** Set penalty parameter update factor. */
            void setPenaltyUpdateFactor( double val );

            /** Get whether to solve for (complement.) unconstrained global minumum first. */
            bool getSolveZeroPenaltyFirst( );

            /** Set whether to solve for (complement.) unconstrained global minumum first. */
            void setSolveZeroPenaltyFirst( bool val );

            /** Get maximum number of iterations. */
            int getMaxIterations( );

            /** Set maximum number of iterations. */
            void setMaxIterations( int val );

            /** Get print level. */
            PrintLevel getPrintLevel( );

            /** Set print level. */
            void setPrintLevel( PrintLevel val );

            /** Set print level (using an integer). */
            void setPrintLevel( int val );

        protected:
            void copy( const Options& rhs );            /**< Copy each property. */

            double stationarityTolerance;               /**< Tolerance for 1-Norm of stationarity violation. */
            double complementarityTolerance;		    /**< Complementarity tolerance. */
            double initialPenaltyParameter;	    /**< Start value for complementarity penalty term. */
            double penaltyUpdateFactor;	    /**< Factor for updating penaltised complementarity term. */

            bool solveZeroPenaltyFirst;                 /**< Flag indicating whether first QP should ignore penalization. */

            int maxIterations;                           /**< Maximum number of iterations to be performed. */

            PrintLevel printLevel;                        /**< Print level. */
    };

    class Utilities {
        public:
            // C = A*B.
            static void MatrixMultiplication(const double* const A, const double* const B, double* C, int m, int n, int p);

            // C = A'*B
            static void TransponsedMatrixMultiplication(const double* const A, const double* const B, double* C, int m, int n, int p);

            // c = A'*b
            static void TransponsedMatrixMultiplication(const csc* const A, const double* const b, double* c, int m, int n);

            // C = A'*B + B'*A
            static void MatrixSymmetrizationProduct(const double* const A, const double* const B, double* C, int m, int n);

            // d = A*b + c
            static void AffineLinearTransformation(const double alpha, const double* const A, const double* const b, const double* const c, double* d, int m, int n);

            // d = A*b + c
            static void AffineLinearTransformation(const double alpha, const csc* const S, const double* const b, const double* const c, double* d, int m);

            // C = alpha*A + beta*B
            static void WeightedMatrixAdd(const double alpha, const double* const A, const double beta, const double* const B, double* C, int m, int n);

            // c = alpha*a + beta*b
            static void WeightedVectorAdd(const double alpha, const double* const a, const double beta, const double* const b, double* c, int m);

            // returns p' * Q * p
            static double QuadraticFormProduct(const double* const Q, const double* const p, int m);

            // returns p' * Q * p
            static double QuadraticFormProduct(const csc* const S, const double* const p, int m);

            // returns a'*b
            static double DotProduct(const double* const a, const double* const b, int m);

            // returns 1-norm
            static double MaxAbs(const double* const a, int m);

            // Clear sparse matrix
            static void ClearSparseMat(csc* M);

            // Read integral data from file
            static ReturnValue readFromFile(int* data, int n, const char* datafilename);

            // Read float data from file
            static ReturnValue readFromFile(double* data, int n, const char* datafilename );

            // Read float data from file
            static ReturnValue writeToFile(double* data, int n, const char* datafilename );

            // Print a double valued matrix
            static void printMatrix(const double* const A, int m, int n, const char* const name);

            // Print an integer valued matrix
            static void printMatrix(const int* const A, int m, int n, const char* const name);

            // Print dense representation of csc matrix
            static void printMatrix(const csc* A, const char* const name);

            // Printing bounds
            static void printStep(double* xk, double* pk, double* xk_new, double alpha, int nV);

            // Printing bounds
            static void printBounds(double* lb, double* xk, double* ub, int m);

            /** Transform a csc matrix to dense.
             *
             * @param sparse A sparse matrix.
             * @param full A target pointer for the full matrix (expected to have size m*n).
             * @param m Number of rows of `H_sparse` (in its dense representation).
             * @param n Number of columns of `H_sparse` (in its dense representation).
             *
             * @returns returnValue::SUCCESSFUL_RETURN, or returnValue::INDEX_OUT_OF_BOUNDSA if an index leads to invalid memory access of the dense array.
             */
            static ReturnValue csc_to_dns(const csc* const sparse, double* full, int m, int n);


            /** Transform a dense matrix to csc.
             *
             * @param full A dense double array.
             * @param m Number of rows of `full`.
             * @param n Number of columns of `full`.
             *
             * @returns A csc pointer to the sparse matrix.
             */
            static csc* dns_to_csc(const double* const full, int m, int n);


            // Methods below this line where taken from qpOASES implementation
            /** Returns the absolute value of x. */
            static double getAbs(double x);

            /** Checks if the absolute difference between x and y is less than TOL. */
            static bool isEqual(double x, double y, double TOL);

            /** Checks if the absolute difference between x and y is less than the constant Utilities::ZERO. */
            static bool isEqual(double x, double y);

            /** Checks if the absolute value of x is less than TOL. */
            static bool isZero(double x, double TOL);

            /** Checks if the absolute value of x is less than the constant Utilities::ZERO. */
            static bool isZero(double x);

            /** Returns the sign of a double x. */
            static double getSign(double x);

            /** Returns the maximum of two integer values x and y. */
            static int getMax(int x, int y);

            /** Returns the minimum of two integer values x and y. */
            static int getMin(int x, int y);

            /** Returns the maximum of two real values x and y. */
            static double getMax(double x, double y);

            /** Returns the minimum of two real values x and y. */
            static double getMin(double x, double y);

            /** Numerical value of machine precision (min eps, s.t. 1+eps > 1).
             *	Note: this value has to be positive! */
            #ifdef __USE_SINGLE_PRECISION__
            const double EPS = 1.193e-07f;
            #else
            constexpr static double EPS = 2.221e-16;
            #endif /* __USE_SINGLE_PRECISION__ */

            /** Numerical value of zero (for situations in which it would be
             *	unreasonable to compare with 0.0).
            *	Note: this value has to be positive! */
            constexpr static double ZERO = 1.0e-25;

            /** Numerical value of infinity (e.g. for non-existing bounds).
                Note: this value has to be positive! */
            constexpr static double INFTY = 1.0e20;

            /** Maximum number of characters within a string.
             *	Note: this value should be at least 41! */
            constexpr static uint MAX_STRING_LENGTH = 160;
    };

    class OutputStatistics {
        public:
            /** Default constructor. */
            OutputStatistics( );

            OutputStatistics& operator=( const OutputStatistics& rhs );

            void reset( );

            /** Update total iteration counter.
             *
             * @return Success or specifies the invalid argument.
            */
            ReturnValue updateIterTotal( int delta_iter );

            /** Update total outer iteration counter.
             *
             * @return Success or specifies the invalid argument.
            */
            ReturnValue updateIterOuter( int delta_iter );

            /** Update total number of working set changes counter.
             *
             * @return Success or specifies the invalid argument.
            */
            ReturnValue updateSubproblemIter( int delta_iter );

            /** Update rho at solution.
             *
             * @return Success or specifies the invalid argument.
            */
            ReturnValue updateRhoOpt( double _rho );

            /** Update the solution status.
             *
             * @return Success or specifies the invalid argument.
            */
            ReturnValue updateSolutionStatus( AlgorithmStatus _status );

            /** Get the total number of iterations. */
            int getIterTotal( ) const;

            /** Get the total number of outer iterations. */
            int getIterOuter( ) const;

            /** Get the total number of subproblem iterations. */
            int getSubproblemIter( ) const;

            /** Get the penalty parameter at the optimal solution (if found). */
            double getRhoOpt( ) const;

            /** Get the solution status (if solved it will return the stationarity type). */
            AlgorithmStatus getSolutionStatus( ) const;

        private:
            int iter_total = 0;
            int iter_outer = 0;
            int subproblem_iter = 0;
            double rho_opt = 0.0;
            AlgorithmStatus status = PROBLEM_NOT_SOLVED;
    };

    class MessageHandler {
        public:
            static ReturnValue PrintMessage( ReturnValue ret );

            static AlgorithmStatus PrintSolution( AlgorithmStatus algoStat );

            static void PrintSolutionLine( );
    };
}

#endif  // LCQPOASES_UTILITIES_HPP