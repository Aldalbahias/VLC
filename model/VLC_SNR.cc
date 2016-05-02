#include <math.h>
#include <cmath>
#include "VLC_SNR.h"
#include "ns3/double.h"
#include "ns3/integer.h"
#include "ns3/log.h"


namespace ns3 {
	
NS_LOG_COMPONENT_DEFINE ("VLC_SNR");	// define a log component with the name "VLC_SNR"
 
NS_OBJECT_ENSURE_REGISTERED (VLC_SNR);	// register VLC_SNR class with the TypeId system
 
TypeId VLC_SNR::GetTypeId (void)	// returns meta-information about VLC_SNR class 
{ 									// including parent class, group name, constructor, and attributes
	static TypeId tid = TypeId ("ns3::VLC_SNR")
		.SetParent<Object> ()
		.SetGroupName("Network")
		.AddConstructor<VLC_SNR> ()
		.AddAttribute ("PowerReceived", "average received optical signal power",
						DoubleValue (0),
						MakeDoubleAccessor (&VLC_SNR::Pr),
						MakeDoubleChecker<double> ())
		.AddAttribute ("SNR", "signal-to-noise-ratio",
						DoubleValue (0),
						MakeDoubleAccessor (&VLC_SNR::SNR),
						MakeDoubleChecker<double> ())
		.AddAttribute ("LowerWavelength", "lower bound WaveLength",
						IntegerValue (0),
						MakeIntegerAccessor (&VLC_SNR::wavelength_lower),
						MakeIntegerChecker<int> ())
		.AddAttribute ("UpperWavelength", "upper bound WaveLength",
						IntegerValue (0),
						MakeIntegerAccessor (&VLC_SNR::wavelength_upper),
						MakeIntegerChecker<int> ())
		.AddAttribute ("Temperature", "Blackbody temp of LED",
						DoubleValue (0),
						MakeDoubleAccessor (&VLC_SNR::temp),
						MakeDoubleChecker<double> ())
	;
	return tid;
}

//Values of the Standard Luminocity Functions
double VLC_SNR::V_lambda[] = { 
0.000039, 0.000120, 0.000396, 0.001210, 0.004000, 0.011600, 0.023000, 
0.038000, 0.060000, 0.090980, 0.139020, 0.208020, 0.323000,  0.503000, 
0.710000, 0.862000, 0.954000, 0.994950,  0.995000, 0.952000, 0.870000, 
0.757000, 0.631000, 0.503000, 0.381000, 0.265000, 0.175000, 0.107000, 
0.061000, 0.032000, 0.017000, 0.008210, 0.004102, 0.002091, 0.001047, 
0.000520, 0.000249, 0.000120, 0.000060, 0.000030 };

//General values for Respositvity 
double VLC_SNR::Response[] = { 
0.150, 0.160, 0.170, 0.190, 0.200, 0.220, 0.230, 0.240, 0.250, 0.260, 
0.270, 0.280, 0.300, 0.320, 0.330, 0.350, 0.360, 0.370, 0.375, 0.380, 
0.390, 0.400, 0.415, 0.420, 0.430, 0.440, 0.450, 0.460, 0.470, 0.475,
0.480, 0.485, 0.490, 0.495, 0.500, 0.505, 0.510, 0.520, 0.526, 0.532 };

// constructor
VLC_SNR::VLC_SNR ()
{
	NS_LOG_FUNCTION (this);
	noise_var = 0;   // total noise variance
	Pr = 0;			// average received optical signal power
	res = 0;  		// responsitivity of receiver
	SNR = 0;  		// signal-to-noise ratio
	B = 0;
	wavelength_lower = 0;	// lower bound WaveLength [nm]
	wavelength_upper = 0;	// upper bound Wavelength [nm]
	temp = 0;  			// Blackbody temp of LED
}

// destructor
VLC_SNR::~VLC_SNR ()
{
	NS_LOG_FUNCTION (this);
}

// sets upper and lower bound wavelength 
void VLC_SNR::SetWavelength (int lower, int upper)
{
	NS_LOG_FUNCTION (this << lower << upper);
	wavelength_lower = lower;
	wavelength_upper = upper;
}

// sets the blackbody temperature of LED
void VLC_SNR::SetTemperature (double t)
{
	NS_LOG_FUNCTION (this << t);
	temp = t;
}

double VLC_SNR::GetTemperature(){
	NS_LOG_FUNCTION (this );
	return this->temp;
}

// sets the average received optical signal power
void VLC_SNR::SetReceivedPower (double p)
{
	NS_LOG_FUNCTION (this << p);
	Pr = p;
}

// CalculateNoiseVar method calculates the noise variance using the following parameters:
// Ib: background current [A]
// I2: noise-bandwidth factor
// I3: 
// A: photodetector Area [m^2]
// B: noise bandwidth
// Tk: absolute temperature [K]
// Cpd: fixed capacitance of photodetector per unit area [F/cm^2]
// Gol: open-loop voltage gain
// gamma: FET channel noise factor
// gm: FET transconductance [s]
void VLC_SNR::CalculateNoiseVar ( double A)
{
	NS_LOG_FUNCTION (this);
	
	//res = IntegralRes() / IntegralPlanck();
	res = 0.003;
	
	static const double q = 1.602176487e-19;		//electronic charge [Coulombs]
	static const double k = 1.38064852e-23;		//Boltzmann constant [m^2 kg s^-2 K^-1]
	static const double I2 = 0.5620; //noise bandwidth factor
	double I3 = 0.0868; //noise bandwidth factor
	double Ib = 5100e-6; //photocurrent due to background radiation [microA]
	double Gol = 10; //open-loop voltage gain
	double Cpd = 112e-12; //fixed capacitance of photodetector per unit area [pF/cm^2]
	double gm = 30e-3; //FET transconductance [mS]
	double	gamma = 1.5; //FET channel noise factor

	double shot_var, thermal_var;

	// shot noise variance
	shot_var = (2 * q * res * Pr * B) + (2 * q * Ib * I2 * B);

	// thermal noise variance
	thermal_var = (8 * M_PI * k * temp * Cpd * A * I2 * (std::pow(B, 2)) / Gol)
	+ (16 * (std::pow(M_PI, 2)) * k * temp * gamma * (std::pow(Cpd, 2)) * (std::pow(A, 2)) * I3 * (std::pow(B, 3)) / gm);
	
	noise_var = shot_var + thermal_var;
}

// caluclates the SNR value using received power, responsivity and noise variance
void VLC_SNR::CalculateSNR ()
{
	NS_LOG_FUNCTION (this);
	if (noise_var != 0)
		SNR = std::pow((Pr * res), 2) / noise_var;
}

// returns the signal-to-noise ratio (SNR)
double VLC_SNR::GetSNR ()
{
	NS_LOG_FUNCTION (this);
	CalculateSNR();
	return SNR;
}

// Definite integral of the Spectral Radiance(wavelength, temperature) d(wavelength)
double VLC_SNR::IntegralPlanck()
{
	NS_LOG_FUNCTION (this);
	double integral = 0;       

	while(wavelength_lower <= wavelength_upper)
	{
		integral += SpectralRadiance(wavelength_lower, temp) * 10e-9;
		wavelength_lower += 10;
	}
	return integral;
}

// Definite integral of the Response(wavelength)*Spectral Radiance(wavelength, temperature) d(wavelength)
double VLC_SNR::IntegralRes()
{
	NS_LOG_FUNCTION (this);
	double integral = 0;
	while(wavelength_lower <= wavelength_upper)
	{
		integral += Response[(wavelength_lower - 380) / 10] * SpectralRadiance(wavelength_lower, temp) * 10e-9;
		wavelength_lower += 10;
	}
	return integral;
}

void VLC_SNR::SetElectricNoiseBandWidth (double b){	// sets the noise bandwidth
	NS_LOG_FUNCTION (this);
	B = b;
}

double VLC_SNR::GetNoiseBandwidth(){			//return the noise bandwidth
	NS_LOG_FUNCTION (this);
	return B;
}

// Calculates Spectral Radiance based on wavelength and Blackbody temp of LED
double VLC_SNR::SpectralRadiance(int wavelength, double temperature)
{
	NS_LOG_FUNCTION (this);
	double spectral_rad;
	double h = 6.62607004;	//Planck's constant
	double c = 299792458;	//speed of light
	double k = 1.3806488e-23;	//Boltzmann constant
	double waveLength = wavelength * 1e-9; //nm
	spectral_rad = 15 * (std::pow((h * c) / ( M_PI * k * temperature), 4)) 
					/ ((std::pow(waveLength, 5)) * ((std::exp((h * c) / (waveLength * k * temperature))) - 1));
	return spectral_rad;
}

} // namespace ns3
