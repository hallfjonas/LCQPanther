/*
 *	This file is part of LCQPanther.
 *
 *	LCQPanther -- A Solver for Quadratic Programs with Commplementarity Constraints.
 *	Copyright (C) 2020 - 2021 by Jonas Hall et al.
 *
 *	LCQPanther is free software; you can redistribute it and/or
 *	modify it under the terms of the GNU Lesser General Public
 *	License as published by the Free Software Foundation; either
 *	version 2.1 of the License, or (at your option) any later version.
 *
 *	LCQPanther is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *	See the GNU Lesser General Public License for more details.
 *
 *	You should have received a copy of the GNU Lesser General Public
 *	License along with LCQPanther; if not, write to the Free Software
 *	Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */


#ifndef LCQPanther_LCQPROBLEM_HPP
#define LCQPanther_LCQPROBLEM_HPP

#include "Utilities.hpp"
#include "Subsolver.hpp"

#include <qpOASES.hpp>
#include <vector>

using qpOASES::QProblem;

namespace LCQPanther {
	class LCQProblem
	{
		/*
		*	PUBLIC MEMBER FUNCTIONS
		*/
		public:

			/** Default constructor. */
			LCQProblem( );


			/** Construct LCQP solver with dimensions.
			 *
			 * @param _nV Number of optimization variables.
			 * @param _nC Number of linear constraints.
			 * @param _nComp Number of complementarity pairs.
			 */
			LCQProblem(
				int _nV,
				int _nC,
				int _nComp
			);


			/** Destructor. */
			~LCQProblem( );


			/** Run solver passing the desired LCQP in dense format (qpOASES is used on subsolver level).
			 *
			 * @param _H The objective's hessian matrix.
			 * @param _g The obective's linear term.
			 * @param _S1 The matrix selecting the left hand side of the complementarity pairs.
			 * @param _S2 The matrix selecting the right hand side of the complementarity pairs.
			 * @param _A The constraint matrix. A `NULL` pointer can be passed if no linear constraints exist.
			 * @param _lbA The lower bounds associated to the constraint matrix `_A`. A `NULL` pointer can be passed if no lower bounds exist.
			 * @param _ubA The upper bounds associated to the constraint matrix `_A`. A `NULL` pointer can be passed if no upper bounds exist.
			 * @param _lb The box constraint's lower bounds. A `NULL` pointer can be passed if no lower bounds exist.
			 * @param _ub The box constraint's upper bounds. A `NULL` pointer can be passed if no upper bounds exist.
			 * @param _x0 The initial guess for the optimal primal solution vector. If a `NULL` pointer is passed the zero vector is used.
			 * @param _y0 The initial guess for the optimal dual solution vector. If a `NULL` pointer is passed, then the initialization depends on the subsolver and its options.
			 *
			 * @returns SUCCESSFUL_RETURN if a solution is found. Otherwise the return value will indicate an occured error.
			*/
			ReturnValue loadLCQP(
				const double* const _H,
				const double* const _g,
				const double* const _S1,
				const double* const _S2,
				const double* const _A = 0,
				const double* const _lbA = 0,
				const double* const _ubA = 0,
				const double* const _lb = 0,
				const double* const _ub = 0,
				const double* const _x0 = 0,
				const double* const _y0 = 0
			 );


			/** Run solver passing the desired LCQP in (file) dense format (qpOASES is used on subsolver level).
			 *  All matrices are assumed to be stored row-wise.
			 *
			 * @param H_file The objective's hessian matrix.
			 * @param g_file The obective's linear term.
			 * @param S1_file The matrix selecting the left hand side of the complementarity pairs.
			 * @param S2_file The matrix selecting the right hand side of the complementarity pairs.
			 * @param A_file The constraint matrix. A `NULL` pointer can be passed if no linear constraints exist.
			 * @param lbA_file The lower bounds associated to the constraint matrix `_A`. A `NULL` pointer can be passed if no lower bounds exist.
			 * @param ubA_file The upper bounds associated to the constraint matrix `_A`. A `NULL` pointer can be passed if no upper bounds exist.
			 * @param lb_file The box constraint's lower bounds. A `NULL` pointer can be passed if no lower bounds exist.
			 * @param ub_file The box constraint's upper bounds. A `NULL` pointer can be passed if no upper bounds exist.
			 * @param x0_file The initial guess for the optimal primal solution vector. If a `NULL` pointer is passed the zero vector is used.
			 * @param y0_file The initial guess for the optimal dual solution vector. If a `NULL` pointer is passed, then the initialization depends on the subsolver and its options.
			 *
			 * @returns SUCCESSFUL_RETURN if a solution is found. Otherwise the return value will indicate an occured error.
			*/
			ReturnValue loadLCQP(
				const char* const H_file,
				const char* const g_file,
				const char* const S1_file,
				const char* const S2_file,
				const char* const A_file = 0,
				const char* const lbA_file = 0,
				const char* const ubA_file = 0,
				const char* const lb_file = 0,
				const char* const ub_file = 0,
				const char* const x0_file = 0,
				const char* const y0_file = 0
			);


