
..highlight:: bash

Visible light communication module Integration (vlcnew)
**************************************************
visible light communication is the mean of using light intensity for the purpose of communication. Visible light has been around for few years where this technology allows the use of unlimited bandwidth, lower power consumption and immunity to interference when compared to the conventional  RF technology.

Model Description
************************
The source code for the new module lives in the directory ``src/vlcnew``.

Design
======
This module can be used to investigate visible light communication  at both network and physical layer using different modulation schemes such as OOK, #PAM and VPPM. The module is consists of related classes some of which are inherited from ns3's classes. The main idea of this module is simulate large-scale visible light communication system that can be very costly to implemented in real life. This simulator is built to help researchers who are interested in in studying the signal to noise ratio (SNR), bit error rate (BER) and goodput of visible light under different network topology. At this moment, we implemented two classes one transmitter and the second is receiver in addition different classes for propagation loss, error rate  and many more. The transmitter gain is implemented inside the transmitter and the receiver gain is implemented inside the receiver.  The channel know both tx and rx gain and is able to compute the loss as the receiver moves away using our mobility model that we inherited form ns3 to crap both devices's orientation. 

Scope and Limitations
=====================
This module can investigate the channel condition under different modulation schemes. In addition it can help to investigate the network performance under different topology a user can create. At this stage the visible light standard did not implemented. 


References
==========
Extending ns3 to simulate visible light communication at network-level (http://ieeexplore.ieee.org/document/7500485/)

Usage
*****

This section is principally concerned with the usage of your model, using
the public API.  Focus first on most common usage patterns, then go
into more advanced topics.



Helpers
=======
 the easiest way to vlc node to node communication is by using the following helpers: 

vlcChannelHelper : to create a vlc channel 
vlc_DeviceHelper : to set transmitter and the receiver parameters
transmitter parameters: 
Our signal is a positive square form  signal that is pushed into the transmitter power taking the time as parameter.  The signal consists of the following parameters: 
1- size 
2- Duty ratio 
3- bias 
4- Max 
5- Min 

In addition to the above parameter, the transmitter has “Transmitter gain” with the  following parameters: 
1- Semiangle
2-Angle of irradiance
3- Lambertian Order. 

Also the following parameter from the mobility model : 
1-Position
2- Azimuth 
3- Elevation  

Others Parameters: 
Transmitter Data rate 

Receiver Parameters: 
1-Filter gain 
2-refractive index 
3-filed of view 
4-concentration gain 
5- Incidence Angle
5-PhotoDetectorArea
6-duty cycle ( for VPPM error model) 
7-beta 
8-elevation 
9-position 
10-Azimuth 
Also from the receiver we can choose the applied Modulation scheme where :
0 value  represent OOK
1 value  represent 4-PAM 
2 value represent VPPM




Attributes
==========

What classes hold attributes, and what are the key ones worth mentioning? // will be gevin in details soon

Output
======

What kind of data does the model generate?  What are the key trace
sources?   What kind of logging output can be enabled? // will be gevin in details soon

Examples
========

Ath this moment one example is implemented to test this module called : "VPPMtest.cc". The example is consist of 4 nodes where vlc is used to generate downlink traffic and WiFi is used as an uplink. A user can also generate traffic for different modulation scheme (mentioned in helper above). 


Validation
**********

Describe how the model has been tested/validated.  What tests run in the
test suite?  How much API and code is covered by the tests?  Again, 
references to outside published work may help here.
