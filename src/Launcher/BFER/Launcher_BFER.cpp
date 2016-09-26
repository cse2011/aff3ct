#include <string>
#include <iostream>

#include "Tools/bash_tools.h"

#include "Launcher_BFER.hpp"

template <typename B, typename R, typename Q>
Launcher_BFER<B,R,Q>
::Launcher_BFER(const int argc, const char **argv, std::ostream &stream)
: Launcher<B,R,Q>(argc, argv, stream)
{
	this->simu_params.type            = "BFER";
	this->simu_params.max_fe          = 100;
	this->simu_params.benchs          = 0;
	this->simu_params.enable_debug    = false;
	this->simu_params.debug_limit     = 0;
	this->simu_params.enable_leg_term = false;
	this->simu_params.enable_dec_thr  = false;
	this->simu_params.time_report     = false;
	this->simu_params.trace_path_file = "";
	this->enco_params.systematic      = true;
	this->mod_params.demod_max        = "MAX";
}

template <typename B, typename R, typename Q>
void Launcher_BFER<B,R,Q>
::build_args()
{
	Launcher<B,R,Q>::build_args();

	this->opt_args["max-fe"         ] = "n_fe";
	this->doc_args["max-fe"         ] = "max number of frame errors for each SNR simulation.";
	this->opt_args["benchs"         ] = "n_benchs";
	this->doc_args["benchs"         ] = "enable special benchmark mode with a loop around the decoder.";
	this->opt_args["enable-leg-term"] = "";
	this->doc_args["enable-leg-term"] = "enable the legacy display (needed for retro-compatibility with PyBer).";
	this->opt_args["enable-dec-thr" ] = "";
	this->doc_args["enable-dec-thr" ] = "enable the display of the decoder throughput considering only the decoder time.";
	this->opt_args["enable-debug"   ] = "";
	this->doc_args["enable-debug"   ] = "enable debug mode: print array values after each step.";
	this->opt_args["debug-limit"    ] = "n_vals";
	this->doc_args["debug-limit"    ] = "set the max number of elements to display in the debug mode.";
	this->opt_args["trace"          ] = "enables trace";
	this->doc_args["trace"          ] = "traces array values in a CSV file.";
	this->opt_args["time-report"    ] = "";
	this->doc_args["time-report"    ] = "display time information about the simulation chain.";
}

template <typename B, typename R, typename Q>
void Launcher_BFER<B,R,Q>
::store_args()
{
	Launcher<B,R,Q>::store_args();

	// facultative parameters
	if(this->ar.exist_arg("max-fe"         )) this->simu_params.max_fe          = std::stoi(this->ar.get_arg("max-fe"));
	if(this->ar.exist_arg("benchs"         )) this->simu_params.benchs          = std::stoi(this->ar.get_arg("benchs"));
	if(this->ar.exist_arg("enable-leg-term")) this->simu_params.enable_leg_term = true;
	if(this->ar.exist_arg("enable-dec-thr" )) this->simu_params.enable_dec_thr  = true;
	if(this->ar.exist_arg("enable-debug"   )) this->simu_params.enable_debug    = true;
	if(this->ar.exist_arg("debug-limit"    ))
	{
		this->simu_params.enable_debug = true;
		this->simu_params.debug_limit  = std::stoi(this->ar.get_arg("debug-limit"));
	}
	if(this->ar.exist_arg("time-report"    )) this->simu_params.time_report     = true;
	if(this->ar.exist_arg("trace"          )) this->simu_params.trace_path_file = this->ar.get_arg("trace");
}

template <typename B, typename R, typename Q>
void Launcher_BFER<B,R,Q>
::print_header()
{
	Launcher<B,R,Q>::print_header();

	std::string syst_enc = ((this->enco_params.systematic) ? "on" : "off");

	std::string threads = "unused";
	if (this->simu_params.n_threads)
		threads = std::to_string(this->simu_params.n_threads) + " thread(s)";

	// display configuration and simulation parameters
	this->stream << "# " << bold("* Max frame error count     (FE)") << " = " << this->simu_params.max_fe << std::endl;
	this->stream << "# " << bold("* Systematic encoding           ") << " = " << syst_enc                 << std::endl;
	this->stream << "# " << bold("* Decoding algorithm            ") << " = " << this->deco_params.algo   << std::endl;
	this->stream << "# " << bold("* Decoding implementation       ") << " = " << this->deco_params.implem << std::endl;
	this->stream << "# " << bold("* Multi-threading               ") << " = " << threads                  << std::endl;
}

// ==================================================================================== explicit template instantiation 
#include "Tools/types.h"
#ifdef MULTI_PREC
template class Launcher_BFER<B_8,R_8,Q_8>;
template class Launcher_BFER<B_16,R_16,Q_16>;
template class Launcher_BFER<B_32,R_32,Q_32>;
template class Launcher_BFER<B_64,R_64,Q_64>;
#else
template class Launcher_BFER<B,R,Q>;
#endif
// ==================================================================================== explicit template instantiation