			/** Run solver passing the desired LCQP in sparse format (OSQP is used on subsolver level).
			 *
			 * @param _H_data Non-zero Hessian matrix values.
			 * @param _H_i Row indicies of non-zero values.
			 * @param _H_p Pointer to column starts.
			 * @param _g The objective's linear term.
			 * @param _S1_data Non-zero values of LHS of complementarity product.
			 * @param _S1_i Row indicies of non-zero values of S1.
			 * @param _S1_p Pointer to column starts of S1.
			 * @param _S2_data Non-zero values of RHS of complementarity product.
			 * @param _S1_i Row indicies of non-zero values of S2.
			 * @param _S1_p Pointer to column starts of S2.
			 * @param _A_data Non-zero values of constraint matrix.
			 * @param _A_i Row indicies of non-zero values of A.
			 * @param _A_p Pointer to column starts of A.
			 * @param _lbA The constraints lower bounds. A `NULL` pointer can be passed if no lower bounds exist.
			 * @param _ubA The constraints upper bounds. A `NULL` pointer can be passed if no upper bounds exist.
			 * @param _lb The box constraints lower bounds. A `NULL` pointer can be passed if no lower bounds exist.
			 * @param _ub The box constraints upper bounds. A `NULL` pointer can be passed if no upper bounds exist.
			 * @param _x0 The initial guess for the optimal primal solution vector. If a `NULL` pointer is passed the zero vector is used.
			 * @param _y0 The initial guess for the optimal dual solution vector. If a `NULL` pointer is passed, then the initialization depends on the subsolver and its options.
			 *
			 * @returns SUCCESSFUL_RETURN if a solution is found. Otherwise the return value will indicate an occured error.
			*/
			ReturnValue loadLCQP(
				double* _H_data,
				int* _H_i,
				int* _H_p,
				double* _g,
				double* _S1_data,
				int* _S1_i,
				int* _S1_p,
				double* _S2_data,
				int* _S2_i,
				int* _S2_p,
				double* _A_data = 0,
				int* _A_i = 0,
				int* _A_p = 0,
				double* _lbA = 0,
				double* _ubA = 0,
				double* _lb = 0,
				double* _ub = 0,
				double* _x0 = 0,
				double* _y0 = 0
			);


