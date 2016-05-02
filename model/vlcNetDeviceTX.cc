/*
 * vlcNetDeviceTX.cc
 *
 *  Created on: Mar 25, 2016
 *      Author: Adel Aldabahi
 */

#include "ns3/vlcNetDeviceTX.h"

namespace vlc {

vlc_NetDeviceTX::vlc_NetDeviceTX(): m_TMAX(60){
	m_semiangle = 70;
	m_angleOfRadiance = 0;
	m_lOrder = 1;
	m_TXGain = 0;
	m_bias = 0;
}

double vlc_NetDeviceTX::GetLambertianOrder(){
	return this->m_lOrder;
}

//before setting Lambertian Order make sure the semiangle value is set
//Need to setup error handling when semiangle is not set
void vlc_NetDeviceTX::SetLambertainOrder(){
	this->m_lOrder = (-1*log(2))/(log(cos(this->m_semiangle)));
}

void vlc_NetDeviceTX::AddTXOpticalPowerSignal(double power){
	this->m_TXOpticalPower.push_back(power);
}
std::vector<double>& vlc_NetDeviceTX::GetTXOpticalPowerSignal(){
	return this->m_TXOpticalPower;
}
double vlc_NetDeviceTX::GetOpticalPowerSignalAtInstant(int time){
	return this->m_TXOpticalPower.at(time);
}
void vlc_NetDeviceTX::SetTXOpticalPowerSignal(std::vector<double> &powerSignal){
	this->m_TXOpticalPower = powerSignal;
}


double vlc_NetDeviceTX::GetTXPowerMax(){
	return this->m_TMAX;
}

void vlc_NetDeviceTX::SetCapacity(int size){

	m_TXOpticalPower.reserve(size);
	m_signal.reserve(size);
}

double vlc_NetDeviceTX::GetSemiangle(){
	return this->m_semiangle;
}

void vlc_NetDeviceTX::SetSemiangle(double angle){
	this->m_semiangle = angle*M_PI/180;
	this->SetLambertainOrder();
}

void vlc_NetDeviceTX::SetAngleOfRadiance(double angle){
	this->m_angleOfRadiance = angle*M_PI/180;
}

double vlc_NetDeviceTX::GetAngleOfRadiance(){
	return this->m_angleOfRadiance;
}

double vlc_NetDeviceTX::GetTXGain(){
	return this->m_TXGain;
}
void vlc_NetDeviceTX::SetTXGain(){
	this->m_TXGain = ((this->m_lOrder + 1)/(2*M_PI))*std::pow(std::cos((long double)this->m_angleOfRadiance),2);
}


void vlc_NetDeviceTX::AddSignal(double signal){
	this->m_signal.push_back(signal);
}

std::vector<double>& vlc_NetDeviceTX::GetSignal(){
	return this->m_signal;
}

double vlc_NetDeviceTX::GetSignalAtInstant(int time){
	return this->m_signal.at(time);
}

void vlc_NetDeviceTX::SetSignal(std::vector<double> &signal){
	this->m_signal = signal;
}

void vlc_NetDeviceTX::SetBias(double bias){
	this->m_bias = bias;
}

double vlc_NetDeviceTX::GetBias(){
	return m_bias;
}


void vlc_NetDeviceTX::BoostSignal(){

	m_TXOpticalPower.clear();

	for(unsigned int i=0;i< m_signal.size();i++){
		m_TXOpticalPower.push_back( (double)(m_signal.at(i) + m_bias) );
		if(m_TXOpticalPower.at(i) > m_TMAX){
			m_TXOpticalPower.at(i) = m_TMAX;
		}

	}

}

double vlc_NetDeviceTX::GetAveragePowerSignalPower(){
	double pMax = this->m_TXOpticalPower.at(0);
	double pMin = this->m_TXOpticalPower.at(m_TXOpticalPower.size()-1);
	return (pMax+pMin)/2;
}

double vlc_NetDeviceTX::GetAverageSignal(){
	double pMax = m_signal.at(0);
	double pMin = m_signal.at(m_signal.size()-1);
	return (pMax+pMin)/2;
}


vlc_NetDeviceTX::~vlc_NetDeviceTX() {

}

} /* namespace vlc */
