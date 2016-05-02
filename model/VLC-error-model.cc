#include <cmath>
#include "VLC-error-model.h"
#include "ns3/packet.h"
#include "ns3/assert.h"
#include "ns3/log.h"
#include "ns3/boolean.h"
#include "ns3/enum.h"
#include "ns3/integer.h"
#include "ns3/double.h"
#include "ns3/string.h"
#include "ns3/pointer.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("VLC_ErrorModel");	// define a log component with the name "VLC_ErrorModel"
 
NS_OBJECT_ENSURE_REGISTERED (VLC_ErrorModel);	// register VLC_ErrorModel class with the TypeId system
 
TypeId VLC_ErrorModel::GetTypeId (void)	// returns meta-information about VLC_ErrorModel class 
{ 										// including parent class, group name, constructor, and attributes
	static TypeId tid = TypeId ("ns3::VLC_ErrorModel")
		.SetParent<RateErrorModel> ()
		.SetGroupName("Network")
		.AddConstructor<VLC_ErrorModel> ()
		.AddAttribute ("ModulationOrder", "The modulation order (M)",
						IntegerValue (0),
						MakeIntegerAccessor (&VLC_ErrorModel::mod_order),
						MakeIntegerChecker<int> ())
		.AddAttribute ("Alpha", "The duty cycle of the VPPM signal",
						DoubleValue (0.0),
						MakeDoubleAccessor (&VLC_ErrorModel::alpha),
						MakeDoubleChecker<double> ())
		.AddAttribute ("Beta", "A factor relating noise bandwidth to signal bandwidth",
						DoubleValue (0.0),
						MakeDoubleAccessor (&VLC_ErrorModel::beta),
						MakeDoubleChecker<double> ())
		.AddAttribute ("SNR", "Signal-to-Noise Ratio",
						DoubleValue (0.0),
						MakeDoubleAccessor (&VLC_ErrorModel::SNR),
						MakeDoubleChecker<double> ())
		.AddAttribute ("RanVar1", "The decision variable attached to this error model.",
						StringValue ("ns3::UniformRandomVariable[Min=0.0|Max=1.0]"),
						MakePointerAccessor (&VLC_ErrorModel::m_ranvar),
						MakePointerChecker<RandomVariableStream> ())
		.AddAttribute ("ModulationScheme", "The modulation scheme used in this model", 
						EnumValue (PAM),
						MakeEnumAccessor (&VLC_ErrorModel::mod_scheme),
						MakeEnumChecker (PAM, "PAM",
										 OOK, "OOK",
										 VPPM, "VPPM"))
	;
	return tid;
}

// constructor
VLC_ErrorModel::VLC_ErrorModel ()
{

	NS_LOG_FUNCTION (this);

	alpha = 0;
	beta = 1;
	SNR = 0;
	mod_order = 0;
	mod_scheme = OOK;

}

// destructor
VLC_ErrorModel::~VLC_ErrorModel ()
{
	NS_LOG_FUNCTION (this);
}

VLC_ErrorModel::ModScheme		 
VLC_ErrorModel::GetScheme (void) const	// returns the modulation scheme used
{
	NS_LOG_FUNCTION (this);
	return mod_scheme; 
}

void
VLC_ErrorModel::SetScheme (ModScheme scheme)	// sets the value of the modulation scheme used
{
	NS_LOG_FUNCTION (this << scheme);
	mod_scheme = scheme;
	if (scheme == OOK)
		mod_order = 2;
}


void VLC_ErrorModel::SetScheme (std::string scheme){			// sets the value of the modulation scheme used
	NS_LOG_FUNCTION (this << scheme);
	if(scheme=="PAM"){
		SetScheme(VLC_ErrorModel::PAM);
	}
	else if(scheme=="OOK"){
		SetScheme(VLC_ErrorModel::OOK);
	}
	else if(scheme=="VPPM"){
		SetScheme(VLC_ErrorModel::VPPM);
	}

}
// SetRandomVariable method assigns a random variable stream to be used by this model
void 
VLC_ErrorModel::SetRandomVariable (Ptr<RandomVariableStream> ranvar)
{
	NS_LOG_FUNCTION (this << ranvar);
	m_ranvar = ranvar;
}

//AssignStreams method assigns a fixed stream number to the random variables used by this model
int64_t 
VLC_ErrorModel::AssignStreams (int64_t stream)
{
	NS_LOG_FUNCTION (this << stream);
	m_ranvar->SetStream (stream);
	return 1;
}
  
// GetModulationOrder method returns the modulation order (M)
int
VLC_ErrorModel::GetModulationOrder (void) const 
{ 
	NS_LOG_FUNCTION (this);
	return mod_order; 
}