			/** Run solver passing the desired LCQP in (file) sparse format (OSQP is used on subsolver level).
			 *
			 * @param _H_data_file Non-zero Hessian matrix values.
			 * @param _H_nnx_file Number of non-zero values of Hessian.
			 * @param _H_i_file Row indicies of non-zero values.
			 * @param _H_p_file Pointer to column starts.
			 * @param _g_file The objective's linear term.
			 * @param _lb_file The box constraint's lower bounds. A `NULL` pointer can be passed if no lower bounds exist.
			 * @param _ub_file The box constraint's upper bounds. A `NULL` pointer can be passed if no upper bounds exist.
			 * @param _S1_data_file Non-zero values of LHS of complementarity product.
			 * @param _S1_i_file Row indicies of non-zero values of S1.
			 * @param _S1_p_file Pointer to column starts of S1.
			 * @param _S2_data_file Non-zero values of RHS of complementarity product.
			 * @param _S1_i_file Row indicies of non-zero values of S2.
			 * @param _S1_p_file Pointer to column starts of S2.
			 * @param _A_data_file Non-zero values of constraint matrix.
			 * @param _A_i_file Row indicies of non-zero values of A.
			 * @param _A_p_file Pointer to column starts of A.
			 * @param _lbA_file The constraint's lower bounds. A `NULL` pointer can be passed if no lower bounds exist.
			 * @param _ubA_file The constraint's upper bounds. A `NULL` pointer can be passed if no upper bounds exist.
			 * @param _x0_file The initial guess for the optimal primal solution vector. If a `NULL` pointer is passed the zero vector is used.
			 * @param _y0 _fileThe initial guess for the optimal dual solution vector. If a `NULL` pointer is passed, then the initialization depends on the subsolver and its options.
			 *
			 * @returns SUCCESSFUL_RETURN if a solution is found. Otherwise the return value will indicate an occured error.
			*/
			ReturnValue loadLCQP(
				const char* const H_data_file,
				const char* const H_i_file,
				const char* const H_p_file,
				const char* const g_file,
				const char* const lb_file,
				const char* const ub_file,
				const char* const S1_data_file,
				const char* const S1_i_file,
				const char* const S1_p_file,
				const char* const S2_data_file,
				const char* const S2_i_file,
				const char* const S2_p_file,
				const char* const A_data_file = 0,
				const char* const A_i_file = 0,
				const char* const A_p_file = 0,
				const char* const lbA_file = 0,
				const char* const ubA_file = 0,
				const char* const x0_file = 0,
				const char* const y0_file = 0
			);

			/** After problem is set up, call this function and solve LCQP. */
			ReturnValue runSolver( );

			/** Writes the primal solution vector.
			 *
			 * @param xOpt A pointer to the desired primal solution storage vector.
			 *
			 * @returns If the problem was solved successfully the stationarity type is passed. Else PROBLEM_NOT_SOLVED is returned.
			 */
			virtual AlgorithmStatus getPrimalSolution( double* const xOpt ) const;


			/** Writes the dual solution vector.
			 *
			 * @param yOpt A pointer to the desired dual solution storage vector.
			 *
			 * @returns If the problem was solved successfully the stationarity type is passed. Else PROBLEM_NOT_SOLVED is returned.
			 */
			virtual AlgorithmStatus getDualSolution( double* const yOpt ) const;


			/** Get the number of dual variables. This depends on the utilized subproblem solver.
			 *
			 * @return Returns the number of dual variables.
			 */
			virtual int getNumerOfDuals( ) const;


			/** Get the output statistics.
			 *
			 * @param _stats The output statistics pointer to copy the stats to.
			 */
			virtual void getOutputStatistics( OutputStatistics& stats) const;


			/** Pass options for the LCQP.
			 *
			 * @param _options Options to be used.
			 */
			inline void setOptions(	const Options& _options	);


		/*
		*	PROTECTED MEMBER FUNCTIONS
		*/
		protected:
			/** Clears all memory. */
			void clear( );


			/** Copies all properties from rhs to this.
			 *
			 * @param rhs The LCQProblem to be copied.
			 */
			ReturnValue copy( const LCQProblem& rhs );


			/** Prints concise information on the current iteration. */
			void printIteration( );


			/** Print header every once in a while. */
			void printHeader();


			/** Print line (mainly for printing header). */
			void printLine();


			/** Store the (dense) Hessian matrix H internally.
			 *
			 * @param H_new New dense Hessian matrix (with correct dimension!), a shallow copy is made.
			 */
			inline ReturnValue setH( const double* const H_new );


			/** Store the (sparse) Hessian matrix H internally.
			 *
			 * @param _H_data Non-zero Hessian matrix values.
			 * @param _H_i Row indicies of non-zero values.
			 * @param _H_p Pointer to column starts.
			 */
			inline ReturnValue setH(
				double* H_data,
				int* H_i,
				int* H_p
			);



			inline ReturnValue setG( const double* const g_new );

			/** Store the lower (box) bounds internally.
			 *
			 * @param lb_new New lower bound vector (with correct dimension!).
			 */
			inline ReturnValue setLB( const double* const lb_new );


			/** Store a specific lower (box) bound internally.
			 *
			 * @param number Number of entry to be changed.
			 * @param value New value for entry of lower bound vector.
			 */
			inline ReturnValue setLB(
				int number,
				double value
			);


