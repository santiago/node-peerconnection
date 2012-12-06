//
// PeerConnection.h
//
// CC 2012 Sofrit0 <sgaviria@gmail.com>
//

#ifndef __NODE_PEERCONNECTION_H__
#define __NODE_PEERCONNECTION_H__

#include <v8.h>
#include <node.h>

#include "talk/base/scoped_ptr.h"
#include "talk/app/webrtc/peerconnection.h"
#include "talk/app/webrtc/peerconnectionfactory.h"

using namespace v8;
using namespace node;

namespace NodePeerConnection {
  extern const char kAudioLabel[];
  extern const char kVideoLabel[];
  extern const char kStreamLabel[];

  class PeerConnection: public node::ObjectWrap, public webrtc::PeerConnectionObserver {
    public:
      PeerConnection();
      virtual ~PeerConnection();
  
      static Persistent<FunctionTemplate> constructor;
      static void Initialize(Handle<Object> target);
      static Handle<Value> New(const Arguments &args);
    
      static Handle<Value> AddStream(const Arguments &args);
      static Handle<Value> RemoveStream(const Arguments &args);
      static Handle<Value> CanSendDtmf(const Arguments &args);
      static Handle<Value> SendDtmf(const Arguments &args);
      static Handle<Value> CreateOffer(const Arguments &args);
      static Handle<Value> CreateAnswer(const Arguments &args);
      static Handle<Value> SetLocalDescription(const Arguments &args);
      static Handle<Value> SetRemoteDescription(const Arguments &args);
      static Handle<Value> UpdateIce(const Arguments &args);
      static Handle<Value> AddIceCandidate(const Arguments &args);

      /*static Handle<Value> GetReadyState(Local<String> prop, const AccessorInfo &info);
      static Handle<Value> GetIceState(Local<String> prop, const AccessorInfo &info);
    
      static Handle<Value> GetLocalDescription(Local<String> prop, const AccessorInfo &info);
      static Handle<Value> GetRemoteDescription(Local<String> prop, const AccessorInfo &info);*/

    protected:
      void DeletePeerConnection();
    
      virtual void OnError();
      virtual void OnStateChange(
        webrtc::PeerConnectionObserver::StateType state_changed) {}
      virtual void OnAddStream(webrtc::MediaStreamInterface* stream);
      virtual void OnRemoveStream(webrtc::MediaStreamInterface* stream);
      virtual void OnRenegotiationNeeded() {}
      virtual void OnIceChange() {}
      virtual void OnIceCandidate(const webrtc::IceCandidateInterface* candidate);
      
    private:
      int peer_id_;
      talk_base::scoped_refptr<webrtc::PeerConnectionInterface> peer_connection_;
      talk_base::scoped_refptr<webrtc::PeerConnectionFactoryInterface>
        peer_connection_factory_;
    
      std::map<std::string, talk_base::scoped_refptr<webrtc::MediaStreamInterface> >
        active_streams_;
      std::string server_;
  };
}

#endif // __NODE_PEERCONNECTION_H__