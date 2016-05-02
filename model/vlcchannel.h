/*
 * vlcchannel.h
 *
 *  Created on: Mar 23, 2016
 *      Author: Adel Aldalbahi
 */

#ifndef SRC_VLCNEW_VLCCHANNEL_H_
#define SRC_VLCNEW_VLCCHANNEL_H_

#include "ns3/point-to-point-channel.h"
#include "ns3/propagation-loss-model.h"
#include "ns3/propagation-delay-model.h"
#include "ns3/pointer.h"
#include "ns3/ptr.h"
#include "ns3/core-module.h"
#include "ns3/mobility-module.h"
#include "ns3/VlcPropagationLoss.h"
#include "ns3/VLC_SNR.h"
#include "ns3/VLC-error-model.h"
#include "ns3/log.h"

#include "ns3/vlcNetDevice.h"
#include "ns3/vlcNetDeviceTX.h"
#include "ns3/vlcNetDeviceRX.h"


namespace vlc {

class vlc_channel : public ns3::PointToPointChannel {
public:
	vlc_channel();

	virtual ~vlc_channel();

	void SetPropagationLossModel(ns3::Ptr<ns3::PropagationLossModel> loss);  //sets the propagation loss model for the channel

	ns3::Ptr<ns3::PropagationLossModel> GetPropagationLossModel();			//returns a pointer to the propagation loss model

	void SetPropagationDelayModel(ns3::Ptr<ns3::PropagationDelayModel> delay);  //sets the propagation delay model for the channel

	ns3::Ptr<ns3::PropagationDelayModel> GetPropagationDelayModel();  //returns the propagation delay model of the channel

	void SetPropagationDelay(double delay);

	double GetDistance();  //returns the distance after computing the distance using the mobility models of TX and RX

	void SetDistance();		//sets the distance after computing the distance using the mobility models of TX and RX

	void DoCalcPropagationLoss();		//calculates the optical power signal for the RX using the optical power signal of the TX and loss model

	void SetPorpagationLossParametersFromTX();		//sets the parameters of the loss model from the TX

	void SetPorpagationLossParametersFromRX();		//sets the paraameters of the loss model from the RX

	double DoCalcPropagationLossForSignal(int timeInstant);		//computes the optical power signal of RX at a particular instant

	void SetAveragePower(double power);		//computes the averaage power of the signals

	double GetAveragePower();		//returns the average power of the signalss

	void SetWavelength (int lower, int upper);	// sets upper and lower bound wavelength [nm]

	void SetTemperature (double t);		// sets the blackbody temperature of LED

	double GetTemperature();

	void SetReceivedPower (double p);	// sets the average received optical signal power

	void CalculateNoiseVar ();	//calculates the noise variance

	void CalculateSNR ();		// caluclates the SNR value

	double GetSNR () const;		// returns the signal-to-noise ratio (SNR)

	void SetElectricNoiseBandWidth (double b);	// sets the noise bandwidth
	double GetNoiseBandwidth();			//return the noise bandwidth


private:
	ns3::Ptr<ns3::PropagationLossModel> m_loss;
	double m_distanceBWTXandRX;
	ns3::Ptr<ns3::PropagationDelayModel> m_delay;
	double m_AvgPower;
	ns3::Ptr<ns3::VLC_SNR> m_SNR;

};

} /* namespace vlc */

#endif /* SRC_VLCNEW_VLCCHANNEL_H_ */