			/** Store the upper (box) bounds internally.
			 *
			 * @param ub_new New upper bound vector (with correct dimension!).
			 */
			inline ReturnValue setUB( const double* const ub_new );


			/** Store a specific upper (box) bound internally.
			 *
			 * @param number Number of entry to be changed.
			 * @param value New value for entry of lower bound vector.
			 */
			inline ReturnValue setUB(
				int number,
				double value
			);


			/** Set the new linear constraint consisting of (dense) complementarity pairs and regular linear constraints.
			 *
			 * @param S1_new New lhs complementarity matrix.
			 * @param S2_new New rhs complementarity matrix.
			 * @param A_new New constraint matrix.
			 * @param lbA New lower bounds for A.
			 * @param ubA New upper bounds for A.
			 */
			ReturnValue setConstraints(
				const double* const S1_new,
				const double* const S2_new,
				const double* const A_new,
				const double* const lbA,
				const double* const ubA
			);


			/** Set the new linear constraint consisting of (dense) complementarity pairs and regular linear constraints.
			 *
			 * @param S1_data Non-zero values of LHS of complementarity product.
			 * @param S1_i Row indicies of non-zero values of S1.
			 * @param S1_p Pointer to column starts of S1.
			 * @param S2_data Non-zero values of RHS of complementarity product.
			 * @param S1_i Row indicies of non-zero values of S2.
			 * @param S1_p Pointer to column starts of S2.
			 * @param A_data Non-zero values of constraint matrix.
			 * @param A_i Row indicies of non-zero values of A.
			 * @param A_p Pointer to column starts of A.
			 * @param lbA The constraint's lower bounds. A `NULL` pointer can be passed if no lower bounds exist.
			 * @param ubA The constraint's upper bounds. A `NULL` pointer can be passed if no upper bounds exist.
			 */
			ReturnValue setConstraints(
				double* S1_data,
				int* S1_i,
				int* S1_p,
				double* S2_data,
				int* S2_i,
				int* S2_p,
				double* A_data,
				int* A_i,
				int* A_p,
				double* lbA,
				double* ubA
			);


			/** Set the complementarity matrix (requires the constraints to be set) as the symmetrization product of S1 and S2.
			 *  C = S1'*S2 + S2'*S1
			 */
			ReturnValue setC( );

			/** Sets the initial guess x0 and y0.
			 *
			 * @param _x0 The primal initial guess.
			 * @param _y0 The dual initial guess.
			 */
			inline ReturnValue setInitialGuess(
				const double* const _x0,
				const double* const _y0
			);


			/** TODO: Write description. */
			inline ReturnValue setSparseMatrix(
				const double* const _M_data,
				const int _M_nnx,
				const int* const _M_i,
				const int* const _M_p,
				qpOASES::SparseMatrix Mat
			);

			/** TODO: Write description. */
			inline ReturnValue setSparseMatrix(
				const double* const _M_data,
				const int _M_nnx,
				const int* const _M_i,
				const int* const _M_p,
				qpOASES::SymSparseMat Mat
			);


			/** Set Qk. */
			void setQk( );


			/** Returns the NLP stationarity vector.
			 *
			 * @param x_eval The point at which the stationarity should be evaluated (TODO: why no y_eval?).
			 * @param penVal The current penalty value.
			 * @param g_original The original objective linear term.
			 *
			 * @returns The stationarity vector.
			 */
			double* getPenaltyStationarity(
				const double* const x_eval,
				const double penVal,
				const double* const g_original
			);


		/*
		*	PROTECTED MEMBER VARIABLES
		*/
		protected:
			Options options;						/**< Class for algorithmic options. */

		private:

			/** Called in runSolver to initialize variables. */
			ReturnValue initializeSolver( );

			/** Switch to sparse mode (if initialized with dense data but want to use sparse solver). */
			ReturnValue switchToSparseMode( );

			/** Switch to dense mode (if initialized with sparse data but want to use dense solver). */
			ReturnValue switchToDenseMode( );

			/** Update the penalty linearization. */
			void updateLinearization( );

			/** Solves the qp subproblem wrt H, gk, A, S1, S2 .
			 *
			 * @param initialSolve Pass true on first solve of sequence, false on subsequent calls (initialization vs hotstart).
			 */
			ReturnValue solveQPSubproblem( bool initialSolve );

