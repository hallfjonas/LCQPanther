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

namespace lcqpOASES {
    
    enum returnValue {
        // Not implemented
        NOT_YET_IMPLEMENTED = -1,                   /**< Not yet implemented (internal use only). */

        // Success
        SUCCESSFUL_RETURN = 0,						/**< Successful return. */
        
        // Algorithmic status
        PROBLEM_NOT_SOLVED = 10,
        MAX_OUTER_ITERATIONS_REACHED = 11,
        MAX_INNER_ITERATIONS_REACHED = 12,

        // Generic Errors
        LCQPOBJECT_NOT_SETUP = 300,                   /**< Constructor has not been called. */
        INDEX_OUT_OF_BOUNDS = 301,                    /**< Index out of bounds. */
        SUBPROBLEM_SOLVER_ERROR = 302,
        UNABLE_TO_READ_FILE = 303,

        // Invalid arguments
        INVALID_ARGUMENT = 100,
        INVALID_PENALTY_UPDATE_VALUE = 101,
        INVALID_COMPLEMENTARITY_TOLERANCE = 102,
        INVALID_INITIAL_PENALTY_VALUE = 103,
        INVALID_MAX_OUTER_ITERATIONS_VALUE = 104,
        INVALID_MAX_INNER_ITERATIONS_VALUE = 105,

        // Stationarity types
        W_STATIONARY_SOLUTION = 200,
        C_STATIONARY_SOLUTION = 201,
        S_STATIONARY_SOLUTION = 202        
    };

    enum printLevel {
        NONE = 0,                                   /**< No Output. */                    
        OUTER_LOOP_ITERATES = 1,                    /**< Print stats for each outer loop iterate. */
        INNER_LOOP_ITERATES = 2,                    /**< Print stats for each inner loop iterate. */
        VERBOSE = 3                                 /**< Print stats for each inner loop (and possibly output of subproblem solver). */
    };

    enum qpSubproblemSolver {
        QPOASES = 0                                 /**< qpOASES. */
    };

    class Options {

        public:
            /** Default constructor. */
            Options( );

            /** Copy constructor (deep copy). */
            Options(	const Options& rhs			/**< Rhs object. */
                        );

            /** Destructor. */
            ~Options( );

            /** Assignment operator. */
            Options& operator=( const Options& rhs );

            void setToDefault( );                   /**< Sets all options to default values. */

            returnValue ensureConsistency( );       /**< Ensures the consistency of given options. */

            double stationarityTolerance;           /**< Tolerance for 1-Norm of stationarity violation. */
            double complementarityTolerance;		/**< Complementarity tolerance. */
            double initialComplementarityPenalty;	/**< Start value for complementarity penalty term. */
            double complementarityPenaltyUpdate;	/**< Factor for updating penaltised complementarity term. */          
            
            bool solveZeroPenaltyFirst;             /**< Flag indicating whether first QP should ignore penalization. */

            int maxOuterIterations;                 /**< Maximum number of outer iterations to be performed. */
            int maxInnerIterations;                 /**< Maximum number of inner iterations to be performed. */

            qpSubproblemSolver qpSubSolver;         /**< Inidicating which qpSolver to use. */
            printLevel printLvl;                    /**< Print level. */

        protected:
            void copy( const Options& rhs );        /**< Copy each property. */
    };


    class Utilities {
        public:
            // C = A*B.
            static void MatrixMultiplication(const double* const A, const double* const B, double* C, int m, int n, int p);

            // C = A'*B + B'*A
            static void MatrixSymmetrizationProduct(const double* const A, const double* const B, double* C, int m, int n);

            // d = A*b + c
            static void AffineLinearTransformation(const double alpha, const double* const A, const double* const b, const double* const c, double* d, int m, int n);

            // C = alpha*A + beta*B
            static void WeightedMatrixAdd(const double alpha, const double* const A, const double beta, const double* const B, double* C, int m, int n);
            
            // c = alpha*a + beta*b
            static void WeightedVectorAdd(const double alpha, const double* const a, const double beta, const double* const b, double* c, int m);

            // returns p' * Q * p
            static double QuadraticFormProduct(const double* const Q, const double* const p, int m);

            // returns a'*b
            static double DotProduct(const double* const a, const double* const b, int m);

            // returns 1-norm
            static double MaxAbs(const double* const a, int m);

            // Read integral data from file
            static returnValue readFromFile(int* data, int n, const char* datafilename);

            // Read float data from file
            static returnValue readFromFile(double* data, int n, const char* datafilename );

            constexpr static const double EPS = 1.11e-16;
    };
}


#endif  // LCQPOASES_UTILITIES_HPP