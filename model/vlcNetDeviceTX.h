/*
 * vlcNetDeviceTX.h
 *
 *  Created on: Mar 25, 2016
 *      Author: Adel Aldabahi
 */

#ifndef VLCNETDEVICETX_H_
#define VLCNETDEVICETX_H_



#include "ns3/core-module.h"
#include "ns3/vlcNetDevice.h"
#include "ns3/ptr.h"
#include "ns3/vlcchannel.h"
#include <cmath>


namespace vlc {

class vlc_NetDeviceTX : public vlc::vlc_NetDevice {

public:
	vlc_NetDeviceTX();

	virtual ~vlc_NetDeviceTX();

	//adds a signal instant to the TX optical power signal
	void AddTXOpticalPowerSignal(double power);

	//returns the TX Optical power signal in the form of std::vector of doubles
	std::vector<double>& GetTXOpticalPowerSignal();

	//returns the TX power signal at instant time, time has to be lesser than the capacity of std::vector of signal
	double GetOpticalPowerSignalAtInstant(int time);

	//sets the TX power signal from a std::vector
	void SetTXOpticalPowerSignal(std::vector<double> &powerSignal);

	//reserves the capacity of signal vector
	void SetCapacity(int size);

	//returns the semiangle of the TX device
	double GetSemiangle();

	//sets the semianle of the TX device
	void SetSemiangle(double angle);

	//sets the angle of radiance of the TX device
	void SetAngleOfRadiance(double angle);

	//returns the angle of radiance of the TX device
	double GetAngleOfRadiance();

	//returns the lambertian order of the TX device
	double GetLambertianOrder();

	//computes and then sets the lambertian order of the TX device
	void SetLambertainOrder();

	//returns the gain of the TX device
	double GetTXGain();
	//computes and sets the gain of the TX device
	void SetTXGain();

	//adds a signal component to the signal vector
	void AddSignal(double signal);

	//returns the signal vector of the TX device
	std::vector<double>& GetSignal();

	//returns the magnitude of the signal at a particular instant
	double GetSignalAtInstant(int time);

	//sets the signal vector of the TX device
	void SetSignal(std::vector<double> &signal);

	//sets the bias voltage of the TX device
	void SetBias(double bias);

	//returns the bias voltage of the TX device
	double GetBias();

	//calculates the optical power signal after biasing it by m_bias
	void BoostSignal();

	//returns the Maximum TX power that can be transmitted
	double GetTXPowerMax();

	//returns the average of TX Power signal
	double GetAveragePowerSignalPower();


	//returns the average of the TX signal
	double GetAverageSignal();


private:
	std::vector<double> m_TXOpticalPower;
	std::vector<double> m_signal;
	const double m_TMAX;
	double m_semiangle;
	double m_angleOfRadiance;
	double m_lOrder;
	double m_TXGain;
	double m_bias;

};

} /* namespace vlc */

#endif /* VLCNETDEVICETX_H_ */
