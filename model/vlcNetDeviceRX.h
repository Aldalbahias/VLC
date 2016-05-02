/*
 * vlcNetDeviceRX.h
 *
 *  Created on: Mar 25, 2016
 *      Author: Adel Aldalbahi
 */

#ifndef VLCNETDEVICERX_H_
#define VLCNETDEVICERX_H_

#include <math.h>
#include <vector>
#include <cmath>
#include "ns3/vlcNetDevice.h"
#include "ns3/ptr.h"
#include "ns3/VLC-error-model.h"
#include "ns3/error-model.h"
#include "ns3/random-variable-stream.h"
#include "ns3/pointer.h"

namespace vlc {


class vlc_NetDeviceRX : public vlc_NetDevice{
public:
	//constructor for the RX device, initializes all private members to zero
	vlc_NetDeviceRX();

	//destructor for the RX device
	virtual ~vlc_NetDeviceRX();

	//adds a signal instant to the RX optical power signal
	void AddRXOpticalPowerSignal(double power);

	//returns the RX Optical power signal in the form of std::vector of doubles
	std::vector<double>& GetRXOpticalPowerSignal();

	//returns the RX power signal at instant time, time has to be lesser than the capacity of std::vector of signal
	double GetOpticalPowerSignalAtInstant(int time);

	//sets the RX power signal from a std::vector
	void SetRXOpticalPowerSignal(std::vector<double> &powerSignal);

	//sets the size of the signal of RX
	void SetCapacity(int size);

	//sets the filter gain of the RX device
	double GetFilterGain();

	//returns the filter gain of the RX device
	void SetFilterGain(double fgain);

	//returns the photodetector area of the RX device
	double GetPhotoDetectorArea();

	//sets the photo detector area of the RX device
	void SetPhotoDectectorArea(double pArea);

	//returns the FOV angle of the RX device
	double GetFOVAngle();

	//sets the FOV angle of the RX device
	void SetFOVAngle(double angle);

	//returns the refractive index of the RX device
	double GetRefractiveIndex();

	//sets the refractive index of the RX device
	void SetRefractiveIndex(double angle);

	//returns the concentration gain of the RX device
	double GetConcentrationGain();

	//sets the concentration gain of the RX device
	void SetConcentrationGain();

	//returns the total gain of the RX device
	double GetRXGain();
	//sets the total gain of the RX device using internal parameters
	void SetRXGain();

	//sets the incidence angle of the RX device
	void SetIncidenceAngle(double angle);

	//returns the concentration gain of the RX device
	double GetIncidenceAngle();

	ns3::VLC_ErrorModel::ModScheme GeModulationtScheme (void) const;	 // returns the modulation scheme used

	void SetScheme (std::string scheme); // sets the value of the modulation scheme used

	void SetRandomVariableForErrorModel (ns3::Ptr<ns3::RandomVariableStream> ranVar);	// assigns a random variable stream to be used by this model

	int64_t AssignStreamsForErrorModel (int64_t stream);	// assigns a fixed stream number to the random variables used by this model

	double GetSNRFromErrorModel (void) const;		// returns the signal-to-noise ratio (SNR)

	void SetSNRForErrorModel (double snr);		// sets the SNR value

	double CalculateErrorRateForErrorModel (void);		// calculates the error rate value according to modulation scheme

	bool IsCorrupt (ns3::Ptr<ns3::Packet> pkt);	// determines if the packet is corrupted according to the error model

	// methods for PAM
	int GetModulationOrder (void) const;	// returns the modulation order (M)
	void SetModulationOrder (int m_order);	// sets the modulation order value

	// methods for VPPM
	double GetAlpha(void) const;	// returns alpha value
	void SetAlpha (double a);		// sets alpha value

	double GetBeta(void) const;		// returns beta value
	void SetBeta (double b);		// sets beta value


private:
	std::vector<double> m_RXOpticalPower;
	std::vector<double> m_signal;
	double m_filterGain;
	double m_photodetectorArea;
	double m_FOVangle;
	double m_refIndex;
	double m_angleOfIncidence;
	double m_concentrationGain;
	double m_RXGain;
	double m_bias;
	ns3::Ptr<ns3::VLC_ErrorModel> m_error;

};

} /* namespace vlc */


#endif /* VLCNETDEVICERX_H_ */