			/** Check outer stationarity at current iterate xk. */
			bool stationarityCheck( );

			/** Check satisfaction of complementarity value. */
			bool complementarityCheck( );

			/** Perform penalty update. */
			void updatePenalty( );

			/** Get optimal step length. */
			void getOptimalStepLength( );

			/** Update xk and gk. */
			void updateStep( );

			/** Update Qk. */
			void updateQk( );

			/** Update outer iteration counter. */
			void updateOuterIter( );

			/** Update outer iteration counter. */
			void updateTotalIter( );

			/** Gradient perturbation method. */
			void perturbGradient( );

			/** Step perturbation method. */
			void perturbStep( );

			/** Transform the dual variables from penalty form to LCQP form. */
			void transformDuals( );

			/** Determine stationarity type of optimal solution. */
			void determineStationarityType( );

			/** Get indices of weak complementarites. */
			std::vector<int> getWeakComplementarities( );

			int nV;									/**< Number of variables. */
			int nC;									/**< Number of constraints. */
			int nComp;								/**< Number of complementarity constraints. */
			int nDuals; 							/**< Number of duals variables. */
			int boxDualOffset;						/**< Offset for linear constraint duals (i.e. 0 if no BC (Box Constraints) exist nV if BC exist). */

			double* H = NULL;						/**< Objective Hessian term. */

			double* g = NULL;						/**< Objective linear term. */

			double* lb = NULL;						/**< Lower bound vector (on variables). */
			double* ub = NULL;						/**< Upper bound vector (on variables). */
			double* lb_tmp = NULL;						/**< Temporary box constraints. */
			double* ub_tmp = NULL;						/**< Temporary box constraints. */

			double* A = NULL;						/**< Constraint matrix. */
			double* lbA = NULL;						/**< Lower bound vector (on constraints). */
			double* ubA = NULL;						/**< Upper bound vector (on constraints). */

			double* S1 = NULL;						/**< LHS of complementarity product. */
			double* S2 = NULL;						/**< RHS of complementarity product. */
			double* C = NULL;						/**< Complementarity matrix (S1'*S2 + S2'*S1). */

			double rho; 							/**< Current penalty value. */

			double* gk;								/**< Current objective linear term. */

			double* xk = NULL;						/**< Current primal iterate. */
			double* yk = NULL;						/**< Current dual vector. */
			double* yk_A = NULL;					/**< Current dual vector w.r.t A. */
			double* xnew = NULL;					/**< Current qpSubproblem solution. */
			double* pk = NULL;						/**< xnew - xk. */

			double alphak; 							/**< Optimal step length. */
			double* lk_tmp = NULL;					/**< An auxiliar vector to help compute lkj. */

			double* Qk = NULL;						/**< H + rho*C, required for stationarity and optimal step length. */
			double* statk = NULL;					/**< Stationarity of current iterate. */
			double* constr_statk = NULL;			/**< Constraint contribution to stationarity equation. */
			double* box_statk = NULL;				/**< Box Constraint contribution to stationarity equation. */

			int outerIter;							/**< Outer iterate counter. */
			int innerIter;							/**< Inner iterate counter. */
			int totalIter;							/**< Total iterate counter. */

			int qpIterk;							/**< Iterations taken by qpSolver to solve subproblem. */

			AlgorithmStatus algoStat;				/**< Status of algorithm. */

			bool sparseSolver = false;				/**< Whether to use sparse algebra or dense. */

			csc* H_sparse = NULL;					/**< Sparse objective Hessian matrix. */
			csc* A_sparse = NULL;					/**< Sparse constraint matrix. */
			csc* S1_sparse = NULL;					/**< Sparse S1. */
			csc* S2_sparse = NULL;					/**< Sparse S2. */
			csc* C_sparse = NULL;					/**< Sparse C. */
			csc* Qk_sparse = NULL;					/**< Sparse Qk. */
			std::vector<int> Qk_indices_of_C;		/**< Remember the indices of Qk corresponding to C (for fast Qk update). */

			Subsolver subsolver;					/**< Subsolver class for solving the QP subproblems. */

			OutputStatistics stats;					/**< Output statistics. */
	};
}


#include "LCQProblem.ipp"

#endif	/* LCQPanther_LCQPROBLEM_HPP */


/*
 *	end of file
 */
