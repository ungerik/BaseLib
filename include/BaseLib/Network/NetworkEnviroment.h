/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef NetworkEnviroment_h
#define NetworkEnviroment_h



#include "BaseLib/Network/AbstractConnection.h"
#include "BaseLib/Functors/Enumerator.h"



namespace BaseLib {
namespace Network {



using BaseLib::Functors::Enumerator;



class BL_EXPORT NetworkEnviroment {
public:

	// Global:

	static void enumNetworkEnviromentProtocolPorts(const Enumerator<uint16>& enumerator);
	static void addNetworkEnviromentProtocolPort(uint16 port);
	static void removeNetworkEnviromentProtocolPort(uint16 port);

	static int getDownloadBandwidth();
	static int getUploadBandwidth();

	static int getDownloadBandwidthLimit(); // -1 is maximum
	static void setDownloadBandwidthLimit(int newDownloadBandwidth);
	static int getUploadBandwidthLimit();
	static void setUploadBandwidthLimit(int newUploadBandwidth);

	// Peers:

	static void enumPeersInLan(const Enumerator<String>& enumerator);

	static void addPeer(const String& peerName);
	static void removePeer(const String& peerName);

	static int getPeerDownloadBandwidthLimit(const String& peerName);
	static void setPeerDownloadBandwidthLimit(const String& peerName, int newDownloadBandwidth);
	static int getPeerUploadBandwidthLimit(const String& peerName);
	static void setPeerUploadBandwidthLimit(const String& peerName, int newUploadBandwidth);
	
	// Protocols:

	static void addOwnProtocol(const String& protocol, uint16 port);
	static void removeOwnProtcol(const String& protocol);

	static void enumOwnProtocols(const Enumerator<String>& enumerator);
	static uint16 getOwnProtocolPort(const String& protocol);
	
	static void enumPeerProtocols(const String& peerName, const Enumerator<String>& enumerator);
	static uint16 getPeerProtocolPort(const String& peerName, const String& protocol);

	// Peer Gateways:

	static int getGatewayCountOfPeer(const String& peerName);
	static int getDownloadBandwidthOfGateway(const String& peerName, int gatewayIndex = 0);
	static int getUploadBandwidthOfGateway(const String& peerName, int gatewayIndex = 0);

	static void enumPeersBehindGateway(const String& peerName, const Enumerator<String>& enumerator);

	// Own Gateways:

	static int getOwnGatewayCount();
	static void addGateway(int downloadBandwidth = -1, int uploadBandwidth = -1);
	static void removeGateway(int gatewayIndex);

	static int getOwnGatewayDownloadBandwidth(int gatewayIndex);
	static void setOwnGatewayDownloadBandwidth(int gatewayIndex, int newDownloadBandwidth);
	static int getOwnGatewayUploadBandwidth(int gatewayIndex);
	static void setOwnGatewayUploadBandwidth(int gatewayIndex, int newUploadBandwidth);

	static int getPeerCountBehindOwnGateway(int gatewayIndex);
	static void addPeerBehindOwnGateway(const String& peerName, int gatewayIndex);
	static void removePeerBehindOwnGateway(const String& peerName, int gatewayIndex);


};



} // namespace Network
} // namespace BaseLib



#endif // #ifndef NetworkEnviroment_h