/*
 * vlcDeviceHelper.cpp
 *
 *  Created on: Apr 9, 2016
 *      Author: adel
 */

#include "vlcDeviceHelper.h"



namespace vlc {

vlc_DeviceHelper::vlc_DeviceHelper() {


}

void vlc_DeviceHelper::CreateTransmitter(std::string TXName){
	m_TXDevices[TXName] = CreateObject<vlc::vlc_NetDeviceTX>();
}

void vlc_DeviceHelper::CreateReceiver(std::string RXName){
	m_RXDevices[RXName] = CreateObject<vlc::vlc_NetDeviceRX>();
}

void vlc_DeviceHelper::SetTrasmitterParameter(std::string devName, std::string paramName, double value ){

	if(paramName=="SemiAngle"){
		m_TXDevices[devName]->SetSemiangle(value);
	}
	else if(paramName=="AngleOfRadiance"){
		m_TXDevices[devName]->SetAngleOfRadiance(value);
	}
	else if(paramName=="LambertianOrder"){
		m_TXDevices[devName]->SetLambertainOrder();
	}
	else if(paramName=="Gain"){
		m_TXDevices[devName]->SetTXGain();
	}
	else if(paramName=="Bias"){
		m_TXDevices[devName]->SetBias(value);
	}
	else if(paramName=="Azimuth"){
		m_TXDevices[devName]->SetAzmuth(value);
	}
	else if(paramName=="Elevation"){
		m_TXDevices[devName]->SetElevation(value);
	}
	else if(paramName=="DataRateInMBPS"){
		std::ostringstream strs;
		strs << value;
		std::string str = strs.str();
		str = str + "Mbps";
		DataRate drate(str);
		m_TXDevices[devName]->SetDataRate(drate);
	}


}

void vlc_DeviceHelper::SetTrasmitterPosition(std::string devName, double x, double y, double z){
	m_TXDevices[devName]->SetPosition(Vector(x,y,z));
}

void vlc_DeviceHelper::SetReceiverPosition(std::string devName, double x, double y, double z){
	m_RXDevices[devName]->SetPosition(Vector(x,y,z));
}

void vlc_DeviceHelper::SetTrasmitterBoost(std::string devName){
	m_TXDevices[devName]->BoostSignal();
}

void vlc_DeviceHelper::SetReceiverParameter(std::string devName, std::string paramName, double value ){
	if(paramName=="FilterGain"){
		m_RXDevices[devName]->SetFilterGain(value);
	}
	else if(paramName=="PhotoDetectorArea"){
		m_RXDevices[devName]->SetPhotoDectectorArea(value);
	}
	else if(paramName=="FOVAngle"){
		m_RXDevices[devName]->SetFOVAngle(value);
	}
	else if(paramName=="RefractiveIndex"){
		m_RXDevices[devName]->SetRefractiveIndex(value);
	}
	else if(paramName=="IncidenceAngle"){
		m_RXDevices[devName]->SetIncidenceAngle(value);
	}
	else if(paramName=="ConcentrationGain"){
		m_RXDevices[devName]->SetConcentrationGain();
	}
	else if(paramName=="RXGain"){
		m_RXDevices[devName]->SetRXGain();
	}
	else if(paramName=="SetModulationScheme"){
		if(value==0){
			m_RXDevices[devName]->SetScheme( "OOK" );
		}
		else if(value==1){
			m_RXDevices[devName]->SetScheme("PAM");
		}
		else if(value==2){
			m_RXDevices[devName]->SetScheme("VPPM");
		}
	}
	else if(paramName=="DutyCycle"){
		m_RXDevices[devName]->SetAlpha(value);
	}
	else if(paramName=="Beta"){
		m_RXDevices[devName]->SetBeta(value);
	}


}

double vlc_DeviceHelper::GetReceiverParameter(std::string devName,std::string paramName){
	if(paramName=="BER"){
		return this->m_RXDevices[devName]->CalculateErrorRateForErrorModel();
	}
	else if(paramName=="SER"){
		return this->m_RXDevices[devName]->CalculateErrorRateForErrorModel();
	}
	return 0;
}

std::vector<double> vlc_DeviceHelper::GenerateSignal(int size,double dutyRatio,double bias, double VMax,double VMin){

	std::vector<double> result;
	result.reserve(size);

	for(int i=0;i<size;i++){

		if(i<size*dutyRatio){
			result.push_back(VMax+bias);
		}
		else{
			result.push_back(VMin+bias);
		}
	}

	return result;

}

void vlc_DeviceHelper::SetTXSignal(std::string devName,int size,double dutyRatio,double bias, double VMax,double VMin){

	std::vector<double> r =  GenerateSignal(size, dutyRatio, bias, VMax, VMin) ;
	m_TXDevices[devName]->SetSignal(r);

}

ns3::Ptr<vlc_NetDeviceTX> vlc_DeviceHelper::GetTransmitter(std::string devName){

	return this->m_TXDevices[devName];

}
ns3::Ptr<vlc_NetDeviceRX> vlc_DeviceHelper::GetReceiver(std::string devName){

	return this->m_RXDevices[devName];
}



vlc_DeviceHelper::~vlc_DeviceHelper() {
	this->m_RXDevices.clear();
	this->m_TXDevices.clear();
}

} /* namespace vlc */