// SetModulationOrder method sets the modulation order value
void 
VLC_ErrorModel::SetModulationOrder (int m_order) 
{ 
	NS_LOG_FUNCTION (this << m_order);
	mod_order = m_order; 
}

// GetAlpha method returns alpha value
double
VLC_ErrorModel::GetAlpha (void) const 
{ 
	NS_LOG_FUNCTION (this);
	return alpha; 
}

// SetAlpha method sets alpha value
void 
VLC_ErrorModel::SetAlpha (double a) 
{ 
	NS_LOG_FUNCTION (this << a);
	alpha = a; 
}

// GetBeta method returns beta value
double
VLC_ErrorModel::GetBeta (void) const 
{ 
	NS_LOG_FUNCTION (this);
	return beta; 
}

// SetBeta method sets beta value
void 
VLC_ErrorModel::SetBeta (double b) 
{ 
	NS_LOG_FUNCTION (this << b);
	beta = b; 
}

// GetSNR method returns the signal-to-noise ratio (SNR) value
double
VLC_ErrorModel::GetSNR (void) const 
{ 
	NS_LOG_FUNCTION (this);
	return SNR; 
}

// SetSNR method sets the SNR value
void 
VLC_ErrorModel::SetSNR (double snr) 
{ 
	NS_LOG_FUNCTION (this << snr);
	SNR = snr; 
}

// CalculateErrorRate calculates SER or BER value according to modulation scheme
double
VLC_ErrorModel::CalculateErrorRate (void)
{
	NS_LOG_FUNCTION (this);
	if (mod_scheme == VPPM)
		return CalculateBER();
	else if (mod_scheme == PAM || mod_scheme == OOK)
		return CalculateSER();
	return 0;
}

// CalculateSER method calculates the SER value of OOK and PAM models
// using modulation order(M) and SNR
double VLC_ErrorModel::CalculateSER (void)
{
	NS_LOG_FUNCTION (this);
	// Calculate Q(sqrt(SNR) / (M-1))
	// Q-function is the tail probability of the standard normal distribution
	double Q = 0.5 * erfc( (std::sqrt(SNR) / (mod_order-1) ) / std::sqrt(2));
	double SER = (2 * (mod_order-1) / mod_order) * Q;
	SetRate(SER);
	if (mod_scheme == OOK)
		SetUnit(ERROR_UNIT_BIT);
	return SER;
}

// CalculateBER method calculates the BER of VPPM model using alpha, beta and SNR
double VLC_ErrorModel::CalculateBER (void)
{
	NS_LOG_FUNCTION (this);
	double x; // the vaue to calculate Q(x)
	if (alpha <= 0.5)
		x = std::sqrt(SNR / (2 * beta * alpha));
	else
		x = std::sqrt(SNR * (1 - alpha) / (2 * beta * std::pow(alpha, 2)));
	// Calculate BER = Q(x)
	// Q-function is the tail probability of the standard normal distribution
	double Q = 0.5 * erfc(x / std::sqrt(2));
	SetRate(Q);	// call SetRate method in parent class RateErrorModel to set m_rate to BER value
	SetUnit(ERROR_UNIT_BIT);
	return Q;
}

// DoCorrupt method determines if the packet is corrupted according to the error model used
bool VLC_ErrorModel::IsCorrupt (Ptr<Packet> p)
{
	NS_LOG_FUNCTION (this << p);
	
	if (mod_scheme == PAM || mod_scheme == OOK)
	{
		// check if the model is enabled
		if (!IsEnabled ())
		{
			return false;
		}
		
		// computes pkt error rate from symbol error rate
		double symbol_size = log2(mod_order);	// symbol size in bits
		double symbols_per_pkt = static_cast<double>(8 * p->GetSize ()) / symbol_size; // no. of symbols per packet
		// Compute pkt error rate by finding the complement of the probablility 
		// that a packets is not corrupted
		// = (1 - the probability that all symbols in pkt are not corrupted)
		double per = 1 - std::pow (1.0 - GetRate(), symbols_per_pkt);
		// the pkt is corrupted according to PER
		// using random variable m_ranvar
		return (m_ranvar->GetValue () < per);
	}
	
	// for VPPM scheme, call the method defined in parent class RateErrorModel
	else
	{
		RateErrorModel::SetRandomVariable(m_ranvar);
		return RateErrorModel::IsCorrupt(p);
	}
}


// DoReset method does nothing
void VLC_ErrorModel::DoReset (void)
{ 
	NS_LOG_FUNCTION (this);
	/* re-initialize any state; no-op for now */ 
}

} // namespace ns3
